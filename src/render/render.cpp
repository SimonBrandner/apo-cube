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

			for (int j = 0; j < 4; ++j) {
				Vector transformed = transform_vector(camera, corners[j]);
				Vector projected = convert_to_2d(transformed);
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
	float near_plane = 0.1f;

	float scale = tan_deg(FOV * 0.5f) * near_plane;
	float x_ndc = (x / z) * scale;
	float y_ndc = (y / z) * scale;

	Vector rescaled = Vector(x_ndc, y_ndc, z); // z will be used for z-index
	rescaled = rescale_2d_to_screen(rescaled);

	return rescaled;
}

void calculate_pixels_bresenham(std::array<Vector, 4> corners, Color color,
								Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH],
								float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	for (size_t i = 0; i < corners.size(); ++i) {
		Vector start = corners[i];
		Vector end = corners[(i + 1) % corners.size()];

		int x0 = static_cast<int>(start.get_x());
		int y0 = static_cast<int>(start.get_y());
		float z0 = start.get_z();

		int x1 = static_cast<int>(end.get_x());
		int y1 = static_cast<int>(end.get_y());
		float z1 = end.get_z();

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;

		int total_steps = std::max(dx, dy);
		int step_count = 0;

		while (true) {
			if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
				float t = (total_steps == 0) ? 0.0f : (float)step_count / total_steps;
				float z = z0 + t * (z1 - z0);

				if (z > z_buffer[y0][x0]) {
					z_buffer[y0][x0] = z;
					pixels[y0][x0] = color;
					std::cout << "Pixel set at (" << x0 << ", " << y0 << ") with color: ";
				}
			}

			if (x0 == x1 && y0 == y1) break;

			int e2 = 2 * err;
			if (e2 > -dy) {
				err -= dy;
				x0 += sx;
			}
			if (e2 < dx) {
				err += dx;
				y0 += sy;
			}
			++step_count;
		}
	}
}


// UNUSED RN, MAYBE USEFUL IN THE FUTURE
void sort_projected_corners(std::array<std::optional<std::array<Vector, 4>>, 6> *projected_corners, Camera camera) {
	for (int i = 0; i < 6 - 1; ++i) {
		for (int j = 0; j < 6 - i - 1; ++j) {
			if ((*projected_corners)[j].has_value() && (*projected_corners)[j + 1].has_value()) {
				float dist1 = Side((*projected_corners)[j].value()[0], 0, Color(), 'f').get_center_point().distance(camera.get_position());
				float dist2 = Side((*projected_corners)[j + 1].value()[0], 0, Color(), 'f').get_center_point().distance(camera.get_position());

				if (dist1 < dist2) {
					std::swap((*projected_corners)[j], (*projected_corners)[j + 1]);
				}
			}
		}
	}
}

