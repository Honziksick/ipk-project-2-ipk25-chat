/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MainClientFacade.cpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    16.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `MainClientFacade` class, which serves  *
 *               as the main entry point for running the IPK25 Chat Client.    *
 *               It handles initialization, signal registration, and           *
 *               configuration parsing.                                        *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MainClientFacade.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `MainClientFacade` class for managing the main
 *        client operations.
 */

#include "Facades/MainClientFacade.hpp"
#include "Arguments/ArgumentParser.hpp"
#include "Utilities/ExceptionHandler.hpp"
#include "Utilities/SignalHandler.hpp"
#include "Utilities/Logger.hpp"
#include <exception>  // std::exception
#include <memory>     // std::make_unique

using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Arguments;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Facades
{
    void MainClientFacade::runChatClient(const int argc, char *argv[]) {
        logger("Starting runChatClient with argc: %d", argc);

        try {
            // Register signal handlers (SIGIMT. SIGSEGV)
            logger("Registering signal handlers...");
            SignalHandler::registerHandlers();

            // Initialize the command line options
            logger("Initializing command line options...");
            getCommandLineOptions(argc, argv);

            // Initialize the client FSM facade
            logger("Initializing client FSM facade...");
            initializeClientFsmFacade();
        }
        catch(const exception &e) {
            ExceptionHandler::handleError(e, ExceptionHandler::TERMINATE);
        }

        logger("runChatClient completed successfully");
    } // MainClientFacade::runChatClient()

    void MainClientFacade::getCommandLineOptions(const int argc, char *argv[]) {
        logger("Parsing command line options...");
        mCommandLineOptions = ArgumentParser::parseArguments(argc, argv);
        logger("Command line options parsed successfully");
    } // MainClientFacade::getCommandLineOptions()

    void MainClientFacade::initializeClientFsmFacade() {
        logger("Creating ClientFsmFacade...");
        mClientFsmFacade = make_unique<ClientFsmFacade>(mCommandLineOptions);
        logger("ClientFsmFacade initialized successfully");
    }
} // IPK25ChatClient::Facades

/*** end of file MainClientFacade.cpp ***/
