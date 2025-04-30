#ifndef TRANSFORM_3D_HPP
#define TRANSFORM_3D_HPP

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"

Vector transform_vector(Camera camera, Vector point);

#endif //TRANSFORM_3D_HPP
