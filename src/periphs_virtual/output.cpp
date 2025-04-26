#include "output.hpp"

#include <fstream>
#include <iostream>

#define fsizeLEDs 4
#define BYTE 8

OutputPeripherals::OutputPeripherals() {}

// Sets the 32 LEDs file to 32 * 0/1
bool OutputPeripherals::set_leds(bool leds[fsizeLEDs*BYTE]) {
	std::ofstream file(fname_leds, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file " << fname_leds << std::endl;
		return false;
	}

	char bytes[fsizeLEDs] = {0};
	for (int i = 0; i < fsizeLEDs; ++i) {
		bytes[i] = connect_bools_into_byte(leds + (i * BYTE));
	}

	file.write(bytes, fsizeLEDs);
	file.close();
	return true;
}

// Sets the screen file to the 2D array of RGB565 values
bool OutputPeripherals::set_screen(uint16_t screen[screen_width][screen_height]) {
	std::ofstream file(fname_screen, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file " << fname_screen << std::endl;
		return false;
	}

	for (int y = 0; y < screen_height; ++y) {
		file.write((const char*)(&screen[y][0]), screen_width * sizeof(int16_t));
	}

	file.close();
	return true;
}

char connect_bools_into_byte(bool bits[BYTE]) {
	char res = 0;
	for (int i = 0; i < BYTE; ++i) {
		res |= (bits[i] << i);
	}
	return res;
}
