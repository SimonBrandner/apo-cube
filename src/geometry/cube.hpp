#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <cstddef>

#include "face.hpp"

#include "../render/color.hpp"

#define CUBE_CENTER Vector(0, 0, -15)
#define CUBE_EDGE_LENGTH 10

#define NUMBER_OF_FACES 6

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
		std::array<Face, NUMBER_OF_FACES> faces;

	public:
		Cube(Vector center_point, float edge_length, CubeColorConfig color_config);
		Vector offset_center(float x, float y, float z) const;
		std::array<Face, NUMBER_OF_FACES>& get_faces();
};

#endif // CUBE_HPP
