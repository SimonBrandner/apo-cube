#include <cstdint>
#include <iostream>
#include <unistd.h>

#include "./geometry/camera.hpp"
#include "./geometry/cube.hpp"
#include "./math/matrix.hpp"
#include "./math/utils.hpp"
#include "./math/vector.hpp"
#include "./peripherals/input.hpp"
#include "./peripherals/output.hpp"
#include "./peripherals/utils.hpp"
#include "./render/menu.hpp"
#include "./render/screen.hpp"

void math_do_smt() {
	float matrix_a_data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix matrix_a = Matrix(matrix_a_data);
	float matrix_b_data[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	Matrix matrix_b = Matrix(matrix_b_data);
	float vector_data[3] = {1, 2, 3};
	Vector vector = Vector(vector_data);

	std::cout << "Testing math" << std::endl
			  << "matrix_a" << std::endl
			  << matrix_a << std::endl
			  << "matrix_b" << std::endl
			  << matrix_b << std::endl
			  << "vector:" << std::endl
			  << vector << std::endl
			  << "matrix_a * vector:" << std::endl
			  << matrix_a * vector << std::endl
			  << "matrix_a * matrix_b" << std::endl
			  << matrix_a * matrix_b << std::endl;
}

CubeColorConfig main_menu(PeripheralMemoryMapping peripherals_memory_mapping) {
	CubeColorConfig cube_color_config = CubeColorConfig();
	InputPeripherals input_peripherals =
		InputPeripherals(peripherals_memory_mapping);
	OutputPeripherals output_peripherals =
		OutputPeripherals(peripherals_memory_mapping);

	int8_t selected_face = 0;
	while (true) {
		// Handle inputs
		InputDelta input_delta = input_peripherals.get_delta();
		KnobPressState input_pressed = input_peripherals.get_knob_press_state();
		cube_color_config.at(selected_face) =
			Color(input_delta.red, input_delta.green, input_delta.blue);

		if (input_pressed.green) {
			break;
		}
		if (input_pressed.red) {
			selected_face -= 1;
		}
		if (input_pressed.blue) {
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
	Camera camera = Camera();

	while (true) {
		KnobPressState input_pressed = input_peripherals.get_knob_press_state();
		InputDelta input_delta = input_peripherals.get_delta();

		if (input_pressed.green) {
			break;
		}

		camera.update(input_delta);
	}
}

int main(int argc, char *argv[]) {
	PeripheralMemoryMapping peripherals_memory_mapping = setup();
	CubeColorConfig cube_color_config = main_menu(peripherals_memory_mapping);
	run(peripherals_memory_mapping, cube_color_config);

	cleanup();
	return 0;
}
