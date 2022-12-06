#include "uart/uart.h"
#include "uart/printf-stdarg.h"
#include "can/can_controller.h"

#include <stdio.h>
#include <stdarg.h>

#include <sam.h>

int main() {
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    configure_uart();

    if (can_init_def_tx_rx_mb((5 << PHASE2) | (6 << PHASE1) | (1 << PROPAG) | (0 << SJW) | (52 << BRP) | (0 << SMP))){
		printf("oopsie\n\r");
	}

    while (1) {
			CAN_MESSAGE msg;
			msg.data[0] = 'c';
			msg.data[1] = 'a';
			msg.data[2] = 'n';
			msg.data[3] = 'd';
			msg.data[4] = 'i';
			msg.data[5] = 's';
			msg.data_length = 6;
			msg.id = 1;
			if (can_send(&msg, 0)) {
				printf("can send failed\n\r");
			} else {
				//printf("works");
			}
			for (int i = 0; i < 10000000; i ++) {
				__asm__("nop");
			}
    }

    return 0;
}