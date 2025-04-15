/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageFields.hpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    16.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines constants for the expected number of        *
 *               fields in various message types and their respective field    *
 *               indexes for both TCP and UDP communication protocols.         *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageFields.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining constants for message field counts and indexes
 *        for TCP and UDP protocols.
 */

#ifndef MESSAGE_FIELDS_HPP
#define MESSAGE_FIELDS_HPP

namespace IPK25ChatClient::Constants
{
    class MessageFields {
    public:
        // TCP message structure
        static constexpr size_t TCP_EXPECTED_ERR_MESSAGE_FIELDS = 5;    /**< ERR   message structure: ERR FROM {DisplayName} IS {MessageContent}      */
        static constexpr size_t TCP_EXPECTED_REPLY_MESSAGE_FIELDS = 4;  /**< REPLY message structure: REPLY {"OK"|"NOK"} IS {MessageContent}          */
        static constexpr size_t TCP_EXPECTED_AUTH_MESSAGE_FIELDS = 6;   /**< AUTH  message structure: AUTH {Username} AS {DisplayName} USING {Secret} */
        static constexpr size_t TCP_EXPECTED_JOIN_MESSAGE_FIELDS = 4;   /**< JOIN  message structure: JOIN {ChannelID} AS {DisplayName}               */
        static constexpr size_t TCP_EXPECTED_MSG_MESSAGE_FIELDS = 5;    /**< MSG   message structure: MSG FROM {DisplayName} IS {MessageContent}      */
        static constexpr size_t TCP_EXPECTED_BYE_MESSAGE_FIELDS = 3;    /**< BYE   message structure: BYE FROM {DisplayName}                          */

        // UDP message structure
        static constexpr size_t UDP_EXPECTED_ERR_MESSAGE_FIELDS = 4;      /**< ERR     message structure: {Type} {MessageID} {DisplayName} {MessageContent}            */
        static constexpr size_t UDP_EXPECTED_REPLY_MESSAGE_FIELDS = 5;    /**< REPLY   message structure: {Type} {MessageID} {Result} {Ref_MessageID} {MessageContent} */
        static constexpr size_t UDP_EXPECTED_AUTH_MESSAGE_FIELDS = 5;     /**< AUTH    message structure: {Type} {MessageID} {Username} {DisplayName} {Secret}         */
        static constexpr size_t UDP_EXPECTED_JOIN_MESSAGE_FIELDS = 4;     /**< JOIN    message structure: {Type} {MessageID} {ChannelID} {DisplayName}      */
        static constexpr size_t UDP_EXPECTED_MSG_MESSAGE_FIELDS = 4;      /**< MSG     message structure: {Type} {MessageID} {DisplayName} {MessageContent} */
        static constexpr size_t UDP_EXPECTED_BYE_MESSAGE_FIELDS = 3;      /**< BYE     message structure: {Type} {MessageID} {DisplayName} */
        static constexpr size_t UDP_EXPECTED_CONFIRM_MESSAGE_FIELDS = 2;  /**< CONFIRM message structure: {Type} {Ref_MessageID} */
        static constexpr size_t UDP_EXPECTED_PING_MESSAGE_FIELDS = 2;     /**< PING    message structure: {Type} {MessageID}     */

        // AUTH message indexes (TCP)
        static constexpr size_t TCP_AUTH_TYPE_INDEX = 0;           /**< Index of the message type in an AUTH message (TCP).    */
        static constexpr size_t TCP_AUTH_USERNAME_INDEX = 1;       /**< Index of the username in an AUTH message (TCP).        */
        static constexpr size_t TCP_AUTH_AS_KEYWORD_INDEX = 2;     /**< Index of the "AS" keyword in an AUTH message (TCP).    */
        static constexpr size_t TCP_AUTH_DISPLAY_NAME_INDEX = 3;   /**< Index of the display name in an AUTH message (TCP).    */
        static constexpr size_t TCP_AUTH_USING_KEYWORD_INDEX = 4;  /**< Index of the "USING" keyword in an AUTH message (TCP). */
        static constexpr size_t TCP_AUTH_SECRET_INDEX = 5;         /**< Index of the secret in an AUTH message (TCP).          */

