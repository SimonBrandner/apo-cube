#ifndef CUBE_HPP
#define CUBE_HPP

#include <cstdint>

class Color {
  private:
	uint8_t red;
	uint8_t green;
	uint8_t blue;

  public:
	Color(uint8_t red, uint8_t green, uint8_t blue);
};

struct CubeColorConfig {
	CubeColorConfig();

	Color front;
	Color back;
	Color top;
	Color bottom;
	Color left;
	Color right;
};

#endif // CUBE_HPP
