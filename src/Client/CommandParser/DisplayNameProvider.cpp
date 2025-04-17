/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         DisplayNameProvider.cpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      16.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `DisplayNameProvider` class, which      *
 *               provides a thread-safe mechanism to manage the display name   *
 *               of the chat client user.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file DisplayNameProvider.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `DisplayNameProvider` class, which ensures
          thread-safe management of the display name for the chat client user.
 */

#include "Client/CommandParser/DisplayNameProvider.hpp"
#include <string>  // std::string
#include <mutex>   // std::mutex

using namespace std;

namespace IPK25ChatClient::Client::CommandParser
{
    void DisplayNameProvider::setDisplayName(const std::string &displayName) {
        lock_guard<mutex> lock(mMutex);
        mDisplayName = displayName;
    } // DisplayNameProvider::setDisplayName

    string DisplayNameProvider::getDisplayName() {
        lock_guard<mutex> lock(mMutex);
        return mDisplayName;
    } // DisplayNameProvider::getDisplayName

    bool DisplayNameProvider::isDisplayNameSet() {
        lock_guard<mutex> lock(mMutex);
        return !mDisplayName.empty();
    } // DisplayNameProvider::isDisplayNameSet
}

/*** end of file DisplayNameProvider.cpp ***/
