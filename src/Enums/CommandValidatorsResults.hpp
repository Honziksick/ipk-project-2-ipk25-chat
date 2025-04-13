/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommandValidatorsResults.hpp                                  *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    13.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines the `CommandValidatorsResult` enumeration,  *
 *               which represents the possible outcomes of message validation  *
 *               in the IPK25 Chat Client.                                     *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommandValidatorsResults.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `CommandValidatorsResult` enumeration for
 *        message validation results.
 */

#ifndef COMMAND_VALIDATORS_RESULTS_HPP
#define COMMAND_VALIDATORS_RESULTS_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum CommandValidatorsResult
     * @brief Represents the results of message validation in the IPK25 Chat Client.
     */
    enum class CommandValidatorsResult {
        OK = 0,                             /**< Message parameter is vavlid.    */
        INVALID,                            /**< Message parameter is invavlid.  */
        UNKNOWN,                            /**< Unknown validation result.      */
        PARAMETER_TOO_LONG,                 /**< A parameter exceeds the maximum allowed length.          */
        PARAMETER_TOO_SHORT,                /**< A parameter is shorter than the minimum required length. */
        PARAMETER_CONTAINS_INVALID_SYMBOLS  /**< A parameter contains invalid or disallowed symbols.      */
    }; // CommandValidatorsResult
} // IPK25ChatClient::Enums

#endif // COMMAND_VALIDATORS_RESULTS_HPP

/*** end of file CommandValidatorsResults.hpp ***/
