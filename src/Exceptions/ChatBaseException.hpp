/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ChatBaseException.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the `ChatBaseException` class used in the     *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatBaseException.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file declaring the `ChatBaseException` class used in the
 *        IPK25 Chat Client project.
 */

#ifndef CHAT_BASE_EXCEPTION_HPP
#define CHAT_BASE_EXCEPTION_HPP

#include "Enums/ExitCodes.hpp"
#include "Enums/ClientInternalErrorMessages.hpp"
#include <exception> // std::exception
#include <string>    // std::string

namespace IPK25ChatClient::Exceptions
{
    /**
     * @class ChatBaseException
     * @brief Exception class for handling errors in the IPK25 Chat Client project.
     */
    class ChatBaseException : public std::exception {
    public:
        /**
         * @brief Constructor for ChatBaseException.
         * @param code The error code.
         * @param message The error message.
         * @param detail Additional details about the error.
         * @param clientInternalError The client internal error message code.
         */
        ChatBaseException(Enums::ExitCode code, std::string message, std::string detail,
                          Enums::ClientInternalErrorMessage clientInternalError);

        /**
         * @brief Returns the error message.
         * @return The error message as a C-style string.
         */
        [[nodiscard]]
        const char *what() const noexcept override;

        /**
         * @brief Returns the error code as integer.
         * @return The error code value.
         */
        [[nodiscard]]
        int code() const noexcept;

        /**
         * @brief Returns additional details about the error.
         * @return The error details as a string.
         */
        [[nodiscard]]
        std::string detail() const noexcept;

        /**
         * @brief Retrieves the client internal error message code of the error
         *        message to be displayed to the user.
         *
         * @return Enums::ClientInternalErrorMessage The client internal error message code.
         */
        [[nodiscard]]
        Enums::ClientInternalErrorMessage clientInternalError() const noexcept;

    protected:
        /**
         * @brief Imports all values from the `Enums::ExitCode` enumeration into
         *        the current namespace.
         */
        using enum Enums::ExitCode;

        /**
         * @brief Imports all values from the `Enums::ClientInternalErrorMessage`
         *        enumeration into the current namespace.
         */
        using enum Enums::ClientInternalErrorMessage;

        const Enums::ExitCode mCode;  /**< The error code.    */
        const std::string mMessage;   /**< The error message. */
        std::string mDetail;          /**< Additional details about the error. */
        Enums::ClientInternalErrorMessage mClientInternalError;  /**< Client internal error message for the user. */
    }; // ChatBaseException
} // IPK25ChatClient::Exceptions

#endif // CHAT_BASE_EXCEPTION_HPP

/*** end of file ChatBaseException.hpp ***/
