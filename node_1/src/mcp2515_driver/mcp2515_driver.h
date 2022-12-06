#pragma once

#include "mcp2515.h"
#include "../spi_driver/spi_driver.h"

#include <stdint.h>

uint8_t mcp2515_init();
uint8_t mcp2515_read(uint8_t address);
void mcp2515_write(uint8_t address, uint8_t data);
void mcp2515_reset();
void mcp2515_enable();
void mcp2515_disable();
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
uint8_t mcp2515_read_status();
void mcp2515_request_to_send(uint8_t TXB);