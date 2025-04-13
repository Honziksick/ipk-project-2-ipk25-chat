/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommandValidators.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    13.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `CommandValidators` class,       *
 *               which provides static methods for validating various command  *
 *               parameters used in the IPK25 Chat Client application. These   *
 *               methods ensure that parameters meet specific constraints      *
 *               such as allowed symbols, length limits, and regex patterns.   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommandValidators.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining of the `CommandValidators` class
 *        for message parameter validation.
 */

#ifndef COMMAND_VALIDATORS_HPP
#define COMMAND_VALIDATORS_HPP

#include "Enums/MessageParameters.hpp"
#include "Enums/CommandValidatorsResults.hpp"
#include <string_view>  // std::string_view

namespace IPK25ChatClient::CommandParser
{
    /**
     * @class CommandValidators
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
    class CommandValidators final {
    public:
        /**
         * @brief Validates a message parameter based on its type.
         *
         * @param parameterType The type of the message parameter (e.g., USERNAME, CHANNEL_ID).
         * @param messageParameter The value of the parameter to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult validateMessageParameter(Enums::MessageParameter parameterType,
                                                                      std::string_view messageParameter);

    private:
        /**
         * @brief Validates that the parameter contains only allowed symbols.
         *
         * @note Spaces and line feeds are not allowed by default.
         *
         * @param messageParameter The parameter to validate.
         * @param whiteCharsAllowed A boolean flag indicating whether spaces
         *                          and line feeds are allowed in the parameter.
         *
         * @return `true` if the parameter contains only allowed symbols, `false` otherwise.
         */
        static bool validateContainingOnlyAllowedSymbols(std::string_view messageParameter, bool whiteCharsAllowed = false);

        /**
         * @brief Validates that the parameter meets the minimum length requirement.
         *
         * @param messageParameter The parameter to validate.
         * @param minLength The minimum allowed length.
         *
         * @return `true` if the parameter meets the minimum length, `false` otherwise.
         */
        static bool validateMinParameterLength(std::string_view messageParameter, unsigned int minLength);

        /**
         * @brief Validates that the parameter does not exceed the maximum length.
         *
         * @param messageParameter The parameter to validate.
         * @param maxLength The maximum allowed length.
         *
         * @return `true` if the parameter does not exceed the maximum length, `false` otherwise.
         */
        static bool validateMaxParameterLength(std::string_view messageParameter, unsigned int maxLength);

        /**
         * @brief Validates a username parameter.
         *
         * @param username The username to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult validateUsername(std::string_view username);

        /**
         * @brief Performs deep validation of a username parameter.
         *
         * @param username The username to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult deepUsernameValidation(std::string_view username);

        /**
         * @brief Validates a channel ID parameter.
         *
         * @param channelId The channel ID to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult validateChannelId(std::string_view channelId);

        /**
         * @brief Performs deep validation of a channel ID parameter.
         *
         * @param channelId The channel ID to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult deepChannelIdValidation(std::string_view channelId);

        /**
         * @brief Validates a secret parameter.
         *
         * @param secret The secret to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult validateSecret(std::string_view secret);

        /**
         * @brief Performs deep validation of a secret parameter.
         *
         * @param secret The secret to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult deepSecretValidation(std::string_view secret);

        /**
         * @brief Validates a display name parameter.
         *
         * @param displayName The display name to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult validateDisplayName(std::string_view displayName);

        /**
         * @brief Performs deep validation of a display name parameter.
         *
         * @param displayName The display name to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult deepDisplayNameValidation(std::string_view displayName);

        /**
         * @brief Validates a message content parameter.
         *
         * @param messageContent The message content to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult validateMessageContent(std::string_view messageContent);

        /**
         * @brief Performs deep validation of a message content parameter.
         *
         * @param messageContent The message content to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::CommandValidatorsResult deepMessageContentValidation(std::string_view messageContent);
    }; // CommandValidators
} // IPK25ChatClient::CommandParser

#endif // COMMAND_VALIDATORS_HPP

/*** end of file CommandValidators.hpp ***/
