#include "./utils.hpp"

#include <iostream>

#include "../mz_apo/serialize_lock.h"

PeripheralMemoryMapping setup() {
	/* Serialize execution of applications */

	/* Try to acquire lock the first */
	if (serialize_lock(1) <= 0) {
		std::cout << "System is occupied" << std::endl;

		if (1) {
			printf("Waiting\n");
			/* Wait till application holding lock releases it or exits */
			serialize_lock(0);
		}
	}

	return PeripheralMemoryMapping();
}

void cleanup() { serialize_unlock(); }
