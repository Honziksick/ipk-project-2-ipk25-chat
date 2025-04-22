/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientFSMBase.cpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the base class `ClientFSMBase` for the      *
 *               client finite state machine (FSM). This file contains the     *
 *               constructor and methods for managing the FSM's state and      *
 *               initializing communication handlers based on the transport    *
 *               protocol.                                                     *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientFSMBase.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the base class `ClientFSMBase` for the client
 *        finite state machine (FSM).
 */

#include "Client/ClientFSM/ClientFSMBase.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Client/CommandParser/UserCommandParser.hpp"
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Messaging/MessagingHandler/TCPMessagingHandler.hpp"
#include "Messaging/MessagingHandler/UDPMessagingHandler.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Enums/ClientFSMStates.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>   // std::string
#include <memory>   // std::unique_ptr, std::make_shared
#include <cstring>  // std::strerror
#include <poll.h>   // pollfd

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Client::CommandParser;
using namespace IPK25ChatClient::Messaging::Handler;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Client::FSM
{
    ClientFsmBase::ClientFsmBase(const CommandLineOptions &commandLineOptions)
        : mReceivedAuthReply{true},
          mSocketFd{make_shared<int>(-1)},
          mCurrentState{ClientFsmState::START},
          mDisplayNameProvider{make_shared<DisplayNameProvider>()},
          mUserCommandParser{make_unique<UserCommandParser>(mDisplayNameProvider)} {
        logger("Program flow control given to ClientFsmFacade");

        // Initialize the CommunicationHandler based on the protocol type
        if(commandLineOptions.mTransportProtocol == TransportProtocolType::TCP) {
            mMessagingHandler = make_unique<TcpMessagingHandler>(commandLineOptions, mSocketFd, mDisplayNameProvider);
            logger("Initialized ComunicationHandler: TCP");
        }
        else if(commandLineOptions.mTransportProtocol == TransportProtocolType::UDP) {
            mMessagingHandler = make_unique<UdpMessagingHandler>(commandLineOptions, mSocketFd, mDisplayNameProvider);
            logger("Initialized ComunicationHandler: UDP");
        }
        else {
            throw ConstructorErrorException(
                    "Invalid protocol type was given to the ClientFsmBase constructor: " +
                    CastUtils::castEnumToString(commandLineOptions.mTransportProtocol)
                    );
        }

        logger("Current FSM state: %s", CastUtils::castEnumToString(mCurrentState).c_str());
    } // ClientFsmFacade::ClientFsmFacade

    void ClientFsmBase::updateCurrentState(const ClientFsmState newState) {
        mCurrentState = newState;
    } // ClientFsmBase::updateCurrentState

    void ClientFsmBase::setupPollFd(pollfd *fdWatcher) const {
        // Set up STDIN
        fdWatcher[POLL_STDIN_INDEX].fd = STDIN_FD;
        fdWatcher[POLL_STDIN_INDEX].events = POLLIN;

        // Set up the socket
        fdWatcher[POLL_SOCKET_INDEX].fd = *mSocketFd;
        fdWatcher[POLL_SOCKET_INDEX].events = POLLIN;
    } // ClientFsmBase::setupPollFd

    int ClientFsmBase::pollEvents(pollfd *fdWatcher, const int pollTimeoutMs) {
        // Wait for events on the file descriptors
        const int eventCount = poll(fdWatcher, POLL_FD_COUNT, pollTimeoutMs);

        // Check if poll() failed
        if(eventCount < 0) {
            if(errno == EINTR) {
                logger("poll() interrupted by signal.");
                throw UserInterruptionException(
                        "poll() interrupted by signal: " + string(strerror(errno))
                        );
            }
            else {
                logger("poll() error: %s", strerror(errno));
                throw ConnectionErrorException(
                        "poll() error: " + string(strerror(errno)),
                        ClientInternalErrorMessage::CLIENT_CONNECTION_ERROR
                        );
            }
        }
        return eventCount;
    } // ClientFsmBase::pollEvents

    void ClientFsmBase::executeUserCommand(const UserCommand &userCommand) {
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
    } // ClientFsmBase::executeUserCommand

    void ClientFsmBase::processServerMessage(const ParsedMessage &receivedMessage) {
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
    } // ClientFsmBase::processServerMessage

    void ClientFsmBase::onUserAuthRequested(const UserCommand &userCommand) {
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
            mMessagingHandler->sendAuthMessage(userCommand.mUsername,
                                               userCommand.mDisplayName, userCommand.mSecret);
            activateReplyDeadline();

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
    } // ClientFsmBase::onUserAuthRequested

    void ClientFsmBase::onUserJoinRequested(const UserCommand &userCommand) {
        logger("/join userCommand requested.");

        // Process the JOIN userCommand
        if(mCurrentState == ClientFsmState::OPEN) {
            mMessagingHandler->sendJoinMessage(userCommand.mChannelId);
            activateReplyDeadline();

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
    } // ClientFsmBase::onUserJoinRequested

    void ClientFsmBase::onUserMsgRequested(const UserCommand &userCommand) const {
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
    } // ClientFsmBase::onUserMsgRequested

    void ClientFsmBase::onUserHelpRequested() {
        logger("/help command requested.");

        ClientOutput::printClientHelp();

        logger("/help command processed successfully.");
    } // ClientFsmBase::onUserHelpRequested

    void ClientFsmBase::onUserErrRequested(const ChatBaseException &e, const bool sendErrMessage) const {
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
            mMessagingHandler->closeConnection(false);
        }
        logger("/err command processed successfully.");
    } // ClientFsmBase::onUserErrRequested

    void ClientFsmBase::onServerMsg(const ParsedMessage &receivedMessage) const {
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
                logger("Displaying message type: %s",
                       CastUtils::castEnumToString(receivedMessage.mType).c_str());
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
                logger("Displaying message type: %s",
                       CastUtils::castEnumToString(receivedMessage.mType).c_str());
                mMessagingHandler->displayIncomingMessage(receivedMessage);
            default:
                break;
        } // switch(mCurrentState)
    } // ClientFsmBase::onServerMsg
} // IPK25ChatClient::Client::FSM

/*** end of file ClientFSMBase.cpp ***/
