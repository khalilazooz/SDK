/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "lcd_hal.h"
#include "lcd_mngr.h"
#include "debug.h"
#include "gpio.h"
#include "timer_mngr.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define LCD_MGMT_LOG_ENABLE

#ifdef LCD_MGMT_LOG_ENABLE
#define LCD_MANG_LOG(...)				SYS_LOGGER("[LCD_MANG]: "__VA_ARGS__)
#define LCD_MANG_LOG_ERR(...)			SYS_LOGGER_ERR("[LCD_MANG]: "__VA_ARGS__)
#define LCD_MANG_LOG_WRN(...)			SYS_LOGGER_WRN("[LCD_MANG]: "__VA_ARGS__)
#define LCD_MANG_LOG_INFO(...)			SYS_LOGGER_INFO("[LCD_MANG]: "__VA_ARGS__)
#define LCD_MANG_LOG_SUCC(...)			SYS_LOGGER_SUCC("[LCD_MANG]: "__VA_ARGS__)
#else
#define LCD_MANG_LOG(...)
#define LCD_MANG_LOG_ERR(...)
#define LCD_MANG_LOG_WRN(...)
#define LCD_MANG_LOG_INFO(...)
#define LCD_MANG_LOG_SUCC(...)
#endif

#define SCREEN_ROWS									2
#define SCREEN_LIGHT_OFF_TIMEOUT					300 /*30 sec*/
#define SCREEN_DATA_OFF_TIMEOUT						600 /*60 sec*/

#define SELECT_ROW									0
#define UPDATE_VALUE								1
#define GET_BIT(REGISTER,BIT_NO) ((REGISTER>>BIT_NO)&1)
#define MIN(a,b) ((a>b)?(b):(a))

#define IDLE_CODE			0
#define UP_BUTTON			GET_BIT(PING,0)
#define UP_CODE				1	
#define DOWN_BUTTON			GET_BIT(PING,1)
#define DOWN_CODE			2
#define OK_BUTTON			GET_BIT(PING,2)
#define SELECT_CODE			3
#define BACK_BUTTON			GET_BIT(PING,3)
#define BACK_CODE			4
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static tstr_lcd_mangr_inst * gpstr_default_lcd_page = NULL;
static tstr_lcd_mangr_inst * gpstr_current_lcd_page = NULL;
static uint_8 gu8_button_state;
static uint_8 gu8_screen_pointer = 0;
static uint_16 gu16_current_value= 0;
static bool gb_lcd_mangr_init = FALSE;
static bool gb_update= FALSE;
static uint_8 gu8_button_function = SELECT_ROW;
static tstr_timer_mgmt_ins str_screen_timeout;
static tstr_timer_mgmt_ins str_screen_light_off_timeout;
static tstr_timer_mgmt_ins str_screen_data_off_timeout;
static bool b_screen_timeout = FALSE;
static bool b_screen_light_off_timeout = FALSE;
static bool b_screen_data_off_timeout = FALSE;
static bool b_action = FALSE;
static bool b_screen_light_off = FALSE;
static bool b_screen_data_off = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

static void lcd_mangr_screen_timeout_cb(void * arg)
{
	b_screen_timeout = TRUE;
}
static void lcd_mangr_screen_light_off_timeout_cb(void * arg)
{
	b_screen_light_off_timeout = TRUE;
	b_screen_light_off = TRUE;
}
static void lcd_mangr_screen_data_off_timeout_cb(void * arg)
{
	b_screen_data_off_timeout = TRUE;
	b_screen_data_off = TRUE;
}

static void lcd_magr_cursor_show(void)
{
	uint_8 u8_blinking_pos = strlen((const sint_8 *)gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->au8_data) + 1;
	lcd_goto_xy(gu8_screen_pointer, u8_blinking_pos);
	lcd_enable_cursor();
}


