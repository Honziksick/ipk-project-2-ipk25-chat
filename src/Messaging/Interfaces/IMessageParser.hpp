/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IMessageParser.hpp                                            *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `IMessageParser` interface, which defines  *
 *               the contract for parsing messages in the chat client.         *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessageParser.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `IMessageParser` interface for parsing
 *        messages into structured `ParsedMessage` objects.
 */

#ifndef I_MESSAGE_PARSER_HPP
#define I_MESSAGE_PARSER_HPP

#include "Common/ChatDataTypes.hpp"
#include "Messaging/ParsedMessage.hpp"

namespace IPK25ChatClient::Messaging
{
    /**
     * @class IMessageParser
     * @brief Interface for parsing incoming messages in the chat client.
     */
    class IMessageParser {
    public:
        /**
         * @brief Virtual destructor for the `IMessageParser` interface.
         */
        virtual ~IMessageParser() = default;

        /**
         * @brief Parses raw message content into a `ParsedMessage` object.
         *
         * @param data The raw message content to be parsed.
         * @return A `ParsedMessage` object containing the parsed message data.
         */
        virtual ParsedMessage parseIncomingMessage(const Common::MessageContent &data) = 0;
    }; // IMessageParser
} // IPK25ChatClient::Messaging

#endif // I_MESSAGE_PARSER_HPP

/*** end of file IMessageParser.hpp ***/
