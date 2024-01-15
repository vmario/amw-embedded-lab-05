#pragma once

#include <stdint.h>

struct Counter {
	void increment();
	void decrement();
	void reset();

private:
	/**
	 * Bieżąca wartość licznika.
	 */
	uint16_t value{0};
};
