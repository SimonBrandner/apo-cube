#include "matrix.hpp"

Matrix::Matrix(float data[9]) {
	for (size_t i = 0; i < 9; ++i) {
		this->data[i] = data[i];
	}
}

const float Matrix::at(const size_t &row, const size_t &column) const {
	if (row >= 3 || column >= 3) {
		// panic
	}

	return this->data[row * 3 + column];
}

const Matrix Matrix::transpose() const {
	float data[9];

	for (size_t column = 0; column < 3; ++column) {
		for (size_t row = 0; row < 3; ++row) {
			data[column * 3 + row] = this->at(row, column);
		}
	}

	return Matrix(data);
}

const Vector Matrix::operator*(const Vector &rhs) const {
	float data[3] = {0};

	for (size_t row = 0; row < 3; ++row) {
		for (size_t column = 0; column < 3; ++column) {
			data[row] += this->at(row, column) * rhs.at(column);
		}
	}

	return Vector(data);
}

const Matrix Matrix::operator*(const Matrix &rhs) const {
	Matrix transposed = rhs.transpose();
	float data[9] = {0};

	// Multiply element-wise
	for (size_t row = 0; row < 3; ++row) {
		for (size_t column = 0; column < 3; ++column) {
			for (size_t i = 0; i < 3; ++i) {
				data[row * 3 + column] +=
					this->at(row, i) * transposed.at(column, i);
			}
		}
	}

	return Matrix(data);
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
	stream << "(";
	for (size_t row = 0; row < 3; ++row) {
		stream << "(";
		for (size_t column = 0; column < 3; ++column) {
			stream << matrix.at(row, column);
			if (column < 2) {
				stream << ", ";
			}
		}
		stream << ")";
		if (row < 2) {
			stream << ", ";
		}
	}
	stream << ")";

	return stream;
}
