/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TCPMessagingHandler.hpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      15.04.2025                                                    *
 * Last edit:    16.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining the `TcpMessagingHandler` class, which   *
 *               handles TCP-based messaging operations in the IPK25 Chat      *
 *               Client.                                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TCPMessagingHandler.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `TcpMessagingHandler` class for handling
 *        TCP-based messaging.
 */

#ifndef TCP_MESSAGING_HANDLER_HPP
#define TCP_MESSAGING_HANDLER_HPP

#include "Messaging/MessagingHandler/MessagingHandlerBase.hpp"
#include "Common/ParsedMessage.hpp"

namespace IPK25ChatClient::Messaging::Handler
{
    /**
     * @class TcpMessagingHandler
     * @brief Handles TCP-based messaging operations.
     *
     * @details This class is responsible for processing incoming messages and
     *          sending various types of messages (e.g., authentication, join,
     *          message, and goodbye) over a TCP connection. It extends the
     *          `MessagingHandlerBase` class.
     */
    class TcpMessagingHandler final : public MessagingHandlerBase {
    public:
        /**
         * @brief `TcpMessagingHandler` inherits constructors from `MessagingHandlerBase`.
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
    }; // TCPMessagingHandler
} // IPK25ChatClient::Messaging::Handler

#endif // TCP_MESSAGING_HANDLER_HPP

/*** end of file TCPMessagingHandler.hpp ***/
