#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <cstddef>

#include "side.hpp"

#include "../render/color.hpp"

#define NUMBER_OF_SIDES (6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION)

struct CubeColorConfig {
	public:
		CubeColorConfig();
		Color &at(size_t index);

		Color front;
		Color back;
		Color top;
		Color bottom;
		Color left;
		Color right;
};

class Cube {
	private:
		CubeColorConfig color_config;
		float edge_length;
		float middle[3];
		std::array<Side, NUMBER_OF_SIDES> sides;

	public:
		Cube(Vector center_point, float edge_length, CubeColorConfig color_config);
		Vector offset_center(float x, float y, float z) const;
		std::array<Side, NUMBER_OF_SIDES>& get_sides();
};

#endif // CUBE_HPP
