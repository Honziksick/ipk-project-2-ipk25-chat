/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPCommunicationHandler.hpp                                   *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      17.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  This file declares the `UdpCommunicationHandler` class,       *
 *               which implements TCP-based communication for the IPK25 Chat   *
 *               Client. It extends the `CommunicationHandlerBase` class and   *
 *               provides methods for opening connections, sending messages,   *
 *               and receiving messages.                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPCommunicationHandler.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `UdpCommunicationHandler` class for
 *        TCP specific communication methods.
 */

#ifndef UDP_COMMUNICATION_HANDLER_HPP
#define UDP_COMMUNICATION_HANDLER_HPP

#include "Networking/CommunicationHandlerBase.hpp"
#include "Messaging/Interfaces/IMessageBuilder.hpp"
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Common/ParsedMessage.hpp"
#include "Common/ChatDataTypes.hpp"
#include <vector>        // std::vector
#include <memory>        // std::shared_ptr
#include <deque>         // std::deque
#include <netinet/in.h>  // sockaddr_in, socklen_t

namespace IPK25ChatClient::Networking
{
    /**
     * @class UdpCommunicationHandler
     * @brief A class for managing UDP communication in the IPK25 Chat Client.
     * @details This class provides functionality for establishing a UDP
     *          connection, sending and receiving messages, and handling
     *          message confirmations.
     */
    class UdpCommunicationHandler final : public CommunicationHandlerBase {
    public:
        /**
         * @brief Constructs a `UdpCommunicationHandler` object.
         * @details Initializes the UDP communication handler with the provided
         *          command line options, socket file descriptor, and message
         *          builder. This constructor sets up the necessary resources
         *          for managing UDP communication.
         *
         * @param commandLineOptions The command line options containing configuration for the handler.
         * @param socketFd A shared pointer to the socket file descriptor used for communication.
         * @param messageBuilder A shared pointer to the message builder used for constructing messages.
         * @param displayNameProvider A shared pointer to the display name provider for managing user display names.
         */
        explicit UdpCommunicationHandler(const Common::CommandLineOptions &commandLineOptions,
                                         const std::shared_ptr<int> &socketFd,
                                         const std::shared_ptr<Messaging::Builder::IMessageBuilder> &messageBuilder,
                                         std::shared_ptr<Client::CommandParser::DisplayNameProvider> displayNameProvider);

        /**
         * @brief Destructor for the `UdpCommunicationHandler` class.
         * @details The destructor closes the UDP connection if it is still open.
         */
        ~UdpCommunicationHandler() override;

        /**
         * @brief Opens a UDP connection to the server.
         * @details This method performs the following steps to establish the
         *          UDP connection. It resolves the server's hostname or IPv4
         *          address using the `CommunicationUtils::resolveHostname` utility.
         *          If the resolution fails, it throws a `HostnameResolutionErrorException`.
         *          Then it copies the resolved address information into the
         *          `mServerAddr` structure and sets its length and creates a
         *          UDP socket using the `socket` system call. If the socket
         *          creation fails, it throws a `ConnectionErrorException`.
         */
        void openConnection() override;

        /**
         * @brief Closes the current connection.
         * @details This method checks if the socket is still open and performs
         *          a graceful shutdown before closing the socket.
         *
         * @param sendBye Flag indicating whether to send a BYE message before termination.
         */
        void closeConnection(bool sendBye) override;

        /**
         * @brief Sends a message to the server.
         * @details This method sends the provided message content to the server
         *          over an established UDP connection. If the connection is not
         *          established, it throws an `InternalErrorException`. If the
         *          message cannot be sent, it logs the error and returns `false`.
         *
         * @param messageContent The content of the message to be sent.
         */
        void sendMessage(Common::MessageContent messageContent) override;

        /**
         * @brief Receives a message from the server.
         * @details This method handled the reception of messages from the
         *          server. It processes the incoming data and returns them in
         *          a structured format.
         *
         * @return A vector of `Common::ParsedMessage` objects representing the
         *         content of the received messages.
         */
        std::vector<Common::ParsedMessage> receiveMessages() override;

    private:
        static constexpr int POLL_FD_COUNT{1};                    /**< Number of file descriptors to poll.       */
        static constexpr int POLL_TIMEOUT_DONT_WAIT{0};           /**< Poll timeout for non-blocking wait.       */
        static constexpr size_t MAX_STORED_SEEN_MESSAGES = 1024;  /**< Maximum number of seen messages to store. */

