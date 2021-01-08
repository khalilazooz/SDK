/*
 * sensor_handler.c
 *
 *  Created on: Jan 1, 2021
 *      Author: Khalil azooz
 */



/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "sensor_handler.h"
#include "heater_sensor.h"
#include "common.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
static bool gb_sensor_handler = FALSE;


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

sint_16 sensor_handler_init(void)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_sensor_handler == FALSE)
	{
		do
		{
			/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_SENSOR
			s16_retval = heater_sensor_init();
			ERROR_BREAK(s16_retval);
#endif
		}while(0);
	}
	return s16_retval;
}

sint_16 sensor_handler_read(tstr_sensor_info * str_sensor_info , uint_32 * u32_read_val)
{
	sint_16 s16_retval = SUCCESS;

	if(gb_sensor_handler == TRUE)
	{
		if(str_sensor_info != NULL)
		{
			switch(str_sensor_info->enu_sensor_type)
			{
				/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_SENSOR
				case HEATER_SENSOR_TYP:
				{
					s16_retval = heater_sensor_read((tstr_heater_sensor const * )(str_sensor_info->pv_sensor_data) ,u32_read_val);
					break;
				}
#endif
				default:
				{
					s16_retval = SENSOR_HANDLER_INVALID_PARAMETER ;
					break;
				}
			}
		}
		else
		{
			s16_retval = SENSOR_HANDLER_INVALID_PARAMETER ;
		}
	}
	else
	{
		s16_retval = SENSOR_HANDLER_NOT_INITIALIZED_YET ;
	}
	return s16_retval;

}

sint_16 sensor_handler_calibrate(tstr_sensor_info * str_sensor_info ,uint_32 u32_snsr_rd_1 ,uint_32 u32_snsr_rd_2, uint_32 u32_snsr_cal_rd_1,uint_32 u32_snsr_cal_rd_2)
{
	sint_16 s16_retval = SUCCESS;

	if(gb_sensor_handler == TRUE)
	{
		if(str_sensor_info != NULL)
		{
			switch(str_sensor_info->enu_sensor_type)
			{
				/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_SENSOR
				case HEATER_SENSOR_TYP:
				{
					s16_retval = heater_sensor_calibrate((tstr_heater_sensor const *)(str_sensor_info->pv_sensor_data),uint_32 u32_snsr_rd_1 ,uint_32 u32_snsr_rd_2, uint_32 u32_snsr_cal_rd_1,uint_32 u32_snsr_cal_rd_2);
					break;
				}
#endif
				default:
				{
					s16_retval = SENSOR_HANDLER_INVALID_PARAMETER ;
					break;
				}
			}
		}
		else
		{
			s16_retval = SENSOR_HANDLER_INVALID_PARAMETER ;
		}
	}
	else
	{
		s16_retval = SENSOR_HANDLER_NOT_INITIALIZED_YET ;
	}
	return s16_retval;

}
