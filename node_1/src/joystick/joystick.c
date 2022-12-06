#include "joystick.h"
#include "../adc_driver/adc_driver.h"
#include "../can_driver/can_driver.h"

#define JOYSTICK_ID 10

void joystick_send() {
	pos_t pos;
	pos_read(&pos);
	can_message_t msg;
	msg.data[0] = pos.x;
	msg.data[1] = pos.y;
	msg.data_length = 2;
	msg.id = JOYSTICK_ID;
	can_message_send(&msg);
}