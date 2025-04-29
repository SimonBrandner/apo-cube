#include <iostream>
#include <unistd.h>

#include "./geometry/camera.hpp"
#include "./geometry/cube.hpp"
#include "./math/matrix.hpp"
#include "./math/vector.hpp"
#include "./peripherals/input.hpp"
#include "./peripherals/utils.hpp"

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

	while (true) {
		InputDelta input_delta = input_peripherals.get_delta();
		KnobPressState input_pressed = input_peripherals.get_knob_press_state();
		cube_color_config.front =
			Color(input_delta.red, input_delta.green, input_delta.blue);

		if (input_pressed.red || input_pressed.blue || input_pressed.green) {
			break;
		}
	}

	return cube_color_config;
}

void run(PeripheralMemoryMapping peripherals_memory_mapping,
		 CubeColorConfig cube_color_config) {
	InputPeripherals input_peripherals =
		InputPeripherals(peripherals_memory_mapping);
	Camera camera = Camera();

	while (true) {
		InputDelta input_delta = input_peripherals.get_delta();
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
