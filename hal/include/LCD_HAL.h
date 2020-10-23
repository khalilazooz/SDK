

#ifndef LCD_H_
#define LCD_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
#include "pins_define.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/





#define LCD_CMD_CLEAR_DISPLAY	          0x01
#define LCD_CMD_CURSOR_HOME		          0x02

// Display control
#define LCD_CMD_DISPLAY_OFF                0x08
#define LCD_CMD_DISPLAY_NO_CURSOR          0x0c
#define LCD_CMD_DISPLAY_CURSOR_NO_BLINK    0x0E
#define LCD_CMD_DISPLAY_CURSOR_BLINK       0x0F

// Function set
#define LCD_CMD_4BIT_2ROW_5X7              0x28
#define LCD_CMD_8BIT_2ROW_5X7              0x38

//functions prototype
void lcd_init(void);
void lcd_send_command (uint_8 );
void lcd_write_character(uint_8 );
void lcd_write_word(uint_8 []);
void lcd_clear(void);
void lcd_set_courser(uint_8,uint_8);
void lcd_goto_xy (uint_8 , uint_8 );



#endif /* LCD_H_ */