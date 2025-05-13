#ifndef TRANSFORM_3D_HPP
#define TRANSFORM_3D_HPP

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "../geometry/face.hpp"

#define NEAR_PLANE 1e-6f

Matrix get_transformation_matrix(Camera &camera, Vector cube_center);
void transform_vector_3d(const Matrix &rotation_matrix, Camera &camera, Vector &point);

#endif // TRANSFORM_3D_HPP
