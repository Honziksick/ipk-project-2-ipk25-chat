/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         MessageParserBase.hpp                                         *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      17.04.2025                                                    *
 * Last edit:    17.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration the `MessageParserBase` base class for message    *
 *               parsing in the IPK25 Chat Client. It provides common          *
 *               functionality and constants for derived message parser        *
 *               classes.                                                      *
 *                                                                             *
 ******************************************************************************/
/**
 * @file MessageParserBase.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief
 */

#ifndef MESSAGE_PARSER_BASE_HPP
#define MESSAGE_PARSER_BASE_HPP

#include "Messaging/Interfaces/IMessageParser.hpp"

namespace IPK25ChatClient::Messaging::Parser
{
    /**
     * @class MessageParserBase
     * @brief Base class for message parsers.
     *
     * @details This class provides a foundation for implementing message
     *          parsers in the IPK25 Chat Client. It includes shared constants
     *          and functionality that can be utilized by derived classes.
     */
    class MessageParserBase : public IMessageParser{
    protected:
        constexpr static auto END_OF_MESSAGE_DELIMITER = "\r\n";  /**< The delimiter used to identify the end of a message. */
    }; // MessageParserBase
} // IPK25ChatClient::Messaging::Parser

#endif // MESSAGE_PARSER_BASE_HPP

/*** end of file MessageParserBase.hpp ***/
