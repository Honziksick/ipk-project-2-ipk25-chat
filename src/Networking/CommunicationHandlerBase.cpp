/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommunicationHandlerBase.cpp                                  *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the                  *
 *               `CommunicationHandlerBase class, which serves as a base       *
 *               class for handling both TCP and UDP communication in the      *
 *               IPK25 Chat Client. It provides methods for managing           *
 *               connections, such as closing connections and checking         *
 *               connection status.                                            *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommunicationHandlerBase.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `CommunicationHandlerBase` class for handling
 *        both TCP and UDP communication.
 */

#include "Networking/CommunicationHandlerBase.hpp"
#include "Messaging/MessageParser/TCPMessageParser.hpp"
#include "Messaging/MessageParser/UDPMessageParser.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <memory>    // std::unique_ptr, std::shared_ptr
#include <unistd.h>  // close()

using namespace IPK25ChatClient::Messaging::Parser;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Networking
{
    CommunicationHandlerBase::CommunicationHandlerBase(const CommandLineOptions &commandLineOptions, const shared_ptr<int> &socketFd)
        : mSocketFd{socketFd}, mIsConnected{DISCONNECTED}, mServerAddress{commandLineOptions.mTargetServer},
          mServerPort{commandLineOptions.mServerPort} {
        // Initialize the incoming message parser based on the protocol type
        if(commandLineOptions.mTransportProtocol == TransportProtocolType::TCP) {
            mMessageParser = make_unique<TcpMessageParser>();
            logger("Initialized incoming MessageParser: TCP");
        }
        else if(commandLineOptions.mTransportProtocol == TransportProtocolType::UDP) {
            mMessageParser = make_unique<UdpMessageParser>();
            logger("Initialized incoming MessageParser: UDP");
        }
        else {
            throw ConstructorErrorException(
                    "Invalid protocol type was given to CommunicationHandlerBase: " +
                    CastUtils::castEnumToString(commandLineOptions.mTransportProtocol)
                    );
        }
    } // CommunicationHandlerBase::CommunicationHandlerBase

    void CommunicationHandlerBase::closeConnection() {
        // Check if the socket isn't already closed
        if(*mSocketFd > SOCKET_CLOSED) {
            logger("Performing graceful shutdown on socket 'FD = %d`", *mSocketFd);

            gracefulShutdown(); // polymorphic (for UDP and TCP)
            close(*mSocketFd);
            *mSocketFd = SOCKET_CLOSED;
            mIsConnected = DISCONNECTED;

            logger("Socket 'FD = %d' has been closed.", *mSocketFd);
            logger("Connection state set to: DISCONNECTED.");
        }
    } // CommunicationHandlerBase::closeConnection
} // IPK25ChatClient::Networking

/*** end of file CommunicationHandlerBase.cpp ***/
