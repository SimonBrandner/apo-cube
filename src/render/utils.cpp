#include "utils.hpp"

uint16_t rgb888_to_rgb565(uint8_t red, uint8_t green, uint8_t blue) {
	uint16_t r = (red & 0xF8) << 8; // 5 bits
	uint16_t g = (green & 0xFC) << 3; // 6 bits
	uint16_t b = (blue & 0xF8) >> 3; // 5 bits

	return r | g | b;
}
