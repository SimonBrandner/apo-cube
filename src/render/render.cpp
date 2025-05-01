#include "render.hpp"

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "transform_3d.hpp"
#include "transform_2d.hpp"

#include <array>
#include <iostream>
#include <cmath>

#define CUBE_MIDDLE Vector(0, 0, -15)
#define CUBE_SIDE_LENGTH 10

Render::Render(Camera& camera, CubeColorConfig cube_color_config)
	: camera(camera), cube_color_config(cube_color_config) {}

// renders the entire cube onto the screen
void Render::render_cube(Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	Cube cube(CUBE_MIDDLE, CUBE_SIDE_LENGTH, cube_color_config);

	std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> projected_vertices = transform_cube(cube, camera);

	// initialize pixels to white
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			pixels[y][x] = Color(255, 255, 255);
		}
	}

	// initialize z buffer to min, the higher the z value, the closer the pixel is to the camera
	float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			z_buffer[y][x] = -MAXFLOAT;
		}
	}

	// draws all the sides of the cube to the screen
	for (int i = 0; i < 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION; ++i) {
		if (projected_vertices[i].has_value()) {
			Side side = cube.get_sides()[i].value();
			calculate_pixels_bresenham(
				projected_vertices[i].value(), // projected corners
				side.get_color(), // color of the side
				pixels, // 2d array of pixels
				z_buffer // 2d array of pixels z buffer
			);
		}
	}
}

// transforms the entire cube into 2D space
std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> transform_cube(Cube cube, Camera camera) {
	const std::optional<Side>* sides = cube.get_sides();
	std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> projected_sides;

	for (int i = 0; i < 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION; ++i) {
		if (sides[i].has_value()) {
			std::array<Vector, 4> corners = sides[i]->get_corners();
			std::array<Vector, 4> projected_corners;

			for (int j = 0; j < 4; ++j) {
				Vector transformed = transform_vector(camera, corners[j]);
				projected_corners[j] = convert_to_2d(transformed);
			}

			projected_sides[i] = projected_corners;
		}
	}

	return projected_sides;
}
