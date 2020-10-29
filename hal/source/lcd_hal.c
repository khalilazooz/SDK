/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "lcd_hal.h"
#include "debug.h"

#define LCD_LOG_ENABLE

#ifdef LCD_LOG_ENABLE
#define LCD_LOG(...)              SYS_LOGGER("[LCD_MANG]: "__VA_ARGS__)
#define LCD_LOG_ERR(...)          SYS_LOGGER_ERR("[LCD_MANG]: "__VA_ARGS__)
#define LCD_LOG_WRN(...)          SYS_LOGGER_WRN("[LCD_MANG]: "__VA_ARGS__)
#define LCD_LOG_INFO(...)         SYS_LOGGER_INFO("[LCD_MANG]: "__VA_ARGS__)
#define LCD_LOG_SUCC(...)         SYS_LOGGER_SUCC("[LCD_MANG]: "__VA_ARGS__)
#else
#define LCD_LOG(...)
#define LCD_LOG_ERR(...)
#define LCD_LOG_WRN(...)
#define LCD_LOG_INFO(...)
#define LCD_LOG_SUCC(...)
#endif

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/


/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/
  sint_16	lCD_Init(){
	#if        LCD_MODE    ==  BITS_8
	lcd_command(0x38);
	_delay_ms(1);
	lcd_command(0x0c);
	_delay_ms(1);
	lcd_command(0x01);
	_delay_ms(2);
	lcd_command(0b00000110);
	
	#elif   LCD_MODE  ==   BITS_4
	
	#else
	#error "Wrong LCD MODE!"
	#endif
	return lcd_success;
}
sint_16 lcd_command(uint_8 cmnd)
{
	 gpio_set_pin_value(LCD_Command_Port,RS ,LOW);
	 gpio_set_pin_value(LCD_Command_Port,RW ,LOW);
	gpio_set_port_value(LCD_Data_Port ,cmnd);
	 gpio_set_pin_value(LCD_Command_Port,EN ,HIGH);
	_delay_ms(2);
	 gpio_set_pin_value(LCD_Command_Port,EN ,LOW);
		_delay_ms(2);
		return lcd_success;
}

sint_16 lcd_char(uint_8 char_data)  /* LCD data write function */
{
	 gpio_set_pin_value(LCD_Command_Port,RS ,HIGH);/* RS=1 Data reg. */
	 gpio_set_pin_value(LCD_Command_Port,RW ,LOW);/* RW=0 write operation */
	gpio_set_port_value(LCD_Data_Port ,char_data);
	 gpio_set_pin_value(LCD_Command_Port,EN ,HIGH);/* Enable Pulse */
	_delay_ms(2);
	 gpio_set_pin_value(LCD_Command_Port,EN ,LOW);
	_delay_ms(2);/* Data write delay */
return lcd_success;
}

sint_16 lcd_string(uint_8 *str)		/* Send string to LCD function */
{
	for(int i=0;!str[i];i++)		/* Send each char of string till the NULL */
	{
		lcd_char(str[i]);
	}
	return lcd_success;
}

sint_16 lcd_string_xy(uint_8 row, uint_8 pos, uint_8 *str)  /* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	lcd_command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	lcd_command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	lcd_string(str);		/* Call LCD string function */
return lcd_success;
}

sint_16 lcd_clear(void)
{
	lcd_command (0x01);		/* clear display */
	lcd_command (0x80);		/* cursor at home position */
return lcd_success;
}

sint_16 LCD_cursor_goto(uint_8 copy_u8x,uint_8 copy_u8y)
{
	if(copy_u8x<=16 && copy_u8y<2){
uint_8 first_addres[]={0x80,0xc0};
lcd_command(first_addres[copy_u8y-1]+ copy_u8x-1);
return lcd_success;}
else{
	return lcd_invaled_argument;
}
}

sint_16 lcd_custom_char(uint_8 loc, uint_8 *msg)
{
	uint_8 i;
	if(loc<8)
	{
		lcd_command(0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		lcd_char(msg[i]);
	return lcd_success;
	}
	else{
		return lcd_invaled_argument;
	}

}