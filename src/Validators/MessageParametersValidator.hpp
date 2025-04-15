/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageParametersValidator.hpp                                *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `MessageParametersValidator`     *
 *               class, which implements validation logic for message          *
 *               parameters in the IPK25 Chat Client application.              *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageParametersValidator.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MessageParametersValidator` class for
 *        validating message parameters in the IPK25 Chat Client application.
 */

#ifndef MESSAGE_PARAMETERS_VALIDATOR_HPP
#define MESSAGE_PARAMETERS_VALIDATOR_HPP

#include "Validators/Interfaces/IMessageParametersValidator.hpp"
#include "Validators/MessageValidatorBase.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include <string_view>  // std::string_view

namespace IPK25ChatClient::Validators
{
    /**
     * @class MessageParametersValidator
     * @brief Implements validation logic for message parameters.
     *
     * @details This class provides methods to validate various types of message
     *          parameters, ensuring they meet specific constraints such as
     *          allowed symbols, length limits, and regex patterns. It extends
     *          the functionality of `IMessageParametersValidator` and
     *          `MessageValidatorBase`.
     *
     * @note Methods use `std::string_view` for efficiency and to avoid
     *       unnecessary copying of passed strings.
     * @note Basic validation consists of checking if the parameter matches
     *       a regex pattern.
     * @note If the basic validation fails, deep validation commences. Deep
     *       validation checks separatly for allowed symbols, minimum and maximum
     *       lengths and provides detailed error messages.
     */
    class MessageParametersValidator : public IMessageParametersValidator, public MessageValidatorBase {
    public:
        /**
         * @brief Validates a message parameter based on its type.
         *
         * @details This method performs validation of a message parameter
         *          based on the specified parameter type. The validation
         *          ensures the parameter meets the required constraints.
         *
         * @param parameterType The type of the message parameter (e.g., USERNAME, CHANNEL_ID).
         * @param commandParameter The value of the parameter to validate.
         *
         * @return A ValidatorResult indicating the validation outcome.
         */
        Enums::ValidatorResult validateMessageParameter(Enums::MessageParameter parameterType,
                                                        std::string_view commandParameter) override;

    protected:
        /**
         * @brief Validates a username parameter.
         *
         * @param username The username to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateUsername(std::string_view username);

        /**
         * @brief Validates a channel ID parameter.
         *
         * @param channelId The channel ID to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateChannelId(std::string_view channelId);

        /**
         * @brief Validates a secret parameter.
         *
         * @param secret The secret to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateSecret(std::string_view secret);

        /**
         * @brief Validates a display name parameter.
         *
         * @param displayName The display name to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateDisplayName(std::string_view displayName);

        /**
         * @brief Validates a message content parameter.
         *
         * @param messageContent The message content to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult validateMessageContent(std::string_view messageContent);

    private:
        /**
         * @brief Performs deep validation of a username parameter.
         *
         * @param username The username to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepUsernameValidation(std::string_view username);

        /**
         * @brief Performs deep validation of a channel ID parameter.
         *
         * @param channelId The channel ID to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepChannelIdValidation(std::string_view channelId);

        /**
         * @brief Performs deep validation of a secret parameter.
         *
         * @param secret The secret to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepSecretValidation(std::string_view secret);

        /**
         * @brief Performs deep validation of a display name parameter.
         *
         * @param displayName The display name to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepDisplayNameValidation(std::string_view displayName);

        /**
         * @brief Performs deep validation of a message content parameter.
         *
         * @param messageContent The message content to validate.
         *
         * @return A CommandValidatorsResult indicating the validation outcome.
         */
        static Enums::ValidatorResult deepMessageContentValidation(std::string_view messageContent);

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
    }; // MessageParametersValidator
} // IPK25ChatClient::Validators

#endif // MESSAGE_PARAMETERS_VALIDATOR_HPP

/*** end of file MessageParametersValidator.hpp ***/
