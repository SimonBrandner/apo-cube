#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"
#include "../math/vector.hpp"

void transform_vector(Camera camera, Vector &point) {
	point = point - camera.get_position();

	float yaw = camera.get_yaw();
	float pitch = camera.get_pitch();

	float sin_yaw = sin_deg(yaw);
	float cos_yaw = cos_deg(yaw);
	float sin_pitch = sin_deg(pitch);
	float cos_pitch = cos_deg(pitch);

	float yaw_data[9] = {cos_yaw, 0, -sin_yaw,
		                 0, 1, 0,
						 sin_yaw, 0, cos_yaw};

	float pitch_data[9] = {1, 0, 0,
						   0, cos_pitch, -sin_pitch,
						   0, sin_pitch, cos_pitch};

	Matrix yaw_matrix = Matrix(yaw_data);
	Matrix pitch_matrix = Matrix(pitch_data);

	Matrix rotation_matrix = yaw_matrix * pitch_matrix;
	point = rotation_matrix * point;
}
