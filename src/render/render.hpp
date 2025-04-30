#ifndef RENDER_HPP
#define RENDER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../math/vector.hpp"
#include "../periphs_virtual/input.hpp"
#include "screen.hpp"
#include <array>
#include <optional>

Vector transform_vector(Camera camera, Vector point);
Vector convert_to_2d(Vector point);
std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> render_cube_points(Cube cube, Camera camera);
void calculate_pixels_bresenham(std::array<Vector, 4> corners, Color color,
								Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH],
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void fill_side(std::array<Vector, 4> corners, Color color,
								Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH],
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH],
								bool is_pixel[SCREEN_HEIGHT][SCREEN_WIDTH]);
#endif //RENDER_HPP
