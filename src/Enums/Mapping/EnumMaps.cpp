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
 * Last edit:    15.04.2025                                                    *
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
#include "Enums/ExitCodes.hpp"
#include "Enums/CommandParameters.hpp"
#include "Enums/MessageTypes.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Enums/ValidatorResults.hpp"
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
            {ExitCode::PROTOCOL_ERROR, "Protocol Error"},
            {ExitCode::UNKNOWN_ERROR, "Unknown Error"},
            {ExitCode::TIMEOUT_ERROR, "Timeout Error"},
            {ExitCode::USER_INTERRUPTION_ERROR, "User Interruption Error"}
        };
        return cMap;
    } // EnumMaps::getExitCodeMap

    const unordered_map<CommandParameter, string> &EnumMaps::getMessageParameterMap() {
        static const unordered_map<CommandParameter, string> cMap = {
            {CommandParameter::MESSAGE_ID, "MessageID"},
            {CommandParameter::USERNAME, "Username"},
            {CommandParameter::CHANNEL_ID, "ChannelID"},
            {CommandParameter::SECRET, "Secret"},
            {CommandParameter::DISPLAY_NAME, "DisplayName"},
            {CommandParameter::MESSAGE_CONTENT, "MessageContent"}
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
} // IPK25ChatClient::Enums

/*** end of file EnumMaps.cpp ***/
