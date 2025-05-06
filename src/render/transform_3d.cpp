#include "../geometry/camera.hpp"
#include "../geometry/face.hpp"
#include "../math/matrix.hpp"
#include "../math/utils.hpp"
#include "../math/vector.hpp"


Matrix get_transformation_matrix(Camera &camera) {
	float yaw = camera.get_yaw();
	float pitch = camera.get_pitch();

	float sin_yaw = sin_deg(yaw);
	float cos_yaw = cos_deg(yaw);
	float sin_pitch = sin_deg(pitch);
	float cos_pitch = cos_deg(pitch);

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

	Matrix yaw_matrix(yaw_data);
	Matrix pitch_matrix(pitch_data);

	return yaw_matrix * pitch_matrix;
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
		if (point.get_z() >= 0) {
			return false;
		}
	}

	return true;
}
