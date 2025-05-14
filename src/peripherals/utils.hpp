#ifndef PERIPHERAL_UTILS_HPP
#define PERIPHERAL_UTILS_HPP

#include "../peripherals/mapping.hpp"

/**
 * @brief Initializes the peripherals and sets up the memory mapping.
 *
 * @return PeripheralMemoryMapping The memory mapping for the peripherals.
 */
PeripheralMemoryMapping setup();

/**
 * @brief Calls the serialize_unlock in MZ_APO to release the lock.
 */
void cleanup();

#endif // PERIPHERAL_UTILS_HPP
