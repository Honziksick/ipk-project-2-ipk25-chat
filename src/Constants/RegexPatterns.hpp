/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         RegexPatterns.hpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    16.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains regular expression patterns as constants   *
 *               for validating various parameters in the IPK25 Chat Client.   *
 *                                                                             *
 ******************************************************************************/
/**
 * @file RegexPatterns.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file containing regular expression patterns as constants.
 */

#ifndef REGEX_PATTERNS_HPP
#define REGEX_PATTERNS_HPP

#define _GLIBCXX_REGEX_STATE_LIMIT 1000000
#include <regex>

namespace IPK25ChatClient::Constants
{
    /**
     * @class RegexPatterns
     * @brief Class containing regular expression patterns as constants for
     *        validating various parameters.
     *
     * @details These patterns including length restrictions are set according
     *          to the specification of the IPK25 Chat Client project
     *          ([source](https://git.fit.vutbr.cz/NESFIT/IPK-Projects/src/branch/master/Project_2#message-types)).
     */
    class RegexPatterns {
    public:
        // Regular expression patterns accrording to the specification
        static constexpr auto ALLOWED_SYMBOLS_REGEX_PATTERN = R"([a-zA-Z0-9_-]+)";                                  /**< Pattern for validating allowed symbols. */
        static constexpr auto ALLOWED_SYMBOLS_WITH_WHITES_REGEX_PATTERN = R"((?=.*[\x21-\x7E])[ \x0A\x21-\x7E]+)";  /**< Pattern for validating allowed symbols (co-created with GitHub Copilot). */
        static constexpr auto USERNAME_REGEX_PATTERN = R"([a-zA-Z0-9_-]{1,20})";                     /**< Pattern for validating usernames.       */
        static constexpr auto CHANNEL_REGEX_ID_PATTERN = R"([a-zA-Z0-9_-]{1,20})";                   /**< Pattern for validating channel IDs.     */
        static constexpr auto CHANNEL_REGEX_ID_PATTERN_WITH_DOT = R"([a-zA-Z0-9_\x2E-]{1,20})";      /**< Pattern for validating channel IDs.     */
        static constexpr auto SECRET_REGEX_PATTERN = R"([a-zA-Z0-9_-]{1,128})";                      /**< Pattern for validating secrets.         */
        static constexpr auto DISPLAYNAME_REGEX_PATTERN = R"([\x21-\x7E]{1,20})";                    /**< Pattern for validating display names.   */
        static constexpr auto MESSAGE_CONTENT_REGEX_PATTERN_WITHOUT_LENGTH = R"([\x0A\x20-\x7E]+)";  /**< Pattern for validating message content. */

        // Additional regular expression patterns
        /**
         * @brief Regular expression for validating hostnames.
         * @note This regex pattern was co-created with GitHub Copilot.
         */
        static constexpr auto HOSTNAME_REGEX_PATTERN = R"(^([A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?\.)+[A-Za-z]{2,63}\.?$)";

        /**
         * @brief Regular expression for validating IPv4 addresses.
         * @note Source: https://ihateregex.io/expr/ip/
         */
        static constexpr auto IPV4_REGEX_PATTERN =
                R"(^(?!0\.0\.0\.0$)(\b25[0-5]|\b2[0-4][0-9]|\b[01]?[0-9][0-9]?)(\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$)";
    }; // RegexPatterns
} // IPK25ChatClient::Constants

#endif // REGEX_PATTERNS_HPP

/*** end of file RegexPatterns.hpp ***/
