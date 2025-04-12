/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommunicationUtils.hpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    10.04.2025                                                    *
 *                                                                             *
 * Description:  This header file provides utility methods for handling        *
 *               communication-related tasks in the IPK25 Chat Client. It      *
 *               includes methods for resolving hostnames and IP addresses     *
 *               to facilitate network communication.                          *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommunicationUtils.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining utility methods for communication in the
 *        IPK25 Chat Client.
 */

#ifndef COMMUNICATION_UTILS_HPP
#define COMMUNICATION_UTILS_HPP

#include <string>   // std::string
#include <netdb.h>  // addrinfo

namespace IPK25ChatClient::Utilities
{
    /**
     * @class CommunicationUtils
     * @brief Provides utility functions for network communication.
     */
    class CommunicationUtils {
    public:
        /**
         * @brief Resolves a hostname or IP address to an `addrinfo` structure.
         *
         * @details This method takes a hostname or IP address, a socket type,
         *          and a server port, and resolves them into an `addrinfo`
         *          structure that can be used for creating a socket connection.
         *
         * @param hostnameOrIpAddress The hostname or IP address to resolve.
         * @param socketType The type of socket (e.g., SOCK_STREAM for TCP).
         * @param serverPort The port number of the server.
         *
         * @return A pointer to an `addrinfo` structure containing the resolved
         *         address information. The caller is responsible for freeing
         *         this structure using `freeaddrinfo()`.
         */
        static addrinfo *resolveHostname(const std::string &hostnameOrIpAddress,
                                         int socketType, int serverPort);
    }; // CommunicationUtils
} // IPK25ChatClient::Utilities

#endif // COMMUNICATION_UTILS_HPP

/*** end of file CommunicationUtils.hpp ***/
