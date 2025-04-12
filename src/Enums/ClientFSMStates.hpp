/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientFSMStates.hpp                                           *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      12.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Defines the enumeration `ClientFsmState` for a different      *
 *               client FSM states used in the IPK25 Chat Client.              *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientFSMStates.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the enumeration `ClientFsmState` for a different
 *        client FSM states.
 */

#ifndef CLIENT_FSM_STATES_HPP
#define CLIENT_FSM_STATES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum ClientFsmState
     * @brief Enumeration of client FSM states.
     */
    enum class ClientFsmState {
        START,    /**< Initial state of the client.                                       */
        AUTH,     /**< State where the client is authenticating.                          */
        JOIN,     /**< State where the client is joining a channel.                       */
        OPEN,     /**< State where the client is connected and can send/receive messages. */
        END       /**< Final state where the client has terminated the connection.        */
    }; // ClientFsmState
} // IPK25ChatClient::Enums

#endif // CLIENT_FSM_STATES_HPP

/*** end of file ClientFSMStates.hpp ***/
