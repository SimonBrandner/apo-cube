#ifndef TRANSFORM_3D_HPP
#define TRANSFORM_3D_HPP

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"

#define NEAR_PLANE 1e-6f // minimum distance to the near plane

/**
 * @brief Calculates the transformation matrix for the camera using
 * distance from the cube, yaw, pitch, and roll.
 *
 * @param camera The camera object containing the camera's position and
 * orientation.
 * @param cube_center The center of the cube in 3D space.
 * @return The transformation matrix for the camera
 */
Matrix get_transformation_matrix(Camera &camera, Vector cube_center);

/**
 * @brief Transforms a 3D point using the given transformation matrix.
 *
 * @param rotation_matrix The transformation matrix to apply.
 * @param camera The camera object containing the camera's position and
 * orientation.
 * @param point The 3D point to transform.
 */
void transform_vector_3d(const Matrix &rotation_matrix, Camera &camera,
						 Vector &point);

#endif // TRANSFORM_3D_HPP
