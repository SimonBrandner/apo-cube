#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../math/vector.hpp"
#include "screen.hpp"

#include <array>
#include <optional>

class Renderer {
	private:
		Camera &camera;
		CubeColorConfig cube_color_config;
		Color background_color;

	public:
		Renderer(Camera &camera, CubeColorConfig cube_color_config, Color background_color);
		Screen renderer_cube();
};

std::array<std::optional<std::array<Vector, 4>>, 6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION>
transform_cube(Cube cube, Camera camera);

#endif //RENDERER_HPP
