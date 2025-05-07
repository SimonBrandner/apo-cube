#include "../geometry/camera.hpp"
#include "../geometry/face.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"
#include "../math/vector.hpp"

#include <iostream>

Matrix get_transformation_matrix(Camera &camera, Vector middle_cube) {
	float yaw = camera.get_yaw();
	float pitch = camera.get_pitch();
	float roll = camera.get_roll();

	float sin_yaw = sin_deg(yaw);
	float cos_yaw = cos_deg(yaw);
	float sin_pitch = sin_deg(pitch);
	float cos_pitch = cos_deg(pitch);
	float sin_roll = sin_deg(roll);
	float cos_roll = cos_deg(roll);

	float distance = camera.get_distance_from_cube();  //camera.get_position().distance(middle_cube);

	float rel_x = distance * cos_pitch * sin_yaw;
	float rel_y = distance * sin_pitch;
	float rel_z = distance * cos_pitch * cos_yaw;


	Vector new_position = middle_cube + Vector(rel_x, rel_y, rel_z);
	camera.set_position(new_position.get_x(), new_position.get_y(), new_position.get_z());

	float yaw_data[9] = {
		cos_yaw, 0, -sin_yaw,
		0,       1, 0,
		sin_yaw, 0, cos_yaw
	};

	float pitch_data[9] = {
		1, 0,          0,
		0, cos_pitch, -sin_pitch,
		0, sin_pitch,  cos_pitch
	};

	float roll_data[9] = {
		cos_roll, -sin_roll, 0,
		sin_roll,  cos_roll, 0,
		0,         0,        1
	};

	Matrix yaw_matrix(yaw_data);
	Matrix pitch_matrix(pitch_data);
	Matrix roll_matrix(roll_data);

	Matrix rotation_matrix = roll_matrix * pitch_matrix * yaw_matrix;
	return rotation_matrix;
}

void transform_vector_3d(const Matrix &rotation_matrix, Camera &camera, Vector &point) {
	point = point - camera.get_position();
	point = rotation_matrix * point;
}

// TODO, implement also the FOV frustum
bool is_face_inside_fov(Face &face, float fov) {
	auto vertices = face.get_vertices();
	for (int i = 0; i < 4; ++i) {
		Vector point = vertices[i];
		if (point.get_z() >= -1e-5f) {
			return false;
		}
	}

	return true;
}
