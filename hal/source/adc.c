/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "adc.h"
#include <avr/io.h>
#include "BIT_MATH.h"
#include "debug.h"
#include "queue.h"
#include "common.h"
#include "timer_mngr.h"
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



#define ADC_CHANNELS_NUM		9

#define ADC_POWER_UPDATE_TIME_OUT		100 /*100 * 100ms = 10 sec*/
#define ADC_VBG							1100
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_initialized = FALSE;
static tstr_queue gstr_adc_queue ;
static tstr_adc_element gastr_adc_channels[ADC_CHANNELS_NUM];
static uint_8 gu8_num_of_conversion = 0;
static uint_16 gu16_adc_vcc = 5000;
static tstr_timer_mgmt_ins gstr_adc_power_update_timer;
static bool gb_adc_power_update_timer_fire = FALSE ;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

static void adc_power_update(void *arg,uint_16 u16_adc_vcc_old,uint_16 u16_adc_vcc_new)
{
	gu16_adc_vcc = u16_adc_vcc_new ;
}

static void adc_power_update_timeout(void * arg)
{
	gb_adc_power_update_timer_fire = TRUE;
}

static void adc_start_conversion(uint_8 u8_channel)
{
	if(GET_BIT(ADCSRA,ADSC)== 0)
	{
		u8_channel &= 0x1F; 				/*add mask for channel to not increase than 7*/
		ADMUX = (ADMUX & 0xE0)|u8_channel;
		SET_BIT(ADCSRA,ADSC);
	}
}


static void adc_read_channel(void)
{
	if(gu8_num_of_conversion > 0 && GET_BIT(ADCSRA,ADSC) == 0)
	{
		sint_16 s16_retval;
		tstr_adc_element str_adc_element;
		s16_retval = queue_dequeue(&gstr_adc_queue, (void *)&str_adc_element);
		if(s16_retval == SUCCESS)
		{
			uint_16 u16_adc_val_mv;
			if(str_adc_element.enu_adc_channel != ADC_BANDGAP_1_22_V)
			{

				u16_adc_val_mv = (uint_16)(((float)ADC / 1024.0) * (float) gu16_adc_vcc);
			}
			else
			{
				u16_adc_val_mv = (uint_16)((1024.0 * (float) ADC_VBG)/ (float) ADC);
			}
			str_adc_element.pf_adc_read_cb(str_adc_element.arg_cb,gu16_adc_vcc,u16_adc_val_mv);
			gu8_num_of_conversion--;
			if(gu8_num_of_conversion > 0)
			{
				s16_retval = queue_get_fornt(&gstr_adc_queue, (void *)&str_adc_element);
				if(s16_retval == SUCCESS)
				{
					if(str_adc_element.enu_adc_channel != ADC_BANDGAP_1_22_V)
					{
						adc_start_conversion((uint_8)str_adc_element.enu_adc_channel);
					}
					else
					{
						adc_start_conversion((uint_8)ADC_BANDGAP_1_22_V);
					}
				}
			}
		}

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

			 timer_mgmt_init();

			 start_timer(&gstr_adc_power_update_timer, ADC_POWER_UPDATE_TIME_OUT, adc_power_update_timeout,  NULL);
			 // AREF = AVcc
			 ADMUX = (1<<REFS0);
			 gb_initialized = TRUE;

			 /*ADC init queue for adc channels*/
			 s16_retval = queue_init(&gstr_adc_queue, (uint_8 *)gastr_adc_channels , ADC_CHANNELS_NUM, sizeof(tstr_adc_element));

			 adc_measure_power_supply(adc_power_update);


			 ADC_LOG("ADC INITIALIZED SUCCESSFULY \r\n");
		 }
	}
	return s16_retval;
}


sint_16 adc_read(tstr_adc_element * str_adc_element)
{
	sint_16 s16_retval = SUCCESS;
	if(str_adc_element != NULL && str_adc_element->pf_adc_read_cb != NULL && str_adc_element->enu_adc_channel <= ADC_CHANNEL_7)
	{
		if(gb_initialized)
		{
			bool b_found = FALSE;
			queue_element_existance(&gstr_adc_queue,(void *)str_adc_element,&b_found);
			if(!b_found)
			{
				if(gu8_num_of_conversion == 0)
				{
					adc_start_conversion(str_adc_element->enu_adc_channel);
				}
				queue_enqueue(&gstr_adc_queue,(void *)str_adc_element);
				gu8_num_of_conversion++;
			}
			else
			{
				s16_retval = ADC_LAST_READ_NOT_FINSHED ;
			}
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


sint_16 adc_measure_power_supply(tpf_adc_read_cb pf_adc_read_cb)
{
	sint_16 s16_retval = SUCCESS;
	if(pf_adc_read_cb != NULL)
	{
		if(gb_initialized)
		{
			bool b_found = FALSE;
			tstr_adc_element str_adc_element ;
			str_adc_element.enu_adc_channel = ADC_BANDGAP_1_22_V ;
			str_adc_element.pf_adc_read_cb = pf_adc_read_cb;
			queue_element_existance(&gstr_adc_queue,(void *)&str_adc_element,&b_found);
			if(!b_found)
			{
				if(gu8_num_of_conversion == 0)
				{
					adc_start_conversion(ADC_BANDGAP_1_22_V);
				}
				queue_enqueue(&gstr_adc_queue,(void *)&str_adc_element);
				gu8_num_of_conversion++;
			}
			else
			{
				s16_retval = ADC_LAST_READ_NOT_FINSHED ;
			}
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

void adc_dispatch(void)
{
	adc_read_channel();

	if(gb_adc_power_update_timer_fire == TRUE)
	{
		gb_adc_power_update_timer_fire = FALSE ;
		adc_measure_power_supply(adc_power_update);
		start_timer(&gstr_adc_power_update_timer, ADC_POWER_UPDATE_TIME_OUT, adc_power_update_timeout,  NULL);
	}
}

