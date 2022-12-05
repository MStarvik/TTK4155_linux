#define F_CPU 4915200UL

#include "mcp2515_driver.h"

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>

uint8_t mcp2515_init() {
	
	SPI_init();
	mcp2515_reset();
	//Self test
	_delay_ms(1);
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf(" mcp2515 is NOT in configuration mode after reset !\r\n");
		printf("Value: %d\r\n", value);
		
		return 1;
	}
	return 0;
}

uint8_t mcp2515_read(uint8_t address) {
	mcp2515_enable();
	
	SPI_exchange(MCP_READ); 
	SPI_exchange(address);
	uint8_t data = SPI_exchange(0);
	
	mcp2515_disable();
	
	return data;
}

void mcp2515_write(uint8_t address, uint8_t data) {
	mcp2515_enable();
	
	SPI_exchange(MCP_WRITE);
	SPI_exchange(address);
	SPI_exchange(data);
	
	mcp2515_disable();
}

void mcp2515_reset() {
	mcp2515_enable();
	
	SPI_exchange(MCP_RESET);

	mcp2515_disable();
}

void mcp2515_request_to_send(uint8_t TXB) {
	mcp2515_enable();
		
	SPI_exchange(0b10000000 | TXB);
	
	mcp2515_disable();
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	mcp2515_enable();
	
	SPI_exchange(MCP_BITMOD);
	SPI_exchange(address);
	SPI_exchange(mask);
	SPI_exchange(data);
	
	mcp2515_disable();
}

uint8_t mcp2515_read_status() {
	mcp2515_enable();
	
	SPI_exchange(MCP_READ_STATUS);
	uint8_t status = SPI_exchange(0);
	SPI_exchange(0);
	
	mcp2515_disable();
	return status;
}

void mcp2515_enable() {
	PORTB &= ~(1 << PB4);
}
void mcp2515_disable() {
	PORTB |= (1 << PB4);
}