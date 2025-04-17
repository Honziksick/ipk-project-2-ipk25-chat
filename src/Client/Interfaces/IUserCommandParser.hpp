/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IUserCommandParser.hpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      16.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Interface for parsing user commands in the IPK25 Chat Client. *
 *               Provides a method to process user input and convert it into   *
 *               structured commands or messages.                              *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IUserCommandParser.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `IUserCommandParser` interface for parsing
 *        user commands in the IPK25 Chat Client.
 */

#ifndef I_USER_COMMAND_PARSER_HPP
#define I_USER_COMMAND_PARSER_HPP

#include "Common/UserCommand.hpp"

namespace IPK25ChatClient::Client::CommandParser
{
    /**
     * @class IUserCommandParser
     * @brief Interface for parsing user commands in the chat client.
     */
    class IUserCommandParser {
    public:
        /**
         * @brief Virtual destructor for the `IUserCommandParser` interface.
         */
        virtual ~IUserCommandParser() = default;

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
        virtual Common::UserCommand parseCommandLine() = 0;
    }; // IUserCommandParser
} // IPK25ChatClient::Client::CommandParser

#endif // I_USER_COMMAND_PARSER_HPP

/*** end of file IUserCommandParser.hpp ***/
