#include <iostream>
#include <unistd.h>

#include "./geometry/camera.hpp"
#include "./geometry/cube.hpp"
#include "./math/matrix.hpp"
#include "./math/vector.hpp"
#include "./peripherals/input.hpp"

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

CubeColorConfig main_menu() {
	CubeColorConfig cube_color_config;
	InputPeripherals input_peripherals = InputPeripherals();

	while (true) {
		InputDelta input_delta = input_peripherals.get_delta();
		cube_color_config.front =
			Color(input_delta.red_knob_delta, input_delta.green_knob_delta,
				  input_delta.blue_knob_delta);

		if (input_delta.knob_pressed) {
			break;
		}
	}

	return cube_color_config;
}

void run(CubeColorConfig cube_color_config) {
	InputPeripherals input_peripherals = InputPeripherals();
	Camera camera = Camera();

	while (true) {
		InputDelta input_delta = input_peripherals.get_delta();
		camera.update(input_delta);
	}
}

int main(int argc, char *argv[]) {
	CubeColorConfig cube_color_config = main_menu();
	run(cube_color_config);

	return 0;
}
