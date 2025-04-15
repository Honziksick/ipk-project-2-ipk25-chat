/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientLimits.hpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines various limits and constants used in the    *
 *               chat client.                                                  *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientLimits.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining various limits and constants used in the chat client.
 */

#ifndef CLIENT_LIMITS_HPP
#define CLIENT_LIMITS_HPP

#include <limits>   // std::numeric_limits
#include <cstdint>  // uint8_t, uint16_t

namespace IPK25ChatClient::Constants
{
    /**
     * @class ClientLimits
     * @brief Defines various limits and constants used in the chat client.
     */
    class ClientLimits {
    public:
        static constexpr size_t MIN_SERVER_PORT = 1;  /**< Minimum server port number (port 0 is reserved and thus not allowed). */
        static constexpr size_t MAX_SERVER_PORT = std::numeric_limits<uint16_t>::max();  /**< Maximum server port number. */

        static constexpr size_t MIN_UDP_RETRANSMIT = std::numeric_limits<uint8_t>::min();   /**< Minimum number of UDP retransmissions. */
        static constexpr size_t MAX_UDP_RETRANSMIT = std::numeric_limits<uint8_t>::max();   /**< Maximum number of UDP retransmissions. */

        static constexpr size_t MIN_UDP_TIMEOUT_MS = std::numeric_limits<uint16_t>::min();  /**< Minimum UDP timeout in milliseconds. */
        static constexpr size_t MAX_UDP_TIMEOUT_MS = std::numeric_limits<uint16_t>::max();  /**< Maximum UDP timeout in milliseconds. */

        static constexpr size_t MIN_USERNAME_LENGTH = 1;               /**< Minimum length of the username. */
        static constexpr size_t MAX_USERNAME_LENGTH = 20;              /**< Maximum length of the username. */

        static constexpr size_t MIN_CHANNEL_ID_LENGTH = 1;             /**< Minimum length of the channel ID. */
        static constexpr size_t MAX_CHANNEL_ID_LENGTH = 20;            /**< Maximum length of the channel ID. */

        static constexpr size_t MIN_SECRET_LENGTH = 1;                 /**< Minimum length of the secret. */
        static constexpr size_t MAX_SECRET_LENGTH = 128;               /**< Maximum length of the secret. */

        static constexpr size_t MIN_DISPLAY_NAME_LENGTH = 1;           /**< Minimum length of the display name. */
        static constexpr size_t MAX_DISPLAY_NAME_LENGTH = 20;          /**< Maximum length of the display name. */

        static constexpr size_t MIN_MESSAGE_CONTENT_LENGTH = 1;        /**< Minimum length of the message content. */
        static constexpr size_t MAX_MESSAGE_CONTENT_LENGTH = 60000;    /**< Maximum length of the message content. */

        static constexpr size_t EXPECTED_NUMBER_OF_AUTH_PARAMS = 3;    /**< Expected number of parameters for the /auth command (`/auth {Username} {Secret} {DisplayName}`). */
        static constexpr size_t EXPECTED_NUMBER_OF_JOIN_PARAMS = 1;    /**< Expected number of parameters for the /join command (`/join {ChannelID}`).       */
        static constexpr size_t EXPECTED_NUMBER_OF_RENAME_PARAMS = 1;  /**< Expected number of parameters for the /rename command (`/rename {DisplayName}`). */
        static constexpr size_t EXPECTED_NUMBER_OF_HELP_PARAMS = 0;    /**< Expected number of parameters for the /help command (`/help`).                   */

        static constexpr size_t TCP_EXPECTED_ERR_MESSAGE_FIELDS = 5;   /**< ERR   message structure: ERR FROM {DisplayName} IS {MessageContent}      */
        static constexpr size_t TCP_EXPECTED_REPLY_MESSAGE_FIELDS = 4; /**< REPLY message structure: REPLY {"OK"|"NOK"} IS {MessageContent}          */
        static constexpr size_t TCP_EXPECTED_AUTH_MESSAGE_FIELDS = 6;  /**< AUTH  message structure: AUTH {Username} AS {DisplayName} USING {Secret} */
        static constexpr size_t TCP_EXPECTED_JOIN_MESSAGE_FIELDS = 4;  /**< JOIN  message structure: JOIN {ChannelID} AS {DisplayName}               */
        static constexpr size_t TCP_EXPECTED_MSG_MESSAGE_FIELDS = 5;   /**< MSG   message structure: MSG FROM {DisplayName} IS {MessageContent}      */
        static constexpr size_t TCP_EXPECTED_BYE_MESSAGE_FIELDS = 3;   /**< BYE   message structure: BYE FROM {DisplayName}                          */

        static constexpr size_t UDP_EXPECTED_ERR_MESSAGE_FIELDS = 4;      /**< ERR     message structure: {Type} {MessageID} {DisplayName} {MessageContent}            */
        static constexpr size_t UDP_EXPECTED_REPLY_MESSAGE_FIELDS = 5;    /**< REPL Y  message structure: {Type} {MessageID} {Result} {Ref_MessageID} {MessageContent} */
        static constexpr size_t UDP_EXPECTED_AUTH_MESSAGE_FIELDS = 5;     /**< AUTH    message structure: {Type} {MessageID} {Username} {DisplayName} {Secret}         */
        static constexpr size_t UDP_EXPECTED_JOIN_MESSAGE_FIELDS = 4;     /**< JOIN    message structure: {Type} {MessageID} {ChannelID} {DisplayName}      */
        static constexpr size_t UDP_EXPECTED_MSG_MESSAGE_FIELDS = 4;      /**< MSG     message structure: {Type} {MessageID} {DisplayName} {MessageContent} */
        static constexpr size_t UDP_EXPECTED_BYE_MESSAGE_FIELDS = 3;      /**< BYE     message structure: {Type} {MessageID} {DisplayName} */
        static constexpr size_t UDP_EXPECTED_CONFIRM_MESSAGE_FIELDS = 2;  /**< CONFIRM message structure: {Type} {Ref_MessageID} */
        static constexpr size_t UDP_EXPECTED_PING_MESSAGE_FIELDS = 2;     /**< PING    message structure: {Type} {MessageID}     */
    }; // ClientLimits
} // IPK25ChatClient::Constants

#endif // CLIENT_LIMITS_HPP

/*** end of file ClientLimits.hpp ***/
