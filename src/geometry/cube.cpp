#include <cstdlib>
#include <iostream>

#include "./cube.hpp"

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
