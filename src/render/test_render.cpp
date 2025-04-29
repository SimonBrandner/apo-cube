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

	std::array<std::optional<std::array<Vector, 4>>, 6> projected_corners = render_cube_points(cube, camera);

	for (int i = 0; i < 6; ++i) {
		if (projected_corners[i].has_value()) {
			std::cout << "Projected Corners for Side " << i << ":\n";
			for (const auto& corner : projected_corners[i].value()) {
				std::cout << corner << "\n";
			}
			std::cout << "\n";
		}
	}

	return 0;
}
