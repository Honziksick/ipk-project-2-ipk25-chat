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
     * @class ExceptionMessages
     * @brief Class containing constant exception messages used in the
     *        IPK25 Chat Client project.
     */
    class ExceptionMessages {
    public:
        /**
         * @brief Message indicating that the user requested help.
         */
        static constexpr auto cHelpRequestedMsg = "User requested help.";

        /**
         * @brief Error message for invalid argument.
         */
        static constexpr auto cInvalidArgumentErrorMsg = "Invalid argument provided.";

        /**
         * @brief Error message for hostname resolution error.
         */
        static constexpr auto cHostnameResolutionErrorMsg = "Hostname resolution error occurred.";

        /**
         * @brief Error message for internal error.
         */
        static constexpr auto cInternalErrorMsg = "Internal error occurred.";

        /**
         * @brief Error message for socket error.
         */
        static constexpr auto cSocketErrorMsg = "Socket error occurred.";

        /**
         * @brief Error message for protocol error.
         */
        static constexpr auto cProtocolErrorMsg = "Protocol error occurred.";

        /**
         * @brief Error message for unknown error.
         */
        static constexpr auto cUnknownErrorMsg = "An unexpected unknown error occurred. Please report this issue to the developers.";

        /**
         * @brief Error message for timeout error.
         */
        static constexpr auto cTimeoutErrorMsg = "Connection timed out.";

        /**
         * @brief Error message for user interruption.
         */
        static constexpr auto cUserInterruptionMsg = "Operation was interrupted by SIGINT signal (i.e., CTRL+C).";
    }; // ExceptionMessages
} // IPK25ChatClient::Constants

#endif // EXCEPTION_MESSAGES_HPP

/*** end of file ExceptionMessages.hpp ***/
