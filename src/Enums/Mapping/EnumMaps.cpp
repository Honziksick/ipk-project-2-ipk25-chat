/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         EnumMaps.cpp                                                  *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `EnumMaps` class, which provides static *
 *               mapping utilities for converting enum values to their         *
 *               corresponding string representations.                         *
 *                                                                             *
 ******************************************************************************/
/**
 * @file EnumMaps.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of static mapping utilities for enum-to-string conversions.
 */

#include "Enums/Mapping/EnumMaps.hpp"
#include "Enums/UserCommandTypes.hpp"
#include "Enums/ClientFsmStates.hpp"
#include "Enums/ClientInternalErrorMessages.hpp"
#include "Enums/ExitCodes.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/MessageTypes.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Enums/ValidatorResults.hpp"
#include "Constants/ClientInternalErrorPhrases.hpp"
#include <unordered_map>  // std::unordered_map
#include <string>         // std::string

using namespace std;

namespace IPK25ChatClient::Enums::Mapping
{
    const unordered_map<UserCommandType, string> &EnumMaps::getUserCommandTypeMap() {
        static const unordered_map<UserCommandType, string> cMap = {
            {UserCommandType::UNKNOWN, "/unknown"},
            {UserCommandType::INVALID, "/invalid"},
            {UserCommandType::MESSAGE, "/message"},
            {UserCommandType::ERR, "/err"},
            {UserCommandType::BYE, "/bye"},
            {UserCommandType::AUTH, "/auth"},
            {UserCommandType::JOIN, "/join"},
            {UserCommandType::RENAME, "/rename"},
            {UserCommandType::HELP, "/help"}
        };
        return cMap;
    } // EnumMaps::getUserCommandTypeMap

    const unordered_map<ClientFsmState, string> &EnumMaps::getClientFsmStateMap() {
        static const unordered_map<ClientFsmState, string> cMap = {
            {ClientFsmState::START, "Start"},
            {ClientFsmState::AUTH, "Auth"},
            {ClientFsmState::JOIN, "Join"},
            {ClientFsmState::OPEN, "Open"},
            {ClientFsmState::END, "End"}
        };
        return cMap;
    } // EnumMaps::getClientFsmStateMap

    const unordered_map<ExitCode, string> &EnumMaps::getExitCodeMap() {
        static const unordered_map<ExitCode, string> cMap = {
            {ExitCode::SUCCESS, "Success"},
            {ExitCode::INVALID_ARGUMENT_ERROR, "Invalid Argument Error"},
            {ExitCode::HOSTNAME_RESOLUTION_ERROR, "Hostname Resolution Error"},
            {ExitCode::INTERNAL_ERROR, "Internal Error"},
            {ExitCode::CONNECTION_ERROR, "Socket Error"},
            {ExitCode::UNESTABLISHED_ERROR, "Unestablished connection"},
            {ExitCode::PROTOCOL_ERROR, "Protocol Error"},
            {ExitCode::UNKNOWN_ERROR, "Unknown Error"},
            {ExitCode::TIMEOUT_ERROR, "Timeout Error"}
        };
        return cMap;
    } // EnumMaps::getExitCodeMap

    const unordered_map<MessageParameter, string> &EnumMaps::getMessageParameterMap() {
        static const unordered_map<MessageParameter, string> cMap = {
            {MessageParameter::MESSAGE_ID, "MessageID"},
            {MessageParameter::USERNAME, "Username"},
            {MessageParameter::CHANNEL_ID, "ChannelID"},
            {MessageParameter::SECRET, "Secret"},
            {MessageParameter::DISPLAY_NAME, "DisplayName"},
            {MessageParameter::MESSAGE_CONTENT, "MessageContent"}
        };
        return cMap;
    } // EnumMaps::getMessageParameterMap

    const unordered_map<MessageType, string> &EnumMaps::getMessageTypeMap() {
        static const unordered_map<MessageType, string> cMap = {
            {MessageType::UNKNOWN, "unknown"},
            {MessageType::CONFIRM, "confirm"},
            {MessageType::REPLY, "reply"},
            {MessageType::AUTH, "auth"},
            {MessageType::JOIN, "join"},
            {MessageType::MSG, "msg"},
            {MessageType::PING, "ping"},
            {MessageType::ERR, "err"},
            {MessageType::BYE, "bye"}
        };
        return cMap;
    } // EnumMaps::getMessageTypeMap

