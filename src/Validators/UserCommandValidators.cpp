/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UserCommandValidators.cpp                                     *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the                  *
 *               `UserCommandValidators` class, which provides methods for     *
 *               validating various message parameters used in the IPK25       *
 *               Chat Client application.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UserCommandValidators.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the class `UserCommandValidators` for message
 *         validation in the IPK25 Chat Client.
 */

#include "Validators/UserCommandValidators.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include "Constants/ClientLimits.hpp"
#include "Constants/RegexPatterns.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>       // std::string
#include <regex>        // std::regex, std::regex_match
#include <string_view>  // std::string_view

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Validators
{
    ValidatorResult UserCommandValidators::validateMessageParameter(const MessageParameter parameterType,
                                                                       const string_view commandParameter) {
        logger("Message parameter validation started: parameterType: %s, commandParameter: %s",
               CastUtils::castEnumToString(parameterType).c_str(), string(commandParameter).c_str());

        // Perform validation based on the parameter type
        auto result = ValidatorResult::UNKNOWN;
        switch(parameterType) {
            case MessageParameter::USERNAME:
                result = validateUsername(commandParameter);
                break;
            case MessageParameter::CHANNEL_ID:
                result = validateChannelId(commandParameter);
                break;
            case MessageParameter::SECRET:
                result = validateSecret(commandParameter);
                break;
            case MessageParameter::DISPLAY_NAME:
                result = validateDisplayName(commandParameter);
                break;
            case MessageParameter::MESSAGE_CONTENT:
                result = validateMessageContent(commandParameter);
                break;
            default:
                throw InternalErrorException(
                        "validateMessageParameter() error: Invalid message parameter "
                        "type passed: " + CastUtils::castEnumToString(parameterType)
                        );
        }

        // Check if the result is OK or may be interpreted as OK
        switch (result) {
            case ValidatorResult::OK:
                logger("Message parameter validation SUCCEDDED: parameterType: %s, "
                       "commandParameter: %s, result: %s", CastUtils::castEnumToString(parameterType).c_str(),
                       string(commandParameter).c_str(), CastUtils::castEnumToString(result).c_str());
                return ValidatorResult::OK;

            case ValidatorResult::PARAMETER_TOO_LONG:
                logger("Message parameter validation SUCCEDDED WITH TRUNCATION: parameterType: %s, "
                       "commandParameter: %s, result: %s", CastUtils::castEnumToString(parameterType).c_str(),
                       string(commandParameter).c_str(), CastUtils::castEnumToString(result).c_str());
                return ValidatorResult::PARAMETER_TOO_LONG;

            default:
                logger("Message parameter validation FAILED: parameterType: %s, commandParameter: %s, result: %s",
                       CastUtils::castEnumToString(parameterType).c_str(), string(commandParameter).c_str(),
                       CastUtils::castEnumToString(result).c_str());
                return ValidatorResult::INVALID;
        }
    } // UserCommandValidators::validateMessageParameter

    bool UserCommandValidators::postProccessValidation(const MessageParameter parameterType,
                                                       const ValidatorResult validationResult, string &commandParameter) {
        logger("Post-processing of the validation started: parameterType: %s, "
               "validationResult: %s, commandParameter: %s", CastUtils::castEnumToString(parameterType).c_str(),
               CastUtils::castEnumToString(validationResult).c_str(), string(commandParameter).c_str());

        // Perform post-processing based on the result
        switch(validationResult) {
            case ValidatorResult::OK:
                return true;
            case ValidatorResult::PARAMETER_TOO_LONG:
                return truncateMessageParameter(parameterType, commandParameter);
            case ValidatorResult::INVALID:
                return false;
            default:
                logger("Message parameter post-proccessing FAILED due to invalid result type: %s",
                       CastUtils::castEnumToString(validationResult).c_str());
                throw InternalErrorException(
                        "postProccessValidation() error: Invalid command validation result type "
                        "type passed: " + CastUtils::castEnumToString(validationResult)
                        );
        }
    } // UserCommandValidators::postProccessValidation

    bool UserCommandValidators::validateContainingOnlyAllowedSymbols(const string_view commandParameter, const bool whiteCharsAllowed) {
        logger("Deep validation called with commandParameter: %s", string(commandParameter).c_str());

        // Choose the correct regex
        regex allowedSymbolsRegex{};
        if(whiteCharsAllowed) {
            allowedSymbolsRegex = RegexPatterns::ALLOWED_SYMBOLS_WITH_WHITES_REGEX_PATTERN;
        }
        else {
            allowedSymbolsRegex = RegexPatterns::ALLOWED_SYMBOLS_REGEX_PATTERN;
        }

        // Validate whether the message parameter contains only allowed symbols
        bool isValid = true;
        if(!regex_match(commandParameter.begin(), commandParameter.end(), allowedSymbolsRegex)) {
            isValid = false;
        }

        // If the match failed, print an error message
        if(!isValid) {
            logger("Deep validation failed: parameter contains invalid symbols.");
            ClientOutput::printClientInternalError(
                    "Given message parameter '" + string(commandParameter) + "' contains invalid symbols. "
                    "Allowed symbols are: " + RegexPatterns::ALLOWED_SYMBOLS_REGEX_PATTERN
                    );
            return false;
        }

        logger("Deep validation passed: parameter contains only allowed symbols.");
        return true;
    } // UserCommandValidators::validateContainingOnlyAllowedSymbols

    bool UserCommandValidators::validateMinParameterLength(const string_view commandParameter, const unsigned int minLength) {
        logger("Deep validation called with commandParameter: %s, minLength: %u", string(commandParameter).c_str(), minLength);

        if(commandParameter.length() < minLength) {
            logger("Deep validation failed: parameter length is %zu, which is less than %u", commandParameter.length(), minLength);
            ClientOutput::printClientInternalError(
                    "Given message parameter '" + string(commandParameter) + "' has invalid length. Message "
                    "parameters must be between at least 1 characters long, but the given parameter is " +
                    to_string(commandParameter.length()) + "characters long."
                    );
            return false;
        }

        logger("Deep validation passed: parameter length is %zu", commandParameter.length());
        return true;
    } // UserCommandValidators::validateMinParameterLength

    bool UserCommandValidators::validateMaxParameterLength(const string_view commandParameter, const unsigned int maxLength) {
        logger("Deep validation called with commandParameter: %s, maxLength: %u", string(commandParameter).c_str(), maxLength);

        if(commandParameter.length() > maxLength) {
            logger("Deep alidation failed: parameter length is %zu, which exceeds %u", commandParameter.length(), maxLength);
            ClientOutput::printClientInternalError(
                    "Given message paramter '" + string(commandParameter) + "' is too long. This message parameter "
                    "can be at most " + to_string(maxLength) + "characters long, but given parameter is " +
                    to_string(commandParameter.length()) + "characters long." + "Given parameter will be truncated "
                    "to the maximum allowed length of " + to_string(maxLength) + "characters." +
                    "Truncated parameter: '" + string(commandParameter.substr(0, maxLength)) + "'."
                    );
            return false;
        }

        logger("Deep validation passed: parameter length is %zu", commandParameter.length());
        return true;
    } // UserCommandValidators::validateMaxParameterLength

    ValidatorResult UserCommandValidators::validateUsername(const string_view username) {
        logger("Validation of username: %s", string(username).c_str());

        static const regex cUsernameRegex(RegexPatterns::USERNAME_REGEX_PATTERN);
        if(!regex_match(username.begin(), username.end(), cUsernameRegex)) {
            logger("Username validation failed, performing deep validation.");
            return deepUsernameValidation(username);
        }

        logger("Username validation passed.");
        return ValidatorResult::OK;
    } // UserCommandValidators::validateUsername

    ValidatorResult UserCommandValidators::deepUsernameValidation(const string_view username) {
        if(!validateContainingOnlyAllowedSymbols(username)) {
            return ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS;
        }
        if(!validateMinParameterLength(username, ClientLimits::MIN_USERNAME_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_SHORT;
        }
        if(!validateMaxParameterLength(username, ClientLimits::MAX_USERNAME_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_LONG;
        }

        return ValidatorResult::UNKNOWN;
    } // UserCommandValidators::deepUsernameValidation

    ValidatorResult UserCommandValidators::validateChannelId(const string_view channelId) {
        logger("Validation of channelId: %s", string(channelId).c_str());

        static const regex cChannelIdRegex(RegexPatterns::CHANNEL_REGEX_ID_PATTERN);
        if(!regex_match(channelId.begin(), channelId.end(), cChannelIdRegex)) {
            logger("ChannelId validation failed, performing deep validation.");
            return deepChannelIdValidation(channelId);
        }

        logger("ChannelId validation passed.");
        return ValidatorResult::OK;
    } // UserCommandValidators::validateChannelId

    ValidatorResult UserCommandValidators::deepChannelIdValidation(const string_view channelId) {
        if(!validateContainingOnlyAllowedSymbols(channelId)) {
            return ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS;
        }
        if(!validateMinParameterLength(channelId, ClientLimits::MIN_CHANNEL_ID_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_SHORT;
        }
        if(!validateMaxParameterLength(channelId, ClientLimits::MAX_CHANNEL_ID_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_LONG;
        }

        return ValidatorResult::UNKNOWN;
    } // UserCommandValidators::deepChannelIdValidation

    ValidatorResult UserCommandValidators::validateSecret(const string_view secret) {
        logger("Validation of secret: %s", string(secret).c_str());

        static const regex cSecretRegex(RegexPatterns::SECRET_REGEX_PATTERN);
        if(!regex_match(secret.begin(), secret.end(), cSecretRegex)) {
            logger("Secret validation failed, performing deep validation.");
            return deepSecretValidation(secret);
        }

        logger("Secret validation passed.");
        return ValidatorResult::OK;
    } // UserCommandValidators::validateSecret

    ValidatorResult UserCommandValidators::deepSecretValidation(const string_view secret) {
        if(!validateContainingOnlyAllowedSymbols(secret)) {
            return ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS;
        }
        if(!validateMinParameterLength(secret, ClientLimits::MIN_SECRET_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_SHORT;
        }
        if(!validateMaxParameterLength(secret, ClientLimits::MAX_SECRET_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_LONG;
        }

        return ValidatorResult::UNKNOWN;
    } // UserCommandValidators::deepSecretValidation

    ValidatorResult UserCommandValidators::validateDisplayName(const string_view displayName) {
        logger("Validation of displayName: %s", string(displayName).c_str());

        static const regex cDisplayNameRegex(RegexPatterns::DISPLAYNAME_REGEX_PATTERN);
        if(!regex_match(displayName.begin(), displayName.end(), cDisplayNameRegex)) {
            logger("DisplayName validation failed, performing deep validation.");
            return deepDisplayNameValidation(displayName);
        }

        logger("DisplayName validation passed.");
        return ValidatorResult::OK;
    } // UserCommandValidators::validateDisplayName

    ValidatorResult UserCommandValidators::deepDisplayNameValidation(const string_view displayName) {
        if(!validateContainingOnlyAllowedSymbols(displayName)) {
            return ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS;
        }
        if(!validateMinParameterLength(displayName, ClientLimits::MIN_DISPLAY_NAME_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_SHORT;
        }
        if(!validateMaxParameterLength(displayName, ClientLimits::MAX_DISPLAY_NAME_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_LONG;
        }

        return ValidatorResult::UNKNOWN;
    } // UserCommandValidators::deepDisplayNameValidation

    ValidatorResult UserCommandValidators::validateMessageContent(const string_view messageContent) {
        logger("Validation of messageContent: %s", string(messageContent).c_str());

        static const regex cMessageContentRegex(RegexPatterns::MESSAGE_CONTENT_REGEX_PATTERN);
        if(!regex_match(messageContent.begin(), messageContent.end(), cMessageContentRegex)) {
            logger("MessageContent validation failed, performing deep validation.");
            return deepMessageContentValidation(messageContent);
        }

        logger("MessageContent validation passed.");
        return ValidatorResult::OK;
    } // UserCommandValidators::validateMessageContent

    ValidatorResult UserCommandValidators::deepMessageContentValidation(const string_view messageContent) {
        if(!validateContainingOnlyAllowedSymbols(messageContent, true)) {
            return ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS;
        }
        if(!validateMinParameterLength(messageContent, ClientLimits::MIN_MESSAGE_CONTENT_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_SHORT;
        }
        if(!validateMaxParameterLength(messageContent, ClientLimits::MAX_MESSAGE_CONTENT_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_LONG;
        }

        return ValidatorResult::UNKNOWN;
    } // UserCommandValidators::deepMessageContentValidation

    bool UserCommandValidators::truncateMessageParameter(const MessageParameter parameterType, string &commandParameter) {
        // Perform truncation based on the parameter type
        switch(parameterType) {
            case MessageParameter::USERNAME:
                return StringUtils::truncateOverReference(commandParameter, ClientLimits::MAX_USERNAME_LENGTH);
            case MessageParameter::CHANNEL_ID:
                return StringUtils::truncateOverReference(commandParameter, ClientLimits::MAX_CHANNEL_ID_LENGTH);
            case MessageParameter::SECRET:
                return StringUtils::truncateOverReference(commandParameter, ClientLimits::MAX_SECRET_LENGTH);
            case MessageParameter::DISPLAY_NAME:
                return StringUtils::truncateOverReference(commandParameter, ClientLimits::MAX_DISPLAY_NAME_LENGTH);
            case MessageParameter::MESSAGE_CONTENT:
                return StringUtils::truncateOverReference(commandParameter, ClientLimits::MAX_MESSAGE_CONTENT_LENGTH);
            default:
                logger("Invalid parameter type for truncation: %s", CastUtils::castEnumToString(parameterType).c_str());
                throw InternalErrorException(
                        "truncateMessageParameter() error: Invalid command parameter "
                        "type passed for truncation: " + CastUtils::castEnumToString(parameterType)
                        );
        }
    } // UserCommandValidators::truncateMessageParameter
} // IPK25ChatClient::Validators

/*** end of file UserCommandValidators.cpp ***/
