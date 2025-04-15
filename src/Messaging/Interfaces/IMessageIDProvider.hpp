/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         IMessageIDProvider.hpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      14.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining the `IMessageIdProvider` interface       *
 *               for providing message IDs in the IPK25 Chat Client.           *
 *                                                                             *
 ******************************************************************************/
/**
 * @file IMessageIDProvider.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Defines the `IMessageIdProvider` interface for managing message IDs
 *        in the IPK25 Chat Client.
 */
#ifndef I_MESSAGE_ID_PROVIDER_HPP
#define I_MESSAGE_ID_PROVIDER_HPP

#include <cstdint>  // uint16_t

namespace IPK25ChatClient::Messaging
{
    /**
     * @class IMessageIdProvider
     * @brief Interface for providing and managing message IDs.
     *
     * @details This interface defines methods for retrieving the current
     *          message ID and generating the next message ID.
     */
    class IMessageIdProvider {
    public:
        /**
         * @brief Virtual destructor for the IMessageIdProvider interface.
         */
        virtual ~IMessageIdProvider() = default;

        /**
         * @brief Retrieves the current message ID.
         *
         * @return The current message ID as a 16-bit unsigned integer.
         */
        virtual uint16_t getCurrentMessageId() = 0;

        /**
         * @brief Generates and retrieves the next message ID.
         *
         * @return The next message ID as a 16-bit unsigned integer.
         */
        virtual uint16_t getNextMessageId() = 0;
    };
} // IPK25ChatClient::Messaging

#endif // I_MESSAGE_ID_PROVIDER_HPP

/*** end of file IMessageIDProvider.hpp ***/
