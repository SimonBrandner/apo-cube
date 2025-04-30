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
	this->sides[0].emplace(offset_center(0, 0, 1),  side_length, color_config.front,  'f');
	this->sides[1].emplace(offset_center(0, 0, -1), side_length, color_config.back,   'b');
	this->sides[2].emplace(offset_center(0, 1, 0),  side_length, color_config.top,    't');
	this->sides[3].emplace(offset_center(0, -1, 0), side_length, color_config.bottom, 'd'); // bottom uses 'd'
	this->sides[4].emplace(offset_center(1, 0, 0),  side_length, color_config.right,  'r');
	this->sides[5].emplace(offset_center(-1, 0, 0), side_length, color_config.left,   'l');
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

