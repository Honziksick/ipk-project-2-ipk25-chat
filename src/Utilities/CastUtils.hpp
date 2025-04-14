/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         CastUtils.hpp                                                 *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      09.04.2025                                                    *
 * Last edit:    14.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the declaration of the `CastUtils`         *
 *               class, which provides utility methodss for type casting,      *
 *               specifically for enums. It includes methods to convert        *
 *               enums to their integer or string representations.             *
 *                                                                             *
 ******************************************************************************/
/**
 * @file CastUtils.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Declarations of the `CastUtils` class for type casting utilities.
 */

#ifndef CAST_UTILS_HPP
#define CAST_UTILS_HPP

#include "Enums/Mapping/EnumMappers.hpp"
#include "Exceptions/ChatExceptions.hpp"
#include <string>       // std::string
#include <type_traits>  // std::is_enum_v

namespace IPK25ChatClient::Utilities
{
    /**
     * @class CastUtils
     * @brief A utility class providing template helper methods for type casting.
     *
     * @note Inspired by: https://www.fit.vut.cz/person/peringer/public/ICP/Prednasky/ICP.pdf (p. 160)
     */
    class CastUtils {
    public:
        /**
         * @brief Converts an enum value to its underlying integer representation.
         * @details This function uses a static assertion to ensure that the
         *          template parameter is an enum type. If a non-enum type is
         *          used, a compile-time error will occur.
         *
         * @tparam EnumType The type of the enum to be converted. Must be an enum type.
         * @param enumValue The enum value to convert.
         *
         * @return int The integer representation of the enum value.
         */
        template <typename EnumType>
        static constexpr int castEnumToInt(EnumType enumValue) {
            static_assert(std::is_enum_v<EnumType>, "Template parameter must be an enum type");
            return static_cast<int>(enumValue);
        } // CastUtils::castEnumToInt

        /**
         * @brief Converts an enum value to its `uint8_t` representation.
         * @details This function uses a static assertion to ensure that the
         *          template parameter is an enum type. If a non-enum type is
         *          used, a compile-time error will occur.
         *
         * @tparam EnumType The type of the enum to be converted. Must be an enum type.
         * @param enumValue The enum value to convert.
         *
         * @return uint8_t The unsigned short representation of the enum value.
         */
        template <typename EnumType>
        static constexpr int castEnumToByte(EnumType enumValue) {
            static_assert(std::is_enum_v<EnumType>, "Template parameter must be an enum type");
            return static_cast<uint8_t>(enumValue);
        } // CastUtils::castEnumToInt

        /**
         * @brief Converts an enum value to its string representation.
         * @details This method uses a static assertion to ensure that the
         *          template parameter is an enum type. It retrieves the
         *          corresponding map for the enum type using `EnumMaps::getEnumToStringMap`.
         *          If the value is found in the map, it returns the corresponding
         *          string. Otherwise, it throws an exception indicating that
         *          the value is not present in the map.
         *
         * @tparam EnumType The type of the enum to be converted. Must be an enum type.
         * @param enumValue The enum value to convert.
         *
         * @return std::string The string representation of the enum value.
         *
         * @note This function was co-created with the help of GitHub Copilot.
         */
        template <typename EnumType>
        static std::string castEnumToString(EnumType enumValue) {
            static_assert(std::is_enum_v<EnumType>, "Template parameter must be an enum type");

            // Retrieve the map for the given enum type
            const auto &enumToStringMap = Enums::Mapping::EnumMappers::getEnumToStringMap<EnumType>();

            // Find the string value in the map
            for(const auto &pair : enumToStringMap) {
                if(pair.first == enumValue) {
                    return pair.second;
                }
            }

            // Throw an exception if the value is not found
            throw Exceptions::InternalErrorException(
                    "Enum value not found in the map. Enum type: " + std::string(typeid(EnumType).name()) +
                    ", value: " + std::to_string(static_cast<int>(enumValue))
                    );
        } // CastUtils::castEnumToString

        /**
         * @brief Converts a string to its corresponding enum value.
         * @details This method retrieves the map of string-to-enum mappings
         *          for the given enum type and finds the enum value corresponding
         *          to the provided string. If the string is not found,
         *          an exception is thrown.
         *
         * @note My implementation was inspired by the previous method.
         *
         * @tparam EnumType The type of the enum to be converted. Must be an enum type.
         * @param strValue The string representation of the enum value.
         *
         * @return EnumType The enum value corresponding to the string.
         */
        template <typename EnumType>
        static EnumType castStringToEnum(const std::string &strValue) {
            static_assert(std::is_enum_v<EnumType>, "Template parameter must be an enum type");

            // Retrieve the map for the given enum type
            const auto &enumToStringMap = Enums::Mapping::EnumMappers::getEnumToStringMap<EnumType>();

            // Find the enum value in the map
            for(const auto &pair : enumToStringMap) {
                if(pair.second == strValue) {
                    return pair.first;
                }
            }

            // Throw an exception if the string is not found
            throw Exceptions::InternalErrorException(
                    "String value not found in the reverse lookup. Enum type: " +
                    std::string(typeid(EnumType).name()) + ", value: " + strValue
                    );
        } // CastUtils::castStringToEnum
    }; // CastUtils
} // IPK25ChatClient::Utilities

#endif // CAST_UTILS_HPP

/*** end of file CastUtils.hpp ***/
