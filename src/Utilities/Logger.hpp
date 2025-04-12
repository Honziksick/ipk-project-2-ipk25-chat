/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         Logger.hpp                                                    *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the Logger utility.                           *
 *               Provides macros for conditional debug printing.               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file Logger.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for the Logger utility.
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Constants/ColorEscapeSequences.hpp"
#include <cstdio>  // fprintf()

using namespace IPK25ChatClient::Constants;

// Define DEBUG_PRINT to enable debug printing
#define DEBUG_PRINT

// Source: https://git.fit.vutbr.cz/NESFIT/IPK-Projects/src/branch/master/Project_2#client-logging
#ifdef DEBUG_PRINT
#define logger(format, ...) \
    do { \
        if (*#format) { \
            fprintf(stderr, "%-40s:%-4d | %30s | " format "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        } \
        else { \
            fprintf(stderr, "%-40s:%-4d | %30s | \n", __FILE__, __LINE__, __func__); \
        } \
    } while (0)
#else
#define logger(format, ...) (0)
#endif // DEBUG_PRINT

#endif // LOGGER_HPP

/*** end of file Logger.hpp ***/
