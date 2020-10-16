

#include <avr/io.h>




int main()
{
	
	app_init();
	
	for (;;)
	{
		app_dispatch();
	}
}