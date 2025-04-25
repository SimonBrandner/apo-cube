#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

// Transfers (0-255, 0-255, 0-255) to (0-31, 0-63, 0-31) that mz apo uses.
uint16_t rgb888_to_rgb565(uint8_t r, uint8_t g, uint8_t b);

#endif //UTILS_HPP
