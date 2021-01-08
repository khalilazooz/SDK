/*
 * actuator_handler.h
 *
 *  Created on: Jan 1, 2021
 *      Author: Khalil azooz
 */

#ifndef ACTUATOR_HANDLER_H_
#define ACTUATOR_HANDLER_H_

/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
#include "gpio.h"

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define PWM_PORT					(GPIO_PORTE)
#define PWM_A_CHANNEL				(GPIO_PIN3)
#define PWM_B_CHANNEL				(GPIO_PIN4)
#define PWM_C_CHANNEL				(GPIO_PIN5)

#define ACTUATOR_HANDLER_NOT_INITIALIZED_YET 		(ACTUATOR_HANDLER_ERROR_BASE - 1)

#define ACTUATOR_HANDLER_INVALID_PARAMETER			(ACTUATOR_HANDLER_ERROR_BASE - 2)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/
typedef enum _tenu_actuator_type
{
	/*List All Actuator in the System Under There Building Flag*/
#ifdef HEATER_ACTUATOR
	HEATER_ACTUATOR_TYP,
#endif
	INVALID_ACTUATOR_TYP
}tenu_actuator_type;

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/

sint_16 actuator_handler_init(void);

sint_16 actuator_handler_write(tenu_actuator_type enu_actuator_type  ,uint_8 u8_percent_output_val , uint_8 u8_gpio_port ,uint_8 u8_gpio_pin);

sint_16 actuator_handler_stop(tenu_actuator_type enu_actuator_type  , uint_8 u8_gpio_port ,uint_8 u8_gpio_pin);


#endif /* ACTUATOR_HANDLER_H_ */
