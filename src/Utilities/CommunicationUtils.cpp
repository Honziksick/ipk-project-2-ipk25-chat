/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommunicationUtils.cpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the                  *
 *               `CommunicationUtils` class, which provides utility functions  *
 *               for handling communication-related tasks in the IPK25 Chat    *
 *               Client. It includes methods for resolving hostnames and       *
 *               IP addresses to facilitate network communication.             *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommunicationUtils.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief  Implementation of `CommunicationUtils` class providing the utility
 *         methods for establishing communication in the IPK25 Chat Client.
 */

#include "Utilities/CommunicationUtils.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/Logger.hpp"
#include <string>   // std::string
#include <cstring>  // std::memset
#include <netdb.h>  // addrinfo, getaddrinfo(), gai_strerror(), freeaddrinfo()

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Exceptions;
using namespace std;

namespace IPK25ChatClient::Utilities
{
    addrinfo *CommunicationUtils::resolveHostname(const string &hostnameOrIpAddress,
                                                  const int socketType, const int serverPort) {
        logger("Starting hostname resolution for: hostname/IPv4 %s, socketType: %d, serverPort: %d",
               hostnameOrIpAddress.c_str(), socketType, serverPort);

        // Prepare the 'hints' structure for address resolution
        addrinfo hints{};
        memset(&hints, 0, sizeof(hints));

        hints.ai_family = AF_INET;       // get IPv4 addresses
        hints.ai_socktype = socketType;  // any socket type (TCP/UDP)
        hints.ai_flags = 0;              // get only real IPs

        logger("Hints prepared: 'ai_family = %d', 'ai_socktype = %d', 'ai_flags = %d'",
               hints.ai_family, hints.ai_socktype, hints.ai_flags);

        // Perform the address resolution
        addrinfo *pResult{nullptr};
        const int getaddrinfoError = getaddrinfo(hostnameOrIpAddress.c_str(),
                                                 to_string(serverPort).c_str(),
                                                 &hints, &pResult);
        if(getaddrinfoError != 0) {
            logger("getaddrinfo() error: %s", gai_strerror(getaddrinfoError));
            throw HostnameResolutionErrorException(
                    "getaddrinfo() error: " + string(gai_strerror(getaddrinfoError)),
                    Enums::ClientInternalErrorMessage::CLIENT_HOST_RESOLUTION_FAILURE
                    );
        }

        logger("Hostname resolution successful. Returning addrinfo structure.");
        return pResult;
    } // CommunicationUtils::resolveHostname()
} // IPK25ChatClient::Utilities

/*** end of file CommunicationUtils.cpp ***/
