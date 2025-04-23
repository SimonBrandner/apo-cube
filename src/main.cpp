#include <iostream>

#include "./math/matrix.hpp"
#include "./math/vector.hpp"
#include "./serialize_lock.h"

int main(int argc, char *argv[]) {
	/* Serialize execution of applications */

	/* Try to acquire lock the first */
	if (serialize_lock(1) <= 0) {
		printf("System is occupied\n");

		if (1) {
			printf("Waitting\n");
			/* Wait till application holding lock releases it or exits */
			serialize_lock(0);
		}
	}

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

	serialize_unlock();

	return 0;
}
