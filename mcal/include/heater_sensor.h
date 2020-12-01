
#ifndef _HEATER_SESOR_
#define _HEATER_SESOR_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


#define HEATER_SESOR_INVALID_ARGUMENT			(HEATER_SESOR_ERROR_BASE-1)
#define HEATER_SESOR_NOT_INITIALIZED_YET		(HEATER_SESOR_ERROR_BASE-2)

/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/

typedef enum _tenu_heater_sensor_type
{
	HEATER_SENSOR_RTD,
	HEATER_SENSOR_THERMISTOR,
	HEATER_SENSOR_THERMOCOUPLE,
	HEATER_SENSOR_SEMICONDUCTOR,
	HEATER_SENSOR_INVALID,
}tenu_heater_sensor_type;

typedef enum _tenu_tc_types
{
	TC_TYPE_K	 = 	0 ,
	TC_TYPE_E	 =  9 ,
	TC_TYPE_J	 =  18	,
	TC_INVALID_TYPE
}tenu_tc_types;

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/

typedef struct _tstr_heater_sensor_conf
{
	tenu_heater_sensor_type enu_heater_sensor_type;
	union
	{
		struct
		{
			uint_16	*	pu16_resistor_val;
			float	*	pu16_alpha;
			uint_16 	u16_referance_resistor;
		}str_rtd;
		struct
		{
			float	*	pfloat_therm_beta;
			uint_16	*	pu16_resistance_25_degree;
			uint_16		u16_referance_resistor;
		}str_therm;
		struct
		{
			float			* thermocouple_d0 ;
			tenu_tc_types	* penu_thermocouple_type ;
		}str_tc;
		struct
		{
			uint_16	 *	pu16_mvoltage_to_temp;
		}str_semi;
	}uni_sensor_conf;
}tstr_heater_sensor_conf;


typedef struct _tstr_heater_sensor
{
	uint_8							u8_sensor_idx;
	uint_8 							u8_adc_channel;
	tstr_heater_sensor_conf			str_heater_sensor_conf;
}tstr_heater_sensor;


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 heater_sensor_init(void);
sint_16 heater_sensor_read(tstr_heater_sensor const * str_heater_sensor,uint_32 * u32_milli_celsius);
#endif /*_HEATER_SESOR_*/




