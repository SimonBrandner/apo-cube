#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>
#include <string>

struct InputDelta {
	int8_t red;
	int8_t green;
	int8_t blue;
};

struct InputNow {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct InputPresses {
	bool red;
	bool green;
	bool blue;
	bool any;
};

class InputPeripherals {
	private:
		const std::string fname_knobs = "src/periphs_virtual/memory/knobs.in";
		const std::string fname_knob_presses = "src/periphs_virtual/memory/knob_presses.in";
		bool previous_delta_initialized = false;
		InputNow previous_delta;

	public:
		InputPeripherals();
		InputDelta get_delta();
		InputPresses input_presses();
};

#endif // INPUT_HPP
