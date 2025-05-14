#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "./vector.hpp"

/**
 * @brief A 3x3 matrix class for 3D transformations.
 *
 * This class represents a 3x3 matrix and provides methods for matrix
 */
class Matrix {
	private:
		float data[9]; // the data of the matrix

	public:
		/**
		 * @brief The default constructor initializes the matrix to zero.
		 */
		Matrix(float data[9]);

		/**
		 * @brief Returns the value at the specified row and column.
		 *
		 * @param row The row index.
		 * @param column The column index.
		 *
		 * @return The value at the specified row and column.
		 */
		const float at(const size_t &row, const size_t &column) const;

		/**
		 * @brief Returns the transpose of the matrix.
		 *
		 * @return The transposed matrix.
		 */
		const Matrix transpose() const;

		/**
		 * @brief Multiplies the matrix by another matrix.
		 *
		 * @param rhs The right-hand side matrix.
		 *
		 * @return The product of the two matrices.
		 */
		const Matrix operator*(const Matrix &rhs) const;

		/**
		 * @brief Multiplies the matrix by a vector.
		 *
		 * @param rhs The right-hand side vector.
		 *
		 * @return The product of the matrix and the vector.
		 */
		const Vector operator*(const Vector &rhs) const;
};

/**
 * @brief Overloads the output stream operator for the Matrix class.
 *
 * @param stream The output stream.
 * @param matrix The matrix to be printed.
 *
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);

#endif // MATRIX_HPP
