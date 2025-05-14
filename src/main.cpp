#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "./geometry/camera.hpp"
#include "./geometry/cube.hpp"
#include "./graphics/menu.hpp"
#include "./graphics/screen.hpp"
#include "./math/utils.hpp"
#include "./peripherals/input.hpp"
#include "./peripherals/output.hpp"
#include "./peripherals/utils.hpp"
#include "./render/renderer.hpp"

// coefficient for increasing the range of the LEDs
#define DISTANCE_LED_COEFFICIENT 0.25f

/**
* @brief This function manages the rendering and interaction with the menu.
* @return true if the exit button is pressed, false for entering the render mode
*/
bool menu(PeripheralMemoryMapping peripherals_memory_mapping,
		  CubeColorConfig &cube_color_config) {
	InputPeripherals input_peripherals =
		InputPeripherals(peripherals_memory_mapping);
	OutputPeripherals output_peripherals =
		OutputPeripherals(peripherals_memory_mapping);

	bool exit;
	int8_t selected_button = 0;
	while (true) {
		// Handle inputs
		KnobRotation rotation_delta = input_peripherals.get_rotation_delta();
		KnobPress press_delta = input_peripherals.get_press_delta();

		// Update color
		if (selected_button >= 0 && selected_button < 6) {
			Color old_color = cube_color_config.at(selected_button);
			Color new_color =
				Color(old_color.get_red() + rotation_delta.red,
					  old_color.get_green() + rotation_delta.green,
					  old_color.get_blue() + rotation_delta.blue);
			cube_color_config.at(selected_button) = new_color;
		}

		// Handle presses
		if (press_delta.green) {
			if (selected_button == START_BUTTON_INDEX) {
				exit = false;
				break;
			} else if (selected_button == EXIT_BUTTON_INDEX) {
				exit = true;
				break;
			}
		}
		if (press_delta.red) {
			selected_button -= 1;
		}
		if (press_delta.blue) {
			selected_button += 1;
		}
		selected_button = mod(selected_button, BUTTON_COUNT);

		// Draw menu and update LCD
		Screen screen = draw_menu(cube_color_config, selected_button);
		output_peripherals.set_screen(screen);
	}

	if (exit) {
		Screen screen = draw_exit_screen();
		output_peripherals.set_screen(screen);
	}

	return exit;
}

/**
 * @brief This function manages the rendering process of the cube and the
 * input of the knobs and output of the screen and LEDs.
 * It also shows how many frames per second are being rendered.
 */
void run(PeripheralMemoryMapping peripherals_memory_mapping,
		 CubeColorConfig cube_color_config) {
	InputPeripherals input_peripherals =
		InputPeripherals(peripherals_memory_mapping);
	OutputPeripherals output_peripherals =
		OutputPeripherals(peripherals_memory_mapping);

	Camera camera = Camera();
	Color background_color = Color::Black();
	Renderer renderer = Renderer(camera, cube_color_config, background_color);

	size_t frame_count = 0;
	auto last_log_time = std::chrono::high_resolution_clock::now();

	while (true) {
		KnobPress press_delta = input_peripherals.get_press_delta();
		if (press_delta.red) {
			break;
		}

		KnobRotation rotation_delta = input_peripherals.get_rotation_delta();
		camera.update(rotation_delta);

		Screen screen = renderer.renderer_cube();
		output_peripherals.set_screen(screen);

		bool leds[LED_COUNT];
		std::fill(std::begin(leds), std::end(leds), true);

		float min_distance_limit = camera.get_min_distance();
		// We subtract 0.01f to fix a rounding error where rotating around the
		// cube would cause the left-most LED to blink
		float distance = abs(camera.get_position() - CUBE_CENTER) - 0.01f;
		for (size_t i = 0; i < std::min((distance - min_distance_limit) *
											DISTANCE_LED_COEFFICIENT,
										LED_COUNT * 1.0f);
			 ++i) {
			leds[i] = false;
		}
		output_peripherals.set_leds(leds);

		++frame_count;
		auto current_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(
			current_time - last_log_time);
		if (elapsed.count() >= 1.0f) {
			std::cout << "FPS: " << frame_count << "\n";
			frame_count = 0;
			last_log_time = current_time;
		}
	}
}

/**
 * @brief This function manages the scenes: Menu and Cube rendering.
 */
int main(int argc, char *argv[]) {
	PeripheralMemoryMapping peripherals_memory_mapping = setup();

	CubeColorConfig cube_color_config;
	while (true) {
		if (menu(peripherals_memory_mapping, cube_color_config)) {
			break;
		}
		run(peripherals_memory_mapping, cube_color_config);
	}

	cleanup();
	return 0;
}
