#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <cstdint>
#include <string>

#define screen_width 480
#define screen_height 320

class OutputPeripherals {
private:
	bool previous_delta_initialized = false;
	std::string fname_leds = "src/periphs_virtual/memory/leds.out";
	std::string fname_screen = "src/periphs_virtual/memory/screen.out";

public:
	OutputPeripherals();
	void set_leds(bool leds[32]);
	void set_screen(uint16_t screen[screen_width][screen_height]);
};

char connect_bools_into_byte(bool bits[8]);

#endif //OUTPUT_HPP
