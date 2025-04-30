#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

class Color {
	private:
		uint8_t red;
		uint8_t green;
		uint8_t blue;

	public:
		Color();
		Color(uint8_t red, uint8_t green, uint8_t blue);
		uint16_t to_rgb565() const;
};

#endif // COLOR_HPP
