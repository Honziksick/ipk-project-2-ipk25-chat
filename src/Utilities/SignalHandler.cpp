/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         SignalHandler.cpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `SignalHandler` class, which is         *
 *               responsible for handling system signals.                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file SignalHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file for the `SignalHandler` class.
 */

#include "Utilities/SignalHandler.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/Logger.hpp"
#include <csignal>  // signal

using namespace IPK25ChatClient::Exceptions;

namespace IPK25ChatClient::Utilities
{
    void SignalHandler::registerHandlers() {
        logger("Registering signal handlers");

        signal(SIGINT, handleSignal);
        signal(SIGSEGV, handleSignal);
    } // SignalHandler::registerHandlers()

    void SignalHandler::handleSignal(const int signal) {
        logger("Handling signal: %d", signal);

        if(signal == SIGINT) {
            throw UserInterruptionException("SIGINT: User interrupted the program.");
        }
        if(signal == SIGSEGV) {
            throw InternalErrorException("SIGSEGV: Segmentation fault occurred.");
        }
    } // SignalHandler::handleSignal()
} // IPK25ChatClient::Utilities

/*** end of file SignalHandler.cpp ***/
