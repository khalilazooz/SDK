/*
 * actuator_handler.c
 *
 *  Created on: Jan 1, 2021
 *      Author: Khalil azooz
 */

/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "actuator_handler.h"
#include "heater_actuator.h"
#include "common.h"

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
static bool gb_actuator_handler = FALSE;

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/


/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 actuator_handler_init(void)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_actuator_handler == FALSE)
	{
		do
		{
			/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_ACTUATOR
			s16_retval = heater_actuator_init();
			ERROR_BREAK(s16_retval);
#endif
		}while(0);
	}
	return s16_retval;
}

sint_16 actuator_handler_write(tenu_actuator_type enu_actuator_type ,uint_8 u8_percent_output_val , uint_8 u8_gpio_port ,uint_8 u8_gpio_pin)
{
	sint_16 s16_retval = SUCCESS;

	if(gb_actuator_handler == TRUE)
	{
		switch(enu_actuator_type)
		{
			/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_ACTUATOR
			case HEATER_ACTUATOR:
			{
				if(u8_gpio_port == PWM_PORT)
				{
					s16_retval = heater_actuator_write( u8_percent_output_val  ,  (u8_gpio_pin - PWM_A_CHANNEL));
				}
				else
				{
					s16_retval = ACTUATOR_HANDLER_INVALID_PARAMETER ;
				}
				break;
			}
#endif
			default:
			{
				s16_retval = ACTUATOR_HANDLER_INVALID_PARAMETER ;
				break;
			}
		}
	}
	else
	{
		s16_retval = ACTUATOR_HANDLER_NOT_INITIALIZED_YET ;
	}
	return s16_retval;

}

sint_16 actuator_handler_stop(tenu_actuator_type enu_actuator_type , uint_8 u8_gpio_port ,uint_8 u8_gpio_pin)
{
	sint_16 s16_retval = SUCCESS;

	if(gb_actuator_handler == TRUE)
	{
		switch(enu_actuator_type)
		{
			/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_ACTUATOR
			case HEATER_ACTUATOR_TYP:
			{
				if(u8_gpio_port == PWM_PORT)
				{
					s16_retval = heater_actuator_stop((u8_gpio_pin - PWM_A_CHANNEL));
				}
				else
				{
					s16_retval = ACTUATOR_HANDLER_INVALID_PARAMETER ;
				}
				break;
			}
#endif
			default:
			{
				s16_retval = ACTUATOR_HANDLER_INVALID_PARAMETER ;
				break;
			}
		}
	}
	else
	{
		s16_retval = ACTUATOR_HANDLER_NOT_INITIALIZED_YET ;
	}
	return s16_retval;
}
