#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "../graphics/screen.hpp"
#include "./mapping.hpp"

#define LED_COUNT 32

class OutputPeripherals {
	private:
		PeripheralMemoryMapping peripheral_memory_mapping;

	public:
		OutputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);
		void set_leds(bool leds[LED_COUNT]);
		void set_screen(Screen screen);
};

#endif // OUTPUT_HPP
