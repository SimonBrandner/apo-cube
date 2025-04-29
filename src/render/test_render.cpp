#include <iostream>
#include <unistd.h>

#include "../geometry/camera.hpp"
#include "../geometry/side.hpp"
#include "../geometry/cube.hpp"

#include "../math/vector.hpp"
#include "../periphs_virtual/output.hpp"
#include "render.hpp"
#include "screen.hpp"

#include <math.h>

int main(int argc, char *argv[]) {
	CubeColorConfig cube_color_config = CubeColorConfig();
	cube_color_config.back = Color(0, 0, 255);
	cube_color_config.front = Color(255, 0, 0);
	cube_color_config.top = Color(0, 255, 0);
	cube_color_config.bottom = Color(255, 255, 0);
	cube_color_config.left = Color(255, 0, 255);
	cube_color_config.right = Color(0, 255, 255);

	float side_array[3] = {0, 0, 15};
	Cube cube = Cube(side_array, 10);
	cube.set_color_config(cube_color_config);
	Camera camera = Camera();

	std::array<std::optional<std::array<Vector, 4>>, 6> projected_vertices = render_cube_points(cube, camera);

	Color pixels[SCREEN_HEIGHT][SCREEN_WIDTH];
	// initialize pixels to black
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

	for (int i = 0; i < 6; ++i) {
		if (projected_vertices[i].has_value()) {
			Side side = cube.get_sides()[i].value();
			std::cout << "Sorted Projected Corners for Side " << i << " ";
			std::cout << "Position: " << side.get_center_point().distance(camera.get_position()) << "\n";
			calculate_pixels_bresenham(
				projected_vertices[i].value(), // projected corners
				side.get_color(), // color
				pixels, // pixels
				z_buffer // z_buffer
			);
		}
	}



	OutputPeripherals outputs = OutputPeripherals();
	outputs.set_screen(pixels);

	return 0;
}
