#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <iostream>

class Color {
	private:
		uint8_t red;
		uint8_t green;
		uint8_t blue;

	public:
		static Color White();
		static Color Black();
		static Color Red();

		Color();
		Color(uint8_t red, uint8_t green, uint8_t blue);
		uint16_t to_rgb565() const;

		uint8_t get_red();
		uint8_t get_green();
		uint8_t get_blue();
};

#endif // COLOR_HPP
