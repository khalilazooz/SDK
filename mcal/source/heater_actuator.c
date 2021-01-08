/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "heater_actuator.h"
#include "pwm.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_heater_actuator_init;

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 heater_actuator_init(void)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_actuator_init == FALSE)
	{
		gb_heater_actuator_init = TRUE;
		u16_retval = pwm_init(PWM_64_PRESCALER);
	}
	return u16_retval;
}

sint_16 heater_actuator_write(uint_8 u8_heater_pwr  , tenu_heater_actuator_output enu_heater_actuator_output)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_actuator_init)
	{
		if((u8_heater_pwr > 0 && u8_heater_pwr <= 100) && enu_heater_actuator_output < HA_OUTPUT_INVALID)
		{
			/*Mapping Power Percent To 256 register value*/
			uint_8 u8_duty = (uint_8)(256.0 *((float)u8_heater_pwr/100.0));
			u16_retval = pwm_start(u8_duty , (tenu_pwm_output) enu_heater_actuator_output);
		}
		else
		{
			u16_retval = HEATER_ACTUATOR_INVALID_PARAMETER;
		}
	}
	else
	{
		u16_retval = HEATER_ACTUATOR_NOT_INTIALIZED_YET ;
	}
	return u16_retval;
}


sint_16 heater_actuator_stop(tenu_heater_actuator_output enu_heater_actuator_output)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_actuator_init)
	{
		if(enu_heater_actuator_output < HA_OUTPUT_INVALID )
		{

			u16_retval = pwm_stop((tenu_pwm_output) enu_heater_actuator_output);
		}
		else
		{
			u16_retval = HEATER_ACTUATOR_INVALID_PARAMETER;
		}
	}
	else
	{
		u16_retval = HEATER_ACTUATOR_NOT_INTIALIZED_YET ;
	}
	return u16_retval;
}
