#include "timer.hpp"

#include <avr/io.h>

const Timer timer;

namespace {
/**
 * Konfiguracja Timer/Counter1.
 */
constexpr uint8_t TIMER1_MODE = _BV(WGM12);

/**
 * Preskaler Timer/Counter1.
 */
constexpr uint8_t TIMER1_PRESCALER = _BV(CS11);
}

/**
 * Inicjalizuje Timer/Counter1.
 */
void Timer::initialize() const
{
	constexpr double TOP{1.0 * F_CPU / 8 / TIMER_FREQUENCY - 1};
	static_assert(TOP == static_cast<uint16_t>(TOP),
		"Cannot obtain the exact frequency.");

	OCR1A = TOP;
	TCCR1B = TIMER1_PRESCALER | TIMER1_MODE;
	TIMSK1 = _BV(OCIE1A);
}

