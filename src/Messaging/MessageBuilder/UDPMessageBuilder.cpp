/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessageBuilder.cpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the `UdpMessageBuilder` class,        *
 *               which provides methods for constructing various types         *
 *               of UDP messages in the IPK25 Chat Client project.             *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessageBuilder.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implements the `UdpMessageBuilder` class for building UDP messages.
 */

#include "Messaging/Interfaces/IMessageBuilder.hpp"
#include "Messaging/MessageBuilder/UDPMessageBuilder.hpp"
#include "Messaging/MessageBuilder/MessageIdProvider.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Enums/MessageTypes.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>       // std::string
#include <vector>       // std::vector
#include <memory>       // std::make_unique
#include <arpa/inet.h>  // htons()

using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Messaging::Builder
{
    UdpMessageBuilder::UdpMessageBuilder() : mMessageIdProvider{make_unique<MessageIdProvider>()} {}

    MessageContent UdpMessageBuilder::buildMessage(const MessageType messageType, const uint16_t refMessageId) {
        // Build the message based on the type (special overload for CONFIRM message)
        switch(messageType) {
            case MessageType::CONFIRM:
                logger("Going to build CONFIRM message");
                return buildConfirmMessage(refMessageId);

            default:
                logger("Invalid message type passed: %s", CastUtils::castEnumToString(messageType).c_str());
                throw InternalErrorException(
                        "buildMessage() error for UDP: Invalid message type "
                        "passed: " + CastUtils::castEnumToString(messageType),
                        ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                        );
        }
    } // UdpMessageBuilder::buildMessage

    void UdpMessageBuilder::appendZeroTerminatedContent(vector<uint8_t> &currentMessageContent, const string &contentToAppend) {
        logger("Appending a messahe parameter with zero termination, called with contentToAppend=%s", contentToAppend.c_str());
        currentMessageContent.insert(currentMessageContent.end(), contentToAppend.begin(), contentToAppend.end());
        currentMessageContent.emplace_back(0);
    } // UdpMessageBuilder::appendZeroTerminatedContent

    void UdpMessageBuilder::appendMessageIdAsNetworkByteOrder(vector<uint8_t> &currentMessageContent) const {
        logger("Converting MessageId to network byte order");

        const uint16_t messageId = mMessageIdProvider->getNextMessageId();
        logger("Next message ID: %u", messageId);
        const uint16_t networkByteOrder = htons(messageId); // Convert to network byte order (short)

        // Extraction and insertion of the 1st byte
        const uint16_t shiftedOrder = networkByteOrder >> 8;     // 1) First we shift the value 8 bits right:
                                                                 //       Before: XXXXXXXX YYYYYYYY
                                                                 //       After:  00000000 XXXXXXXX
        auto firstByte = static_cast<uint8_t>(shiftedOrder);     // 2) Then we select only the lower 8 bits: XXXXXXXX
        currentMessageContent.emplace_back(firstByte);           // 3) Finally, we insert the first byte into the vector


        // Extraction and insertion of the 2nd byte
        const uint16_t maskedOrder = networkByteOrder & 0x00FF;  // 1) First we apply a mask to isolate the lower 8 bits
                                                                 //       Before: XXXXXXXX YYYYYYYY
                                                                 //       After:  00000000 YYYYYYYY
        auto secondByte = static_cast<uint8_t>(maskedOrder);     // 2) Then we select only the lower 8 bits: YYYYYYYY
        currentMessageContent.emplace_back(secondByte);          // 3) Finally, we insert the second byte into the vector

        logger("Message ID appended as network byte order: %u", messageId);
    } // UdpMessageBuilder::appendMessageIdAsNetworkByteOrder

    void UdpMessageBuilder::appendRefMessageIdAsNetworkByteOrder(vector<uint8_t> &currentMessageContent, const uint16_t refMessageId) {
        logger("Converting RefMessageId to network byte order, called with refMessageId=%u", refMessageId);
        const uint16_t networkByteOrder = htons(refMessageId); // Convert to network byte order (short)

        // Extraction and insertion of the 1st byte
        currentMessageContent.emplace_back(static_cast<uint8_t>(networkByteOrder >> 8));

        // Extraction and insertion of the 2nd byte
        currentMessageContent.emplace_back(static_cast<uint8_t>(networkByteOrder & 0x00FF));

        logger("Reference Message ID appended as network byte order: %u", refMessageId);
    } // UdpMessageBuilder::appendMessageIdAsNetworkByteOrder

    MessageContent UdpMessageBuilder::buildAuthMessage(const string &username, const string &displayName, const string &secret) {
        logger("buildAuthMessage called with username=%s, displayName=%s, secret=%s", username.c_str(), displayName.c_str(),
               secret.c_str());

        vector<uint8_t> message;
        message.emplace_back(CastUtils::castEnumToByte(MessageType::AUTH));
        appendMessageIdAsNetworkByteOrder(message);
        appendZeroTerminatedContent(message, username);
        appendZeroTerminatedContent(message, displayName);
        appendZeroTerminatedContent(message, secret);

        logger("Auth message built with size=%zu", message.size());
        return MessageContent{message};
    } // UdpMessageBuilder::buildAuthMessage

    MessageContent UdpMessageBuilder::buildJoinMessage(const string &channelId, const string &displayName) {
        logger("buildJoinMessage called with channelId=%s, displayName=%s", channelId.c_str(), displayName.c_str());

        vector<uint8_t> message;
        message.emplace_back(CastUtils::castEnumToByte(MessageType::JOIN));
        appendMessageIdAsNetworkByteOrder(message);
        appendZeroTerminatedContent(message, channelId);
        appendZeroTerminatedContent(message, displayName);

        logger("Join message built with size=%zu", message.size());
        return MessageContent{message};
    } // UdpMessageBuilder::buildJoinMessage

    MessageContent UdpMessageBuilder::buildMsgMessage(const string &displayName, const string &messageContent) {
        logger("buildMsgMessage called with displayName=%s, messageContent=%s", displayName.c_str(), messageContent.c_str());

        vector<uint8_t> message;
        message.emplace_back(CastUtils::castEnumToByte(MessageType::MSG));
        appendMessageIdAsNetworkByteOrder(message);
        appendZeroTerminatedContent(message, displayName);
        appendZeroTerminatedContent(message, messageContent);

        logger("Msg message built with size=%zu", message.size());
        return MessageContent{message};
    } // UdpMessageBuilder::buildMsgMessage

    MessageContent UdpMessageBuilder::buildErrMessage(const string &displayName, const string &messageContent) {
        logger("buildErrMessage called with displayName=%s, messageContent=%s", displayName.c_str(), messageContent.c_str());

        vector<uint8_t> message;
        message.emplace_back(CastUtils::castEnumToByte(MessageType::ERR));
        appendMessageIdAsNetworkByteOrder(message);
        appendZeroTerminatedContent(message, displayName);
        appendZeroTerminatedContent(message, messageContent);

        logger("Err message built with size=%zu", message.size());
        return MessageContent{message};
    } // UdpMessageBuilder::buildErrMessage

    MessageContent UdpMessageBuilder::buildByeMessage(const string &displayName) {
        logger("buildByeMessage called with displayName=%s", displayName.c_str());

        vector<uint8_t> message;
        message.emplace_back(CastUtils::castEnumToByte(MessageType::BYE));
        appendMessageIdAsNetworkByteOrder(message);
        appendZeroTerminatedContent(message, displayName);

        logger("Bye message built with size=%zu", message.size());
        return MessageContent{message};
    } // UdpMessageBuilder::buildByeMessage

    MessageContent UdpMessageBuilder::buildConfirmMessage(const uint16_t refMessageId) {
        logger("buildConfirmMessage called with refMessageId=%u", refMessageId);

        vector<uint8_t> message;
        message.emplace_back(CastUtils::castEnumToByte(MessageType::CONFIRM));
        appendRefMessageIdAsNetworkByteOrder(message, refMessageId);

        logger("Confirm message built with size=%zu", message.size());
        return MessageContent{message};
    } // UdpMessageBuilder::buildConfirmMessage
} // IPK25ChatClient::Messaging::Builder

/*** end of file UDPMessageBuilder.cpp ***/
