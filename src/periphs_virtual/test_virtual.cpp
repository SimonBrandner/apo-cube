#include "input.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main(void) {
	InputPeripherals peripherals = InputPeripherals();
	while (true) {
		InputDelta delta = peripherals.get_delta();
		std::cout << "Rv: " << (int)delta.red << std::endl;
		std::cout << "Gv: " << (int)delta.green << std::endl;
		std::cout << "Bv: " << (int)delta.blue << std::endl;

		InputPresses presses = peripherals.input_presses();
		std::cout << "Rp: " << presses.red << std::endl;
		std::cout << "Gp: " << presses.green << std::endl;
		std::cout << "Bp: " << presses.blue << "\n" <<  std::endl;


		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}