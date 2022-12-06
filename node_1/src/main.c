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
#include "menu/menu.h"
#include "spi_driver/spi_driver.h"
#include "mcp2515_driver/mcp2515_driver.h"
#include "can_driver/can_driver.h"
#include "joystick/joystick.h"

#include <util/delay.h>

int main(void) {
	fdevopen(put, get);

	usart_init(MYUBRR);
	xmem_init();
	adc_init();
	oled_init();
	// menu_init();
	mcp2515_init();
	can_init();

	sei();
	
	while (1) {
		_delay_ms(500);
		joystick_send();
	}
}

