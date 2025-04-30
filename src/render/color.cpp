#include "color.hpp"

Color Color::White() { return Color(255, 255, 255); }
Color Color::Black() { return Color(0, 0, 0); }
Color Color::Red() { return Color(255, 0, 0); }

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
	: red(red), green(green), blue(blue) {}

// transfers (0-255, 0-255, 0-255) to (0-31, 0-63, 0-31) that mz apo uses.
uint16_t Color::to_rgb565() const {
	const uint16_t r = (red & 0xF8) << 8;	// 5 bits
	const uint16_t g = (green & 0xFC) << 3; // 6 bits
	const uint16_t b = (blue & 0xF8) >> 3;	// 5 bits
	return r | g | b;
}
