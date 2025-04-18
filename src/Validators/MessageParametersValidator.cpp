/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageParametersValidator.cpp                                *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  This source file implements the `MessageParametersValidator`  *
 *               class, which provides validation logic for message parameters *
 *               in the IPK25 Chat Client application.                         *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageParametersValidator.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `MessageParametersValidator` class, which
 *        validates message parameters in the IPK25 Chat Client application.
 */

#include "Validators/MessageParametersValidator.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include "Constants/ClientLimits.hpp"
#include "Constants/RegexPatterns.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>        // std::string
#include <regex>         // std::regex, std::regex_match
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Validators
{
    ValidatorResult MessageParametersValidator::validateMessageParameter(const MessageParameter parameterType,
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
                        "type passed: " + CastUtils::castEnumToString(parameterType),
                        ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                        );
        }

        // Check if the result is OK or may be interpreted as OK
        switch(result) {
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
    } // MessageParametersValidator::validateMessageParameter

    bool MessageParametersValidator::validateContainingOnlyAllowedSymbols(const string_view commandParameter, const bool whiteCharsAllowed) {
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
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_BAD_CHARACTERS);
            return false;
        }

        logger("Deep validation passed: parameter contains only allowed symbols.");
        return true;
    } // MessageParametersValidator::validateContainingOnlyAllowedSymbols

    bool MessageParametersValidator::validateMessageContentAllowedSymbols(const string_view messgaContent) {
        logger("Deep validation called with commandParameter: %s", string(messgaContent).c_str());

        // We define the allowed characters as a set of characters from 0x0A to 0x7E
        const auto allowedSymbols = [] {
            unordered_set<char> set;
            for (char c = 0x0A; c <= 0x7E; ++c) {
                set.insert(c);
            }
            return set;
        }();

        // We check every character in the message content one-by-one
        for (const char &symbol : messgaContent) {
            if (!allowedSymbols.contains(symbol)) {
                logger("Deep validation failed: parameter contains invalid symbols.");
                ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_BAD_CHARACTERS);
                return false;
            }
        }

        logger("Deep validation passed: parameter contains only allowed symbols.");
        return true;
    } // MessageParametersValidator::validateMessageContentAllowedSymbols

    bool MessageParametersValidator::validateMinParameterLength(const string_view commandParameter, const unsigned int minLength) {
        logger("Deep validation called with commandParameter: %s, minLength: %u", string(commandParameter).c_str(), minLength);

        if(commandParameter.length() < minLength) {
            logger("Deep validation failed: parameter length is %zu, which is less than %u", commandParameter.length(), minLength);
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_BAD_LENGTH);
            return false;
        }

        logger("Deep validation passed: parameter length is %zu", commandParameter.length());
        return true;
    } // MessageParametersValidator::validateMinParameterLength

    bool MessageParametersValidator::validateMaxParameterLength(const string_view commandParameter, const unsigned int maxLength) {
        logger("Deep validation called with commandParameter: %s, maxLength: %u", string(commandParameter).c_str(), maxLength);

        if(commandParameter.length() > maxLength) {
            logger("Deep alidation failed: parameter length is %zu, which exceeds %u", commandParameter.length(), maxLength);
            ClientOutput::printClientInternalError(
                    ClientInternalErrorMessage::CLIENT_BAD_LENGTH_TRUNCATE, string(commandParameter.substr(0, maxLength))
                    );
            return false;
        }

        logger("Deep validation passed: parameter length is %zu", commandParameter.length());
        return true;
    } // MessageParametersValidator::validateMaxParameterLength

    ValidatorResult MessageParametersValidator::validateUsername(const string_view username) {
        logger("Validation of username: %s", string(username).c_str());

        static const regex cUsernameRegex(RegexPatterns::USERNAME_REGEX_PATTERN);
        if(!regex_match(username.begin(), username.end(), cUsernameRegex)) {
            logger("Username validation failed, performing deep validation.");
            return deepUsernameValidation(username);
        }

        logger("Username validation passed.");
        return ValidatorResult::OK;
    } // MessageParametersValidator::validateUsername

    ValidatorResult MessageParametersValidator::deepUsernameValidation(const string_view username) {
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
    } // MessageParametersValidator::deepUsernameValidation

    ValidatorResult MessageParametersValidator::validateChannelId(const string_view channelId) {
        logger("Validation of channelId: %s", string(channelId).c_str());

        static const regex cChannelIdRegex(RegexPatterns::CHANNEL_REGEX_ID_PATTERN_WITH_DOT);
        if(!regex_match(channelId.begin(), channelId.end(), cChannelIdRegex)) {
            logger("ChannelId validation failed, performing deep validation.");
            return deepChannelIdValidation(channelId);
        }

        logger("ChannelId validation passed.");
        return ValidatorResult::OK;
    } // MessageParametersValidator::validateChannelId

    ValidatorResult MessageParametersValidator::deepChannelIdValidation(const string_view channelId) {
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
    } // MessageParametersValidator::deepChannelIdValidation

    ValidatorResult MessageParametersValidator::validateSecret(const string_view secret) {
        logger("Validation of secret: %s", string(secret).c_str());

        static const regex cSecretRegex(RegexPatterns::SECRET_REGEX_PATTERN);
        if(!regex_match(secret.begin(), secret.end(), cSecretRegex)) {
            logger("Secret validation failed, performing deep validation.");
            return deepSecretValidation(secret);
        }

        logger("Secret validation passed.");
        return ValidatorResult::OK;
    } // MessageParametersValidator::validateSecret

    ValidatorResult MessageParametersValidator::deepSecretValidation(const string_view secret) {
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
    } // MessageParametersValidator::deepSecretValidation

    ValidatorResult MessageParametersValidator::validateDisplayName(const string_view displayName) {
        logger("Validation of displayName: %s", string(displayName).c_str());

        static const regex cDisplayNameRegex(RegexPatterns::DISPLAYNAME_REGEX_PATTERN);
        if(!regex_match(displayName.begin(), displayName.end(), cDisplayNameRegex)) {
            logger("DisplayName validation failed, performing deep validation.");
            return deepDisplayNameValidation(displayName);
        }

        logger("DisplayName validation passed.");
        return ValidatorResult::OK;
    } // MessageParametersValidator::validateDisplayName

    ValidatorResult MessageParametersValidator::deepDisplayNameValidation(const string_view displayName) {
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
    } // MessageParametersValidator::deepDisplayNameValidation

    ValidatorResult MessageParametersValidator::validateMessageContent(const string_view messageContent) {
        logger("Validation of messageContent: %s", string(messageContent).c_str());

        if(!validateMessageContentAllowedSymbols(messageContent)) {
            return ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS;
        }
        if(!validateMinParameterLength(messageContent, ClientLimits::MIN_MESSAGE_CONTENT_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_SHORT;
        }
        if(!validateMaxParameterLength(messageContent, ClientLimits::MAX_MESSAGE_CONTENT_LENGTH)) {
            return ValidatorResult::PARAMETER_TOO_LONG;
        }

        logger("MessageContent validation passed.");
        return ValidatorResult::OK;
    } // MessageParametersValidator::validateMessageContent
} // IPK25ChatClient::Validators

/*** end of file MessageParametersValidator.cpp ***/
