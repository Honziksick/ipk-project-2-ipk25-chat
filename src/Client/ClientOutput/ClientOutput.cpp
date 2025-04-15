/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ClientOutput.cpp                                              *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      11.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the ClientOutput class, which         *
 *               provides static methods for printing various types of         *
 *               client messages and errors to the standard output.            *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ClientOutput.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file of the `ClientOutput` class, which provides static
 *        methods for printing client messages and errors.
 */

#include "Client/ClientOutput/ClientOutput.hpp"
#include "Constants/MessageKeywords.hpp"
#include "Utilities/StringUtils.hpp"
#include <string>       // std::string
#include <string_view>  // std::string_view
#include <iostream>     // std::cout

using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Client::Output
{
    void ClientOutput::printClientIncomingMessage(const string_view &displayName, const string_view &messageContent) {
        cout << displayName << ": " << messageContent << '\n';
    } // ClientOutput::printClientIncomingMessage

    void ClientOutput::printClientIncomingError(const string_view &displayName, const string_view &messageContent) {
        cout << "ERROR FROM " << displayName << ": " << messageContent << '\n';
    } // ClientOutput::printClientIncomingError

    void ClientOutput::printClientInternalError(const string_view &messageContent) {
        cout << "ERROR: " << messageContent << '\n';
    } // ClientOutput::printClientInternalError

    void ClientOutput::printClientReply(const string &result, const string &messageContent) {
        if(StringUtils::compareKeywordsCaseInsesitive(result, MessageKeywordsLowerCase::OK_LC)) {
            cout << "Action Success: " << messageContent << '\n';
        }
        else {
            cout << "Action Failure: " << messageContent << '\n';
        }
    } // ClientOutput::printClientReply
} // IPK25ChatClient::Client::Output

/*** end of file ClientOutput.cpp ***/
