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

float sqrt(float x, int n) {
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return x;
	}
	float result = x;
	for (int i = 0; i < n - 1; ++i) {
		result = std::sqrt(result);
	}
	return result;
}

float max(float a, float b) {
	return a > b ? a : b;
}

float min(float a, float b) {
	return a < b ? a : b;
}
