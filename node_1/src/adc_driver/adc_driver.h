#pragma once

#include <stdint.h>

typedef struct {
	uint8_t x;
	uint8_t y;
} pos_t;

void adc_init(void);
void adc_read(uint8_t* values);
void pos_read(pos_t* pos);
void adc_calibrate(void);