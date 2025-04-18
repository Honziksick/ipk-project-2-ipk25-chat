/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientInternalErrorPhrases.hpp                                *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      17.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines a class containing constant client internal *
 *               error phrases used by the IPK25 Chat Client application to    *
 *               display to the user if error occures                          *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientInternalErrorPhrases.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining collection of constant error phrases later
 *        concatenated into messages and dissplayed to the user.
 */

#ifndef CLIENT_INTERNAL_ERROR_PHRASES_HPP
#define CLIENT_INTERNAL_ERROR_PHRASES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @class ClientInternalErrorPhrases
     * @brief A class containing constant error phrases for internal client errors.
     *
     * @details This class provides a collection of static constant strings that
     *          represent various error phrases used by the IPK25 Chat Client.
     *          These messages are later concatenated into messages and dissplayed
     *          to the user in case of an erros or an issue.
     */
    class ClientInternalErrorPhrases {
    protected:
        /**
         * @brief General apology phrase for unexpected errors.
         */
        static constexpr auto APOLOGY = "We sincerely apologize for the inconvenience. Please report this error to the support team so we can contact you when the problem is resolved. ";

        /**
         * @brief Phrase indicating the client will inform the server about the error and terminate.
         */
        static constexpr auto SEND_ERROR_TERMINATE = "The application will now attempt to inform the server about the error. The client will afterward terminate gracefully if possible. ";

        /**
         * @brief Phrase indicating the client cannot inform the server and will terminate.
         */
        static constexpr auto DONT_SEND_ERROR_TERMINATE = "The connection to the server is not established, so the client can't inform the server about the error. The application will now terminate. ";

        /**
         * @brief Phrase indicating the client will terminate gracefully.
         */
        static constexpr auto JUST_TERMINATE = "The client will now terminate gracefully. ";

        /**
         * @brief Phrase indicating a connection issue.
         */
        static constexpr auto CONNECTION_ISSUE = "Oops, there seems to be a connection issue. ";

        /**
         * @brief Phrase for unexpected internal errors during a chat session.
         */
        static constexpr auto INTERNAL_ERROR = "An unexpected internal error occurred during your chat session: ";

        /**
         * @brief Phrase indicating the user is trying to enter another /auth command before server reply.
         */
        static constexpr auto AUTH_NO_REPLY = "It is not possible to enter another /auth command before receiving a reply on the previous command from the server first. ";

        /**
         * @brief Phrase indicating the user is already authenticated.
         */
        static constexpr auto AUTH_AGAIN = "The user is already authenticated and cannot authenticate again. ";

        /**
         * @brief Phrase indicating authentication is required before sending messages.
         */
        static constexpr auto NOT_AUTH = "Messages cannot be sent prior to authentication or without joining a chat channel. ";

        /**
         * @brief Phrase for invalid commands entered by the user.
         */
        static constexpr auto BAD_COMMAND = "Oops, it appears you've entered an invalid command. ";

        /**
         * @brief Phrase prompting the user to use the help command.
         */
        static constexpr auto HELP_PROMPT = "You may use the '/help' command to view all valid client commands along with their description, structure and usage examples. ";

        /**
         * @brief Phrase for commands with incorrect parameter counts.
         */
        static constexpr auto BAD_PARAMETER_COUNT = "The provided command has an incorrect number of parameters. ";

        /**
         * @brief Phrase for host resolution failure.
         */
        static constexpr auto HOST_RESOLUTION_FAILURE = "We are currently unable to establish connection with the server due to host resolution failure. Please verify that the server address provided is correct. ";

        /**
         * @brief Phrase for failure to send data to the server.
         */
        static constexpr auto SEND_FAILURE = "Failed to send data to the server. ";

        /**
         * @brief Phrase for failure to receive data from the server.
         */
        static constexpr auto RECEIVE_FAILURE = "Failed to receive data from the server. ";

        /**
         * @brief Phrase for malformed messages received from the server.
         */
        static constexpr auto MALFORMED_MESSAGE = "The client received a malformed message from the server. ";

        /**
         * @brief Phrase indicating the server has closed the connection.
         */
        static constexpr auto SERVER_CLOSURE = "The server has closed the connection. Further communication is not possible. ";

        /**
         * @brief Phrase for invalid characters in message parameters.
         */
        static constexpr auto BAD_CHARACTERS = "Some of the provided message parameters contain invalid characters. ";

        /**
         * @brief Phrase for invalid length of message parameters.
         */
        static constexpr auto BAD_LENGTH = "Some of the provided message parameters have invalid length. ";

        /**
         * @brief Phrase indicating a parameter will be truncated to the maximum allowed length.
         */
        static constexpr auto TRUNCATION = "The invalid parameter will be shortened to the maximum allowed length. The truncated parameter is: ";

        /**
         * @brief Phrase indicating that the server isn't behaving properly.
         */
        static constexpr auto NOT_PROPER_BEHAVIOUR = "This is not a proper behaviour, which means the connection might be compromised. ";

        /**
         * @brief Phrase indicating a server reply was received in OPEN state, which isn't a proper behaviour.
         */
        static constexpr auto REPLY_IN_OPEN = "The client received an unexpected reply from the server while in OPEN state. ";

        /**
         * @brief Phrase indicating a server message was received in AUTH state, which isn't a proper behaviour.
         */
        static constexpr auto MSG_IN_AUTH = "The client received an unexpected message from the server while in AUTH state. ";


    }; // ClientInternalErrorPhrases
} // IPK25ChatClient::Enums

#endif // CLIENT_INTERNAL_ERROR_PHRASES_HPP

/*** end of file ClientInternalErrorPhrases.hpp ***/
