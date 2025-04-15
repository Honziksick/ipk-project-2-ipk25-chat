/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IMessageBuilder.hpp                                           *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining the `IMessageBuilder` interface for      *
 *               building messages in the IPK25 Chat Client.                   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessageBuilder.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Defines the `IMessageBuilder` interface for constructing messages
 *        in the IPK25 Chat Client.
 */

#ifndef I_MESSAGE_BUILDER_HPP
#define I_MESSAGE_BUILDER_HPP

#include "Common/ChatDataTypes.hpp"
#include "Common/UserCommand.hpp"
#include "Enums/MessageTypes.hpp"

namespace IPK25ChatClient::Messaging::Builder
{
    /**
     * @class IMessageBuilder
     * @brief Interface for constructing messages in the IPK25 Chat Client.
     */
    class IMessageBuilder {
    public:
        /**
         * @brief Virtual destructor for the IMessageBuilder interface.
         */
        virtual ~IMessageBuilder() = default;

        /**
         * @brief Constructs a message based on the provided user command.
         * @details This overload of the `buildMessage` method is used to construct
         *          common TCP and UDP messages.
         *
         * @param messageType The type of message to be constructed.
         * @param messageContent A reference to a `UserCommand` object containing
         *                       the data for the message to be constructed and
         *                       its type.
         *
         * @return A `MessageContent` object containing the constructed message.
         */
        virtual Common::MessageContent buildMessage(Enums::MessageType messageType,
                                                    const Common::UserCommand &messageContent) = 0;

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
        virtual Common::MessageContent buildMessage(Enums::MessageType messageType,
                                                    uint16_t refMessageId) = 0;
    }; // IMessageBuilder
} // IPK25ChatClient::Messaging::Builder

#endif // I_MESSAGE_BUILDER_HPP

/*** end of file IMessageBuilder.hpp ***/
