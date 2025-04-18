/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPClientFSM.cpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `TcpClientFsm` class, which represents  *
 *               the finite state machine (FSM) for managing client-side       *
 *               operations in the IPK25 Chat Client. It handles user commands *
 *               and server messages, ensuring proper state transitions.       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPClientFSM.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `TcpClientFsm` class, which manages the client
 *        finite state machine (FSM) for handling user and server interactions
 *        in the IPK25 Chat Client.
 */

#include "Client/ClientFSM/TCPClientFSM.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Messaging/MessagingHandler/TCPMessagingHandler.hpp"
#include "Common/UserCommand.hpp"
#include "Common/ParsedMessage.hpp"
#include "Exceptions/ChatBaseException.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Enums/ClientFsmStates.hpp"
#include "Enums/UserCommandTypes.hpp"
#include "Enums/MessageTypes.hpp"
#include "Constants/MessageFields.hpp"
#include "Constants/MessageKeywords.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/SignalHandler.hpp"
#include "Utilities/Logger.hpp"
#include <exception>  // std::exception
#include <string>     // std::string
#include <vector>     // std::vector
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
    void TcpClientFsm::run() {
        logger("Starting TCP Client FSM...");

        try {
            // Get socket FD and open connection
            mMessagingHandler->openConnection();

            // Main FSM loop
            while(mCurrentState != ClientFsmState::END) {
                // Check for user interruption signals
                SignalHandler::checkSignals();

                // We set up the pollfd structure to monitor descriptors
                pollfd fdWatcher[POLL_FD_COUNT];
                setupPollFd(fdWatcher);

                // Wait for events on the file descriptors
                const int eventCount = pollEvents(fdWatcher);

                // Check if an event occured during poll()
                if(eventCount == 0) {
                    continue;  // No events, continue to the next iteration
                }
                // Event occured, process the event
                else {
                    // Process user input from stdin (POLLHUP for STDIN closure)
                    if(fdWatcher[POLL_STDIN_INDEX].revents & (POLLIN | POLLHUP)) {
                        const UserCommand command = mUserCommandParser->parseCommandLine();
                        if(command.mCommandType != UserCommandType::INVALID) {
                            executeUserCommand(command);
                        }
                        // 'else' is not needed as a client internal error is printed in the parser
                    } // event on STDIN

                    // Process incoming messages from the server
                    if(fdWatcher[POLL_SOCKET_INDEX].revents & POLLIN) {
                        const vector<ParsedMessage> parsedMessages = mMessagingHandler->receiveMessages();
                        for(auto &message : parsedMessages) {
                            processServerMessage(message);
                        }
                    } // event on socket
                } // else event occured

                logger("Current FSM state: %s", CastUtils::castEnumToString(mCurrentState).c_str());
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
    } // TcpClientFsm::run

    void TcpClientFsm::executeUserCommand(const UserCommand &userCommand) {
        if(mCurrentState != ClientFsmState::END) {
            switch(userCommand.mCommandType) {
                case UserCommandType::AUTH:
                    logger("Processing user /auth userCommand.");
                    onUserAuthRequested(userCommand);
                    break;
                case UserCommandType::JOIN:
                    logger("Processing user /join userCommand.");
                    onUserJoinRequested(userCommand);
                    break;
                case UserCommandType::RENAME:
                    logger("User /rename userCommand already processed in `CommandParser`.");
                // Renaming is done in the CommandParser
                    break;
                case UserCommandType::HELP:
                    logger("Processing user /help userCommand.");
                    onUserHelpRequested();
                    break;
                case UserCommandType::MESSAGE:
                    logger("Processing user /msg userCommand (user message).");
                    onUserMsgRequested(userCommand);
                    break;
                case UserCommandType::BYE:
                    logger("Processing user /bye userCommand.");
                    onUserByeRequested();
                    break;
                default:
                    logger("Processing invalid userCommand: %s",
                           CastUtils::castEnumToString(userCommand.mCommandType).c_str());
                    ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_BAD_COMMAND);
                    break;
            } // switch(userCommand.mCommandType)
        } // if(mCurrentState != ClientFsmState::END)
    } // TcpClientFsm::executeUserCommand

    void TcpClientFsm::processServerMessage(const ParsedMessage &receivedMessage) {
        switch(receivedMessage.mType) {
            case MessageType::REPLY:
                logger("Processing server /reply message.");
                onServerReply(receivedMessage);
                break;
            case MessageType::MSG:
                logger("Processing server /msg message.");
                onServerMsg(receivedMessage);
                break;
            case MessageType::ERR:
                logger("Processing server /err message.");
                onServerErr(receivedMessage);
                break;
            case MessageType::BYE:
                logger("Processing server /bye message.");
                onServerBye();
                break;
            default:
                logger("Received unrecognized server message type: %s",
                       CastUtils::castEnumToString(receivedMessage.mType).c_str());
                break;
        } // switch(receivedMessage.mType)
    } // TcpClientFsm::processServerMessage

    void TcpClientFsm::onUserAuthRequested(const UserCommand &userCommand) {
        logger("/auth userCommand requested.");

        // AUTH userCommand used in an invalid state
        if(mCurrentState != ClientFsmState::START && mCurrentState != ClientFsmState::AUTH) {
            logger("/auth userCommand used in an invalid state: %s",
                   CastUtils::castEnumToString(mCurrentState).c_str());
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_AUTH_AGAIN);
        }
        // Can't enter another AUTH userCommand without an REPLY from the server first
        else if(!mReceivedAuthReply) {
            logger("Can't enter another AUTH userCommand without an REPLY from the server first.");
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_AUTH_NO_REPLY);
        }
        // Process the AUTH userCommand
        else {
            // Send the AUTH message to the server and wait for reply
            mMessagingHandler->sendAuthMessage(userCommand.mUsername, userCommand.mDisplayName, userCommand.mSecret);
            mReceivedAuthReply = false;
            logger("The 'mReceivedAuthReply' flag is set to FALSE. Waiting for server reply.");

            // Set the display name
            mDisplayNameProvider->setDisplayName(userCommand.mDisplayName);
            logger("Display name set to: %s", userCommand.mDisplayName.c_str());

            // Transition from START to AUTH
            if(mCurrentState == ClientFsmState::START) {
                logger("Transition from START to AUTH state on user /auth userCommand.");
                updateCurrentState(ClientFsmState::AUTH);
            }
            logger("/auth userCommand processed successfully.");
        }
    } // TcpClientFsm::onUserAuthRequested

    void TcpClientFsm::onUserJoinRequested(const UserCommand &userCommand) {
        logger("/join userCommand requested.");

        // Process the JOIN userCommand
        if(mCurrentState == ClientFsmState::OPEN) {
            mMessagingHandler->sendJoinMessage(userCommand.mChannelId);

            logger("Transition from OPEN to JOIN state on user /join userCommand.");
            updateCurrentState(ClientFsmState::JOIN);

            logger("/join userCommand processed successfully.");
        }
        // JOIN userCommand used in an invalid state
        else {
            logger("/join userCommand used in an invalid state: %s",
                   CastUtils::castEnumToString(mCurrentState).c_str());
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_NOT_AUTH);
        }
    } // TcpClientFsm::onUserJoinRequested

    void TcpClientFsm::onUserMsgRequested(const UserCommand &userCommand) {
        logger("/msg userCommand requested.");

        // Process the MSG userCommand
        if(mCurrentState == ClientFsmState::OPEN) {
            mMessagingHandler->sendMsgMessage(userCommand.mMessageContent);

            logger("No transition done. Staying in OPEN state on user /msg userCommand.");
            logger("/msg userCommand processed successfully.");
        }
        // MSG userCommand used in an invalid state
        else {
            logger("/msg userCommand used in an invalid state: %s",
                   CastUtils::castEnumToString(mCurrentState).c_str());
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_NOT_AUTH);
        }
    } // TcpClientFsm::onUserMsgRequested

    void TcpClientFsm::onUserByeRequested() {
        logger("/bye command requested.");

        // Terminate gracefully
        mMessagingHandler->sendByeMessage();
        mMessagingHandler->closeConnection();

        // Transition from current state to END state
        logger("Transition from %s to END state on user /bye command.",
               CastUtils::castEnumToString(mCurrentState).c_str());
        updateCurrentState(ClientFsmState::END);

        logger("/bye command processed successfully.");
    } // TcpClientFsm::onUserByeRequested

    void TcpClientFsm::onUserHelpRequested() {
        logger("/help command requested.");

        ClientOutput::printClientHelp();

        logger("/help command processed successfully.");
    } // TcpClientFsm::onUserHelpRequested

    void TcpClientFsm::onUserErrRequested(const ChatBaseException &e, const bool sendErrMessage) {
        logger("/err command requested.");

        // Print the error message to the user
        ClientOutput::printClientInternalError(e.clientInternalError());

        // Send the error message to the server if requested
        if(mCurrentState != ClientFsmState::START &&
            mCurrentState != ClientFsmState::JOIN &&
            mCurrentState != ClientFsmState::END) {
            // Send the error message to the server if requested
            if(sendErrMessage) {
                logger("Error message sent to server.");
                mMessagingHandler->sendErrMessage(string(e.what()) + " " + e.detail());
            }
            else {
                logger("Error message not sent to server.");
            }

            // Terminate gracefully
            mMessagingHandler->closeConnection();
        }
        logger("/help command processed successfully.");
    } // TcpClientFsm::onUserErrRequested

    void TcpClientFsm::onServerReply(const ParsedMessage &receivedMessage) {
        const auto result = receivedMessage.mFields[MessageFields::TCP_REPLY_RESULT_KEYWORD_INDEX];
        logger("Server /reply received in the %s state. Result is: %s",
               CastUtils::castEnumToString(mCurrentState).c_str(), result.c_str());

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
                logger("Displaying message type: %s", receivedMessage.mFields[0].c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);

                // Resolve teh reply based on the result
                if(StringUtils::compareKeywordsCaseInsesitive(result, MessageKeywordsLowerCase::OK_LC)) {
                    logger("Transition from AUTH to OPEN state on user /reply OK received.");
                    updateCurrentState(ClientFsmState::OPEN);
                }
                else {
                    logger("Staying in AUTH state on user /reply NOK received.");
                }
                break;
            }
            case ClientFsmState::JOIN: {
                // Displays the reply to the user
                logger("Displaying message type: %s", receivedMessage.mFields[0].c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);

                logger("Transition from JOIN to OPEN state on user /reply received.");
                updateCurrentState(ClientFsmState::OPEN);
                break;
            }
            case ClientFsmState::OPEN: {
                // Displays the reply to the user
                logger("Displaying message type: %s", receivedMessage.mFields[0].c_str());
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
    } // TcpClientFsm::onServerReply

    void TcpClientFsm::onServerMsg(const ParsedMessage &receivedMessage) {
        logger("Server /msg received in the %s state.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        // We will react based on current FSM state
        switch(mCurrentState) {
            case ClientFsmState::START: {
                // This is an undefined server behaviour, so i decided to ignore
                // any messages received in the START state.
                logger("Server /msg received in START state. Undefined behaviour. Ignoring.");
                break;
            }
            case ClientFsmState::AUTH: {
                // Displays the message to the user
                logger("Displaying message type: %s", receivedMessage.mFields[0].c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);

                logger("/msg command processed successfully. It is not allowed "
                        "in the AUTH state, so exception will be thrown.");
                throw ProtocolErrorException(
                        "Server /msg received in AUTH state.",
                        ClientInternalErrorMessage::CLIENT_MSG_IN_AUTH
                        );
            }
            case ClientFsmState::OPEN:
            case ClientFsmState::JOIN:
                // Displays the message to the user
                logger("Displaying message type: %s", receivedMessage.mFields[0].c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);
            default:
                break;
        } // switch(mCurrentState)
    } // TcpClientFsm::onServerMsg

    void TcpClientFsm::onServerErr(const ParsedMessage &receivedMessage) {
        logger("Server /err received in the %s state.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        // Displays the error to the user
        logger("Displaying message type: %s", receivedMessage.mFields[0].c_str());
        mMessagingHandler->displayIncomingMessage(receivedMessage);

        // Execute a FSM transition
        logger("Transition from %s to END state on user /err received.",
               CastUtils::castEnumToString(mCurrentState).c_str());
        updateCurrentState(ClientFsmState::END);

        logger("/err command processed successfully.");
    } // TcpClientFsm::onServerErr

    void TcpClientFsm::onServerBye() {
        logger("Server /bye received in the %s state.",
               CastUtils::castEnumToString(mCurrentState).c_str());

        // Execute a FSM transition
        logger("Transition from %s to END state on user /bye received.",
               CastUtils::castEnumToString(mCurrentState).c_str());
        updateCurrentState(ClientFsmState::END);

        logger("/bye command processed successfully.");
    } // TcpClientFsm::onServerBye
} // IPK25ChatClien::Client::FSM

/*** end of file TCPClientFSM.cpp ***/
