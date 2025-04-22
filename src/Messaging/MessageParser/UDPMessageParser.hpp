/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessageParser.hpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `UdpMessageParser` class, which handles    *
 *               parsing of UDP messages in the chat client. The class is      *
 *               deliberately written to mirror the structure of               *
 *               `TCPMessageParser`, while respecting the binary framing       *
 *               rules of the UDP variant described in the project spec.       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessageParser.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `UdpMessageParser` class, responsible for
 *        parsing and processing UDP messages in the chat client.
 */

#ifndef UDP_MESSAGE_PARSER_HPP
#define UDP_MESSAGE_PARSER_HPP

#include "Messaging/Interfaces/IMessageParser.hpp"
#include "Common/ParsedMessage.hpp"
#include "Common/ChatDataTypes.hpp"
#include <string>    // std::string
#include <optional>  // std::optional

namespace IPK25ChatClient::Messaging::Parser
{
    /**
     * @class UdpMessageParser
     * @brief A class responsible for parsing UDP messages in the chat client.
     *
     * @details This class implements the `IMessageParser` interface and
     *          provides methods to parse raw UDP message content into
     *          structured `ParsedMessage` objects.
     */
    class UdpMessageParser final : public IMessageParser {
    public:
        /**
         * @brief Constructs a new `UdpMessageParser` object.
         */
        explicit UdpMessageParser();

        /**
         * @brief Parses raw message content into a `ParsedMessage` object.
         * @details This method processes the raw UDP message content and extracts
         *          structured information into `ParsedMessage` objects. If the
         *          message is incomplete or malformed, it returns `std::nullopt`.
         *
         * @param messageContent The raw message content to be parsed.
         *
         * @return std::optional<std::vector<Common::ParsedMessage>> If a complete
         *         message is available, its parsed representation is returned,
         *         otherwise, std::nullopt.
         */
        std::optional<std::vector<Common::ParsedMessage>> parseIncomingMessages(const Common::MessageContent &messageContent) override;

    private:
        static constexpr size_t ZERO_TERMINATOR_BYTE_SIZE{1};       /**< Size of the null terminator ('\0') in bytes.                       */
        static constexpr size_t REPLY_RESULT_BYTE_SIZE{1};          /**< Size of the result field in REPLY messages in bytes.               */
        static constexpr size_t REPLY_REF_MESSAGE_ID_BYTE_SIZE{2};  /**< Size of the reference message ID field in REPLY messages in bytes. */

        bool mErrorFlag;  /**< Flag to indicate if an error occurred during parsing. */

        /**
         * @brief Tokenizes a UDP message into a `ParsedMessage` object.
         * @details This method extracts the structured data from the raw UDP
         *          byte stream and populates a `ParsedMessage` object with the
         *          parsed information.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @return A `ParsedMessage` object containing the parsed data.
         */
        Common::ParsedMessage tokenizeMessage(const std::vector<unsigned char> &udpByteStream, size_t &startIndex);

        /**
         * @brief Checks if the UDP byte stream contains a valid chat header.
         * @details This method validates the presence of a chat header in the
         *          UDP byte stream. If the header is invalid, an exception may
         *          be thrown.
         *
         * @param udpByteStream The raw UDP byte stream.
         */
        static void doesItContainChatHeader(const std::vector<unsigned char> &udpByteStream);

        /**
         * @brief Reads a null-terminated string from the UDP byte stream.
         * @details This method extracts a string from the byte stream, stopping
         *          at the first null terminator ('\0'). If no null terminator
         *          is found, an error is flagged.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for reading.
         *
         * @return The extracted string.
         */
        std::string readUntilZeroTerminator(const std::vector<uint8_t> &udpByteStream, size_t startIndex);

        /**
         * @brief Parses multiple string fields from the UDP byte stream.
         * @details This method extracts a specified number of null-terminated
         *          strings from the byte stream and appends them to the provided
         *          vector.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param fieldsVector A vector to store the parsed string fields.
         * @param fieldCount The number of string fields to parse.
         */
        void parseStringFields(const std::vector<unsigned char> &udpByteStream, size_t &startIndex,
                               std::vector<std::string> &fieldsVector, size_t fieldCount);

        /**
         * @brief Parses the UDP chat header.
         * @details This method extracts the message type and message ID from
         *          the UDP byte stream and updates the `ParsedMessage` object
         *          with the parsed values.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param parsedMessage The `ParsedMessage` object to store the parsed data.
         */
        static void parseUdpChatHeader(const std::vector<unsigned char> &udpByteStream, size_t &startIndex,
                                       Common::ParsedMessage &parsedMessage);

        /**
         * @brief Parses a REPLY message.
         * @details This method extracts the result, reference message ID,
         *          and optional message content from a REPLY message in the
         *          UDP byte stream.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param parsedMessage The `ParsedMessage` object to store the parsed data.
         */
        void parseReply(const std::vector<uint8_t> &udpByteStream, size_t &startIndex, Common::ParsedMessage &parsedMessage);

        /**
         * @brief Parses an AUTH message.
         * @details This method extracts the username, display name, and secret
         *          from an AUTH message in the UDP byte stream.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param parsedMessage The `ParsedMessage` object to store the parsed data.
         */
        void parseAuth(const std::vector<uint8_t> &udpByteStream, size_t &startIndex, Common::ParsedMessage &parsedMessage);

        /**
         * @brief Parses a JOIN message.
         * @details This method extracts the channel ID and display name from
         *          a JOIN message in the UDP byte stream.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param parsedMessage The `ParsedMessage` object to store the parsed data.
         */
        void parseJoin(const std::vector<uint8_t> &udpByteStream, size_t &startIndex, Common::ParsedMessage &parsedMessage);

        /**
         * @brief Parses a MSG or ERR message.
         * @details This method extracts the display name and message content
         *          from a MSG or ERR message in the UDP byte stream.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param parsedMessage The `ParsedMessage` object to store the parsed data.
         */
        void parseMsgOrErr(const std::vector<uint8_t> &udpByteStream, size_t &startIndex, Common::ParsedMessage &parsedMessage);

        /**
         * @brief Parses a BYE message.
         * @details This method extracts the display name from a BYE message
         *          in the UDP byte stream.
         *
         * @param udpByteStream The raw UDP byte stream.
         * @param startIndex The starting index for parsing.
         * @param parsedMessage The `ParsedMessage` object to store the parsed data.
         */
        void parseBye(const std::vector<uint8_t> &udpByteStream, size_t &startIndex, Common::ParsedMessage &parsedMessage);

    }; // UdpMessageParser
} // IPK25ChatClient::Messaging::Parser

#endif // UDP_MESSAGE_PARSER_HPP

/*** end of file UDPMessageParser.hpp ***/
