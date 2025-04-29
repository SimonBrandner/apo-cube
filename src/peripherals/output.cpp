#include <cstdint>
#include <iostream>
#include <stdint.h>
#include <unistd.h>

#include "../mz_apo/mzapo_parlcd.h"
#include "../mz_apo/mzapo_phys.h"
#include "../mz_apo/mzapo_regs.h"
#include "./mapping.hpp"
#include "./output.hpp"

// FIXME: Rremove this testing code
void lcd_do_smt() {
	std::cout << "LCD test:" << std::endl;

	unsigned char *mem_base;
	unsigned char *parlcd_mem_base;
	uint32_t val_line = 5;
	int i, j, k;
	unsigned int c;

	/*
	 * Setup memory mapping which provides access to the peripheral
	 * registers region of RGB LEDs, knobs and line of yellow LEDs.
	 */
	mem_base = (unsigned char *)map_phys_address(SPILED_REG_BASE_PHYS,
												 SPILED_REG_SIZE, 0);

	/* If mapping fails exit with error code */
	if (mem_base == NULL)
		exit(1);

	struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
	for (i = 0; i < 30; i++) {
		*(volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o) = val_line;
		val_line <<= 1;
		printf("LED val 0x%x\n", val_line);
		clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
	}

	parlcd_mem_base = (unsigned char *)map_phys_address(PARLCD_REG_BASE_PHYS,
														PARLCD_REG_SIZE, 0);

	if (parlcd_mem_base == NULL)
		exit(1);

	parlcd_hx8357_init(parlcd_mem_base);

	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	for (i = 0; i < 320; i++) {
		for (j = 0; j < 480; j++) {
			c = 0;
			parlcd_write_data(parlcd_mem_base, c);
		}
	}

	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	for (i = 0; i < 320; i++) {
		for (j = 0; j < 480; j++) {
			c = ((i & 0x1f) << 11) | (j & 0x1f);
			parlcd_write_data(parlcd_mem_base, c);
		}
	}

	loop_delay.tv_sec = 0;
	loop_delay.tv_nsec = 2 * 1000 * 1000;
	for (k = 0; k < 60; k++) {

		parlcd_write_cmd(parlcd_mem_base, 0x2c);
		for (i = 0; i < 320; i++) {
			for (j = 0; j < 480; j++) {
				c = (((i + k) & 0x1f) << 11) | ((j + k) & 0x1f);
				parlcd_write_data(parlcd_mem_base, c);
			}
		}

		clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
	}
}

void led_do_smt() {
	uint32_t val_line = 5;

	std::cout << "LED test:" << std::endl;
	/*
	 * Setup memory mapping which provides access to the peripheral
	 * registers region of RGB LEDs, knobs and line of yellow LEDs.
	 */
	unsigned char *mem_base = (unsigned char *)map_phys_address(
		SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

	/* If mapping fails exit with error code */
	if (mem_base == NULL)
		exit(1);

	for (size_t i = 0; i < 30; i++) {
		*(volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o) = val_line;
		val_line <<= 1;
		printf("LED val 0x%x\n", val_line);
		sleep(1);
	}
}

OutputPeripherals::OutputPeripherals(
	PeripheralMemoryMapping peripheral_memory_mapping) {
	this->peripheral_memory_mapping = peripheral_memory_mapping;
	parlcd_hx8357_init(
		(unsigned char *)this->peripheral_memory_mapping.get_lcd_address());
}
void OutputPeripherals::set_leds(bool leds[32]) {
	uint32_t new_register_value;
	for (size_t i = 0; i < 32; ++i) {
		new_register_value |= leds[i];
		new_register_value <<= 1;
	}

	*(volatile uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
						   SPILED_REG_LED_LINE_o) = new_register_value;
}

void OutputPeripherals::set_screen(Color screen[SCREEN_WIDTH][SCREEN_HEIGHT]) {
	uint8_t *base =
		(unsigned char *)this->peripheral_memory_mapping.get_lcd_address();

	uint32_t data;
	parlcd_write_cmd(base, 0x2c);
	for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
		for (size_t x = 0; x < SCREEN_WIDTH; x++) {
			parlcd_write_data(base, screen[y][x].to_rgb565());
		}
	}
}
