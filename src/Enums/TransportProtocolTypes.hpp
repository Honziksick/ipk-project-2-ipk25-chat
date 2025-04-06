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
 * Last edit:    06.04.2025                                                    *
 *                                                                             *
 * Description:  Header file defining protocol types enumeration for the       *
 *               IPK25 Chat Client project.                                    *
 *                                                                             *
 ******************************************************************************/
/**
 * @file TransportProtocolTypes.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file for protocol types enumeration.
 */

#ifndef TRANSPORT_PROTOCOL_TYPES_HPP
#define TRANSPORT_PROTOCOL_TYPES_HPP

namespace IPK25ChatClient::Enums
{
    /**
     * @enum TransportProtocol
     * @brief Enumeration for transport protocol types.
     */
    enum class TransportProtocol {
        None = 0,    /**< No protocol type specified. */
        UDP  = 1,    /**< UDP protocol.               */
        TCP  = 2,    /**< TCP protocol.               */
        IPv4 = 3,    /**< IPv4 protocol.              */
        IPv6 = 4,    /**< IPv6 protocol.              */
    }; // TransportProtocol
} // IPK25ChatClient::Enums

#endif // TRANSPORT_PROTOCOL_TYPES_HPP

/*** end of file TransportProtocolTypes.hpp ***/