static void lcd_mangr_update(bool need_update)
{
	if (need_update)
	{
		lcd_clear();
		uint_16 u16_i = 0;
		 
		for (u16_i = gpstr_current_lcd_page->u8_row_idx; u16_i < gpstr_current_lcd_page->u8_row_idx + MIN(SCREEN_ROWS,gpstr_current_lcd_page->u8_rows_num); u16_i++)
		{
			uint_8 u8_data_len = 0;
			uint_8 u8_input_len = 0;
			uint_16 u16_lcd_index = (u16_i - (gpstr_current_lcd_page->u8_row_idx));
			if (gu8_screen_pointer == u16_lcd_index)
			{
				lcd_string_xy(u16_lcd_index,0,(uint_8*)">");
			}
			else
			{
				lcd_string_xy(u16_lcd_index,0,(uint_8*)" ");
			}
			lcd_string_xy(u16_lcd_index,1,(uint_8*)gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			u8_data_len = strlen((const sint_8 *)gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			//LCD_MANG_LOG("%s\r\n",gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			if (gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == DATA_WITH_INPUT || gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == DATA_WITH_VARIABLE)
			{
				uint_8 au8_data_buffer[4];
				itoa ((uint_32)(gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data % 10000),(sint_8*)au8_data_buffer,(uint_32)10);
				u8_input_len = strlen((const sint_8 *)au8_data_buffer);
				if ((u8_input_len+u8_data_len)-2 < 15)
				{
					lcd_string((uint_8*)au8_data_buffer);
				}
			}
		}
		
		if (gu8_button_function == UPDATE_VALUE)
		{
			lcd_magr_cursor_show();
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
			gpstr_current_lcd_page = gpstr_default_lcd_page;
			lcd_mangr_update(TRUE);
			DDRG = 0x00;
			timer_mgmt_init();
			start_timer(&str_screen_light_off_timeout,SCREEN_LIGHT_OFF_TIMEOUT,lcd_mangr_screen_light_off_timeout_cb,NULL);
			start_timer(&str_screen_data_off_timeout,SCREEN_DATA_OFF_TIMEOUT,lcd_mangr_screen_data_off_timeout_cb,NULL);
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
	return SUCCESS;
}

void lcd_mangr_dispatch(void)
{
	
	if (UP_BUTTON)
	{
		if (gu8_button_state != DOWN_CODE)
		{
			gb_update = TRUE;
			if (gu8_button_function == SELECT_ROW)
			{
				if (gu8_screen_pointer == 1)
				{
					gu8_screen_pointer = 0;
				}
				else if (gu8_screen_pointer == 0 && gpstr_current_lcd_page->u8_row_idx != 0)
				{
					gpstr_current_lcd_page->u8_row_idx--;
				}
				else
				{
					gb_update = FALSE;
				}
			}
			else if (gu8_button_function == UPDATE_VALUE)
			{		
				if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data != 9999)
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data++;
				}
				else
				{
					gb_update = FALSE;
				}
			}
			gu8_button_state = DOWN_CODE;
		}		
		b_action= TRUE;
	}
	else
	if (DOWN_BUTTON)
	{
		if (gu8_button_state != UP_CODE)
		{
			gb_update = TRUE;
			if (gu8_button_function == SELECT_ROW)
			{
				if (gu8_screen_pointer == 0)
				{
					if (gpstr_current_lcd_page->u8_rows_num > 1)
					{
						gu8_screen_pointer = 1;
					}
				}
				else if (gu8_screen_pointer == 1 && gpstr_current_lcd_page->u8_row_idx < (gpstr_current_lcd_page->u8_rows_num-2))
				{
					gpstr_current_lcd_page->u8_row_idx++;
				}
				else
				{
					gb_update = FALSE;
				}
			}
			else if (gu8_button_function == UPDATE_VALUE)
			{
				if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data != 0)
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data--;
				}
				else
				{
					gb_update = FALSE;
				}
			}
			
			gu8_button_state = UP_CODE;
		}
		b_action= TRUE;
	}
	else if (OK_BUTTON)
	{		
		if (gu8_button_state != SELECT_CODE)
		{
			if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type == DATA_WITH_INPUT)
			{
				if (gu8_button_function == UPDATE_VALUE)
				{
					gu8_button_function = SELECT_ROW;
					lcd_disable_cursor();
				}
				else
				{
					gu8_button_function = UPDATE_VALUE;
					gu16_current_value = gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data;
					lcd_magr_cursor_show();
				}
			}
			else if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type == DATA_WITH_LINK)
			{
				if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page != NULL)
				{
					gpstr_current_lcd_page = gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page;
					gpstr_current_lcd_page->u8_row_idx = 0 ;
					gu8_screen_pointer = 0;
					if (gpstr_current_lcd_page->u16_time_out != 0)
					{
						start_timer(&str_screen_timeout,gpstr_current_lcd_page->u16_time_out,lcd_mangr_screen_timeout_cb,NULL);
					}
					gb_update = TRUE;
				}
			}
			gu8_button_state = SELECT_CODE;
		}	
		b_action= TRUE;
	}
	else if (BACK_BUTTON)
	{
		if (gu8_button_state != BACK_CODE)
		{
			if (gu8_button_function == UPDATE_VALUE)
			{
				gu8_button_function = SELECT_ROW;
				lcd_disable_cursor();
				gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data = gu16_current_value;
				gb_update = TRUE;
			}
			else
			{
				if (gpstr_current_lcd_page->pstr_prev_page != NULL)
				{
					gpstr_current_lcd_page = gpstr_current_lcd_page->pstr_prev_page;
					gpstr_current_lcd_page->u8_row_idx = 0 ;
					gu8_screen_pointer = 0;
					gb_update = TRUE;
				}
			}
			gu8_button_state = BACK_CODE;
		}
		b_action= TRUE;
	}
	else
	{
		gu8_button_state = IDLE_CODE;
	}
	if(b_action)
	{
		b_action = FALSE;
		if (gpstr_current_lcd_page !=  gpstr_default_lcd_page)
		{
			reset_timer(&str_screen_timeout);
		}
		if(b_screen_light_off)
		{
			b_screen_light_off = FALSE;
			start_timer(&str_screen_light_off_timeout,SCREEN_LIGHT_OFF_TIMEOUT,lcd_mangr_screen_light_off_timeout_cb,NULL);
			LCD_MANG_LOG("LIGHT ON\r\n");
		}
		else
		{
			reset_timer(&str_screen_light_off_timeout);
		}
		
		if(b_screen_data_off)
		{
			b_screen_data_off = FALSE;
			start_timer(&str_screen_data_off_timeout,SCREEN_DATA_OFF_TIMEOUT,lcd_mangr_screen_data_off_timeout_cb,NULL);
			LCD_MANG_LOG("SCREEN ON\r\n");
		}
		else
		{
			reset_timer(&str_screen_data_off_timeout);
		}	
	}
	if (b_screen_timeout)
	{
		b_screen_timeout = FALSE;
		if (gpstr_current_lcd_page !=  gpstr_default_lcd_page)
		{
			lcd_disable_cursor();
			gu8_button_function = SELECT_ROW;
			gpstr_current_lcd_page = gpstr_default_lcd_page;
			gpstr_current_lcd_page->u8_row_idx = 0 ;
			gu8_screen_pointer = 0;
			gb_update = TRUE;
		}
	}
	if (b_screen_light_off_timeout)
	{
		b_screen_light_off_timeout = FALSE;
		LCD_MANG_LOG("LIGHT OFF\r\n");
	}
	
	if (b_screen_data_off_timeout)
	{
		b_screen_data_off_timeout = FALSE;
		LCD_MANG_LOG("SCREEN OFF\r\n");
	}
	
	lcd_mangr_update(gb_update);
}

