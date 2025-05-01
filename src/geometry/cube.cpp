#include "cube.hpp"
#include <iostream>
#include <cmath>
#include <optional>
#include <cstdlib>
#include <iostream>

CubeColorConfig::CubeColorConfig() {}

Color &CubeColorConfig::at(size_t index) {
	switch (index) {
	case 0:
		return this->front;
	case 1:
		return this->back;
	case 2:
		return this->left;
	case 3:
		return this->right;
	case 4:
		return this->top;
	case 5:
		return this->bottom;
	}

	std::cerr << "Unknown face: " << index << std::endl;
	exit(-1);
}

Cube::Cube(Vector side_middle, float side_length, CubeColorConfig color_config)
	: side_length(side_length)
{
	for (int i = 0; i < 3; ++i) {
		this->middle[i] = side_middle.at(i);
	}

	long side_index = 0;

	for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
		for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
			this->sides[++side_index].emplace(offset_center(0, 0, 1),  side_length, color_config.front,  'f', i, j);
		}
	}
	for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
		for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
			this->sides[++side_index].emplace(offset_center(0, 0, -1), side_length, color_config.back,   'b', i, j);
		}
	}
	for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
		for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
			this->sides[++side_index].emplace(offset_center(0, 1, 0),  side_length, color_config.top,    't', i, j);
		}
	}
	for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
		for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
			this->sides[++side_index].emplace(offset_center(0, -1, 0), side_length, color_config.bottom, 'd', i, j);
		}
	}
	for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
		for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
			this->sides[++side_index].emplace(offset_center(1, 0, 0),  side_length, color_config.right,  'r', i, j);
		}
	}
	for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
		for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
			this->sides[++side_index].emplace(offset_center(-1, 0, 0), side_length, color_config.left,   'l', i, j);
		}
	}
}

Vector Cube::offset_center(float x, float y, float z) const {
	return Vector(
		middle[0] + x * side_length / 2,
		middle[1] + y * side_length / 2,
		middle[2] + z * side_length / 2
	);
}

const std::optional<Side>* Cube::get_sides() const {
	return this->sides;
}

