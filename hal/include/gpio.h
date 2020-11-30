#ifndef _GPIO_INT_H_
#define _GPIO_INT_H_

#include"Basictypes.h"
#include"BIT_MATH.h"

/*******errors macros***/
#define GPIO_ERROR_BASE					-500
#define GPIO_INVALED_ARGUMENT			GPIO_ERROR_BASE-1
#define GPIO_NOT_SELECTED				GPIO_ERROR_BASE-2
#define GPIO_RE_SELECTED				GPIO_ERROR_BASE-3
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

void gpio_de_selsct_port(uint_8 GPIO_PortID);

void gpio_de_select_pin(uint_8 GPIO_PortID,uint_8 GPIO_PinID);

#endif



