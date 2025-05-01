#ifndef RENDER_HPP
#define RENDER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../math/vector.hpp"
#include "screen.hpp"

#include <array>
#include <optional>

class Render {
	private:
		Camera &camera;
		CubeColorConfig cube_color_config;

	public:
		Render(Camera &camera, CubeColorConfig cube_color_config);
		Screen render_cube();
};

std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION>
transform_cube(Cube cube, Camera camera);

#endif //RENDER_HPP
