#include "cube.hpp"

#include <iostream>
#include <cmath>
#include <array>
#include <optional>
#include <cstdlib>
#include <iostream>

#include "../render/color.hpp"
#include "../math/vector.hpp"
#include "side.hpp"

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
	case 6:
		return this->screen_background;
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

	struct FaceConfig {
		float dx, dy, dz;
		Color color;
		char id;
	};

	std::array<FaceConfig, 6> faces = {{
		{ 0,  0,  1, color_config.front,  'f'},
		{ 0,  0, -1, color_config.back,   'b'},
		{ 0,  1,  0, color_config.top,    't'},
		{ 0, -1,  0, color_config.bottom, 'd'},
		{ 1,  0,  0, color_config.right,  'r'},
		{-1,  0,  0, color_config.left,   'l'}
	}};

	// create the sides of the cube and subdivides them, for clipping purposes
	long side_index = 0;
	for (const auto& face : faces) {
		for (int i = 0; i < SIDE_SUBDIVISION; ++i) {
			for (int j = 0; j < SIDE_SUBDIVISION; ++j) {
				this->sides[++side_index].emplace(
					offset_center(face.dx, face.dy, face.dz),
					side_length,
					face.color,
					face.id,
					i, j
				);
			}
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
