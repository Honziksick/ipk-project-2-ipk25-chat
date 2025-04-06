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

using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Enums;
using namespace std;

namespace IPK25ChatClient::Exceptions
{
    HelpRequestedException::HelpRequestedException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::SUCCESS,
            cHelpRequestedMsg,
            move(detail)
        } {}

    InvalidArgumentException::InvalidArgumentException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::INVALID_ARGUMENT_ERROR,
            cInvalidArgumentErrorMsg,
            move(detail)
        } {}

    HostnameResolutionException::HostnameResolutionException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::HOSTNAME_RESOLUTION_ERROR,
            cHostnameResolutionErrorMsg,
            move(detail)
        } {}

    InternalErrorException::InternalErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::INTERNAL_ERROR,
            cInternalErrorMsg,
            move(detail)
        } {}

    SocketErrorException::SocketErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::SOCKET_ERROR,
            cSocketErrorMsg,
            move(detail)
        } {}

    ProtocolErrorException::ProtocolErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::PROTOCOL_ERROR,
            cProtocolErrorMsg,
            move(detail)
        } {}

    UknownErrorException::UknownErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::UNKNOWN_ERROR,
            cUnknownErrorMsg,
            move(detail)
        } {}

    TimeoutErrorException::TimeoutErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::TIMEOUT_ERROR,
            cTimeoutErrorMsg,
            move(detail)
        } {}

    UserInterruptionException::UserInterruptionException(string detail) noexcept
        : ChatBaseException{
            ExitCodes::USER_INTERRUPTION_ERROR,
            cUserInterruptionMsg,
            move(detail)
        } {}
} // IPK25ChatClient::Exceptions

/*** end of file ChatExceptions.cpp ***/
