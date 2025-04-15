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
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `TcpMessageBuilder` class, which          *
 *               provides methods for constructing various types of            *
 *               messages used in the IPK25 Chat Client.                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageBuilder.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Defines the `TcpMessageBuilder` class for building chat messages.
 */

#ifndef TCP_MESSAGE_BUILDER_HPP
#define TCP_MESSAGE_BUILDER_HPP

#include "Messaging/MessageBuilder/MessageBuilderBase.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Common/UserCommand.hpp"
#include "Enums/MessageTypes.hpp"
#include <string>   // std::string
#include <cstdint>  // uint16_t

namespace IPK25ChatClient::Messaging
{
    /**
     * @class TcpMessageBuilder
     * @brief Provides methods for building various types of TCP messages.
     */
    class TcpMessageBuilder final : public MessageBuilderBase {
    public:
        /**
         * @brief Constructs a message based on the provided user command.
         * @details This overload of the `buildMessage` method is used only when
         *          using the UDP protocol to cunstruct CONFIRM message.
         *
         * @note TCP doesn't support this overload.
         *
         * @param messageType The type of message to be constructed.
         * @param refMessageId The MessageID value of the message being confirmed.
         *
         * @return A `MessageContent` object containing the constructed message.
         */
        Common::MessageContent buildMessage(Enums::MessageType messageType,
                                            uint16_t refMessageId) override;

    private:
        /**
         * @brief Builds an authentication message.
         *
         * @param username The username of the user.
         * @param displayName The display name of the user.
         * @param secret The secret for authentication.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        Common::MessageContent buildAuthMessage(const std::string &username,
                                                const std::string &displayName,
                                                const std::string &secret) override;

        /**
         * @brief Builds a join message for joining a channel.
         *
         * @param channelId The ID of the channel to join.
         * @param displayName The display name of the user.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        Common::MessageContent buildJoinMessage(const std::string &channelId,
                                                const std::string &displayName) override;

        /**
         * @brief Builds a message to send to a channel.
         *
         * @param displayName The display name of the user.
         * @param messageContent The content of the message.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        Common::MessageContent buildMsgMessage(const std::string &displayName,
                                               const std::string &messageContent) override;

        /**
         * @brief Builds an error message.
         *
         * @param displayName The display name of the user.
         * @param messageContent The content of the error message.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        Common::MessageContent buildErrMessage(const std::string &displayName,
                                               const std::string &messageContent) override;

        /**
         * @brief Builds a goodbye message.
         *
         * @param displayName The display name of the user.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        Common::MessageContent buildByeMessage(const std::string &displayName) override;
    }; // TcpMessageBuilder
} // IPK25ChatClient::Messaging

#endif // TCP_MESSAGE_BUILDER_HPP

/*** end of file TCPMessageBuilder.hpp ***/
