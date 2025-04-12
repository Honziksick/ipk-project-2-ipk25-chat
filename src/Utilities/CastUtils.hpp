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
 * Last edit:    09.04.2025                                                    *
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

#include "Enums/Mapping/EnumMaps.hpp"
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
            const auto &enumToStringMap = Enums::EnumMaps::getEnumToStringMap<EnumType>();

            // Find the enum value in the map
            auto iterator = enumToStringMap.find(enumValue);
            if(iterator != enumToStringMap.end()) {
                return iterator->second;
            }

            // Throw an exception if the value is not found
            throw Exceptions::InternalErrorException(
                    "Enum value not found in the map. Enum type: " + std::string(typeid(EnumType).name()) +
                    ", value: " + std::to_string(static_cast<int>(enumValue))
                    );
        } // CastUtils::castEnumToString
    }; // CastUtils
} // IPK25ChatClient::Utilities

#endif // CAST_UTILS_HPP

/*** end of file CastUtils.hpp ***/
