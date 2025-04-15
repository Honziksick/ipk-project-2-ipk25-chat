/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageValidatorBase.cpp                                      *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This source file implements the `MessageValidatorBase`        *
 *               class, which provides common validation methods for message   *
 *               parameters used in the IPK25 Chat Client application.         *
 *               It includes methods for post-processing validation and        *
 *               truncating parameters based on their type.                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageValidatorBase.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `MessageValidatorBase` class, which provides
 *        common validation methods for message parameters.
 */

#include "Validators/MessageValidatorBase.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include "Constants/ClientLimits.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>  // std::string

using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Validators
{
    bool MessageValidatorBase::postProcessValidation(const MessageParameter parameterType,
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
                        "postProcessValidation() error: Invalid command validation result type "
                        "type passed: " + CastUtils::castEnumToString(validationResult)
                        );
        }
    } // MessageValidatorBase::postProcessValidation

    bool MessageValidatorBase::truncateMessageParameter(const MessageParameter parameterType, string &commandParameter) {
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
    } // MessageValidatorBase::truncateMessageParameter
} // IPK25ChatClient::Validators

/*** end of file MessageValidatorBase.cpp ***/
