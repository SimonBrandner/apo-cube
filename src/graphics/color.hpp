#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

class Color {
	private:
		uint8_t red;
		uint8_t green;
		uint8_t blue;

	public:
		static Color White();
		static Color Black();
		static Color Red();
		static Color Blue();
		static Color Magenta();
		static Color Cyan();
		static Color Green();
		static Color Yellow();

		Color();
		Color(uint8_t red, uint8_t green, uint8_t blue);

		uint16_t to_rgb565() const;
		uint8_t get_red() const;
		uint8_t get_green() const;
		uint8_t get_blue() const;
};

#endif // COLOR_HPP
