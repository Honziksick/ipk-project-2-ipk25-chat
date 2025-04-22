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
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains constant exception messages used in the    *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ExceptionMessages.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file containing exception messages for the IPK25 Chat Client project.
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
        static constexpr auto HELP_REQUESTED_MSG = "User requested help.";

        /**
         * @brief Message indicating that the user pressed CTRL+D or EOF was read.
         */
        static constexpr auto END_OF_FILE_MSG = "User pressed CTRL+D or EOF was read.";

        /**
         * @brief Message indicating that the server is disconnected.
         */
        static constexpr auto SERVER_DISCONNECTED_MSG = "The server has disconnected.";

        /**
         * @brief Error message for invalid argument.
         */
        static constexpr auto INVALID_ARGUMENT_ERROR_MSG = "Invalid argument provided.";

        /**
         * @brief Error message for hostname resolution error.
         */
        static constexpr auto HOSTNAME_RESOLUTION_ERROR_MSG = "Hostname resolution error occurred.";

        /**
         * @brief Error message for internal error.
         */
        static constexpr auto INTERNAL_ERROR_MSG = "Internal error occurred.";

        /**
         * @brief Error message for socket error.
         */
        static constexpr auto CONNECTION_ERROR_MSG = "Socket error occurred.";

        /**
         * @brief Error message for protocol error.
         */
        static constexpr auto PROTOCOL_ERROR_MSG = "Protocol error occurred.";

        /**
         * @brief Error message for unknown error.
         */
        static constexpr auto UNKNOWN_ERROR_MSG = "An unexpected unknown error occurred. Please report this issue to the developers.";

        /**
         * @brief Error message for unestablished connection error.
         */
        static constexpr auto UNESTABLISHED_ERROR_MSG = "The connection is not established.";

        /**
         * @brief Error message for object constructor error.
         */
        static constexpr auto CONSTRUCTOR_ERROR_MSG = "An error occurred during the object construction process.";

        /**
         * @brief All retransmission attempts failed error message.
         */
        static constexpr auto MESSAGE_LOST_MSG = "All retransmission attempts failed.";

        /**
         * @brief Server send Bye message notification.
         */
        static constexpr auto SERVER_SEND_BYE = "Server send Bye message.";

        /**
         * @brief Error message for timeout error.
         */
        static constexpr auto TIMEOUT_ERROR_MSG = "Connection timed out.";

        /**
         * @brief Error message for user interruption.
         */
        static constexpr auto USER_INTERRUPTION_MSG = "Operation was interrupted by SIGINT signal (i.e., CTRL+C).";
    }; // ExceptionMessages
} // IPK25ChatClient::Constants

#endif // EXCEPTION_MESSAGES_HPP

/*** end of file ExceptionMessages.hpp ***/
