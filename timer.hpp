#pragma once

#include <stdint.h>

/**
 * Częstotliwość przerwania przepełnienia Timer/Counter1. [Hz]
 */
constexpr uint16_t TIMER_FREQUENCY = 200;

void timerInitialize();
