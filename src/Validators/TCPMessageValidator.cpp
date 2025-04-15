/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessageValidator.cpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `TcpMessageValidator` class, which      *
 *               implements validation logic for TCP messages in the IPK25     *
 *               Chat Client application.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessageValidator.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `TcpMessageValidator` class for validating
 *        TCP messages in the IPK25 Chat Client application.
 */

#include "Validators/TCPMessageValidator.hpp"
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
    ValidatorResult TcpMessageValidator::validateMessage(const ParsedMessage &parsedMessage) {
        logger("Validating TCP message. Type: %s, Fields count: %zu",
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
                        "passed: " + CastUtils::castEnumToString(parsedMessage.mType)
                        );
        } // switch(parsedMessage.mType)
    } // TcpMessageValidator::validateMessage

    bool TcpMessageValidator::mapValidatorResultToBool(const ValidatorResult partialResult) {
        switch(partialResult) {
            case ValidatorResult::OK:
                logger("Message and its message parameters validation SUCCEDDED: result: %s",
                       CastUtils::castEnumToString(partialResult).c_str());
                return true;
            default:
                logger("Message and its message parameters FAILED, mapping to ValidatorResult::INVALID: "
                       "result: %s", CastUtils::castEnumToString(partialResult).c_str());
                return false;
        } // switch(partialResult)
    } // TcpMessageValidator::resolvePartialValidatorResult

    // AUTH message structure: AUTH/0 {Username}/1 AS/2 {DisplayName}/3 USING/4 {Secret}/5
    ValidatorResult TcpMessageValidator::validateAuthMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::TCP_EXPECTED_AUTH_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) "AUTH"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_AUTH_TYPE_INDEX], MessageKeywordsLowerCase::AUTH_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) {Username}
        if(!mapValidatorResultToBool(validateUsername(parsedMessage.mFields[MessageFields::TCP_AUTH_USERNAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 3) "AS"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_AUTH_AS_KEYWORD_INDEX], MessageKeywordsLowerCase::AS_LC)) {
            return ValidatorResult::INVALID;
        }
        // 4) {DisplayName}
        if(!mapValidatorResultToBool(validateUsername(parsedMessage.mFields[MessageFields::TCP_AUTH_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 5) "USING"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_AUTH_USING_KEYWORD_INDEX], MessageKeywordsLowerCase::USING_LC)) {
            return ValidatorResult::INVALID;
        }
        // 6) {Secret}
        if(!mapValidatorResultToBool(validateUsername(parsedMessage.mFields[MessageFields::TCP_AUTH_SECRET_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // TcpMessageValidator::validateAuthMessage

    // JOIN message structure: JOIN {ChannelID} AS {DisplayName}
    ValidatorResult TcpMessageValidator::validateJoinMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::TCP_EXPECTED_JOIN_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) "JOIN"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_JOIN_TYPE_INDEX], MessageKeywordsLowerCase::JOIN_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) {ChannelID}
        if(!mapValidatorResultToBool(validateChannelId(parsedMessage.mFields[MessageFields::TCP_JOIN_CHANNEL_ID_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 3) "AS"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_JOIN_AS_KEYWORD_INDEX], MessageKeywordsLowerCase::AS_LC)) {
            return ValidatorResult::INVALID;
        }
        // 4) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::TCP_JOIN_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // TcpMessageValidator::validateJoinMessage

    // ERR message structure: ERR FROM {DisplayName} IS {MessageContent}
    ValidatorResult TcpMessageValidator::validateErrMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::TCP_EXPECTED_ERR_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) "ERR"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_ERR_TYPE_INDEX], MessageKeywordsLowerCase::ERR_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) "FROM"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_ERR_FROM_KEYWORD_INDEX], MessageKeywordsLowerCase::FROM_LC)) {
            return ValidatorResult::INVALID;
        }
        // 3) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::TCP_ERR_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 4) "IS"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_ERR_IS_KEYWORD_INDEX], MessageKeywordsLowerCase::IS_LC)) {
            return ValidatorResult::INVALID;
        }
        // 5) {MessageContent}
        if(!mapValidatorResultToBool(validateMessageContent(parsedMessage.mFields[MessageFields::TCP_ERR_MESSAGE_CONTENT_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // TcpMessageValidator::validateErrMessage

    // BYE message structure: BYE FROM {DisplayName}
    ValidatorResult TcpMessageValidator::validateByeMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::TCP_EXPECTED_BYE_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) "BYE"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_BYE_TYPE_INDEX], MessageKeywordsLowerCase::BYE_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) "FROM"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_BYE_FROM_KEYWORD_INDEX], MessageKeywordsLowerCase::FROM_LC)) {
            return ValidatorResult::INVALID;
        }
        // 3) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::TCP_BYE_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // TcpMessageValidator::validateByeMessage

    // REPLY message structure: REPLY {"OK"|"NOK"} IS {MessageContent}
    ValidatorResult TcpMessageValidator::validateReplyMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::TCP_EXPECTED_REPLY_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) "REPLY"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_REPLY_TYPE_INDEX], MessageKeywordsLowerCase::REPLY_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) {"OK"|"NOK"}
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_REPLY_RESULT_KEYWORD_INDEX], MessageKeywordsLowerCase::OK_LC) &&
           !StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_REPLY_RESULT_KEYWORD_INDEX], MessageKeywordsLowerCase::NOK_LC)) {
            return ValidatorResult::INVALID;
        }
        // 3) "IS"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_REPLY_IS_KEYWORD_INDEX], MessageKeywordsLowerCase::IS_LC)) {
            return ValidatorResult::INVALID;
        }
        // 4) {MessageContent}
        if(!mapValidatorResultToBool(validateMessageContent(parsedMessage.mFields[MessageFields::TCP_REPLY_MESSAGE_CONTENT_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // TcpMessageValidator::validateReplyMessage

    // MSG message structure: MSG FROM {DisplayName} IS {MessageContent}
    ValidatorResult TcpMessageValidator::validateMsgMessage(const ParsedMessage &parsedMessage) {
        // Check if the message has the expected number of fields
        if(parsedMessage.mFields.size() != MessageFields::TCP_EXPECTED_MSG_MESSAGE_FIELDS) {
            return ValidatorResult::INVALID;
        }
        // 1) "MSG"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_MSG_TYPE_INDEX], MessageKeywordsLowerCase::MSG_LC)) {
            return ValidatorResult::INVALID;
        }
        // 2) "FROM"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_MSG_FROM_KEYWORD_INDEX], MessageKeywordsLowerCase::FROM_LC)) {
            return ValidatorResult::INVALID;
        }
        // 3) {DisplayName}
        if(!mapValidatorResultToBool(validateDisplayName(parsedMessage.mFields[MessageFields::TCP_MSG_DISPLAY_NAME_INDEX]))) {
            return ValidatorResult::INVALID;
        }
        // 4) "IS"
        if(!StringUtils::compareKeywordsCaseInsesitive(parsedMessage.mFields[MessageFields::TCP_MSG_IS_KEYWORD_INDEX], MessageKeywordsLowerCase::IS_LC)) {
            return ValidatorResult::INVALID;
        }
        // 5) {MessageContent}
        if(!mapValidatorResultToBool(validateMessageContent(parsedMessage.mFields[MessageFields::TCP_MSG_MESSAGE_CONTENT_INDEX]))) {
            return ValidatorResult::INVALID;
        }

        // If all checks passed, return OK
        return ValidatorResult::OK;
    } // TcpMessageValidator::validateMsgMessage
} // IPK25ChatClient::Validators

/*** end of file TCPMessageValidator.cpp ***/
