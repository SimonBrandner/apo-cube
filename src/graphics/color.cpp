#include "color.hpp"

Color Color::White() { return Color(255, 255, 255); }
Color Color::Black() { return Color(0, 0, 0); }
Color Color::Red() { return Color(255, 0, 0); }
Color Color::Blue() { return Color(0, 0, 255); }
Color Color::Magenta() { return Color(255, 0, 255); }
Color Color::Cyan() { return Color(0, 255, 255); }
Color Color::Green() { return Color(0, 255, 0); }
Color Color::Yellow() { return Color(255, 255, 0); }

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
	: red(red), green(green), blue(blue) {}

uint16_t Color::to_rgb565() const {
	const uint16_t r = (red & 0xF8) << 8;	// 5 bits
	const uint16_t g = (green & 0xFC) << 3; // 6 bits
	const uint16_t b = (blue & 0xF8) >> 3;	// 5 bits
	return r | g | b;
}

uint8_t Color::get_red() const { return this->red; }
uint8_t Color::get_green() const { return this->green; }
uint8_t Color::get_blue() const { return this->blue; }
