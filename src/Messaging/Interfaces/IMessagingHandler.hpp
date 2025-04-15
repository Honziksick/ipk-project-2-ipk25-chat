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
 * Last edit:    15.04.2025                                                    *
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
         * @brief Processes an incoming message.
         * @details This method is responsible for handling a parsed message
         *          and performing the appropriate action based on its type.
         *
         * @param parsedMessage The parsed message to process.
         */
        virtual void processIncomingMessage(const Common::ParsedMessage &parsedMessage) = 0;

        /**
         * @brief Sets the display name for the messaging handler.
         * @details Updates the display name used by the handler for outgoing
         *          messages.
         *
         * @param displayName The display name to set.
         */
        virtual void setDisplayName(const std::string &displayName) = 0;

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
         * @param displayName The display name of the user.
         */
        virtual void sendJoinMessage(const std::string &channelId,
                                     const std::string &displayName) = 0;

        /**
         * @brief Sends a message to a channel or user.
         * @details Constructs and sends a message containing the specified
         *          content to the target channel or user.
         *
         * @param displayName The display name of the sender.
         * @param messageContent The content of the message to send.
         */
        virtual void sendMsgMessage(const std::string &displayName,
                                    const std::string &messageContent) = 0;

        /**
         * @brief Sends a goodbye message.
         * @details Constructs and sends a message indicating that the user
         *          is leaving the chat or channel.
         */
        virtual void sendByeMessage() = 0;
    }; // IMessagingHandler
} // IPK25ChatClient::Messaging::Handler

#endif // I_MESSAGING_HANDLER_HPP

/*** end of file IMessagingHandler.hpp ***/
