
#ifndef _ADC_H_
#define _ADC_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define ADC_INVALID_ARRGUMENTS							(ADC_ERROR_BASE - 1)
#define ADC_NOT_INITIALIZED_YET							(ADC_ERROR_BASE - 2)
#define ADC_LAST_READ_NOT_FINSHED						(ADC_ERROR_BASE - 3)
#define ADC_CANNOT_SET_POWER_LESS_THAN_MIN_POWER		(ADC_ERROR_BASE - 4)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

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




/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/


sint_16 adc_init(tenu_adc_prescaler_mode enu_adc_pre);
sint_16 adc_set_prescaler(tenu_adc_prescaler_mode enu_adc_pre);
sint_16 adc_measure_power_supply_using_vbg(uint_16 * u16_adc_power_read);
sint_16 adc_read(tenu_adc_channel enu_channel,uint_16 * u16_adc_avg_read,uint_8 u8_ntimes);
uint_16 get_reference_voltage(void);
void adc_dispatch(void);
#endif /*_ADC_H_*/





