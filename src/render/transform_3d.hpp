#ifndef TRANSFORM_3D_HPP
#define TRANSFORM_3D_HPP

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "../math/matrix.hpp"

Matrix get_transformation_matrix(Camera &camera, Vector middle_cube);
void transform_vector_3d(const Matrix &rotation_matrix, Camera &camera, Vector &point);
bool is_face_visible(Face &face);

#endif // TRANSFORM_3D_HPP
