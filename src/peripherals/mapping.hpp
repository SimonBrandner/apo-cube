#ifndef MAPPING_HPP
#define MAPPING_HPP

#include <cstdint>

class PeripheralMemoryMapping {
	private:
		const uint8_t *lcd_address;
		const uint8_t *spi_address;

	public:
		PeripheralMemoryMapping();

		const uint8_t *const get_lcd_address() const;
		const uint8_t *const get_spi_address() const;
};

#endif // MAPPING_HPP
