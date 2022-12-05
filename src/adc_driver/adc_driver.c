#define F_CPU 4915200UL

#include "adc_driver.h"
#include "../xmem_driver/xmem_driver.h"

#include <avr/io.h>
#include <util/delay.h>

int8_t offset_x;
int8_t offset_y;

void adc_init(void) {
	//Set PB5 to output
	DDRD |= (1 << DDD5);
	
	// Output compare register
	OCR1A = 1;
	
	// Compare Output Mode, toggle on compare match
	TCCR1A |= (1 << COM1A0);
	
	// Wave form generation mode, mode 15
	TCCR1A |= (1 << WGM10) | (1 << WGM11);
	
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	
	// Clock select, set to no prescaling
	TCCR1B |= (1 << CS10);
};

void adc_read(uint8_t* values) {
	xmem_write(0, 0x400);
	_delay_ms(10);
	values[0] = xmem_read(0x400);
	values[1] = xmem_read(0x400);
	values[2] = xmem_read(0x400);
	values[3] = xmem_read(0x400);
}

void adc_calibrate(void) {
	pos_t pos = pos_read();
	offset_x = 128 - pos.x;
	offset_y = 128 - pos.y;
}

uint8_t saturate_add(uint8_t a, int8_t b) {
	if (b < 0) {
		uint8_t c = a + b;
		if (c > a) {
			// Underflow
			return 0;
		}
		return c;
	}
	else if (b > 0) {
		uint8_t c = a + b;
		if (c < a) {
			// Overflow
			return 255;
		}
		return c;
	}
	return a;
}	

pos_t pos_read(void) {
	pos_t pos;
	
	xmem_write(0, 0x400);
	_delay_ms(10);
	
	pos.x = saturate_add(xmem_read(0x400), offset_x);
	pos.y = saturate_add(xmem_read(0x400), offset_y);
	
	return pos;
}