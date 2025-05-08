#ifndef OUTPUTV_HPP
#define OUTPUTV_HPP

#include <string>

#include "../render/screen.hpp"

class OutputPeripherals {
	private:
		const std::string fname_leds = "src/periphs_virtual/memory/leds.out";
		const std::string fname_screen =
			"src/periphs_virtual/memory/screen.out";

	public:
		OutputPeripherals();
		bool set_leds(bool leds[32]);
		bool set_screen(Screen screen);
};

char connect_bools_into_byte(bool bits[8]);

#endif // OUTPUTV_HPP
