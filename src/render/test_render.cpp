#include <iostream>
#include <unistd.h>

#include "../geometry/camera.hpp"
#include "../geometry/side.hpp"
#include "../geometry/cube.hpp"

#include "../math/vector.hpp"
#include "render.hpp"

int main(int argc, char *argv[]) {
	CubeColorConfig cube_color_config = CubeColorConfig();
	cube_color_config.back = Color(0, 0, 255);
	cube_color_config.front = Color(255, 0, 0);
	cube_color_config.top = Color(0, 255, 0);
	cube_color_config.bottom = Color(255, 255, 0);
	cube_color_config.left = Color(255, 0, 255);
	cube_color_config.right = Color(0, 255, 255);

	float side[3] = {0, 0, 0};
	Cube cube = Cube(side, 10);
	cube.set_color_config(cube_color_config);
	Camera camera = Camera();

	const std::optional<Side>* sides = cube.get_sides();
	for (int i = 0; i < 6; ++i) {
		if (sides[i].has_value()) {
			Vector center = sides[i]->get_center_point();
			std::cout << "Side " << i << " center: " << center << std::endl;
			std::array<Vector, 4> corners = sides[i]->get_corners();
			std::cout << "Corners: ";
			for (int j = 0; j < 4; ++j) {
				std::cout << corners[j] << " ";
				corners[j] = transform_vector(camera, corners[j]);
				std::cout << corners[j] << " \n";
			}
			std::cout << std::endl;
		}
	}

	return 0;
}
