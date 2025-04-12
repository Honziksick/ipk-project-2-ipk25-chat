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
 * Last edit:    11.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the `TcpMessageBuilder` class, which  *
 *               provides static methods for constructing various types of     *
 *               messages used in the IPK25 Chat Client.                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageBuilder.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implements the `TcpMessageBuilder` class for building chat messages.
 */

#include "TCPMessageBuilder.hpp"
#include "Utilities/Logger.hpp"
#include <string>   // std::string
#include <sstream>  // std::ostringstream

using namespace std;

namespace IPK25ChatClient::Messaging
{
    string TcpMessageBuilder::buildAuthMessage(const string &username, const string &displayName, const string &secret) {
        logger("username=%s, displayName=%s, secret=%s", username.c_str(), displayName.c_str(), secret.c_str());

        // Construct the message
        ostringstream message;
        message << "AUTH " << username << " AS " << displayName << " USING " << secret << "\r\n";

        logger("message=%s", message.str().c_str());
        return message.str();
    } // TcpMessageBuilder::buildAuthMessage

    string TcpMessageBuilder::buildJoinMessage(const string &channelId, const string &displayName) {
        logger("channelId=%s, displayName=%s", channelId.c_str(), displayName.c_str());

        // Construct the message
        ostringstream message;
        message << "JOIN " << channelId << " AS " << displayName << "\r\n";

        logger("message=%s", message.str().c_str());
        return message.str();
    } // TcpMessageBuilder::buildJoinMessage

    string TcpMessageBuilder::buildMsgMessage(const string &displayName, const string &messageContent) {
        logger("displayName=%s, messageContent=%s", displayName.c_str(), messageContent.c_str());

        // Construct the message
        ostringstream message;
        message << "MSG FROM " << displayName << " IS " << messageContent << "\r\n";

        logger("message=%s", message.str().c_str());
        return message.str();
    } // TcpMessageBuilder::buildMsgMessage

    string TcpMessageBuilder::buildErrMessage(const string &displayName, const string &messageContent) {
        logger("displayName=%s, messageContent=%s", displayName.c_str(), messageContent.c_str());

        // Construct the message
        ostringstream message;
        message << "ERR FROM " << displayName << " IS " << messageContent << "\r\n";

        return message.str();
    } // TcpMessageBuilder::buildErrMessage

    string TcpMessageBuilder::buildByeMessage(const string &displayName) {
        logger("displayName=%s", displayName.c_str());

        // Construct the message
        ostringstream message;
        message << "BYE FROM " << displayName << "\r\n";

        logger("message=%s", message.str().c_str());
        return message.str();
    } // TcpMessageBuilder::buildByeMessage

    string TcpMessageBuilder::buildReplyMessage(const string &messageContent, const bool success) {
        logger("messageContent=%s, success=%s", messageContent.c_str(), success ? "true" : "false");

        // Construct the message
        ostringstream message;
        message << "REPLY " << (success ? "OK" : "NOK") << " IS " << messageContent << "\r\n";

        logger("message=%s", message.str().c_str());
        return message.str();
    } // TcpMessageBuilder::buildReplyMessage
} // IPK25ChatClient::Messaging

/*** end of file TCPMessageBuilder.cpp ***/
