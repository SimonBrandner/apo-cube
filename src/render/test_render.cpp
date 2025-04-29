#include <iostream>
#include <unistd.h>

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "../math/utils.hpp"

Vector transform_vector(Camera camera, Vector point) {
	Vector camera_position = camera.get_position();
	Vector point_trans_to_camera = point - camera_position;

	float yaw = 0;
	float pitch = 0;

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
	std::cout << "Transformed point: " << transformed_point << std::endl;
	return transformed_point;
}

int main(int argc, char *argv[]) {
	Camera camera = Camera();
	Vector point = Vector(10, 10, 10);
	transform_vector(camera, point);

	return 0;
}
