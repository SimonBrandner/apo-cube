#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "./vector.hpp"

class Matrix {
	float data[9];

	public:
		Matrix(float data[9]);

		const float at(const size_t &row, const size_t &column) const;
		const Matrix transpose() const;
		const Vector operator*(const Vector &rhs) const;
		const Matrix operator*(const Matrix &rhs) const;
};

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);

#endif // MATRIX_HPP
