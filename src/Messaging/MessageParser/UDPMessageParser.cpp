/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessageParser.cpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `UdpMessageParser` class, which         *
 *               handles parsing of UDP messages in the chat client.           *
 *               The class is deliberately written to mirror the structure     *
 *               of `UDPMessageParser`, while respecting the binary framing    *
 *               rules of the UDP variant described in the project spec.       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessageParser.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `UdpMessageParser` class, responsible for
 *        parsing and processing UDP messages in the chat client.
 */

#include "Messaging/MessageParser/UDPMessageParser.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Common/ParsedMessage.hpp"
#include "Enums/MessageTypes.hpp"
#include "Constants/MessageFields.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>     // std::string
#include <vector>     // std::vector
#include <optional>   // std::optional
#include <variant>    // std::holds_alternative, std::get
#include <typeinfo>   // std::typeid
#include <algorithm>  // std::find(), std::distance()
#include <utility>    // std::move()


using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Utilities;
using namespace IPK25ChatClient::Exceptions;
using namespace std;

namespace IPK25ChatClient::Messaging::Parser
{
    UdpMessageParser::UdpMessageParser(): mErrorFlag{false} {}

    optional<vector<ParsedMessage>> UdpMessageParser::parseIncomingMessages(const MessageContent &messageContent) {
        logger("Entering function parseIncomingMessages()");

        if(!holds_alternative<vector<uint8_t>>(messageContent)) {
            logger("Invalid MessageContent type. Expected: vector<uint8_t>, but got: %s", typeid(messageContent).name());
            throw InternalErrorException(
                    "Expected vector<uint8_t> in MessageContent, but got " + string(typeid(messageContent).name()),
                    ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR);
        }

        // We check if the datagram is long enough to contain the header.
        const auto udpByteStream = get<vector<uint8_t>>(messageContent);
        doesItContainChatHeader(udpByteStream);

        // Preparing to parse the incoming messages
        vector<ParsedMessage> parsedMessages;
        size_t startIndex = 0;

        // Process each complete message in the UDP byte stream until no more headers can be found
        while(startIndex + MessageFields::UDP_CHAT_HEADER_SIZE <= udpByteStream.size()) {
            logger("Tokenizing message at startIndex: %zu", startIndex);
            parsedMessages.emplace_back(tokenizeMessage(udpByteStream, startIndex));
        }

        // Check if any complete messages were parsed from the buffer
        if(parsedMessages.empty()) {
            logger("No complete messages found in the buffer.");
            return nullopt;
        }

        logger("Parsed %zu messages successfully.", parsedMessages.size());
        return parsedMessages;
    } // UdpMessageParser::parseIncomingMessages

    ParsedMessage UdpMessageParser::tokenizeMessage(const vector<uint8_t> &udpByteStream, size_t &startIndex) {
        logger("Entering function. startIndex: %zu, udpByteStream size: %zu", startIndex, udpByteStream.size());

        // First we parse the header
        ParsedMessage parsedMessage{};
        parseUdpChatHeader(udpByteStream, startIndex, parsedMessage);

        // Then we parse the body according to the message type
        switch(parsedMessage.mType) {
            case MessageType::CONFIRM:
            case MessageType::PING:
                // We don't need to parse anything else for these messages
                logger("Message type %s does not require body parsing.", CastUtils::castEnumToString(parsedMessage.mType).c_str());
                break;
            case MessageType::REPLY:
                parseReply(udpByteStream, startIndex, parsedMessage);
                break;
            case MessageType::AUTH:
                parseAuth(udpByteStream, startIndex, parsedMessage);
                break;
            case MessageType::JOIN:
                parseJoin(udpByteStream, startIndex, parsedMessage);
                break;
            case MessageType::MSG:
            case MessageType::ERR:
                parseMsgOrErr(udpByteStream, startIndex, parsedMessage);
                break;
            case MessageType::BYE:
                parseBye(udpByteStream, startIndex, parsedMessage);
                break;
            default:
                break;
        }

        // If the message is malformed or incomplete, we set its type to UNKNOWN
        if(mErrorFlag) {
            logger("Error flag is set. Returning ParsedMessage with MessageType::UNKNOWN.");
            parsedMessage.mType = MessageType::UNKNOWN;
        }

        return parsedMessage;
    } // UdpMessageParser::tokenizeMessage

