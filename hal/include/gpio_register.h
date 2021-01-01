
#ifndef _GPIO_REG_H_
#define _GPIO_REG_H_


/*******************   PORTA Registers    *******************/
#define       PORTA       *((volatile uint_8 *)0x3B)
#define       DDRA        *((volatile uint_8 *)0x3A)
#define       PINA        *((volatile uint_8 *)0x39)
/************************************************************/

/*******************   PORTB Registers    *******************/
#define       PORTB       *((volatile uint_8 *)0x38)
#define       DDRB        *((volatile uint_8 *)0x37)
#define       PINB        *((volatile uint_8 *)0x36)
/************************************************************/

/*******************   PORTC Registers    *******************/
#define       PORTC       *((volatile uint_8 *)0x35)
#define       DDRC        *((volatile uint_8 *)0x34)
#define       PINC        *((volatile uint_8 *)0x33)
/************************************************************/

/*******************   PORTD Registers    *******************/
#define       PORTD       *((volatile uint_8 *)0x32)
#define       DDRD        *((volatile uint_8 *)0x31)
#define       PIND        *((volatile uint_8 *)0x30)
/************************************************************/
/*******************   PORTE Registers    *******************/
#define       PORTE       *((volatile uint_8 *)0x23)
#define       DDRE        *((volatile uint_8 *)0x22)
#define       PINE        *((volatile uint_8 *)0x21)
/************************************************************/
/*******************   PORTF Registers    *******************/
#define       PORTF       *((volatile uint_8 *)0x62)
#define       DDRF        *((volatile uint_8 *)0x61)
#define       PINF        *((volatile uint_8 *)0x20)
/************************************************************/
/*******************   PORTG Registers    *******************/
#define       PORTG       *((volatile uint_8 *)0x65)
#define       DDRG        *((volatile uint_8 *)0x64)
#define       PING        *((volatile uint_8 *)0x63)
/************************************************************/
#endif
