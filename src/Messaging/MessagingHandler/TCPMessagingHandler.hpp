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
         * @brief Processes an incoming message.
         * @details This method is responsible for handling a parsed message
         *          and performing the appropriate action based on its type.
         *
         * @param parsedMessage The parsed message to process.
         */
        void processIncomingMessage(const Common::ParsedMessage &parsedMessage) override;
    }; // TCPMessagingHandler
} // IPK25ChatClient::Messaging::Handler

#endif // TCP_MESSAGING_HANDLER_HPP

/*** end of file TCPMessagingHandler.hpp ***/
