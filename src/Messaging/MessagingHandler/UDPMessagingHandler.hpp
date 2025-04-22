/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         UDPMessagingHandler.hpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      18.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining the `UdpMessagingHandler` class, which   *
 *               handles UDP-based messaging operations in the IPK25 Chat      *
 *               Client.                                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file UDPMessagingHandler.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `UdpMessagingHandler` class for handling
 *        UDP-based messaging.
 */

#ifndef UDP_MESSAGING_HANDLER_HPP
#define UDP_MESSAGING_HANDLER_HPP

#include "Messaging/MessagingHandler/MessagingHandlerBase.hpp"
#include "Common/ParsedMessage.hpp"

namespace IPK25ChatClient::Messaging::Handler
{
    class UdpMessagingHandler final : public MessagingHandlerBase {
    public:
        /**
         * @brief `UdpMessagingHandler` inherits constructors from `MessagingHandlerBase`.
         */
        using MessagingHandlerBase::MessagingHandlerBase;

        /**
         * @brief Handles an incoming message from the server.
         * @details This method processes a parsed message and performs the
         *          appropriate action based on its type, such as displaying a
         *          reply, message, or an error.
         *
         * @param parsedMessage The parsed message to be processed.
         */
        void displayIncomingMessage(const Common::ParsedMessage &parsedMessage) override;
    }; // UdpMessagingHandler
} // IPK25ChatClient::Messaging::Handler

#endif // UDP_MESSAGING_HANDLER_HPP

/*** end of file UDPMessagingHandler.hpp ***/
