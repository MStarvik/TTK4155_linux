#include "oled_driver.h"
#include "../xmem_driver/xmem_driver.h"
#include "../fonts/fonts.h"

void oled_init() {
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode
	oled_write_command(0x02);
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); // display on
}

void oled_write_data(char data) {
	xmem_write(data, 0x200);
}

void oled_write_command(char data) {
	xmem_write(data, 0x000);
}

void oled_goto_column(uint8_t column) {
	uint8_t setLowerColumn = column & 0b00001111;
	oled_write_command(setLowerColumn);
	
	uint8_t setHigherColumn = (1 << 4) + (column >> 4);
	oled_write_command(setHigherColumn);
}

void oled_goto_line(uint8_t line) {
	uint8_t setPageStart = 0xb0 + line;
	oled_write_command(setPageStart);
}

void oled_pos(uint8_t row, uint8_t column) {
	oled_goto_line(row);
	oled_goto_column(column);
}

void oled_print_arrow() {
	oled_write_data(0b00011000);
	oled_write_data(0b00011000);
	oled_write_data(0b00011000);
	oled_write_data(0b01111110);
	oled_write_data(0b00111100);
	oled_write_data(0b00011000);
	oled_write_data(0b00000000);
	oled_write_data(0b00000000);
}

void oled_clear_line(uint8_t line) {
	oled_pos(line, 0);
	for (uint8_t i = 0; i < 128; i++) {
		oled_write_data(0b00000000);
		//printf("i: %d", i);
	}
}

void oled_reset() {
	for (uint8_t i = 0; i < 8; i++) {
		oled_clear_line(i);
		//_delay_ms(10);
	}
}

void oled_home() {
	oled_pos(0,0);
}

void oled_print(char* string) {
	//oled_pos(0,0);
	char c = string[0];
	while (c != '\0') {
		for (int i = 0; i < 8; i++) {
			uint8_t byte = pgm_read_byte(&(font8[c - 32][i]));
			oled_write_data(byte);
		}
		c = *(++string);
	}
	
}