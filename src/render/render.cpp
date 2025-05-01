#include "render.hpp"

#include <array>
#include <iostream>
#include <cmath>

#include "../geometry/camera.hpp"
#include "../math/matrix.hpp"
#include "../math/vector.hpp"
#include "transform_3d.hpp"
#include "transform_2d.hpp"

#define CUBE_MIDDLE Vector(0, 0, -15)
#define CUBE_SIDE_LENGTH 10

Render::Render(Camera &camera, CubeColorConfig cube_color_config)
	: camera(camera), cube_color_config(cube_color_config) {}

// renders the entire cube onto the screen
Screen Render::render_cube() {
	Screen screen = Screen();

	Cube cube(CUBE_MIDDLE, CUBE_SIDE_LENGTH, cube_color_config);
	std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> projected_vertices = transform_cube(cube, camera);

	// set background color
	screen.draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cube_color_config.screen_background);

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
				projected_vertices[i].value(), // projected vertices
				side.get_color(), // color of the side
				screen, // Screen -> array of pixels
				z_buffer // 2d array of pixels z buffer
			);
		}
	}

	return screen;
}

// transforms the entire cube into 2D space
std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> transform_cube(Cube cube, Camera camera) {
	const std::optional<Side>* sides = cube.get_sides();
	std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION> projected_sides;

	for (int i = 0; i < 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION; ++i) {
		if (sides[i].has_value()) {
			// pass by reference to avoid copying issue
			std::array<Vector, 4> vertices = sides[i]->get_vertices();
			std::array<Vector, 4> projected_vertices;

			for (int j = 0; j < 4; ++j) {
				Vector transformed = transform_vector(camera, vertices[j]);
				projected_vertices[j] = convert_to_2d(transformed, camera.get_fov());
			}

			// pass by reference to avoid copying issue
			projected_sides[i] = projected_vertices;
		}
	}

	return projected_sides;
}
