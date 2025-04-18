/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessageParser.cpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `TCPMessageParser` class, which         *
 *               handles parsing of TCP messages in the chat client.           *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageParser.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `TCPMessageParser` class, responsible for
 *        parsing and processing TCP messages in the chat client.
 */

#include "Messaging/MessageParser/TCPMessageParser.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Common/ParsedMessage.hpp"
#include "Enums/MessageTypes.hpp"
#include "Constants/MessageFields.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>     // std::string, std::getline
#include <vector>     // std::vector
#include <optional>   // std::nullopt
#include <variant>    // holds_alternative<>(), std::get<>()
#include <exception>  // std::exception
#include <typeinfo>   // typeid()

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Utilities;
using namespace IPK25ChatClient::Exceptions;
using namespace std;

namespace IPK25ChatClient::Messaging::Parser
{
    optional<vector<ParsedMessage>> TcpMessageParser::parseIncomingMessages(const MessageContent &messageContent) {
        if(!holds_alternative<string>(messageContent)) {
            logger("Invalid MessageContent type. Expected string, but got: %s", typeid(messageContent).name());
            throw InternalErrorException(
                    "Expected string in MessageContent, but got " + string(typeid(messageContent).name()),
                    ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                    );
        }

        // We append the incoming data to the internal buffer.
        appendNewContent(get<string>(messageContent));

        // We check the contents of the buffer for complete messages.
        const vector<string> completeMessages = tryToExtractCompletedMessages();

        // If we have any complete message, we tokenize it
        if(!completeMessages.empty()) {
            try {
                vector<ParsedMessage> parsedMessages;
                for(auto &message : completeMessages) {
                    logger("Complete message found. Tokenizing message: %s", message.c_str());
                    parsedMessages.emplace_back(tokenizeMessage(message));
                }
                return parsedMessages;
            }
            catch(const exception &e) {
                logger("Error during message tokenization: %s", e.what());
                throw;
            }
        }
        // Else no complete messages are available yet
        else {
            logger("No complete messages found in the buffer.");
            return nullopt;
        }
    } // TcpMessageParser::parseIncomingMessages

    void TcpMessageParser::appendNewContent(const string &newContent) {
        logger("Appending new content to the buffer. New content: %s", newContent.c_str());
        mBuffer.append(newContent);
    } // TcpMessageParser::appendData

    vector<string> TcpMessageParser::tryToExtractCompletedMessages() {
        logger("Attempting to extract completed messages from the buffer. Current buffer: %s", mBuffer.c_str());

        // Find the first delimiter
        size_t delimiterPosition{mBuffer.find(END_OF_MESSAGE_DELIMITER)};

        // Process the buffer while delimiters are found (i.e., while there are complete messages)
        vector<string> completeMessages;
        while(delimiterPosition != string::npos) {
            // Add the complete message to the vector
            string message = mBuffer.substr(0, delimiterPosition);
            completeMessages.emplace_back(message);
            logger("Found a complete message: %s", message.c_str());

            // Remove the processed part of the buffer, including the delimiter
            mBuffer = mBuffer.substr(delimiterPosition + string(END_OF_MESSAGE_DELIMITER).length());

            // Find the next delimiter (if multiple complete messages are in the buffer)
            delimiterPosition = mBuffer.find(END_OF_MESSAGE_DELIMITER);
        }

        logger("Extraction complete. Remaining buffer: %s", mBuffer.c_str());
        return completeMessages;
    } // TcpMessageParser::tryToExtractCompletedMessages

    ParsedMessage TcpMessageParser::tokenizeMessage(const string &message) {
        logger("Tokenizing message: %s", message.c_str());

        // We find a first token, which represents the command
        const size_t firstDelimiterPosition = message.find(TOKEN_DELIMITER);
        if(firstDelimiterPosition == string::npos) {
            logger("Malformed message: missing token delimiter. Message: %s", message.c_str());
            throw ProtocolErrorException(
                    "Client received a malformed message from the server: missing delimiter",
                    ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE
                    );
        }
        const string messageTypeToken = message.substr(0, firstDelimiterPosition);
        logger("Message type token identified: %s", messageTypeToken.c_str());

        // ABNF strings are case-insensitive, and the character set for these
        // strings is US-ASCII. (Source: RFC 5234)
        auto messageType{MessageType::UNKNOWN};
        try {
            messageType = CastUtils::castStringToEnum<MessageType>(StringUtils::toLower(messageTypeToken));
        }
        catch(...) {
            logger("Malformed message: unknown message type. Message: %s", message.c_str());
            throw ProtocolErrorException(
                    "Client received a malformed message from the server: unknown message type.",
                    ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE
                    );
        }

        // We split the message using 'splitIntoFixedCount()' depanding on the message type
        ParsedMessage parsedMessage{};
        switch(messageType) {
            case MessageType::AUTH: {
                logger("Parsing AUTH message. Message: %s", message.c_str());

                // Expecting 6 tokens: AUTH {Username} AS {DisplayName} USING {Secret}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         MessageFields::TCP_EXPECTED_AUTH_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::AUTH;
                break;
            }
            case MessageType::JOIN: {
                logger("Parsing JOIN message. Message: %s", message.c_str());

                // Expecting 4 tokens: JOIN {ChannelID} AS {DisplayName}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         MessageFields::TCP_EXPECTED_JOIN_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::JOIN;
                break;
            }
            case MessageType::MSG: {
                logger("Parsing MSG message. Message: %s", message.c_str());

                // Expecting 5 tokens: MSG FROM {DisplayName} IS {MessageContent}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         MessageFields::TCP_EXPECTED_MSG_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::MSG;
                break;
            }
            case MessageType::ERR: {
                logger("Parsing ERR message. Message: %s", message.c_str());

                // Expecting 5 tokens: ERR FROM {DisplayName} IS {MessageContent}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         MessageFields::TCP_EXPECTED_ERR_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::ERR;
                break;
            }
            case MessageType::BYE: {
                logger("Parsing BYE message. Message: %s", message.c_str());

                // Expecting 3 tokens: BYE FROM {DisplayName}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         MessageFields::TCP_EXPECTED_BYE_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::BYE;
                break;
            }
            case MessageType::REPLY: {
                logger("Parsing REPLY message. Message: %s", message.c_str());

                // Expecting 4 tokens: REPLY {OK|NOK} IS {MessageContent}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         MessageFields::TCP_EXPECTED_REPLY_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::REPLY;
                break;
            }
            default: {
                logger("Malformed message: unknown message type. Message: %s", message.c_str());
                throw ProtocolErrorException(
                        "Client received a malformed message from the server: unknown message type.",
                        ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE
                        );
            }
        } // switch(commandTokenType)

        // We return the tokenized (parsed) message
        logger("Message tokenized successfully. Parsed message type: %s", CastUtils::castEnumToString(parsedMessage.mType).c_str());
        return parsedMessage;
    } // TcpMessageParser::tokenizeMessage
} // IPK25ChatClient::Messaging::Parser

/*** end of file TCPMessageParser.cpp ***/
