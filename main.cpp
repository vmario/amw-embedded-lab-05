#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"
#include "counter.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_SWITCH PINC ///< Rejestr wejściowy przycisków.

/**
 * Numery pinów przycisków.
 */
enum BIT_SWITCH {
	BIT_SWITCH_S1 = 1, ///< Przycisk S1.
	BIT_SWITCH_S2 = 2, ///< Przycisk S2.
	BIT_SWITCH_S3 = 3, ///< Przycisk S3.
};

/**
 * Licznik sterowany przyciskami.
 *
 * Stosujemy zmienną globalną, gdyż może być obsługiwany z pętli głównej i z przerwań.
 */
Counter counter;

/**
 * Obsługa przerwania komparatora Timer/Counter1.
 */
ISR(TIMER1_COMPA_vect)
{
	display.refresh();
}

/**
 * Pętla główna.
 */
void mainLoop()
{
	if (bit_is_clear(PIN_SWITCH, BIT_SWITCH_S1)) {
		counter.increment();
	}

	if (bit_is_clear(PIN_SWITCH, BIT_SWITCH_S2)) {
		counter.decrement();
	}

	if (bit_is_clear(PIN_SWITCH, BIT_SWITCH_S3)) {
		counter.reset();
	}
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();

	sei();

	while (true) {
		mainLoop();
	}
}
