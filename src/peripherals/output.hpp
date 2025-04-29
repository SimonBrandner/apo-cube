#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "../render/screen.hpp"
#include "./mapping.hpp"

class OutputPeripherals {
	private:
		PeripheralMemoryMapping peripheral_memory_mapping;

	public:
		OutputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);
		void set_leds(bool leds[32]);
		void set_screen(Screen screen);
};

#endif // OUTPUT_HPP
