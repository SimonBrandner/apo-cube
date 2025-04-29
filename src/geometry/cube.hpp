#ifndef CUBE_HPP
#define CUBE_HPP

#include <cstdint>
#include "side.hpp"
#include "../render/color.hpp"

struct CubeColorConfig {
	CubeColorConfig();

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
		float side_length;
		float middle[3];

	public:
		Cube();
		Cube(float side_middle[3], float side_length);
		void set_color_config(CubeColorConfig);
};

#endif // CUBE_HPP
