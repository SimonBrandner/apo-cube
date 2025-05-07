#include <cstdint>
#include <stdint.h>
#include <unistd.h>

#include "../mz_apo/mzapo_parlcd.h"
#include "../mz_apo/mzapo_regs.h"
#include "../render/screen.hpp"
#include "./mapping.hpp"
#include "./output.hpp"

OutputPeripherals::OutputPeripherals(
	PeripheralMemoryMapping peripheral_memory_mapping) {
	this->peripheral_memory_mapping = peripheral_memory_mapping;
	parlcd_hx8357_init(
		(unsigned char *)this->peripheral_memory_mapping.get_lcd_address());
}

void OutputPeripherals::set_leds(bool leds[32]) {
	uint32_t new_register_value = 0;
	for (size_t i = 0; i < 32; ++i) {
		new_register_value |= leds[i];
		if (i != 31) {
			new_register_value <<= 1;
		}
	}

	*(volatile uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
						   SPILED_REG_LED_LINE_o) = new_register_value;
}

void OutputPeripherals::set_screen(Screen screen) {
	uint8_t *base =
		(unsigned char *)this->peripheral_memory_mapping.get_lcd_address();

	parlcd_write_cmd(base, 0x2c);
	for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
		for (size_t x = 0; x < SCREEN_WIDTH; x++) {
			parlcd_write_data(base, screen.at(x, y).to_rgb565());
		}
	}
}
