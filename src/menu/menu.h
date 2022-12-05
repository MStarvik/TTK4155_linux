#pragma once

#include <stdint.h>

#include <avr/interrupt.h>


ISR(TIMER0_OVF_vect);

void menu_init();
void menu_update(const uint8_t x, const uint8_t y);
