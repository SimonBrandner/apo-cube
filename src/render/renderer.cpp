#include "renderer.hpp"

#include <array>
#include <cmath>

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "./transform_2d.hpp"
#include "./transform_3d.hpp"

#define CUBE_MIDDLE Vector(0, 0, -15)
#define CUBE_EDGE_LENGTH 10

Renderer::Renderer(Camera &camera, CubeColorConfig cube_color_config,
				   Color background_color)
	: camera(camera), cube_color_config(cube_color_config),
	  background_color(background_color) {}

// renderers the entire cube onto the screen
Screen Renderer::renderer_cube() {
	Screen screen = Screen();

	Cube cube(CUBE_MIDDLE, CUBE_EDGE_LENGTH, cube_color_config);
	transform_cube(cube, camera);

	// set background color
	screen.draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background_color);

	// initialize z buffer to min, the higher the z value, the closer the pixel
	// is to the camera
	float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			z_buffer[y][x] = -MAXFLOAT;
		}
	}

	// draws all the faces of the cube to the screen
	for (int i = 0; i < NUMBER_OF_FACES; ++i) {
		Face &face = cube.get_faces()[i];
		calculate_pixels_bresenham(face,
								   screen,	// Screen -> array of pixels
								   z_buffer // 2d array of pixels z buffer
		);
	}

	return screen;
}

// transforms the entire cube into 2D space
void transform_cube(Cube &cube, Camera camera) {
	for (int i = 0; i < NUMBER_OF_FACES; ++i) {
		// pass by reference to avoid copying issue
		std::array<Vector, 4> &vertices = cube.get_faces()[i].get_vertices();
		Matrix rotation_matrix = get_transformation_matrix(camera);

		for (int j = 0; j < 4; ++j) {
			transform_vector_3d(rotation_matrix, camera, vertices[j]);
			convert_to_2d(vertices[j], camera.get_fov());
		}
	}
}