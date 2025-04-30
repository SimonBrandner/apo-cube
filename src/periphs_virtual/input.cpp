#include "input.hpp"

#include <iostream>
#include <fstream>
#include <unistd.h>

#define FSIZERGB 3
#define FSIZEPRESSES 1

InputPeripherals::InputPeripherals() {}

// Returns the difference between the current and previous state of the RGB knobs
KnobRotation InputPeripherals::get_delta() {
	std::ifstream file(fname_knobs, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << fname_knobs << std::endl;
		//exit(-1); // do not exit, because the file can be locked by vir. periph.
		return {0, 0, 0}; // just return delta 0
	}

	// stores the raw bytes of the RGB knobs
	char buffer[FSIZERGB];
	file.read(buffer, FSIZERGB);
	if (!file) {
		std::cerr << "Error reading file: " << fname_knobs << std::endl;
		//exit(-1); // do not exit, because the file can be locked by vir. periph.
		return {0, 0, 0}; // just return delta 0
	}

	// converts the raw bytes to a 32-bit integer
	uint32_t rgb_values = 0;
	for (size_t i = 0; i < FSIZERGB; ++i) {
		rgb_values = rgb_values * 256 + (buffer[i] & 0xFF);
	}

	// apply bitwise operations to extract the RGB values
	uint8_t red = (rgb_values >> 16) & 0xFF;
	uint8_t green = (rgb_values >> 8) & 0xFF;
	uint8_t blue = rgb_values & 0xFF;

	if (!previous_delta.has_value()) {
		previous_delta = {red, green, blue};
		return {0, 0, 0};
	}

	// numbers can overflow, which is good, and we will use it to store the
	// result in the closest difference of the circle knobs.
	const InputNow& prev = previous_delta.value();
	int8_t red_delta = (red - prev.red);
	int8_t green_delta = (green - prev.green);
	int8_t blue_delta = (blue - prev.blue);

	previous_delta = {red, green, blue};
	return {red_delta, green_delta, blue_delta};
}

// Returns the current state of the RGB knobs
KnobPress InputPeripherals::get_knob_press_state() {
	std::ifstream file(fname_knob_presses, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << fname_knob_presses << std::endl;
		return {false, false, false};
	}

	char presses_values = 0;
	file.read(&presses_values, FSIZEPRESSES);
	if (!file) {
		std::cerr << "Error reading file: " << fname_knob_presses << std::endl;
		return {false, false, false};
	}

	bool red = (presses_values >> 0) & 0x01;
	bool green = (presses_values >> 1) & 0x01;
	bool blue = (presses_values >> 2) & 0x01;
	return {red, green, blue};
}
