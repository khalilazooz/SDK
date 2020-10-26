/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include "common.h"
#include "lcd_hal.h"
#include "lcd_mngr.h"
#include "debug.h"
#include "gpio.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define LCD_MGMT_LOG_ENABLE

#ifdef LCD_MGMT_LOG_ENABLE
#define LCD_LOG(...)				SYS_LOGGER("[LCD]: "__VA_ARGS__)
#define LCD_LOG_ERR(...)			SYS_LOGGER_ERR("[LCD]: "__VA_ARGS__)
#define LCD_LOG_WRN(...)			SYS_LOGGER_WRN("[LCD]: "__VA_ARGS__)
#define LCD_LOG_INFO(...)			SYS_LOGGER_INFO("[LCD]: "__VA_ARGS__)
#define LCD_LOG_SUCC(...)			SYS_LOGGER_SUCC("[LCD]: "__VA_ARGS__)
#else
#define LCD_LOG(...)
#define LCD_LOG_ERR(...)
#define LCD_LOG_WRN(...)
#define LCD_LOG_INFO(...)
#define LCD_LOG_SUCC(...)
#endif

#define SCREEN_ROWS									2
#define SCREEN_TIMEOUT								50 /*5 sec*/
#define SCREEN_LIGHT_OFF_TIMEOUT					300 /*30 sec*/
#define SCREEN_DATA_OFF_TIMEOUT						600 /*60 sec*/


#define IDLE_CODE			0
#define UP_BUTTON			1
#define UP_CODE				1	
#define DOWN_BUTTON			1	
#define DOWN_CODE			2
#define OK_BUTTON			1	
#define SELECT_CODE			3
#define SET_BUTTON			1
#define SET_CODE			4
#define BACK_BUTTON			1
#define BACK_CODE			5
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static tstr_lcd_mangr_inst * gpstr_default_lcd_page = NULL;
static tstr_lcd_mangr_inst * gpstr_current_lcd_page = NULL;
static tstr_row_data * gpstr_current_row = NULL;
static uint_8 gu8_button_state;
static bool gb_need_update = FALSE;
static uint_8 gu8_screen_pointer = 0;
static bool gb_lcd_mangr_init = FALSE;
static bool gb_update= FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
static void lcd_mangr_update(bool need_update)
{
	if (need_update)
	{
		uint_16 u16_i = 0;
		for (u16_i = gpstr_current_lcd_page->u8_row_idx; u16_i < gpstr_current_lcd_page->u8_row_idx + SCREEN_ROWS; u16_i++)
		{
			uint_16 u16_lcd_index = (u16_i - (gpstr_current_lcd_page->u8_row_idx));
			if (gu8_screen_pointer == u16_lcd_index)
			{
				lcd_string_xy(u16_lcd_index,0,">");
			}
			lcd_string_xy(u16_lcd_index,1,gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			LCD_LOG("%s\r\n",gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			if (gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == DATA_WITH_INPUT || gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == DATA_WITH_VARIABLE)
			{
				uint_8 au8_data_buffer[4];
				itoa ((gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data % 10000),au8_data_buffer,10);
				lcd_string(au8_data_buffer);
			}
		}
		gb_update = FALSE;
	}
	else
	{
		/*Do nothing*/
	}
}
/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/



sint_16 lcd_mangr_init(tstr_lcd_mangr_inst * pstr_lcd_header_page)
{
	if (gb_lcd_mangr_init == FALSE)
	{
		if (pstr_lcd_header_page != NULL)
		{
			gb_lcd_mangr_init = TRUE;
			lcd_init();
			gpstr_default_lcd_page = pstr_lcd_header_page;
			gpstr_current_lcd_page = pstr_lcd_header_page;
			lcd_mangr_update(TRUE);
		}
		else
		{
			/*TODO Invalid Arguments*/
		}
	}
	else
	{
		/*TODO Intialized Before*/
	}
	return SUCCESS;
}

sint_16 lcd_mangr_change_row_data(tstr_lcd_mangr_inst * pstr_lcd_page,uint_16 u16_data,uint_8 u8_row_id)
{
	if (pstr_lcd_page != NULL && u16_data != 0 && (pstr_lcd_page->u8_rows_num) >u8_row_id)
	{
		pstr_lcd_page->pastr_row_data[u8_row_id]->u16_var_data = u16_data;
		if (pstr_lcd_page == gpstr_current_lcd_page)
		{
			gb_update = TRUE;
		}
	}
	else
	{
		/*TODO RETURN Invalid Arguments*/
	}
}

void lcd_mangr_dispatch(void)
{
	
	if (UP_BUTTON)
	{
		if (gu8_button_state != UP_CODE)
		{
			gu8_button_state = UP_CODE;
		}
	}
	else if (DOWN_BUTTON)
	{
		if (gu8_button_state != DOWN_CODE)
		{
			gu8_button_state = DOWN_CODE;
		}		
	}
	else if (OK_BUTTON)
	{		
		if (gu8_button_state != SELECT_CODE)
		{
			gu8_button_state = SELECT_CODE;
		}	
	}
	else if (BACK_BUTTON)
	{
		if (gu8_button_state != BACK_CODE)
		{
			gu8_button_state = BACK_CODE;
		}
	}
	else
	{
		gu8_button_state = IDLE_CODE;
	}
	
	lcd_mangr_update(gb_update);
}