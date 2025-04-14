/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ParsedMessage.hpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      13.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `ParsedMessage` class, which represents    *
 *               a parsed message structure used in the chat clinet during     *
 *               both TCP and UDP communication.                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ParsedMessage.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the `ParsedMessage` class, which represents
 *        a parsed message structure containing message type and fields.
 */

#ifndef PARSED_MESSAGE_HPP
#define PARSED_MESSAGE_HPP

#include "Enums/MessageTypes.hpp"
#include <string>   // std::string
#include <vector>   // std::vector
#include <cstdint>  // uint16_t

namespace IPK25ChatClient::Common
{
    /**
     * @class ParsedMessage
     * @brief Represents a parsed message structure.
     *
     * @details This class is used to store the parsed content of a message,
     *          including its type and associated fields. This data class can
     *          be used to represent both TCP and UDP messages.
     */
    class ParsedMessage final {
    public:
        explicit ParsedMessage();

        Enums::MessageType mType;          /**< The type of the message (e.g., AUTH, MSG, BYE).                      */
        uint16_t mRefMessageId;            /**< The MessageID value of the message being confirmed (unused for TCP). */
        std::vector<std::string> mFields;  /**< The fields of the message (e.g., displayName, message content).      */
    }; // ParsedMessage
} // IPK25ChatClient::Common

#endif // PARSED_MESSAGE_HPP

/*** end of file ParsedMessage.hpp ***/
