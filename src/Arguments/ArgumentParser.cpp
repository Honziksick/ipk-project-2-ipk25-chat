/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ArgumentParser.cpp                                            *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    20.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `ArgumentParser` class, which is        *
 *               responsible for parsing command line arguments and options.   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ArgumentParser.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `ArgumentParser` class for parsing command line
 *        arguments and options.
 */

#include "CLI11.hpp"  /* CLI11 je header-only library for command-line parsing
                         Source: https://github.com/CLIUtils/CLI11 */
#include "Arguments/ArgumentParser.hpp"
#include "Common/CommandLineOptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Constants/ClientLimits.hpp"
#include "Constants/RegexPatterns.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include "Utilities/Logger.hpp"
#include <string>  // std::string
#include <regex>   // std::regex

using namespace IPK25ChatClient::Common;
using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;
using namespace IPK25ChatClient::Exceptions;
using namespace std;

namespace IPK25ChatClient::Arguments
{
    CommandLineOptions ArgumentParser::parseArguments(const int argc, char *argv[]) {
        logger("Starting to parse arguments, argc: %d", argc);

        // Create an instance of CommandLineOptions to hold the parsed options
        CommandLineOptions commandLineOptions;

        // Create an instance of the CLI11 application
        CLI::App app;

        // Local variables to store unprocessed inputs
        string transportProtocol;
        string targetServer;

        // Set up the CLI11 application
        setupCliApp(app, commandLineOptions, transportProtocol, targetServer);

        // Attempt to parse and validate the arguments
        try {
            app.parse(argc, argv);
        }
        catch(const CLI::CallForHelp &e) {
            if(const auto exitCode{app.exit(e)}; exitCode == EXIT_SUCCESS) {
                throw HelpRequestedException();
            }
            else {
                throw InternalErrorException(
                        "CLI11 library returned error while parsing "
                        "command line arguments: " + string(e.what())
                        );
            }
        }
        catch(const CLI::Error &e) {
            throw InvalidArgumentException(string(e.what()));
        }

        // Validate the target server hostname or IP address format
        validateTargetServer(targetServer);

        populateRemainingOptions(commandLineOptions, transportProtocol, targetServer);

        logger(
                "Arguments parsed successfully: mTargetServer: %s, mTransportProtocol: %s, mServerPort: %u, mUdpMaxRetransmit: %u, mUdpTimeoutMs: %u",
                targetServer.c_str(),
                commandLineOptions.mTransportProtocol == Enums::TransportProtocolType::TCP ? "TCP" : "UDP",
                commandLineOptions.mServerPort,
                commandLineOptions.mUdpMaxRetransmit,
                commandLineOptions.mUdpTimeoutMs);
        logger("Finished parsing arguments");

        return commandLineOptions;
    } // ArgumentParser::parseArguments

    void ArgumentParser::setupCliApp(CLI::App &app, CommandLineOptions &commandLineOptions, string &transportProtocol,
                                     string &targetServer) {
        // General description of the application
        app.name("IPK25 Chat Client v1.0");
        app.description(
            "IPK25 Chat Client implements the IPK25-CHAT protocol over TCP or UDP (IPv4 only). "
            "Supports user authentication, channel management, message exchange and graceful "
            "termination. UDP variant includes application‑level CONFIRM and retransmission logic; "
            "TCP variant uses a simple text grammar over a reliable stream."
        );

        // Customize usage message
        app.usage("   ./ipk25chat-client [-t udpOrTcp | --transport-protocol udpOrTcp] [-s ipOrHostname | --server ipOrHostname]\n"
                "                      <-p port | --port port> <-d timeout | --wait timeout> <-r max | --max-retransmissions max>"
                );

        // Add options
        app.set_help_flag("-h,--help", "Display this help message and terminate the program with exit code 0");

        app.add_option("-t,--transport-protocol", transportProtocol,
                       "Transport protocol to use: \"tcp\" or \"udp\"")
           ->required(true)
           ->expected(1)
           ->check(CLI::IsMember({"tcp", "udp"}));

        app.add_option("-s,--server", targetServer,
                       "Hostname or IPv4 address of the chat server")
           ->required(true)
           ->expected(1);

        app.add_option("-p,--port", commandLineOptions.mServerPort,
                       "Server port (default: 4567)")
           ->required(false)
           ->expected(0, 1)
           ->check(CLI::Range(ClientLimits::MIN_SERVER_PORT, ClientLimits::MAX_SERVER_PORT));

        app.add_option("-r,--max-retransmissions", commandLineOptions.mUdpMaxRetransmit,
                       "UDP confirmation timeout in milliseconds (default: 250)")
           ->required(false)
           ->expected(0, 1)
           ->check(CLI::Range(ClientLimits::MIN_UDP_RETRANSMIT, ClientLimits::MAX_UDP_RETRANSMIT));

        app.add_option("-d,--wait", commandLineOptions.mUdpTimeoutMs,
                       "Maximum number of UDP retransmissions (default: 3)")
           ->required(false)
           ->expected(0, 1)
           ->check(CLI::Range(ClientLimits::MIN_UDP_TIMEOUT_MS, ClientLimits::MAX_UDP_TIMEOUT_MS));

        // Footer with example usage and error codes
        app.footer(
            "\nEXAMPLE USAGE:\n"
            "   ./ipk25chat-client -t tcp -s 127.0.0.1\n"
            "   ./ipk25chat-client -t tcp -s localhost\n"
            "   ./ipk25chat-client -t udp -s chat.example.com -p 10000\n"
            "   ./ipk25chat-client -t udp -s 192.168.1.5 -p 3000 -d 100 -r 1\n"
            "\n\n"
            "EXIT CODES:\n"
            "    0   – Success\n"
            "   64   – Invalid argument (usage error)\n"
            "   68   – Hostname resolution error\n"
            "   70   – Internal error\n"
            "   71   – Connection (socket) error\n"
            "   76   – Protocol error\n"
            "   78   – Unknown error\n"
            "  107   – Connection unexpectedly not established\n"
            "  110   – Message lost (retransmission limit exceeded)\n"
            "  116   – Connection timed out\n"
        );
    } // ArgumentParser::setupCliApp

    void ArgumentParser::validateTargetServer(const string &targetServer) {
        if(!(regex_match(targetServer, regex(RegexPatterns::HOSTNAME_REGEX_PATTERN)) ||
            regex_match(targetServer, regex(RegexPatterns::IPV4_REGEX_PATTERN)) ||
            targetServer == "localhost")) {
            throw InvalidArgumentException(
                    "Invalid server hostname or IP address: " + targetServer
                    );
        }

        logger("Target server validated successfully: %s", targetServer.c_str());
    } // ArgumentParser::validateTargetServer

    void ArgumentParser::populateRemainingOptions(CommandLineOptions &commandLineOptions,
                                                  const string &transportProtocol, const string &targetServer) {
        commandLineOptions.mTransportProtocol =
                (transportProtocol == "tcp") ? TransportProtocolType::TCP : TransportProtocolType::UDP;

        commandLineOptions.mTargetServer = targetServer;
    } // ArgumentParser::populateRemainingOptions
} // IPK25ChatClient::Arguments

/*** end of file ArgumentParser.cpp ***/
