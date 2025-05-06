#include <cstdint>

#include "../mz_apo/mzapo_regs.h"
#include "./input.hpp"
#include "./mapping.hpp"

InputPeripherals::InputPeripherals(
	PeripheralMemoryMapping peripheral_memory_mapping) {
	this->peripheral_memory_mapping = peripheral_memory_mapping;
}

KnobRotation InputPeripherals::get_rotation_delta() {
	uint32_t knobs =
		*(uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
					  SPILED_REG_KNOBS_8BIT_o);
	KnobRotation new_state = {0};
	new_state.blue = ((knobs >> 0) & 0xFF);
	new_state.green = ((knobs >> 8) & 0xFF);
	new_state.red = ((knobs >> 16) & 0xFF);

	KnobRotation delta = {0};
	delta.blue = new_state.blue - this->rotation_state.blue;
	delta.green = new_state.green - this->rotation_state.green;
	delta.red = new_state.red - this->rotation_state.red;

	this->rotation_state = new_state;

	return delta;
}

KnobPress InputPeripherals::get_press_delta() {
	uint32_t knobs =
		*(uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
					  SPILED_REG_KNOBS_8BIT_o);

	KnobPress new_state;
	new_state.blue = (knobs >> 24) & 0x1;
	new_state.green = (knobs >> 25) & 0x1;
	new_state.red = (knobs >> 26) & 0x1;

	KnobPress delta;
	delta.blue = !new_state.blue && this->press_state.blue;
	delta.green = !new_state.green && this->press_state.green;
	delta.red = !new_state.red && this->press_state.red;

	this->press_state = new_state;

	return delta;
}
