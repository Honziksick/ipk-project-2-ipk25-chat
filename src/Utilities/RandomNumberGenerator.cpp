/*******************************************************************************
 *                                                                             *
 * Project:      IPK25 Chat Client                                             *
 * University:   Faculty of Information Technology, BUT                        *
 * Subject:      IPK: Computer Communications and Networks                     *
 *                                                                             *
 * File:         RandomNumberGenerator.cpp                                     *
 * Author:       Jan Kalina <xkalinj00>                                        *
 *                                                                             *
 * Created:      08.04.2025                                                    *
 * Last edit:    08.04.2025                                                    *
 *                                                                             *
 * Description:  This file contains the implementation of the                  *
 *               RandomNumberGenerator class, which provides utility           *
 *               functions for random number generation.                       *
 *                                                                             *
 ******************************************************************************/
/**
 * @file RandomNumberGenerator.cpp
 * @author Jan Kalina \<xkalinj00>
 * @brief Implementation of the RandomNumberGenerator class for random
 *        number generation.
 */

#include "Utilities/RandomNumberGenerator.hpp"
#include "Constants/RandomNumbersRanges.hpp"

using namespace IPK25ChatClient::Constants;
using namespace std;

namespace IPK25ChatClient::Utilities
{
    // Inicialize the static members of the RandomNumberGenerator class
    random_device RandomNumberGenerator::mRandomDevice;
    mt19937 RandomNumberGenerator::mRandomGenerator(mRandomDevice());
    uniform_int_distribution<uint16_t> RandomNumberGenerator::mPortDistribution16(RandomNumbersRange::MIN_EPHEMERAL_PORT,
                                                                                  RandomNumbersRange::MAX_EPHEMERAL_PORT); // recommended ephemeral port range

    uint16_t RandomNumberGenerator::getEphemeralPort16() {
        return mPortDistribution16(mRandomGenerator);
    } // RandomNumberGenerator::getEphemeralPort16()
} // IPK25ChatClient::Utilities

/*** end of file RandomNumberGenerator.hpp ***/
