

#ifndef LCD_MNGR_H_
#define LCD_MNGR_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define MAX_NUM_OF_PAGES				10
#define MAX_NUM_OF_PAGES_FOR_EACH_INST	3

/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/
typedef enum _tenu_type_of_data
{
	DATA,
	DATA_WITH_INPUT,
}tenu_type_of_data;


typedef struct _tstr_lcd_mangr_inst
{
	uint_8 au8_row1[16];
	uint_8 au8_row2[16];
	
	uint_16 u16_time_out;
	
	bool b_enable;
	
	tenu_type_of_data enu_row1_data_type;
	tenu_type_of_data enu_row2_data_type;
	
	uint_16 u16_row1_input_data;
	uint_16 u16_row2_input_data;
	
	uint_8 u8_active_port ;
	uint_8 u8_active_pin ;
	
	uint_8 u8_page_selector;
	_tstr_lcd_mangr_inst * next_pages[MAX_NUM_OF_PAGES_FOR_EACH_INST];
}tstr_lcd_mangr_inst;



/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/

#endif /*LCD_MNGR_H_*/