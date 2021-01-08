/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "led.h"
#include "gpio.h"
#include "timer_mngr.h"
#include "common.h"
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define LED_LOG_ENABLE
#ifdef LED_LOG_ENABLE
#define LED_LOG(...)				SYS_LOGGER("[LED]: "__VA_ARGS__)
#define LED_LOG_ERR(...)			SYS_LOGGER_ERR("[LED]: "__VA_ARGS__)
#define LED_LOG_WRN(...)			SYS_LOGGER_WRN("[LED]: "__VA_ARGS__)
#define LED_LOG_INFO(...)			SYS_LOGGER_INFO("[LED]: "__VA_ARGS__)
#define LED_LOG_SUCC(...)			SYS_LOGGER_SUCC("[LED]: "__VA_ARGS__)
#else
#define LED_LOG(...)
#define LED_LOG_ERR(...)
#define LED_LOG_WRN(...)
#define LED_LOG_INFO(...)
#define LED_LOG_SUCC(...)
#endif



#define MAXMUM_BLINK_LEDS			(10)
#define MAXMUM_FLASH_LEDS			(10)

#define INVALID_MARK				(0XFF)
#define FLASH_TIMES					(3)//cannot be greater than 3
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static tstr_led_module_param gstr_led_module_param;
static bool led_initalized = FALSE;

static tstr_led_attr gastr_blinky_leds[MAXMUM_BLINK_LEDS] ;
static uint_8 gu8_blinky_leds_count = 0 ;
static bool gb_blink_state = TRUE;

static tstr_led_attr gastr_flashy_leds[MAXMUM_FLASH_LEDS] ;
static uint_8 gu8_flashy_leds_count = 0 ;
static bool gb_flash_state = TRUE;

static tstr_timer_mgmt_ins gstr_led_blink_timer;
static bool gb_blink_timer_fired = FALSE;
static tstr_timer_mgmt_ins gstr_led_flash_timer;
static bool gb_flash_timer_fired = FALSE;

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
static void blink_timer_cb(void *arg)
{
	gb_blink_state = (gb_blink_state == TRUE) ? FALSE : TRUE;
	gb_blink_timer_fired = TRUE;
}

static void flash_timer_cb(void *arg)
{
	gb_flash_state = (gb_flash_state == TRUE) ? FALSE : TRUE;
	gb_flash_timer_fired = TRUE;
}
sint_16 add_led_to_array(tstr_led_attr str_led_attr , tstr_led_attr * pstr_led_attr, uint_8 u8_array_max_size)
{
	sint_16 u16_retval = ERROR;
	uint_8 u8_index;
	for(u8_index = 0 ; u8_index < u8_array_max_size;u8_index++)
	{
		if(pstr_led_attr[u8_index].u3_port == 0x07 && pstr_led_attr[u8_index].u3_pin == 0x07)
		{
			pstr_led_attr[u8_index] = str_led_attr ;
			u16_retval = SUCCESS;
			break;
		}
	}
	return u16_retval;
}

sint_16 remove_led_to_array(tstr_led_attr str_led_attr , tstr_led_attr * pstr_led_attr, uint_8 u8_array_max_size)
{
	sint_16 u16_retval = ERROR;
		uint_8 u8_index;
		for(u8_index = 0 ; u8_index < u8_array_max_size;u8_index++)
		{
			if(pstr_led_attr[u8_index].u3_port == str_led_attr.u3_port && pstr_led_attr[u8_index].u3_pin == str_led_attr.u3_pin)
			{
				pstr_led_attr[u8_index].u3_port = 0x07 ;
				pstr_led_attr[u8_index].u3_pin = 0x07 ;
				u16_retval = SUCCESS;
				break;
			}
		}
		return u16_retval;
}
/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/
sint_16 led_init(tstr_led_module_param * pstr_led_module_param)
{
	sint_16 u16_retval = SUCCESS;
	if(led_initalized == FALSE)
	{
		if(pstr_led_module_param != NULL
		   && pstr_led_module_param->u16_led_blink_off_period > 0
		   && pstr_led_module_param->u16_led_blink_on_period  > 0
		   && pstr_led_module_param->u16_led_flash_off_period > 0
		   && pstr_led_module_param->u16_led_flash_on_period  > 0)
		{
			timer_mgmt_init();
			u16_retval = gpio_init();
			if(u16_retval == SUCCESS)
			{

				MEMSET(gastr_blinky_leds,INVALID_MARK,sizeof(tstr_led_attr) * MAXMUM_BLINK_LEDS);
				MEMSET(gastr_flashy_leds,INVALID_MARK,sizeof(tstr_led_attr) * MAXMUM_BLINK_LEDS);
				gstr_led_module_param = (*pstr_led_module_param);
				led_initalized = TRUE;
			}
		}
		else
		{
			u16_retval = LED_INVALID_PARAMETER;
		}
	}
	return u16_retval;
}
sint_16 led_on(uint_8 u8_port,uint_8 u8_pin)
{
	sint_16 u16_retval = SUCCESS;
	u16_retval = gpio_select(u8_port , u8_pin);
	u16_retval = gpio_set_pin_direction(u8_port , u8_pin , GPIO_OUTPUT);
	u16_retval = gpio_set_pin_value(u8_port, u8_pin, GPIO_HIGH);
	return u16_retval;

}

