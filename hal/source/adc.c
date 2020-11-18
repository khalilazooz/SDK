/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "adc.h"
#include <avr/io.h>
#include <math.h>
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define ADC_LOG_ENABLE
#ifdef ADC_LOG_ENABLE
#define ADC_LOG(...)				SYS_LOGGER("[ADC]: "__VA_ARGS__)
#define ADC_LOG_ERR(...)			SYS_LOGGER_ERR("[ADC]: "__VA_ARGS__)
#define ADC_LOG_WRN(...)			SYS_LOGGER_WRN("[ADC]: "__VA_ARGS__)
#define ADC_LOG_INFO(...)			SYS_LOGGER_INFO("[ADC]: "__VA_ARGS__)
#define ADC_LOG_SUCC(...)			SYS_LOGGER_SUCC("[ADC]: "__VA_ARGS__)
#else
#define ADC_LOG(...)
#define ADC_LOG_ERR(...)
#define ADC_LOG_WRN(...)
#define ADC_LOG_INFO(...)
#define ADC_LOG_SUCC(...)
#endif
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_initialized = FALSE;
static tstr_adc_element gastr_adc_element[10]={0};
static uint_16 gu16_queue_idx = 0;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
static void adc_calculate_ms()
{

}


static void adc_read_channel(tenu_adc_channel enu_adc_channel)
{

}
/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/



sint_16 adc_set_prescaler(tenu_adc_prescaler_mode enu_adc_pre)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_initialized)
	{
		switch(enu_adc_pre)
		{
			case F_CPU_DIV_2_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS0);
			}
			break;
			case F_CPU_DIV_4_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS1);
			}
			break;
			case F_CPU_DIV_8_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
			}
			break;
			case F_CPU_DIV_16_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS2);
			}
			break;
			case F_CPU_DIV_32_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);
			}
			break;
			case F_CPU_DIV_64_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
			}
			break;
			case F_CPU_DIV_128_MODE:
			{
				ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

			}
			break;
			default:
			{
				s16_retval = ADC_INVALID_ARRGUMENTS;
			}
			break;
		}
		if(s16_retval != ADC_INVALID_ARRGUMENTS)
		{
			ADC_LOG("ADC PRESCALER DEVIDED BY %d AND ADC FRQ IS %d",pow(2,(enu_adc_pre+1)) , (F_CPU/pow(2,(enu_adc_pre+1))));
			ADC_LOG_INFO("CONVERSION TIME WILL BE %d(us)",(uint_16)(1000000.0/(float)(F_CPU/pow(2,(enu_adc_pre+1)))) * 13);
		}
	}
	else
	{
		s16_retval = ADC_NOT_INITIALIZED_YET;
	}
	return s16_retval;
}


sint_16 adc_measure_power_supply(tpf_adc_read_cb pf_adc_read_cb)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_initialized)
	{
		gastr_adc_element[gu16_queue_idx].pf_adc_read_cb = pf_adc_read_cb;
		gastr_adc_element[gu16_queue_idx].enu_adc_channel = ADC_BANDGAP_1_22_V;
		gu16_queue_idx++;
	}
	else
	{
		s16_retval = ADC_NOT_INITIALIZED_YET;
	}
	return s16_retval;
}


sint_16 adc_init(tenu_adc_prescaler_mode enu_adc_pre)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_initialized == FALSE)
	{
		gb_initialized = TRUE;
		 // AREF = AVcc
		 ADMUX = (1<<REFS0);
		 s16_retval = adc_set_prescaler(enu_adc_pre);
		 if(s16_retval == SUCCESS)
		 {
			 ADC_LOG("ADC INITIALIZED SUCCESSFULY \r\n");
		 }
	}
	return s16_retval;
}


void adc_dispatch(void)
{




}

