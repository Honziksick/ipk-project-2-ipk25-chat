/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UserCommandValidators.hpp                                     *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `UserCommandValidators` class,   *
 *               which provides static methods for validating various command  *
 *               parameters used in the IPK25 Chat Client application. These   *
 *               methods ensure that parameters meet specific constraints      *
 *               such as allowed symbols, length limits, and regex patterns.   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UserCommandValidators.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining of the `UserCommandValidators` class
 *        for message parameter validation.
 */

#ifndef USER_COMMAND_VALIDATORS_HPP
#define USER_COMMAND_VALIDATORS_HPP

#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include <string_view>  // std::string_view

namespace IPK25ChatClient::Validators
{
    /**
     * @class UserCommandValidators
     * @brief Provides static methods for validating message parameters.
     *
     * @details This class contains methods to validate various message parameters
     *          such as usernames, channel IDs, secrets, display names, and
     *          message content. It includes both basic and deep validation
     *          methods to ensure parameters meet the required constraints.
     *
     * @note Methods use `std::string_view` for efficiency and to avoid
     *       unnecessary copying of passed strings.
     * @note Basic validation consists of checking if the parameter matches
     *       a regex pattern.
     * @note If the basic validation fails, deep validation commences. Deep
     *       validation checks separatly for allowed symbols, minimum and maximum
     *       lengths and provides detailed error messages.
     */
    class UserCommandValidators final {
    public:
        /**
         * @brief Validates a message parameter based on its type.
         *
         * @param parameterType The type of the message parameter (e.g., USERNAME, CHANNEL_ID).
         * @param commandParameter The value of the parameter to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateMessageParameter(Enums::MessageParameter parameterType,
                                                                       std::string_view commandParameter);
        /**
         * @brief Performs post-processing validation of a command parameter.
         *
         * @details This method handles validation result post-proccessing.
         *          It determines of the validation succeeded, failed, or the
         *          parameter needs to be truncated to maximum length.
         *
         * @param parameterType The type of the message parameter being validated.
         * @param validationResult The result of the initial validation process.
         * @param commandParameter The command parameter to be validated and potentially modified.
         *
         * @return `true` if the post-processing validation is successful, `false` otherwise.
         */
        static bool postProccessValidation(Enums::MessageParameter parameterType,
                                           Enums::ValidatorResult validationResult,
                                           std::string &commandParameter);

    private:
        /**
         * @brief Validates that the parameter contains only allowed symbols.
         *
         * @note Spaces and line feeds are not allowed by default.
         *
         * @param commandParameter The parameter to validate.
         * @param whiteCharsAllowed A boolean flag indicating whether spaces
         *                          and line feeds are allowed in the parameter.
         *
         * @return `true` if the parameter contains only allowed symbols, `false` otherwise.
         */
        static bool validateContainingOnlyAllowedSymbols(std::string_view commandParameter, bool whiteCharsAllowed = false);

        /**
         * @brief Validates that the parameter meets the minimum length requirement.
         *
         * @param commandParameter The parameter to validate.
         * @param minLength The minimum allowed length.
         *
         * @return `true` if the parameter meets the minimum length, `false` otherwise.
         */
        static bool validateMinParameterLength(std::string_view commandParameter, unsigned int minLength);

        /**
         * @brief Validates that the parameter does not exceed the maximum length.
         *
         * @param commandParameter The parameter to validate.
         * @param maxLength The maximum allowed length.
         *
         * @return `true` if the parameter does not exceed the maximum length, `false` otherwise.
         */
        static bool validateMaxParameterLength(std::string_view commandParameter, unsigned int maxLength);

        /**
         * @brief Validates a username parameter.
         *
         * @param username The username to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateUsername(std::string_view username);

        /**
         * @brief Performs deep validation of a username parameter.
         *
         * @param username The username to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepUsernameValidation(std::string_view username);

        /**
         * @brief Validates a channel ID parameter.
         *
         * @param channelId The channel ID to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateChannelId(std::string_view channelId);

        /**
         * @brief Performs deep validation of a channel ID parameter.
         *
         * @param channelId The channel ID to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepChannelIdValidation(std::string_view channelId);

        /**
         * @brief Validates a secret parameter.
         *
         * @param secret The secret to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateSecret(std::string_view secret);

        /**
         * @brief Performs deep validation of a secret parameter.
         *
         * @param secret The secret to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepSecretValidation(std::string_view secret);

        /**
         * @brief Validates a display name parameter.
         *
         * @param displayName The display name to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateDisplayName(std::string_view displayName);

        /**
         * @brief Performs deep validation of a display name parameter.
         *
         * @param displayName The display name to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepDisplayNameValidation(std::string_view displayName);

        /**
         * @brief Validates a message content parameter.
         *
         * @param messageContent The message content to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateMessageContent(std::string_view messageContent);

        /**
         * @brief Performs deep validation of a message content parameter.
         *
         * @param messageContent The message content to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepMessageContentValidation(std::string_view messageContent);

        /**
         * @brief Truncates a message parameter based on its type.
         *
         * @details This method modifies the provided command parameter by truncating
         *          it to the maximum allowed length for the given parameter type.
         *          The truncation is performed by `StringUtils::truncateOverReference()`.
         *
         * @param parameterType The type of the message parameter (e.g., USERNAME, CHANNEL_ID).
         * @param commandParameter The command parameter to be truncated. Passed by reference,
         *                         so modifications will affect the original string.
         *
         * @return `true` if the parameter was truncated, `false` if no truncation was necessary.
         */
        static bool truncateMessageParameter(Enums::MessageParameter parameterType, std::string& commandParameter);
    }; // UserCommandValidators
} // IPK25ChatClient::Validators

#endif // USER_COMMAND_VALIDATORS_HPP

/*** end of file UserCommandValidators.hpp ***/
