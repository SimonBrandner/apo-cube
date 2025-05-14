#include "transform_3d.hpp"

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"
#include "../math/vector.hpp"

/* transform the cube and set the yaw and pitch by setting the position of the
 * camera and orientation to look at the center of the cube from the given yaw
 * and pitch and roll
 */
Matrix get_transformation_matrix(Camera &camera, Vector cube_center) {
	float yaw = camera.get_yaw();
	float pitch = camera.get_pitch();
	float roll = camera.get_roll();

	float sin_yaw = sin_deg(yaw);
	float cos_yaw = cos_deg(yaw);
	float sin_pitch = sin_deg(pitch);
	float cos_pitch = cos_deg(pitch);
	float sin_roll = sin_deg(roll);
	float cos_roll = cos_deg(roll);

	float distance = camera.get_distance();

	float rel_x = distance * cos_pitch * sin_yaw;
	float rel_y = distance * sin_pitch;
	float rel_z = distance * cos_pitch * cos_yaw;

	// new position of the camera
	Vector new_position = cube_center + Vector(rel_x, rel_y, rel_z);
	camera.set_position(new_position.get_x(), new_position.get_y(),
						new_position.get_z());

	float yaw_array[9] = {cos_yaw, 0, -sin_yaw, 0, 1, 0, sin_yaw, 0, cos_yaw};

	float pitch_array[9] = {1,			0, 0,		  0,		cos_pitch,
							-sin_pitch, 0, sin_pitch, cos_pitch};

	float roll_array[9] = {cos_roll, -sin_roll, 0, sin_roll, cos_roll,
						   0,		 0,			0, 1};

	Matrix yaw_matrix(yaw_array);
	Matrix pitch_matrix(pitch_array);
	Matrix roll_matrix(roll_array);

	// roll must be applied first
	Matrix rotation_matrix = roll_matrix * pitch_matrix * yaw_matrix;
	return rotation_matrix;
}

void transform_vector_3d(const Matrix &rotation_matrix, Camera &camera,
						 Vector &point) {
	point = point - camera.get_position();
	point = rotation_matrix * point;
}
