/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientOutput.hpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the ClientOutput class, which provides        *
 *               static methods for printing various types of client           *
 *               messages and errors to the standard output.                   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientOutput.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `ClientOutput` class, which provides static
 *        methods for printing client messages and errors.
 */

#ifndef CLIENT_OUTPUT_HPP
#define CLIENT_OUTPUT_HPP

#include <string>  // std::string_view

namespace IPK25ChatClient::Client::Output
{
    /**
     * @class ClientOutput
     * @brief Provides static methods for printing client messages and errors.
     */
    class ClientOutput final {
    public:
        /**
         * @brief Prints an incoming message from another client.
         * @details Format: `{DisplayName}: {MessageContent}\n`
         *
         * @param displayName The display name of the sender.
         * @param messageContent The content of the incoming message.
         */
        static void printClientIncomingMessage(const std::string_view &displayName,
                                               const std::string_view &messageContent);

        /**
         * @brief Prints an incoming error message from another client.
         * @details Format: `ERROR FROM {DisplayName}: {MessageContent}\n`
         *
         * @param displayName The display name of the sender.
         * @param messageContent The content of the error message.
         */
        static void printClientIncomingError(const std::string_view &displayName,
                                             const std::string_view &messageContent);

        /**
         * @brief Prints an internal error message.
         * @details Format: `ERROR: {MessageContent}\n`
         *
         * @param messageContent The content of the internal error message.
         */
        static void printClientInternalError(const std::string_view &messageContent);

        /**
         * @brief Prints a success message for a client reply.
         * @details Format: `Action Success: {MessageContent}\n`
         *
         * @param messageContent The content of the success message.
         */
        static void printClientReplySuccess(const std::string_view &messageContent);

        /**
         * @brief Prints a failure message for a client reply.
         * @details Format: `Action Failure: {MessageContent}\n`
         *
         * @param messageContent The content of the failure message.
         */
        static void printClientReplyFailure(const std::string_view &messageContent);
    }; // ClientOutput
} // IPK25ChatClient::Client::Output

#endif // CLIENT_OUTPUT_HPP

/*** end of file ClientOutput.hpp ***/
