#include <chrono>
#include <cstdint>
#include <unistd.h>

#include "./geometry/camera.hpp"
#include "./geometry/cube.hpp"
#include "./math/utils.hpp"
#include "./peripherals/input.hpp"
#include "./peripherals/output.hpp"
#include "./peripherals/utils.hpp"
#include "./render/menu.hpp"
#include "./render/renderer.hpp"
#include "./render/screen.hpp"

CubeColorConfig main_menu(PeripheralMemoryMapping peripherals_memory_mapping) {
	CubeColorConfig cube_color_config = CubeColorConfig();
	InputPeripherals input_peripherals =
		InputPeripherals(peripherals_memory_mapping);
	OutputPeripherals output_peripherals =
		OutputPeripherals(peripherals_memory_mapping);

	int8_t selected_face = 0;
	while (true) {
		// Handle inputs
		KnobRotation rotation_delta = input_peripherals.get_rotation_delta();
		KnobPress press_delta = input_peripherals.get_press_delta();

		// Update color
		Color old_color = cube_color_config.at(selected_face);
		Color new_color = Color(old_color.get_red() + rotation_delta.red,
								old_color.get_green() + rotation_delta.green,
								old_color.get_blue() + rotation_delta.blue);
		cube_color_config.at(selected_face) = new_color;

		// Handle presses
		if (press_delta.green) {
			break;
		}
		if (press_delta.red) {
			selected_face -= 1;
		}
		if (press_delta.blue) {
			selected_face += 1;
		}
		selected_face = mod(selected_face, 6);

		// Draw menu and update LCD
		Screen screen = draw_menu(cube_color_config, selected_face);
		output_peripherals.set_screen(screen);
	}

	return cube_color_config;
}

void run(PeripheralMemoryMapping peripherals_memory_mapping,
		 CubeColorConfig cube_color_config) {
	InputPeripherals input_peripherals =
		InputPeripherals(peripherals_memory_mapping);
	OutputPeripherals output_peripherals =
		OutputPeripherals(peripherals_memory_mapping);

	Camera camera = Camera();
	Color background_color = Color(0, 255, 255);
	Renderer renderer = Renderer(camera, cube_color_config, background_color);

	size_t frame_count = 0;
	auto last_log_time = std::chrono::high_resolution_clock::now();

	while (true) {
		KnobPress press_delta = input_peripherals.get_press_delta();
		if (press_delta.green) {
			break;
		}

		KnobRotation rotation_delta = input_peripherals.get_rotation_delta();
		camera.update(rotation_delta);

		Screen screen = renderer.renderer_cube();
		output_peripherals.set_screen(screen);

		++frame_count;
		auto current_time = std::chrono::high_resolution_clock::now();
		if ((current_time - last_log_time).count() >= 1.0f) {
			std::cout << "FPS: " << frame_count << "\n";
			frame_count = 0;
			last_log_time = current_time;
		}
	}
}

int main(int argc, char *argv[]) {
	PeripheralMemoryMapping peripherals_memory_mapping = setup();
	CubeColorConfig cube_color_config = main_menu(peripherals_memory_mapping);
	run(peripherals_memory_mapping, cube_color_config);

	cleanup();
	return 0;
}