        const uint8_t mUdpMaxRetransmit;  /**< Maximum number of retransmissions for UDP messages.   */
        const uint16_t mUdpTimeoutMs;     /**< Timeout for UDP operations in milliseconds.           */
        sockaddr_in mServerAddr{};        /**< Server address structure.                             */
        socklen_t mServerAddrLen{};       /**< Length of the server address structure.               */
        bool mServerPortSwitched;         /**< Flag indicating if the server port has been switched. */
        std::deque<uint16_t> mSeenIds;    /**< Deque storing IDs of seen messages.                   */
        std::vector<Common::ParsedMessage> mStagedMessages;                                /**< Vector of staged messages for processing.    */
        std::shared_ptr<Messaging::Builder::IMessageBuilder> mMessageBuilder;              /**< Shared pointer to the message builder.       */
        std::shared_ptr<Client::CommandParser::DisplayNameProvider> mDisplayNameProvider;  /**< Shared pointer to the display name provider. */

        /**
         * @brief Sends a confirmation for a received message.
         * @details This method sends a confirmation message to the server for
         *          a specific message ID that has been successfully received.
         *          The confirmation helps ensure reliable communication by
         *          acknowledging the receipt of the message. It uses the UDP
         *          socket to send the confirmation to the server.
         *
         * @param refMessageId The ID of the message to confirm. This ID is used
         *                     to identify the message being acknowledged.
         */
        void sendConfirm(uint16_t refMessageId);

        /**
         * @brief Waits for a confirmation for a specific message ID.
         * @details This method blocks execution until a confirmation is
         *          received for the specified message ID or a timeout occurs.
         *          It is used to ensure that the server has acknowledged the
         *          receipt of a message sent by the client.
         *
         * @param waitingForId The ID of the message to wait for confirmation.
         *                     This ID is used to match the confirmation response.
         *
         * @return `true` if the confirmation is received successfully, `false`
         *         if the confirmation is not received within the timeout period.
         */
        bool waitForConfirm(uint16_t waitingForId);

        /**
         * @brief Handles an incoming datagram.
         * @details This method processes a received UDP datagram. It parses
         *          the datagram into individual messages, validates their
         *          content, and optionally sends a confirmation for a specific
         *          message ID. The parsed messages are stored in the provided
         *          output vector for further processing.
         *
         * @param receiveBuffer The buffer containing the received datagram data.
         * @param outParsedMessage A vector to store the parsed messages extracted
         *                         from the datagram.
         * @param expectedMessageIdToConfirm An optional message ID to confirm. If provided,
         *                                    the method sends a confirmation for this message ID.
         *
         * @return `true` if the datagram was successfully processed, `false`
         *         if an error occurred during processing.
         */
        bool handleIncomingDatagram(const std::vector<uint8_t> &receiveBuffer,
                                    std::vector<Common::ParsedMessage> &outParsedMessage,
                                    std::optional<uint16_t> expectedMessageIdToConfirm);

        /**
         * @brief Marks a message ID as seen.
         * @details This method adds the specified message ID to the list of
         *          seen messages. It ensures that duplicate messages are not
         *          processed multiple times by maintaining a record of already
         *          seen message IDs.
         *
         * @param messageId The ID of the message to mark as seen. This ID is
         *                  added to the internal list of seen messages.
         */
        void markAsSeen(uint16_t messageId);

        /**
         * @brief Checks if a message ID has been seen.
         * @details This method checks whether the specified message ID is
         *          present in the list of seen messages. It is used to prevent
         *          processing duplicate messages.
         *
         * @param messageId The ID of the message to check.
         *
         * @return `true` if the message ID has already been seen, `false` otherwise.
         */
        [[nodiscard]]
        bool wasSeen(uint16_t messageId) const;

        /**
         * @brief Switches the dynamic port for communication.
         * @details This method updates the server address structure with a new
         *          port obtained from the provided address structure. It is
         *          used to handle dynamic port changes during communication.
         *
         * @param formerSocketAdress The address structure containing the new
         *                           port information. The method extracts the
         *                           port from this structure and updates the
         *                           server address accordingly.
         */
        void switchDynamicPort(const sockaddr_in &formerSocketAdress);
    }; // UDPCommunicationHandler
} // IPK25ChatClient::Networking

#endif // UDP_COMMUNICATION_HANDLER_HPP

/*** end of file UDPCommunicationHandler.hpp ***/
