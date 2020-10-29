

#ifndef LCD_H_
#define LCD_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
#include "pins_define.h"
#include "gpio.h"
#include <util/delay.h>
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define LCD_MODE     BITS_8
#define LOW			0
#define HIGH		1
#define LCD_CLR 		   0x01
#define LCD_RETURNHOME 	   0x02
#define LCD_CURSOR_SHL 	   0x18
#define LCD_CURSOR_SHR 	   0x1c
#define LCD_DISPLAY_SHR    0x05
#define LCD_DISPLAY_SHL    0x07
#define LCD_DISPLAY_OFF    0x08
#define LCD_DISPLAY_ON     0x0c
#define LCD_cursor_OFF     0x0c
#define LCD_cursor_ON      0x0f
#define LCD_start_1stline  0x80
#define LCD_start_2stline  0xc0


/***************************************************************/
/**************       ERRORS MACROS      *************/
/***************************************************************/
#define lcd_error_base		-600
#define lcd_success						lcd_error_base
#define lcd_error						lcd_error_base-1
#define lcd_invaled_argument			lcd_error_base-2
/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/







//functions prototype
sint_16 lCD_Init(void);
sint_16 lcd_custom_char(uint_8 loc, uint_8 *msg);
sint_16 lcd_clear(void);
sint_16 lcd_string_xy (uint_8 row, uint_8 pos, uint_8 *str);
sint_16 lcd_string(uint_8 *str);
sint_16 lcd_char (uint_8 char_data);
sint_16 lcd_command(uint_8 cmnd);
sint_16 LCD_cursor_goto(uint_8 copy_u8x,uint_8 copy_u8y);
#endif /* LCD_H_ */