/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IMessagingHandler.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Interface for messaging handlers in the IPK25 Chat Client.    *
 *               Provides methods for processing incoming messages and         *
 *               sending various types of messages.                            *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessagingHandler.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining interface `IMessagingHandler` for handling
 *        messaging operations in the IPK25 Chat Client.
 */

#ifndef I_MESSAGING_HANDLER_HPP
#define I_MESSAGING_HANDLER_HPP

#include "Common/ParsedMessage.hpp"
#include <string>  // std::string

namespace IPK25ChatClient::Messaging::Handler
{
    /**
     * @class IMessagingHandler
     * @brief Abstract interface for messaging handlers.
     *
     * Defines methods for processing incoming messages and sending
     * authentication, join, message, and goodbye messages.
     */
    class IMessagingHandler {
    public:
        /**
         * @brief Virtual destructor for the interface.
         */
        virtual ~IMessagingHandler() = default;

        /**
         * @brief Opens a connection to the server.
         * @details This method establishes a connection to the specified
         *          server and prepares the handler for communication.
         */
        virtual void openConnection() = 0;

        /**
         * @brief Closes the active connection.
         * @details This method gracefully terminates the connection and release
         *          any associated resources.
         */
        virtual void closeConnection() = 0;

        /**
         * @brief Receives a message from the server and processes it.
         * @details This method is responsible for receiving a message from the
         *          server through the communication handler, parsing the message,
         *          and returning its content in a structured format. The
         *          implementation of this method is provided in the derived classes.
         *
         * @return std::vector<Common::ParsedMessage> Vector of parsed content
         *         of the received message.
         */
        virtual std::vector<Common::ParsedMessage> receiveMessages() = 0;

        /**
         * @brief Sends an authentication message.
         * @details Constructs and sends a message to authenticate the user
         *          with the provided credentials.
         *
         * @param username The username for authentication.
         * @param displayName The display name for the user.
         * @param secret The secret or password for authentication.
         */
        virtual void sendAuthMessage(const std::string &username,
                                     const std::string &displayName,
                                     const std::string &secret) = 0;

        /**
         * @brief Sends a join message to a specific channel.
         * @details Constructs and sends a message to join a channel with the
         *          specified channel ID and display name.
         *
         * @param channelId The ID of the channel to join.
         */
        virtual void sendJoinMessage(const std::string &channelId) = 0;

        /**
         * @brief Sends a message to a channel or user.
         * @details Constructs and sends a message containing the specified
         *          content to the target channel or user.
         *
         * @param messageContent The content of the message to send.
         */
        virtual void sendMsgMessage(const std::string &messageContent) = 0;

        /**
         * @brief Sends an error message.
         * @details Constructs and sends an error message with the specified
         *          content. This method "swallows" any exceptions thrown during
         *          the sending process.
         *
         * @param messageContent The content of the error message.
         */
        virtual void sendErrMessage(const std::string &messageContent) = 0;

        /**
         * @brief Sends a goodbye message.
         * @details Constructs and sends a message indicating that the user
         *          is leaving the chat or channel.
         */
        virtual void sendByeMessage() = 0;

        /**
         * @brief Handles an incoming message from the server.
         * @details This method processes a parsed message and performs the
         *          appropriate action based on its type, such as displaying a
         *          reply, message, or an error.
         *
         * @param parsedMessage The parsed message to be processed.
         */
        virtual void displayIncomingMessage(const Common::ParsedMessage &parsedMessage) = 0;
    }; // IMessagingHandler
} // IPK25ChatClient::Messaging::Handler

#endif // I_MESSAGING_HANDLER_HPP

/*** end of file IMessagingHandler.hpp ***/
