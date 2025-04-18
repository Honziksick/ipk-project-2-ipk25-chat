/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessagingHandler.cpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `TcpMessagingHandler` class, which      *
 *               handles TCP-based messaging operations in the IPK25 Chat      *
 *               Client.                                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessagingHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `TcpMessagingHandler` class for handling
 *        TCP-based messaging.
 */

#include "Messaging/MessagingHandler/TCPMessagingHandler.hpp"
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
    void TcpMessagingHandler::processIncomingMessage(const ParsedMessage &parsedMessage) {
        logger("processIncomingMessage() called with message type: %s", CastUtils::castEnumToString(parsedMessage.mType).c_str());

        // React appropriately to received message
        switch(parsedMessage.mType) {
            case MessageType::REPLY:
                ClientOutput::printClientReply(parsedMessage.mFields[MessageFields::TCP_REPLY_RESULT_KEYWORD_INDEX],
                                               parsedMessage.mFields[MessageFields::TCP_REPLY_MESSAGE_CONTENT_INDEX]);
                break;
            case MessageType::MSG:
                ClientOutput::printClientIncomingMessage(parsedMessage.mFields[MessageFields::TCP_MSG_DISPLAY_NAME_INDEX],
                                                         parsedMessage.mFields[MessageFields::TCP_MSG_MESSAGE_CONTENT_INDEX]);
                break;
            case MessageType::ERR:
                ClientOutput::printClientIncomingError(parsedMessage.mFields[MessageFields::TCP_ERR_DISPLAY_NAME_INDEX],
                                                       parsedMessage.mFields[MessageFields::TCP_ERR_MESSAGE_CONTENT_INDEX]);
                break;
            case MessageType::BYE:
                break;
            default:
                logger("Unrecognized message type: %s", CastUtils::castEnumToString(parsedMessage.mType).c_str());
                throw InternalErrorException(
                        "processIncomingMessage(): trying to proccess unsupported message type: " +
                        CastUtils::castEnumToString(parsedMessage.mType), ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                        );
        } // switch(parsedMessage.mType)

        logger("processIncomingMessage() completed successfully");
    } // TcpMessagingHandler::processIncomingMessage
} // IPK25ChatClient::Messaging::Handler

/*** end of file TCPMessagingHandler.cpp ***/
