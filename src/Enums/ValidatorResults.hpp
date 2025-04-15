/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ValidatorResults.hpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines the `ValidatorResults` enumeration,         *
 *               which represents the possible outcomes of message validation  *
 *               in the IPK25 Chat Client.                                     *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ValidatorResults.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `ValidatorResults` enumeration for
 *        message validation results.
 */

#ifndef VALIDATOR_RESULTS_HPP
#define VALIDATOR_RESULTS_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum ValidatorResult
     * @brief Represents the results of message validation in the IPK25 Chat Client.
     */
    enum class ValidatorResult {
        OK = 0,                             /**< Message parameter is vavlid.    */
        INVALID,                            /**< Message parameter is invavlid.  */
        UNKNOWN,                            /**< Unknown validation result.      */
        PARAMETER_TOO_LONG,                 /**< A parameter exceeds the maximum allowed length.          */
        PARAMETER_TOO_SHORT,                /**< A parameter is shorter than the minimum required length. */
        PARAMETER_CONTAINS_INVALID_SYMBOLS  /**< A parameter contains invalid or disallowed symbols.      */
    }; // ValidatorResults
} // IPK25ChatClient::Enums

#endif // VALIDATOR_RESULTS_HPP

/*** end of file ValidatorResults.hpp ***/
