#ifndef INPUT_HPP
#define INPUT_HPP

#include "mapping.hpp"
#include <cstdint>

struct KnobRotation {
	public:
		int8_t red;
		int8_t green;
		int8_t blue;
};

struct KnobPress {
	public:
		bool red;
		bool green;
		bool blue;
};

class InputPeripherals {
	private:
		PeripheralMemoryMapping peripheral_memory_mapping;
		KnobPress press_state;
		KnobRotation rotation_state;

	public:
		InputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);
		KnobRotation get_rotation_delta();
		KnobPress get_press_delta();
};

#endif // INPUT_HPP
