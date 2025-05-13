#ifndef MENU_HPP
#define MENU_HPP

#include "../geometry/cube.hpp"
#include "screen.hpp"

#define X_OFFSET 10
#define Y_OFFSET 40
#define START_BUTTON_INDEX 6
#define EXIT_BUTTON_INDEX 7
#define BUTTON_COUNT 8 // 6 faces + 1 start + 1 exit
#define ROW_HEIGHT 20
#define INFO_TEXT_ROW_COUNT 5

Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_face);

#endif // MENU_HPP
