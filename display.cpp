#include "display.hpp"

#include "gpio.hpp"

#include <stdint.h>

/**
 * Wzorce cyfr na wyświetlaczu siedmiosegmentowym.
 */
const uint8_t FONT[] = {
	0b00000011, // 0
	0b10011111, // 1
	0b00100101, // 2
	0b00001101, // 3
	0b10011001, // 4
	0b00000000, // 5
	0b00000000, // 6
	0b00000000, // 7
	0b00000000, // 8
	0b00000000, // 9
};

/**
 * Tablica cyfr na wyświetlaczu (od prawej do lewej).
 */
uint8_t DIGITS[DISPLAY_SIZE] = {FONT[0], FONT[0], FONT[0], FONT[0]};

/**
 * Wyświetla pojedynczą cyfrę na wyświetlaczu.
 *
 * @param value Cyfra do wyświetlenia.
 * @param position Numer cyfry na wyświetlaczu (od prawej do lewej).
 */
void showDigit(uint8_t value, uint8_t position)
{
	shiftByte(value);
	shiftByte(1 << (position + 4));
	latchData();
}

/**
 * Odświeża wyświetlacz, wyświetlając za każdym razem kolejną cyfrę z tablicy DIGITS.
 */
void refreshDisplay()
{
	static uint8_t cursor;

	showDigit(DIGITS[cursor], cursor);

	if (++cursor >= DISPLAY_SIZE) {
		cursor = 0;
	}
}

