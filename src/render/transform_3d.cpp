#include "transform_3d.hpp"

Vector transform_vector(Camera camera, Vector point) {
	Vector camera_position = camera.get_position();
	Vector point_trans_to_camera = point - camera_position;

	float yaw = camera.get_yaw();
	float pitch = camera.get_pitch();

	float yaw_data[9] = {
		cos_deg(yaw), 0, -sin_deg(yaw),
		0, 1, 0,
		sin_deg(yaw), 0, cos_deg(yaw)
	};
	Matrix yaw_matrix = Matrix(yaw_data);

	float pitch_data[9] = {
		1, 0, 0,
		0, cos_deg(pitch), -sin_deg(pitch),
		0, sin_deg(pitch), cos_deg(pitch)
	};
	Matrix pitch_matrix = Matrix(pitch_data);

	Matrix rotation_matrix = yaw_matrix * pitch_matrix;
	Vector transformed_point = rotation_matrix * point_trans_to_camera;
	return transformed_point;
}
