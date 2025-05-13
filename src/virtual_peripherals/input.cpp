#include "../peripherals/input.hpp"

#include <fstream>
#include <iostream>

#define FSIZERGB 3
#define FSIZEPRESSES 1

#define FILE_NAME_ROTATION "scripts/virtual_peripherals/memory/knobs.in"
#define FILE_NAME_PRESSES "scripts/virtual_peripherals/memory/knob_presses.in"

InputPeripherals::InputPeripherals(PeripheralMemoryMapping _) {}

// returns the diff between the current and previous state of the RGB knobs
KnobRotation InputPeripherals::get_rotation_delta() {
	std::ifstream file(FILE_NAME_ROTATION, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << FILE_NAME_ROTATION << std::endl;
		// do not exit, because the file can be locked by vir. periph.
		return {0, 0, 0}; // just return delta 0
	}

	// stores the raw bytes of the RGB knobs
	char buffer[FSIZERGB];
	file.read(buffer, FSIZERGB);
	if (!file) {
		std::cerr << "Error reading file: " << FILE_NAME_ROTATION << std::endl;
		// do not exit, because the file can be locked by vir. periph.
		return {0, 0, 0}; // just return delta 0
	}

	// converts the raw bytes to a 32-bit integer
	uint32_t knobs = 0;
	for (size_t i = 0; i < FSIZERGB; ++i) {
		knobs = knobs * 256 + (buffer[i] & 0xFF);
	}

	KnobRotation new_state = {0};
	new_state.blue = ((knobs >> 0) & 0xFF);
	new_state.green = ((knobs >> 8) & 0xFF);
	new_state.red = ((knobs >> 16) & 0xFF);

	KnobRotation delta = {0};
	delta.blue = new_state.blue - this->rotation_state.blue;
	delta.green = new_state.green - this->rotation_state.green;
	delta.red = new_state.red - this->rotation_state.red;

	this->rotation_state = new_state;

	// avoid using the old state of the knobs
	if (!this->first_read) {
		this->first_read = true;
		return {0, 0, 0};
	}

	return delta;
}

// returns the current state of the RGB knobs
KnobPress InputPeripherals::get_press_delta() {
	std::ifstream file(FILE_NAME_PRESSES, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << FILE_NAME_PRESSES << std::endl;
		return {false, false, false};
	}

	char knobs = 0;
	file.read(&knobs, FSIZEPRESSES);
	if (!file) {
		std::cerr << "Error reading file: " << FILE_NAME_PRESSES << std::endl;
		return {false, false, false};
	}

	KnobPress new_state;
	new_state.red = (knobs >> 0) & 0x01;
	new_state.green = (knobs >> 1) & 0x01;
	new_state.blue = (knobs >> 2) & 0x01;

	KnobPress delta;
	delta.blue = !new_state.blue && this->press_state.blue;
	delta.green = !new_state.green && this->press_state.green;
	delta.red = !new_state.red && this->press_state.red;

	this->press_state = new_state;

	return delta;
}
