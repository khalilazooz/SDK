#ifndef _GPIO_H_
#define _GPIO_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include"Basictypes.h"
#include"BIT_MATH.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define GPIO_INVALED_ARGUMENT	(GPIO_ERROR_BASE-1)
#define GPIO_PIN_RESEVED		(GPIO_ERROR_BASE-2)
#define GPIO_PIN_NOT_SELECTED	(GPIO_ERROR_BASE-3)
#define GPIO_NOT_INTIALIZED		(GPIO_ERROR_BASE-4)

/******* PORTS ID ******/
#define GPIO_PORTA 				(0)
#define GPIO_PORTB 				(1)
#define GPIO_PORTC 				(2)
#define GPIO_PORTD 				(3)
#define GPIO_PORTE 				(4)
#define GPIO_PORTF 				(5)
#define GPIO_PORTG 				(6)
#define INVALID_PORT			(7)
/***********************/

/******* PIN ID ********/
#define GPIO_PIN0 				(0)
#define GPIO_PIN1 				(1)
#define GPIO_PIN2 				(2)
#define GPIO_PIN3 				(3)
#define GPIO_PIN4 				(4)
#define GPIO_PIN5 				(5)
#define GPIO_PIN6 				(6)
#define GPIO_PIN7 				(7)
#define INVALID_PIN				(8)

/***********ALLPORT***********/
#define     GPIO_ALL_OUTPUT   	(0XFF)
#define     GPIO_ALL_HIGH   	(0XFF)
#define     GPIO_ALL_INPUT    	(0)
#define     GPIO_ALL_LOW    	(0)
/******* PORT DIRECTION  *******/
#define     GPIO_OUTPUT   		(1)
#define     GPIO_INPUT    		(0)
/*******************************/

/*********PORT VALUE  ********/
#define   GPIO_HIGH     		(1)
#define   GPIO_LOW      		(0)
/*****************************/


/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/

sint_16 gpio_init(void);

sint_16 gpio_select(uint_8 u8_gpio_port,uint_8 u8_gpio_pin);


sint_16 gpio_deselect(uint_8 u8_gpio_port,uint_8 u8_gpio_pin);

sint_16 gpio_set_port_direction( uint_8 u8_gpio_port,uint_8 u8_gpio_direction);

sint_16 gpio_set_pin_direction( uint_8 u8_gpio_port,uint_8 u8_gpio_pin,bool b_gpio_direction);

sint_16 gpio_set_port_value( uint_8 u8_gpio_port,uint_8 u8_portval);

sint_16 gpio_set_pin_value( uint_8 u8_gpio_port,uint_8 u8_gpio_pin,bool b_pinval);

sint_16 gpio_toggle(uint_8 u8_gpio_port,uint_8 u8_gpio_pin);

sint_16 gpio_get_pin_value( uint_8 u8_gpio_port,uint_8 u8_gpio_pin,bool* pb_pinval);

#endif /*_GPIO_H_*/


