/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ExceptionHandler.cpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the ExceptionHandler class, which is        *
 *               responsible for printing error messages and terminating the   *
 *               application with the appropriate exit code when an error      *
 *               exception is caught.                                          *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ExceptionHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file for the ExceptionHandler class.
 */

#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/ExceptionHandler.hpp"
#include "Utilities/Logger.hpp"
#include "Constants/ColorEscapeSequences.hpp"
#include <exception> // std::exception
#include <iostream>  // std::cerr
#include <string>    // std::string

using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Constants;
using namespace std;

namespace IPK25ChatClient::Utilities
{
    void ExceptionHandler::handleError(const exception &exception) {
        logger("Handling error: %s", exception.what());

        // Attempt to cast the original exception to ChatBaseException
        const ChatBaseException *pChatException = getChatException(exception);

        // Create an UnknownErrorException (only used if 'dynamic_cast' above failed)
        const UknownErrorException unknownException{exception.what()};

        // If 'dynamic_cast' above failed, use the address of UnknownException
        if(!pChatException) {
            logger("Unknown exception type, using UknownErrorException");
            pChatException = &unknownException;
        }

        // Now we are 100% sure that the pChatException points to ChatBaseException
        printError(*pChatException);
        terminateProgram(pChatException->code());
    } // ExceptionHandler::handleError()

    void ExceptionHandler::printError(const ChatBaseException &exception) {
        cerr << Color::RED << "Error " << exception.code() << ": " << exception.what() << Color::RESET << endl;
        if(!exception.detail().empty()) {
            cerr << Color::YELLOW << "Detail: " << exception.detail() << Color::RESET << endl;
        }
    } // ExceptionHandler::printError()

    void ExceptionHandler::terminateProgram(const int errorCode) {
        logger("Terminating program with error code: %d", errorCode);
        exit(errorCode);
    } // ExceptionHandler::terminateProgram()

    const ChatBaseException *ExceptionHandler::getChatException(const exception &exception) {
        logger("Getting ChatBaseException from exception: %s", exception.what());
        return dynamic_cast<const ChatBaseException*>(&exception);
    } // ExceptionHandler::getChatException()
} // IPK25ChatClient::Exceptions

/*** end of file ExceptionHandler.cpp ***/
