#ifndef INPUTV_HPP
#define INPUTV_HPP

#include <cstdint>
#include <string>
#include <optional>

struct KnobRotation  {
	int8_t red;
	int8_t green;
	int8_t blue;
};

struct InputNow {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct KnobPress {
	bool red;
	bool green;
	bool blue;
};

class InputPeripherals {
	private:
		const std::string fname_knobs = "src/periphs_virtual/memory/knobs.in";
		const std::string fname_knob_presses = "src/periphs_virtual/memory/knob_presses.in";
		std::optional<InputNow> previous_delta;

	public:
		InputPeripherals();
		KnobRotation  get_delta();
		KnobPress get_knob_press_state();
};

#endif // INPUTV_HPP
