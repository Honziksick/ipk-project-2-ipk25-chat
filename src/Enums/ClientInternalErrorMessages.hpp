/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientInternalErrorMessages.hpp                               *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      17.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  This file defines an enumeration of various types of internal *
 *               error messages that the IPK25 Chat Client can display to the  *
 *               user.                                                         *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientInternalErrorMessages.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining an enumeration  of various types of internal
 *        error messages that can display to the user.
 */

#ifndef CLIENT_INTERNAL_ERROR_MESSAGES_HPP
#define CLIENT_INTERNAL_ERROR_MESSAGES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum ClientInternalErrorMessage
     * @brief Enumeration of internal error message types.
     *
     * @details This enum class defines various types of internal error messages
     *          that the IPK25 Chat Client can display to the user. Error messages
     *          are build from the phrases defined in the `ClientInternalErrorPhrases`
     *          class and mapped by the enum mapper.
     */
    enum class ClientInternalErrorMessage {
        CLIENT_UNKNOWN = 0,              /**< The client internal error message is not yet defined.               */
        CLIENT_INTERNAL_ERROR,           /**< Sends: INTERNAL_ERROR + SEND_ERROR_TERMINATE + APOLOGY              */
        CLIENT_CONNECTION_ERROR,         /**< Sends: CONNECTION_ISSUE + SEND_ERROR_TERMINATE                      */
        CLIENT_BAD_COMMAND,              /**< Sends: BAD_COMMAND + HELP_PROMPT                                    */
        CLIENT_BAD_CHARACTERS,           /**< Sends: BAD_CHARACTERS + HELP_PROMPT                                 */
        CLIENT_BAD_LENGTH,               /**< Sends: BAD_LENGTH + HELP_PROMPT                                     */
        CLIENT_BAD_LENGTH_TRUNCATE,      /**< Sends: BAD_LENGTH + HELP_PROMPT + TRUNCATION                        */
        CLIENT_MALFORMED_MESSAGE,        /**< Sends: MALFORMED_MESSAGE + SEND_ERROR_TERMINATE                     */
        CLIENT_HOST_RESOLUTION_FAILURE,  /**< Sends: HOST_RESOLUTION_FAILURE + DONT_SEND_ERROR_TERMINATE          */
        CLIENT_SEND_FAILURE,             /**< Sends: SEND_FAILURE + SEND_ERROR_TERMINATE                          */
        CLIENT_RECEIVE_FAILURE,          /**< Sends: RECEIVE_FAILURE + SEND_ERROR_TERMINATE                       */
        CLIENT_SERVER_CLOSURE,           /**< Sends: SERVER_CLOSURE + JUST_TERMINATE                              */
        CLIENT_AUTH_AGAIN,               /**< Sends: AUTH_AGAIN                                                   */
        CLIENT_AUTH_NO_REPLY,            /**< Sends: AUTH_NO_REPLY                                                */
        CLIENT_NOT_AUTH,                 /**< Sends: NOT_AUTH                                                     */
        CLIENT_REPLY_IN_OPEN,            /**< Sends: REPLY_IN_OPEN + NOT_PROPER_BEHAVIOUR + SEND_ERROR_TERMINATE  */
        CLIENT_MSG_IN_AUTH               /**< Sends: MSG_IN_AUTH + NOT_PROPER_BEHAVIOUR + SEND_ERROR_TERMINATE    */
    }; // ClientInternalErrorMessage
} // IPK25ChatClient::Enums

#endif // CLIENT_INTERNAL_ERROR_MESSAGES_HPP

/*** end of file ClientInternalErrorMessages.hpp ***/
