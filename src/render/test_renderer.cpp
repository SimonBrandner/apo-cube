#include <iostream>
#include <chrono>

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"

#include "../periphs_virtual/output.hpp"
#include "../periphs_virtual/input.hpp"
#include "renderer.hpp"
#include "screen.hpp"

// this will keep renderering frames based of the input delta.
int main(int argc, char *argv[]) {
	OutputPeripherals outputs = OutputPeripherals();
	InputPeripherals inputs = InputPeripherals();

	auto last_time = std::chrono::high_resolution_clock::now();
	int frame_count = 0;

	Camera camera = Camera();

	CubeColorConfig cube_color_config = CubeColorConfig();
	cube_color_config.back = Color(0, 0, 255);
	cube_color_config.front = Color(255, 0, 0);
	cube_color_config.top = Color(0, 255, 0);
	cube_color_config.bottom = Color(255, 255, 0);
	cube_color_config.left = Color(255, 0, 255);
	cube_color_config.right = Color(0, 255, 255);

	Color background_color = Color(0, 0, 0);

	Renderer renderer = Renderer(camera, cube_color_config, background_color);

	while (true) {
		KnobRotation delta = inputs.get_delta();
		camera.update(delta);

		Screen screen = renderer.renderer_cube();
		outputs.set_screen(screen);

		frame_count++;
		auto current_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> elapsed = current_time - last_time;
		if (elapsed.count() >= 1.0f) {
			std::cout << "FPS: " << frame_count << "\n";
			frame_count = 0;
			last_time = current_time;
		}
	}

	return 0;
}
