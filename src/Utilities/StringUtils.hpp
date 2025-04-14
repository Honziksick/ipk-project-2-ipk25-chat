/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         StringUtils.hpp                                               *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      13.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the declaration of the `StringUtils`       *
 *               class, which provides utility functions for string            *
 *               operations (e.g., toLower, splitBySpaces, ...).               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file StringUtils.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `StringUtils` class for string operations.
 */

#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>  // std::string
#include <vector>  // std::vector

namespace IPK25ChatClient::Utilities
{
    /**
     * @class StringUtils
     * @brief Utility class for string operations.
     */
    class StringUtils {
    public:
        /**
         * @brief Converts a `std::string` to lowercase.
         *
         * @note With little modification taken from https://stackoverflow.com/a/313990.
         *
         * @param str The string to be converted.
         * @return std::string The lowercase version of the input `std::string`.
         */
        static std::string toLower(const std::string &str);

        /**
         * @brief Splits g a string into tokens based on a given delimiter.
         *
         * @param str The input string to be split.
         * @param delimiter The delimiter used to split the string (e.g., "\r\n").
         *
         * @return A vector of tokens extracted from the input string.
         */
        static std::vector<std::string> splitByDelimiter(const std::string &str, const std::string &delimiter);

        /**
         * @brief Splits a string into a vector of substrings based on spaces.
         *
         * @details This function takes a string as an input stream and splits
         *          it into individual substrings (tokens) separated by spaces.
         *          Consecutive spaces are ignored, and only non-empty tokens
         *          are included in the resulting vector.
         *
         * @note Implementation inspired by: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
         *
         * @param str The input string to be split.
         *
         * @return std::vector<std::string> A vector containing the substrings
         *         obtained by splitting the input string by spaces.
         */
        static std::vector<std::string> splitBySpaces(const std::string &str);

        /**
         * @brief Truncates a string to a specified maximum length.
         *
         * @details This function modifies the input string directly (over
         *          reference) by truncating it to the specified maximum
         *          length if it exceeds that length.
         *
         * @param str The string to be truncated passed by reference, so
         *            modifications will affect the original string.
         * @param maxLength The maximum allowed length for the string.
         *
         * @return `true` If the string was truncated, `false` otherwise.
         */
        static bool truncateOverReference(std::string &str, size_t maxLength);
    }; // StringUtils
} // IPK25ChatClient::Utilities

#endif // STRING_UTILS_HPP

/*** end of file StringUtils.hpp ***/
