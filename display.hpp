#pragma once

#include <avr/io.h>

/**
 * Liczba cyfr na wyświetlaczu.
 */
constexpr uint8_t DISPLAY_SIZE{4};

extern const uint8_t FONT[];

extern uint8_t DIGITS[DISPLAY_SIZE];

void refreshDisplay();
