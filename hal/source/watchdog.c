#include"Basictypes.h"
#include"BIT_MATH.h"
#include"watchdog.h"

sint_16 WDT_Enable(wdt_prescaler)
{
	
	WDTCR |=wdt_prescaler;
	SET_BIT(WDTCR,3);
return wdt_success;
}
sint_16 WDT_Disable()
{
	WDTCR |= (1<<3)|(1<<4);
	WDTCR = 0x00;
return wdt_success;
}
