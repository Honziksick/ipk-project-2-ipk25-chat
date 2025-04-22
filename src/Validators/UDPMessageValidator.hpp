/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessageValidator.hpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      17.04.2025                                                    *
 * Last edit:    19.04.2025                                                    *
 *                                                                             *
 * Description:  This header file defines the `UdpMessageValidator` class,     *
 *               which implements validation logic for UDP messages in the     *
 *               IPK25 Chat Client application.                                *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessageValidator.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Defines the `UdpMessageValidator` class for validating UDP messages
 *        in the IPK25 Chat Client application.
 */

#ifndef UDP_MESSAGE_VALIDATOR_HPP
#define UDP_MESSAGE_VALIDATOR_HPP

#include "Validators/Interfaces/IMessageValidator.hpp"
#include "Validators/MessageParametersValidator.hpp"
#include "Common/ParsedMessage.hpp"
#include "Enums/ValidatorResults.hpp"

namespace IPK25ChatClient::Validators
{
    /**
     * @class UdpMessageValidator
     * @brief Implements validation logic for various types of UDP messages.
     *
     * @details Each message type (e.g., AUTH, JOIN, ERR) has a dedicated
     *          validation method to ensure compliance with specific constraints.
     *          This class  extends the functionality of `IMessageValidator` and
     *          `MessageParametersValidator`.
     */
    class UdpMessageValidator final : public IMessageValidator, public MessageParametersValidator {
    public:
        /**
         * @brief Validates a parsed message.
         * @details This method performs validation of a parsed message to ensure
         *          it meets the required constraints and specifications.
         *
         * @param parsedMessage The parsed message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        Enums::ValidatorResult validateMessage(const Common::ParsedMessage &parsedMessage) override;

    private:
        /**
         * @brief Validates an AUTH message.
         *
         * @param parsedMessage The parsed AUTH message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        static Enums::ValidatorResult validateAuthMessage(const Common::ParsedMessage &parsedMessage);

        /**
         * @brief Validates a JOIN message.
         *
         * @param parsedMessage The parsed JOIN message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        static Enums::ValidatorResult validateJoinMessage(const Common::ParsedMessage &parsedMessage);

        /**
         * @brief Validates an ERR message.
         *
         * @param parsedMessage The parsed ERR message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        static Enums::ValidatorResult validateErrMessage(const Common::ParsedMessage &parsedMessage);

        /**
         * @brief Validates a BYE message.
         *
         * @param parsedMessage The parsed BYE message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        static Enums::ValidatorResult validateByeMessage(const Common::ParsedMessage &parsedMessage);

        /**
         * @brief Validates a REPLY message.
         *
         * @param parsedMessage The parsed REPLY message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        static Enums::ValidatorResult validateReplyMessage(const Common::ParsedMessage &parsedMessage);

        /**
         * @brief Validates a MSG message.
         *
         * @param parsedMessage The parsed MSG message to validate.
         *
         * @return A `ValidatorResult` indicating the validation outcome.
         */
        static Enums::ValidatorResult validateMsgMessage(const Common::ParsedMessage &parsedMessage);
    }; // UdpMessageValidator
} // IPK25ChatClient::Validators

#endif // UDP_MESSAGE_VALIDATOR_HPP

/*** end of file UDPMessageValidator.hpp ***/
