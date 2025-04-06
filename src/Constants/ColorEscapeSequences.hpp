/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ColorEscapeSequences.hpp                                      *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      03.04.2025                                                    *
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description: This file contains the definition of color escape sequences    *
 *              used for formatting text output in the IPK25 Chat Client       *
 *              project.                                                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ColorEscapeSequences.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief This file defines constants for color escape sequences used in
 *        text formatting.
 */

#ifndef COLOR_ESCAPE_SEQUENCES_HPP
#define COLOR_ESCAPE_SEQUENCES_HPP

namespace IPK25ChatClient::Constants
{
    // General formatting escape sequences
    inline constexpr auto RESET = "\033[0m";           /**< Reset all attributes. */
    inline constexpr auto FORMAT_BOLD = "\033[1m";     /**< Bold text format.     */

    // Foreground colors
    inline constexpr auto COLOR_RED = "\033[31m";      /**< Red text color.       */
    inline constexpr auto COLOR_GREEN = "\033[32m";    /**< Green text color.     */
    inline constexpr auto COLOR_YELLOW = "\033[33m";   /**< Yellow text color.    */
    inline constexpr auto COLOR_MAGENTA = "\033[35m";  /**< Magenta text color.   */
    inline constexpr auto COLOR_CYAN = "\033[36m";     /**< Cyan text color.      */
} // IPK25ChatClient::Constants

#endif // COLOR_ESCAPE_SEQUENCES_HPP

/*** end of file ColorEscapeSequences.hpp ***/
