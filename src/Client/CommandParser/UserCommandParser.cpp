/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UserCommandParser.cpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      12.04.2025                                                    *
 * Last edit:    15.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `UserCommandParser` class, which        *
 *               provides functionality for parsing user input commands into   *
 *               structured `UserCommand` objects irectly from command line.   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UserCommandParser.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `UserCommandParser` class for parsing user
 *        commands from `STDIN` into structured objects.
 */

#include "Client/CommandParser/UserCommandParser.hpp"
#include "Validators/UserCommandValidators.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Common/UserCommand.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Constants/ClientLimits.hpp"
#include "Enums/UserCommandTypes.hpp"
#include "Enums/CommandParameters.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/CastUtils.hpp"
#include <string>    // std::string, std::getline(), std::to_string()
#include <vector>    // std::vector
#include <iostream>  // std::cin

using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Client::Output;
using namespace IPK25ChatClient::Client;
using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Utilities;
using namespace IPK25ChatClient::Validators;
using namespace std;

namespace IPK25ChatClient::Client::CommandParser
{
    UserCommand UserCommandParser::parseCommandLine() {
        // Read a line from the standard input ('\n' is read but not included)
        const string line{readLine()};

        // Check if the command wasn't stand-alone '\n'
        if(line.empty()) {
            ClientOutput::printClientInternalError(
                    "It seems you may have accidentally pressed 'Enter' which "
                    "resulted in proccesing an empty command/message. If you are "
                    "unsure how to enter a command or a message, you may enter the "
                    "'/help' command for more information about this topic."
                    );
            return UserCommand{
                .mCommandType = UserCommandType::INVALID
            };
        }

        // If the line starts with '/', parse it as a client command
        if(line[0] == '/') {
            return parseClientCommand(line);
        }
        // Else, parse it as a chat message
        else {
            return parseChatMessage(line);
        }
    } // UserCommandParser::parseCommandLine

    string UserCommandParser::readLine() {
        // Read a line from the standard input
        if(string line; getline(cin, line)) {
            return line;
        }
        else {
            // Check if the end of file (EOF) was reached
            if(cin.eof()) {
                throw EndOfFileException("End of file reached.");
            }
            return string{};
        }
    } // UserCommandParser::readLine

