#include "spi_driver.h"

#include <avr/io.h>

void SPI_init(void) {
	/* Set MOSI and SCK output, all others input */
	DDRB = (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
	/* Enable SPI, Master, set clock rate fck/128 */
	SPCR = (1 << SPE) | (1 << MSTR) | (0 << SPR1) | (0 << SPR0) | (0 << CPOL) | (0 << CPHA);
	/*  */
	PORTB |= 1 << PB4;
}

uint8_t SPI_exchange(uint8_t c) {
	SPDR = c;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

void SPI_send(uint8_t cData) {
	PORTB &= ~(1 << PB4);
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)));
	/*  */
	PORTB |= 1 << PB4;
}

