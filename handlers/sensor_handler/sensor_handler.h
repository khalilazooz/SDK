/*
 * sensor_handler.h
 *
 *  Created on: Jan 1, 2021
 *      Author: Khalil azooz
 */

#ifndef SENSOR_HANDLER_H_
#define SENSOR_HANDLER_H_

/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define SENSOR_HANDLER_NOT_INITIALIZED_YET 		(SENSOR_HANDLER_ERROR_BASE - 1)

#define SENSOR_HANDLER_INVALID_PARAMETER			(SENSOR_HANDLER_ERROR_BASE - 2)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/
typedef enum _tenu_sensor_type
{
#ifdef HEATER_SENSOR
	HEATER_SENSOR_TYP,
#endif
	INVALID_SENSOR_TYP,
}tenu_sensor_type;

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/

typedef struct _tstr_sensor_info
{
	tenu_sensor_type enu_sensor_type;
	void * pv_sensor_data ;
}tstr_sensor_info;
/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/

sint_16 sensor_handler_init(void);
sint_16 sensor_handler_read(tstr_sensor_info * str_sensor_info , uint_32 * u32_read_val);
sint_16 sensor_handler_calibrate(tstr_sensor_info * str_sensor_info ,uint_32 u32_snsr_rd_1 ,uint_32 u32_snsr_rd_2, uint_32 u32_snsr_cal_rd_1,uint_32 u32_snsr_cal_rd_2);


#endif /* SENSOR_HANDLER_H_ */
