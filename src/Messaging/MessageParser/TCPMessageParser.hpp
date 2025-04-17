/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessageParser.hpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `TcpMessageParser` class, which provides  *
 *               functionality for parsing TCP messages into structured data.  *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageParser.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining `TcpMessageParser` class for parsing raw TCP
 *        message content into structured data.
 */

#ifndef TCP_MESSAGE_PARSER_HPP
#define TCP_MESSAGE_PARSER_HPP

#include "Messaging/MessageParser/MessageParserBase.hpp"
#include "Common/ParsedMessage.hpp"
#include "Common/ChatDataTypes.hpp"
#include <string>    // std::string
#include <vector>    // std::vector
#include <optional>  // std::optional

namespace IPK25ChatClient::Messaging::Parser
{
    /**
     * @class TcpMessageParser
     * @brief A final class for parsing raw TCP message content into structured
     *        `ParsedMessage` objects.
     */
    class TcpMessageParser final : public MessageParserBase {
    public:
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
        std::optional<std::vector<Common::ParsedMessage>> parseIncomingMessages(const Common::MessageContent &messageContent) override;

    private:
        constexpr static auto TOKEN_DELIMITER = " ";  /**< Delimiter used to separate fields of the messages. */
        std::string mBuffer;  /**< A buffer to store incomplete message data. */

        /**
         * @brief Appends new data to the internal buffer.
         * @brief This method adds the provided data to the internal buffer,
         *        which is used to store incomplete messages until they can be
         *        fully parsed.
         *
         * @param newContent The data to append to the buffer.
         */
        void appendNewContent(const std::string &newContent);

        /**
         * @brief Attempts to extract completed messages from the buffer.
         * @details This method checks the internal buffer for complete messages
         *          based on the predefined delimiter. If complete messages are
         *          found, they are extracted and returned as a vector of strings.
         *
         * @return std::vector<std::string> A vector containing all completed
         *         messages extracted from the buffer.
         */
        std::vector<std::string> tryToExtractCompletedMessages();

        /**
         * @brief Tokenizes a single message into a `ParsedMessage` object.
         * @details This method processes a single message string and converts
         *          it into a structured `ParsedMessage` object by extracting
         *          relevant fields.
         *
         * @param message The message string to tokenize.
         * @return Common::ParsedMessage The parsed representation of the message.
         */
        static Common::ParsedMessage tokenizeMessage(const std::string &message);
    }; // TcpMessageParser
} // IPK25ChatClient::Messaging::Parser

#endif // TCP_MESSAGE_PARSER_HPP

/*** end of file TCPMessageParser.hpp ***/
