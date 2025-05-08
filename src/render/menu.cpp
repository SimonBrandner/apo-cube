#include <cstddef>
#include <cstdint>
#include <string>

#include "../mz_apo/font_types.h"
#include "./menu.hpp"
#include "./screen.hpp"

Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_button) {
	Screen screen = Screen();
	Color text_color = Color::White();
	font_descriptor_t font = font_winFreeSystem14x16;
	std::string labels[6] = {"Front:", "Back:", "Left:",
							 "Right:", "Top",	"Bottom"}; // Strange Charm!

	screen.draw_text("Welcome to apo-cube!", 10, 10, text_color, &font);
	screen.draw_rectangle(4, 55 + selected_button * 20, 4, 4, text_color);

	for (size_t i = 0; i < 6; ++i) {
		Color color = cube_coloring_config.at(i);
		size_t y = 50 + i * 20;

		screen.draw_text(labels[i], X_OFFSET, y, text_color, &font);
		screen.draw_rectangle(100, y, font.height, font.height, color);

		screen.draw_text(std::to_string(color.get_red()), 200, y, text_color,
						 &font);
		screen.draw_text(std::to_string(color.get_green()), 250, y, text_color,
						 &font);
		screen.draw_text(std::to_string(color.get_blue()), 300, y, text_color,
						 &font);
	}

	screen.draw_text("Start", X_OFFSET, 50 + START_BUTTON_INDEX * 20,
					 text_color, &font);
	screen.draw_text("Exit", X_OFFSET, 50 + EXIT_BUTTON_INDEX * 20, text_color,
					 &font);

	return screen;
}
