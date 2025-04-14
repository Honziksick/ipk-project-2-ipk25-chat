/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         ParsedMessage.cpp                                             *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      13.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  Implementation of the `ParsedMessage` class, which represents *
 *               a parsed message structure used in the chat clinet during     *
 *               both TCP and UDP communication.                               *
 *                                                                             *
 ******************************************************************************/
/**
 * @file ParsedMessage.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the `ParsedMessage` class, which represents
 *        a parsed message structure containing message type and fields.
 */

#include "Common/ParsedMessage.hpp"
#include "Enums/MessageTypes.hpp"

using namespace IPK25ChatClient::Enums;

namespace IPK25ChatClient::Common
{
    ParsedMessage::ParsedMessage() : mType{MessageType::UNKNOWN}, mRefMessageId{0} {}
} // IPK25ChatClient::Common

/*** end of file ParsedMessage.cpp ***/
