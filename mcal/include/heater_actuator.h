
#ifndef _HEATER_ACTUATOR_H_
#define _HEATER_ACTUATOR_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define HEATER_ACTUATOR_INVALID_PARAMETER			(HEATER_ACTUATOR_ERROR_BASE-1)
#define HEATER_ACTUATOR_NOT_INTIALIZED_YET			(HEATER_ACTUATOR_ERROR_BASE-2)

/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/
typedef enum  _tenu_heater_actuator_output
{
	HA_OUTPUT_A,
	HA_OUTPUT_B,
	HA_OUTPUT_C,
	HA_OUTPUT_INVALID
}tenu_heater_actuator_output;

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 heater_actuator_init(void);
sint_16 heater_actuator_write(uint_8 u8_heater_pwr  , tenu_heater_actuator_output enu_heater_actuator_output);
sint_16 heater_actuator_stop(tenu_heater_actuator_output enu_heater_actuator_output);
#endif /*_HEATER_ACTUATOR_H_*/





