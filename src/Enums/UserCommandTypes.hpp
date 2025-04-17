/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UserCommandTypes.hpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      12.04.2025                                                    *
 * Last edit:    16.04.2025                                                    *
 *                                                                             *
 * Description:  Defines the enumeration for different types of client         *
 *               commands. These commands are executed by the user, hence      *
 *               the name `UserCommandType`.                                   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UserCommandTypes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the enumeration for different types of client
 *        commands.
 */

#ifndef CLIENT_COMMAND_TYPES_HPP
#define CLIENT_COMMAND_TYPES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum UserCommandType
     * @brief Enumeration of client command types.
     */
    enum class UserCommandType {
        // Helper values for the parser
        UNKNOWN = 0,  /**< Represents an unknown command.                                                       */
        INVALID,      /**< Represents an invalid command.                                                       */
        MESSAGE,      /**< Indicates that the user did not enter a command but a message to be sent.            */
        BYE,          /**< Indicates that an end of file has reached (or CTRL+D was pressed).                   */

        // Real client commands
        AUTH,         /**< \\auth: Sends AUTH message with the data provided from the command to the server.    */
        JOIN,         /**< \\join: Sends JOIN message with channel name from the command to the server.         */
        RENAME,       /**< \\rename: Locally changes the display name of the user.                              */
        HELP          /**< \\help: Prints out supported local commands with their parameters and a description. */
    }; // UserCommandType
} // IPK25ChatClient::Enums

#endif // CLIENT_COMMAND_TYPES_HPP

/*** end of file UserCommandTypes.hpp ***/
