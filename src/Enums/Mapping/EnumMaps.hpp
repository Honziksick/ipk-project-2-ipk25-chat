/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         EnumMaps.hpp                                                  *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `EnumMaps` class, which provides static    *
 *               mapping utilities for converting enum values to their         *
 *               corresponding string representations.                         *
 *                                                                             *
 ******************************************************************************/
/**
 * @file EnumMaps.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining static methods to retrieve enum-to-string maps.
 */

#ifndef ENUM_MAPS_HPP
#define ENUM_MAPS_HPP

#include "Enums/UserCommandTypes.hpp"
#include "Enums/ClientFsmStates.hpp"
#include "Enums/ExitCodes.hpp"
#include "Enums/TransportProtocolTypes.hpp"
#include "Enums/MessageParameters.hpp"
#include "Enums/MessageTypes.hpp"
#include "Enums/MessageValidatorResults.hpp"
#include <unordered_map>  // std::unordered_map
#include <string>         // std::string

namespace IPK25ChatClient::Enums::Mapping
{
    /**
     * @class EnumMaps
     * @brief Provides static methods to retrieve enum-to-string mappings.
     *
     * @details The `EnumMaps` class contains static methods that return constant
     *          references to `std::unordered_map` objects. These maps define the
     *          relationships between enum values and their corresponding string
     *          representations. The class is designed to be used as a utility
     *          without requiring instantiation.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf (p. 160)
     */
    class EnumMaps {
    protected:
        /**
         * @brief Retrieves the mapping for `UserCommandType` to strings.
         * @return A constant reference to the map of `UserCommandType` to strings.
         */
        static const std::unordered_map<UserCommandType, std::string> &getUserCommandTypeMap();

        /**
         * @brief Retrieves the mapping for `ClientFsmState` to strings.
         * @return A constant reference to the map of `ClientFsmState` to strings.
         */
        static const std::unordered_map<ClientFsmState, std::string> &getClientFsmStateMap();

        /**
         * @brief Retrieves the mapping for `ExitCode` to strings.
         * @return A constant reference to the map of `ExitCode` to strings.
         */
        static const std::unordered_map<ExitCode, std::string> &getExitCodeMap();

        /**
         * @brief Retrieves the mapping for `TransportProtocolType` to strings.
         * @return A constant reference to the map of `TransportProtocolType` to strings.
         */
        static const std::unordered_map<TransportProtocolType, std::string> &getTransportProtocolTypeMap();

        /**
         * @brief Retrieves the mapping for `MessageParameter` to strings.
         * @return A constant reference to the map of `MessageParameter` to strings.
         */
        static const std::unordered_map<MessageParameter, std::string> &getMessageParameterMap();

        /**
         * @brief Retrieves the mapping for `MessageValidatorResult` to strings.
         * @return A constant reference to the map of `MessageValidatorResult` to strings.
         */
        static const std::unordered_map<MessageValidatorResult, std::string> &getMessageValidatorResultMap();

        /**
         * @brief Retrieves the mapping for `MessageType` to strings.
         * @return A constant reference to the map of `MessageType` to strings.
         */
        static const std::unordered_map<MessageType, std::string> &getMessageTypeMap();
    }; // EnumMaps
} // namespace IPK25ChatClient::Enums

#endif // ENUM_MAPS_HPP

/*** end of file EnumMaps.hpp ***/