    const unordered_map<ValidatorResult, string> &EnumMaps::getMessageValidatorResultMap() {
        static const unordered_map<ValidatorResult, string> cMap = {
            {ValidatorResult::OK, "Message parameter is valid"},
            {ValidatorResult::INVALID, "Message parameter is invalid"},
            {ValidatorResult::UNKNOWN, "Message parameter: Status unknown"},
            {ValidatorResult::PARAMETER_TOO_LONG, "Message parameter: Parameter too long"},
            {ValidatorResult::PARAMETER_TOO_SHORT, "Message parameter: Parameter too short"},
            {ValidatorResult::PARAMETER_CONTAINS_INVALID_SYMBOLS, "Message parameter: Parameter contains invalid symbols"}
        };
        return cMap;
    } // EnumMaps::getMessageValidatorResultMap

    const unordered_map<TransportProtocolType, string> &EnumMaps::getTransportProtocolTypeMap() {
        static const unordered_map<TransportProtocolType, string> cMap = {
            {TransportProtocolType::None, "None"},
            {TransportProtocolType::UDP, "UDP"},
            {TransportProtocolType::TCP, "TCP"},
            {TransportProtocolType::IPv4, "IPv4"},
            {TransportProtocolType::IPv6, "IPv6"}
        };
        return cMap;
    } // EnumMaps::getTransportProtocolTypeMap

    const unordered_map<ClientInternalErrorMessage, string> &EnumMaps::getClientInternalErrorMessageMap() {
        static const unordered_map<ClientInternalErrorMessage, string> cMap = {
            {ClientInternalErrorMessage::CLIENT_UNKNOWN, string{}},
            {ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR, string(INTERNAL_ERROR) + string(SEND_ERROR_TERMINATE) + string(APOLOGY)},
            {ClientInternalErrorMessage::CLIENT_CONNECTION_ERROR, string(CONNECTION_ISSUE) + string(SEND_ERROR_TERMINATE)},
            {ClientInternalErrorMessage::CLIENT_BAD_COMMAND, string(BAD_COMMAND) + string(HELP_PROMPT)},
            {ClientInternalErrorMessage::CLIENT_BAD_CHARACTERS, string(BAD_CHARACTERS) + string(HELP_PROMPT)},
            {ClientInternalErrorMessage::CLIENT_BAD_LENGTH, string(BAD_LENGTH) + string(HELP_PROMPT)},
            {ClientInternalErrorMessage::CLIENT_BAD_LENGTH_TRUNCATE, string(BAD_LENGTH) + string(HELP_PROMPT) + string(TRUNCATION)},
            {ClientInternalErrorMessage::CLIENT_MALFORMED_MESSAGE, string(MALFORMED_MESSAGE) + string(SEND_ERROR_TERMINATE)},
            {ClientInternalErrorMessage::CLIENT_HOST_RESOLUTION_FAILURE, string(HOST_RESOLUTION_FAILURE) + string(DONT_SEND_ERROR_TERMINATE)},
            {ClientInternalErrorMessage::CLIENT_SEND_FAILURE, string(SEND_FAILURE) + string(SEND_ERROR_TERMINATE)},
            {ClientInternalErrorMessage::CLIENT_RECEIVE_FAILURE, string(RECEIVE_FAILURE) + string(SEND_ERROR_TERMINATE)},
            {ClientInternalErrorMessage::CLIENT_SERVER_CLOSURE, string(SERVER_CLOSURE) + string(JUST_TERMINATE)},
            {ClientInternalErrorMessage::CLIENT_AUTH_AGAIN, string(AUTH_AGAIN)},
            {ClientInternalErrorMessage::CLIENT_NOT_AUTH, string(NOT_AUTH)}
        };
        return cMap;
    } // EnumMaps::getClientInternalErrorMessagesMap
} // IPK25ChatClient::Enums

/*** end of file EnumMaps.cpp ***/
