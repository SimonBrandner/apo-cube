#include <cstddef>
#include <iostream>
#include <string>

#include "../mz_apo/font_types.h"
#include "./color.hpp"
#include "./screen.hpp"

size_t get_character_width(font_descriptor_t *font_descriptor, int character) {
	if ((character < font_descriptor->firstchar) ||
		(character - font_descriptor->firstchar >= font_descriptor->size)) {
		std::cerr << "Character not in font!" << std::endl;
		exit(-1);
	}

	if (font_descriptor->width) {
		return font_descriptor->width[character - font_descriptor->firstchar];
	}
	return font_descriptor->maxwidth;
}

const font_bits_t *get_character_bits(char character,
									  font_descriptor_t *font_descriptor) {
	return font_descriptor->bits +
		   font_descriptor->height * (character - font_descriptor->firstchar);
}

Screen::Screen() {
	for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) {
		this->data[i] = Color();
	}
}

size_t Screen::draw_character(char character, size_t origin_x, size_t origin_y,
							  Color color, font_descriptor_t *font_descriptor) {
	size_t character_width = get_character_width(font_descriptor, character);
	const font_bits_t *character_bits =
		get_character_bits(character, font_descriptor);

	for (size_t y = 0; y < font_descriptor->height; ++y) {
		for (size_t x = 0; x < character_width; ++x) {
			if ((character_bits[y] >> (16 - x)) & 0x01) {
				this->at(origin_x + x, origin_y + y) = color;
			}
		}
	}
	return character_width;
}

void Screen::draw_text(std::string text, size_t x, size_t y, Color color,
					   font_descriptor_t *font_descriptor) {
	for (auto &character : text) {
		x += this->draw_character(character, x, y, color, font_descriptor) +
			 CHARACTER_SPACING;
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
