#pragma once

#include <avr/io.h>

#include <stdint.h>

#define DDR_SDI DDRB ///< Rejestr kierunku pinu danych.
#define DDR_CLOCK DDRD ///< Rejestr kierunku zegarów.

#define PORT_SDI PORTB ///< Wyjście pinu danych.
#define PORT_CLOCK PORTD ///< Wyjście zegarów.

/**
 * Numery pinów sterujących rejestrem przesuwnym.
 */
enum PIN {
	PIN_SDI = 0, ///< Dane wejściowe.
	PIN_CLOCK_SHIFT = 7, ///< Taktowanie danych.
	PIN_CLOCK_LATCH = 4, ///< Zatrzask.
};

void gpioInitialize();

void shiftByte(uint8_t byte);

void latchData();
