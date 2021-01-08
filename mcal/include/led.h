
#ifndef _LED_H_
#define _LED_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define LED_INVALID_PARAMETER				(LED_ERROR_BASE -1)
#define LED_NOT_INTIALIZED_YET				(LED_ERROR_BASE -2)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/
typedef struct _tstr_led_module_param
{
	uint_16 u16_led_blink_on_period;
	uint_16 u16_led_blink_off_period;
	uint_16 u16_led_flash_on_period;
	uint_16 u16_led_flash_off_period;
}tstr_led_module_param;

typedef struct _tstr_led_attr
{
	uint_8 u3_port:3;
	uint_8 u3_pin:3;
	uint_8 u2_times:2;
}tstr_led_attr;
/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 led_init(tstr_led_module_param * pstr_led_module_param);
sint_16 led_on(uint_8 u8_port,uint_8 u8_pin);
sint_16 led_blink(uint_8 u8_port,uint_8 u8_pin);
sint_16 led_flash(uint_8 u8_port,uint_8 u8_pin);
sint_16 led_off(uint_8 u8_port,uint_8 u8_pin);
void led_dispatch(void);
#endif /*_LED_H_*/





