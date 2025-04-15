/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageBuilderBase.hpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining the abstract base class                  *
 *               `MessageBuilderBase` for constructing various types           *
 *               of messages used in the IPK25 Chat Client.                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageBuilderBase.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MessageBuilderBase` class, an abstract base
 *        class for constructing specific types of messages in the IPK25 Chat Client.
 */

#ifndef MESSAGE_BUILDER_BASE_HPP
#define MESSAGE_BUILDER_BASE_HPP

#include "Messaging/Interfaces/IMessageBuilder.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Common/UserCommand.hpp"
#include "Enums/MessageTypes.hpp"
#include <string>  // std::string

namespace IPK25ChatClient::Messaging
{
    /**
     * @class MessageBuilderBase
     * @brief Abstract base class that provides virtual methods for constructing
     *        specific types of messages.
     */
    class MessageBuilderBase : public IMessageBuilder {
    public:
        /**
         * @brief Constructor for the MessageBuilderBase class.
         */
        explicit MessageBuilderBase();

        /**
         * @brief Virtual destructor for the MessageBuilderBase class.
         */
        ~MessageBuilderBase() override = default;

        /**
         * @brief Constructs a message based on the provided user command.
         *
         * @param messageType The type of message to be constructed.
         * @param messageContent A reference to a `UserCommand` object containing
         *                       the data for the message to be constructed and
         *                       its type.
         *
         * @return A `MessageContent` object containing the constructed message.
         */
        Common::MessageContent buildMessage(Enums::MessageType messageType,
                                            const Common::UserCommand &messageContent) override;

    protected:
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
        virtual Common::MessageContent buildAuthMessage(const std::string &username,
                                                        const std::string &displayName,
                                                        const std::string &secret) = 0;

        /**
         * @brief Builds a join message for joining a channel.
         *
         * @param channelId The ID of the channel to join.
         * @param displayName The display name of the user.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        virtual Common::MessageContent buildJoinMessage(const std::string &channelId,
                                                        const std::string &displayName) = 0;

        /**
         * @brief Builds a message to send to a channel.
         *
         * @param displayName The display name of the user.
         * @param messageContent The content of the message.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        virtual Common::MessageContent buildMsgMessage(const std::string &displayName,
                                                       const std::string &messageContent) = 0;

        /**
         * @brief Builds an error message.
         *
         * @param displayName The display name of the user.
         * @param messageContent The content of the error message.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        virtual Common::MessageContent buildErrMessage(const std::string &displayName,
                                                       const std::string &messageContent) = 0;

        /**
         * @brief Builds a goodbye message.
         *
         * @param displayName The display name of the user.
         *
         * @return A `MessageContent` containing the constructed message
         *         (`std::string` for TCP and `std::vector<uint8_t>` for UDP).
         */
        virtual Common::MessageContent buildByeMessage(const std::string &displayName) = 0;
    }; // MessageBuilderBase
} // IPK25ChatClient::Messaging

#endif // MESSAGE_BUILDER_BASE_HPP

/*** end of file MessageBuilderBase.hpp ***/
