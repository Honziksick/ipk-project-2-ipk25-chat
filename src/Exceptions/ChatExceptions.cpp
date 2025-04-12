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
 * Last edit:    10.04.2025                                                    *
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
            ExitCode::SUCCESS,
            ExceptionMessages::HELP_REQUESTED_MSG,
            move(detail)
        } {}

    InvalidArgumentException::InvalidArgumentException(string detail) noexcept
        : ChatBaseException{
            ExitCode::INVALID_ARGUMENT_ERROR,
            ExceptionMessages::INVALID_ARGUMENT_ERROR_MSG,
            move(detail)
        } {}

    HostnameResolutionErrorException::HostnameResolutionErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCode::HOSTNAME_RESOLUTION_ERROR,
            ExceptionMessages::HOSTNAME_RESOLUTION_ERROR_MSG,
            move(detail)
        } {}

    InternalErrorException::InternalErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCode::INTERNAL_ERROR,
            ExceptionMessages::INTERNAL_ERROR_MSG,
            move(detail)
        } {}

    ConnectionErrorException::ConnectionErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCode::CONNECTION_ERROR,
            ExceptionMessages::CONNECTION_ERROR_MSG,
            move(detail)
        } {}

    ProtocolErrorException::ProtocolErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCode::PROTOCOL_ERROR,
            ExceptionMessages::PROTOCOL_ERROR_MSG,
            move(detail)
        } {}

    UknownErrorException::UknownErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCode::UNKNOWN_ERROR,
            ExceptionMessages::UNKNOWN_ERROR_MSG,
            move(detail)
        } {}

    TimeoutErrorException::TimeoutErrorException(string detail) noexcept
        : ChatBaseException{
            ExitCode::TIMEOUT_ERROR,
            ExceptionMessages::TIMEOUT_ERROR_MSG,
            move(detail)
        } {}

    UserInterruptionException::UserInterruptionException(string detail) noexcept
        : ChatBaseException{
            ExitCode::USER_INTERRUPTION_ERROR,
            ExceptionMessages::USER_INTERRUPTION_MSG,
            move(detail)
        } {}
} // IPK25ChatClient::Exceptions

/*** end of file ChatExceptions.cpp ***/
