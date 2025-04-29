#include <cstddef>
#include <string>

#include "../mz_apo/font_types.h"
#include "./color.hpp"
#include "./screen.hpp"

void Screen::draw_character(char character, size_t origin_x, size_t origin_y,
							Color color) {
	for (size_t y = 0; y < font_winFreeSystem14x16.maxwidth; ++y) {
		for (size_t x = 0; x < font_winFreeSystem14x16.height; ++x) {
			for (size_t row_index = 0;
				 row_index < font_winFreeSystem14x16.height; ++row_index) {
				// TODO: Render text
			}
		}
	}
}

void Screen::draw_text(std::string text, size_t x, size_t y, Color color) {
	for (auto &character : text) {
		this->draw_character(character, x, y, color);
		x += font_winFreeSystem14x16.maxwidth + 4;
	}
}

void Screen::draw_rectangle(size_t x, size_t y, size_t width, size_t height,
							Color color) {
	for (size_t current_y = 0; current_y < width; ++current_y) {
		for (size_t current_x = 0; current_x < width; ++current_x) {
			this->at(current_x + x, current_y + y) = color;
		}
	}
}

Color &Screen::at(size_t x, size_t y) {
	return this->data[SCREEN_WIDTH * y + x];
}
