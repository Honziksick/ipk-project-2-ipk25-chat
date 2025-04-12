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
 * Last edit:    10.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the ChatExceptions classes used in the        *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatExceptions.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for the ChatExceptions classes.
 */

#ifndef CHAT_EXCEPTIONS_HPP
#define CHAT_EXCEPTIONS_HPP

#include "Exceptions/ChatBaseException.hpp"
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
         * @param detail Additional information if needed.
         */
        explicit HelpRequestedException(std::string detail = "") noexcept;
    }; // HelpRequestedException

    /**
     * @class InvalidArgumentException
     * @brief Exception class for invalid arguments.
     */
    class InvalidArgumentException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for InvalidArgumentException.
         * @param detail Additional information about the error.
         */
        explicit InvalidArgumentException(std::string detail = "") noexcept;
    }; // InvalidArgumentException

    /**
     * @class HostnameResolutionErrorException
     * @brief Exception class for hostname resolution errors.
     */
    class HostnameResolutionErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for HostnameResolutionException.
         * @param detail Additional information about the error.
         */
        explicit HostnameResolutionErrorException(std::string detail = "") noexcept;
    }; // HostnameResolutionErrorException

    /**
     * @class InternalErrorException
     * @brief Exception class for internal errors.
     */
    class InternalErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for InternalErrorException.
         * @param detail Additional information about the error.
         */
        explicit InternalErrorException(std::string detail = "") noexcept;
    }; // InternalErrorException

    /**
     * @class ConnectionErrorException
     * @brief Exception class for socket errors.
     */
    class ConnectionErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for ConnectionErrorException.
         * @param detail Additional information about the error.
         */
        explicit ConnectionErrorException(std::string detail = "") noexcept;
    }; // ConnectionErrorException

    /**
     * @class ProtocolErrorException
     * @brief Exception class for protocol errors.
     */
    class ProtocolErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for ProtocolErrorException.
         * @param detail Additional information about the error.
         */
        explicit ProtocolErrorException(std::string detail = "") noexcept;
    }; // ProtocolErrorException

    /**
     * @class UknownErrorException
     * @brief Exception class for unknown errors.
     */
    class UknownErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for UknownErrorException.
         * @param detail Additional information about the error.
         */
        explicit UknownErrorException(std::string detail = "") noexcept;
    }; // UknownErrorException

    /**
     * @class TimeoutErrorException
     * @brief Exception class for timeout errors.
     */
    class TimeoutErrorException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for TimeoutErrorException.
         * @param detail Additional information about the error.
         */
        explicit TimeoutErrorException(std::string detail = "") noexcept;
    }; // TimeoutErrorException

    /**
     * @class UserInterruptionException
     * @brief Exception class for user interruptions.
     */
    class UserInterruptionException final : public ChatBaseException {
    public:
        /**
         * @brief Constructor for UserInterruptionException.
         * @param detail Additional information about the error.
         */
        explicit UserInterruptionException(std::string detail = "") noexcept;
    }; // UserInterruptionException
} // IPK25ChatClient::Exceptions

#endif // CHAT_EXCEPTIONS_HPP

/*** end of file ChatExceptions.hpp ***/
