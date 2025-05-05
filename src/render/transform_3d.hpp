#ifndef TRANSFORM_3D_HPP
#define TRANSFORM_3D_HPP

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"
#include "../math/vector.hpp"

Matrix get_transformation_matrix(Camera &camera);
void transform_vector_3d(const Matrix &rotation_matrix, Camera &camera, Vector &point);

#endif // TRANSFORM_3D_HPP
