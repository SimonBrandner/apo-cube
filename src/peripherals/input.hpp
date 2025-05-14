#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>

#include "mapping.hpp"

/**
 * @brief Struct to hold the state of the knobs.
 *
 * The knobs are represented as 8-bit signed integers, where positive values
 * indicate clockwise rotation and negative values indicate counter-clockwise
 * rotation.
 */
struct KnobRotation {
	public:
		int8_t red;
		int8_t green;
		int8_t blue;
};

/**
 * @brief Struct to hold the press state of the knobs.
 *
 * The press state is represented as a boolean value, where true indicates that
 * the knob is pressed and false indicates that it is not pressed.
 */
struct KnobPress {
	public:
		bool red;
		bool green;
		bool blue;
};

/**
 * @brief Class to handle input from the knobs.
 *
 * This class reads the state of the knobs and provides methods to get the
 * rotation and press state of the knobs.
 */
class InputPeripherals {
	private:
		PeripheralMemoryMapping
			peripheral_memory_mapping; // Memory mapping for the peripherals
		KnobPress press_state;		   // Current press state of the knobs
		KnobRotation rotation_state;   // Current rotation state of the knobs
		bool first_read = false; // Flag to indicate if this is the first read

	public:
		/**
		 * @brief Constructor for the InputPeripherals class.
		 *
		 * Initializes the input peripherals with the given memory mapping.
		 *
		 * @param peripheral_memory_mapping The memory mapping for the
		 * peripherals.
		 */
		InputPeripherals(PeripheralMemoryMapping peripheral_memory_mapping);

		/**
		 * @brief Getter for the delta press state of the knobs.
		 *
		 * @return The difference of press state of the knobs.
		 */
		KnobRotation get_rotation_delta();

		/**
		 * @brief Getter for the press state delta of the knobs.
		 *
		 * @return The difference of press state of the knobs.
		 */
		KnobPress get_press_delta();
};

#endif // INPUT_HPP
