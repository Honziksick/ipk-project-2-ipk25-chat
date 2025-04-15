/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageIDProvider.cpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `MessageIdProvider` class, which        *
 *               provides functionality for generating and managing unique     *
 *               message IDs in a thread-safe manner.                          *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageIDProvider.cpp
 * @author Jan Kalina <xkalinj00>
 * @brief Implementation of the `MessageIdProvider` class for managing unique
 *        message IDs.
 */

#include "Messaging/MessageBuilder/MessageIdProvider.hpp"
#include <mutex>    // std::mutex
#include <cstdint>  // uint16_t

using namespace std;

namespace IPK25ChatClient::Messaging
{
    MessageIdProvider::MessageIdProvider() : mCurrentIdCounter{0} {}

    uint16_t MessageIdProvider::getCurrentMessageId() {
        lock_guard<mutex> lock{mMutex};  // Automatically unlocks when exiting scope
        return mCurrentIdCounter;
    } // MessageIdProvider::getCurrentMessageId

    uint16_t MessageIdProvider::getNextMessageId() {
        lock_guard<mutex> lock{mMutex};  // Automatically unlocks when exiting scope

        // Get the next message ID
        const uint16_t nextMessageId = mCurrentIdCounter;
        mCurrentIdCounter++;

        return nextMessageId;
    } // MessageIdProvider::getNextMessageId
} // IPK25ChatClient::Messaging

/*** end of file MessageIDProvider.cpp ***/