        // JOIN message indexes (TCP)
        static constexpr size_t TCP_JOIN_TYPE_INDEX = 0;          /**< Index of the message type in a JOIN message (TCP). */
        static constexpr size_t TCP_JOIN_CHANNEL_ID_INDEX = 1;    /**< Index of the channel ID in a JOIN message (TCP).   */
        static constexpr size_t TCP_JOIN_AS_KEYWORD_INDEX = 2;    /**< Index of the "AS" keyword in a JOIN message (TCP). */
        static constexpr size_t TCP_JOIN_DISPLAY_NAME_INDEX = 3;  /**< Index of the display name in a JOIN message (TCP). */

        // ERR message indexes (TCP)
        static constexpr size_t TCP_ERR_TYPE_INDEX = 0;             /**< Index of the message type in an ERR message (TCP).    */
        static constexpr size_t TCP_ERR_FROM_KEYWORD_INDEX = 1;     /**< Index of the "FROM" keyword in an ERR message (TCP).  */
        static constexpr size_t TCP_ERR_DISPLAY_NAME_INDEX = 2;     /**< Index of the display name in an ERR message (TCP).    */
        static constexpr size_t TCP_ERR_IS_KEYWORD_INDEX = 3;       /**< Index of the "IS" keyword in an ERR message (TCP).    */
        static constexpr size_t TCP_ERR_MESSAGE_CONTENT_INDEX = 4;  /**< Index of the message content in an ERR message (TCP). */

        // BYE message indexes (TCP)
        static constexpr size_t TCP_BYE_TYPE_INDEX = 0;          /**< Index of the message type in a BYE message (TCP).   */
        static constexpr size_t TCP_BYE_FROM_KEYWORD_INDEX = 1;  /**< Index of the "FROM" keyword in a BYE message (TCP). */
        static constexpr size_t TCP_BYE_DISPLAY_NAME_INDEX = 2;  /**< Index of the display name in a BYE message (TCP).   */

        // REPLY message indexes (TCP)
        static constexpr size_t TCP_REPLY_TYPE_INDEX = 0;             /**< Index of the message type in a REPLY message (TCP).        */
        static constexpr size_t TCP_REPLY_RESULT_KEYWORD_INDEX = 1;   /**< Index of the result ("OK"/"NOK") in a REPLY message (TCP). */
        static constexpr size_t TCP_REPLY_IS_KEYWORD_INDEX = 2;       /**< Index of the "IS" keyword in a REPLY message (TCP).        */
        static constexpr size_t TCP_REPLY_MESSAGE_CONTENT_INDEX = 3;  /**< Index of the message content in a REPLY message (TCP).     */

        // MSG message indexes (TCP)
        static constexpr size_t TCP_MSG_TYPE_INDEX = 0;             /**< Index of the message type in a MSG message (TCP).    */
        static constexpr size_t TCP_MSG_FROM_KEYWORD_INDEX = 1;     /**< Index of the "FROM" keyword in a MSG message (TCP).  */
        static constexpr size_t TCP_MSG_DISPLAY_NAME_INDEX = 2;     /**< Index of the display name in a MSG message (TCP).    */
        static constexpr size_t TCP_MSG_IS_KEYWORD_INDEX = 3;       /**< Index of the "IS" keyword in a MSG message (TCP).    */
        static constexpr size_t TCP_MSG_MESSAGE_CONTENT_INDEX = 4;  /**< Index of the message content in a MSG message (TCP). */

        // TODO: Set the correct indexes for the UDP message types when implementing UDPMessagingValidator
        // AUTH message indexes (UDP)
        static constexpr size_t UDP_AUTH_TYPE_INDEX = 0;           /**< Index of the message type in an AUTH message (UDP).    */
        static constexpr size_t UDP_AUTH_USERNAME_INDEX = 1;       /**< Index of the username in an AUTH message (UDP).        */
        static constexpr size_t UDP_AUTH_AS_KEYWORD_INDEX = 2;     /**< Index of the "AS" keyword in an AUTH message (UDP).    */
        static constexpr size_t UDP_AUTH_DISPLAY_NAME_INDEX = 3;   /**< Index of the display name in an AUTH message (UDP).    */
        static constexpr size_t UDP_AUTH_USING_KEYWORD_INDEX = 4;  /**< Index of the "USING" keyword in an AUTH message (UDP). */
        static constexpr size_t UDP_AUTH_SECRET_INDEX = 5;         /**< Index of the secret in an AUTH message (UDP).          */

