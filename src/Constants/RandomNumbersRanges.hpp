/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         RandomNumbersRanges.hpp                                       *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      08.04.2025                                                    *
 * Last edit:    08.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains constant ranges for random number          *
 *               generation used in the IPK25 Chat Client project.             *
 *                                                                             *
 ******************************************************************************/
/**
 * @file RandomNumbersRanges.hpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Header file defining constant ranges for random number generation.
 */

#ifndef RANDOM_NUMBERS_RANGES_HPP
#define RANDOM_NUMBERS_RANGES_HPP

#include <cstdint> // uint16_t, uint32_t

namespace IPK25ChatClient::Constants
{
    /**
     * @class RandomNumbersRange
     * @brief Class containing constant ranges for random number generation.
     */
    class RandomNumbersRange {
    public:
        // Defines the range for 16-bit ephemeral port numbers.
        // For more details, see: https://en.wikipedia.org/wiki/Ephemeral_port
        static constexpr uint16_t MIN_EPHEMERAL_PORT = 49152;  /**< Minimum value for ephemeral port range. */
        static constexpr uint16_t MAX_EPHEMERAL_PORT = 65535;  /**< Maximum value for ephemeral port range. */
    }; // RandomNumbersRange
} // namespace IPK25ChatClient::Constants

#endif // RANDOM_NUMBERS_RANGES_HPP

/*** end of file RandomNumbersRanges.hpp ***/
