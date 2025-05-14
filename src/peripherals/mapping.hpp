#ifndef MAPPING_HPP
#define MAPPING_HPP

#include <cstdint>

/**
 * @brief The PeripheralMemoryMapping class is used to map the memory addresses
 * of the peripherals (LCD and SPI) to the corresponding hardware addresses.
 */
class PeripheralMemoryMapping {
	private:
		const uint8_t *lcd_address; // LCD memory address
		const uint8_t *spi_address; // SPI memory address

	public:
		/**
		 * @brief Constructor for the PeripheralMemoryMapping class.
		 * Initializes the memory addresses of the peripherals.
		 */
		PeripheralMemoryMapping();

		/**
		 * @brief Getter for the LCD memory address.
		 *
		 * @return const uint8_t* Pointer to the LCD memory address.
		 */
		const uint8_t *const get_lcd_address() const;

		/**
		 * @brief Getter for the SPI memory address.
		 *
		 * @return const uint8_t* Pointer to the SPI memory address.
		 */
		const uint8_t *const get_spi_address() const;
};

#endif // MAPPING_HPP
