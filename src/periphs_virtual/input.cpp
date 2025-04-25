#include "input.hpp"

#include <iostream>
#include <unistd.h>

#define fsizeRGB 3
#define fsizePRESSES 1

InputPeripherals::InputPeripherals() {}

// Returns the difference between the current and previous state of the RGB knobs
InputDelta InputPeripherals::get_delta() {
	FILE *fp = fopen(fname_knobs.c_str(), "rb");
	if (!fp) {
		std::cerr << "Error opening file: " << fname_knobs << std::endl;
		return {0, 0, 0};
	}

	uint32_t rgb_values = 0;
	if (fread(&rgb_values, fsizeRGB, 1, fp) != 1) {
		std::cerr << "Error reading file: " << fname_knobs << std::endl;
		fclose(fp);
		return {0, 0, 0};
	}
	fclose(fp);

	uint8_t red = (rgb_values >> 16) & 0xFF;
	uint8_t green = (rgb_values >> 8) & 0xFF;
	uint8_t blue = rgb_values & 0xFF;

	if (previous_delta_initialized == false) {
		previous_delta = {red, green, blue};
		previous_delta_initialized = true;
		return {0, 0, 0};
	}

	// numbers can overflow, which is good, and we will use it to
	// result in the closest difference of the circle knobs.
	int8_t red_delta = (red - previous_delta.red);
	int8_t green_delta = (green - previous_delta.green);
	int8_t blue_delta = (blue - previous_delta.blue);

	previous_delta = {red, green, blue};
	return {red_delta, green_delta, blue_delta};
}

// Returns the current state of the RGB knobs
InputPresses InputPeripherals::input_presses() {
	FILE *fp = fopen(fname_knob_presses.c_str(), "rb");
	if (fp == NULL) {
		std::cerr << "Error opening file: " << fname_knob_presses << std::endl;
		return {false, false, false, false};
	}
	char presses_values = 0;
	if (fread(&presses_values, fsizePRESSES, 1, fp) != 1) {
		std::cerr << "Error reading file a: " << fname_knobs << std::endl;
		fclose(fp);
		return {false, false, false, false};
	}
	bool red = (presses_values >> 0) & 0x01;
	bool green = (presses_values >> 1) & 0x01;
	bool blue = (presses_values >> 2) & 0x01;
	return {red, green, blue, (red || green || blue)};
}
