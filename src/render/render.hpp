#ifndef RENDER_HPP
#define RENDER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../math/vector.hpp"
#include "../periphs_virtual/input.hpp"
#include <array>
#include <optional>

Vector transform_vector(Camera camera, Vector point);
Vector convert_to_2d(Vector point);
std::array<std::optional<std::array<Vector, 4>>, 6> render_cube_points(Cube cube, Camera camera);

#endif //RENDER_HPP
