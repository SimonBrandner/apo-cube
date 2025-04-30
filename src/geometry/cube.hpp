#ifndef CUBE_HPP
#define CUBE_HPP

#include <cstddef>

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
		float side_length;
		float middle[3];

	public:
		Cube();
		Cube(float side_middle[3], float side_length);
		void set_color_config(CubeColorConfig);
};

#endif // CUBE_HPP
