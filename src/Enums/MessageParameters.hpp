/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageParameters.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    11.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines the `MessageParameter` enumeration, which   *
 *               represents various parameters associated with messages in     *
 *               the IPK25 Chat Client.                                        *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageParameters.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MessageParameter` enumeration for
 *        message-related parameters.
 */

#ifndef MESSAGE_PARAMETERS_HPP
#define MESSAGE_PARAMETERS_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum MessageParameter
     * @brief Represents various parameters of a message in the IPK25 Chat Client.
     */
    enum class MessageParameter {
        MESSAGE_ID = 0,    /**< Unique identifier for a message.                      */
        USERNAME,          /**< Username of the message sender.                       */
        CHANNEL_ID,        /**< Identifier of the channel where the message was sent. */
        SECRET,            /**< Secret token of the user associated with the message. */
        DISPLAY_NAME,      /**< Display name of the user.                             */
        MESSAGE_CONTENT    /**< Content of the message.                               */
    }; // MessageParameter
} // IPK25ChatClient::Enums

#endif // MESSAGE_PARAMETERS_HPP

/*** end of file MessageParameters.hpp ***/
