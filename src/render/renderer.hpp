#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "screen.hpp"

#define CUBE_MIDDLE Vector(0, 0, -15)
#define CUBE_EDGE_LENGTH 10

class Renderer {
	private:
		Camera &camera;
		CubeColorConfig cube_color_config;
		Color background_color;

	public:
		Renderer(Camera &camera, CubeColorConfig cube_color_config,
				 Color background_color);
		Screen renderer_cube();
};

void transform_cube(Cube &cube, Camera camera);

#endif // RENDERER_HPP
