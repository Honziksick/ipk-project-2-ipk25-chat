/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ChatBaseException.cpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    03.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the ChatBaseException class used in   *
 *               the IPK25 Chat Client project.                                *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatBaseException.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file for the ChatBaseException class.
 */

#include "Exceptions/ChatBaseException.hpp"
#include <utility>  // std::move

using namespace std;

namespace IPK25ChatClient::Exceptions
{
    ChatBaseException::ChatBaseException(const Enums::ExitCode code, string message, string detail)
        : mCode{code}, mMessage{move(message)}, mDetail{move(detail)} {}

    const char *ChatBaseException::what() const noexcept {
        return mMessage.c_str();
    } // ChatBaseException::what()

    int ChatBaseException::code() const noexcept {
        return static_cast<int>(mCode);
    } // ChatBaseException::code()

    string ChatBaseException::detail() const noexcept {
        return mDetail;
    } // ChatBaseException::detail()
} // IPK25ChatClient::Exceptions

/*** end of file ChatBaseException.cpp ***/
