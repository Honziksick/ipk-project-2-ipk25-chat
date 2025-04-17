/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MainClientFacade.hpp                                          *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    16.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `MainClientFacade` class, which serves as  *
 *               the main entry point for the IPK25 Chat Client application.   *
 *               It handles initialization, configuration parsing, and         *
 *               managing the client FSM.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MainClientFacade.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `MainClientFacade` class for managing the
 *        main client operations.
 */

#ifndef MAIN_CLIENT_FACADE_HPP
#define MAIN_CLIENT_FACADE_HPP

#include "Common/CommandLineOptions.hpp"
#include "Client/Interfaces/IClientFSM.hpp"
#include <memory>  // std::unique_ptr

namespace IPK25ChatClient::Facades
{
    /**
     * @class MainClientFacade
     * @brief Main entry point for the IPK25 Chat Client application.
     *
     * @details This class is responsible for initializing the application,
     *          parsing command line options, and managing the client FSM.
     */
    class MainClientFacade final {
    public:
        /**
         * @brief Default constructor for `MainClientFacade`.
         */
        MainClientFacade() = default;

        /**
         * @brief Runs the chat client application.
         * @details This method initializes the application by registering
         *          signal handlers, parsing command line options, and setting
         *          up the client FSM facade.
         *
         * @param argc The number of command line arguments.
         * @param argv The array of command line arguments.
         */
        void runChatClient(int argc, char *argv[]);

    private:
        Common::CommandLineOptions mCommandLineOptions;  /**< Stores the parsed command line options.     */
        std::unique_ptr<Client::FSM::IClientFsm> mFsm;   /**< Pointer to the client's FSM implementation. */

        /**
         * @brief Parses the command line options.
         * @details This method uses the `ArgumentParser` to parse the provided
         *          command line arguments and stores the result in the member
         *          variable `mCommandLineOptions`.
         *
         * @param argc The number of command line arguments.
         * @param argv The array of command line arguments.
         */
        void getCommandLineOptions(int argc, char *argv[]);

        /**
         * @brief Initializes the client FSM (Finite State Machine).
         * @details This method creates an instance of the appropriate FSM
         *          implementation (TCP or UDP) based on the transport protocol
         *          specified in the command line options. If an invalid protocol
         *          type is provided, an exception is thrown.
         */
        void initializeClientFsm();

        /**
         * @brief Runs the client FSM (Finite State Machine).
         * @details This method executes the finite state machine (FSM) logic
         *          for the chat client. It ensures the proper functioning
         *          of the client by managing its states and transitions.
         */
        void runClientFsm() const;
    }; // MainClientFacade
} // IPK25ChatClient::Facades

#endif // MAIN_CLIENT_FACADE_HPP

/*** end of file MainClientFacade.hpp ***/
