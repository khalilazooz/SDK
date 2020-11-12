/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "lcd_hal.h"
#include "debug.h"
#include "gpio.h"
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
void lcd_command(uint_8 cmnd)
{
	gpio_set_port_value(GPIO_PORT_D,cmnd);
	gpio_set_pin_value(GPIO_PORT_C,RS,GPIO_LOW);	/* RS=0 command reg. */
	gpio_set_pin_value(GPIO_PORT_C,RW,GPIO_LOW);	/* RW=0 Write operation */
	gpio_set_pin_value(GPIO_PORT_C,EN,GPIO_HIGH);	/* Enable pulse */
	_delay_us(1);
	gpio_set_pin_value(GPIO_PORT_C,EN,GPIO_LOW);
	_delay_ms(2);
}

void lcd_char(uint_8 char_data)  /* LCD data write function */
{
	gpio_set_port_value(GPIO_PORT_D,char_data);
	gpio_set_pin_value(GPIO_PORT_C,RS,GPIO_HIGH);	/* RS=1 Data reg. */
	gpio_set_pin_value(GPIO_PORT_C,RW,GPIO_LOW);	/* RW=0 write operation */
	gpio_set_pin_value(GPIO_PORT_C,EN,GPIO_HIGH);	/* Enable Pulse */
	_delay_us(1);
	gpio_set_pin_value(GPIO_PORT_C,EN,GPIO_LOW);
	_delay_ms(2);			/* Data write delay */
}

void lcd_init(void)			/* LCD Initialize function */
{
	gpio_set_port_direction(GPIO_PORT_D,GPIO_ALL_OUTPUT);		/* Make LCD command port direction as o/p */
	gpio_set_pin_direction(GPIO_PORT_C,RS,GPIO_OUTPUT);		/* Make LCD data port direction as o/p */
	gpio_set_pin_direction(GPIO_PORT_C,EN,GPIO_OUTPUT);
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	lcd_command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	lcd_command (0x0C);		/* Display ON Cursor OFF */
	lcd_command (0x06);		/* Auto Increment cursor */
	lcd_command (0x01);		/* clear display */
	_delay_ms(2);			/* Clear display command delay> 1.63 ms */
	lcd_command (0x80);		/* Cursor at home position */
}


void lcd_string(uint_8 *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		lcd_char(str[i]);
	}
}

void lcd_string_xy(uint_8 row, uint_8 pos, uint_8 *str)  /* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	lcd_command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	lcd_command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	lcd_string(str);		/* Call LCD string function */
}

void lcd_clear(void)
{
	lcd_command (0x01);		/* clear display */
	lcd_command (0x80);		/* cursor at home position */
}


void lcd_custom_char(uint_8 loc, uint_8 *msg)
{
	uint_8 i;
	if(loc<8)
	{
		lcd_command(0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)
		{	
			lcd_char(msg[i]);
		}		
	}
}

void lcd_enable_cursor(void)
{
	lcd_command(0x0F);
}

void lcd_disable_cursor(void)
{
	lcd_command (0x0C);
}

void lcd_goto_xy(uint_8 row, uint_8 pos)  /* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	lcd_command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	lcd_command((pos & 0x0F)|0xC0);
}
