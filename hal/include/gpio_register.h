
#ifndef _GPIO_REG_H_
#define _GPIO_REG_H_


/*******************   PORTA Registers    *******************/
#define       GPIO_U8_PORTA       *((volatile uint_8 *)0x3B)
#define       GPIO_U8_DDRA        *((volatile uint_8 *)0x3A)
#define       GPIO_U8_PINA        *((volatile uint_8 *)0x39)
/************************************************************/

/*******************   PORTB Registers    *******************/
#define       GPIO_U8_PORTB       *((volatile uint_8 *)0x38)
#define       GPIO_U8_DDRB        *((volatile uint_8 *)0x37)
#define       GPIO_U8_PINB        *((volatile uint_8 *)0x36)
/************************************************************/

/*******************   PORTC Registers    *******************/
#define       GPIO_U8_PORTC       *((volatile uint_8 *)0x35)
#define       GPIO_U8_DDRC        *((volatile uint_8 *)0x34)
#define       GPIO_U8_PINC        *((volatile uint_8 *)0x33)
/************************************************************/

/*******************   PORTD Registers    *******************/
#define       GPIO_U8_PORTD       *((volatile uint_8 *)0x32)
#define       GPIO_U8_DDRD        *((volatile uint_8 *)0x31)
#define       GPIO_U8_PIND        *((volatile uint_8 *)0x30)
/************************************************************/
/*******************   PORTE Registers    *******************/
#define       GPIO_U8_PORTE       *((volatile uint_8 *)0x23)
#define       GPIO_U8_DDRE        *((volatile uint_8 *)0x22)
#define       GPIO_U8_PINE        *((volatile uint_8 *)0x21)
/************************************************************/
/*******************   PORTF Registers    *******************/
#define       GPIO_U8_PORTF       *((volatile uint_8 *)0x62)
#define       GPIO_U8_DDRF        *((volatile uint_8 *)0x61)
#define       GPIO_U8_PINF        *((volatile uint_8 *)0x20)
/************************************************************/
/*******************   PORTG Registers    *******************/
#define       GPIO_U8_PORTG       *((volatile uint_8 *)0x65)
#define       GPIO_U8_DDRG        *((volatile uint_8 *)0x64)
#define       GPIO_U8_PING        *((volatile uint_8 *)0x63)
/************************************************************/
#endif
