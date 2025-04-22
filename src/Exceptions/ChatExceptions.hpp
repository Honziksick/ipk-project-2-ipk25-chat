/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ChatExceptions.hpp                                            *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `ChatExceptions` classes used in the      *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatExceptions.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for the `ChatExceptions` classes.
 */

#ifndef CHAT_EXCEPTIONS_HPP
#define CHAT_EXCEPTIONS_HPP

#include "Exceptions/ChatBaseException.hpp"
#include "Enums/ClientInternalErrorMessages.hpp"
#include <string> // std::string

namespace IPK25ChatClient::Exceptions
{
    /**
     * @class HelpRequestedException
     * @brief Exception class for user requesting help.
     */
    class HelpRequestedException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for HelpRequestedException.
         *
         * @param detail Additional information if needed.
         * @param clientInternalError Client internal error message code.
         */
        explicit HelpRequestedException(std::string detail = "",
                                        Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // HelpRequestedException

    /**
     * @class EndOfFileException
     * @brief Exception class for user requesting help.
     */
    class EndOfFileException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for EndOfFileException.
         *
         * @param detail Additional information if needed.
         * @param clientInternalError Client internal error message code.
         */
        explicit EndOfFileException(std::string detail = "",
                                    Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // EndOfFileException

    /**
     * @class ServerSendByeException
     * @brief Exception class used when server sends Bye message in UDP variant.
     */
    class ServerSendByeException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for EndOfFileException.
         *
         * @param detail Additional information if needed.
         * @param clientInternalError Client internal error message code.
         */
        explicit ServerSendByeException(std::string detail = "",
                                        Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // ServerSendByeException

    /**
     * @class ServerDisconnectedException
     * @brief Exception class for user requesting help.
     */
    class ServerDisconnectedException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for ServerDisconnectedException.
         *
         * @param detail Additional information if needed.
         * @param clientInternalError Client internal error message code.
         */
        explicit ServerDisconnectedException(std::string detail = "",
                                             Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // ServerDisconnectedException

    /**
     * @class InvalidArgumentException
     * @brief Exception class for invalid arguments.
     * @param clientInternalError Client internal error message code.
     */
    class InvalidArgumentException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for InvalidArgumentException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit InvalidArgumentException(std::string detail = "",
                                          Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // InvalidArgumentException

    /**
     * @class HostnameResolutionErrorException
     * @brief Exception class for hostname resolution errors.
     */
    class HostnameResolutionErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for HostnameResolutionException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit HostnameResolutionErrorException(std::string detail = "",
                                                  Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // HostnameResolutionErrorException

    /**
     * @class InternalErrorException
     * @brief Exception class for internal errors.
     */
    class InternalErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for InternalErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit InternalErrorException(std::string detail = "",
                                        Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // InternalErrorException

    /**
     * @class ConstructorErrorException
     * @brief Exception class used when error occurs during the construction of an object.
     */
    class ConstructorErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for ConstructorErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit ConstructorErrorException(std::string detail = "",
                                           Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // ConstructorErrorException

    /**
     * @class ConnectionErrorException
     * @brief Exception class for socket errors.
     */
    class ConnectionErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for ConnectionErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit ConnectionErrorException(std::string detail = "",
                                          Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // ConnectionErrorException

    /**
     * @class ProtocolErrorException
     * @brief Exception class for protocol errors.
     */
    class ProtocolErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for ProtocolErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit ProtocolErrorException(std::string detail = "",
                                        Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // ProtocolErrorException

    /**
     * @class UknownErrorException
     * @brief Exception class for unknown errors.
     */
    class UknownErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for UknownErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit UknownErrorException(std::string detail = "",
                                      Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // UknownErrorException

    /**
     * @class UnestablishedConnectionErrorException
     * @brief Exception class for errors caused by unestablished connection.
     */
    class UnestablishedConnectionErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for UnestablishedConnectionErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit UnestablishedConnectionErrorException(std::string detail = "",
                                                       Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // UnestablishedConnectionErrorException

    /**
     * @class MessageLostErrorException
     * @brief Exception class for timeout errors.
     */
    class MessageLostErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for TimeoutErrorException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit MessageLostErrorException(std::string detail = "",
                                           Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // MessageLostErrorException


    /**
     * @class TimeoutErrorException
     * @brief Exception class used when reply 5s timeout is reached.
     */
    class TimeoutErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for EndOfFileException.
         *
         * @param detail Additional information if needed.
         * @param clientInternalError Client internal error message code.
         */
        explicit TimeoutErrorException(std::string detail = "",
                                       Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // TimeoutErrorException

    /**
     * @class UserInterruptionException
     * @brief Exception class for user interruptions.
     */
    class UserInterruptionException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for UserInterruptionException.
         *
         * @param detail Additional information about the error.
         * @param clientInternalError Client internal error message code.
         */
        explicit UserInterruptionException(std::string detail = "",
                                           Enums::ClientInternalErrorMessage clientInternalError = CLIENT_UNKNOWN) noexcept;
    }; // UserInterruptionException
} // IPK25ChatClient::Exceptions

#endif // CHAT_EXCEPTIONS_HPP

/*** end of file ChatExceptions.hpp ***/
