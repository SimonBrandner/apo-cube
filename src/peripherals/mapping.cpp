#include "./mapping.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "../mz_apo/mzapo_phys.h"
#include "../mz_apo/mzapo_regs.h"


PeripheralMemoryMapping::PeripheralMemoryMapping() {
	this->spi_address =
		(uint8_t *)map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
	this->lcd_address =
		(uint8_t *)map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

	if (this->spi_address == NULL || this->lcd_address == NULL) {
		std::cerr << "Failed to map physical memory - not much we can do!"
				  << std::endl;
		exit(-1);
	}
}

const uint8_t *const PeripheralMemoryMapping::get_lcd_address() const {
	return this->lcd_address;
}

const uint8_t *const PeripheralMemoryMapping::get_spi_address() const {
	return this->spi_address;
}
