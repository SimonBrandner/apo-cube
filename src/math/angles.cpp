#include "angles.hpp"

#include <cmath>

float sin_deg(float x) {
	float radian = x * M_PI / 180.0f;
	return std::sin(radian);
}

float cos_deg(float x) {
	float radian = x * M_PI / 180.0f;
	return std::cos(radian);
}

float tan_deg(float x) {
	float radian = x * M_PI / 180.0f;
	return std::tan(radian);
}

