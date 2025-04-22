/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageValidatorBase.hpp                                      *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `MessageValidatorBase` class,    *
 *               which serves as a base class providing common validation      *
 *               methods for message parameters used in the IPK25 Chat Client  *
 *               application. It implements the `IValidator` interface.        *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageValidatorBase.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MessageValidatorBase` class the `IValidator`
 *        interface
 */

#ifndef MESSAGE_VALIDATOR_BASE_HPP
#define MESSAGE_VALIDATOR_BASE_HPP

#include "Validators/Interfaces/IValidator.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include <string>  // std::string

namespace IPK25ChatClient::Validators
{
    /**
     * @class MessageValidatorBase
     * @brief Base class for validating message parameters implementing
     *        the `IValidator` interface.
     */
    class MessageValidatorBase : public IValidator {
    public:
        /**
         * @brief Performs post-processing validation of a command parameter.
         *
         * @details This method handles the result of the initial validation process.
         *          It determines whether the validation succeeded, failed, or if the
         *          parameter needs to be truncated to the maximum allowed length.
         *
         * @param parameterType The type of the message parameter being validated.
         * @param validationResult The result of the initial validation process.
         * @param commandParameter The command parameter to be validated and potentially modified.
         *
         * @return `true` if the post-processing validation is successful, `false` otherwise.
         */
        bool postProcessValidation(Enums::MessageParameter parameterType,
                                   Enums::ValidatorResult validationResult,
                                   std::string &commandParameter) override;

    protected:
        /**
         * @brief Maps a validation result to a boolean value.
         *
         * @details This method converts a `ValidatorResult` to a boolean value.
         *          If the result is `ValidatorResult::OK`, it returns `true`.
         *          For any other result, it returns `false`.
         *
         * @param partialResult The partial validation result to be mapped.
         * @return `true` if the result is `ValidatorResult::OK`, otherwise `false`.
         */
        static bool mapValidatorResultToBool(Enums::ValidatorResult partialResult);

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
        static bool truncateMessageParameter(Enums::MessageParameter parameterType, std::string &commandParameter);
    }; // MessageValidatorBase
} // IPK25ChatClient::Validators

#endif // MESSAGE_VALIDATOR_BASE_HPP

/*** end of file MessageValidatorBase.hpp ***/
