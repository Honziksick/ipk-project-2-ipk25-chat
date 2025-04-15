/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessageBuilder.cpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the `TcpMessageBuilder` class, which  *
 *               provides static methods for constructing various types of     *
 *               messages used in the IPK25 Chat Client.                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageBuilder.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `TcpMessageBuilder` class for building chat
 *        messages.
 */

#include "Messaging/MessageBuilder/TCPMessageBuilder.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>   // std::string
#include <sstream>  // std::ostringstream

using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Messaging
{
    MessageContent TcpMessageBuilder::buildMessage(MessageType messageType, uint16_t refMessageId) {
        throw InternalErrorException("buildMessage() is not supported for TcpMessageBuilder.");
    } // TcpMessageBuilder::buildMessage

    MessageContent TcpMessageBuilder::buildAuthMessage(const string &username, const string &displayName, const string &secret) {
        logger("username=%s, displayName=%s, secret=%s", username.c_str(), displayName.c_str(), secret.c_str());

        // Construct the message
        ostringstream message;
        message << "AUTH " << username << " AS " << displayName << " USING " << secret << "\r\n";

        logger("message=%s", message.str().c_str());
        return MessageContent{message.str()};
    } // TcpMessageBuilder::buildAuthMessage

    MessageContent TcpMessageBuilder::buildJoinMessage(const string &channelId, const string &displayName) {
        logger("channelId=%s, displayName=%s", channelId.c_str(), displayName.c_str());

        // Construct the message
        ostringstream message;
        message << "JOIN " << channelId << " AS " << displayName << "\r\n";

        logger("message=%s", message.str().c_str());
        return MessageContent{message.str()};
    } // TcpMessageBuilder::buildJoinMessage

    MessageContent TcpMessageBuilder::buildMsgMessage(const string &displayName, const string &messageContent) {
        logger("displayName=%s, messageContent=%s", displayName.c_str(), messageContent.c_str());

        // Construct the message
        ostringstream message;
        message << "MSG FROM " << displayName << " IS " << messageContent << "\r\n";

        logger("message=%s", message.str().c_str());
        return MessageContent{message.str()};
    } // TcpMessageBuilder::buildMsgMessage

    MessageContent TcpMessageBuilder::buildErrMessage(const string &displayName, const string &messageContent) {
        logger("displayName=%s, messageContent=%s", displayName.c_str(), messageContent.c_str());

        // Construct the message
        ostringstream message;
        message << "ERR FROM " << displayName << " IS " << messageContent << "\r\n";

        return MessageContent{message.str()};
    } // TcpMessageBuilder::buildErrMessage

    MessageContent TcpMessageBuilder::buildByeMessage(const string &displayName) {
        logger("displayName=%s", displayName.c_str());

        // Construct the message
        ostringstream message;
        message << "BYE FROM " << displayName << "\r\n";

        logger("message=%s", message.str().c_str());
        return MessageContent{message.str()};
    } // TcpMessageBuilder::buildByeMessage
} // IPK25ChatClient::Messaging

/*** end of file TCPMessageBuilder.cpp ***/
