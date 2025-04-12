/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageValidatorResults.hpp                                   *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    11.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines the `MessageValidatorResult` enumeration,   *
 *               which represents the possible outcomes of message validation  *
 *               in the IPK25 Chat Client.                                     *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageValidatorResults.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MessageValidatorResult` enumeration for
 *        message validation results.
 */

#ifndef MESSAGE_VALIDATOR_RESULTS_HPP
#define MESSAGE_VALIDATOR_RESULTS_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum MessageValidatorResult
     * @brief Represents the results of message validation in the IPK25 Chat Client.
     */
    enum class MessageValidatorResult {
        OK = 0,                             /**< Message parameter is vavlid.    */
        INVALID,                            /**< Message parameter is invavlid.  */
        UNKNOWN,                            /**< Unknown validation result.      */
        PARAMETER_TOO_LONG,                 /**< A parameter exceeds the maximum allowed length.          */
        PARAMETER_TOO_SHORT,                /**< A parameter is shorter than the minimum required length. */
        PARAMETER_CONTAINS_INVALID_SYMBOLS  /**< A parameter contains invalid or disallowed symbols.      */
    }; // MessageValidatorResult
} // IPK25ChatClient::Enums

#endif // MESSAGE_VALIDATOR_RESULTS_HPP

/*** end of file MessageValidatorResults.hpp ***/
