#include "gpio.hpp"

/**
 * Inicjalizuje porty GPIO.
 */
void gpioInitialize()
{
	DDR_SDI = _BV(PIN_SDI);
	DDR_CLOCK = _BV(PIN_CLOCK_SHIFT) | _BV(PIN_CLOCK_LATCH);
}

/**
 * Umieszcza pojedynczy bajt w rejestrze przesuwnym.
 *
 * @param byte Bajt umieszczany w rejestrze.
 */
void shiftByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; ++i) {
		if (byte & 0x01) {
			PORT_SDI |= _BV(PIN_SDI);
		} else {
			PORT_SDI &= ~_BV(PIN_SDI);
		}

		byte >>= 1;

		PORT_CLOCK |= _BV(PIN_CLOCK_SHIFT);
		PORT_CLOCK &= ~_BV(PIN_CLOCK_SHIFT);
	}
}

/**
 * Zatrzaskuje dane (przepisuje je na wyjście).
 */
void latchData()
{
	PORT_CLOCK |= _BV(PIN_CLOCK_LATCH);
	PORT_CLOCK &= ~_BV(PIN_CLOCK_LATCH);
}
