#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <cstddef>
#include <string>

#include "./color.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 360

class Screen {
	private:
		Color data[SCREEN_WIDTH * SCREEN_HEIGHT];

	public:
		Color &at(size_t x, size_t y);
		void draw_rectangle(size_t x, size_t y, size_t width, size_t height,
							Color color);
		void draw_character(char character, size_t x, size_t y, Color color);
		void draw_text(std::string text, size_t x, size_t y, Color color);
};

#endif // SCREEN_HPP
