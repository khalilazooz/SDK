/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "adc.h"
#include <avr/io.h>
#include "BIT_MATH.h"
#include "debug.h"
#include "common.h"
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



#define ADC_CHANNELS_NUM				9

#define ADC_POWER_UPDATE_TIME_OUT		100 /*100 * 100ms = 10 sec*/
#define ADC_VBG							1100

#define MINIMUM_ADC_POWER				2000
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_initialized = FALSE;
static uint_16 gu16_adc_vcc = 5000;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
static void adc_start_conversion(uint_8 u8_channel)
{
	if(GET_BIT(ADCSRA,ADSC)== 0)
	{
		u8_channel &= 0x1F; 				/*add mask for channel to not increase than 7*/
		ADMUX = (ADMUX & 0xE0)|u8_channel;
		SET_BIT(ADCSRA,ADSC);
	}
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
		ADC_LOG("ADC PRE DIV BY %d FRQ IS %ld \r\n",(uint_16) POW(2,(enu_adc_pre+1)) , (uint_32) (F_CPU/POW(2,(enu_adc_pre+1))));
		ADC_LOG("conv time %d(us) \r\n",(uint_16)(1000000.0/(float)(F_CPU/POW(2,(enu_adc_pre+1)))) * 13);
	}

	return s16_retval;
}



sint_16 adc_init(tenu_adc_prescaler_mode enu_adc_pre)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_initialized == FALSE)
	{
		 s16_retval = adc_set_prescaler(enu_adc_pre);
		 if(s16_retval == SUCCESS)
		 {
			 gb_initialized = TRUE;
			 // AREF = AVcc
			 ADMUX = (1<<REFS0);
			 ADC_LOG("ADC INITIALIZED SUCCESSFULY \r\n");
		 }
	}
	return s16_retval;
}

sint_16 adc_read(tenu_adc_channel enu_channel,uint_16 * u16_adc_avg_read,uint_8 u8_ntimes)
{
	sint_16 s16_retval = SUCCESS;
	if(enu_channel < ADC_INVALID_CHANNEL && u16_adc_avg_read != NULL && u8_ntimes > 0)
	{
		if(gb_initialized)
		{
			while(GET_BIT(ADCSRA,ADSC) != 0); /*wait until the last read finished*/
			uint_32 u32_adc_read = 0;
			uint_8 u8_time = u8_ntimes;
			while(u8_time > 0)
			{
				adc_start_conversion(enu_channel);
				while(GET_BIT(ADCSRA,ADSC) != 0);
				u8_time --;
				u32_adc_read += ADC ;
			}
			u32_adc_read /= u8_ntimes;
			(*u16_adc_avg_read) = (uint_16)(((float)(u32_adc_read) / 1024.0) * (float) gu16_adc_vcc);

		}
		else
		{
			s16_retval = ADC_NOT_INITIALIZED_YET;
		}
	}
	else
	{
		s16_retval = ADC_INVALID_ARRGUMENTS;
	}
	return s16_retval;
}



sint_16 adc_measure_power_supply_using_vbg(uint_16 * u16_adc_power_read)
{
	sint_16 s16_retval = SUCCESS;
	if(u16_adc_power_read != NULL)
	{
		if(gb_initialized)
		{
			while(GET_BIT(ADCSRA,ADSC) != 0); /*wait until the last read finished*/
			uint_8 u8_ntimes = 10;
			uint_32 u32_adc_read = 0;
			uint_8 u8_time = u8_ntimes;
			while(u8_time > 0)
			{
				adc_start_conversion(ADC_BANDGAP_1_22_V);
				while(GET_BIT(ADCSRA,ADSC) != 0);
				u8_time --;
				u32_adc_read += ADC ;
			}
			u32_adc_read /= u8_ntimes;
			(*u16_adc_power_read) = (uint_16)((1024.0 * (float) ADC_VBG)/ (float) u32_adc_read);
		}
		else
		{
			s16_retval = ADC_NOT_INITIALIZED_YET;
		}
	}
	else
	{
		s16_retval = ADC_INVALID_ARRGUMENTS;
	}
	return s16_retval;
}


sint_16 set_reference_voltage(uint_16 u16_adc_vcc)
{
	sint_16 s16_retval = SUCCESS;
	if(u16_adc_vcc < MINIMUM_ADC_POWER)
	{
		gu16_adc_vcc = u16_adc_vcc;
	}
	else
	{
		s16_retval = ADC_CANNOT_SET_POWER_LESS_THAN_MIN_POWER;
	}
	return s16_retval;
}


uint_16 get_reference_voltage(void)
{
	return gu16_adc_vcc;
}

