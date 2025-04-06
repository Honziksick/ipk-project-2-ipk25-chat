/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CommandLineOptions.cpp                                        *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the CommandLineOptions class, which         *
 *               handles the storage of command line options for the IPK25     *
 *               Chat Client application.                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CommandLineOptions.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation file for the CommandLineOptions class.
 */

#include "Common/CommandLineOptions.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Constants/DefaultCommandLineOptions.hpp"

using namespace IPK25ChatClient::Enums;
using namespace IPK25ChatClient::Constants;

namespace IPK25ChatClient::Common
{
    CommandLineOptions::CommandLineOptions()
        : mTransportProtocol{TransportProtocol::None}, mServerPort{DefaultCliOptions::cServerPort},
          mUdpMaxRetransmit{DefaultCliOptions::cUdpMaxRetransmit}, mUdpTimeoutMs{DefaultCliOptions::cUdpTimeoutMs} {}
} // IPK25ChatClient::Common

/*** end of file CommandLineOptions.cpp ***/
