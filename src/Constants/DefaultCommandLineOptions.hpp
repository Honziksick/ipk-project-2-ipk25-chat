/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         DefaultCommandLineOptions.hpp                                 *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains default values for command line options    *
 *               used in the IPK25 Chat Client application.                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file DefaultCommandLineOptions.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file containing default values for command line options.
 */

#ifndef DEFAULT_COMMAND_LINE_OPTIONS_HPP
#define DEFAULT_COMMAND_LINE_OPTIONS_HPP

#include <cstdint> // uint8_t, uint16_t

namespace IPK25ChatClient::Constants
{
    inline constexpr uint16_t cServerPort = 4567;    /**< Default server port number. */
    inline constexpr uint8_t cUdpMaxRetransmit = 3;  /**< Default maximum number of UDP retransmissions. */
    inline constexpr uint16_t cUdpTimeoutMs = 250;   /**< Default UDP timeout duration in milliseconds. */
} // IPK25ChatClient::Constants

#endif // DEFAULT_COMMAND_LINE_OPTIONS_HPP

/*** end of file DefaultCommandLineOptions.hpp ***/
