/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPClientFSM.hpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      18.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `UdpClientFsm` class, which represents     *
 *               the finite state machine (FSM) for managing client-side       *
 *               operations in the IPK25 Chat Client. It handles user commands *
 *               and server messages, ensuring proper state transitions.       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPClientFSM.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `UdpClientFsm` class, which implements the
 *        finite state machine (FSM) for managing client-side operations in the
 *        IPK25 Chat Client.
 */

#ifndef UDP_CLIENT_FSM_HPP
#define UDP_CLIENT_FSM_HPP

#include "Client/ClientFSM/ClientFSMBase.hpp"
#include "Common/ParsedMessage.hpp"
#include <queue>   // std::queue
#include <chrono>  // std::chrono::steady_clock

namespace IPK25ChatClient::Client::FSM
{
    /**
     * @class UdpClientFsm
     * @brief Represents the finite state machine (FSM) for the chat client.
     *
     * @details This class inherits from `ClientFsmBase` and implements the
     *          logic for handling user commands and server messages, ensuring
     *          proper state transitions in the chat client.
     */
    class UdpClientFsm final : public ClientFsmBase {
    public:
        /**
         * @brief Inherits constructors from the `ClientFsmBase` class.
         */
        using ClientFsmBase::ClientFsmBase;

        /**
         * @brief Executes the finite state machine logic.
         * @details This pure method must be implemented by derived classes
         *          to define the behaviour of the finite state machine. It is
         *          responsible for managing state transitions and executing
         *          state-specific logic.
         */
        void run() override;

    private:
        std::queue<Common::UserCommand> mStagedCommands;       /**< Queue for storing user commands staged for processing. */
        std::chrono::steady_clock::time_point mReplyDeadline;  /**< Timestamp representing the reply deadline.             */
        bool mIsReplyDeadlineActive{false};                    /**< Flag indicating whether the reply deadline is active.  */

        /**
         * @brief Handles the `/bye` command from the user.
         * @details This method processes the `/bye` command, which is used to
         *          gracefully exit the chat client. It transitions the FSM from
         *          any state (except `end`) to the `end` state, signaling the
         *          end of the session.
         */
        void onUserByeRequested() override;

        /**
         * @brief Handles a REPLY message from the server.
         * @details Transitions the FSM:
         *          - From `auth` to `open` upon receiving a positive REPLY.
         *          - From `join` to `open` upon receiving any REPLY.
         *
         * @param receivedMessage The parsed message containing all details.
         */
        void onServerReply(const Common::ParsedMessage &receivedMessage) override;

        /**
         * @brief Handles an ERR message from the server.
         * @details Transitions the FSM from any state (`auth`, `open`, `join`,
         *          or `start`) to the `end` state upon receiving an ERR message.
         *
         * @param receivedMessage The parsed message containing all details.
         */
        void onServerErr(const Common::ParsedMessage &receivedMessage) override;

        /**
         * @brief Handles a BYE message from the server.
         * @details Transitions the FSM from any state (`auth`, `open`, `join`,
         *          or `start`)  to the `end` state upon receiving a BYE message.
         */
        void onServerBye() override;

        /**
         * @brief Activates the reply deadline timer.
         * @details This method sets the reply deadline to 5 seconds from the
         *          current time and activates the timer. It is used to ensure
         *          that the client receives a response from the server within
         *          the specified time frame.

         * @note Only for UDP.
         */
        void activateReplyDeadline() override;

        /**
         * @brief Deactivates the reply deadline timer.
         * @details This method sets the `mIsReplyDeadlineActive` flag to `false`,
         *          effectively disabling the reply deadline timer. It is used
         *          when the client no longer expects a reply from the server.
         */
        void deactivateReplyDeadline();

        /**
         * @brief Checks if the reply deadline has expired.
         * @details This method determines whether the reply deadline has been
         *          reached or exceeded. It checks if the `mIsReplyDeadlineActive`
         *          flag is `true` and compares the current time with the stored
         *          deadline (`mReplyDeadline`).
         *
         * @return `true` if the reply deadline is active and has expired,
         *         otherwise `false`.
         */
        bool isReplyDeadlineExpired() const;
    }; // UdpClientFsm
} // IPK25ChatClient::Client::FSM

#endif // UDP_CLIENT_FSM_HPP

/*** end of file UDPClientFSM.hpp ***/
