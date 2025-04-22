/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessagingHandlerBase.hpp                                      *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Base class for messaging handlers in the IPK25 Chat Client.   *
 *               Provides common functionality for derived messaging handler   *
 *               classes, such as managing communication and message building. *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessagingHandlerBase.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining base class `MessagingHandlerBase` for messaging
 *        handlers in the IPK25 Chat Client.
 */

#ifndef MESSAGING_HANDLER_BASE_HPP
#define MESSAGING_HANDLER_BASE_HPP

#include "Messaging/Interfaces/IMessagingHandler.hpp"
#include "Messaging/Interfaces/IMessageBuilder.hpp"
#include "Networking/Interfaces/ICommunicationHandler.hpp"
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Validators/Interfaces/IMessageValidator.hpp"
#include <string>  // std::string
#include <memory>  // std::unique_ptr, std::shared_ptr

namespace IPK25ChatClient::Messaging::Handler
{
    /**
     * @class MessagingHandlerBase
     * @brief Base class for messaging handlers.
     *
     * @details This class provides common functionality for derived messaging
     *          handler classes, including communication handling and message
     *          building.
     */
    class MessagingHandlerBase : public IMessagingHandler {
    public:
        /**
         * @brief Constructs a `MessagingHandlerBase` object.
         * @details Constructor of the messaging handler with the provided
         *          command line options passed to constructors other submodules.
         *
         * @param commandLineOptions The command line options for the application.
         * @param socketFd The socket file descriptor for communication.
         * @param displayNameProvider The shared user display name provider.
         */
        explicit MessagingHandlerBase(const Common::CommandLineOptions &commandLineOptions,
                                      const std::shared_ptr<int> &socketFd,
                                      const std::shared_ptr<Client::CommandParser::DisplayNameProvider> &displayNameProvider);

        /**
         * @brief Virtual destructor for the base class.
         */
        ~MessagingHandlerBase() override = default;

        /**
         * @brief Opens a connection to the server.
         * @details This method establishes a connection to the specified
         *          server and prepares the handler for communication.
         */
        void openConnection() override;

        /**
         * @brief Closes the active connection.
         * @details This method gracefully terminates the connection and release
         *          any associated resources.
         *
         * @param sendBye Flag indicating whether to send a BYE message before termination.
         */
        void closeConnection(bool sendBye) override;

        /**
         * @brief Receives a message from the server and processes it.
         * @details This method is responsible for receiving a message from the
         *          server through the communication handler, parsing the message,
         *          and returning its content in a structured format. The
         *          implementation of this method is provided in the derived classes.
         *
         * @return std::vector<Common::ParsedMessage> Vector of parsed content
         *         of the received message.
         */
        std::vector<Common::ParsedMessage> receiveMessages() override;

        /**
         * @brief Sends an authentication message.
         * @details Constructs and sends a message to authenticate the user
         *          with the provided credentials.
         *
         * @param username The username for authentication.
         * @param displayName The display name for the user.
         * @param secret The secret or password for authentication.
         */
        void sendAuthMessage(const std::string &username,
                             const std::string &displayName,
                             const std::string &secret) override;

        /**
         * @brief Sends a join message to a specific channel.
         * @details Constructs and sends a message to join a channel with the
         *          specified channel ID and display name.
         *
         * @param channelId The ID of the channel to join.
         */
        void sendJoinMessage(const std::string &channelId) override;

        /**
         * @brief Sends a message to a channel or user.
         * @details Constructs and sends a message containing the specified
         *          content to the target channel or user.
         *
         * @param messageContent The content of the message to send.
         */
        void sendMsgMessage(const std::string &messageContent) override;

        /**
         * @brief Sends a goodbye message.
         * @details Constructs and sends a message indicating that the user
         *          is leaving the chat or channel.
         */
        void sendByeMessage() override;

        /**
         * @brief Sends an error message.
         * @details Constructs and sends an error message with the specified
         *          content. This method "swallows" any exceptions thrown during
         *          the sending process.
         *
         * @param messageContent The content of the error message.
         */
        void sendErrMessage(const std::string &messageContent) override;

    protected:
        std::unique_ptr<Networking::ICommunicationHandler> mCommunicationHandler;          /**< Handles communication over the network. */
        std::shared_ptr<Builder::IMessageBuilder> mMessageBuilder;                         /**< Builds messages for sending.            */
        std::shared_ptr<Client::CommandParser::DisplayNameProvider> mDisplayNameProvider;  /**< Shared display name of the user.        */
        std::unique_ptr<Validators::IMessageValidator> mMessageValidator;                  /**< Validates received messages.            */
    }; // MessagingHandlerBase
} // IPK25ChatClient::Messaging::Handler

#endif // MESSAGING_HANDLER_BASE_HPP

/*** end of file MessagingHandlerBase.hpp ***/
