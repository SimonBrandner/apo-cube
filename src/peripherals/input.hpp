#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>

struct InputDelta {
	uint8_t red_knob_delta;
	uint8_t green_knob_delta;
	uint8_t blue_knob_delta;
	bool knob_pressed;
};

class InputPeripherals {
	public:
		InputPeripherals();
		InputDelta get_delta();
};

#endif // INPUT_HPP
