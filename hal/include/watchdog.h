#define    MCUCSR    *((volatile u8*)0x54)
#define    WDTCR     *((volatile u8*)0x41)

#define wdt_success   -700

sint_16 WDT_Enable(wdt_prescaler);
sint_16 WDT_Disable();

typedef enum wdt_prescaler
{
	wdt_17_1_ms=0,
	wdt_34_3_ms=1,
	wdt_68_5_ms=2,
	wdt_140_ms=3,
	wdt_270_ms=4,
	wdt_550_ms=5,
	wdt_1100_ms=6,
	wdt_2200_ms=7
}wdt_prescaler;