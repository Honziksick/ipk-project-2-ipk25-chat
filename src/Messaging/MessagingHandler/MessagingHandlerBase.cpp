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
 * Last edit:    16.04.2025                                                    *
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
#include "Client/CommandParser/UserCommandParser.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>  // std::string
#include <memory>  // std::make_unique

using namespace IPK25ChatClient::Messaging::Builder;
using namespace IPK25ChatClient::Networking;
using namespace IPK25ChatClient::Client::CommandParser;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Messaging::Handler
{
    MessagingHandlerBase::MessagingHandlerBase(const CommandLineOptions &commandLineOptions) {
        if(commandLineOptions.mTransportProtocol == TransportProtocolType::TCP) {
            mCommunicationHandler = make_unique<TcpCommunicationHandler>(commandLineOptions);
            mMessageBuilder = make_unique<TcpMessageBuilder>();
            logger("Initialized ComunicationHandler and MessageBuilder: TCP");
        }
        else if(commandLineOptions.mTransportProtocol == TransportProtocolType::UDP) {
            mCommunicationHandler = make_unique<UdpCommunicationHandler>(commandLineOptions);
            mMessageBuilder = make_unique<UdpMessageBuilder>();
            logger("Initialized ComunicationHandler and MessageBuilder: UDP");
        }
        else {
            throw InternalErrorException(
                    "Invalid protocol type was given to MessagingHandlerBase: " +
                    CastUtils::castEnumToString(commandLineOptions.mTransportProtocol)
                    );
        }
    } // MessagingHandlerBase::MessagingHandlerBase

    void MessagingHandlerBase::setDisplayName(const string &displayName) {
        logger("Users display name set to: %s", displayName.c_str());
        mUserDisplayName = displayName;
    } // MessagingHandlerBase::setDisplayName

    void MessagingHandlerBase::sendAuthMessage(const string &username, const string &displayName, const string &secret) {
        logger("sendAuthMessage() called with username: %s, displayName: %s", username.c_str(), displayName.c_str());

        try {
            const UserCommand userCommand{
                .mUsername = username,
                .mSecret = secret,
                .mDisplayName = displayName
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::AUTH, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendAuthMessage() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendAuthMessage() completed successfully");
    } // MessagingHandlerBase::sendAuthMessage

    void MessagingHandlerBase::sendJoinMessage(const string &channelId, const string &displayName) {
        logger("sendJoinMessage() called with channelId: %s, displayName: %s", channelId.c_str(), displayName.c_str());

        try {
            const UserCommand userCommand{
                .mDisplayName = displayName,
                .mChannelId = channelId
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::JOIN, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendJoinMessage() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendJoinMessage() completed successfully");
    } // MessagingHandlerBase::sendJoinMessage

    void MessagingHandlerBase::sendMsgMessage(const string &displayName, const string &messageContent) {
        logger("sendMsgMessage() called with displayName: %s, messageContent: %s", displayName.c_str(), messageContent.c_str());

        try {
            const UserCommand userCommand{
                .mDisplayName = displayName,
                .mMessageContent = messageContent
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::MSG, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendMsgMessage() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendMsgMessage() completed successfully");
    } // MessagingHandlerBase::sendMsgMessage

    void MessagingHandlerBase::sendByeMessage() {
        logger("sendByeMessage() with mUserDisplayName: %s", mUserDisplayName.c_str());

        try {
            const UserCommand userCommand{
                .mDisplayName = mUserDisplayName
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::BYE, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        catch(const ConnectionErrorException &e) {
            sendErrMessage(e.detail());
            logger("sendBye() error: type: %s, detail: %s", e.what(), e.detail().c_str());
            throw;
        }

        logger("sendByeMessage() completed successfully");
    } // MessagingHandlerBase::sendByeMessage

    void MessagingHandlerBase::sendErrMessage(const string &messageContent) const {
        logger("sendErrMessage() called with mUserDisplayName: %s, messageContent: %s",
               mUserDisplayName.c_str(), messageContent.c_str());

        try {
            const UserCommand userCommand{
                .mDisplayName = mUserDisplayName,
                .mMessageContent = messageContent
            };
            const auto message = mMessageBuilder->buildMessage(MessageType::ERR, userCommand);
            mCommunicationHandler->sendMessage(message);
        }
        catch(...) {
            logger("sendErrMessage() error thrown while sending error message");
        }

        logger("sendErrMessage() completed successfully");
    } // MessagingHandlerBase::sendErrMessage
} // IPK25ChatClient::Messaging::Handler

/*** end of file MessagingHandlerBase.cpp ***/
