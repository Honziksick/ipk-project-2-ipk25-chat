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
 * Last edit:    18.04.2025                                                    *
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
#include "Client/CommandParser/DisplayNameProvider.hpp"
#include "Validators/MessageParametersValidator.hpp"
#include "Client/ClientOutput/ClientOutput.hpp"
#include "Common/UserCommand.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Constants/ClientLimits.hpp"
#include "Enums/UserCommandTypes.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/ClientInternalErrorMessages.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <string>    // std::string, std::getline(), std::to_string()
#include <vector>    // std::vector
#include <memory>    // std::make_unique
#include <iostream>  // std::cin, std::getline()
#include <cstring>   // std::strerror

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
    UserCommandParser::UserCommandParser(const std::shared_ptr<DisplayNameProvider> &displayNameProvider)
        : mMessageParametersValidator{make_unique<MessageParametersValidator>()}, mDisplayNameProvider{displayNameProvider} {}

    UserCommand UserCommandParser::parseCommandLine() {
        logger("Parsing command line started.");

        // Read a line from the standard input ('\n' is read but not included)
        const string line{readLine()};

        // Check if full line was read
        if(line.empty()) {
            logger("Line is empty.");
            return UserCommand{
                .mCommandType = UserCommandType::INVALID
            };
        }

        // If the line starts with '/', parse it as a client command
        if(line[0] == '/') {
            logger("Line identified as a client command.");
            return parseClientCommand(line);
        }
        // Else, parse it as a chat message
        else {
            logger("Line identified as a chat message.");
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
                throw EndOfFileException();
            }
            return string{};
        }
    } // UserCommandParser::readLine

    UserCommand UserCommandParser::parseClientCommand(const string &line) const {
        logger("Parsing client command: %s", line.c_str());

        // Split the command line into tokens by spaces
        const auto tokens{StringUtils::splitBySpaces(line)};

        // Check if the tokenization was successful
        if(tokens.empty()) {
            logger("Tokenization failed, no tokens found.");
            throw InternalErrorException(
                    "An unexpected error occurred while proccesing your command. "
                    "Please try entering your command again.",
                    ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                    );
        }

        // First token represents the command name (type) and the rest are parameters
        const auto commandType = determineCommandType(tokens[0]);
        const vector commandParameters(tokens.begin() + 1, tokens.end());

        // Parse the command based on its type
        switch(commandType) {
            case UserCommandType::AUTH:
                logger("Command type identified as AUTH.");
                return parseAuthCommand(commandParameters);
            case UserCommandType::JOIN:
                logger("Command type identified as JOIN.");
                return parseJoinCommand(commandParameters);
            case UserCommandType::RENAME:
                logger("Command type identified as RENAME.");
                return parseRenameCommand(commandParameters);
            case UserCommandType::HELP:
                logger("Command type identified as HELP.");
                return parseHelpCommand(commandParameters);
            default:
                logger("Invalid command type: %s", tokens[0].c_str());
                ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_BAD_COMMAND);
                return UserCommand{
                    .mCommandType{UserCommandType::INVALID}
                };
        }
    } // UserCommandParser::parseClientCommand

    UserCommand UserCommandParser::parseChatMessage(const string &line) const {
        logger("Parsing chat message: %s", line.c_str());

        // Copy the message content to a local variable
        string messageContent{line};

        // Validate the message content (e.g. length, allowed symbols)
        const auto messageContentResult =
                mMessageParametersValidator->validateMessageParameter(MessageParameter::MESSAGE_CONTENT, messageContent);

        // Truncate the message content if necessary
        if(mMessageParametersValidator->postProcessValidation(MessageParameter::MESSAGE_CONTENT, messageContentResult, messageContent)) {
            logger("Chat message validation successful.");
            return UserCommand{
                .mCommandType{UserCommandType::MESSAGE},
                .mMessageContent{messageContent}
            };
        }
        // If any validation resulted in CommandValidatiorsResult::INVALID
        else {
            logger("Chat message validation failed.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseChatMessage

    UserCommandType UserCommandParser::determineCommandType(const string &commandToken) {
        logger("Determining command type for token: %s", commandToken.c_str());

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

    UserCommand UserCommandParser::parseAuthCommand(const vector<string> &commandParameters) const {
        logger("Parsing AUTH command.");

        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_AUTH_PARAMS)) {
            logger("Incorrect number of parameters for AUTH command.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Copy the parameters to local variables
        string username{commandParameters[0]};
        string secret{commandParameters[1]};
        string displayName{commandParameters[2]};

        // Validate the parameters (e.g. length, allowed symbols)
        const auto usernameResult = mMessageParametersValidator->validateMessageParameter(MessageParameter::USERNAME, username);
        const auto secretResult = mMessageParametersValidator->validateMessageParameter(MessageParameter::SECRET, secret);
        const auto displayNameResult = mMessageParametersValidator->validateMessageParameter(MessageParameter::DISPLAY_NAME, displayName);

        // Truncate the parameters if necessary
        if(mMessageParametersValidator->postProcessValidation(MessageParameter::USERNAME, usernameResult, username) &&
            mMessageParametersValidator->postProcessValidation(MessageParameter::SECRET, secretResult, secret) &&
            mMessageParametersValidator->postProcessValidation(MessageParameter::DISPLAY_NAME, displayNameResult, displayName)) {
            mDisplayNameProvider->setDisplayName(displayName);  // Update the user's display name
            logger("AUTH command validation successful.");
            return UserCommand{
                .mCommandType{UserCommandType::AUTH},
                .mUsername{username},
                .mSecret{secret},
                .mDisplayName{displayName}
            };
        }
        // If any validation resulted in CommandValidatiorsResult::INVALID
        else {
            logger("AUTH command validation failed.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseAuthCommand

    UserCommand UserCommandParser::parseJoinCommand(const vector<string> &commandParameters) const {
        logger("Parsing JOIN command.");

        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_JOIN_PARAMS)) {
            logger("Incorrect number of parameters for JOIN command.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Copy the parameter to a local variable
        string channelId{commandParameters[0]};

        // Validate the parameter (e.g. length, allowed symbols)
        const auto channelIdResult = mMessageParametersValidator->validateMessageParameter(MessageParameter::CHANNEL_ID, channelId);

        // Truncate the parameter if necessary
        if(mMessageParametersValidator->postProcessValidation(MessageParameter::CHANNEL_ID, channelIdResult, channelId)) {
            logger("JOIN command validation successful.");
            return UserCommand{
                .mCommandType{UserCommandType::JOIN},
                .mChannelId{channelId},
            };
        }
        // If the validation resulted in CommandValidatiorsResult::INVALID
        else {
            logger("JOIN command validation failed.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseJoinCommand

    UserCommand UserCommandParser::parseRenameCommand(const vector<string> &commandParameters) const {
        logger("Parsing RENAME command.");

        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_RENAME_PARAMS)) {
            logger("Incorrect number of parameters for RENAME command.");

            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Copy the parameter to a local variable
        string displayName{commandParameters[0]};

        // Validate the parameter (e.g. length, allowed symbols)
        const auto displayNameResult = mMessageParametersValidator->validateMessageParameter(MessageParameter::DISPLAY_NAME, displayName);

        // Truncate the parameter if necessary
        if(mMessageParametersValidator->postProcessValidation(MessageParameter::DISPLAY_NAME, displayNameResult, displayName)) {
            logger("RENAME command validation successful.");

            // Update the user's display name
            mDisplayNameProvider->setDisplayName(displayName);
            logger("User renamed itself to: %s", mDisplayNameProvider->getDisplayName().c_str());

            return UserCommand{
                .mCommandType{UserCommandType::RENAME},
                .mDisplayName{commandParameters[0]}
            };
        }
        // If the validation resulted in CommandValidatiorsResult::INVALID
        else {
            logger("RENAME command validation failed.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID},
            };
        }
    } // UserCommandParser::parseRenameCommand

    UserCommand UserCommandParser::parseHelpCommand(const vector<string> &commandParameters) {
        logger("Parsing HELP command.");

        // Check if the command has the correct number of parameters
        if(!checkCorrectNumberOfParameters(commandParameters, ClientLimits::EXPECTED_NUMBER_OF_HELP_PARAMS)) {
            logger("Incorrect number of parameters for HELP command.");
            return UserCommand{
                .mCommandType{UserCommandType::INVALID}
            };
        }

        // Help command has no parameters
        logger("HELP command validation successful.");
        return UserCommand{
            .mCommandType{UserCommandType::HELP},
        };
    } // UserCommandParser::parseHelpCommand

    bool UserCommandParser::checkCorrectNumberOfParameters(const vector<string> &commandParameters, const size_t expectedCount) {
        logger("Checking number of parameters: has %zu, expected %zu.", commandParameters.size(), expectedCount);

        if(commandParameters.size() == expectedCount) {
            return true;
        }
        else {
            logger("Incorrect number of parameters.");
            ClientOutput::printClientInternalError(ClientInternalErrorMessage::CLIENT_BAD_COMMAND);
            return false;
        }
    } // UserCommandParser::checkCorrectNumberOfParameters
} // IPK25ChatClient::Client::CommandParser

/*** end of file UserCommandParser.cpp ***/
