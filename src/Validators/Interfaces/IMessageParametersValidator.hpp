/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IMessageParametersValidator.hpp                               *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `IMessageParametersValidator`    *
 *               interface, which provides a contract for validating message   *
 *               parameters in the IPK25 Chat Client application.              *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessageParametersValidator.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `IMessageParametersValidator` interface for
 *        validating message parameters in the IPK25 Chat Client application.
 */

#ifndef I_MESSAGE_PARAMETERS_VALIDATOR_HPP
#define I_MESSAGE_PARAMETERS_VALIDATOR_HPP

#include "Enums/MessageParameters.hpp"
#include "Enums/ValidatorResults.hpp"
#include <string_view>  // std::string_view

namespace IPK25ChatClient::Validators
{
    /**
     * @class IMessageParametersValidator
     * @brief Interface for validating message parameters.
     *
     * @details This interface provides a method for validating message parameters
     *          based on their type. Implementing classes must define the behaviour
     *          for ensuring parameters meet specific constraints.
     */
    class IMessageParametersValidator {
    public:
        /**
         * @brief Virtual destructor for the `IMessageParametersValidator` interface.
         */
        virtual ~IMessageParametersValidator() = default;

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
    }; // IMessageParametersValidator
} // IPK25ChatClient::Validators

#endif // I_MESSAGE_PARAMETERS_VALIDATOR_HPP

/*** end of file IMessageParametersValidator.hpp ***/
