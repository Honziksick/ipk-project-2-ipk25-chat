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
 * Last edit:    17.04.2025                                                    *
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
#include "Common/ParsedMessage.hpp"
#include <optional>  // std::optional

namespace IPK25ChatClient::Messaging::Parser
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
         * @brief Parses incoming messages and returns a collection of parsed
         *        messages.
         * @details This method processes the incoming message content, appends
         *          it to the internal buffer,  and attempts to extract and
         *          tokenize complete messages. If no complete messages are
         *          found, it returns an empty optional. If the message content
         *          is invalid, an exception is thrown.
         *
         * @param messageContent The incoming message content to be parsed.
         *
         * @return An optional vector of `ParsedMessage` objects if complete
         *         messages are successfully parsed, or `std::nullopt` if no
         *         complete messages are available.
         */
        virtual std::optional<std::vector<Common::ParsedMessage>> parseIncomingMessages(const Common::MessageContent &messageContent) = 0;
    }; // IMessageParser
} // IPK25ChatClient::Messaging::Parser

#endif // I_MESSAGE_PARSER_HPP

/*** end of file IMessageParser.hpp ***/
