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
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `ExitCode` enum class, which is used to    *
 *               represent error and other exit codes in the IPK25 Chat        *
 *               Client project.                                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ExitCodes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `ExitCode` enum class.
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
        SUCCESS                   = 0,     /**< Success exit code (on help, server bye, CTRL+C and CTRL+D).       */
        INTERNAL_ERROR            = 1,     /**< Internal error code (EPERM).                                      */
        INVALID_ARGUMENT_ERROR    = 22,    /**< Command line usage error (EINVAL).                                */
        UNKNOWN_ERROR             = 42,    /**< Unknown error (The Answer to Life, the Universe, and Everything). */
        MESSAGE_LOST_ERROR        = 61,    /**< Message lost error (ENODATA).                                     */
        PROTOCOL_ERROR            = 71,    /**< Protocol error (EPROTO).                                          */
        SERVER_DISCONNECTED_ERROR = 100,   /**< Server disconnected error (ENETDOWN).                             */
        CONNECTION_ERROR          = 101,   /**< General connection problem error code (ENETUNREACH).              */
        UNESTABLISHED_ERROR       = 107,   /**< Connection is unexpectedly not established (ENOTCONN).            */
        TIMEOUT_ERROR             = 110,   /**< Connection timed out (ETIMEDOUT).                                 */
        HOSTNAME_RESOLUTION_ERROR = 113,   /**< Hostname resolution error code (EHOSTUNREACH).                    */
    }; // ExitCode
} // IPK25ChatClient::Enums

#endif // EXIT_CODES_HPP

/*** end of file ExitCodes.hpp ***/
