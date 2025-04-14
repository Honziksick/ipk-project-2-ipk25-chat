/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         StringUtils.cpp                                               *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      13.04.2025                                                    *
 * Last edit:    13.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the `StringUtils`    *
 *               class, which provides utility functions for string            *
 *               operations (e.g., toLower, splitBySpaces).              *
 *                                                                             *
 ******************************************************************************/
/**
 * @file StringUtils.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `StringUtils` class for string operations.
 */

#include "StringUtils.hpp"
#include <string>     // std::string
#include <vector>     // std::vector
#include <cctype>     // std::tolower
#include <algorithm>  // std::transform
#include <sstream>    // std::istringstream

using namespace std;

namespace IPK25ChatClient::Utilities
{
    string StringUtils::toLower(const string &str) {
        string lowerCaseString = str;
        ranges::transform(lowerCaseString, lowerCaseString.begin(),
                          [](const unsigned char character) {
                              return tolower(character);
                          });
        return lowerCaseString;
    } // StringUtils::toLower

    vector<string> StringUtils::splitBySpaces(const string &str) {
        vector<string> tokenVector;  // Vector of future tokens
        istringstream stream{str};   // Conversion of string to input stream
        string token;                // Temporary variable for each token

        // Read tokens until the end of the line and ignores multiple spaces
        while(stream >> token) {
            tokenVector.emplace_back(token);
        }

        return tokenVector;
    } // StringUtils::splitBySpaces

    bool StringUtils::truncateOverReference(string &str, const size_t maxLength) {
        if (str.length() > maxLength) {
            str = str.substr(0, maxLength);
            return true;
        }
        return false;
    } // StringUtils::truncateOverReference
} // IPK25ChatClient::Utilities

/*** end of file StringUtils.cpp ***/
