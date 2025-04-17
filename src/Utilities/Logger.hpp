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
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for the Logger utility, which provides a flexible *
 *               mechanism for logging debug messages with contextual          *
 *               information such as file name line number, and function name. *
 *                                                                             *
 ******************************************************************************/
/**
 * @file Logger.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief  Header file for the Logger utility, which provides a flexible
 *         mechanism for logging debug messages
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Constants/ColorEscapeSequences.hpp"
#include <cstdio>  // fprintf()

using namespace IPK25ChatClient::Constants;

// Define DEBUG_PRINT to enable debug printing
#define DEBUG_PRINT

/**
 * @def logger(format, ...)
 * @brief Macro for conditional debug logging.
 *
 * @details This macro logs messages to the standard error stream (`stderr`)
 *          with contextual information such as the file name, line number,
 *          and function name. The output is color-coded using escape sequences
 *          defined in `ColorEscapeSequences.hpp`.
 *
 * @note If `DEBUG_PRINT` is not defined, the macro does nothing.
 * @note Upgraded by me and pushed to:
 *       https://git.fit.vutbr.cz/NESFIT/IPK-Projects/src/branch/master/Project_2#client-logging
 *
 * @param format A printf-style format string for the log message.
 * @param ... Additional arguments for the format string.
 *
 */
#ifdef DEBUG_PRINT
#define logger(format, ...) \
    do { \
        if (*#format) { \
            fprintf(stderr, "%s%-60s:%-4d | %30s | " format "%s\n", \
                    Color::MAGENTA, __FILE__, __LINE__, __func__, ##__VA_ARGS__, Color::RESET); \
        } \
        else { \
            fprintf(stderr, "%s%-60s:%-4d | %30s | %s\n", \
                    Color::MAGENTA, __FILE__, __LINE__, __func__, Color::RESET); \
        } \
    } while (0)
#else
#define logger(format, ...) (0)
#endif // DEBUG_PRINT

#endif // LOGGER_HPP

/*** end of file Logger.hpp ***/
