

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
/**************					Enumes		       *************/
/***************************************************************/
typedef enum _tenu_type_of_data
{
	DATA,
	DATA_WITH_INPUT,
	DATA_WITH_VARIABLE,
	DATA_WITH_LINK,
	INVALID_DATA,
}tenu_type_of_data;

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/
typedef struct _tstr_lcd_mangr_inst tstr_lcd_mangr_inst;



typedef struct _tstr_row_data
{
	uint_8 u8_id;
	uint_8 au8_data[15];
	tenu_type_of_data enu_data_type;
	uint_16 u16_var_data;
	tstr_lcd_mangr_inst * pstr_next_page;	
}tstr_row_data;

typedef struct _tstr_lcd_mangr_inst
{
	tstr_row_data ** pastr_row_data;
	uint_8 u8_rows_num;
	uint_8 u8_row_idx;
	uint_16 u16_time_out;
	struct _tstr_lcd_mangr_inst *pstr_prev_page;
}tstr_lcd_mangr_inst;



/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/


sint_16 lcd_mangr_init(tstr_lcd_mangr_inst * pstr_lcd_header_page);
sint_16 lcd_mangr_change_row_data(tstr_lcd_mangr_inst * pstr_lcd_page,uint_16 u16_data,uint_8 u8_row_id);
void lcd_mangr_dispatch(void);
#endif /*LCD_MNGR_H_*/