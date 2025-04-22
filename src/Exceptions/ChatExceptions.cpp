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
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation file for the `ChatBaseException` class used    *
 *               in the IPK25 Chat Client project.                             *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatExceptions.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file for the `ChatExceptions` classes.
 */

#include "Exceptions/ChatExceptions.hpp"
#include "Constants/ExceptionMessages.hpp"
#include "Enums/ClientInternalErrorMessages.hpp"
#include "Enums/ExitCodes.hpp"
#include <string>   // std::string
#include <utility>  // std::move

using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Enums;
using namespace std;

namespace IPK25ChatClient::Exceptions
{
    HelpRequestedException::HelpRequestedException(string detail,
                                                   const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            SUCCESS,
            ExceptionMessages::HELP_REQUESTED_MSG,
            move(detail),
            clientInternalError
        } {}

    EndOfFileException::EndOfFileException(string detail,
                                           const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            SUCCESS,
            ExceptionMessages::END_OF_FILE_MSG,
            move(detail),
            clientInternalError
        } {}

    ServerSendByeException::ServerSendByeException(string detail,
                                                   const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            SUCCESS,
            ExceptionMessages::SERVER_SEND_BYE,
            move(detail),
            clientInternalError
        } {}

    ServerDisconnectedException::ServerDisconnectedException(string detail,
                                                             const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            SERVER_DISCONNECTED_ERROR,
            ExceptionMessages::SERVER_DISCONNECTED_MSG,
            move(detail),
            clientInternalError
        } {}

    InvalidArgumentException::InvalidArgumentException(string detail,
                                                       const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            INVALID_ARGUMENT_ERROR,
            ExceptionMessages::INVALID_ARGUMENT_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    HostnameResolutionErrorException::HostnameResolutionErrorException(string detail,
                                                                       const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            HOSTNAME_RESOLUTION_ERROR,
            ExceptionMessages::HOSTNAME_RESOLUTION_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    InternalErrorException::InternalErrorException(string detail,
                                                   const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            INTERNAL_ERROR,
            ExceptionMessages::INTERNAL_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    ConstructorErrorException::ConstructorErrorException(string detail,
                                                         const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            INTERNAL_ERROR,
            ExceptionMessages::CONSTRUCTOR_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    ConnectionErrorException::ConnectionErrorException(string detail,
                                                       const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            CONNECTION_ERROR,
            ExceptionMessages::CONNECTION_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    ProtocolErrorException::ProtocolErrorException(string detail,
                                                   const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            PROTOCOL_ERROR,
            ExceptionMessages::PROTOCOL_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    UknownErrorException::UknownErrorException(string detail,
                                               const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            UNKNOWN_ERROR,
            ExceptionMessages::UNKNOWN_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    UnestablishedConnectionErrorException::UnestablishedConnectionErrorException(string detail,
                                                                                 const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            UNESTABLISHED_ERROR,
            ExceptionMessages::UNESTABLISHED_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}

    MessageLostErrorException::MessageLostErrorException(string detail,
                                                         const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            MESSAGE_LOST_ERROR,
            ExceptionMessages::MESSAGE_LOST_MSG,
            move(detail),
            clientInternalError
        } {}

    UserInterruptionException::UserInterruptionException(string detail,
                                                         const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            SUCCESS,
            ExceptionMessages::USER_INTERRUPTION_MSG,
            move(detail),
            clientInternalError
        } {}

    TimeoutErrorException::TimeoutErrorException(string detail,
                                                 const ClientInternalErrorMessage clientInternalError) noexcept
        : ChatBaseException{
            TIMEOUT_ERROR,
            ExceptionMessages::TIMEOUT_ERROR_MSG,
            move(detail),
            clientInternalError
        } {}
} // IPK25ChatClient::Exceptions

/*** end of file ChatExceptions.cpp ***/
