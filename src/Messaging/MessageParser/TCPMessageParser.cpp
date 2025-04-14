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
 * Last edit:    14.04.2025                                                    *
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
using namespace IPK25ChatClient::Utilities;
using namespace IPK25ChatClient::Exceptions;
using namespace std;

namespace IPK25ChatClient::Messaging
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
        // We split
        const vector<string> tokens = StringUtils::splitBySpaces(message);

        if(tokens.empty()) {
            ClientOutput::printClientInternalError(
                    "Client failed to proccess incoming message. We appologize for the inconvenience."
                    );
            return ParsedMessage{};
        }

        // První token se interpretuje jako typ zprávy.
        ParsedMessage parsedMessage{};
        try {
            // ABNF strings are case insensitive and the character set for these
            // strings is US-ASCII. (Source: RFC 5234)
            parsedMessage.mType = CastUtils::castStringToEnum<MessageType>(StringUtils::toLower(tokens[0]));
        }
        catch(...) {
            parsedMessage.mType = MessageType::UNKNOWN;
        }

        // The remaining tokens are interpreted as fields of the message.
        for(int iToken = 1; iToken < tokens.size(); iToken++) {
            if(!tokens[iToken].empty()) {
                parsedMessage.mFields.emplace_back(tokens[iToken]);
            }
        }

        return parsedMessage;
    } // TcpMessageParser::tokenizeMessage
} // IPK25ChatClient::Messaging

/*** end of file TCPMessageParser.cpp ***/
