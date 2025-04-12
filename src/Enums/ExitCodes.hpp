/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ExitCodes.hpp                                                 *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    10.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the ExitCodes enum class, which is used to     *
 *               represent error and other exit codes in the IPK25 Chat        *
 *               Client project.                                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ExitCodes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the ExitCodes enum class.
 */

#ifndef EXIT_CODES_HPP
#define EXIT_CODES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum ExitCode
     * @brief Enum class representing custom exit codes in the IPK25 Chat Client.
     *
     * @details This enum class defines various error codes that can be used
     *          to represent different error conditions in the IPK25 Chat Client
     *          project.
     */
    enum class ExitCode {
        SUCCESS                   = 0,   /**< Success exit code (EX_OK).                     */
        INVALID_ARGUMENT_ERROR    = 64,  /**< Command line usage error (EX_USAGE).           */
        HOSTNAME_RESOLUTION_ERROR = 68,  /**< Hostname resolution error code (EX_NOHOST).    */
        INTERNAL_ERROR            = 70,  /**< Internal error code (EX_SOFTWARE).             */
        CONNECTION_ERROR          = 71,  /**< Socket error code (EX_OSERR).                  */
        PROTOCOL_ERROR            = 76,  /**< Protocol error (EPROTO).                       */
        UNKNOWN_ERROR             = 78,  /**< Unknown error code (EX_CONFIG).                */
        TIMEOUT_ERROR             = 116, /**< Connection timed out (ETIMEDOUT).              */
        USER_INTERRUPTION_ERROR   = 130  /**< Interrupted by user error code (128 + SIGINT). */
    }; // ExitCode
} // IPK25ChatClient::Enums

#endif // EXIT_CODES_HPP

/*** end of file ExitCodes.hpp ***/
