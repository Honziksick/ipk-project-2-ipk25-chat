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
 * Last edit:    03.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the ChatBaseException class used in the       *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatBaseException.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for the ChatBaseException class.
 */

#ifndef CHAT_BASE_EXCEPTION_HPP
#define CHAT_BASE_EXCEPTION_HPP

#include "Enums/ExitCodes.hpp"
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
         */
        ChatBaseException(Enums::ExitCode code, std::string message, std::string detail = "");

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

    private:
        const Enums::ExitCode mCode; /**< The error code.                     */
        const std::string mMessage;   /**< The error message.                  */
        std::string mDetail;          /**< Additional details about the error. */
    }; // ChatBaseException
} // IPK25ChatClient::Exceptions

#endif // CHAT_BASE_EXCEPTION_HPP

/*** end of file ChatBaseException.hpp ***/
