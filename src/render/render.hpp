#ifndef RENDER_HPP
#define RENDER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../math/vector.hpp"
#include "screen.hpp"
#include <array>
#include <optional>

std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> render_cube_points(Cube cube, Camera camera);
void render_cube(CubeColorConfig cube_color_config, Camera camera, Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif //RENDER_HPP
