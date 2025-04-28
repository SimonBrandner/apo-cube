#include "utils.hpp"

#include <cmath>

float sin_deg(float x) {
	float radian = x * M_PI / 180.0f;
	return std::sin(radian);
}

float cos_deg(float x) {
	float radian = x * M_PI / 180.0f;
	return std::cos(radian);
}
