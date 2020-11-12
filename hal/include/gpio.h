#ifndef _GPIO_INT_H_
#define _GPIO_INT_H_

#include "Basictypes.h"
#include "BIT_MATH.h"
#include "gpio_register.h"
/*******errors macros***/
#define gpio_error_base				-500
#define gpio_success						gpio_error_base
#define gpio_error						gpio_error_base-1
#define gpio_invaled_argument			gpio_error_base-2

/******* PORTS ID ******/
#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2
#define GPIO_PORT_D 3
#define GPIO_PORT_E 4
#define GPIO_PORT_F 5
#define GPIO_PORT_G 6
/***********************/

/******* PIN ID ********/
#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7
/***********ALLPORT***********/
#define     GPIO_ALL_OUTPUT   0XFF
#define     GPIO_ALL_HIGH   0XFF
#define     GPIO_ALL_INPUT    0
#define     GPIO_ALL_LOW    0
/******* PORT DIRECTION  *******/
#define     GPIO_OUTPUT   1
#define     GPIO_INPUT    0
/*******************************/

/*********PORT VALUE  ********/
#define   GPIO_HIGH     1
#define   GPIO_LOW      0
/*****************************/

/********** GPIO_FUNCTIONS(PORT,PIN,OUTPUT) ************/
sint_16  gpio_set_port_direction( uint_8 GPIO_PortID,uint_8 GPIO_Direction);

sint_16  gpio_set_pin_direction( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Direction);

sint_16  gpio_set_port_value( uint_8 GPIO_PortID,uint_8 GPIO_Value);

sint_16  gpio_set_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Value);

sint_16  gpio_get_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8*p);

#endif


