#include "vector.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>

Vector::Vector() { data[0] = data[1] = data[2] = 0.0f; }

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

const float Vector::distance(const Vector &rhs) const {
	return abs(*this - rhs);
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

const double abs(const Vector &vector) {
	double sum = 0;
	for (size_t i = 0; i < 3; ++i) {
		sum += pow(vector.at(i), 2);
	}
	return sqrt(sum);
}

const Vector Vector::operator/(float scalar) const {
	if (scalar == 0.0f) {
		std::cerr << "Division by zero!" << std::endl;
		exit(-1);
	}

	float data[3] = {0};
	for (size_t i = 0; i < 3; ++i) {
		data[i] = this->data[i] / scalar;
	}

	return Vector(data);
}

Vector Vector::normalized() const {
	float len = abs(*this);
	if (len > 0.0f) {
		return *this / len;
	}
	return *this; // return zero vector if length is zero
}

Vector Vector::cross(const Vector &rhs) const {
	float x = this->data[1] * rhs.at(2) - this->data[2] * rhs.at(1);
	float y = this->data[2] * rhs.at(0) - this->data[0] * rhs.at(2);
	float z = this->data[0] * rhs.at(1) - this->data[1] * rhs.at(0);

	return Vector(x, y, z);
}