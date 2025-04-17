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
 * Last edit:    16.04.2025                                                    *
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

#include <string>       // std::string
#include <string_view>  // std::string_view

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
         * @brief Prints a reply message from the server.
         * @details Format: `Action [Succes|Failure]: {MessageContent}\n`
         *
         * @param result The result of the reply (e.g., "OK" or "NOK").
         * @param messageContent The content of the reply message.
         */
        static void printClientReply(const std::string &result,
                                     const std::string &messageContent);

        /**
         * @brief Prints the help message for the client.
         * @details This method outputs a detailed help message to the standard
         *          output, describing the usage of various client commands and
         *          their examples.
         */
        static void printClientHelp();

    private:
        /**
         * @brief A constant string containing the help message for the client.
         * @details The message includes usage instructions, descriptions of commands,
         *          and examples for interacting with the chat client.
         *
         * @note Used ChatGPT for grammar and spelling check.
         */
        static constexpr auto CLIENT_HELP_MESSAGE = R"(
Usage:
/auth <username> <secret> <displayName>
    Authenticate with the chat server using your account name, password (secret) and the display name you wish to use.

/join <channelId>
    Join or switch to the specified channel. If you omit this, you stay in the default channel assigned after AUTH.

/rename <newDisplayName>
    Change your display name for subsequent messages.

/help
    Show this help message.

/bye
    Exit the chat client gracefully (sends BYE to server and closes connection).

Chatting:
    To send a message to the current channel, just type your text without a leading slash and press Enter.
    Messages longer than the protocol‐allowed maximum will be truncated and you will see a local warning.

Examples:
    /auth alice p@ssw0rd AliceWonder
    /join general
    Hello everyone!
    /rename Alice
    /bye)"; // CLIENT_HELP_MESSAGE
    }; // ClientOutput
} // IPK25ChatClient::Client::Output

#endif // CLIENT_OUTPUT_HPP

/*** end of file ClientOutput.hpp ***/
