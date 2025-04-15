/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IMessageValidator.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This file declares the `IMessageValidator` interface, which   *
 *               provides methods for validating and post-processing message   *
 *               parameters such as usernames, channel IDs, secrets, display   *
 *               names, and message content.                                   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessageValidator.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Interface `IMessageValidator` for validating and post-processing
 *        message parameters.
 */

#ifndef I_MESSAGE_VALIDATOR_HPP
#define I_MESSAGE_VALIDATOR_HPP

#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include <string_view>  // std::string_view

namespace IPK25ChatClient::Validators
{
    /**
     * @class IMessageValidator
     * @brief Interface for validating message parameters.
     *
     * @details This interface defines methods for validating various message
     *          parameters such as usernames, channel IDs, secrets, display names,
     *          and message content. It includes both basic validation and
     *          post-processing validation to ensure parameters meet the required
     *          constraints.
     */
    class IMessageValidator {
    public:
        /**
         * @brief Virtual destructor for the `IMessageValidator` interface.
         */
        virtual ~IMessageValidator() = default;

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
        virtual Enums::ValidatorResult validateMessageParameter(Enums::MessageParameter parameterType,
                                                                std::string_view commandParameter) = 0;

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
        virtual bool postProcessValidation(Enums::MessageParameter parameterType,
                                           Enums::ValidatorResult validationResult,
                                           std::string &commandParameter) = 0;
    }; // IMessageValidator
} // IPK25ChatClient::Validators

#endif // I_MESSAGE_VALIDATOR_HPP

/*** end of file IMessageValidator.hpp ***/
