/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPCommunicationHandler.cpp                                   *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the                  *
 *               `TcpCommunicationHandler` class, which is responsible for     *
 *               managing TCP communication in the IPK25 Chat Client. It       *
 *               provides methods for establishing connections, sending and    *
 *               receiving messages, and performing a graceful shutdown of     *
 *               the connection.                                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPCommunicationHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `TcpCommunicationHandler` class for TCP specific
 *        communication methods.
 */

#include "Networking/TCPCommunicationHandler.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Messaging/Interfaces/IMessageParser.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Constants/ClientLimits.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CommunicationUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>        // std::string
#include <vector>        // std::vector
#include <variant>       // std::holds_alternative<>(), std::get<>()
#include <sys/socket.h>  // socket(), connect(), send(), recv()
#include <netdb.h>       // addrinfo, freeaddrinfo()
#include <unistd.h>      // close()
#include <cstring>       // strerror()

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Messaging;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Networking
{
    void TcpCommunicationHandler::openConnection() {
        logger("Starting TCP connection process to server: %s on port: %d", mServerAddress.c_str(), mServerPort);

        // Check if the connection is already established
        if(mIsConnected) {
            logger("Connection already established. No need to open a new connection.");
            return;
        }

        // Resolve the server hostname or IPv4 address
        addrinfo *pResult = CommunicationUtils::resolveHostname(mServerAddress, SOCK_STREAM, mServerPort);

        if(!pResult) {
            logger("NULL pointer returned by 'resolveHostname(): hostname resolution failed.");
            throw ConnectionErrorException(
                    "NULL pointer returned by 'resolveHostname(): hostname resolution failed."
                    );
        }

        // Iterate through the resolved addresses and try to connect
        for(const addrinfo *iResolvedAddress = pResult; iResolvedAddress != nullptr; iResolvedAddress = iResolvedAddress->ai_next) {
            logger("Attempting to create socket for address family: %d, socket type: %d, protocol: %d",
                   iResolvedAddress->ai_family, iResolvedAddress->ai_socktype, iResolvedAddress->ai_protocol);

            // Create a TCP socket
            const int tcpSocketFd = socket(iResolvedAddress->ai_family, iResolvedAddress->ai_socktype, iResolvedAddress->ai_protocol);
            if(tcpSocketFd <= SOCKET_CLOSED) {
                logger("Failed to create a socket. Error: %s", strerror(errno));
                continue;
            }

            // Connect to the server
            if(connect(tcpSocketFd, iResolvedAddress->ai_addr, iResolvedAddress->ai_addrlen) == 0) {
                logger("Successfully connected to server. Socket 'FD = %d'.", tcpSocketFd);
                mSocketFd = tcpSocketFd;
                mIsConnected = CONNECTED;
                freeaddrinfo(pResult);
                return;
            }

            // If the connection fails, close the socket and try the next address
            logger("Failed to connect to server. Closing socket FD: %d. Error: %s", tcpSocketFd, strerror(errno));
            close(tcpSocketFd);
        }

        // If we reach here, it means we couldn't connect to any of the resolved addresses
        freeaddrinfo(pResult);

        logger("Failed to connect to any resolved address. Throwing ConnectionErrorException.");
        ClientOutput::printClientInternalError(
                "At the moment, we are unable to connect to the server. Please check "
                "the correctness of the provided address and port, and try again later. "
                "If the problem persists, contact support. The connection to the server "
                "is not established, so the client can't inform the server about the error. "
                "The application will now terminate."
                );
        throw ConnectionErrorException(
                "Failed to connect to any of the resolved IPv4 address."
                );
    } // TcpCommunicationHandler::openConnection

    void TcpCommunicationHandler::sendMessage(const MessageContent messageContent) {
        // Extract the string from the MessageContent variant
        string contentToSend;
        if(holds_alternative<string>(messageContent)) {
            contentToSend = get<string>(messageContent);
        }
        else {
            throw InternalErrorException(
                    "sendMessage() error for TCP: The custom variant data type 'MessageContent' is not a string. "
                    );
        }

        // Check if the connection is established
        if(!mIsConnected) {
            logger("Trying to send message %s while not connected.", contentToSend.c_str());
            throw InternalErrorException(
                    "Trying to send message while not connected. Content " + contentToSend
                    );
        }

        // Send the message
        ssize_t bytesSentTotal = 0;
        const auto bytesToSend = static_cast<ssize_t>(contentToSend.size());
        while(bytesSentTotal < bytesToSend) {
            const ssize_t bytesSent = send(mSocketFd, contentToSend.data() + bytesSentTotal, bytesToSend - bytesSentTotal, 0);

            // If the send() function returns an error
            if(bytesSent < 0) {
                mIsConnected = DISCONNECTED;
                logger("send() returned error: Failed to send message. Content: %s, "
                       "Socket 'FD = %d', error: %s", contentToSend.c_str(), mSocketFd, strerror(errno));
                ClientOutput::printClientInternalError(
                        "Failed to send data to the server. The client will now attempt to inform "
                        "the server about the error. If the server is not reachable, application will "
                        "terminate gracefully."
                        );
                throw ConnectionErrorException(
                        "Failed to send data to the server due to send() error: " + string(strerror(errno))
                        );
            }

            // If the send() function returns 0, it means the connection has been closed
            if(bytesSent == 0) {
                mIsConnected = DISCONNECTED;
                logger("send() returned 0: Connection closed by server");
                ClientOutput::printClientInternalError(
                        "Connection closed by server. No data received. No further communication "
                        "available. The application will now terminate gracefully."
                        );
                throw ServerDisconnectedException(
                        "Connection closed by server. No data sent."
                        );
            }

            // Update the total number of bytes sent
            bytesSentTotal += bytesSent;
        }
        logger("Message sent successfully: %s", contentToSend.c_str());
    } // TcpCommunicationHandler::sendMessage

    ParsedMessage TcpCommunicationHandler::receiveMessage() {
        // Check if the connection is established
        if(!mIsConnected) {
            logger("Attempted to receive data while not connected.");
            throw InternalErrorException("Attempted to receive data while not connected.");
        }

        // Allocate a buffer for receiving data (+1 to indicate possible overflow afterwrds)
        constexpr size_t bufferSize{ClientLimits::MAX_MESSAGE_CONTENT_LENGTH + 1};
        char receiveBuffer[bufferSize];

        // Receive data from the server (this approach correctly handle fragmanted messages)
        while(true) {
            const ssize_t bytesReceived = recv(mSocketFd, receiveBuffer, bufferSize, 0);

            // If the recv() function returns an error
            if(bytesReceived < 0) {
                mIsConnected = DISCONNECTED;
                logger("recv() returned error: Failed to receive data. Socket 'FD = %d', "
                       "error: %s", mSocketFd, strerror(errno));
                ClientOutput::printClientInternalError(
                        "Failed to receive data from the server. The client will now attempt to inform "
                        "the server about the error. If the server is not reachable, application will "
                        "terminate gracefully."
                        );
                throw ConnectionErrorException(
                        "Failed to receive data from the server due to recv() error: " + string(strerror(errno))
                        );
            }

            // If the recv() function returns 0, it means the connection has been closed
            if(bytesReceived == 0) {
                mIsConnected = DISCONNECTED;
                logger("recv() returned 0: Connection closed by server");
                ClientOutput::printClientInternalError(
                        "Connection closed by server. No data received. No further communication "
                        "available. The application will now terminate gracefully."
                        );
                throw ServerDisconnectedException(
                        "Connection closed by server. No data received."
                        );
            }

            // Cast the received data to a string and make it he message content
            string dataReceived(receiveBuffer, bytesReceived);
            MessageContent messageContent{dataReceived};

            // Check if the message is complete (if not, continue receiving)
            optional<ParsedMessage> maybeParsedMessage = mMessageParser->parseIncomingMessage(messageContent);
            if(maybeParsedMessage.has_value()) {
                logger("Message received successfully");
                return maybeParsedMessage.value();
            }
        }
    } // TcpCommunicationHandler::receiveMessage


    void TcpCommunicationHandler::gracefulShutdown() {
        // Attempt a graceful shutdown by sending a TCP FIN packet.
        if(shutdown(mSocketFd, SHUT_WR) < 0) {
            logger("Graceful shutdown failed on socket 'FD = %d', error: %s", mSocketFd, strerror(errno));
            throw ConnectionErrorException(
                    "Graceful connection termination failed. The communication protocol is set to TCP, "
                    "so no additional attempts to gracefully terminate the connection won't be made, "
                    "and the application will successfully exit."
                    );
        }
        else {
            logger("Graceful shutdown successful on socket 'FD = %d'", mSocketFd);
        }
    } // TcpCommunicationHandler::gracefulShutdown
} // IPK25ChatClient::Networking

/*** end of file TCPCommunicationHandler.cpp ***/
