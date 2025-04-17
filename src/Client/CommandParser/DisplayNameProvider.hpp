/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         DisplayNameProvider.hpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      16.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `DisplayNameProvider` class, which         *
 *               provides a thread-safe mechanism to manage the display name   *
 *               of the chat client user.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file DisplayNameProvider.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for the `DisplayNameProvider` class, which manages
 *        a thread-safe display name for the chat client user.
 */

#ifndef DISPLAY_NAME_PROVIDER_HPP
#define DISPLAY_NAME_PROVIDER_HPP

#include "Client/CommandParser/DisplayNameProvider.hpp"
#include <string>  // std::string
#include <mutex>   // std::mutex

namespace IPK25ChatClient::Client::CommandParser
{
    /**
     * @class DisplayNameProvider
     * @brief Provides a thread-safe mechanism to manage the user's display name.
     */
    class DisplayNameProvider {
    public:
        /**
         * @brief Sets the user's display name.
         *
         * @param displayName The new display name to be set.
         */
        void setDisplayName(const std::string &displayName);

        /**
         * @brief Retrieves the user's current display name.
         *
         * @return The current display name as a `std::string`.
         */
        std::string getDisplayName();

        /**
         * @brief Checks if the display name has been set.
         *
         * @return `true` if the display name is set, `false` otherwise.
         */
        bool isDisplayNameSet();

    private:
        std::string mDisplayName;  /**< The display name of the user.                           */
        std::mutex mMutex;         /**< Mutex to ensure thread-safe access to the display name. */
    };
} // IPK25ChatClient::Client::CommandParser

#endif // DISPLAY_NAME_PROVIDER_HPP

/*** end of file DisplayNameProvider.hpp ***/
