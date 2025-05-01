#include "render.hpp"

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "transform_3d.hpp"
#include "transform_2d.hpp"

#include <iostream>
#include <cmath>

std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> render_cube_points(Cube cube, Camera camera) {
	const std::optional<Side>* sides = cube.get_sides();
	std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> projected_sides;

	for (int i = 0; i < 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION; ++i) {
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

void render_cube(CubeColorConfig cube_color_config, Camera camera, Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	float cube_middle_point[3] = {0, 0, -15};
	Cube cube = Cube(cube_middle_point, 10, cube_color_config);

	std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> projected_vertices = render_cube_points(cube, camera);

	// initialize pixels to white
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			pixels[y][x] = Color(255, 255, 255);
		}
	}

	float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			z_buffer[y][x] = -MAXFLOAT;
		}
	}

	for (int i = 0; i < 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION; ++i) {
		if (projected_vertices[i].has_value()) {
			Side side = cube.get_sides()[i].value();
			calculate_pixels_bresenham(
				projected_vertices[i].value(), // projected corners
				side.get_color(), // color
				pixels, // pixels
				z_buffer // z_buffer
			);
		}
	}
}
