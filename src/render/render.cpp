#include "render.hpp"

#include "../geometry/camera.hpp"
#include "../math/angles.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "../periphs_virtual/input.hpp"
#include "../periphs_virtual/output.hpp"
#include <iostream>

std::array<std::optional<std::array<Vector, 4>>, 6> render_cube_points(Cube cube, Camera camera) {
	const std::optional<Side>* sides = cube.get_sides();
	std::array<std::optional<std::array<Vector, 4>>, 6> projected_sides;

	for (int i = 0; i < 6; ++i) {
		if (sides[i].has_value()) {
			std::array<Vector, 4> corners = sides[i]->get_corners();
			std::array<Vector, 4> projected_corners;

			std::cout << "Side " << i << ":\n";
			for (int j = 0; j < 4; ++j) {
				std::cout << "  Original: " << corners[j] << "\n";
				Vector transformed = transform_vector(camera, corners[j]);
				std::cout << "  Camera Space: " << transformed << "\n";
				Vector projected = convert_to_2d(transformed);
				std::cout << "  2D Screen: " << projected << "\n\n";
				projected_corners[j] = projected;
			}

			projected_sides[i] = projected_corners;
		}
	}

	return projected_sides;
}

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

Vector rescale_2d_to_screen(Vector point2d) {
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;

	float x_screen = (point2d.get_x() + 1.0f) * 0.5f * width;
	float y_screen = (1.0f - point2d.get_y()) * 0.5f * height;

	return Vector(x_screen, y_screen, 0);
}

Vector convert_to_2d(Vector point) {
	float x = point.get_x();
	float y = point.get_y();
	float z = point.get_z();

	// prerspective projection
	const float FOV = 90.0f; // fov deg, now const, in the future parameter maybe
	float near_plane = 0.1f; // Near clipping plane

	float scale = tan_deg(FOV * 0.5f) * near_plane;
	float x_ndc = (x / z) * scale;
	float y_ndc = (y / z) * scale;

	Vector rescaled = Vector(x_ndc, y_ndc, 0);
	rescaled = rescale_2d_to_screen(rescaled);

	return rescaled;
}
