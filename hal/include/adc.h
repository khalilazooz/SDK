
#ifndef _ADC_H_
#define _ADC_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define ADC_INVALID_ARRGUMENTS			(ADC_ERROR_BASE - 1)
#define ADC_NOT_INITIALIZED_YET			(ADC_ERROR_BASE - 2)
#define ADC_LAST_READ_NOT_FINSHED		(ADC_ERROR_BASE - 3)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

typedef void (*tpf_adc_read_cb)(void *,uint_16,uint_16);
/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/

typedef enum _tenu_adc_prescaler_mode
{
	F_CPU_DIV_2_MODE,
	F_CPU_DIV_4_MODE,
	F_CPU_DIV_8_MODE,
	F_CPU_DIV_16_MODE,
	F_CPU_DIV_32_MODE,
	F_CPU_DIV_64_MODE,
	F_CPU_DIV_128_MODE,
	INVALID_MODE,
}tenu_adc_prescaler_mode;



typedef enum _tenu_adc_channel
{
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_INVALID_CHANNEL,
	ADC_BANDGAP_1_22_V = 0x1E,
}tenu_adc_channel;



/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/

typedef struct _tstr_adc_element
{
	tenu_adc_channel enu_adc_channel;
	tpf_adc_read_cb pf_adc_read_cb;
	void * arg_cb ;
}tstr_adc_element;



/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/


sint_16 adc_init(tenu_adc_prescaler_mode enu_adc_pre);
sint_16 adc_set_prescaler(tenu_adc_prescaler_mode enu_adc_pre);
sint_16 adc_read(tstr_adc_element * str_adc_element);
sint_16 adc_measure_power_supply(tpf_adc_read_cb pf_adc_read_cb);
void adc_dispatch(void);
#endif /*_ADC_H_*/





