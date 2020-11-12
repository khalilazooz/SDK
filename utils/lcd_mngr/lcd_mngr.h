

#ifndef LCD_MNGR_H_
#define LCD_MNGR_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define  LCD_PASSWORD_ENABLE
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
	DATA_WITH_ACTION,
#ifdef LCD_PASSWORD_ENABLE
	PASS_WITH_INPUT,
#endif
	INVALID_DATA,
}tenu_type_of_data;


typedef enum _tenu_battery_level
{
	BATTERY_EMPTY_CHARGE,
	BATTERY_25_PER_CHARGE,
	BATTERY_50_PER_CHARGE,
	BATTERY_75_PER_CHARGE,
	BATTERY_FULL_CHARGE,
	BATTERY_INVALID,
}tenu_battery_level;

typedef enum _tenu_page_type
{
	NORMAL_PAGE,
#ifdef LCD_PASSWORD_ENABLE
	NEED_PASS_PAGE,
	CHANGE_PASS_PAGE,
	ENTER_PASS_PAGE,
#endif
	CHOOSE_PAGE,
	PROCESING_PAGE,
	INVALID_PAGE,
}tenu_page_type;
/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/
typedef struct _tstr_lcd_mangr_inst tstr_lcd_mangr_inst;



typedef struct _tstr_row_data
{
	uint_8 u8_row_gidx;
	uint_8 u8_id;
	uint_8 au8_data[15];
	tenu_type_of_data enu_data_type;
	uint_16 u16_var_data;
	tstr_lcd_mangr_inst * pstr_next_page;	
}tstr_row_data;

typedef struct _tstr_lcd_mangr_inst
{
	tstr_row_data ** pastr_row_data;
	tenu_page_type  enu_page_type;
	uint_8 u8_page_id;
	uint_8 u8_rows_num;
	uint_8 u8_row_idx;
	uint_16 u16_time_out;
	struct _tstr_lcd_mangr_inst * pstr_prev_page;
}tstr_lcd_mangr_inst;



/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/


sint_16 lcd_mangr_init(tstr_lcd_mangr_inst * pstr_lcd_header_page);
void lcd_mangr_battery_charging(bool data);
void lcd_mangr_dispatch(void);
#endif /*LCD_MNGR_H_*/