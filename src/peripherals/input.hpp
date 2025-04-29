#ifndef INPUT_HPP
#define INPUT_HPP

#include "mapping.hpp"
#include <cstdint>

struct InputDelta {
	public:
		int8_t red;
		int8_t green;
		int8_t blue;
};

struct KnobPressState {
	public:
		bool red;
		bool green;
		bool blue;
};

class InputPeripherals {
	private:
		PeripheralMemoryMapping peripheral_memory_mapping;

	public:
		InputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);
		InputDelta get_delta();
		KnobPressState get_knob_press_state();
};

#endif // INPUT_HPP
