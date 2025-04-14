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
 * Last edit:    14.04.2025                                                    *
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

#include "Messaging/Interfaces/IMessageParser.hpp"
#include "Common/ParsedMessage.hpp"
#include "Common/ChatDataTypes.hpp"
#include <string>    // std::string
#include <vector>    // std::vector
#include <optional>  // std::optional

namespace IPK25ChatClient::Messaging
{
    /**
     * @class TcpMessageParser
     * @brief A final class for parsing raw TCP message content into structured
     *        `ParsedMessage` objects.
     */
    class TcpMessageParser final : public IMessageParser {
    public:
        /**
         * @brief Parses raw message content into a `ParsedMessage` object.
         *
         * @param messageContent The raw message content to be parsed.
         * @return std::optional<ParsedMessage> If a complete message is available,
         *         its parsed representation is returned; otherwise, std::nullopt.
         */
        std::optional<Common::ParsedMessage> parseIncomingMessage(const Common::MessageContent &messageContent) override;

    private:
        constexpr static auto END_OF_MESSAGE_DELIMITER = "\r\n";  /**< The delimiter used to identify the end of a message. */
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
} // IPK25ChatClient::Messaging

#endif // TCP_MESSAGE_PARSER_HPP

/*** end of file TCPMessageParser.hpp ***/
