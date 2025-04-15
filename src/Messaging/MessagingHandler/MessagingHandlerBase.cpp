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

    void MessagingHandlerBase::setDisplayName(const string &displayName) {
        logger("Users display name set to: %s", displayName.c_str());
        mUserDisplayName = displayName;
    } // MessagingHandlerBase::setDisplayName
} // IPK25ChatClient::Messaging::Handler

/*** end of file MessagingHandlerBase.cpp ***/
