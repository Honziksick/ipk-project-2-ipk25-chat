/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ICommunicationHandler.hpp                                     *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    09.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines the `ICommunicationHandler` interface,      *
 *               which provides an abstraction for managing both TCP and UDP   *
 *               communication in the IPK25 Chat Client. It declares methods   *
 *               for opening and closing connections, sending and receiving    *
 *               messages, and checking the connection status.                 *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ICommunicationHandler.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Interface for handling both TCP and UDP communication in the
 *        IPK25 Chat Client.
 */

#ifndef I_COMMUNICATION_HANDLER_HPP
#define I_COMMUNICATION_HANDLER_HPP

#include "Common/ChatDataTypes.hpp"

namespace IPK25ChatClient::Networking
{
    /**
     * @class ICommunicationHandler
     * @brief Abstract interface for handling communication in the chat client.
     *
     * @details This interface provides a contract for implementing communication
     *          handlers that manage both TCP and UDP connections, message
     *          transmission, and connection state monitoring.
     */
    class ICommunicationHandler {
    public:
        /**
         * @brief Virtual destructor for the interface.
         */
        virtual ~ICommunicationHandler() = default;

        /**
         * @brief Opens a connection to the server.
         *
         * @details This method establishes a connection to the specified
         *          server and prepares the handler for communication.
         */
        virtual void openConnection() = 0;

        /**
         * @brief Closes the active connection.
         *
         * @details This method gracefully terminates the connection and release
         *          any associated resources.
         */
        virtual void closeConnection() = 0;

        /**
         * @brief Sends a message to the server.
         *
         * @param messageContent The message content to be sent.
         * @return `true` if the message was sent successfully, `false` otherwise.
         */
        virtual bool sendMessage(Common::MessageContent messageContent) = 0;

        /**
         * @brief Receives a message from the server.
         *
         * @return The content of the received message.
         */
        virtual Common::MessageContent receiveMessage() = 0;

        /**
         * @brief Checks if the connection is currently active.
         *
         * @return `true` if the connection is active, `false` otherwise.
         */
        [[nodiscard]]
        virtual bool isConnected() const = 0;
    }; // ICommunicationHandler
} // IPK25ChatClient::Networking

#endif // I_COMMUNICATION_HANDLER_HPP

/*** end of file ICommunicationHandler.hpp ***/
