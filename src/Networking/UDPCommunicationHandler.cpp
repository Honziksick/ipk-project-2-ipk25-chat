/*******************************************************************************
*                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPCommunicationHandler.cpp                                   *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      17.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the                  *
 *               `UdpCommunicationHandler` class, which is responsible for     *
 *               managing TCP communication in the IPK25 Chat Client. It       *
 *               provides methods for establishing connections, sending and    *
 *               receiving messages, and performing a graceful shutdown of     *
 *               the connection.                                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPCommunicationHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `UdpCommunicationHandler` class for
 *        TCP-specific communication methods.
 */

#include "Networking/UDPCommunicationHandler.hpp"
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Messaging/Interfaces/IMessageParser.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Constants/ClientLimits.hpp"
#include "Constants/MessageFields.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CommunicationUtils.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>        // std::string
#include <vector>        // std::vector
#include <memory>        // std::shared_ptr
#include <utility>       // std::move
#include <variant>       // std::holds_alternative<>(), std::get<>()
#include <chrono>        // std::chrono::steady_clock, std::chrono::milliseconds
#include <cstring>       // std::strerror()
#include <poll.h>        // pollfd, poll()
#include <sys/socket.h>  // sendto(), recvfrom()
#include <poll.h>        // pollfd, poll()
#include <netdb.h>       // addrinfo, freeaddrinfo()
#include <netinet/in.h>  // sockaddr_in, sin_port
#include <arpa/inet.h>   // ntohs()

