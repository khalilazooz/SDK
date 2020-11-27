
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
typedef void (*tpf_heater_sensor_notify)(uint_8,void *);

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
			uint_16		u16_resistor_val;
			float	*	pu16_alpha;
			uint_16 	pu16_referance_resistor;
		}str_rtd;
		struct
		{
			uint_16		u16_resistor_val;
			uint_16		resistance_to_tmep;
		}str_therm;
		struct
		{
			uint_16		mvoltage_to_temp;
		}str_tc;
		struct
		{
			uint_16		mvoltage_to_temp;
		}str_semi;
	}uni_sensor_conf;
}tstr_heater_sensor_conf;


typedef struct _tstr_heater_sensor
{
	uint_8							u8_sensor_idx;
	uint_8 							u8_adc_channel;
	tstr_heater_sensor_conf			str_heater_sensor_conf;
	uint_16 						u16_sensor_read_time;
}tstr_heater_sensor;


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 heater_sensor_init(tpf_heater_sensor_notify pf_heater_sensor_notify);
sint_16 heater_sensor_add(tstr_heater_sensor const * str_heater_sensor);
#endif /*_HEATER_SESOR_*/




