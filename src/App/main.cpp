/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         main.cpp                                                      *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the main function that serves as the entry *
 *               point for the IPK25 Chat Client application. It initializes   *
 *               the application and chatting.                                 *
 *                                                                             *
 ******************************************************************************/
/**
 * @file main.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Main entry point for the IPK25 Chat Client application.
 */

#include "Facades/MainClientFacade.hpp"
#include "Utilities/ExceptionHandler.hpp"
#include "Utilities/Logger.hpp"
#include <exception>  // std::exception

using namespace IPK25ChatClient;
using namespace std;

int main(const int argc, char *argv[]) {
    logger("Starting IPK25 Chat Client application");
    try {
        Facades::MainClientFacade appFacade;
        appFacade.runChatClient(argc, argv);
    }
    catch(const exception &e) {
        logger("Exception caught in main(): %s", e.what());
        Utilities::ExceptionHandler::handleError(e, Utilities::ExceptionHandler::TERMINATE);
    }

    logger("Successfully exiting IPK25 Chat Client application");
    return EXIT_SUCCESS;
} // main()

/*** end of file main.cpp ***/
