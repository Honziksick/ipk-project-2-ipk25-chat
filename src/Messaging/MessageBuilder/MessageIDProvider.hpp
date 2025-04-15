/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageIDProvider.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `MessageIdProvider` class, which provides *
 *               functionality for generating and managing unique message IDs  *
 *               in a thread-safe manner.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageIDProvider.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MessageIdProvider` class for generating
 *        unique message IDs.
 */

#ifndef MESSAGE_ID_PROVIDER_HPP
#define MESSAGE_ID_PROVIDER_HPP

#include "Messaging/Interfaces/IMessageIDProvider.hpp"
#include <mutex>    // std::mutex
#include <cstdint>  // uint16_t

namespace IPK25ChatClient::Messaging::Builder
{
    /**
     * @class MessageIdProvider
     * @brief A thread-safe implementation of `IMessageIdProvider` for managing
     *        message IDs.
     *
     * @details This class provides methods to retrieve the current message ID
     *          and generate the next unique message ID in a thread-safe manner
     *          using a mutex for synchronization.
     */
    class MessageIdProvider final : public IMessageIdProvider {
    public:
        /**
         * @brief Constructs a new `MessageIdProvider` object.
         */
        explicit MessageIdProvider();

        /**
         * @brief Default destructor.
         */
        ~MessageIdProvider() override = default;

        /**
         * @brief Retrieves the current message ID without incrementing it.
         *
         * @return The current message ID as a 16-bit unsigned integer.
         */
        uint16_t getCurrentMessageId() override;

        /**
         * @brief Generates and retrieves the next unique message ID.
         *
         * @details This method increments the internal message ID counter
         *          in a thread-safe manner and returns the new value.
         *
         * @return The next unique message ID as a 16-bit unsigned integer.
         */
        uint16_t getNextMessageId() override;

    private:
        uint16_t mCurrentIdCounter;  /**< The current message ID counter.                           */
        std::mutex mMutex;           /**< Mutex for synchronizing access to the message ID counter. */
    }; // MessageIdProvider
} // IPK25ChatClient::Messaging::Builder

#endif // MESSAGE_ID_PROVIDER_HPP

/*** end of file MessageIDProvider.hpp ***/
