/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         TransportProtocolTypes.hpp                                    *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      06.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining the protocol types enumeration for the   *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TransportProtocolTypes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining the protocol types enumeration.
 */

#ifndef TRANSPORT_PROTOCOL_TYPES_HPP
#define TRANSPORT_PROTOCOL_TYPES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum TransportProtocolType
     * @brief Enumeration for transport protocol types.
     */
    enum class TransportProtocolType {
        None = 0,    /**< No protocol type specified. */
        UDP,         /**< UDP protocol.               */
        TCP,         /**< TCP protocol.               */
        IPv4,        /**< IPv4 protocol.              */
        IPv6,        /**< IPv6 protocol.              */
    }; // TransportProtocolType
} // IPK25ChatClient::Enums

#endif // TRANSPORT_PROTOCOL_TYPES_HPP

/*** end of file TransportProtocolTypes.hpp ***/
