#include <cstddef>
#include <cstdint>
#include <string>

#include "../mz_apo/font_types.h"
#include "./menu.hpp"
#include "./screen.hpp"

Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_face) {
	Screen screen = Screen();
	Color text_color = Color();

	screen.draw_text("Welcome to apo-cube!", 10, 10, text_color,
					 &font_winFreeSystem14x16);

	std::string labels[6] = {"Front:", "Back:", "Left:",
							 "Right:", "Top",	"Bottom"}; // Strange Charm!
	for (size_t i = 0; i < 6; ++i) {
		screen.draw_text(labels[i], 10, 50 + i * 20, text_color,
						 &font_winFreeSystem14x16);
	}

	Color colors[6];
	for (size_t i = 0; i < 6; ++i) {
		screen.draw_rectangle(100, 50 + i * 20, 30,
							  font_winFreeSystem14x16.height, text_color);
	}

	screen.draw_rectangle(4, 60 + selected_face * 20, 4, 4, text_color);

	return screen;
}