    UserCommand UserCommandParser::parseClientCommand(const string &line) {
        // Split the command line into tokens by spaces
        const auto tokens{StringUtils::splitBySpaces(line)};

        // Check if the tokenization was successful
        if(tokens.empty()) {
            ClientOutput::printClientInternalError(
                    "An unexpected error occurred while proccesing your command. "
                    "Please try entering your command again."
                    );
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // First token represents the command name (type) and the rest are parameters
        const auto commandType = determineCommandType(tokens[0]);
        const vector commandParameters(tokens.begin() + 1, tokens.end());

        // Parse the command based on its type
        switch(commandType) {
            case UserCommandType::AUTH:
                return parseAuthCommand(commandParameters);
            case UserCommandType::JOIN:
                return parseJoinCommand(commandParameters);
            case UserCommandType::RENAME:
                return parseRenameCommand(commandParameters);
            case UserCommandType::HELP:
                return parseHelpCommand(commandParameters);
            default:
                ClientOutput::printClientInternalError(
                        "The provided command '" + tokens[0] + "' is not recognized by the "
                        "client. You may enter the '/help' command to list valid client "
                        "commands and how to use them."
                        );
                return UserCommand{
                    .mCommandType{UserCommandType::INVALID}
                };
        }
    } // UserCommandParser::parseClientCommand

    UserCommand UserCommandParser::parseChatMessage(const string &line) {
        // Copy the message content to a local variable
        string messageContent{line};

        // Validate the message content (e.g. length, allowed symbols)
        const auto messageContentResult =
                UserCommandValidators::validateMessageParameter(CommandParameter::MESSAGE_CONTENT, messageContent);

        // Truncate the message content if necessary
        if(UserCommandValidators::postProccessValidation(CommandParameter::MESSAGE_CONTENT, messageContentResult, messageContent)) {
            return UserCommand{
                .mCommandType{UserCommandType::MESSAGE},
                .mMessageContent{messageContent}
            };
        }
        // If any validation resulted in CommandValidatiorsResult::INVALID
        else {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseChatMessage

    UserCommandType UserCommandParser::determineCommandType(const string &commandToken) {
        // '/auth' command
        if(StringUtils::toLower(commandToken) == CastUtils::castEnumToString(UserCommandType::AUTH)) {
            return UserCommandType::AUTH;
        }
        // '/join' command
        else if(StringUtils::toLower(commandToken) == CastUtils::castEnumToString(UserCommandType::JOIN)) {
            return UserCommandType::JOIN;
        }
        // '/rename' command
        else if(StringUtils::toLower(commandToken) == CastUtils::castEnumToString(UserCommandType::RENAME)) {
            return UserCommandType::RENAME;
        }
        // '/help' command
        else if(StringUtils::toLower(commandToken) == CastUtils::castEnumToString(UserCommandType::HELP)) {
            return UserCommandType::HELP;
        }
        // invalid command
        else {
            return UserCommandType::INVALID;
        }
    } // UserCommandParser::determineCommandType

    UserCommand UserCommandParser::parseAuthCommand(const vector<string> &commandParameters) {
        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_AUTH_PARAMS)) {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Copy the parameters to local variables
        string username{commandParameters[0]};
        string secret{commandParameters[1]};
        string displayName{commandParameters[2]};

        // Validate the parameters (e.g. length, allowed symbols)
        const auto usernameResult = UserCommandValidators::validateMessageParameter(CommandParameter::USERNAME, username);
        const auto secretResult = UserCommandValidators::validateMessageParameter(CommandParameter::SECRET, secret);
        const auto displayNameResult = UserCommandValidators::validateMessageParameter(CommandParameter::DISPLAY_NAME, displayName);

        // Truncate the parameters if necessary
        if(UserCommandValidators::postProccessValidation(CommandParameter::USERNAME, usernameResult, username) &&
            UserCommandValidators::postProccessValidation(CommandParameter::SECRET, secretResult, secret) &&
            UserCommandValidators::postProccessValidation(CommandParameter::DISPLAY_NAME, displayNameResult, displayName)) {
            return UserCommand{
                .mCommandType{UserCommandType::AUTH},
                .mUsername{username},
                .mSecret{secret},
                .mDisplayName{displayName}
            };
        }
        // If any validation resulted in CommandValidatiorsResult::INVALID
        else {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseAuthCommand

    UserCommand UserCommandParser::parseJoinCommand(const vector<string> &commandParameters) {
        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_JOIN_PARAMS)) {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Copy the parameter to a local variable
        string channelId{commandParameters[0]};

        // Validate the parameter (e.g. length, allowed symbols)
        const auto channelIdResult = UserCommandValidators::validateMessageParameter(CommandParameter::CHANNEL_ID, channelId);

        // Truncate the parameter if necessary
        if(UserCommandValidators::postProccessValidation(CommandParameter::CHANNEL_ID, channelIdResult, channelId)) {
            return UserCommand{
                .mCommandType{UserCommandType::JOIN},
                .mChannelId{channelId},
            };
        }
        // If the validation resulted in CommandValidatiorsResult::INVALID
        else {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseJoinCommand

    UserCommand UserCommandParser::parseRenameCommand(const vector<string> &commandParameters) {
        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_RENAME_PARAMS)) {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Copy the parameter to a local variable
        string displayName{commandParameters[0]};

        // Validate the parameter (e.g. length, allowed symbols)
        const auto displayNameResult = UserCommandValidators::validateMessageParameter(CommandParameter::DISPLAY_NAME, displayName);

        // Truncate the parameter if necessary
        if(UserCommandValidators::postProccessValidation(CommandParameter::DISPLAY_NAME, displayNameResult, displayName)) {
            return UserCommand{
                .mCommandType{UserCommandType::RENAME},
                .mDisplayName{commandParameters[2]}
            };
        }
        // If the validation resulted in CommandValidatiorsResult::INVALID
        else {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseRenameCommand

    UserCommand UserCommandParser::parseHelpCommand(const vector<string> &commandParameters) {
        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_HELP_PARAMS)) {
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Help command has no parameters
        return UserCommand{
            .mCommandType{UserCommandType::HELP},
        };
    } // UserCommandParser::parseHelpCommand

    bool UserCommandParser::checkCorrectNumberOfParameters(const vector<string> &commandParameters, const size_t expectedCount) {
        if(commandParameters.size() == expectedCount) {
            return true;
        }
        else {
            ClientOutput::printClientInternalError(
                    "The provided command has an incorrect number of parameters "
                    "(has: " + to_string(commandParameters.size()) + ", expected: " +
                    to_string(expectedCount) + "). You may enter the '/help' command "
                    "to list valid client commands and how to use them."
                    );
            return false;
        }
    } // UserCommandParser::checkCorrectNumberOfParameters
} // IPK25ChatClient::Client::CommandParser

/*** end of file UserCommandParser.cpp ***/
