#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <ostream>

/**
 * @brief A 3D vector class.
 *
 * This class represents a 3D vector and provides various operations such as
 * addition, subtraction, multiplication, division, normalization, and
 * cross-product.
 */
class Vector {
	private:
		float data[3]; // Array to store the vector components (x, y, z)

	public:
		/**
		 * @brief The default constructor initializes the vector to (0, 0, 0).
		 */
		Vector();

		/**
		 * @brief Constructor initializes the vector with given x, y, z values.
		 * @param x The x component of the vector.
		 * @param y The y component of the vector.
		 * @param z The z component of the vector.
		 */
		Vector(float x, float y, float z);

		/**
		 * @brief Constructor initializes the vector with the given array of
		 * values.
		 * @param data Array containing the x, y, z components of the vector.
		 */
		Vector(float data[3]);

		/**
		 * @brief Overloads the + operator for vector addition.
		 * @return A new Vector that is the sum of this vector and the given
		 * vector.
		 */
		const Vector operator+(const Vector &rhs) const;

		/**
		 * @brief Overloads the - operator for vector subtraction.
		 * @return A new Vector that is the difference of this vector and the
		 * given vector.
		 */
		const Vector operator-(const Vector &rhs) const;

		/**
		 * @brief Overloads the * operator for vector multiplication.
		 * @return A new Vector that is the product of this vector and the given
		 * vector.
		 */
		const Vector operator*(const Vector &rhs) const;

		/**
		 * @brief Overloads the / operator for scalar division.
		 * @return A new Vector that is the quotient of this vector and the
		 * given scalar.
		 */
		const Vector operator/(float scalar) const;

		/**
		 * @brief Normalizes the vector.
		 *
		 * @return A new Vector that is the normalized version of this vector.
		 */
		Vector normalized() const;

		/**
		 * @brief Computes the cross-product of this vector and another vector.
		 *
		 * @param rhs The other vector.
		 * @return A new Vector that is the cross-product of this vector and the
		 * given vector.
		 */
		Vector cross(const Vector &rhs) const;

		/**
		 * @brief Calculates the distance between this vector and another
		 * vector.
		 *
		 * @param rhs The other vector.
		 * @return The distance between this vector and the given vector.
		 */
		const float distance(const Vector &rhs) const;

		/**
		 * @brief Gets the value at the specified index.
		 *
		 * @param index The index of the component.
		 * @return The value of the component at the specified index.
		 */
		const float at(size_t index) const;

		/**
		 * @brief Gets the x component of the vector.
		 *
		 * @return The x component of the vector.
		 */
		const float get_x() const;

		/**
		 * @brief Gets the y component of the vector.
		 *
		 * @return The y component of the vector.
		 */
		const float get_y() const;

		/**
		 * @brief Gets the z component of the vector.
		 *
		 * @return The z component of the vector.
		 */
		const float get_z() const;
};

/**
 * @brief Overloads the << operator for printing the vector.
 *
 * @param stream The output stream.
 * @param vector The vector to be printed.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Vector &vector);

/**
 * @brief Computes the absolute value of a vector.
 *
 * @param vector The vector to compute the absolute value for.
 * @return The absolute value of the vector.
 */
const double abs(const Vector &vector);

#endif // VECTOR_HPP
