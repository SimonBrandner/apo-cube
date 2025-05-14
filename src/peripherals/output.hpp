#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "../graphics/screen.hpp"
#include "./mapping.hpp"

#define LED_COUNT 32 // Number of LEDs in the MZ_APO LED strip

class OutputPeripherals {
	private:
		PeripheralMemoryMapping
			peripheral_memory_mapping; // Memory mapping for the peripherals

	public:
		/**
		 * @brief Constructor for the OutputPeripherals class.
		 * Initializes the peripheral memory mapping.
		 */
		OutputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);

		/**
		 * @brief Setter for the 32 LEDs.
		 */
		void set_leds(bool leds[LED_COUNT]);

		/**
		 * @brief Setter for the Screen buffer.
		 */
		void set_screen(Screen screen);
};

#endif // OUTPUT_HPP