    void UdpMessageParser::parseUdpChatHeader(const vector<uint8_t> &udpByteStream, size_t &startIndex, ParsedMessage &parsedMessage) {
        logger("Parsing UDP chat header at index: %zu", startIndex);

        // Extract the message type from the byte stream
        const MessageType messageType = CastUtils::castByteToMessageType(udpByteStream[startIndex]);
        logger("Extracted message type: %s", CastUtils::castEnumToString(messageType).c_str());

        // Extract the message ID from the byte stream
        const uint16_t messageId = CastUtils::castTwoBytesToWord(udpByteStream, startIndex + MessageFields::UDP_MESSAGE_ID_START_BYTE);
        logger("Extracted message ID: %u ([1] 0x%02X, [2] 0x%02X)", messageId,
               udpByteStream[startIndex + MessageFields::UDP_MESSAGE_ID_START_BYTE],
               udpByteStream[startIndex + MessageFields::UDP_MESSAGE_ID_START_BYTE + 1]);

        // Increment the start index by the size of the header
        startIndex += MessageFields::UDP_CHAT_HEADER_SIZE;
        logger("Updated start index after parsing header: %zu", startIndex);

        // Update the parsedMessage message object with the extracted values
        parsedMessage.mType = messageType;
        parsedMessage.mRefMessageId = messageId;  // 'refMessageId' for CONFIRM, 'messageId' otherwise
    } // UdpMessageParser::parseUdpChatHeader

    void UdpMessageParser::parseReply(const vector<uint8_t> &udpByteStream, size_t &startIndex, ParsedMessage &parsedMessage) {
        logger("Parsing REPLY. startIndex: %zu, udpByteStream size: %zu", startIndex, udpByteStream.size());

        // Check if enough bytes for casting to result and refMessageId remain
        if(startIndex + REPLY_RESULT_BYTE_SIZE + REPLY_REF_MESSAGE_ID_BYTE_SIZE > udpByteStream.size()) {
            logger("UDP REPLY too short. startIndex: %zu, udpByteStream size: %zu", startIndex, udpByteStream.size());
            mErrorFlag = true;
            return;
        }

        // Parse result
        const uint8_t result = udpByteStream[startIndex];
        startIndex += REPLY_RESULT_BYTE_SIZE;
        string resultString = (result == 1) ? "OK" : "NOK";
        logger("Parsed result: byte: %u, string: %s, newStart: %zu", result, resultString.c_str(), startIndex);

        // Parse refMessageId
        const uint16_t refMessageId = CastUtils::castTwoBytesToWord(udpByteStream, startIndex);
        startIndex += REPLY_REF_MESSAGE_ID_BYTE_SIZE;
        logger("Parsed refMessageId = %u, newStart: %zu", refMessageId, startIndex);

        // Parse messageContent
        vector<string> fields;
        parseStringFields(udpByteStream, startIndex, fields, MessageFields::UDP_EXPECTED_REPLY_MESSAGE_FIELDS - 2);

        parsedMessage.mFields = {move(resultString), to_string(refMessageId), move(fields[0])};
        logger("ParsedMessage fields set. Fields: [%s, %s, %s]",
               parsedMessage.mFields[MessageFields::UDP_REPLY_RESULT_KEYWORD_INDEX].c_str(),
               parsedMessage.mFields[MessageFields::UDP_REPLY_REF_MESSAGE_ID_INDEX].c_str(),
               parsedMessage.mFields[MessageFields::UDP_REPLY_MESSAGE_CONTENT_INDEX].c_str());
    } // UdpMessageParser::parseReply

    void UdpMessageParser::parseAuth(const vector<uint8_t> &udpByteStream, size_t &startIndex, ParsedMessage &parsedMessage) {
        logger("Parsing AUTH. startIndex: %zu, udpByteStream size: %zu", startIndex, udpByteStream.size());

        // Parse username, displayName and secret
        vector<string> fields;
        parseStringFields(udpByteStream, startIndex, fields, MessageFields::UDP_EXPECTED_AUTH_MESSAGE_FIELDS);

        parsedMessage.mFields = move(fields);
        logger("ParsedMessage fields set. Fields: [%s, %s, %s]",
               parsedMessage.mFields[MessageFields::UDP_AUTH_USERNAME_INDEX].c_str(),
               parsedMessage.mFields[MessageFields::UDP_AUTH_DISPLAY_NAME_INDEX].c_str(),
               parsedMessage.mFields[MessageFields::UDP_AUTH_SECRET_INDEX].c_str());
    } // UdpMessageParser::parseAuth

    void UdpMessageParser::parseJoin(const vector<uint8_t> &udpByteStream, size_t &startIndex, ParsedMessage &parsedMessage) {
        logger("Parsing JOIN. startIndex: %zu, udpByteStream size: %zu", startIndex, udpByteStream.size());

        // Parse channelID and displayName
        vector<string> fields;
        parseStringFields(udpByteStream, startIndex, fields, MessageFields::UDP_EXPECTED_JOIN_MESSAGE_FIELDS);

        parsedMessage.mFields = move(fields);
        logger("ParsedMessage fields set. Fields: [%s, %s]",
               parsedMessage.mFields[MessageFields::UDP_JOIN_CHANNEL_ID_INDEX].c_str(),
               parsedMessage.mFields[MessageFields::UDP_JOIN_DISPLAY_NAME_INDEX].c_str());
    } // UdpMessageParser::parseJoin

