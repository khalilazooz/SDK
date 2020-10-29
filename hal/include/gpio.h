#ifndef _GPIO_INT_H_
#define _GPIO_INT_H_

#include"Basictypes.h"
#include"BIT_MATH.h"
#include"ERROR_STATUS.h"
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
ErrorStatus  gpio_set_port_direction( uint_8 GPIO_PortID,uint_8 GPIO_Direction);

ErrorStatus  gpio_set_pin_direction( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Direction);

ErrorStatus  gpio_set_port_value( uint_8 GPIO_PortID,uint_8 GPIO_Value);

ErrorStatus  gpio_set_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Value);

uint_8       gpio_get_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID);

#endif
