/*
 * uart_driver.c
 *
 * Created: 03.09.2022 11:27:38
 *  Author: larsmto
 */ 

#include "usart_driver.h"

#include <avr/io.h>

void usart_init(unsigned int ubrr) {
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter and receiver interrupt */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);
}

void usart_transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char usart_receive( void ) {
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

int put(char data, FILE* file) {
	usart_transmit(data);
	return 0;
}

int get(FILE* file) {
	return usart_receive();
}

ISR(USART0_RXC_vect) {
	usart_transmit(UDR0);
}