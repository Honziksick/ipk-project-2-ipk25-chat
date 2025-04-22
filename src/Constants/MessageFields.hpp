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
 * Last edit:    20.04.2025                                                    *
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
        static constexpr size_t TCP_EXPECTED_ERR_MESSAGE_FIELDS = 5;      /**< ERR   message structure: ERR FROM {DisplayName} IS {MessageContent}      */
        static constexpr size_t TCP_EXPECTED_REPLY_MESSAGE_FIELDS = 4;    /**< REPLY message structure: REPLY {"OK"|"NOK"} IS {MessageContent}          */
        static constexpr size_t TCP_EXPECTED_AUTH_MESSAGE_FIELDS = 6;     /**< AUTH  message structure: AUTH {Username} AS {DisplayName} USING {Secret} */
        static constexpr size_t TCP_EXPECTED_JOIN_MESSAGE_FIELDS = 4;     /**< JOIN  message structure: JOIN {ChannelID} AS {DisplayName}               */
        static constexpr size_t TCP_EXPECTED_MSG_MESSAGE_FIELDS = 5;      /**< MSG   message structure: MSG FROM {DisplayName} IS {MessageContent}      */
        static constexpr size_t TCP_EXPECTED_BYE_MESSAGE_FIELDS = 3;      /**< BYE   message structure: BYE FROM {DisplayName}                          */

        // UDP message structure (Message = Header + Fields; Header = {Type}/1 {MessageID}/2
        static constexpr size_t UDP_CHAT_HEADER_SIZE = 3;                 /**< HEADER  message structure: {Type}/1 {MessageID}/2                                                  */
        static constexpr size_t UDP_EXPECTED_ERR_MESSAGE_FIELDS = 2;      /**< ERR     message structure: {Type}/1 {MessageID}/2 {DisplayName}/X0 {MessageContent}/X0             */
        static constexpr size_t UDP_EXPECTED_REPLY_MESSAGE_FIELDS = 3;    /**< REPLY   message structure: {Type}/1 {MessageID}/2 {Result}/1 {Ref_MessageID}/2 {MessageContent}/X0 */
        static constexpr size_t UDP_EXPECTED_AUTH_MESSAGE_FIELDS = 3;     /**< AUTH    message structure: {Type}/1 {MessageID}/2 {Username}/X0 {DisplayName}/X0 {Secret}/X0       */
        static constexpr size_t UDP_EXPECTED_JOIN_MESSAGE_FIELDS = 2;     /**< JOIN    message structure: {Type}/1 {MessageID}/2 {ChannelID}/X0 {DisplayName}/X0      */
        static constexpr size_t UDP_EXPECTED_MSG_MESSAGE_FIELDS = 2;      /**< MSG     message structure: {Type}/1 {MessageID}/2 {DisplayName}/X0 {MessageContent}/X0 */
        static constexpr size_t UDP_EXPECTED_BYE_MESSAGE_FIELDS = 1;      /**< BYE     message structure: {Type}/1 {MessageID}/2 {DisplayName}/X0 */
        static constexpr size_t UDP_EXPECTED_CONFIRM_MESSAGE_FIELDS = 0;  /**< CONFIRM message structure: {Type}/1 {Ref_MessageID}/2 */
        static constexpr size_t UDP_EXPECTED_PING_MESSAGE_FIELDS = 0;     /**< PING    message structure: {Type}/1 {MessageID}/2     */

        // AUTH message indexes (TCP)
        static constexpr size_t TCP_AUTH_TYPE_INDEX = 0;              /**< Index of the message type in an AUTH message (TCP).        */
        static constexpr size_t TCP_AUTH_USERNAME_INDEX = 1;          /**< Index of the username in an AUTH message (TCP).            */
        static constexpr size_t TCP_AUTH_AS_KEYWORD_INDEX = 2;        /**< Index of the "AS" keyword in an AUTH message (TCP).        */
        static constexpr size_t TCP_AUTH_DISPLAY_NAME_INDEX = 3;      /**< Index of the display name in an AUTH message (TCP).        */
        static constexpr size_t TCP_AUTH_USING_KEYWORD_INDEX = 4;     /**< Index of the "USING" keyword in an AUTH message (TCP).     */
        static constexpr size_t TCP_AUTH_SECRET_INDEX = 5;            /**< Index of the secret in an AUTH message (TCP).              */

        // JOIN message indexes (TCP)
        static constexpr size_t TCP_JOIN_TYPE_INDEX = 0;              /**< Index of the message type in a JOIN message (TCP).         */
        static constexpr size_t TCP_JOIN_CHANNEL_ID_INDEX = 1;        /**< Index of the channel ID in a JOIN message (TCP).           */
        static constexpr size_t TCP_JOIN_AS_KEYWORD_INDEX = 2;        /**< Index of the "AS" keyword in a JOIN message (TCP).         */
        static constexpr size_t TCP_JOIN_DISPLAY_NAME_INDEX = 3;      /**< Index of the display name in a JOIN message (TCP).         */

        // ERR message indexes (TCP)
        static constexpr size_t TCP_ERR_TYPE_INDEX = 0;               /**< Index of the message type in an ERR message (TCP).         */
        static constexpr size_t TCP_ERR_FROM_KEYWORD_INDEX = 1;       /**< Index of the "FROM" keyword in an ERR message (TCP).       */
        static constexpr size_t TCP_ERR_DISPLAY_NAME_INDEX = 2;       /**< Index of the display name in an ERR message (TCP).         */
        static constexpr size_t TCP_ERR_IS_KEYWORD_INDEX = 3;         /**< Index of the "IS" keyword in an ERR message (TCP).         */
        static constexpr size_t TCP_ERR_MESSAGE_CONTENT_INDEX = 4;    /**< Index of the message content in an ERR message (TCP).      */

        // BYE message indexes (TCP)
        static constexpr size_t TCP_BYE_TYPE_INDEX = 0;               /**< Index of the message type in a BYE message (TCP).          */
        static constexpr size_t TCP_BYE_FROM_KEYWORD_INDEX = 1;       /**< Index of the "FROM" keyword in a BYE message (TCP).        */
        static constexpr size_t TCP_BYE_DISPLAY_NAME_INDEX = 2;       /**< Index of the display name in a BYE message (TCP).          */

        // REPLY message indexes (TCP)
        static constexpr size_t TCP_REPLY_TYPE_INDEX = 0;             /**< Index of the message type in a REPLY message (TCP).        */
        static constexpr size_t TCP_REPLY_RESULT_KEYWORD_INDEX = 1;   /**< Index of the result ("OK"/"NOK") in a REPLY message (TCP). */
        static constexpr size_t TCP_REPLY_IS_KEYWORD_INDEX = 2;       /**< Index of the "IS" keyword in a REPLY message (TCP).        */
        static constexpr size_t TCP_REPLY_MESSAGE_CONTENT_INDEX = 3;  /**< Index of the message content in a REPLY message (TCP).     */

        // MSG message indexes (TCP)
        static constexpr size_t TCP_MSG_TYPE_INDEX = 0;               /**< Index of the message type in a MSG message (TCP).          */
        static constexpr size_t TCP_MSG_FROM_KEYWORD_INDEX = 1;       /**< Index of the "FROM" keyword in a MSG message (TCP).        */
        static constexpr size_t TCP_MSG_DISPLAY_NAME_INDEX = 2;       /**< Index of the display name in a MSG message (TCP).          */
        static constexpr size_t TCP_MSG_IS_KEYWORD_INDEX = 3;         /**< Index of the "IS" keyword in a MSG message (TCP).          */
        static constexpr size_t TCP_MSG_MESSAGE_CONTENT_INDEX = 4;    /**< Index of the message content in a MSG message (TCP).       */

        // UDP HEADER byte indexes
        static constexpr size_t UDP_TYPE_START_BYTE = 0;              /**< Starting index of the type in a UDP message (vector).      */
        static constexpr size_t UDP_MESSAGE_ID_START_BYTE = 1;        /**< Starting index of the messageID in a UDP message (vector). */

        // AUTH message indexes (UDP)
        static constexpr size_t UDP_AUTH_USERNAME_INDEX = 0;          /**< Index of the username in an AUTH message (UDP).            */
        static constexpr size_t UDP_AUTH_DISPLAY_NAME_INDEX = 1;      /**< Index of the display name in an AUTH message (UDP).        */
        static constexpr size_t UDP_AUTH_SECRET_INDEX = 2;            /**< Index of the secret in an AUTH message (UDP).              */

        // JOIN message indexes (UDP)
        static constexpr size_t UDP_JOIN_CHANNEL_ID_INDEX = 0;        /**< Index of the channel ID in a JOIN message (UDP).           */
        static constexpr size_t UDP_JOIN_DISPLAY_NAME_INDEX = 1;      /**< Index of the display name in a JOIN message (UDP).         */

        // ERR message indexes (UDP)
        static constexpr size_t UDP_ERR_DISPLAY_NAME_INDEX = 0;       /**< Index of the display name in an ERR message (UDP).         */
        static constexpr size_t UDP_ERR_MESSAGE_CONTENT_INDEX = 1;    /**< Index of the message content in an ERR message (UDP).      */

        // BYE message indexes (UDP)
        static constexpr size_t UDP_BYE_DISPLAY_NAME_INDEX = 0;       /**< Index of the display name in a BYE message (UDP).          */

        // REPLY message indexes (UDP)
        static constexpr size_t UDP_REPLY_RESULT_KEYWORD_INDEX = 0;   /**< Index of the result ("OK"/"NOK") in a REPLY message (UDP). */
        static constexpr size_t UDP_REPLY_REF_MESSAGE_ID_INDEX = 1;   /**< Index of the message the server is replying to (UDP).      */
        static constexpr size_t UDP_REPLY_MESSAGE_CONTENT_INDEX = 2;  /**< Index of the message content in a REPLY message (UDP).     */

        // MSG message indexes (UDP)
        static constexpr size_t UDP_MSG_DISPLAY_NAME_INDEX = 0;       /**< Index of the display name in a MSG message (UDP).          */
        static constexpr size_t UDP_MSG_MESSAGE_CONTENT_INDEX = 1;    /**< Index of the message content in a MSG message (UDP).       */
    }; // MessageFields
} // IPK25ChatClient::Constants

#endif // MESSAGE_FIELDS_HPP

/*** end of file MessageFields.hpp ***/
