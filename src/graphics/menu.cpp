#include "menu.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

#include "../mz_apo/font_types.h"
#include "screen.hpp"

Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_button) {
	Screen screen = Screen();
	Color text_color = Color::White();
	font_descriptor_t font = font_winFreeSystem14x16;
	std::string labels[NUMBER_OF_FACES] = {
		"Front:", "Back:", "Left:",
		"Right:", "Top",   "Bottom"}; // Strange Charm!

	screen.draw_text("Welcome to apo-cube!", 10, 10, text_color, &font);
	screen.draw_rectangle(4, 55 + selected_button * ROW_HEIGHT, 4, 4,
						  text_color);

	for (size_t i = 0; i < NUMBER_OF_FACES; ++i) {
		Color color = cube_coloring_config.at(i);
		size_t y = Y_OFFSET + i * ROW_HEIGHT;

		screen.draw_text(labels[i], X_OFFSET, y, text_color, &font);
		screen.draw_rectangle(100, y, font.height, font.height, color);

		screen.draw_text(std::to_string(color.get_red()), 200, y, text_color,
						 &font);
		screen.draw_text(std::to_string(color.get_green()), 250, y, text_color,
						 &font);
		screen.draw_text(std::to_string(color.get_blue()), 300, y, text_color,
						 &font);
	}

	screen.draw_text("Start", X_OFFSET,
					 Y_OFFSET + START_BUTTON_INDEX * ROW_HEIGHT, text_color,
					 &font);
	screen.draw_text("Exit", X_OFFSET,
					 Y_OFFSET + EXIT_BUTTON_INDEX * ROW_HEIGHT, text_color,
					 &font);

	std::string text_rows[INFO_TEXT_ROW_COUNT] = {
		"Press red and blue knobs to move around",
		"the menu. Press the green knob to click",
		"in the menu. Rotate knobs to adjust face",
		"colors in the menu. Press the green knob",
		"to exit the 3D cube render. "};

	for (size_t i = 0; i < INFO_TEXT_ROW_COUNT; ++i) {
		screen.draw_text(text_rows[i], X_OFFSET,
						 Y_OFFSET + (BUTTON_COUNT + 1 + i) * ROW_HEIGHT,
						 text_color, &font);
	}

	return screen;
}
