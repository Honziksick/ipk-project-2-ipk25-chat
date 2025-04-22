/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessageBuilder.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `UdpMessageBuilder` class, which          *
 *               provides methods for constructing various types of UDP        *
 *               messages in the IPK25 Chat Client project.                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessageBuilder.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `UdpMessageBuilder` class for building
 *        UDP messages.
 */

#ifndef UDP_MESSAGE_BUILDER_HPP
#define UDP_MESSAGE_BUILDER_HPP

#include "Messaging/MessageBuilder/MessageBuilderBase.hpp"
#include "Messaging/MessageBuilder/MessageIDProvider.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Common/UserCommand.hpp"
#include "Enums/MessageTypes.hpp"
#include <string>  // std::string
#include <vector>  // std::vector
#include <memory>  // std::unique_ptr

namespace IPK25ChatClient::Messaging::Builder
{
    /**
     * @class TcpMessageBuilder
     * @brief Provides methods for building various types of TCP messages.
     */
    class UdpMessageBuilder final : public MessageBuilderBase {
    public:
        /**
         * @brief Constructor for the `UdpMessageBuilder` class.
         */
        explicit UdpMessageBuilder();

        /**
         * @brief Constructs a message based on the provided user command.
         * @details This overload of the `buildMessage` method is used only when
         *          using the UDP protocol to cunstruct CONFIRM message.
         *
         * @param messageType The type of message to be constructed.
         * @param refMessageId The MessageID value of the message being confirmed.
         *
         * @return A `MessageContent` object containing the constructed message.
         */
        Common::MessageContent buildMessage(Enums::MessageType messageType,
                                            uint16_t refMessageId) override;

    private:
        std::unique_ptr<MessageIdProvider> mMessageIdProvider;  /**< MessageIdProvider provides and manages message IDs. */

        /**
         * @brief Appends a zero-terminated string to the provided byte message
         *        content vector.
         *
         * @param currentMessageContent A reference to the vector where the
         *                              content will be appended.
         * @param contentToAppend The string content to append, which will be
         *                        zero-terminated.
         */
        static void appendZeroTerminatedContent(std::vector<uint8_t> &currentMessageContent,
                                                const std::string &contentToAppend);

        /**
         * @brief Appends the 2-byte long message ID in network byte order
         *        to the provided byte message content vector.
         *
         * @param currentMessageContent A reference to the vector where the
         *                              message ID will be appended.
         */
        void appendMessageIdAsNetworkByteOrder(std::vector<uint8_t> &currentMessageContent) const;

        /**
         * @brief Appends the 2-byte long referential message ID in network
         *        byte order to the provided byte message content vector.
         *
         * @details Referential message ID is used for confirming messages in
         *          UDP protocol and determines on which message are we reacting.
         *
         * @param currentMessageContent A reference to the vector where the
         *                              message ID will be appended.
         * @param refMessageId The MessageID value of the message being confirmed.
         */
        static void appendRefMessageIdAsNetworkByteOrder(std::vector<uint8_t> &currentMessageContent, uint16_t refMessageId);

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

        /**
         * @brief Builds a confirm message (unique for UDP variant).
         *
         * @param refMessageId The MessageID value of the message being confirmed.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        static Common::MessageContent buildConfirmMessage(uint16_t refMessageId);
    }; // UdpMessageBuilder
} // IPK25ChatClient::Messaging::Builder

#endif // UDP_MESSAGE_BUILDER_HPP

/*** end of file UDPMessageBuilder.hpp ***/
