#include "utils.hpp"
#include  "../periphs_virtual/output.hpp"

// default constructor
Color::Color() : r(0), g(0), b(0) {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
	: r(red), g(green), b(blue) {}

// transfers (0-255, 0-255, 0-255) to (0-31, 0-63, 0-31) that mz apo uses.
uint16_t Color::to_rgb565() const {
	uint16_t red = (r & 0xF8) << 8;  // 5 bits
	uint16_t green = (g & 0xFC) << 3;  // 6 bits
	uint16_t blue = (b & 0xF8) >> 3;  // 5 bits
	return red | green | blue;
}
