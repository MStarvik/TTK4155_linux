/*
 * uart_driver.h
 *
 * Created: 03.09.2022 11:27:38
 *  Author: larsmto
 */ 

#pragma once

#include <stdio.h>

#include <avr/interrupt.h>

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

void usart_init(unsigned int ubrr);

void usart_transmit(unsigned char data);

unsigned char usart_receive(void);

int put(char data, FILE* file);

int get(FILE* file);

ISR(USART0_RXC_vect);