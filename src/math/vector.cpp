#include <cstddef>
#include <ostream>
#include <iostream>

#include "vector.hpp"

Vector::Vector(float x, float y, float z) {
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}

Vector::Vector(float data[3]) {
	for (size_t i = 0; i < 3; ++i) {
		this->data[i] = data[i];
	}
}

const float Vector::at(size_t index) const { return this->data[index]; }

const float Vector::get_x() const { return this->data[0]; }
const float Vector::get_y() const { return this->data[1]; }
const float Vector::get_z() const { return this->data[2]; }

std::ostream &operator<<(std::ostream &stream, const Vector &vector) {
	stream << "(";
	for (size_t i = 0; i < 3; ++i) {
		stream << vector.at(i);
		if (i < 2) {
			stream << ", ";
		}
	}
	stream << ")";

	return stream;
}

const Vector Vector::operator+(const Vector &rhs) const {
	float data[3] = {0};

	for (size_t i = 0; i < 3; ++i) {
		data[i] = this->data[i] + rhs.at(i);
	}

	return Vector(data);
}

const Vector Vector::operator-(const Vector &rhs) const {
	float data[3] = {0};

	for (size_t i = 0; i < 3; ++i) {
		data[i] = this->data[i] - rhs.at(i);
	}

	return Vector(data);
}

const Vector Vector::operator*(const Vector &rhs) const {
	float data[3] = {0};

	for (size_t i = 0; i < 3; ++i) {
		data[i] = this->data[i] * rhs.at(i);
	}

	return Vector(data);
}
