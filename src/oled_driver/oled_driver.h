#pragma once

#include <stdint.h>

void oled_init();

void oled_write_data(char data);

void oled_write_command(char data);

void oled_pos(uint8_t row, uint8_t column);

void oled_print_arrow();

void oled_goto_line(uint8_t line);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_reset();

void oled_print(char* string);