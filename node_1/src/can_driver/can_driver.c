#include "can_driver.h"
#include "../mcp2515_driver/mcp2515.h"
#include "../mcp2515_driver/mcp2515_driver.h"

#include <stdio.h>

#include <avr/io.h>

void can_init() {
	//Set Bit Timing
	mcp2515_bit_modify(MCP_CNF3, CNF3_PHSEG2_Mask, 5);
	
	mcp2515_bit_modify(MCP_CNF2, CNF2_BTLMODE_Mask | CNF2_SAM_Mask | CNF2_PHSEG1_Mask | CNF2_PRSEG_Mask, BTLMODE | SAMPLE_1X | (6 << 3) | 1);
	
	mcp2515_bit_modify(MCP_CNF1, CNF1_SJW_Mask | CNF1_BRP_Mask, 4);
	
	//Normal Mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
			
	//Enable receive interrupts
	mcp2515_bit_modify(MCP_CANINTE, MCP_RX0IE | MCP_RX1IE, 0xFF);

	//Enable external interrupt
	cli();
	DDRD &= ~(1 << PD2); // sets INT0 to input
	GICR |=	(1 << INT0); 
	MCUCR &= ~(1 << ISC00);
	sei();
}

void can_message_send(can_message_t* msg) {
	//Wait for previous transmission to be done
	while (mcp2515_read(MCP_TXB0CTRL)&(1 << MCP_TXREQ)) {}

	//set id registers
	mcp2515_write(MCP_TXB0SIDH, msg->id >> 3);
	mcp2515_write(MCP_TXB0SIDL, msg->id << 5);
	
	//Set data length register
	mcp2515_write(MCP_TXB0DLC, msg->data_length < 8 ? msg->data_length : 8);
	
	for (uint8_t i = 0; i < msg->data_length; i++) {
		mcp2515_write(MCP_TXB0D0 + i, msg->data[i]);
	}
	
	mcp2515_bit_modify(MCP_TXB0CTRL, MCP_TXREQ, MCP_TXREQ);
}

void can_data_receive(uint8_t buffer, can_message_t* msg) {
	msg->id = 0;
	if (buffer == 0) {
		msg->id = (uint16_t)((mcp2515_read(MCP_RXB0SIDH)) << 3) + (mcp2515_read(MCP_RXB0SIDL) >> 5);
		msg->data_length = mcp2515_read(MCP_RXB0DLC);
		
		for (uint8_t i = 0; i < msg->data_length; i++) {
			msg->data[i] = mcp2515_read(MCP_RXB0D0+i);
		}
		
	} else if (buffer == 1) {
		msg->id = ((uint16_t)(mcp2515_read(MCP_RXB1SIDH)) << 3) + (mcp2515_read(MCP_RXB1SIDL) >> 5);
		msg->data_length = mcp2515_read(MCP_RXB1DLC);
		
		for (uint8_t i = 0; i < msg->data_length; i++) {
			msg->data[i] = mcp2515_read(MCP_RXB1D0+i);
		}
	}
}

ISR(INT0_vect) {
	printf("interrupt");
	if (mcp2515_read(MCP_CANINTF) & MCP_RX0IF) {
		can_message_t msg;
		can_data_receive(0, &msg);
		for (uint8_t i = 0; i < msg.data_length; i++) {
			printf("data received buffer0: %c\r\n", msg.data[i]);
		}
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
	}
	
	if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF) {
		can_message_t msg;
		can_data_receive(1, &msg);
		for (uint8_t i = 0; i < msg.data_length; i++) {
			printf("data received buffer1: %c\r\n", msg.data[i]);
		}
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX1IF, 0);
	}
}