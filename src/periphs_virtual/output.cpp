#include "output.hpp"

#include <fstream>
#include <iostream>

#define FSIZELEDS 4
#define BYTE 8

OutputPeripherals::OutputPeripherals() {}

// Sets the 32 LEDs file to 32 * 0/1
bool OutputPeripherals::set_leds(bool leds[FSIZELEDS*BYTE]) {
	std::ofstream file(fname_leds, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file " << fname_leds << std::endl;
		return false;
	}

	char bytes[FSIZELEDS] = {0};
	for (int i = 0; i < FSIZELEDS; ++i) {
		bytes[i] = connect_bools_into_byte(leds + (i * BYTE));
	}

	file.write(bytes, FSIZELEDS);
	file.close();
	return true;
}

// Sets the screen file to the 2D array of RGB565 values
bool OutputPeripherals::set_screen(Color screen[SCREEN_WIDTH][SCREEN_HEIGHT]) {
	std::ofstream file(fname_screen, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file " << fname_screen << std::endl;
		return false;
	}

	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			uint16_t rgb565 = screen[x][y].to_rgb565(); // convert from RGB888 to RGB565
			file.write((const char*)&rgb565, sizeof(uint16_t)); // write 2 bytes (RGB565)
		}
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
