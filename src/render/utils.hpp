#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

class Color {
public:
	uint8_t r, g, b;

	// Default constructor
	Color();

	// Takes 3x 8-bit values (0-255) of r, g, b
	Color(uint8_t red, uint8_t green, uint8_t blue);

	// Convert RGB888 to RGB565
	uint16_t to_rgb565() const;
};

#endif //UTILS_HPP
