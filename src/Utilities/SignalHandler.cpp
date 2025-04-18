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
 * Last edit:    18.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `SignalHandler` class, which is         *
 *               responsible for handling system signals in a safe and         *
 *               controlled manner.                                            *
 *                                                                             *
 ******************************************************************************/
/**
 * @file SignalHandler.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `SignalHandler` class, which provides functionality
 *        for handling system signals (e.g., SIGINT, SIGSEGV) in a thread-safe way.
 */

#include "Utilities/SignalHandler.hpp"
#include "Utilities/Logger.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include <atomic>   // std::atomic
#include <csignal>  // signal

using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Exceptions;

namespace IPK25ChatClient::Utilities
{
    // Initialization of the static atomic flags
    std::atomic<bool> SignalHandler::mSigintReceived{false};
    std::atomic<bool> SignalHandler::mSigsegvReceived{false};

    void SignalHandler::registerHandlers() {
        logger("Registering signal handlers");

        signal(SIGINT, handleSignal);
        signal(SIGSEGV, handleSignal);
    } // SignalHandler::registerHandlers()

    void SignalHandler::handleSignal(const int signal) {
        logger("Handling signal: %d", signal);

        if(signal == SIGINT) {
            mSigintReceived = true;
        }
        if(signal == SIGSEGV) {
            mSigsegvReceived = true;
        }
    } // SignalHandler::handleSignal

    void SignalHandler::checkSignals() {
        if(mSigintReceived) {
            throw UserInterruptionException("Signal SIGINT received.");
        }
        if(mSigsegvReceived) {
            throw InternalErrorException(
                    "Signal SIGSEGV received.",
                    ClientInternalErrorMessage::CLIENT_INTERNAL_ERROR
                    );
        }
    } // SignalHandler::checkSignals
} // IPK25ChatClient::Utilities

/*** end of file SignalHandler.cpp ***/
