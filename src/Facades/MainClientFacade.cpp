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
#include "Client/ClientFSM/TCPClientFSM.hpp"
#include "Client/ClientFSM/UDPClientFSM.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Utilities/ExceptionHandler.hpp"
#include "Utilities/CastUtils.hpp"
#include "Utilities/Logger.hpp"
#include <exception>  // std::exception
#include <memory>     // std::make_unique

using namespace IPK25ChatClient::Arguments;
using namespace IPK25ChatClient::Client::FSM;
using namespace IPK25ChatClient::Exceptions;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Utilities;
using namespace std;

namespace IPK25ChatClient::Facades
{
    void MainClientFacade::runChatClient(const int argc, char *argv[]) {
        logger("Starting runChatClient with argc: %d", argc);

        try {
            // Initialize the command line options
            getCommandLineOptions(argc, argv);

            // Initialize the client FSM facade
            initializeClientFsm();

            // Executes the client FSM
            runClientFsm();
        }
        catch(const exception &e) {
            ExceptionHandler::handleError(e, ExceptionHandler::TERMINATE);
        }

        logger("runChatClient completed successfully");
    } // MainClientFacade::runChatClient

    void MainClientFacade::getCommandLineOptions(const int argc, char *argv[]) {
        logger("Parsing command line options...");
        mCommandLineOptions = ArgumentParser::parseArguments(argc, argv);
        logger("Command line options parsed successfully");
    } // MainClientFacade::getCommandLineOptions

    void MainClientFacade::initializeClientFsm() {
        logger("Creating ClientFsm...");

        // Initialize the FSM based on the protocol type
        if(mCommandLineOptions.mTransportProtocol == TransportProtocolType::TCP) {
            mFsm = make_unique<TcpClientFsm>(mCommandLineOptions);
            logger("Initialized FSM: TCP");
        }
        else if(mCommandLineOptions.mTransportProtocol == TransportProtocolType::UDP) {
            mFsm = make_unique<UdpClientFsm>(mCommandLineOptions);
            logger("Initialized FSM: UDP");
        }
        else {
            throw InternalErrorException(
                    "Invalid protocol type was given to when initializing FSM: " +
                    CastUtils::castEnumToString(mCommandLineOptions.mTransportProtocol)
                    );
        }
    } // MainClientFacade::initializeClientFsm

    void MainClientFacade::runClientFsm() const {
        logger("Executing the client FSM...");
        mFsm->run();
        logger("FSM terminated successfully");
    } // MainClientFacade::runClientFsm
} // IPK25ChatClient::Facades

/*** end of file MainClientFacade.cpp ***/
