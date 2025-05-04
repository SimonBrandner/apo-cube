#ifndef CUBE_HPP
#define CUBE_HPP

#include <optional>
#include <iostream>
#include <cstddef>

#include "side.hpp"


#include "../render/color.hpp"

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
		std::optional<Side> sides[6 * SIDE_SUBDIVISION * SIDE_SUBDIVISION];

	public:
		Cube(Vector center_point, float edge_length, CubeColorConfig color_config);
		Vector offset_center(float x, float y, float z) const;
		const std::optional<Side>* get_sides() const; // FIXME: Remove optional
};

#endif // CUBE_HPP
