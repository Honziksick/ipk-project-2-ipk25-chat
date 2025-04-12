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
 * Last edit:    12.04.2025                                                    *
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
        static constexpr unsigned int MIN_SERVER_PORT = 1;  /**< Minimum server port number (port 0 is reserved and thus not allowed). */
        static constexpr unsigned int MAX_SERVER_PORT = std::numeric_limits<uint16_t>::max();  /**< Maximum server port number. */

        static constexpr unsigned int MIN_UDP_RETRANSMIT = std::numeric_limits<uint8_t>::min();   /**< Minimum number of UDP retransmissions. */
        static constexpr unsigned int MAX_UDP_RETRANSMIT = std::numeric_limits<uint8_t>::max();   /**< Maximum number of UDP retransmissions. */

        static constexpr unsigned int MIN_UDP_TIMEOUT_MS = std::numeric_limits<uint16_t>::min();  /**< Minimum UDP timeout in milliseconds. */
        static constexpr unsigned int MAX_UDP_TIMEOUT_MS = std::numeric_limits<uint16_t>::max();  /**< Maximum UDP timeout in milliseconds. */

        static constexpr unsigned int MIN_USERNAME_LENGTH = 1;             /**< Minimum length of the username. */
        static constexpr unsigned int MAX_USERNAME_LENGTH = 20;            /**< Maximum length of the username. */

        static constexpr unsigned int MIN_CHANNEL_ID_LENGTH = 1;           /**< Minimum length of the channel ID. */
        static constexpr unsigned int MAX_CHANNEL_ID_LENGTH = 20;          /**< Maximum length of the channel ID. */

        static constexpr unsigned int MIN_SECRET_LENGTH = 1;               /**< Minimum length of the secret. */
        static constexpr unsigned int MAX_SECRET_LENGTH = 128;             /**< Maximum length of the secret. */

        static constexpr unsigned int MIN_DISPLAY_NAME_LENGTH = 1;         /**< Minimum length of the display name. */
        static constexpr unsigned int MAX_DISPLAY_NAME_LENGTH = 20;        /**< Maximum length of the display name. */

        static constexpr unsigned int MIN_MESSAGE_CONTENT_LENGTH = 1;      /**< Minimum length of the message content. */
        static constexpr unsigned int MAX_MESSAGE_CONTENT_LENGTH = 60000;  /**< Maximum length of the message content. */
    }; // ClientLimits
} // IPK25ChatClient::Constants

#endif // CLIENT_LIMITS_HPP

/*** end of file ClientLimits.hpp ***/
