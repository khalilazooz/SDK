/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "heater_sensor.h"
#include "common.h"
#include "debug.h"
#include "adc.h"
#include "timer_mngr.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


#define HEATER_SESOR_LOG_ENABLE
#ifdef HEATER_SESOR_LOG_ENABLE
#define HEATER_SESOR_LOG(...)				SYS_LOGGER("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_ERR(...)			SYS_LOGGER_ERR("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_WRN(...)			SYS_LOGGER_WRN("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_INFO(...)			SYS_LOGGER_INFO("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_SUCC(...)			SYS_LOGGER_SUCC("[HS]: "__VA_ARGS__)
#else
#define HEATER_SESOR_LOG(...)
#define HEATER_SESOR_LOG_ERR(...)
#define HEATER_SESOR_LOG_WRN(...)
#define HEATER_SESOR_LOG_INFO(...)
#define HEATER_SESOR_LOG_SUCC(...)
#endif


#define HEATER_SENSOR_MAX_NUM			(8)
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static tpf_heater_sensor_notify		gpf_heater_sensor_notify ;
static bool 						gb_heater_sensor_init  = FALSE ;
static tstr_timer_mgmt_ins 			gstr_heater_timer ;

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

static void adc_cb(void * pv_data ,uint_16 u16_volt_ref,uint_16 u16_adc_read)
{
	uint_32		u32_milli_celsius = 0;
	switch(((tstr_heater_sensor * )pv_data)->str_heater_sensor_conf.enu_heater_sensor_type)
	{
		case HEATER_SENSOR_RTD:
		{
			uint_16 u16_resistance;
			float alpha = (*((tstr_heater_sensor * )pv_data)->str_heater_sensor_conf.uni_sensor_conf.str_rtd.pu16_alpha);
			float ref_res = (float)((tstr_heater_sensor * )pv_data)->str_heater_sensor_conf.uni_sensor_conf.str_rtd.pu16_referance_resistor;
			float zero_res = (float)((tstr_heater_sensor * )pv_data)->str_heater_sensor_conf.uni_sensor_conf.str_rtd.u16_resistor_val ;
			u16_resistance = (uint_16)(((ref_res)*(((float)u16_volt_ref) - ((float)u16_adc_read)))/(float)u16_adc_read);
			u32_milli_celsius = (uint_16)((((float)u16_resistance- zero_res)/( zero_res * alpha))*1000.0);
			break;
		}
		case HEATER_SENSOR_THERMISTOR:
		{


			break;
		}
		case HEATER_SENSOR_THERMOCOUPLE:
		{


			break;
		}
		case HEATER_SENSOR_SEMICONDUCTOR:
		{


			break;
		}
		default :
			break;
	}
	if(gpf_heater_sensor_notify != NULL)
	{
		/*Notify Upper layer with temperature value*/
		gpf_heater_sensor_notify(((tstr_heater_sensor * )pv_data)->u8_sensor_idx,(void * )&u32_milli_celsius);
	}
	//start_timer(&gstr_heater_timer, str_heater_sensor->u16_sensor_read_time, heater_sensor_timer_cb, (void *)str_heater_sensor);
}
static void heater_sensor_timer_cb(void * arg)
{
	tstr_adc_element str_adc_element ;
	str_adc_element.arg_cb = arg ;
	str_adc_element.enu_adc_channel= ((tstr_heater_sensor * )arg)->u8_adc_channel;
	str_adc_element.pf_adc_read_cb = adc_cb;
	adc_read(&str_adc_element);
}
/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/


sint_16 heater_sensor_init(tpf_heater_sensor_notify pf_heater_sensor_notify)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_sensor_init == FALSE)
	{
		if(pf_heater_sensor_notify != NULL)
		{
			gb_heater_sensor_init = TRUE;
			gpf_heater_sensor_notify = pf_heater_sensor_notify;

			u16_retval = adc_init(F_CPU_DIV_128_MODE);
			if(u16_retval == SUCCESS)
			{
				u16_retval = timer_mgmt_init();
			}
		}
		else
		{
			u16_retval = HEATER_SESOR_INVALID_ARGUMENT;
		}
	}
	return u16_retval;
}

sint_16 heater_sensor_add(tstr_heater_sensor const * str_heater_sensor)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_sensor_init != TRUE)
	{
		if((str_heater_sensor != NULL) && (str_heater_sensor->u8_sensor_idx != 0) &&
		   (str_heater_sensor->u8_adc_channel < ADC_INVALID_CHANNEL) && (str_heater_sensor->u16_sensor_read_time != 0) &&
		    (str_heater_sensor->str_heater_sensor_conf.enu_heater_sensor_type < HEATER_SENSOR_INVALID))
		{
			u16_retval = start_timer(&gstr_heater_timer, str_heater_sensor->u16_sensor_read_time, heater_sensor_timer_cb, (void *)str_heater_sensor);
		}
		else
		{
			u16_retval = HEATER_SESOR_INVALID_ARGUMENT ;
		}
	}
	else
	{
		u16_retval = HEATER_SESOR_NOT_INITIALIZED_YET;
	}
	return u16_retval;
}




