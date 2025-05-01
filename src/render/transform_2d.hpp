#ifndef TRANSFORM_2D_HPP
#define TRANSFORM_2D_HPP

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "../math/utils.hpp"
#include "screen.hpp"

Vector rescale_2d_to_screen(const Vector &point2d);
Vector convert_to_2d(const Vector &point, float fov);
void calculate_pixels_bresenham(const std::array<Vector, 4> &vertices, Color color,
								Screen &screen,
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void fill_side(const std::array<Vector, 4> &vertices, Color color, Screen &screen,
			   float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH],
			   const bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif //TRANSFORM_2D_HPP
