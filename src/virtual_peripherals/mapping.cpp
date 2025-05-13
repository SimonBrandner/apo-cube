#include "../peripherals/mapping.hpp"

#include <cstdint>
#include <cstdlib>
#include <iostream>

PeripheralMemoryMapping::PeripheralMemoryMapping() {}

const uint8_t *const PeripheralMemoryMapping::get_lcd_address() const {
	std::cerr << "get_lcd_address caled on virtual PeripheralMemoryMapping"
			  << std::endl;
	exit(-1);
}

const uint8_t *const PeripheralMemoryMapping::get_spi_address() const {
	std::cerr << "get_spi_address caled on virtual PeripheralMemoryMapping"
			  << std::endl;
	exit(-1);
}
