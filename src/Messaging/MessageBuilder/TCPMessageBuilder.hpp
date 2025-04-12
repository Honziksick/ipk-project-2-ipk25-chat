/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessageBuilder.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    11.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `TcpMessageBuilder` class, which provides *
 *               static methods for constructing various types of messages     *
 *               used in the IPK25 Chat Client.                                *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageBuilder.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Defines the `TcpMessageBuilder` class for building chat messages.
 */

#ifndef TCP_MESSAGE_BUILDER_HPP
#define TCP_MESSAGE_BUILDER_HPP

#include <string>  // std::string

namespace IPK25ChatClient::Messaging
{
    /**
     * @class TcpMessageBuilder
     * @brief Provides static methods for building various types of TCP messages.
     */
    class TcpMessageBuilder final {
    public:
        /**
         * @brief Builds an authentication message.
         *
         * @param username The username of the user.
         * @param displayName The display name of the user.
         * @param secret The secret for authentication.
         *
         * @return A string containing the constructed authentication message.
         */
        static std::string buildAuthMessage(const std::string &username,
                                            const std::string &displayName,
                                            const std::string &secret);

        /**
         * @brief Builds a join message for joining a channel.
         *
         * @param channelId The ID of the channel to join.
         * @param displayName The display name of the user.
         *
         * @return A string containing the constructed join message.
         */
        static std::string buildJoinMessage(const std::string &channelId,
                                            const std::string &displayName);

        /**
         * @brief Builds a message to send to a channel.
         *
         * @param displayName The display name of the user.
         * @param messageContent The content of the message.
         *
         * @return A string containing the constructed message.
         */
        static std::string buildMsgMessage(const std::string &displayName,
                                           const std::string &messageContent);

        /**
         * @brief Builds an error message.
         *
         * @param displayName The display name of the user.
         * @param messageContent The content of the error message.
         *
         * @return A string containing the constructed error message.
         */
        static std::string buildErrMessage(const std::string &displayName,
                                           const std::string &messageContent);

        /**
         * @brief Builds a goodbye message.
         *
         * @param displayName The display name of the user.
         *
         * @return A string containing the constructed goodbye message.
         */
        static std::string buildByeMessage(const std::string &displayName);

        /**
         * @brief Builds a reply message indicating success or failure.
         *
         * @param messageContent The content of the reply message.
         * @param success A boolean indicating whether the operation was successful.
         *
         * @return A string containing the constructed reply message.
         */
        static std::string buildReplyMessage(const std::string &messageContent,
                                             bool success);
    }; // TcpMessageBuilder
} // IPK25ChatClient::Messaging

#endif // TCP_MESSAGE_BUILDER_HPP

/*** end of file TCPMessageBuilder.hpp ***/
