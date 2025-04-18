#include <iostream>

#include "./matrix.hpp"
#include "./vector.hpp"

int main(int argc, char **argv) {
	float matrix_a_data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix matrix_a = Matrix(matrix_a_data);
	float matrix_b_data[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	Matrix matrix_b = Matrix(matrix_a_data);
	float vector_data[3] = {1, 2, 3};
	Vector vector = Vector(vector_data);

	std::cout << "matrix_a" << std::endl
			  << matrix_a << std::endl
			  << "matrix_b" << std::endl
			  << matrix_b << std::endl
			  << "vector:" << std::endl
			  << vector << std::endl
			  << "matrix_a * vector:" << std::endl
			  << matrix_a * vector << std::endl
			  << "matrix_a * matrix_b" << std::endl
			  << matrix_a * matrix_b << std::endl;
	return 0;
}
