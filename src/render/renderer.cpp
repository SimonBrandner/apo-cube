#include "renderer.hpp"

#include <array>
#include <cmath>

#include "../geometry/camera.hpp"
#include "../math/vector.hpp"
#include "./transform_2d.hpp"
#include "./transform_3d.hpp"

#include <algorithm>

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

	// sort the faces based on their distance from the camera
	std::sort(cube.get_faces().begin(), cube.get_faces().end(),
			  [](const Face &a, const Face &b) {
				  return a.get_distance_from_camera() >
						 b.get_distance_from_camera();
			  });

	// draws all the faces of the cube to the screen
	for (int i = 0; i < NUMBER_OF_FACES; ++i) {
		Face &face = cube.get_faces()[i];
		if (is_face_visible(face)) {
			calculate_pixels_bresenham(face, screen);
		}
	}

	return screen;
}

// transforms the entire cube into 2D space
void transform_cube(Cube &cube, Camera &camera) {
	std::array<Face, (NUMBER_OF_FACES)>& faces = cube.get_faces();

	for (int i = 0; i < NUMBER_OF_FACES; ++i) {
		Face &face = faces[i];

		std::array<Vector, 4> &vertices = face.get_vertices();
		Matrix rotation_matrix = get_transformation_matrix(camera, CUBE_MIDDLE);

		transform_vector_3d(rotation_matrix, camera, face.get_center_point());
		face.set_distance_from_camera(abs(face.get_center_point()));

		for (int j = 0; j < VERTICES; ++j) {
			transform_vector_3d(rotation_matrix, camera, vertices[j]);
			convert_to_2d(vertices[j], camera.get_fov());
		}
	}
}