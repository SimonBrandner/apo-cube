#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "../geometry/cube.hpp"
#include "./mapping.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

class OutputPeripherals {
	private:
		PeripheralMemoryMapping peripheral_memory_mapping;

	public:
		OutputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);
		void set_leds(bool leds[32]);
		void set_screen(Color screen[SCREEN_WIDTH][SCREEN_HEIGHT]);
};

#endif // OUTPUT_HPP