        // JOIN message indexes (UDP)
        static constexpr size_t UDP_JOIN_TYPE_INDEX = 0;          /**< Index of the message type in a JOIN message (UDP). */
        static constexpr size_t UDP_JOIN_CHANNEL_ID_INDEX = 1;    /**< Index of the channel ID in a JOIN message (UDP).   */
        static constexpr size_t UDP_JOIN_AS_KEYWORD_INDEX = 2;    /**< Index of the "AS" keyword in a JOIN message (UDP). */
        static constexpr size_t UDP_JOIN_DISPLAY_NAME_INDEX = 3;  /**< Index of the display name in a JOIN message (UDP). */

        // ERR message indexes (UDP)
        static constexpr size_t UDP_ERR_TYPE_INDEX = 0;             /**< Index of the message type in an ERR message (UDP).    */
        static constexpr size_t UDP_ERR_FROM_KEYWORD_INDEX = 1;     /**< Index of the "FROM" keyword in an ERR message (UDP).  */
        static constexpr size_t UDP_ERR_DISPLAY_NAME_INDEX = 2;     /**< Index of the display name in an ERR message (UDP).    */
        static constexpr size_t UDP_ERR_IS_KEYWORD_INDEX = 3;       /**< Index of the "IS" keyword in an ERR message (UDP).    */
        static constexpr size_t UDP_ERR_MESSAGE_CONTENT_INDEX = 4;  /**< Index of the message content in an ERR message (UDP). */

        // BYE message indexes (UDP)
        static constexpr size_t UDP_BYE_TYPE_INDEX = 0;          /**< Index of the message type in a BYE message (UDP).   */
        static constexpr size_t UDP_BYE_FROM_KEYWORD_INDEX = 1;  /**< Index of the "FROM" keyword in a BYE message (UDP). */
        static constexpr size_t UDP_BYE_DISPLAY_NAME_INDEX = 2;  /**< Index of the display name in a BYE message (UDP).   */

        // REPLY message indexes (UDP)
        static constexpr size_t UDP_REPLY_TYPE_INDEX = 0;             /**< Index of the message type in a REPLY message (UDP).        */
        static constexpr size_t UDP_REPLY_RESULT_KEYWORD_INDEX = 1;   /**< Index of the result ("OK"/"NOK") in a REPLY message (UDP). */
        static constexpr size_t UDP_REPLY_IS_KEYWORD_INDEX = 2;       /**< Index of the "IS" keyword in a REPLY message (UDP).        */
        static constexpr size_t UDP_REPLY_MESSAGE_CONTENT_INDEX = 3;  /**< Index of the message content in a REPLY message (UDP).     */

        // MSG message indexes (UDP)
        static constexpr size_t UDP_MSG_TYPE_INDEX = 0;             /**< Index of the message type in a MSG message (UDP).    */
        static constexpr size_t UDP_MSG_FROM_KEYWORD_INDEX = 1;     /**< Index of the "FROM" keyword in a MSG message (UDP).  */
        static constexpr size_t UDP_MSG_DISPLAY_NAME_INDEX = 2;     /**< Index of the display name in a MSG message (UDP).    */
        static constexpr size_t UDP_MSG_IS_KEYWORD_INDEX = 3;       /**< Index of the "IS" keyword in a MSG message (UDP).    */
        static constexpr size_t UDP_MSG_MESSAGE_CONTENT_INDEX = 4;  /**< Index of the message content in a MSG message (UDP). */

        // CONFIRM message indexes (UDP)

        // PING message indexes (UDP)
    }; // MessageFields
} // IPK25ChatClient::Constants

#endif // MESSAGE_FIELDS_HPP

/*** end of file MessageFields.hpp ***/
