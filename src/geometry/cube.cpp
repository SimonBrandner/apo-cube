#include "cube.hpp"
#include <iostream>
#include <cmath>
#include <optional>

CubeColorConfig::CubeColorConfig() {}

Cube::Cube(float side_middle[3], float side_length, CubeColorConfig color_config)
	: side_length(side_length)
{
	for (int i = 0; i < 3; ++i) {
		this->middle[i] = side_middle[i];
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

