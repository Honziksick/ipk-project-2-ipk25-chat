/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientFSMBase.hpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `ClientFsmBase` base class for the client  *
 *               finite state machine (FSM). It provides common functionality  *
 *               and defines the interface for handling user and server events *
 *               in the FSM.                                                   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientFSMBase.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `ClientFsmBase` class, which serves as a base
 *        class for the client finite state machine (FSM) providing common functionality.
 */

#ifndef CLIENT_FSM_BASE_HPP
#define CLIENT_FSM_BASE_HPP

#include "Client/Interfaces/IClientFSM.hpp"
#include "Client/Interfaces/IUserCommandParser.hpp"
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Messaging/Interfaces/IMessagingHandler.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Common/UserCommand.hpp"
#include "Common/ParsedMessage.hpp"
#include "Exceptions/ChatBaseException.hpp"
#include "Enums/ClientFSMStates.hpp"
#include <memory>  // std::unique_ptr, std::shared_ptr
#include <poll.h>  // pollfd

namespace IPK25ChatClient::Client::FSM
{
    /**
     * @class ClientFsmBase
     * @brief Base class for the client finite state machine (FSM).
     *
     * @details This class provides the core structure for implementing the FSM
     *          logic. It defines common attributes and pure virtual methods
     *          that must be implemented by derived classes to handle specific
     *          user and server events.
     *
     * @note For better naming consistency I asked the GitHub copilot for
     *       suggestion on how to name the transition methods as clearly as
     *       possible.
     */
    class ClientFsmBase : public IClientFsm {
    public:
        /**
         * @brief Constructs a `ClientFsmBase` object.
         *
         * @param commandLineOptions Command-line options for configuring the client.
         */
        explicit ClientFsmBase(const Common::CommandLineOptions &commandLineOptions);

        /**
         * @brief Destructor for the base class.
         */
        ~ClientFsmBase() override = default;

    protected:
        bool mReceivedAuthReply;                            /**< Flag indicating if the server replied on the AUTH message.        */
        std::shared_ptr<int> mSocketFd;                     /**< Socket file descriptor shared with the MessagingHandler.          */
        Enums::ClientFsmState mCurrentState;                /**< Current state of the FSM.                                         */
        static constexpr int POLL_FD_COUNT{2};              /**< Number of file descriptors to poll.                               */
        static constexpr size_t POLL_STDIN_INDEX{0};        /**< Index for the standard input file descriptor in the pollfd array. */
        static constexpr size_t POLL_SOCKET_INDEX{1};       /**< Index for the socket file descriptor in the pollfd array.         */
        static constexpr int POLL_INFINITE_TIMEOUT_MS{-1};  /**< Timeout value for the `poll()` system call (`-1` means infinite). */
        std::shared_ptr<CommandParser::DisplayNameProvider> mDisplayNameProvider;  /**< Display name provider of the user for logging purposes. */
        std::unique_ptr<CommandParser::IUserCommandParser> mUserCommandParser;     /**< User command parser for handling user input.            */
        std::unique_ptr<Messaging::Handler::IMessagingHandler> mMessagingHandler;  /**< Messaging handler for sending and receiving messages.   */

        /**
         * @brief Updates the current state of the FSM.
         * @details This method updates the internal state of the FSM to the specified
         *          new state. It is used internally to manage state transitions.
         *
         * @param newState The new state to transition to.
         */
        void updateCurrentState(Enums::ClientFsmState newState);

        /**
         * @brief Sets up the pollfd structure for monitoring file descriptors.
         * @details This method initializes the pollfd structure to monitor two
         *          file descriptors: standard input (STDIN_FD) and the socket
         *          file descriptor (`mSocketFd`). It sets the events to POLLIN
         *          to detect when data is available to read.
         *
         * @param fdWatcher Pointer to an array of pollfd structures to be
         *                  configured. The method sets up the file descriptors
         *                  and events for standard input and the socket.
         */
        void setupPollFd(pollfd *fdWatcher) const;

        /**
         * @brief Waits for events on the specified file descriptors using the
         *        `poll()` system call.
         * @details This method uses the `poll()` system call to monitor multiple
         *          file descriptors for events. If poll() is interrupted by a
         *          signal, a `UserInterruptionException` is thrown. For other
         *          errors, a `ConnectionErrorException` is thrown.
         *
         * @param fdWatcher Pointer to an array of pollfd structures that specify
         *                  the file descriptors and events to monitor.
         * @param pollTimeoutMs Timeout value for the poll operation in milliseconds.
         *
         * @return The number of file descriptors with events, or throws
         *         an exception if an error occurs.
         */
        static int pollEvents(pollfd *fdWatcher, int pollTimeoutMs);

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
        void executeUserCommand(const Common::UserCommand &userCommand);

