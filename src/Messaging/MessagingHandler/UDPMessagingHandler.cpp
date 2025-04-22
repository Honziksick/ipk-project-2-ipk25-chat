/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessagingHandler.cpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      18.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `UdpMessagingHandler` class, which      *
 *               handles UDP-based messaging operations in the IPK25 Chat      *
 *               Client.                                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessagingHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `UdpMessagingHandler` class for handling
 *        UDP-based messaging.
 */

#include "Messaging/MessagingHandler/UDPMessagingHandler.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Common/ParsedMessage.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Constants/MessageFields.hpp"
#include "Enums/MessageTypes.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>  // std::string

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Messaging::Handler
{
    void UdpMessagingHandler::displayIncomingMessage(const ParsedMessage &parsedMessage) {
        logger("displayIncomingMessage() called with message type: %s", CastUtils::castEnumToString(parsedMessage.mType).c_str());

        // React appropriately to received message
        switch(parsedMessage.mType) {
            case MessageType::REPLY:
                logger("Displaying server /reply message.");
                ClientOutput::printClientReply(parsedMessage.mFields[MessageFields::UDP_REPLY_RESULT_KEYWORD_INDEX],
                                               parsedMessage.mFields[MessageFields::UDP_REPLY_MESSAGE_CONTENT_INDEX]);
                break;
            case MessageType::MSG:
                logger("Displaying server /msg message.");
                ClientOutput::printClientIncomingMessage(parsedMessage.mFields[MessageFields::UDP_MSG_DISPLAY_NAME_INDEX],
                                                         parsedMessage.mFields[MessageFields::UDP_MSG_MESSAGE_CONTENT_INDEX]);
                break;
            case MessageType::ERR:
                logger("Displaying server /err message.");
                ClientOutput::printClientIncomingError(parsedMessage.mFields[MessageFields::UDP_ERR_DISPLAY_NAME_INDEX],
                                                       parsedMessage.mFields[MessageFields::UDP_ERR_MESSAGE_CONTENT_INDEX]);
                break;
            case MessageType::BYE:
            case MessageType::PING:
            case MessageType::CONFIRM:
                logger("Displaying server message type: %s", CastUtils::castEnumToString(parsedMessage.mType).c_str());
                break;
            default:
                logger("Unrecognized message type: %s", CastUtils::castEnumToString(parsedMessage.mType).c_str());
                throw InternalErrorException(
                        "displayIncomingMessage(): trying to proccess unsupported message type: " +
                        CastUtils::castEnumToString(parsedMessage.mType),
                        ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                        );
        } // switch(parsedMessage.mType)

        logger("displayIncomingMessage() completed successfully");
    } // UdpMessagingHandler::processIncomingMessage
} // IPK25ChatClient::Messaging::Handler

/*** end of file UDPMessagingHandler.cpp ***/
