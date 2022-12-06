#include "oled_buffer.h"
#include "../fonts/fonts.h"
#include "../oled_driver/oled_driver.h"

#include <avr/io.h>

static uint8_t buffer_row = 0;
static uint8_t buffer_column = 0;

static volatile uint8_t* buffer = ( uint8_t *) 0x1800;

uint8_t oled_buffer_read_data(uint8_t row, uint8_t column) {
	return buffer[row * 128 + column];
}

void oled_buffer_write_data(uint8_t byte) {
	buffer[buffer_row * 128 + buffer_column] = byte;
	buffer_column++;
}

void oled_buffer_pos(uint8_t row, uint8_t column) {
	buffer_row = row;
	buffer_column = column;
}

//void oled_buffer_print_arrow();

//void oled_buffer_clear_line(uint8_t line);

void oled_buffer_print(char* string) {
	char c = string[0];
	while (c != '\0') {
		for (int i = 0; i < 8; i++) {
			uint8_t byte = pgm_read_byte(&(font8[c - 32][i]));
			oled_buffer_write_data(byte);
		}
		c = *(++string);
	}
}

void oled_buffer_reset() {
	for (uint8_t row = 0; row < 8; row++) {
		for (uint8_t column = 0; column < 128; column++) {
			buffer[row * 128 + column] = 0;
		}
	}
	buffer_row = 0;
	buffer_column = 0;
}

void oled_buffer_flush() {
	for (uint8_t row = 0; row < 8; row++) {
		oled_pos(row, 0);
		for (uint8_t column = 0; column < 128; column++) {
			uint8_t byte = oled_buffer_read_data(row, column);
			oled_write_data(byte);
		}
	}
}