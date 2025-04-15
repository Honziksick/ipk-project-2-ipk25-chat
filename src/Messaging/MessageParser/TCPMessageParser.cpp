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
 * Last edit:    15.04.2025                                                    *
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
#include "Constants/ClientLimits.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>    // std::string, std::getline
#include <vector>    // std::vector
#include <variant>   // std::get<>()
#include <optional>  // std::nullopt

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Utilities;
using namespace IPK25ChatClient::Exceptions;
using namespace std;

namespace IPK25ChatClient::Messaging::Parser
{
    optional<ParsedMessage> TcpMessageParser::parseIncomingMessage(const MessageContent &messageContent) {
        if(!holds_alternative<string>(messageContent)) {
            throw InternalErrorException(
                "Expected string in MessageContent, but got " + string(typeid(messageContent).name())
                );
        }

        // We append the incoming data to the buffer.
        appendNewContent(get<string>(messageContent));

        // We check the contents of the buffer for a complete messages.
        const vector<string> completeMessages = tryToExtractCompletedMessages();

        // If we have a complete message, we tokenize it
        if(!completeMessages.empty()) {
            try {
                ParsedMessage parsed = tokenizeMessage(completeMessages.front());
                return parsed;
            }
            catch(...) {
                return nullopt;
            }
        }
        // Else no complete messages are available yet
        else {
            return nullopt;
        }
    } // TcpMessageParser::parseIncomingMessage

    void TcpMessageParser::appendNewContent(const string &newContent) {
        mBuffer.append(newContent);
    } // TcpMessageParser::appendData

    vector<string> TcpMessageParser::tryToExtractCompletedMessages() {
        // Find the first delimiter
        size_t delimiterPosition{mBuffer.find(END_OF_MESSAGE_DELIMITER)};

        // Process the buffer while delimiters are found (i.e., while there are complete messages)
        vector<string> completeMessages;
        while(delimiterPosition != string::npos) {
            // Add the complete message to the vector
            completeMessages.emplace_back(mBuffer.substr(0, delimiterPosition));

            // Remove the processed part of the buffer, including the delimiter
            mBuffer = mBuffer.substr(delimiterPosition + string(END_OF_MESSAGE_DELIMITER).length());

            // Find the next delimiter (if multiple complete messages are in the buffer)
            delimiterPosition = mBuffer.find(END_OF_MESSAGE_DELIMITER);
        }
        return completeMessages;
    } // TcpMessageParser::tryToExtractCompletedMessages

    ParsedMessage TcpMessageParser::tokenizeMessage(const string &message) {
        // We get a first token, which represents the command
        const size_t firstDelimiterPosition = message.find(TOKEN_DELIMITER);
        if(firstDelimiterPosition == string::npos) {
            logger("Client received a malformed message from the server: missing any delimiter");
            ClientOutput::printClientInternalError(
                    "Client received a malformed message from the server. The client will try "
                    "to send an error message to the server and will gracefully terminate if possible."
                    );
            throw ProtocolErrorException(
                    "Client received a malformed message from the server: message is incomplete"
                    );
        }
        const string messageTypeToken = message.substr(0, firstDelimiterPosition);

        // ABNF strings are case-insensitive, and the character set for these
        // strings is US-ASCII. (Source: RFC 5234)
        const auto messageType = CastUtils::castStringToEnum<MessageType>(StringUtils::toLower(messageTypeToken));

        // We split the message using 'splitIntoFixedCount()' depanding on the message type
        ParsedMessage parsedMessage{};
        switch(messageType) {
            case MessageType::AUTH: {
                // Expecting 6 tokens: AUTH {Username} AS {DisplayName} USING {Secret}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         ClientLimits::TCP_EXPECTED_AUTH_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::AUTH;
                break;
            }
            case MessageType::JOIN: {
                // Expecting 4 tokens: JOIN {ChannelID} AS {DisplayName}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         ClientLimits::TCP_EXPECTED_JOIN_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::JOIN;
                break;
            }
            case MessageType::MSG: {
                // Expecting 5 tokens: MSG FROM {DisplayName} IS {MessageContent}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         ClientLimits::TCP_EXPECTED_MSG_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::MSG;
                break;
            }
            case MessageType::ERR: {
                // Expecting 5 tokens: ERR FROM {DisplayName} IS {MessageContent}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         ClientLimits::TCP_EXPECTED_ERR_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::ERR;
                break;
            }
            case MessageType::BYE: {
                // Expecting 3 tokens: BYE FROM {DisplayName}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         ClientLimits::TCP_EXPECTED_BYE_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::BYE;
                break;
            }
            case MessageType::REPLY: {
                // Expecting 4 tokens: REPLY {OK|NOK} IS {MessageContent}
                parsedMessage.mFields = StringUtils::splitIntoFixedCount(message, TOKEN_DELIMITER,
                                                                         ClientLimits::TCP_EXPECTED_REPLY_MESSAGE_FIELDS);
                parsedMessage.mType = MessageType::REPLY;
                break;
            }
            default: {
                logger("Client received a malformed message from the server: unknown message type");
                ClientOutput::printClientInternalError(
                        "Client received a malformed message from the server. The client will try "
                        "to send an error message to the server and will gracefully terminate if possible."
                        );
                throw ProtocolErrorException(
                        "Client received a malformed message from the server: unknown message type"
                        );
            }
        } // switch(commandTokenType)

        return parsedMessage;  // We return the tokenized (parsed) message
    } // TcpMessageParser::tokenizeMessage
} // IPK25ChatClient::Messaging::Parser

/*** end of file TCPMessageParser.cpp ***/
