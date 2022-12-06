#pragma once

#include <stdint.h>

void SPI_init(void);
void SPI_send(uint8_t cData);
uint8_t SPI_exchange(uint8_t c);
