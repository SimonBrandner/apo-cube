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

float tan_deg(float x) {
	float radian = x * M_PI / 180.0f;
	return std::tan(radian);
}

int mod(int a, int b) {
	int r = a % b;
	return r < 0 ? r + b : r;
}

float max(float a, float b) {
	return a > b ? a : b;
}

float min(float a, float b) {
	return a < b ? a : b;
}
