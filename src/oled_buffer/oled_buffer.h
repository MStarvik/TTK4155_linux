#pragma once

#include <stdint.h>

uint8_t oled_buffer_read_data(uint8_t row, uint8_t column);

void oled_buffer_write_data(uint8_t byte);

void oled_buffer_pos(uint8_t row, uint8_t column);

//void Buffer_print_arrow();

//void Buffer_clear_line(uint8_t line);

void oled_buffer_print(char* string);

void oled_buffer_flush();

void oled_buffer_reset();