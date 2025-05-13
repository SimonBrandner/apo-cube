#include "../peripherals/output.hpp"

#include <fstream>
#include <iostream>

#define FSIZELEDS 4
#define BYTE 8

#define FILE_NAME_LEDS "scripts/virtual_peripherals/memory/leds.out"
#define FILE_NAME_SCREEN "scripts/virtual_peripherals/memory/screen.out"

char connect_bools_into_byte(bool bits[BYTE]) {
	char res = 0;
	for (int i = 0; i < BYTE; ++i) {
		res |= (bits[i] << i);
	}
	return res;
}

OutputPeripherals::OutputPeripherals(PeripheralMemoryMapping _) {}

// sets the 32 LEDs file to 32 * 0/1
void OutputPeripherals::set_leds(bool leds[FSIZELEDS * BYTE]) {
	std::ofstream file(FILE_NAME_LEDS, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file " << FILE_NAME_LEDS << std::endl;
		exit(-1);
	}

	char bytes[FSIZELEDS] = {0};
	for (int i = 0; i < FSIZELEDS; ++i) {
		bytes[i] = connect_bools_into_byte(leds + (i * BYTE));
	}

	file.write(bytes, FSIZELEDS);
	file.close();
}

// sets the screen file to the 2D array of RGB565 values
void OutputPeripherals::set_screen(Screen screen) {
	std::ofstream file(FILE_NAME_SCREEN, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file " << FILE_NAME_SCREEN << std::endl;
		exit(-1);
	}

	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			uint16_t rgb565 =
				screen.at(x, y).to_rgb565(); // convert from RGB888 to RGB565
			file.write((const char *)&rgb565,
					   sizeof(uint16_t)); // write 2 bytes (RGB565)
		}
	}

	file.close();
}
