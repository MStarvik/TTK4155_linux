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
#include "oled_driver/oled_driver.h"
#include "oled_buffer/oled_buffer.h"
#include "user_interface/user_interface.h"

#include <util/delay.h>

int main(void) {
	usart_init(MYUBRR);
	xmem_init();
	adc_init();
	oled_init();

	sei();
	fdevopen(put, get);
	
	//SRAM_test();

	adc_calibrate();
	oled_reset();

	UserInterface* UI = UI_create();
	Node* first = Node_create("first", NULL);
	Node* second = Node_create("second", NULL);
	Node* third = Node_create("third", NULL);
	
	Node_addChild(UI->root, first);
	Node_addChild(UI->root, second);
	Node_addChild(UI->root, third);
	
	UI->selected = first;
	
	while (1) {
		static int16_t prev_y = -1;

		uint8_t values[4];
		adc_read(values);
		printf("x: %d y: %d l: %d r: %d\r\n", values[0], values[1], values[2], values[3]);
		uint8_t x = values[0];
		uint8_t y = values[1];
		if(y == 255 && prev_y != 255) {
			UI_prev(UI);
			printf("prev\r\n");
		} else if (y == 0 && prev_y != 0) {
			UI_next(UI);
			printf("next\r\n");
		} 
		prev_y = y;
		
		oled_reset();
		UI_draw(UI);
	}
}

