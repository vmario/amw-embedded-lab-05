#include "stopwatch.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <stdint.h>

/**
 * Rozpisuje liczbę na kolejne cyfry dziesiętne i zapisuje w buforze wyświetlacza.
 *
 * @param value Wartość do umieszczenia na wyświetlaczu.
 */
void timeToDisplay(uint16_t value)
{
	for (uint8_t i = 0; i < DISPLAY_SIZE; ++i) {
		DIGITS[i] = FONT[value % 10];
		value /= 10;
	}
}

/**
 * Odmierza czas i wysyła do bufora wyświetlacza.
 */
void stopwatchIncrement()
{
	static uint16_t time;

	if (++time > 9999) {
		time = 0;
	}

	timeToDisplay(time);
}

/**
 * Dzieli takty z timera w celu odmierzania czasu.
 */
void stopwatchTick()
{
	static uint8_t time;

	if (++time == TIMER_FREQUENCY) {
		time = 0;
		stopwatchIncrement();
	}
}
