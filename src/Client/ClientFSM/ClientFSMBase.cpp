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
 * Last edit:    18.04.2025                                                    *
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


    int ClientFsmBase::pollEvents(pollfd *fdWatcher) {
        // Wait for events on the file descriptors
        const int eventCount = poll(fdWatcher, POLL_FD_COUNT, POLL_TIMEOUT_MS);

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
    }
} // IPK25ChatClient::Client::FSM

/*** end of file ClientFSMBase.cpp ***/