sint_16 led_blink(uint_8 u8_port,uint_8 u8_pin)
{
	sint_16 u16_retval = SUCCESS;
	u16_retval = gpio_select(u8_port , u8_pin);
	u16_retval = gpio_set_pin_direction(u8_port , u8_pin , GPIO_OUTPUT);
	if(u16_retval == SUCCESS)
	{
		tstr_led_attr str_led_attr = {.u3_pin = u8_pin , .u3_port = u8_port};
		u16_retval = add_led_to_array(str_led_attr,gastr_blinky_leds,MAXMUM_BLINK_LEDS);
		if(u16_retval == SUCCESS)
		{
			gu8_blinky_leds_count++;
		}
	}
	return u16_retval;

}

sint_16 led_flash(uint_8 u8_port,uint_8 u8_pin)
{
	sint_16 u16_retval = SUCCESS;
	u16_retval = gpio_select(u8_port , u8_pin);
	u16_retval = gpio_set_pin_direction(u8_port , u8_pin , GPIO_OUTPUT);
	if(u16_retval == SUCCESS)
	{
		tstr_led_attr str_led_attr = {.u3_pin = u8_pin , .u3_port = u8_port ,.u2_times = FLASH_TIMES};
		u16_retval = add_led_to_array(str_led_attr,gastr_flashy_leds,MAXMUM_FLASH_LEDS);
		if(u16_retval == SUCCESS)
		{
			gu8_flashy_leds_count++;
		}
	}

	return u16_retval;

}
sint_16 led_off(uint_8 u8_port,uint_8 u8_pin)
{
	sint_16 u16_retval = SUCCESS;

	tstr_led_attr str_led_attr = {.u3_pin = u8_pin , .u3_port = u8_port};
	u16_retval = remove_led_to_array(str_led_attr,gastr_blinky_leds,MAXMUM_BLINK_LEDS);
	if(u16_retval == SUCCESS)
	{
		gu8_blinky_leds_count--;
	}
	u16_retval = remove_led_to_array(str_led_attr,gastr_flashy_leds,MAXMUM_FLASH_LEDS);
	if(u16_retval == SUCCESS)
	{
		gu8_flashy_leds_count--;
	}
	u16_retval = gpio_set_pin_value(u8_port, u8_pin, GPIO_LOW);
	u16_retval = gpio_deselect(u8_port , u8_pin);
	return u16_retval;
}

void led_dispatch(void)
{
	if(gb_blink_timer_fired == TRUE)
	{
		gb_blink_timer_fired = FALSE;
		uint_8 u8_index;
		for(u8_index = 0 ; u8_index < MAXMUM_BLINK_LEDS;u8_index++)
		{
			if(gastr_blinky_leds[u8_index].u3_pin != 0x07 && gastr_blinky_leds[u8_index].u3_port != 0x07)
			{
				gpio_toggle(gastr_blinky_leds[u8_index].u3_port,gastr_blinky_leds[u8_index].u3_pin);
			}
		}
	}

	if(gu8_blinky_leds_count > 0)
	{
		if(gb_blink_state)
		{
			start_timer(&gstr_led_blink_timer,gstr_led_module_param.u16_led_blink_off_period,blink_timer_cb,NULL);
		}
		else
		{
			start_timer(&gstr_led_blink_timer,gstr_led_module_param.u16_led_blink_on_period,blink_timer_cb,NULL);
		}
	}


	if(gb_flash_timer_fired == TRUE)
	{
		gb_flash_timer_fired = FALSE;
		uint_8 u8_index;
		for(u8_index = 0 ; u8_index < MAXMUM_FLASH_LEDS;u8_index++)
		{
			if(gastr_flashy_leds[u8_index].u3_pin != 0x07 && gastr_flashy_leds[u8_index].u3_port != 0x07)
			{
				gpio_toggle(gastr_flashy_leds[u8_index].u3_port,gastr_flashy_leds[u8_index].u3_pin);
				if(gastr_flashy_leds[u8_index].u2_times  == 0)
				{
					gpio_set_pin_value(gastr_flashy_leds[u8_index].u3_port, gastr_flashy_leds[u8_index].u3_pin, GPIO_LOW);
					gpio_deselect(gastr_flashy_leds[u8_index].u3_port , gastr_flashy_leds[u8_index].u3_pin);
					gastr_flashy_leds[u8_index].u3_port = 0x07;
					gastr_flashy_leds[u8_index].u3_pin = 0x07;
					if(gu8_flashy_leds_count > 0)
					{
						gu8_flashy_leds_count--;
					}
				}
				else if(gb_flash_state == FALSE)
				{
					if(gastr_flashy_leds[u8_index].u2_times > 0)
					{
						gastr_flashy_leds[u8_index].u2_times--;
					}

				}
			}
		}
	}

	if(gu8_flashy_leds_count > 0)
	{
		if(gb_flash_state)
		{
			start_timer(&gstr_led_flash_timer,gstr_led_module_param.u16_led_flash_off_period,flash_timer_cb,NULL);
		}
		else
		{
			start_timer(&gstr_led_flash_timer,gstr_led_module_param.u16_led_flash_on_period,flash_timer_cb,NULL);
		}
	}

}
