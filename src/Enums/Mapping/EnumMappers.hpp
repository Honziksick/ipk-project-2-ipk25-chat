/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         EnumMappers.hpp                                               *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    12.04.2025                                                    *
 *                                                                             *
 * Description:  Declaration of the `EnumMappers` class, which provides        *
 *               static template mapping methods for converting enum values    *
 *               to their corresponding string representations.                *
 *                                                                             *
 ******************************************************************************/
/**
 * @file EnumMappers.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining static template methods for converting enum
 *        values to their string representations.
 */

#ifndef ENUM_MAPPERS_HPP
#define ENUM_MAPPERS_HPP

#include "Enums/Mapping/EnumMaps.hpp"
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
     * @class EnumMappers
     * @brief Provides static template methods for mapping enum values to their
     *        string representations.
     *
     * @details The `EnumMappers` class extends the `EnumMaps` class and offers
     *          a template method to retrieve mappings of enum values to their
     *          corresponding string representations. Each enum type must have
     *          a specialized implementation of the template method.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf (p. 160)
     */
    class EnumMappers : public EnumMaps {
    public:
        /**
         * @brief Template function to retrieve the mapping for a given enum
         *        type to strings.
         *
         * @tparam EnumType The enum type for which the mapping is requested.
         * @return A constant reference to the map of the specified `EnumType`
         *         to strings.
         *
         * @note This method must be specialized for each supported enum type.
         */
        template <typename EnumType>
        static const std::unordered_map<EnumType, std::string> &getEnumToStringMap();
    }; // EnumMappers

    /**
     * @brief Specialization of the template method to retrieve the mapping for `UserCommandType`.
     * @return A constant reference to the map of `UserCommandType` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<UserCommandType, std::string> &EnumMappers::getEnumToStringMap<UserCommandType>() {
        return getUserCommandTypeMap();
    }

    /**
     * @brief Specialization of the template method to retrieve the mapping for `ClientFsmState`.
     * @return A constant reference to the map of `ClientFsmState` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<ClientFsmState, std::string> &EnumMappers::getEnumToStringMap<ClientFsmState>() {
        return getClientFsmStateMap();
    }

    /**
     * @brief Specialization of the template method to retrieve the mapping for `ExitCode`.
     * @return A constant reference to the map of `ExitCode` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<ExitCode, std::string> &EnumMappers::getEnumToStringMap<ExitCode>() {
        return getExitCodeMap();
    }

    /**
     * @brief Specialization of the template method to retrieve the mapping for `TransportProtocolType`.
     * @return A constant reference to the map of `TransportProtocolType` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<TransportProtocolType, std::string> &EnumMappers::getEnumToStringMap<TransportProtocolType>() {
        return getTransportProtocolTypeMap();
    }

    /**
     * @brief Specialization of the template method to retrieve the mapping for `MessageParameter`.
     * @return A constant reference to the map of `MessageParameter` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<MessageParameter, std::string> &EnumMappers::getEnumToStringMap<MessageParameter>() {
        return getMessageParameterMap();
    }

    /**
     * @brief Specialization of the template method to retrieve the mapping for `MessageValidatorResult`.
     * @return A constant reference to the map of `MessageValidatorResult` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<MessageValidatorResult, std::string> &EnumMappers::getEnumToStringMap<MessageValidatorResult>() {
        return getMessageValidatorResultMap();
    }

    /**
     * @brief Specialization of the template method to retrieve the mapping for `MessageType`.
     * @return A constant reference to the map of `MessageType` to strings.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf
     */
    template <>
    inline const std::unordered_map<MessageType, std::string> &EnumMappers::getEnumToStringMap<MessageType>() {
        return getMessageTypeMap();
    }
} // namespace IPK25ChatClient::Enums

#endif // ENUM_MAPPERS_HPP

/*** end of file EnumMappers.hpp ***/
