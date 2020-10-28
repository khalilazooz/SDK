#ifndef _GPIO_INT_H_
#define _GPIO_INT_H_

#include"Basictypes.h"
#include"BIT_MATH.h"
#include"ERROR_STATUS.h"
/******* PORTS ID ******/
#define GPIO_U8_PORT_A 0
#define GPIO_U8_PORT_B 1
#define GPIO_U8_PORT_C 2
#define GPIO_U8_PORT_D 3
#define GPIO_U8_PORT_E 4
#define GPIO_U8_PORT_F 5
#define GPIO_U8_PORT_G 6
/***********************/

/******* PIN ID ********/
#define GPIO_U8_PIN0 0
#define GPIO_U8_PIN1 1
#define GPIO_U8_PIN2 2
#define GPIO_U8_PIN3 3
#define GPIO_U8_PIN4 4
#define GPIO_U8_PIN5 5
#define GPIO_U8_PIN6 6
#define GPIO_U8_PIN7 7
/***********ALLPORT***********/
#define     GPIO_U8_ALL_OUTPUT   0XFF
#define     GPIO_U8_ALL_HIGH   0XFF
#define     GPIO_U8_ALL_INPUT    0
#define     GPIO_U8_ALL_LOW    0
/******* PORT DIRECTION  *******/
#define     GPIO_U8_OUTPUT   1
#define     GPIO_U8_INPUT    0
/*******************************/

/*********PORT VALUE  ********/
#define   GPIO_U8_HIGH     1
#define   GPIO_U8_LOW      0
/*****************************/

/********** GPIO_FUNCTIONS(PORT,PIN,OUTPUT) ************/
ErrorStatus  GPIO_SetPortDirection( uint_8 GPIO_u8PortID,uint_8 GPIO_u8Direction);

ErrorStatus  GPIO_SetPinDirection( uint_8 GPIO_u8PortID,uint_8 GPIO_u8PinID,uint_8 GPIO_u8Direction);

ErrorStatus  GPIO_SetPortValue( uint_8 GPIO_u8PortID,uint_8 GPIO_u8Value);

ErrorStatus  GPIO_SetPinValue( uint_8 GPIO_u8PortID,uint_8 GPIO_u8PinID,uint_8 GPIO_u8Value);

uint_8       GPIO_GetPinValue( uint_8 GPIO_u8PortID,uint_8 GPIO_u8PinID);

#endif