using namespace IPK25ChatClient::Client::CommandParser;
using namespace IPK25ChatClient::Messaging;
using namespace IPK25ChatClient::Messaging::Builder;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Networking
{
    UdpCommunicationHandler::UdpCommunicationHandler(const CommandLineOptions &commandLineOptions, const shared_ptr<int> &socketFd,
                                                     const shared_ptr<IMessageBuilder> &messageBuilder, shared_ptr<DisplayNameProvider> displayNameProvider)
        : CommunicationHandlerBase(commandLineOptions, socketFd),
          mUdpMaxRetransmit{commandLineOptions.mUdpMaxRetransmit},
          mUdpTimeoutMs{commandLineOptions.mUdpTimeoutMs},
          mServerPortSwitched{false},
          mMessageBuilder{messageBuilder},
          mDisplayNameProvider{move(displayNameProvider)} {}

    UdpCommunicationHandler::~UdpCommunicationHandler() {
        UdpCommunicationHandler::closeConnection(false);
    } // UdpCommunicationHandler::~UdpCommunicationHandler

    void UdpCommunicationHandler::openConnection() {
        logger("Starting UDP connection process to server: %s on port: %d", mServerAddress.c_str(), mServerPort);

        // Check if the connection isn't already established
        if(mIsConnected) {
            logger("Connection already established. No need to open a new connection.");
            return;
        }

        // Resolve the server hostname or IPv4 address
        addrinfo *pResult = CommunicationUtils::resolveHostname(mServerAddress, SOCK_DGRAM, mServerPort);
        if(!pResult) {
            logger("NULL pointer returned by 'resolveHostname(): hostname resolution failed.");
            throw HostnameResolutionErrorException(
                    "NULL pointer returned by 'resolveHostname(): hostname resolution failed.",
                    ClientInternalErrorMessage::CLIENT_HOST_RESOLUTION_FAILURE
                    );
        }

        // Iterate through the resolved addresses and try to connect
        vector<sockaddr_in> socketAddresses;
        for(const addrinfo *iResolvedAddress = pResult; iResolvedAddress != nullptr; iResolvedAddress = iResolvedAddress->ai_next) {
            logger("Converting addrinfo into sockaddr_in for address family: %d, socket type: %d, protocol: %d",
                   iResolvedAddress->ai_family, iResolvedAddress->ai_socktype, iResolvedAddress->ai_protocol);

            // Copy the resolved server address ainto the vector (note: only IPv4 should be present, but better sure than sorry)
            if(iResolvedAddress->ai_family == AF_INET) {
                sockaddr_in address{};
                memcpy(&address, iResolvedAddress->ai_addr, sizeof(address));
                socketAddresses.emplace_back(address);
            }
        }

        // Free the memory allocated for the resolved address information.
        freeaddrinfo(pResult);

        // Check if any IPv4 addresses were resolved
        if(socketAddresses.empty()) {
            logger("Failed to connect to any resolved address. Throwing ConnectionErrorException.");
            throw UnestablishedConnectionErrorException(
                    "Failed to connect to any of the resolved IPv4 address.",
                    ClientInternalErrorMessage::CLIENT_CONNECTION_ERROR
                    );
        }

        // Create a UDP socket
        const int udpSocketFd = socket(AF_INET, SOCK_DGRAM, 0);

        if(udpSocketFd < 0) {
            logger("Failed to create a socket. Error: %s", strerror(errno));
            throw UnestablishedConnectionErrorException(
                    "Failed to connect to any of the resolved IPv4 address.",
                    ClientInternalErrorMessage::CLIENT_CONNECTION_ERROR
                    );
        }

        // Set the shared socket FD and mark the connection state as `CONNECTED`.
        *mSocketFd = udpSocketFd;
        mIsConnected = CONNECTED;

        // We can simply select the first address from the vector as the server address
        mServerAddr = socketAddresses.front();
        mServerAddrLen = sizeof(mServerAddr);
    } // UdpCommunicationHandler::openConnection

    void UdpCommunicationHandler::closeConnection(const bool sendBye) {
        // Check if the socket isn't already closed
        if(*mSocketFd > SOCKET_CLOSED) {
            logger("Closing UDP socket 'FD = %d' with sending and "
                   "retransmitting BYE=%s", *mSocketFd, sendBye ? "true" : "false");

            // Attempt a graceful shutdown by sending a UDP BYE packet and wait for CONFIRM
            if(sendBye) {
                logger("UDP graceful shutdown: sending BYE and waiting for CONFIRM");
                const UserCommand userCommand{
                    .mDisplayName = mDisplayNameProvider->getDisplayName(),
                };

                const MessageContent bye = mMessageBuilder->buildMessage(MessageType::BYE, userCommand);
                logger("BYE message built with size=%zu", get<vector<uint8_t>>(bye).size());

                sendMessage(bye);
            }

            // Attempt a graceful shutdown
            shutdown(*mSocketFd, SHUT_RDWR);

            // Close the socket
            logger("Socket 'FD = %d' has been closed.", *mSocketFd);
            close(*mSocketFd);
            *mSocketFd = SOCKET_CLOSED;

            logger("Connection state set to: DISCONNECTED.");
            mIsConnected = DISCONNECTED;
        } // if(*mSocketFd > SOCKET_CLOSED)
    } // UdpCommunicationHandler::closeConnection

    void UdpCommunicationHandler::sendMessage(const MessageContent messageContent) {
        // Extract the vector<uint8_t> from the MessageContent variant
        vector<uint8_t> contentToSend;
        if(holds_alternative<vector<uint8_t>>(messageContent)) {
            contentToSend = get<vector<uint8_t>>(messageContent);
            logger("MessageContent extracted as vector<uint8_t> with size=%zu", contentToSend.size());
        }
        // We can recover from this issue by converting string to byte sequence
        else if(holds_alternative<string>(messageContent)) {
            auto holdsString = get<string>(messageContent);
            contentToSend.assign(holdsString.begin(), holdsString.end());
            logger("Oops, MessageContent extracted as string with size=%zu", holdsString.size());
        }
        else {
            logger("sendMessage() error for UDP: The custom variant data type 'MessageContent' is not a 'vector<uint8_t>'.");
            throw InternalErrorException(
                    "sendMessage() error for UDP: The custom variant data type "
                    "'MessageContent' is not a 'vector<uint8_t>'. ",
                    ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                    );
        }

        // Check if the connection is established
        if(!mIsConnected) {
            logger("Trying to send UDP message while not connected.");
            throw UnestablishedConnectionErrorException(
                    "Trying to send UDP message while not connected.",
                    ClientInternalErrorMessage::CLIENT_CONNECTION_ERROR
                    );
        }

        // Extract the message ID from the byte message content
        const uint16_t messageId = CastUtils::castTwoBytesToWord(contentToSend, MessageFields::UDP_MESSAGE_ID_START_BYTE);
        logger("Extracted messageId=%u from contentToSend", messageId);

        // Retransmission loop
        int attemptsRemaining = mUdpMaxRetransmit + 1; // +1 for the first attempt

        string byteLog = "Bytes: ";
        for(size_t i = 0; i < contentToSend.size(); ++i) {
            byteLog += format("[{}]:{:02X} ", i, contentToSend[i]);
        }
        logger("Sending content: %s", byteLog.c_str());

        while(attemptsRemaining > 0) {
            // Send the message
            const ssize_t bytesSent = sendto(*mSocketFd, contentToSend.data(), contentToSend.size(), 0,
                                             reinterpret_cast<sockaddr*>(&mServerAddr), mServerAddrLen);

            // If the sendto() function returns an error
            if(bytesSent < 0) {
                // EAGAIN = EWOULDBLOCK = non-blocking wait for possible action
                if(errno == EAGAIN || errno == EWOULDBLOCK) {
                    logger("sendMessage(): sendto() returned EAGAIN or EWOULDBLOCK, "
                           "skipping retransmission: %s", strerror(errno));
                    return;
                }

                mIsConnected = DISCONNECTED;
                logger("sendMessage(): sendto() returned error: Failed to send message. Socket 'FD = %d', "
                       "error: %s, Bytes: %zd", *mSocketFd, strerror(errno), bytesSent);
                throw ConnectionErrorException(
                        "Failed to send data to the server due to sendto() error: " + string(strerror(errno)),
                        ClientInternalErrorMessage::CLIENT_SEND_FAILURE
                        );
            }
            // If the sendto() function returns 0, it means the connection has been closed
            if(bytesSent == 0) {
                mIsConnected = DISCONNECTED;
                logger("sendMessage(): sendto() returned 0: Connection closed by server");
                throw ServerDisconnectedException(
                        "Connection closed by server. No data sent.",
                        ClientInternalErrorMessage::CLIENT_SERVER_CLOSURE
                        );
            }

            // Every message must be confirmed by CONFIRM, otherwise we retransmit
            if(waitForConfirm(messageId)) {
                logger("sendMessage() completed successfully");
                return;
            }

            attemptsRemaining--;
        } // while(attemptsRemaining > 0)

        throw MessageLostErrorException(
                "No CONFIRM message was received after 1 + "
                + to_string(mUdpMaxRetransmit) + " retransmissions.",
                ClientInternalErrorMessage::CLIENT_MESSAGE_LOST
                );
    } // UdpCommunicationHandler::sendMessage

    vector<ParsedMessage> UdpCommunicationHandler::receiveMessages() {
        // Check if the connection is established
        if(!mIsConnected) {
            logger("Attempted to receive data while not connected.");
            throw UnestablishedConnectionErrorException(
                    "Attempted to receive data while not connected.",
                    ClientInternalErrorMessage::CLIENT_CONNECTION_ERROR
                    );
        }

        // First we insert the waiting parsed messages
        vector<ParsedMessage> receivedMessages;
        receivedMessages.swap(mStagedMessages);
        logger("Swapped temporary parsed messages, size=%zu", receivedMessages.size());

        // If the recvfrom() function returns an error
        while(true) {
            // We set up the pollfd structure to monitor the socket descriptor and poll
            pollfd fdWatcher{*mSocketFd, POLL_FD_COUNT}; // POLLIN
            const int eventCount = poll(&fdWatcher, POLL_FD_COUNT, POLL_TIMEOUT_DONT_WAIT);

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
            // Check if an event occured during poll()
            if(eventCount == 0) {
                break;  // No events
            }

            // Allocate a buffer for receiving data
            vector<uint8_t> receiveBuffer(ClientLimits::MAX_UDP_PACKET_SIZE);

            // Receive data from the server in an non-blocking manner
            sockaddr_in sourceAddress{};
            socklen_t sourceAddressLength = sizeof(sourceAddress);
            const ssize_t bytesReceived = recvfrom(*mSocketFd, receiveBuffer.data(), receiveBuffer.size(), 0,
                                                   reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

            // If the recvfrom() function returns an error
            if(bytesReceived < 0) {
                mIsConnected = DISCONNECTED;
                logger("recvfrom() returned error: Failed to receive data. Socket 'FD = %d', "
                       "error: %s", *mSocketFd, strerror(errno));

                if(errno == EAGAIN || errno == EWOULDBLOCK) {
                    logger("recvfrom() returned EAGAIN or EWOULDBLOCK: UDP datagram exceeds maximum size.");
                    throw ProtocolErrorException(
                            "UDP datagram exceeds maximum size.",
                            ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE);
                }
                else {
                    throw ConnectionErrorException(
                            "Failed to receive data from the server due to recvfrom() error: " +
                            string(strerror(errno)), ClientInternalErrorMessage::CLIENT_RECEIVE_FAILURE
                            );
                }
            }

            // If the recvfrom() function returns 0, it means the connection has been closed
            if(bytesReceived == 0) {
                mIsConnected = DISCONNECTED;
                logger("sendConfirm(): sendto() returned 0: Connection closed by server");
                throw ServerDisconnectedException(
                        "Connection closed by server. No data sent.",
                        ClientInternalErrorMessage::CLIENT_SERVER_CLOSURE
                        );
            }

            // We must reflect the UDP dynamically changing port in the socket address
            switchDynamicPort(sourceAddress);

            // Make the received bytes the message content
            receiveBuffer.resize(CastUtils::castIntToSizeT(bytesReceived));
            logger("Received datagram resized to: %zu bytes", receiveBuffer.size());

            // Then we process the new incoming datagrams
            handleIncomingDatagram(receiveBuffer, receivedMessages, nullopt);
            logger("UDP message received successfully. Bytes received: %zu", bytesReceived);
        }

        // May be empty if only CONFIRM messages were received
        return receivedMessages;
    } // UdpCommunicationHandler::receiveMessages

    void UdpCommunicationHandler::sendConfirm(const uint16_t refMessageId) {
        logger("sendConfirm() called with refMessageId=%u", refMessageId);

        // First we build the CONFIRM message
        const MessageContent confirmMessage = mMessageBuilder->buildMessage(MessageType::CONFIRM, refMessageId);
        const auto &messageContent = get<vector<uint8_t>>(confirmMessage);
        logger("Built CONFIRM message with size=%zu", messageContent.size());

        string byteLog = "Bytes: ";
        for(size_t i = 0; i < messageContent.size(); ++i) {
            byteLog += format("[{}]:{:02X} ", i, messageContent[i]);
        }
        logger("Sending content: %s", byteLog.c_str());

        // Then we send the CONFIRM message in non-blocking manner
        const ssize_t bytesSent = sendto(*mSocketFd, messageContent.data(), messageContent.size(), 0, reinterpret_cast<sockaddr*>(&mServerAddr), mServerAddrLen);
        logger("sendConfirm(): sendto() called for CONFIRM message, bytesSent=%zd", bytesSent);

        // If the sendto() function returns an error
        if(bytesSent < 0) {
            // EAGAIN = EWOULDBLOCK = non-blocking wait for possible action
            if(errno == EAGAIN || errno == EWOULDBLOCK) {
                logger("sendConfirm(): sendto() returned EAGAIN or EWOULDBLOCK, "
                       "skipping retransmission: %s", strerror(errno));
                return;
            }

            mIsConnected = DISCONNECTED;
            logger("sendConfirm(): sendto() returned error: Failed to send message. Socket 'FD = %d', "
                   "error: %s, Bytes: %zd", *mSocketFd, strerror(errno), bytesSent);
            throw ConnectionErrorException(
                    "Failed to send data to the server due to sendto() error: " + string(strerror(errno)),
                    ClientInternalErrorMessage::CLIENT_SEND_FAILURE
                    );
        }
        // If the sendto() function returns 0, it means the connection has been closed
        if(bytesSent == 0) {
            mIsConnected = DISCONNECTED;
            logger("sendMessage(): sendto() returned 0: Connection closed by server");
            throw ServerDisconnectedException(
                    "Connection closed by server. No data sent.",
                    ClientInternalErrorMessage::CLIENT_SERVER_CLOSURE
                    );
        }

        logger("CONFIRM message sent successfully for refMessageId=%u", refMessageId);
    } // UdpCommunicationHandler::sendConfirm

    bool UdpCommunicationHandler::waitForConfirm(const uint16_t waitingForId) {
        logger("waitForConfirm() called with waitingForId=%u", waitingForId);

        // Set the timeout deadline
        const auto timeoutDeadline = chrono::steady_clock::now() + chrono::milliseconds(mUdpTimeoutMs);

        // Polling interval is half the given timeout for better success rate
        const int stepMs = max(1, mUdpTimeoutMs / 2);

        // Wait for incoming datagrams
        while(chrono::steady_clock::now() < timeoutDeadline) {
            // We set up the pollfd structure to monitor the socket descriptor and poll
            pollfd fdWatcher{*mSocketFd, POLL_FD_COUNT}; // 0

            // The poll internval is the minimum of the remaining timeout and the step
            const int remainingTimeoutMs =
                    static_cast<int>(chrono::duration_cast<chrono::milliseconds>(timeoutDeadline - chrono::steady_clock::now()).count());

            // Wait for events on the socket
            const int eventCount = poll(&fdWatcher, POLL_FD_COUNT, min(stepMs, remainingTimeoutMs));

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
            // Check if an event occured during poll()
            if(eventCount == 0) {
                continue;  // No events
            }

            // Process incoming datagrams
            if(fdWatcher.revents & POLLIN) {
                // Allocate a buffer for receiving data
                vector<uint8_t> receiveBuffer(ClientLimits::MAX_UDP_PACKET_SIZE);

                // Receive data from the server in an non-blocking manner
                sockaddr_in sourceAddress{};
                socklen_t sourceAddressLength = sizeof(sourceAddress);
                const ssize_t bytesReceived = recvfrom(*mSocketFd, receiveBuffer.data(), receiveBuffer.size(), MSG_DONTWAIT,
                                                       reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

                // If the recvfrom() function returns an error or nothing, we try again
                if(bytesReceived <= 0) {
                    continue;
                }

                // We must reflect the UDP dynamically changing port in the socket address
                switchDynamicPort(sourceAddress);

                // Make the received bytes the message content
                receiveBuffer.resize(CastUtils::castIntToSizeT(bytesReceived));
                logger("Received datagram resized to: %zu bytes", receiveBuffer.size());

                // Handles all incoming datagrams and returns the parsed messages via outParsedMessage parameter
                vector<ParsedMessage> parsedMessages;
                const bool receivedExpectedConfirm = handleIncomingDatagram(receiveBuffer, parsedMessages, waitingForId);

                // We save non-COMFIRM messages for later processing and handling in 'receiveMessages()'
                mStagedMessages.insert(mStagedMessages.end(), parsedMessages.begin(), parsedMessages.end());

                // Expected CONFIRM received
                if(receivedExpectedConfirm) {
                    logger("Expected CONFIRM message received for messageId=%u", waitingForId);
                    return true;
                }
            } // if(fdWatcher.revents & POLLIN)
        } // while(chrono::steady_clock::now() < timeoutDeadline

        return false;  // Timeout
    } // UdpCommunicationHandler::waitForConfirm

    bool UdpCommunicationHandler::handleIncomingDatagram(const vector<uint8_t> &receiveBuffer, vector<ParsedMessage> &outParsedMessage,
                                                         const optional<uint16_t> expectedMessageIdToConfirm) {
        logger("handleIncomingDatagram() called with receiveBuffer size=%zu, expectedMessageIdToConfirm=%s",
               receiveBuffer.size(), expectedMessageIdToConfirm ? to_string(*expectedMessageIdToConfirm).c_str() : "nullopt");

        // We need to convert vector<uint8_t> to MessageContent because of parseIncomingMessages()
        const MessageContent messageContent{receiveBuffer};

        // We parse the incoming datagram into better structured messages
        const optional<vector<ParsedMessage>> parsedMessages = mMessageParser->parseIncomingMessages(messageContent);
        logger("Parsed %zu messages from incoming datagram", parsedMessages->size());

        // Check if any messages were parsed
        if(!parsedMessages) {
            logger("No messages parsed from incoming datagram");
            return false;
        }

        // Process the parsed messages
        bool receivedExpectedConfirm{false};
        for(auto &message : *parsedMessages) {
            logger("Proccesing message type: %s, id/refId: %hu",
                   CastUtils::castEnumToString(message.mType).c_str(), message.mRefMessageId);

            // We don't want to process CONFIRM messages here
            if(message.mType == MessageType::CONFIRM) {
                logger("CONFIRM message received. ExpectedMessageId: %s, ReceivedRefMessageId: %u",
                       expectedMessageIdToConfirm ? to_string(*expectedMessageIdToConfirm).c_str() : "nullopt",
                       message.mRefMessageId);

                // Check if the CONFIRM message matches the expected message ID
                if(expectedMessageIdToConfirm && message.mRefMessageId == *expectedMessageIdToConfirm) {
                    receivedExpectedConfirm = true;
                    logger("Expected CONFIRM message matched for MessageId: %u", message.mRefMessageId);
                }
                else {
                    logger("CONFIRM message did not match the expected MessageId.");
                }
                continue;
            }
            // Handle PING message
            if(message.mType == MessageType::PING) {
                logger("PING message received. Sending CONFIRM for RefMessageId: %u", message.mRefMessageId);
                sendConfirm(message.mRefMessageId);
                continue;
            }
            // Handle BYE message
            if(message.mType == MessageType::BYE) {
                logger("BYE message received. Sending CONFIRM for RefMessageId: %u", message.mRefMessageId);
                sendConfirm(message.mRefMessageId);
                throw ServerSendByeException();
            }

            // UDP deduplication
            const uint16_t messageId = message.mRefMessageId;
            if(!wasSeen(messageId)) {
                logger("MessageId=%u not seen before, marking as seen", messageId);
                markAsSeen(messageId);
                outParsedMessage.emplace_back(message);
            }
            else {
                logger("MessageId=%u already seen, skipping", messageId);
            }

            // We send CONFIRM for all messages (even for malformed) except for CONFIRM itself
            sendConfirm(messageId);
            logger("Sent CONFIRM for messageId=%u", messageId);

            // Check if the UDPMessageParser set the message as malformed
            if(message.mType == MessageType::UNKNOWN) {
                logger("UDPMessageParser set message as malformed. MessageId: %u", messageId);
                throw ProtocolErrorException(
                        "UDPMessageParser set message as malformed. MessageId: " + to_string(messageId),
                        ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE
                        );
            }
        } // for(auto &message : *parsedMessages)

        // True for CONFIRM messages, false otherwise
        logger("handleIncomingDatagram() returning isExpectedConfirm=%s", receivedExpectedConfirm ? "true" : "false");
        return receivedExpectedConfirm;
    } // UdpCommunicationHandler::handleIncomingDatagram

    void UdpCommunicationHandler::markAsSeen(uint16_t messageId) {
        // We push the message ID to the queue
        mSeenIds.emplace_back(messageId);

        // If the queue exceeds the maximum size, we remove tha oldest message ID
        if(mSeenIds.size() > MAX_STORED_SEEN_MESSAGES) {
            mSeenIds.pop_front();
        }
    } // UdpCommunicationHandler::markAsSeen

    bool UdpCommunicationHandler::wasSeen(const uint16_t messageId) const {
        return ranges::find(mSeenIds, messageId) != mSeenIds.end();
    } // UdpCommunicationHandler::wasSeen

    void UdpCommunicationHandler::switchDynamicPort(const sockaddr_in &formerSocketAdress) {
        const uint16_t formerPort = ntohs(mServerAddr.sin_port);
        const uint16_t newPort = ntohs(formerSocketAdress.sin_port);

        // Check if the port has changed
        if(formerPort != newPort) {
            mServerAddr.sin_port = formerSocketAdress.sin_port;
            logger("Switched server port from %u to %u", formerPort, newPort);
        }
    } // UdpCommunicationHandler::switchDynamicPort
} // IPK25ChatClient::Networking

/*** end of file UDPCommunicationHandler.cpp ***/
