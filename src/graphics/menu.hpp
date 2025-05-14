#ifndef MENU_HPP
#define MENU_HPP

#include "../geometry/cube.hpp"
#include "screen.hpp"

#define X_OFFSET 10 // X offset for text from the top of the screen
#define Y_OFFSET 40 // Y offset for text from the left of the screen
#define START_BUTTON_INDEX 6 // Index of the start button
#define EXIT_BUTTON_INDEX 7 // Index of the exit button
#define BUTTON_COUNT 8 // 6 faces + 1 start + 1 exit
#define ROW_HEIGHT 20 // Height of each row in the menu
#define INFO_TEXT_ROW_COUNT 5 // Number of rows for the info text

/**
 * Draws the menu screen with the given cube color configuration
 * and selected face.
 *
 * @param cube_coloring_config The color configuration of the cube.
 * @param selected_face The index of the currently selected face.
 * @return The screen object representing the drawn menu.
 */
Screen draw_menu(CubeColorConfig cube_coloring_config, int8_t selected_face);
Screen draw_exit_screen();

#endif // MENU_HPP
