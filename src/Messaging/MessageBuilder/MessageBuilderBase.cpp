/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageBuilderBase.cpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the base class `MessageBuilderBase` for     *
 *               constructing various types of messages used in the IPK25      *
 *               Chat Client.                                                  *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageBuilderBase.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `MessageBuilderBase` class, an base class
 *        for constructing specific types of messages in the IPK25 Chat Client.
 */

#include "Messaging/Interfaces/IMessageBuilder.hpp"
#include "Messaging/MessageBuilder/MessageBuilderBase.hpp"
#include "Common/ChatDataTypes.hpp"
#include "Common/UserCommand.hpp"
#include "Enums/MessageTypes.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"

using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;

namespace IPK25ChatClient::Messaging
{
    MessageBuilderBase::MessageBuilderBase() : IMessageBuilder() {}

    MessageContent MessageBuilderBase::buildMessage(const MessageType messageType, const UserCommand &messageContent) {
        // Build the message based on the type
        switch(messageType) {
            case MessageType::AUTH:
                logger("Going to build AUTH message");
                return buildAuthMessage(messageContent.mUsername, messageContent.mDisplayName, messageContent.mSecret);

            case MessageType::JOIN:
                logger("Going to build JOIN message");
                return buildJoinMessage(messageContent.mChannelId, messageContent.mDisplayName);

            case MessageType::MSG:
                logger("Going to build MSG message");
                return buildMsgMessage(messageContent.mDisplayName, messageContent.mMessageContent);

            case MessageType::ERR:
                logger("Going to build ERR message");
                return buildErrMessage(messageContent.mDisplayName, messageContent.mMessageContent);

            case MessageType::BYE:
                logger("Going to build BYE message");
                return buildByeMessage(messageContent.mDisplayName);

            default:
                logger("Invalid message type passed: %s", CastUtils::castEnumToString(messageType).c_str());
                throw InternalErrorException(
                        "buildMessage() error: Invalid message type passed: " +
                        CastUtils::castEnumToString(messageType)
                        );
        } // switch(messageType)
    } // MessageBuilderBase::buildMessage
} // IPK25ChatClient::Messaging

/*** end of file MessageBuilderBase.cpp ***/
