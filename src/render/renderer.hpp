#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"
#include "../graphics/screen.hpp"

/**
 * @brief The Renderer class manages the rendering process of the cube.
 */
class Renderer {
	private:
		Camera &camera; // reference to the camera object
		CubeColorConfig cube_color_config; // color configuration for the cube
		Color background_color; // background color for the screen

	public:
		/**
		 * @brief Constructor for the Renderer class.
		 * Initializes the camera, cube color configuration, and background color.
		 *
		 * @param camera Reference to the Camera object.
		 * @param cube_color_config Color configuration for the cube.
		 * @param background_color Background color for the screen.
		 */
		Renderer(Camera &camera, CubeColorConfig cube_color_config,
				 Color background_color);

		/**
		 * @brief Renders the cube on the screen.
		 *
		 * @return Screen object representing the rendered cube.
		 */
		Screen renderer_cube();
};

/**
 * @brief Transforms the cube's vertices and faces based on the calculated matrix
 */
void transform_cube(Cube &cube, Camera &camera);

#endif // RENDERER_HPP
