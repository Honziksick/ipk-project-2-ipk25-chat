/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPClientFSM.hpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `TcpClientFsm` class, which represents     *
 *               the finite state machine (FSM) for managing client-side       *
 *               operations in the IPK25 Chat Client. It handles user commands *
 *               and server messages, ensuring proper state transitions.       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPClientFSM.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `TcpClientFsm` class, which implements the
 *        finite state machine (FSM) for managing client-side operations in the
 *        IPK25 Chat Client.
 */

#ifndef TCP_CLIENT_FSM_HPP
#define TCP_CLIENT_FSM_HPP

#include "Client/ClientFSM/ClientFSMBase.hpp"
#include "Common/UserCommand.hpp"
#include "Common/ParsedMessage.hpp"
#include "Exceptions/ChatBaseException.hpp"

namespace IPK25ChatClient::Client::FSM
{
    /**
     * @class TcpClientFsm
     * @brief Represents the finite state machine (FSM) for the chat client.
     *
     * @details This class inherits from `ClientFsmBase` and implements the
     *          logic for handling user commands and server messages, ensuring
     *          proper state transitions in the chat client.
     */
    class TcpClientFsm final : public ClientFsmBase {
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

        /**
         * @brief Executes a user command based on the current state of the FSM.
         * @details This method processes a user command by determining its type
         *          and invoking the appropriate handler function. It ensures
         *          that commands are only executed if the FSM is not in the
         *          `END` state.
         *
         * @param userCommand The user command to be executed, containing its
         *                    type and any associated data.
         */
        void executeUserCommand(const Common::UserCommand &userCommand) override;

        /**
         * @brief Processes a server message based on its type.
         * @details This method determines the type of the received server
         *          message and invokes the corresponding handler function to
         *          process it.
         *
         * @param receivedMessage The parsed message received from the server.
         */
        void processServerMessage(const Common::ParsedMessage &receivedMessage) override;

        /**
         * @brief Handles the `/auth` command from the user.
         * @details This method is responsible for processing the `/auth` command,
         *          which is used to authenticate the user with the server.
         *          It transitions the FSM from the `start` state to the `auth` state
         *          and sends an AUTH request to the server.
         *
         * @param userCommand The user command containing the authentication details.
         */
        void onUserAuthRequested(const Common::UserCommand &userCommand) override;

        /**
         * @brief Handles the `/join` command from the user.
         * @details This method processes the `/join` command, allowing the user
         *          to join a specific channel. It transitions the FSM from the
         *          `open` state to the `join` state and sends a JOIN request to
         *          the server.
         *
         * @param userCommand The user command containing the channel information.
         */
        void onUserJoinRequested(const Common::UserCommand &userCommand) override;

        /**
         * @brief Handles the `/msg` command from the user.
         * @details This method processes the `/msg` command, which is used to
         *          send a message to the current channel. The FSM remains in
         *          the `open` state after sending the message, representing a
         *          loop transition within the `open` state.
         *
         * @param userCommand The user command containing the message content.
         */
        void onUserMsgRequested(const Common::UserCommand &userCommand) override;

        /**
         * @brief Handles the `/bye` command from the user.
         * @details This method processes the `/bye` command, which is used to
         *          gracefully exit the chat client. It transitions the FSM from
         *          any state (except `end`) to the `end` state, signaling the
         *          end of the session.
         */
        void onUserByeRequested() override;

        /**
         * @brief Handles the `/help` command from the user.
         * @details This method is responsible for displaying the help message
         *          to the user. It provides information about available commands
         *          and their usage in the chat client.
         */
        void onUserHelpRequested() override;

        /**
         * @brief Handles the sending error message to the server and graceful termination.
         * @details This method processes an error request by sending an error message
         *          to the server and closing the connection. It is typically used
         *          when an exception occurs that needs to be reported to the server.
         *
         * @param e The exception containing the error details to be sent to the server.
         * @param sendErrMessage Indicates whether to send the error message to the server.
         */
        void onUserErrRequested(const Exceptions::ChatBaseException &e, bool sendErrMessage) override;

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
         * @brief Handles a MSG message from the server.
         * @details Transitions the FSM:
         *          - If the FSM is in the `open` state, it remains in the `open` state.
         *          - If the FSM is in the `join` state, tit remains in the `join` state
         *            and ignores the message.
         *
         * @param receivedMessage The parsed message containing all details.
         */
        void onServerMsg(const Common::ParsedMessage &receivedMessage) override;

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
         *
         * @return The next state of the FSM after processing the message.
         */
        void onServerBye() override;
    }; // TcpClientFsm
} // IPK25ChatClient::Client::FSM

#endif // TCP_CLIENT_FSM_HPP

/*** end of file TCPClientFSM.hpp ***/
