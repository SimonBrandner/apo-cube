#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <cstdint>

#define screen_width 480
#define screen_height 320

class OutputPeripherals {
public:
	OutputPeripherals();
	void set_leds(bool leds[32]); // may return bool in the future?
	void set_screen(uint16_t screen[screen_width][screen_height]);
};

#endif //OUTPUT_HPP
