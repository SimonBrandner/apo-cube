#include "transform_3d.hpp"

#include "../math/vector.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"
#include "../geometry/camera.hpp"

Vector transform_vector(Camera camera, Vector point) {
	Vector local_point = point - camera.get_position();;

	float yaw = camera.get_yaw();
	float pitch = camera.get_pitch();

	float yaw_data[9] = {
		cos_deg(yaw), 0, -sin_deg(yaw),
		0, 1, 0,
		sin_deg(yaw), 0, cos_deg(yaw)
	};

	float pitch_data[9] = {
		1, 0, 0,
		0, cos_deg(pitch), -sin_deg(pitch),
		0, sin_deg(pitch), cos_deg(pitch)
	};

	Matrix yaw_matrix = Matrix(yaw_data);
	Matrix pitch_matrix = Matrix(pitch_data);

	Matrix rotation_matrix = yaw_matrix * pitch_matrix;
	return rotation_matrix * local_point;
}
