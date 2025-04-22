/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessageValidator.cpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `UdpMessageValidator` class, which      *
 *               implements validation logic for UDP messages in the IPK25     *
 *               Chat Client application.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessageValidator.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `UdpMessageValidator` class for validating
 *        UDP messages in the IPK25 Chat Client application.
 */

#include "Validators/UDPMessageValidator.hpp"
#include "Common/ParsedMessage.hpp"
#include "Enums/ValidatorResults.hpp"
#include "Constants/MessageFields.hpp"
#include "Constants/MessageKeywords.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>  // std::string

using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Validators
{
    ValidatorResult UdpMessageValidator::validateMessage(const ParsedMessage &parsedMessage) {
        logger("Validating UDP message. Type: %s, Fields count: %zu",
               CastUtils::castEnumToString(parsedMessage.mType).c_str(), parsedMessage.mFields.size());

        // Perform the validation based on message type
        switch(parsedMessage.mType) {
            case MessageType::AUTH:
                return validateAuthMessage(parsedMessage);
            case MessageType::JOIN:
                return validateJoinMessage(parsedMessage);
            case MessageType::MSG:
                return validateMsgMessage(parsedMessage);
            case MessageType::ERR:
                return validateErrMessage(parsedMessage);
            case MessageType::BYE:
                return validateByeMessage(parsedMessage);
            case MessageType::REPLY:
                return validateReplyMessage(parsedMessage);
            default:
                throw InternalErrorException(
                        "validateMessage() error: Invalid message parameter type "
                        "passed: " + CastUtils::castEnumToString(parsedMessage.mType),
                        ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                        );
        } // switch(parsedMessage.mType)
    } // UdpMessageValidator::validateMessage

    // AUTH message structure: Header + {Username}/1 {DisplayName}/2 {Secret}/3
    ValidatorResult UdpMessageValidator::validateAuthMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::UDP_EXPECTED_AUTH_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) {Username}
        if(!mapValidatorResultToBool(validateUsername(parsedMessage.mFields[MessageFields::UDP_AUTH_USERNAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 2) {DisplayName}
        if(!mapValidatorResultToBool(validateUsername(parsedMessage.mFields[MessageFields::UDP_AUTH_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 3) {Secret}
        if(!mapValidatorResultToBool(validateUsername(parsedMessage.mFields[MessageFields::UDP_AUTH_SECRET_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // UdpMessageValidator::validateAuthMessage

    // JOIN message structure: Header + {ChannelID}/1 {DisplayName}/2
    ValidatorResult UdpMessageValidator::validateJoinMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::UDP_EXPECTED_JOIN_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) {ChannelID}
        if(!mapValidatorResultToBool(validateChannelId(parsedMessage.mFields[MessageFields::UDP_JOIN_CHANNEL_ID_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 2) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::UDP_JOIN_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // UdpMessageValidator::validateJoinMessage

    // ERR message structure: Header + {DisplayName}/1 {MessageContent}/2
    ValidatorResult UdpMessageValidator::validateErrMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::UDP_EXPECTED_ERR_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::UDP_ERR_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 2) {MessageContent}
        if(!mapValidatorResultToBool(validateMessageContent(parsedMessage.mFields[MessageFields::UDP_ERR_MESSAGE_CONTENT_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // UdpMessageValidator::validateErrMessage

    // BYE message structure: Header + {DisplayName}/1
    ValidatorResult UdpMessageValidator::validateByeMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::UDP_EXPECTED_BYE_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::UDP_BYE_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // UdpMessageValidator::validateByeMessage

    // REPLY message structure: Header + {"OK"|"NOK"}/1 {MessageContent}/2
    ValidatorResult UdpMessageValidator::validateReplyMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::UDP_EXPECTED_REPLY_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) {"OK"|"NOK"}
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::UDP_REPLY_RESULT_KEYWORD_INDEX], MessageKeywordsLowerCase::OK_LC) &&
            !StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::UDP_REPLY_RESULT_KEYWORD_INDEX], MessageKeywordsLowerCase::NOK_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) {MessageContent}
        if(!mapValidatorResultToBool(validateMessageContent(parsedMessage.mFields[MessageFields::UDP_REPLY_MESSAGE_CONTENT_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // UdpMessageValidator::validateReplyMessage

    // MSG message structure: Header + {DisplayName}/1 {MessageContent}/2
    ValidatorResult UdpMessageValidator::validateMsgMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::UDP_EXPECTED_MSG_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::UDP_MSG_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 2) {MessageContent}
        if(!mapValidatorResultToBool(validateMessageContent(parsedMessage.mFields[MessageFields::UDP_MSG_MESSAGE_CONTENT_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // UdpMessageValidator::validateMsgMessage
} // IPK25ChatClient::Validators

/*** end of file UDPMessageValidator.cpp ***/
