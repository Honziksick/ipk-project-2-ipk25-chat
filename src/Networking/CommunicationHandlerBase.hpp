/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommunicationHandlerBase.hpp                                  *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  This file declares the `CommunicationHandlerBase` class,      *
 *               which serves as a base class for handling both TCP and UDP    *
 *               communication in the IPK25 Chat Client. It provides common    *
 *               functionality for managing connections, such as checking      *
 *               connection status and closing connections.                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommunicationHandlerBase.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `CommunicationHandlerBase` class for both
 *        TCP and UDP communication handling.
 */

#ifndef COMMUNICATION_HANDLER_BASE_HPP
#define COMMUNICATION_HANDLER_BASE_HPP

#include "Networking/Interfaces/ICommunicationHandler.hpp"
#include "Messaging/Interfaces/IMessageParser.hpp"
#include "Common/CommandLineOptions.hpp"
#include <string>   // std::string
#include <memory>   // std::unique_ptr, std::shared_ptr

namespace IPK25ChatClient::Networking
{
    /**
     * @class CommunicationHandlerBase
     * @brief Base class for handling both TCP and UDP communication in the
     *        IPK25 Chat Client.
     *
     *  @details This class provides common functionality for managing
     *           both TCP and UDP communication, including connection status
     *           checks and connection closure.
     */
    class CommunicationHandlerBase : public ICommunicationHandler {
    public:
        /**
         * @brief Constructs a `CommunicationHandlerBase` object.
         *
         * @param commandLineOptions Command-line options for configuring the handler.
         * @param socketFd Shared file descriptor for the socket connection.
         */
        explicit CommunicationHandlerBase(const Common::CommandLineOptions &commandLineOptions,
                                          const std::shared_ptr<int> &socketFd);

        /**
         * @brief Destroys the `CommunicationHandlerBase` object.
         */
        ~CommunicationHandlerBase() override = default;

    protected:
        static constexpr int SOCKET_CLOSED{-1};     /**< Constant representing a closed socket.      */
        static constexpr bool CONNECTED{true};      /**< Constant representing a connected state.    */
        static constexpr bool DISCONNECTED{false};  /**< Constant representing a disconnected state. */

        std::unique_ptr<Messaging::Parser::IMessageParser> mMessageParser;  /**< Message parser used for processing incoming messages. */
        std::shared_ptr<int> mSocketFd;  /**< Shared file descriptor of the network socket. */
        bool mIsConnected;               /**< Connection status flag.    */
        std::string mServerAddress;      /**< Address of the server.     */
        uint16_t mServerPort;            /**< Port number of the server. */
    }; // CommunicationHandlerBase
} // IPK25ChatClient::Networking

#endif // COMMUNICATION_HANDLER_BASE_HPP

/*** end of file CommunicationHandlerBase.hpp ***/
