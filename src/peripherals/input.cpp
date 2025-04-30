#include <cstdint>
#include <iostream>

#include "../mz_apo/mzapo_regs.h"
#include "./input.hpp"
#include "./mapping.hpp"

InputPeripherals::InputPeripherals(
	PeripheralMemoryMapping peripheral_memory_mapping) {
	this->peripheral_memory_mapping = peripheral_memory_mapping;
}

InputDelta InputPeripherals::get_delta() {
	uint32_t knobs =
		*(uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
					  SPILED_REG_KNOBS_8BIT_o);

	InputDelta input_delta = {0};
	input_delta.blue = (knobs >> 0) & 0xFF;
	input_delta.green = (knobs >> 8) & 0xFF;
	input_delta.red = (knobs >> 16) & 0xFF;

	std::cout << "Knob delta: red=" << (int)input_delta.red
			  << " green=" << (int)input_delta.green
			  << " blue=" << (int)input_delta.blue << std::endl;

	return input_delta;
}

KnobPressState InputPeripherals::get_knob_press_state() {
	uint32_t knobs =
		*(uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
					  SPILED_REG_KNOBS_8BIT_o);

	KnobPressState state;
	state.blue = (knobs >> 24) & 0x1;
	state.green = (knobs >> 25) & 0x1;
	state.red = (knobs >> 26) & 0x1;

	std::cout << "Knob state: red=" << (bool)state.red
			  << " green=" << (bool)state.green << " blue=" << (bool)state.blue
			  << std::endl;

	return state;
}
