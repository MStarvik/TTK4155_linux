/*
 * main.c
 *
 * Created: 03.09.2022 09:12:34
 * Author : larsmto
 */ 

#include "usart_driver/usart_driver.h"

int main(void) {
	usart_init(MYUBRR);
	sei();
	fdevopen(put, get);
	printf("test");
	while (1);
}

