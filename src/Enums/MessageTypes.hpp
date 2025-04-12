/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageTypes.hpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      07.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines the enumeration `MessageType` for           *
 *               different types of messages used in the IPK25 Chat Client.    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageTypes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the enumeration `MessageType` for different
 *        types of messages used in the IPK25 Chat Client.
 */

#ifndef MESSAGE_TYPES_HPP
#define MESSAGE_TYPES_HPP

#include <cstdint>  // uint8_t

namespace IPK25ChatClient::Enums
{
    /**
     * @enum MessageType
     * @brief Enumeration of the message types used in the IPK25 Chat Client.
     */
    enum class MessageType : uint8_t {
        UNKNOWN = 0xAA,    /**< Message type not yet resolved.                                                                          */
        CONFIRM = 0x00,    /**< Explicitly confirms the successful delivery of the message to the other party on the application level. */
        REPLY   = 0x01,    /**< Either party can send this message to indicate that the conversation/connection is to be terminated.    */
        AUTH    = 0x02,    /**< Used for client authentication (signing in) using a user-provided username, display name and password.  */
        JOIN    = 0x03,    /**< Represents the client's request to join a chat channel by its identifier.                               */
        MSG     = 0x04,    /**< Contains user display name and a message designated for the channel they're joined in.                  */
        PING    = 0xFD,    /**< Periodically sent by a server as an aliveness check mechanism.                                          */
        ERR     = 0xFE,    /**< Indicates that an error has occurred while processing the other party's last message.                   */
        BYE     = 0xFF     /**< Either party can send this message to indicate that the conversation/connection is to be terminated.    */
    }; // MessageType
} // IPK25ChatClient::Enums

#endif // MESSAGE_TYPES_HPP

/*** end of file MessageTypes.hpp ***/
