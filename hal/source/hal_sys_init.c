

#include <avr/io.h>

#include "debug.h"
#include "app.h"

int main(void)
{
	SYS_LOGGER_INIT(UART_BAUDRATE_9600);
	app_init();
	for (;;)
	{
		app_dispatch();
	}
}