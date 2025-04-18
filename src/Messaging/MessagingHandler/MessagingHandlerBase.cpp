/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessagingHandlerBase.cpp                                      *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `MessagingHandlerBase` class, which     *
 *               provides common functionality for messaging handlers in the   *
 *               IPK25 Chat Client.                                            *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessagingHandlerBase.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the base class `MessagingHandlerBase` for common
 *        messaging handler functionality.
 */

#include "Messaging/MessagingHandler/MessagingHandlerBase.hpp"
#include "Messaging/MessageBuilder/TCPMessageBuilder.hpp"
#include "Messaging/MessageBuilder/UDPMessageBuilder.hpp"
#include "Networking/TCPCommunicationHandler.hpp"
#include "Networking/UDPCommunicationHandler.hpp"
#include "Validators/TCPMessageValidator.hpp"
#include "Validators/UDPMessageValidator.hpp"
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>  // std::string
#include <memory>  // std::make_unique, std::shared_ptr

using namespace IPK25ChatClient::Messaging::Builder;
using namespace IPK25ChatClient::Networking;
using namespace IPK25ChatClient::Client::CommandParser;
using namespace IPK25ChatClient::Validators;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Messaging::Handler
{
    MessagingHandlerBase::MessagingHandlerBase(const CommandLineOptions &commandLineOptions, const shared_ptr<int> &socketFd,
                                               const shared_ptr<DisplayNameProvider> &displayNameProvider)
        : mDisplayNameProvider{displayNameProvider} {
        // Initialized the CommunicationHandler, MessageBuilder and MessageValidator based on the transport protocol type
        if(commandLineOptions.mTransportProtocol == TransportProtocolType::TCP) {
            mCommunicationHandler = make_unique<TcpCommunicationHandler>(commandLineOptions, socketFd);
            mMessageBuilder = make_unique<TcpMessageBuilder>();
            mMessageValidator = make_unique<TcpMessageValidator>();
            logger("Initialized CommunicationHandler, MessageBuilder and MessageValidator: TCP");
        }
        else if(commandLineOptions.mTransportProtocol == TransportProtocolType::UDP) {
            mCommunicationHandler = make_unique<UdpCommunicationHandler>(commandLineOptions, socketFd);
            mMessageBuilder = make_unique<UdpMessageBuilder>();
            mMessageValidator = make_unique<UdpMessageValidator>();
            logger("Initialized CommunicationHandler, MessageBuilder and MessageValidator: UDP");
        }
        else {
            throw ConstructorErrorException(
                    "Invalid protocol type was given to MessagingHandlerBase: " +
                    CastUtils::castEnumToString(commandLineOptions.mTransportProtocol)
                    );
        }
    } // MessagingHandlerBase::MessagingHandlerBase

    void MessagingHandlerBase::openConnection() {
        mCommunicationHandler->openConnection();
    } // MessagingHandlerBase::openConnection

    void MessagingHandlerBase::closeConnection() {
        mCommunicationHandler->closeConnection();
    } // MessagingHandlerBase::closeConnection

    vector<ParsedMessage> MessagingHandlerBase::receiveMessages() {
        logger("receiveMessages() called. Receiving messages from communication handler.");

        // Get a vector of parsed messages from the communication handler
        const vector<ParsedMessage> parsedMessages = mCommunicationHandler->receiveMessages();
        logger("Received %zu message(s) from communication handler.", parsedMessages.size());

        // Validate parsed messages one-by-one
        for(auto &message : parsedMessages) {
            logger("Validating message type: %s", message.mFields[0].c_str());
            mMessageValidator->validateMessage(message);

            logger("Processing message type: %s", message.mFields[0].c_str());
            processIncomingMessage(message);
        }

        logger("receiveMessages() completed. Returning %zu parsed message(s).", parsedMessages.size());
        return parsedMessages;
    } // MessagingHandlerBase::receiveMessages

    void MessagingHandlerBase::sendAuthMessage(const string &username, const string &displayName, const string &secret) {
        logger("sendAuthMessage() called with username: %s, displayName: %s", username.c_str(), displayName.c_str());

        // Build and send the AUTH message
        try {
            const UserCommand userCommand{
                .mUsername = username,
                .mSecret = secret,
                .mDisplayName = displayName
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::AUTH, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        // Something went wrong, so we try to send an error message
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendAuthMessage() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendAuthMessage() completed successfully");
    } // MessagingHandlerBase::sendAuthMessage

    void MessagingHandlerBase::sendJoinMessage(const string &channelId) {
        logger("sendJoinMessage() called with channelId: %s, displayName: %s",
               channelId.c_str(), mDisplayNameProvider->getDisplayName().c_str());

        // Build and send the JOIN message
        try {
            const UserCommand userCommand{
                .mDisplayName = mDisplayNameProvider->getDisplayName(),
                .mChannelId = channelId
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::JOIN, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        // Something went wrong, so we try to send an error message
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendJoinMessage() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendJoinMessage() completed successfully");
    } // MessagingHandlerBase::sendJoinMessage

    void MessagingHandlerBase::sendMsgMessage(const string &messageContent) {
        logger("sendMsgMessage() called with displayName: %s, messageContent: %s",
               mDisplayNameProvider->getDisplayName().c_str(), messageContent.c_str());

        // Build and send the MSG message
        try {
            const UserCommand userCommand{
                .mDisplayName = mDisplayNameProvider->getDisplayName(),
                .mMessageContent = messageContent
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::MSG, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        // Something went wrong, so we try to send an error message
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendMsgMessage() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendMsgMessage() completed successfully");
    } // MessagingHandlerBase::sendMsgMessage

    void MessagingHandlerBase::sendByeMessage() {
        logger("sendByeMessage() with mUserDisplayName: %s", mDisplayNameProvider->getDisplayName().c_str());

        // Build and send the BYE message
        try {
            const UserCommand userCommand{
                .mDisplayName = mDisplayNameProvider->getDisplayName(),
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::BYE, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        // Something went wrong, so we try to send an error message
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendBye() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendByeMessage() completed successfully");
    } // MessagingHandlerBase::sendByeMessage

    void MessagingHandlerBase::sendErrMessage(const string &messageContent) {
        logger("sendErrMessage() called with mUserDisplayName: %s, messageContent: %s",
               mDisplayNameProvider->getDisplayName().c_str(), messageContent.c_str());

        // Build and send the ERR message
        try {
            const UserCommand userCommand{
                .mDisplayName = mDisplayNameProvider->getDisplayName(),
                .mMessageContent = messageContent
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::ERR, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        // Something went wrong, so we try to send an error message
        catch(...) {
            logger("sendErrMessage() error thrown while sending error message");
        }

        logger("sendErrMessage() completed successfully");
    } // MessagingHandlerBase::sendErrMessage
} // IPK25ChatClient::Messaging::Handler

/*** end of file MessagingHandlerBase.cpp ***/
