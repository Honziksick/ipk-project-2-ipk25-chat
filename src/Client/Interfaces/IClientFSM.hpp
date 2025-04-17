/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IClientFSM.hpp                                                *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Interface for the client finite state machine (FSM). This     *
 *               interface provides a unified way of executing the FSM logic.  *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IClientFSM.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Interface `IClientFsm` definition for the client finite state
 *        machine (FSM).
 */

#ifndef I_CLIENT_FSM_HPP
#define I_CLIENT_FSM_HPP

namespace IPK25ChatClient::Client::FSM
{
    /**
     * @class IClientFsm
     * @brief Interface for the client finite state machine (FSM).
     * @details This interface provides a unified way of executing the FSM logic.
     */
    class IClientFsm {
    public:
        /**
         * @brief Virtual destructor for the `IClientFsm` interface.
         */
        virtual ~IClientFsm() = default;

        /**
         * @brief Executes the finite state machine logic.
         * @details This pure virtual method must be implemented by derived classes
         *          to define the behavior of the finite state machine. It is
         *          responsible for managing state transitions and executing
         *          state-specific logic.
         */
        virtual void run() = 0;
    }; // IClientFsm
} // IPK25ChatClient::Client::FSM

#endif // I_CLIENT_FSM_HPP

/*** end of file IClientFSM.hpp ***/
