
#ifndef _BASICTYPES_H_
#define _BASICTYPES_H_

/***************************************************************/
/**************             includes               *************/
/***************************************************************/

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define TRUE				1
#define FALSE				0

#define NULL	((void *)0)














/*Return function state*/
#define SUCCESS						 0
#define ERROR						-1
#define INVALID_ARGUMENT			-2


#define UART_ERROR_BASE				(-100)

#define FLASH_ERROR_BASE			(-200)

#define ADC_ERROR_BASE				(-300)

#define QUEUE_ERROR_BASE			(-400)

#define HEATER_SESOR_ERROR_BASE		(-500)

#define PWM_ERROR_BASE				(-600)

#define HEATER_ACTUATOR_ERROR_BASE  (-700)

#define GPIO_ERROR_BASE				(-800)

#define LED_ERROR_BASE				(-900)

#define ACTUATOR_HANDLER_ERROR_BASE (-1000)

#define SENSOR_HANDLER_ERROR_BASE	(-1100)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/

/***************************************************************/
/**************              Typedef               *************/
/***************************************************************/
typedef unsigned char			uint_8	;
typedef char					sint_8	;

typedef unsigned short int		uint_16	;
typedef signed short int		sint_16	;

typedef unsigned long int		uint_32	;
typedef signed long int			sint_32	;

typedef unsigned long long int	uint_64	;
typedef signed long long int	sint_64	;


typedef unsigned char			bool	;




#endif /*_BASICTYPES_H_*/
