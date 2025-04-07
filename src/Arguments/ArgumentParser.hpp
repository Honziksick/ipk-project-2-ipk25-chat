/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ArgumentParser.hpp                                            *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the definition of the ArgumentParser       *
 *               class which is responsible for parsing command line           *
 *               arguments and options for the IPK25 Chat Client.              *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ArgumentParser.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for the ArgumentParser class for parsing command line arguments.
 */

#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include "Common/CommandLineOptions.hpp"
#include <string>     // std::string
#include "CLI11.hpp"  /* CLI11 je header-only library for command-line parsing
                         Source: https://github.com/CLIUtils/CLI11 */

namespace IPK25ChatClient::Arguments
{
    /**
     * @class ArgumentParser
     * @brief Class responsible for parsing command line arguments and options.
     */
    class ArgumentParser final {
    public:
        /**
         * @brief Parses command line arguments and returns a populated
         *        CommandLineOptions object.
         *
         * @param argc Number of arguments.
         * @param argv Array of argument strings.
         * @return CommandLineOptions instance initialized with parsed values.
         */
        static Common::CommandLineOptions parseArguments(int argc, char *argv[]);

    private:
        /**
         * @brief Sets up the CLI application with the necessary options and arguments.
         *
         * @param app Reference to the CLI application instance.
         * @param commandLineOptions Reference to the CommandLineOptions object to be populated.
         * @param transportProtocol The transport protocol to be used (TCP or UDP).
         * @param targetServer Reference to the target server string.
         */
        static void setupCliApp(CLI::App &app, Common::CommandLineOptions &commandLineOptions,
                                std::string &transportProtocol, std::string &targetServer);

        /**
         * @brief Validates the target server string.
         *
         * @param targetServer The target server string to be validated.
         */
        static void validateTargetServer(const std::string &targetServer);

        /**
         * @brief Populates the remaining options in the CommandLineOptions object.
         *
         * @param commandLineOptions Reference to the CommandLineOptions object to be populated.
         * @param transportProtocol The transport protocol to be used (TCP or UDP).
         * @param targetServer The target server string to be used.
         */
        static void populateRemainingOptions(Common::CommandLineOptions &commandLineOptions,
                                             const std::string &transportProtocol, const std::string &targetServer);
    }; // ArgumentParser
} // IPK25ChatClient::Arguments

#endif // COMMAND_LINE_PARSER_HPP

/*** end of file ArgumentParser.hpp ***/
