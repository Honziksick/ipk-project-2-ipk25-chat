/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPClientFSM.cpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      18.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `UdpClientFsm` class, which represents  *
 *               the finite state machine (FSM) for managing client-side       *
 *               operations in the IPK25 Chat Client. It handles user commands *
 *               and server messages, ensuring proper state transitions.       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPClientFSM.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `UdpClientFsm` class, which manages the client
 *        finite state machine (FSM) for handling user and server interactions
 *        in the IPK25 Chat Client.
 */

#include "Client/ClientFSM/UDPClientFSM.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Messaging/MessagingHandler/UDPMessagingHandler.hpp"
#include "Common/UserCommand.hpp"
#include "Common/ParsedMessage.hpp"
#include "Exceptions/ChatBaseException.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Enums/ClientFSMStates.hpp"
#include "Enums/UserCommandTypes.hpp"
#include "Enums/MessageTypes.hpp"
#include "Constants/MessageFields.hpp"
#include "Constants/MessageKeywords.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/SignalHandler.hpp"
#include "Utilities/Logger.hpp"
#include <string>     // std::string
#include <vector>     // std::vector
#include <cstring>    // std::strerror
#include <exception>  // std::exception
#include <chrono>     // std::chrono, std::chrono::steady_clock, std::chrono::seconds
#include <poll.h>     // pollfd

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Messaging::Handler;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Client::FSM
{
    void UdpClientFsm::run() {
        logger("Starting UDP Client FSM...");

        try {
            // Get socket FD and open connection
            mMessagingHandler->openConnection();

            // Main FSM loop
            while(mCurrentState != ClientFsmState::END) {
                // Check for user interruption signals
                SignalHandler::checkSignals();

                // Check if the reply deadline expired (REPLY is received in AUTH nad JOIN)
                if(isReplyDeadlineExpired() &&
                    (mCurrentState == ClientFsmState::AUTH || mCurrentState == ClientFsmState::JOIN)) {
                    throw TimeoutErrorException(
                            "No REPLY message arrived within 5 seconds even though it was expected.",
                            ClientInternalErrorMessage::CLIENT_REPLY_LOST
                            );
                }

                // We set up the pollfd structure to monitor descriptors
                pollfd fdWatcher[POLL_FD_COUNT];
                int pollTimeoutMs{POLL_INFINITE_TIMEOUT_MS};
                setupPollFd(fdWatcher);

                // If we are in AUTH or JOIN state, we count the remaining time until REPLY deadline
                if(mCurrentState == ClientFsmState::AUTH || mCurrentState == ClientFsmState::JOIN) {
                    const auto remainingTimeMs =
                            chrono::duration_cast<chrono::milliseconds>(mReplyDeadline - chrono::steady_clock::now()).count();

                    // If the remaining time is negative, the REPLY deadline has expired
                    pollTimeoutMs = (remainingTimeMs > 0) ? static_cast<int>(remainingTimeMs) : 0;
                }

                // Wait for events on the file descriptors
                const int eventCount = poll(fdWatcher, POLL_FD_COUNT, pollTimeoutMs);

                // Check if an event occured during poll()
                if(eventCount == 0 &&
                    (mCurrentState == ClientFsmState::AUTH || mCurrentState == ClientFsmState::JOIN)) {
                    throw TimeoutErrorException(
                            "No REPLY message arrived within 5 seconds even though it was expected.",
                            ClientInternalErrorMessage::CLIENT_REPLY_LOST
                            );
                }
                // Event occured, process the event
                else {
                    // Process user input from stdin (POLLHUP for STDIN closure)
                    if(fdWatcher[POLL_STDIN_INDEX].revents & (POLLIN | POLLHUP) &&
                        (mCurrentState == ClientFsmState::START || mCurrentState == ClientFsmState::OPEN)) {
                        const UserCommand command = mUserCommandParser->parseCommandLine();

                        // We stage the command for when it is possible to execute it
                        if(command.mCommandType != UserCommandType::INVALID) {
                            logger("User command pushed to the CommandBuffer: old size: %lu, new size: %lu, command: %s",
                                   mStagedCommands.size(), mStagedCommands.size() + 1, CastUtils::castEnumToString(command.mCommandType).c_str());
                            mStagedCommands.push(command);
                        }
                        // 'else' is not needed as a client internal error is printed in the parser
                    } // event on STDIN

                    // We execute the first staged command if possible
                    if(!mStagedCommands.empty() &&
                        (mCurrentState == ClientFsmState::START || mCurrentState == ClientFsmState::OPEN)) {
                        // We execute the first command in queue and remove it from it
                        logger("Going to execute command from command buffer: buffer size: %lu, front: %s",
                               mStagedCommands.size(), CastUtils::castEnumToString(mStagedCommands.front().mCommandType).c_str());
                        executeUserCommand(mStagedCommands.front());

                        mStagedCommands.pop();
                        logger("Command executed successfully. old size: %lu, new size: %lu",
                               mStagedCommands.size() + 1, mStagedCommands.size());

                        // If by executing this command we left AUTH or JOIN state, we reset the deadline
                        if(mCurrentState != ClientFsmState::AUTH && mCurrentState != ClientFsmState::JOIN) {
                            logger("Deactivating reply deadline in run() on if(!mStagedCommands.empty() && "
                                    "(mCurrentState == ClientFsmState::START || mCurrentState == ClientFsmState::OPEN).");
                            deactivateReplyDeadline();
                        }
                    }

                    // Process incoming messages from the server
                    if(fdWatcher[POLL_SOCKET_INDEX].revents & POLLIN) {
                        try {
                            const vector<ParsedMessage> parsedMessages = mMessagingHandler->receiveMessages();
                            for(auto &message : parsedMessages) {
                                processServerMessage(message);

                                // If we left AUTH or JOIN state, we reset the deadline
                                if(mCurrentState != ClientFsmState::AUTH && mCurrentState != ClientFsmState::JOIN) {
                                    logger("Deactivating reply deadline in run() on if(mCurrentState != ClientFsmState::AUTH "
                                            "&& mCurrentState != ClientFsmState::JOIN).");
                                    deactivateReplyDeadline();
                                }
                            }
                        }
                        catch(const ServerSendByeException &e) {
                            logger("ServerSendByeException caught: %s", e.what());
                            ParsedMessage byeMessage{};
                            byeMessage.mType = MessageType::BYE;
                            processServerMessage(byeMessage);
                        }
                    } // event on socket
                }
            } // while(mCurrentState != ClientFsmState::END)
        }
        catch(const HostnameResolutionErrorException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            ClientOutput::printClientInternalError(e.clientInternalError());
            throw;
        }
        catch(const ProtocolErrorException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            onUserErrRequested(e, true);
            throw;
        }
        catch(const ConnectionErrorException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            onUserErrRequested(e, true);
            throw;
        }
        catch(const TimeoutErrorException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            onUserErrRequested(e, true);
            throw;
        }
        catch(const ServerDisconnectedException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            onUserErrRequested(e, false);
            throw;
        }
        catch(const EndOfFileException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            executeUserCommand({UserCommandType::BYE});
        }
        catch(const UserInterruptionException &e) {
            logger("Base loop: Error receiving server message: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            executeUserCommand({UserCommandType::BYE});
        }
        catch(const ChatBaseException &e) {
            logger("Base loop: exception caught: what: %s, "
                   "detail: %s", e.what(), e.detail().c_str());
            onUserErrRequested(e, false);
            throw;
        }
        catch(const exception &e) {
            logger("Base loop: Exception caught in FSM loop: %s", e.what());
            executeUserCommand({UserCommandType::BYE});
            throw;
        }
    } // UdpClientFsm::run

    void UdpClientFsm::onUserByeRequested() {
        logger("/bye command requested in state %s.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        // Terminate gracefully
        if(mCurrentState == ClientFsmState::START || mCurrentState == ClientFsmState::AUTH) {
            mMessagingHandler->closeConnection(false);
        }
        else {
            mMessagingHandler->closeConnection(true);
        }

        // Transition from current state to END state
        logger("Transition from %s to END state on user /bye command.",
               CastUtils::castEnumToString(mCurrentState).c_str());
        updateCurrentState(ClientFsmState::END);

        logger("/bye command processed successfully.");
    } // UdpClientFsm::onUserByeRequested

    void UdpClientFsm::onServerReply(const ParsedMessage &receivedMessage) {
        const auto result = receivedMessage.mFields[MessageFields::UDP_REPLY_RESULT_KEYWORD_INDEX];
        logger("Server /reply received in the %s state. Result is: %s",
               CastUtils::castEnumToString(mCurrentState).c_str(), result.c_str());

        // Deactivate the deadline on any reply
        mIsReplyDeadlineActive = false;
        logger("Reply deadline deactivated after receiving server /reply.");

        // We will react based on current FSM state
        switch(mCurrentState) {
            case ClientFsmState::START: {
                // This is an undefined server behaviour, so I decided to ignore
                // any replies received in the START state.
                logger("Server /reply received in START state. Undefined behaviour. Ignoring.");
                break;
            }
            case ClientFsmState::AUTH: {
                // Update the AUTH waiting flag
                mReceivedAuthReply = true;
                logger("The 'mReceivedAuthReply' flag is set to TRUE. Reply on AUTH received.");

                // Displays the reply to the user
                logger("Displaying message type: %s", CastUtils::castEnumToString(receivedMessage.mType).c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);

                // Resolve the reply based on the result
                if(StringUtils::compareKeywordsCaseInsesitive(result, MessageKeywordsLowerCase::OK_LC)) {
                    logger("Transition from AUTH to OPEN state on user /reply OK received.");
                    updateCurrentState(ClientFsmState::OPEN);
                }
                else {
                    logger("Transition from AUTH to START state on user /reply NOK received.");
                    updateCurrentState(ClientFsmState::START);
                }

                break;
            }
            case ClientFsmState::JOIN: {
                // Displays the reply to the user
                logger("Displaying message type: %s", CastUtils::castEnumToString(receivedMessage.mType).c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);

                logger("Transition from JOIN to OPEN state on user /reply received.");
                updateCurrentState(ClientFsmState::OPEN);
                break;
            }
            case ClientFsmState::OPEN: {
                // Displays the reply to the user
                logger("Displaying message type: %s", CastUtils::castEnumToString(receivedMessage.mType).c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);

                logger("/reply command processed successfully. It is not allowed in the "
                        "OPEN state, so exception will be thrown.");
                throw ProtocolErrorException(
                        "Server /reply received in OPEN state. Result is " + result,
                        ClientInternalErrorMessage::CLIENT_REPLY_IN_OPEN
                        );
            }
            default: {
                break;
            }
        } // switch(mCurrentState)

        logger("/reply command processed successfully.");
    } // UdpClientFsm::onServerReply

    void UdpClientFsm::onServerErr(const ParsedMessage &receivedMessage) {
        logger("Server /err received in the %s state.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        // Displays the error to the user
        logger("Displaying message type: %s", CastUtils::castEnumToString(receivedMessage.mType).c_str());
        mMessagingHandler->displayIncomingMessage(receivedMessage);

        // Execute a FSM transition
        logger("Transition from %s to END state on user /err received.",
               CastUtils::castEnumToString(mCurrentState).c_str());
        updateCurrentState(ClientFsmState::END);

        logger("/err command processed successfully.");
    } // UdpClientFsm::onServerErr

    void UdpClientFsm::onServerBye() {
        logger("Server /bye received in the %s state.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        // Execute a FSM transition
        logger("Transition from %s to END state on user /bye received.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        mMessagingHandler->closeConnection(false);
        updateCurrentState(ClientFsmState::END);

        logger("/bye command processed successfully.");
    } // UdpClientFsm::onServerBye

    void UdpClientFsm::activateReplyDeadline() {
        mReplyDeadline = chrono::steady_clock::now() + chrono::seconds(5);
        mIsReplyDeadlineActive = true;
    } // UdpClientFsm::activateReplyDeadline

    void UdpClientFsm::deactivateReplyDeadline() {
        mIsReplyDeadlineActive = false;
    } // UdpClientFsm::deactivateReplyDeadline

    bool UdpClientFsm::isReplyDeadlineExpired() const {
        return mIsReplyDeadlineActive && (chrono::steady_clock::now() >= mReplyDeadline);
    } // UdpClientFsm::isReplyDeadlineExpired
} // IPK25ChatClien::Client::FSM

/*** end of file UDPClientFSM.cpp ***/
