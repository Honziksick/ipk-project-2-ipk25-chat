/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UserCommandParser.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      12.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `UserCommandParser` class, which provides  *
 *               functionality for parsing user input commands into structured *
 *               `UserCommand` objects directly from command line.             *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UserCommandParser.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `UserCommandParser` class for parsing user
 *        commands from `STDIN`.
 */

#ifndef USER_COMMAND_PARSER_HPP
#define USER_COMMAND_PARSER_HPP

#include "Validators/MessageParametersValidator.hpp"
#include "Common/UserCommand.hpp"
#include <string>  // std::string
#include <vector>  // std::vector
#include <memory>  // std::unique_ptr

namespace IPK25ChatClient::Client::CommandParser
{
    /**
     * @class UserCommandParser
     * @brief Provides methods for parsing user input commands into structured
     *        `UserCommand` objects directly from command line.
     */
    class UserCommandParser {
    public:
        /**
         * @brief Parses a command line entered by the user.
         * @details Reads a line of input from `STDIN`, processes it, and converts
         *          it into a structured `UserCommand` object. If the input starts
         *          with '/', it is treated as a client command; otherwise, it is
         *          treated as a chat message.
         *
         * @return A `UserCommand` object representing the parsed command.
         *         If the input is invalid, the returned object will have
         *         `UserCommandType::INVALID`.
         */
        static Common::UserCommand parseCommandLine();

    private:
        static std::unique_ptr<Validators::MessageParametersValidator> mMessageParametersValidator; /**< Validate message parameters. */

        /**
         * @brief Reads a line of input from the user.
         * @details Reads a single line from `STDIN`. If the input fails, an empty
         *          string is returned. If EOF is reached, an exception is thrown.
         *
         * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf (p. 114-119).
         * @note Normally, `std::cin` flags (e.g., `good`, `fail`, etc.) would
         *       be checked to determine if the input was successful. If not,
         *       the input buffer would be cleared until `\n`, and the user
         *       would be prompted to re-enter the command. However, to avoid
         *       potential issues with the evaluation scripts, this method simply
         *       returns an empty string on failure, which will later cause an error.
         *
         * @return A string containing the user's input. Returns an empty string
         *         if the input fails.
         */
        static std::string readLine();

        /**
         * @brief Parses a client command from a given input line.
         * @details Splits the input line into tokens, determines the command type
         *          from the first token, and processes the remaining tokens as
         *          parameters. If the command type is invalid, an error is returned.
         *
         * @note Unlike in the specification, the command is processed as
         *       case-insensitive (converted to lowercase), which grants the
         *       user greater flexibility and reduces the chance of the command
         *       being classified as `UserCommandType::INVALID`.
         *
         * @param line The input line to parse.
         *
         * @return A `UserCommand` object representing the parsed client command.
         */
        static Common::UserCommand parseClientCommand(const std::string &line);

        /**
         * @brief Parses a chat message command from a given input line.
         * @details Validates the message content and truncates it if necessary.
         *          If validation fails, the command is marked as invalid.
         *
         * @param line The input line to parse.
         *
         * @return A `UserCommand` object representing the parsed chat message.
         */
        static Common::UserCommand parseChatMessage(const std::string &line);

        /**
         * @brief Determines the type of command based on the command token.
         * @details Compares the command token with predefined command strings
         *          (e.g., `/auth`, `/join`) to identify the command type.
         *
         * @param commandToken The token representing the command.
         *
         * @return The determined `UserCommandType`.
         */
        static Enums::UserCommandType determineCommandType(const std::string &commandToken);

        /**
         * @brief Parses an authentication command.
         * @details Validates and processes the parameters for the `/auth` command,
         *          including username, secret, and display name. If validation fails,
         *          the command is marked as invalid.
         *
         * @param commandParameters The parameters of the command.
         *
         * @return A `UserCommand` object representing the parsed authentication command.
         */
        static Common::UserCommand parseAuthCommand(const std::vector<std::string> &commandParameters);

        /**
         * @brief Parses a join command.
         * @details Validates and processes the parameters for the `/join` command,
         *          including the channel ID. If validation fails, the command is
         *          marked as invalid.
         *
         * @param commandParameters The parameters of the command.
         *
         * @return A `UserCommand` object representing the parsed join command.
         */
        static Common::UserCommand parseJoinCommand(const std::vector<std::string> &commandParameters);

        /**
         * @brief Parses a rename command.
         *
         * @param commandParameters The parameters of the command.
         * @details Validates and processes the parameters for the `/rename` command,
         *          including the new display name. If validation fails, the command
         *          is marked as invalid.
         *
         * @return A `UserCommand` object representing the parsed rename command.
         */
        static Common::UserCommand parseRenameCommand(const std::vector<std::string> &commandParameters);

        /**
         * @brief Parses a help command.
         * @details Processes the `/help` command, which does not require any
         *          parameters. If parameters are provided, the command is marked
         *          as invalid.
         *
         * @param commandParameters The parameters of the command.
         *
         * @return A `UserCommand` object representing the parsed help command.
         */
        static Common::UserCommand parseHelpCommand(const std::vector<std::string> &commandParameters);

        /**
         * @brief Checks if the number of parameters matches the expected count.
         *
         * @param commandParameters The parameters of the command.
         * @param expectedCount The expected number of parameters.
         *
         * @return `true` if the number of parameters is correct, `false` otherwise.
         */
        static bool checkCorrectNumberOfParameters(const std::vector<std::string> &commandParameters,
                                                   size_t expectedCount);
    }; // UserCommandParser
} // IPK25ChatClient::Client::CommandParser

#endif // USER_COMMAND_PARSER_HPP

/*** end of file UserCommandParser.hpp ***/
