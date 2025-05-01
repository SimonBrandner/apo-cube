#ifndef TRANSFORM_2D_HPP
#define TRANSFORM_2D_HPP

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "../math/utils.hpp"
#include "screen.hpp"

Vector convert_to_2d(Vector point);
void calculate_pixels_bresenham(std::array<Vector, 4> vertices, Color color,
								Screen &screen,
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void fill_side(std::array<Vector, 4> vertices, Color color, Screen &screen,
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH],
								bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif //TRANSFORM_2D_HPP
