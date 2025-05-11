#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>

#include "../mz_apo/font_types.h"
#include "color.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

#define CHARACTER_SPACING 4

class Screen {
	private:
		Color data[SCREEN_WIDTH * SCREEN_HEIGHT];

	public:
		Screen();
		Color &at(size_t x, size_t y);
		void draw_rectangle(size_t x, size_t y, size_t width, size_t height,
							Color color);
		size_t draw_character(char character, size_t x, size_t y, Color color,
							  font_descriptor_t *font_descriptor);
		void draw_text(std::string text, size_t x, size_t y, Color color,
					   font_descriptor_t *font_descriptor);
};

#endif // SCREEN_HPP
