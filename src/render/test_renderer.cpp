#include <iostream>
#include <chrono>

#include "../geometry/camera.hpp"
#include "../geometry/cube.hpp"

#include "../periphs_virtual/output.hpp"
#include "../periphs_virtual/input.hpp"
#include "../graphics/screen.hpp"
#include "renderer.hpp"

/**
 * This is a test program for the renderer for virtual peripherals.
 * The main for the real peripherals is in src/main.cpp.
 * This will keep rendering frames based of the input delta.
 */
int main(int argc, char *argv[]) {
	OutputPeripherals outputs = OutputPeripherals();
	InputPeripherals inputs = InputPeripherals();

	auto last_time = std::chrono::high_resolution_clock::now();
	int frame_count = 0;

	Camera camera = Camera();

	CubeColorConfig cube_color_config = CubeColorConfig();

	Color background_color = Color::White();

	Renderer renderer = Renderer(camera, cube_color_config, background_color);

	while (true) {
		KnobRotation delta = inputs.get_delta();
		camera.update(delta);

		Screen screen = renderer.renderer_cube();
		outputs.set_screen(screen);

		bool leds[32];
		std::fill(std::begin(leds), std::end(leds), true);

		float min_distance_limit = camera.get_min_distance();
		float distance = abs(camera.get_position() - CUBE_CENTER);
		for (size_t i = 0; i < std::min(distance - min_distance_limit, 32.0f); ++i) {
			leds[i] = false;
		}
		outputs.set_leds(leds);

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
