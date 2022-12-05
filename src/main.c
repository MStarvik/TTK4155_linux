/*
 * main.c
 *
 * Created: 03.09.2022 09:12:34
 * Author : larsmto
 */ 

#define F_CPU 4915200UL

#include "usart_driver/usart_driver.h"
#include "xmem_driver/xmem_driver.h"

#include <util/delay.h>

int main(void) {
	usart_init(MYUBRR);
	sei();
	fdevopen(put, get);
	
	xmem_init();
	
	//SRAM_test();
	
	while (1) {
		xmem_write(0, 0x00);
		_delay_ms(10);
	}
}

