#include <cstddef>
#include <iostream>
#include <unistd.h>

#include "./math/matrix.hpp"
#include "./math/vector.hpp"
#include "./serialize_lock.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

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

int main(int argc, char *argv[]) {
	/* Serialize execution of applications */

	/* Try to acquire lock the first */
	if (serialize_lock(1) <= 0) {
		printf("System is occupied\n");

		if (1) {
			printf("Waitting\n");
			/* Wait till application holding lock releases it or exits */
			serialize_lock(0);
		}
	}

	float matrix_a_data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix matrix_a = Matrix(matrix_a_data);
	float matrix_b_data[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	Matrix matrix_b = Matrix(matrix_b_data);
	float vector_data[3] = {1, 2, 3};
	Vector vector = Vector(vector_data);

	std::cout << "Testing math" << std::endl
			  << "matrix_a" << std::endl
			  << matrix_a << std::endl
			  << "matrix_b" << std::endl
			  << matrix_b << std::endl
			  << "vector:" << std::endl
			  << vector << std::endl
			  << "matrix_a * vector:" << std::endl
			  << matrix_a * vector << std::endl
			  << "matrix_a * matrix_b" << std::endl
			  << matrix_a * matrix_b << std::endl;

	lcd_do_smt();
	// led_do_smt();

	serialize_unlock();

	return 0;
}
