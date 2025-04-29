#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>

#include "../render/color.hpp"
#include "../render/screen.hpp"

class OutputPeripherals {
	private:
		const std::string fname_leds = "src/periphs_virtual/memory/leds.out";
		const std::string fname_screen =
			"src/periphs_virtual/memory/screen.out";

	public:
		OutputPeripherals();
		bool set_leds(bool leds[32]);
		bool set_screen(Color screen[SCREEN_WIDTH][SCREEN_HEIGHT]);
};

char connect_bools_into_byte(bool bits[8]);

#endif // OUTPUT_HPP
