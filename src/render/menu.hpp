#ifndef MENU_HPP
#define MENU_HPP

#include "../geometry/cube.hpp"
#include "./screen.hpp"

#define X_OFFSET 10

Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_face);

#endif // MENU_HPP
