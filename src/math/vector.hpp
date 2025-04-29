#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <ostream>

class Vector {
	private:
		float data[3];

	public:
		Vector(float x, float y, float z);
		Vector(float data[3]);

		const Vector operator+(const Vector &rhs) const;
		const Vector operator-(const Vector &rhs) const;
		const Vector operator*(const Vector &rhs) const;

		const float at(size_t index) const;
		const float get_x() const;
		const float get_y() const;
		const float get_z() const;
};

std::ostream &operator<<(std::ostream &stream, const Vector &vector);

#endif // VECTOR_HPP