        /**
         * @brief Processes a server message based on its type.
         * @details This method determines the type of the received server
         *          message and invokes the corresponding handler function to
         *          process it.
         *
         * @param receivedMessage The parsed message received from the server.
         */
        void processServerMessage(const Common::ParsedMessage &receivedMessage);

        /**
         * @brief Handles the `/auth` command from the user.
         * @details This method is responsible for processing the `/auth` command,
         *          which is used to authenticate the user with the server.
         *          It transitions the FSM from the `start` state to the `auth` state
         *          and sends an AUTH request to the server.
         *
         * @param userCommand The user command containing the authentication details.
         */
        void onUserAuthRequested(const Common::UserCommand &userCommand);

        /**
         * @brief Handles the `/join` command from the user.
         * @details This method processes the `/join` command, allowing the user
         *          to join a specific channel. It transitions the FSM from the
         *          `open` state to the `join` state and sends a JOIN request to
         *          the server.
         *
         * @param userCommand The user command containing the channel information.
         */
        void onUserJoinRequested(const Common::UserCommand &userCommand);

        /**
         * @brief Handles the `/msg` command from the user.
         * @details This method processes the `/msg` command, which is used to
         *          send a message to the current channel. The FSM remains in
         *          the `open` state after sending the message, representing a
         *          loop transition within the `open` state.
         *
         * @param userCommand The user command containing the message content.
         */
        void onUserMsgRequested(const Common::UserCommand &userCommand) const;

        /**
         * @brief Handles the `/bye` command from the user.
         * @details This method processes the `/bye` command, which is used to
         *          gracefully exit the chat client. It transitions the FSM from
         *          any state (except `end`) to the `end` state, signaling the
         *          end of the session.
         */
        virtual void onUserByeRequested() = 0;

        /**
         * @brief Handles the `/help` command from the user.
         * @details This method is responsible for displaying the help message
         *          to the user. It provides information about available commands
         *          and their usage in the chat client.
         */
        static void onUserHelpRequested();

        /**
         * @brief Handles the sending error message to the server and graceful termination.
         * @details This method processes an error request by sending an error message
         *          to the server and closing the connection. It is typically used
         *          when an exception occurs that needs to be reported to the server.
         *
         * @param e The exception containing the error details to be sent to the server.
         * @param sendErrMessage Indicates whether to send the error message to the server.
         */
        void onUserErrRequested(const Exceptions::ChatBaseException &e, bool sendErrMessage) const;

        /**
         * @brief Handles a REPLY message from the server.
         * @details Transitions the FSM:
         *          - From `auth` to `open` upon receiving a positive REPLY.
         *          - From `join` to `open` upon receiving any REPLY.
         *
         * @param receivedMessage The parsed message containing all details.
         */
        virtual void onServerReply(const Common::ParsedMessage &receivedMessage) = 0;

        /**
         * @brief Handles a MSG message from the server.
         * @details Transitions the FSM:
         *          - If the FSM is in the `open` state, it remains in the `open` state.
         *          - If the FSM is in the `join` state, tit remains in the `join` state
         *            and ignores the message.
         *
         * @param receivedMessage The parsed message containing all details.
         */
        void onServerMsg(const Common::ParsedMessage &receivedMessage) const;

        /**
         * @brief Handles an ERR message from the server.
         * @details Transitions the FSM from any state (`auth`, `open`, `join`,
         *          or `start`) to the `end` state upon receiving an ERR message.
         *
         * @param receivedMessage The parsed message containing all details.
         */
        virtual void onServerErr(const Common::ParsedMessage &receivedMessage) = 0;

        /**
         * @brief Handles a BYE message from the server.
         * @details Transitions the FSM from any state (`auth`, `open`, `join`,
         *          or `start`)  to the `end` state upon receiving a BYE message.
         */
        virtual void onServerBye() = 0;

        /**
         * @brief Activates the reply deadline timer.
         * @details This method sets the reply deadline to 5 seconds from the
         *          current time and activates the timer. It is used to ensure
         *          that the client receives a response from the server within
         *          the specified time frame.

         * @note Only for UDP.
         */
        virtual void activateReplyDeadline() = 0;

    private:
        static constexpr int STDIN_FD{0};  /**< File descriptor for standard input. */
    }; // ClientFsmBase
} // IPK25ChatClient::Client::FSM

#endif // CLIENT_FSM_BASE_HPP

/*** end of file ClientFSMBase.hpp ***/
