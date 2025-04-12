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
 * Last edit:    10.04.2025                                                    *
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
#include "Common/CommandLineOptions.hpp"
#include "Utilities/Logger.hpp"
#include <unistd.h>  // close()

using namespace IPK25ChatClient::Common;
using namespace std;

namespace IPK25ChatClient::Networking
{
    CommunicationHandlerBase::CommunicationHandlerBase(const CommandLineOptions &commandLineOptions)
        : mSocketFd{SOCKET_CLOSED}, mIsConnected{DISCONNECTED}, mServerAddress{commandLineOptions.mTargetServer},
          mServerPort{commandLineOptions.mServerPort} {}

    CommunicationHandlerBase::~CommunicationHandlerBase() {
        CommunicationHandlerBase::closeConnection();
    } // CommunicationHandlerBase::~CommunicationHandlerBase

    void CommunicationHandlerBase::closeConnection() {
        // Check if the socket isn't already closed
        if(mSocketFd > SOCKET_CLOSED) {
            logger("Performing graceful shutdown on socket 'FD = %d`", mSocketFd);

            gracefulShutdown(); // polymorphic (for UDP and TCP)
            close(mSocketFd);
            mSocketFd = SOCKET_CLOSED;
            mIsConnected = DISCONNECTED;

            logger("Socket 'FD = %d' has been closed.", mSocketFd);
            logger("Connection state set to: DISCONNECTED.");
        }
    } // CommunicationHandlerBase::closeConnection

    bool CommunicationHandlerBase::isConnected() const {
        logger("Connection state is: %s", mIsConnected ? "CONNECTED" : "DISCONNECTED");
        return mIsConnected;
    } // CommunicationHandlerBase::isConnected
} // IPK25ChatClient::Networking

/*** end of file CommunicationHandlerBase.cpp ***/
