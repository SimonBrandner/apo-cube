#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "../geometry/cube.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

class OutputPeripherals {
	public:
		OutputPeripherals();
		bool set_leds(bool leds[32]);
		bool set_screen(Color screen[SCREEN_WIDTH][SCREEN_HEIGHT]);
};

#endif // OUTPUT_HPP
