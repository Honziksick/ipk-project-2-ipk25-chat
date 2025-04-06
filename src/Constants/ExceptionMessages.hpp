/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ExceptionMessages.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains constant exception messages used in the    *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ExceptionMessages.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Constant exception messages for the IPK25 Chat Client project.
 */

#ifndef EXCEPTION_MESSAGES_HPP
#define EXCEPTION_MESSAGES_HPP

namespace IPK25ChatClient::Constants
{
    /**
     * @brief Message indicating that the user requested help.
     */
    inline constexpr auto cHelpRequestedMsg = "User requested help.";

    /**
     * @brief Error message for invalid argument.
     */
    inline constexpr auto cInvalidArgumentErrorMsg = "Invalid argument provided.";

    /**
     * @brief Error message for hostname resolution error.
     */
    inline constexpr auto cHostnameResolutionErrorMsg = "Hostname resolution error occurred.";

    /**
     * @brief Error message for internal error.
     */
    inline constexpr auto cInternalErrorMsg = "Internal error occurred.";

    /**
     * @brief Error message for socket error.
     */
    inline constexpr auto cSocketErrorMsg = "Socket error occurred.";

    /**
     * @brief Error message for protocol error.
     */
    inline constexpr auto cProtocolErrorMsg = "Protocol error occurred.";

    /**
     * @brief Error message for unknown error.
     */
    inline constexpr auto cUnknownErrorMsg = "An unexpected unknown error occurred. Please report this issue to the developers.";

    /**
     * @brief Error message for timeout error.
     */
    inline constexpr auto cTimeoutErrorMsg = "Connection timed out.";

    /**
     * @brief Error message for user interruption.
     */
    inline constexpr auto cUserInterruptionMsg = "Operation was interrupted by SIGINT signal (i.e., CTRL+C).";
} // IPK25ChatClient::Constants

#endif // EXCEPTION_MESSAGES_HPP

/*** end of file ExceptionMessages.hpp ***/
