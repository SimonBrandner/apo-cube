#include "input.hpp"
#include "output.hpp"
#include "../render/utils.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main(void) {
	srand(time(NULL));

	InputPeripherals peripherals = InputPeripherals();

	/*while (true) {
		InputDelta delta = peripherals.get_delta();
		std::cout << "R delta: " << (int)delta.red << std::endl;
		std::cout << "G delta: " << (int)delta.green << std::endl;
		std::cout << "B delta: " << (int)delta.blue << std::endl;


		KnobPressState presses = peripherals.get_knob_press_state();
		std::cout << "R pressed: " << presses.red << std::endl;
		std::cout << "G pressed: " << presses.green << std::endl;
		std::cout << "B pressed: " << presses.blue << "\n" <<  std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}*/

	OutputPeripherals outputs = OutputPeripherals();
	Color screen[SCREEN_WIDTH][SCREEN_HEIGHT];
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			screen[x][y] = Color(rand() % 256, rand() % 256, rand() % 256);
		}
	}
	outputs.set_screen(screen);
	std::cout << "Screen set" << std::endl;

	bool leds[32] = {false};
	for (int i = 0; i < 32; ++i) {
		leds[i] = rand() % 2;
	}
	outputs.set_leds(leds);
	std::cout << "LEDs set" << std::endl;
	return 0;
}
