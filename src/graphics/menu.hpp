#ifndef MENU_HPP
#define MENU_HPP

#include "../geometry/cube.hpp"
#include "screen.hpp"

#define X_OFFSET 10
#define START_BUTTON_INDEX 6
#define EXIT_BUTTON_INDEX 7
#define BUTTON_COUNT 8 // 6 faces + 1 start + 1 exit

Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_face);

#endif // MENU_HPP
