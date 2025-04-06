/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ChatExceptions.cpp                                            *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the ChatBaseException class used in   *
 *               the IPK25 Chat Client project.                                *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatExceptions.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file for the ChatExceptions classes.
 */

#include "Exceptions/ChatExceptions.hpp"
#include "Constants/ExceptionMessages.hpp"
#include "Enums/ExitCodes.hpp"
#include "Utilities/Logger.hpp"

using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Enums;
using namespace std;

namespace IPK25ChatClient::Exceptions
{
    HelpRequestedException::HelpRequestedException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::SUCCESS,
            ExceptionMessages::cHelpRequestedMsg,
            move(detail)
        } {
        logger("HelpRequestedException created with detail: %s", detail.c_str());
    }

    InvalidArgumentException::InvalidArgumentException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::INVALID_ARGUMENT_ERROR,
            ExceptionMessages::cInvalidArgumentErrorMsg,
            move(detail)
        } {
        logger("InvalidArgumentException created with detail: %s", detail.c_str());
    }

    HostnameResolutionException::HostnameResolutionException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::HOSTNAME_RESOLUTION_ERROR,
            ExceptionMessages::cHostnameResolutionErrorMsg,
            move(detail)
        } {
        logger("HostnameResolutionException created with detail: %s", detail.c_str());
    }

    InternalErrorException::InternalErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::INTERNAL_ERROR,
            ExceptionMessages::cInternalErrorMsg,
            move(detail)
        } {
        logger("InternalErrorException created with detail: %s", detail.c_str());
    }

    SocketErrorException::SocketErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::SOCKET_ERROR,
            ExceptionMessages::cSocketErrorMsg,
            move(detail)
        } {
        logger("SocketErrorException created with detail: %s", detail.c_str());
    }

    ProtocolErrorException::ProtocolErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::PROTOCOL_ERROR,
            ExceptionMessages::cProtocolErrorMsg,
            move(detail)
        } {
        logger("ProtocolErrorException created with detail: %s", detail.c_str());
    }

    UknownErrorException::UknownErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::UNKNOWN_ERROR,
            ExceptionMessages::cUnknownErrorMsg,
            move(detail)
        } {
        logger("UknownErrorException created with detail: %s", detail.c_str());
    }

    TimeoutErrorException::TimeoutErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::TIMEOUT_ERROR,
            ExceptionMessages::cTimeoutErrorMsg,
            move(detail)
        } {
        logger("TimeoutErrorException created with detail: %s", detail.c_str());
    }

    UserInterruptionException::UserInterruptionException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::USER_INTERRUPTION_ERROR,
            ExceptionMessages::cUserInterruptionMsg,
            move(detail)
        } {
        logger("UserInterruptionException created with detail: %s", detail.c_str());
    }
} // IPK25ChatClient::Exceptions

/*** end of file ChatExceptions.cpp ***/
