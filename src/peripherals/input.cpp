#include <cstdint>
#include <iostream>

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

	KnobRotation delta = {0};
	delta.blue = (knobs >> 0) & 0xFF;
	delta.green = (knobs >> 8) & 0xFF;
	delta.red = (knobs >> 16) & 0xFF;

	std::cout << "Knob rotation delta: red=" << (int)delta.red
			  << " green=" << (int)delta.green << " blue=" << (int)delta.blue
			  << std::endl;

	return delta;
}

KnobPress InputPeripherals::get_press_delta() {
	uint32_t knobs =
		*(uint32_t *)(this->peripheral_memory_mapping.get_spi_address() +
					  SPILED_REG_KNOBS_8BIT_o);

	KnobPress delta;
	delta.blue = (knobs >> 24) & 0x1;
	delta.green = (knobs >> 25) & 0x1;
	delta.red = (knobs >> 26) & 0x1;

	std::cout << "Knob press delta: red=" << (bool)delta.red
			  << " green=" << (bool)delta.green << " blue=" << (bool)delta.blue
			  << std::endl;

	return delta;
}
