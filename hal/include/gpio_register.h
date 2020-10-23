
#ifndef _DIO_REG_H_
#define _DIO_REG_H_


/*******************   PORTA Registers    *******************/
#define       DIO_U8_PORTA       *((volatile u8 *)0x3B)
#define       DIO_U8_DDRA        *((volatile u8 *)0x3A)
#define       DIO_U8_PINA        *((volatile u8 *)0x39)
/************************************************************/

/*******************   PORTB Registers    *******************/
#define       DIO_U8_PORTB       *((volatile u8 *)0x38)
#define       DIO_U8_DDRB        *((volatile u8 *)0x37)
#define       DIO_U8_PINB        *((volatile u8 *)0x36)
/************************************************************/

/*******************   PORTC Registers    *******************/
#define       DIO_U8_PORTC       *((volatile u8 *)0x35)
#define       DIO_U8_DDRC        *((volatile u8 *)0x34)
#define       DIO_U8_PINC        *((volatile u8 *)0x33)
/************************************************************/

/*******************   PORTD Registers    *******************/
#define       DIO_U8_PORTD       *((volatile u8 *)0x32)
#define       DIO_U8_DDRD        *((volatile u8 *)0x31)
#define       DIO_U8_PIND        *((volatile u8 *)0x30)
/************************************************************/
/*******************   PORTE Registers    *******************/
#define       DIO_U8_PORTE       *((volatile u8 *)0x23)
#define       DIO_U8_DDRE        *((volatile u8 *)0x22)
#define       DIO_U8_PINE        *((volatile u8 *)0x21)
/************************************************************/
/*******************   PORTF Registers    *******************/
#define       DIO_U8_PORTF       *((volatile u8 *)0x62)
#define       DIO_U8_DDRF        *((volatile u8 *)0x61)
#define       DIO_U8_PINF        *((volatile u8 *)0x20)
/************************************************************/
/*******************   PORTG Registers    *******************/
#define       DIO_U8_PORTG       *((volatile u8 *)0x65)
#define       DIO_U8_DDRG        *((volatile u8 *)0x64)
#define       DIO_U8_PING        *((volatile u8 *)0x63)
/************************************************************/
#endif