    void UdpMessageParser::parseMsgOrErr(const vector<uint8_t> &udpByteStream, size_t &startIndex, ParsedMessage &parsedMessage) {
        logger("Parsing %s. startIndex: %zu, udpByteStream size: %zu", CastUtils::castEnumToString(parsedMessage.mType).c_str(), startIndex, udpByteStream.size());

        // Parse displayName and messageContent
        vector<string> fields;
        parseStringFields(udpByteStream, startIndex, fields, MessageFields::UDP_EXPECTED_MSG_MESSAGE_FIELDS);

        parsedMessage.mFields = move(fields);
        logger("ParsedMessage fields set. Fields: [%s, %s]",
               parsedMessage.mFields[MessageFields::UDP_MSG_DISPLAY_NAME_INDEX].c_str(),
               parsedMessage.mFields[MessageFields::UDP_MSG_MESSAGE_CONTENT_INDEX].c_str());
    } // UdpMessageParser::parseMsgOrErr

    void UdpMessageParser::parseBye(const vector<uint8_t> &udpByteStream, size_t &startIndex, ParsedMessage &parsedMessage) {
        logger("Entering function. startIndex: %zu, udpByteStream size: %zu", startIndex, udpByteStream.size());

        // Parse displayName
        vector<string> fields;
        parseStringFields(udpByteStream, startIndex, fields, MessageFields::UDP_EXPECTED_BYE_MESSAGE_FIELDS);

        parsedMessage.mFields = move(fields);
        logger("ParsedMessage fields set. Fields: [%s]",
               parsedMessage.mFields[MessageFields::UDP_BYE_DISPLAY_NAME_INDEX].c_str());
    } // UdpMessageParser::parseBye

    void UdpMessageParser::doesItContainChatHeader(const vector<uint8_t> &udpByteStream) {
        logger("Checking if UDP datagram contains a valid chat header. Datagram size: %zu, "
               "required size: %zu", udpByteStream.size(), MessageFields::UDP_CHAT_HEADER_SIZE);

        if(udpByteStream.size() < MessageFields::UDP_CHAT_HEADER_SIZE) {
            logger("Received UDP datagram is too short (%zu B)", udpByteStream.size());
            throw ProtocolErrorException(
                    "The UDP datagram is too short (malformed message): missing header.",
                    ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE);
        }

        logger("UDP datagram contains a valid chat header.");
    } // UdpMessageParser::doesItContainChatHeader

    string UdpMessageParser::readUntilZeroTerminator(const vector<uint8_t> &udpByteStream, const size_t startIndex) {
        logger("Reading string until zero terminator. Start index: %zu, datagram size: %zu", startIndex, udpByteStream.size());

        if(udpByteStream.begin() + startIndex >= udpByteStream.end()) {
            logger("Malformed UDP message – start index out of range: %zu", startIndex);
            mErrorFlag = true;
            return string{};
        }

        const auto zeroTerminator = find(udpByteStream.begin() + startIndex, udpByteStream.end(), '\0');
        if(zeroTerminator == udpByteStream.end()) {
            logger("Malformed UDP message – unterminated string field starting at index: %zu", startIndex);
            mErrorFlag = true;
            return string{};
        }

        const string result(reinterpret_cast<const char*>(&udpByteStream[startIndex]),
                            distance(udpByteStream.begin() + startIndex, zeroTerminator));
        logger("Extracted string: '%s', length: %zu", result.c_str(), result.size());
        return result;
    } // UdpMessageParser::readUntilZeroTerminator

    void UdpMessageParser::parseStringFields(const vector<uint8_t> &udpByteStream, size_t &startIndex,
                                             vector<string> &fieldsVector, const size_t fieldCount) {
        // Parse the string fields from the byte stream
        for(size_t iField = 0; iField < fieldCount; iField++) {
            logger("Parsing string field %zu of %zu. Start index: %zu", iField + 1, fieldCount, startIndex);

            // Convert everything until '\0' to string
            string field = readUntilZeroTerminator(udpByteStream, startIndex);
            startIndex += field.size() + ZERO_TERMINATOR_BYTE_SIZE;

            // Check if the field malformed
            if(mErrorFlag) {
                break;
            }

            logger("Successfully parsed string field: '%s', new startIndex: %zu", field.c_str(), startIndex);
            fieldsVector.emplace_back(move(field));
        }
    } // UdpMessageParser::parseStringFields
} // IPK25ChatClient::Messaging::Parser

/*** end of file UDPMessageParser.cpp ***/
