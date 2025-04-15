/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IValidator.hpp                                                *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `IValidator` interface, which    *
 *               provides a contract for implementing validation logic for     *
 *               message parameters in the IPK25 Chat Client application.      *
 *               It includes a method for post-processing validation of        *
 *               command parameters.                                           *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IValidator.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `IValidator` interface for message parameter
 *        validation.
 */

#ifndef I_VALIDATOR_HPP
#define I_VALIDATOR_HPP

#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include <string>  // std::string

namespace IPK25ChatClient::Validators
{
    /**
     * @class IValidator
     * @brief Interface for validating message parameters.
     */
    class IValidator {
    public:
        /**
         * @brief Virtual destructor for the `IValidator` interface.
         */
        virtual ~IValidator() = default;

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
    }; // IValidator
} // IPK25ChatClient::Validators

#endif // I_VALIDATOR_HPP

/*** end of file IValidator.hpp ***/
