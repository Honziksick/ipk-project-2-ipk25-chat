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
 * Description:  This header file defines the `IMessageValidator` interface,   *
 *               which provides a contract for validating parsed messages in   *
 *               the IPK25 Chat Client application.                            *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessageValidator.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Defines the `IMessageValidator` interface for validating parsed
 *        messages in the IPK25 Chat Client application.
 */

#ifndef I_MESSAGE_VALIDATOR_HPP
#define I_MESSAGE_VALIDATOR_HPP

#include "Common/ParsedMessage.hpp"
#include "Enums/ValidatorResults.hpp"

namespace IPK25ChatClient::Validators
{
    /**
     * @class IMessageValidator
     * @brief Interface for validating parsed messages.
     *
     * @details This interface provides a method for validating parsed messages
     *          represented by the `ParsedMessage` class. Implementing classes
     *          must define the behaviour for ensuring messages meet specific
     *          validation criteria.
     */
    class IMessageValidator {
    public:
        /**
         * @brief Virtual destructor for the `IMessageValidator` interface.
         */
        virtual ~IMessageValidator() = default;

        /**
         * @brief Validates a parsed message.
         * @details This method performs validation of a parsed message to ensure
         *          it meets the required constraints and specifications.
         *
         * @param parsedMessage The parsed message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        virtual Enums::ValidatorResult validateMessage(const Common::ParsedMessage &parsedMessage) = 0;
    }; // IMessageValidator
} // IPK25ChatClient::Validators

#endif // I_MESSAGE_VALIDATOR_HPP

/*** end of file IMessageValidator.hpp ***/
