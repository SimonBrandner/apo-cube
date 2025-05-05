#ifndef TRANSFORM_2D_HPP
#define TRANSFORM_2D_HPP

#include "../geometry/side.hpp"
#include "../math/vector.hpp"
#include "./screen.hpp"

void rescale_2d_to_screen(Vector &point2d);
void convert_to_2d(Vector &point, float fov);
void calculate_pixels_bresenham(Side &side, Screen &screen,
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void fill_side(Side &side, Screen &screen,
			   float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH],
			   const bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif // TRANSFORM_2D_HPP
