
#ifndef _GPIO_REG_H_
#define _GPIO_REG_H_


/*******************   PORTA Registers    *******************/
#define       GPIO_PORTA       (*((volatile uint_8 *)0x3B))
#define       GPIO_DDRA        (*((volatile uint_8 *)0x3A))
#define       GPIO_PINA        (*((volatile uint_8 *)0x39))
/************************************************************/

/*******************   PORTB Registers    *******************/
#define       GPIO_PORTB       (*((volatile uint_8 *)0x38))
#define       GPIO_DDRB        (*((volatile uint_8 *)0x37))
#define       GPIO_PINB        (*((volatile uint_8 *)0x36))
/************************************************************/

/*******************   PORTC Registers    *******************/
#define       GPIO_PORTC       (*((volatile uint_8 *)0x35))
#define       GPIO_DDRC        (*((volatile uint_8 *)0x34))
#define       GPIO_PINC        (*((volatile uint_8 *)0x33))
/************************************************************/

/*******************   PORTD Registers    *******************/
#define       GPIO_PORTD       (*((volatile uint_8 *)0x32))
#define       GPIO_DDRD        (*((volatile uint_8 *)0x31))
#define       GPIO_PIND        (*((volatile uint_8 *)0x30))
/************************************************************/
/*******************   PORTE Registers    *******************/
#define       GPIO_PORTE       *((volatile uint_8 *)0x23)
#define       GPIO_DDRE        *((volatile uint_8 *)0x22)
#define       GPIO_PINE        *((volatile uint_8 *)0x21)
/************************************************************/
/*******************   PORTF Registers    *******************/
#define       GPIO_PORTF       *((volatile uint_8 *)0x62)
#define       GPIO_DDRF        *((volatile uint_8 *)0x61)
#define       GPIO_PINF        *((volatile uint_8 *)0x20)
/************************************************************/
/*******************   PORTG Registers    *******************/
#define       GPIO_PORTG       *((volatile uint_8 *)0x65)
#define       GPIO_DDRG        *((volatile uint_8 *)0x64)
#define       GPIO_PING        *((volatile uint_8 *)0x63)
/************************************************************/
#endif
