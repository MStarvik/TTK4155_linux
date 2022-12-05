/*
 * main.c
 *
 * Created: 03.09.2022 09:12:34
 * Author : larsmto
 */ 

#define F_CPU 4915200UL

#include "usart_driver/usart_driver.h"
#include "xmem_driver/xmem_driver.h"
#include "adc_driver/adc_driver.h"

#include <util/delay.h>

int main(void) {
	usart_init(MYUBRR);
	xmem_init();
	adc_init();

	sei();
	fdevopen(put, get);
	
	//SRAM_test();

	adc_calibrate();
	
	while (1) {
		uint8_t values[4];
		adc_read(values);
		printf("x: %d y: %d l: %d r: %d\r\n", values[0], values[1], values[2], values[3]);
	}
}

