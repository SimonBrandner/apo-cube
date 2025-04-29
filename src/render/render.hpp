#ifndef RENDER_HPP
#define RENDER_HPP

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "../periphs_virtual/input.hpp"
#include "../periphs_virtual/output.hpp"

Vector transform_vector(Camera camera, Vector point);
Vector convert_to_2d(Vector point);

#endif //RENDER_HPP
