#include "counter.hpp"
#include "display.hpp"

void Counter::increment()
{
	if (value < 9999) {
		value++;
	}

	display.print(value);
}

void Counter::decrement()
{
	if (value > 0) {
		value--;
	}

	display.print(value);
}

void Counter::reset()
{
	value = 0;

	display.print(value);
}

