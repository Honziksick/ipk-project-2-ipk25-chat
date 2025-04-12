/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ChatDataTypes.hpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      10.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Header file for custom data types used in the IPK25 Chat      *
 *               Client project.                                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ChatDataTypes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for custom data types used in the IPK25 Chat Client project.
 */

#ifndef CHAT_DATA_TYPES_HPP
#define CHAT_DATA_TYPES_HPP

#include <string>   // std::string
#include <vector>   // std::vector
#include <variant>  // std::variant
#include <cstdint>  // std::uint8_t

namespace IPK25ChatClient::Common
{
    /**
     * @typedef MessageContent
     * @brief Alias for the content of a message in the IPK25 Chat Client.
     *
     * @details `MessageContent` is defined as a variant that can hold either
     *          a text message (`std::string`) for TCP or binary data
     *          (`std::vector<uint8_t>`) for UDP.
     */
    using MessageContent = std::variant<std::string, std::vector<uint8_t>>;
} // IPK25ChatClient::Common

#endif // CHAT_DATA_TYPES_HPP

/*** end of file ChatDataTypes.hpp ***/
