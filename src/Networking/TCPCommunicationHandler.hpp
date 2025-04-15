/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPCommunicationHandler.hpp                                   *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  This file declares the `TcpCommunicationHandler` class,       *
 *               which implements TCP-based communication for the IPK25 Chat   *
 *               Client. It extends the `CommunicationHandlerBase` class and   *
 *               provides methods for opening connections, sending messages,   *
 *               and receiving messages.                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPCommunicationHandler.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `TcpCommunicationHandler` class for
 *        TCP specific communication methods.
 */

#ifndef TCP_COMMUNICATION_HANDLER_HPP
#define TCP_COMMUNICATION_HANDLER_HPP

#include "Networking/CommunicationHandlerBase.hpp"
#include "Common/ParsedMessage.hpp"
#include "Common/ChatDataTypes.hpp"

namespace IPK25ChatClient::Networking
{
    /**
     * @class TcpCommunicationHandler
     * @brief Contains TCP-based communication methods for the IPK25 Chat Client.
     *
     * @details The `TcpCommunicationHandler` class extends the `CommunicationHandlerBase`
     *          class and provides methods for managing TCP connections, sending
     *          messages, and receiving messages. It also implements a
     *          protocol-specific graceful termination procedure.
     */
    class TcpCommunicationHandler final : public CommunicationHandlerBase {
    public:
        /**
         * @brief Inherits the constructor from the base class `CommunicationHandlerBase`.
         */
        using CommunicationHandlerBase::CommunicationHandlerBase;

        /**
         * @brief Opens a TCP connection to the server.
         *
         * @details This method resolves the server's hostname or IPv4 address
         *          and attempts to establish a TCP connection. If the connection
         *          is already established, it logs the status and returns without
         *          performing any action. If the connection fails for all resolved
         *          addresses, it throws a `ConnectionErrorException`.
         *
         */
        void openConnection() override;

        /**
         * @brief Sends a message to the server.
         *
         * @details This method sends the provided message content to the server
         *          over an established TCP connection. If the connection is not
         *          established, it throws an `InternalErrorException`. If the
         *          message cannot be sent, it logs the error and returns `false`.
         *
         * @param messageContent The content of the message to be sent.
         */
        void sendMessage(Common::MessageContent messageContent) override;

        /**
         * @brief Receives a message from the server.
         *
         * @details This method receives data from the server over an established
         *          TCP connection. If the connection is not established or the
         *          receive operation fails, it throws an `InternalErrorException`.
         *
         * @return The content of the received message.
         */
        Common::ParsedMessage receiveMessage() override;

    private:
        /**
         * @brief Performs a graceful shutdown of the TCP connection.
         *
         * @details This method attempts to terminate the TCP connection
         *          gracefully by sending a TCP FIN packet. If the shutdown
         *          operation fails, it throws a `ConnectionErrorException`.
         */
        void gracefulShutdown() override;
    }; // TCPCommunicationHandler
} // IPK25ChatClient::Networking

#endif // TCP_COMMUNICATION_HANDLER_HPP

/*** end of file TCPCommunicationHandler.hpp ***/
