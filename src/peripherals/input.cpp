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
	uint32_t knobs = *(this->peripheral_memory_mapping.get_spi_address() +
					   SPILED_REG_KNOBS_8BIT_o);

	InputDelta input_delta = {0};
	input_delta.red = (knobs >> 0) & 0xFF;
	input_delta.green = (knobs >> 8) & 0xFF;
	input_delta.blue = (knobs >> 16) & 0xFF;

	return input_delta;
}

KnobPressState InputPeripherals::get_knob_press_state() {
	uint32_t knobs = *(this->peripheral_memory_mapping.get_spi_address() +
					   SPILED_REG_KNOBS_8BIT_o);

	KnobPressState state;
	state.red = (knobs >> 23) & 0x1;
	state.green = (knobs >> 24) & 0x1;
	state.blue = (knobs >> 25) & 0x1;

	std::cout << "Knob state: red=" << state.red << " green=" << state.green
			  << " blue=" << state.blue << std::endl;

	return state;
}
