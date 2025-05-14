#include "menu.hpp"

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
	screen.draw_rectangle(4, Y_OFFSET + 6 + selected_button * ROW_HEIGHT, 4, 4,
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
		"In the menu, press red and blue knobs to",
		"change selection, the green knob to click,",
		"and rotate knobs to adjust face colors. In",
		"the cube view, press the red knob to exit or",
		"rotate knobs to change zoom, pitch and yaw."};

	for (size_t i = 0; i < INFO_TEXT_ROW_COUNT; ++i) {
		screen.draw_text(text_rows[i], X_OFFSET,
						 Y_OFFSET + (BUTTON_COUNT + 1 + i) * ROW_HEIGHT,
						 text_color, &font);
	}

	return screen;
}
