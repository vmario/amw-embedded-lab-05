#include "timer.hpp"

#include <avr/io.h>

/**
 * Konfiguracja Timer/Counter1.
 */
constexpr uint8_t TIMER1_MODE = _BV(WGM12);

/**
 * Preskaler Timer/Counter1.
 */
constexpr uint8_t TIMER1_PRESCALER = _BV(CS11);

/**
 * Inicjalizuje Timer/Counter1.
 */
void timerInitialize()
{
	OCR1A = 0xFFFF;
	TCCR1B = TIMER1_PRESCALER | TIMER1_MODE;
	TIMSK1 = _BV(OCIE1A);
}

