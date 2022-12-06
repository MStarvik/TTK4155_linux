#pragma once 

#include <stdint.h>

#include <avr/interrupt.h>

typedef struct {
	uint16_t id;
	char data_length;
	char data[8];
} can_message_t;

void can_init();

void can_message_send();

void can_data_receive(uint8_t buffer, can_message_t* msg);

void can_int_vect();

ISR(INT0_vect);