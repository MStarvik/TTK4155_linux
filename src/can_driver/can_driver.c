#include "can_driver.h"
#include "../mcp2515_driver/mcp2515.h"
#include "../mcp2515_driver/mcp2515_driver.h"

void can_init() {
	//Loopback Mode CANCTRL register 010
	mcp2515_bit_modify(MODE_CONFIG, 0b111 << 5, 0b010 << 5);
}