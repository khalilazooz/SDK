/***************************************************************/
/**************             includes               *************/
/***************************************************************/

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

#define NEXT										0
#define BACK										1

#define SCREEN_ROWS									2
#define SCREEN_LIGHT_OFF_TIMEOUT					300 /*30 sec*/
#define SCREEN_DATA_OFF_TIMEOUT						600 /*60 sec*/
#define SPEEDY_ACTION_TIME							10
#define POP_UP_TIMEOUT								30
#define BATTERY_CHARGINH_TIMEOUT					5


#define LINK_POINTER_CUST_IDX						6	
#define DOT_MARK_IDX								7
	
#define SELECT_ROW									0
#define UPDATE_VALUE								1
#ifdef LCD_PASSWORD_ENABLE
#define WRITE_PASSWORD								2
#endif
#define MIN(a,b) ((a>b)?(b):(a))

#define IDLE_CODE			0
#define UP_BUTTON			GET_BIT(GPIO_PINF,0)
#define UP_CODE				1	
#define DOWN_BUTTON			GET_BIT(GPIO_PINF,1)	
#define DOWN_CODE			2
#define OK_BUTTON			GET_BIT(GPIO_PINF,2)	
#define SELECT_CODE			3
#define BACK_BUTTON			GET_BIT(GPIO_PINF,3)
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
static tstr_timer_mgmt_ins str_screen_speedy_timeout;
static tstr_timer_mgmt_ins str_pop_up_timeout;
static tstr_timer_mgmt_ins str_battery_chargeing_timeout;
static bool b_pop_up_timeout = FALSE;
static bool b_screen_timeout = FALSE;
static bool b_screen_light_off_timeout = FALSE;
static bool b_screen_data_off_timeout = FALSE;
static bool b_battery_charging_timeout = FALSE;
static bool b_action = FALSE;
static bool b_screen_light_off = FALSE;
static bool b_screen_data_off = FALSE;
static uint_8 gu8_speedy_action = 0;
static tenu_battery_level genu_battery_level = BATTERY_50_PER_CHARGE;

#ifdef LCD_PASSWORD_ENABLE
static uint_16 gu16_password = 0;
static uint_8 u8_lcd_indexer = 4;
tstr_row_data gstr_pass_row1 = {
	.u8_id = 0,
	.au8_data="Plz Enter Pass",
	.enu_data_type = DATA,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};
tstr_row_data gstr_pass_row2 = {
	.u8_id = 0,
	.au8_data="Password:",
	.enu_data_type = PASS_WITH_INPUT,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};
const tstr_row_data * gastr_pass_page_rows[]= {&gstr_pass_row1,&gstr_pass_row2};
tstr_lcd_mangr_inst gstr_password_page = {
				.enu_page_type = ENTER_PASS_PAGE,
				.pastr_row_data = (tstr_row_data **)gastr_pass_page_rows,
				.u8_rows_num = 2,
				.u8_row_idx = 0,
				.u16_time_out = 200,
				.pstr_prev_page = NULL,				
		};
		
tstr_row_data gstr_change_pass_row1 = {
	.u8_id = 0,
	.au8_data="Old PASS:",
	.enu_data_type = PASS_WITH_INPUT,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};
tstr_row_data gstr_change_pass_row2 = {
	.u8_id = 1,
	.au8_data="New PASS:",
	.enu_data_type = PASS_WITH_INPUT,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};
tstr_row_data gstr_change_pass_row3 = {
	.u8_id = 2,
	.au8_data="RE PASS:",
	.enu_data_type = PASS_WITH_INPUT,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};
tstr_row_data gstr_change_pass_row4 = {
	.u8_id = 3,
	.au8_data="Change",
	.enu_data_type = DATA_WITH_ACTION,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};
const tstr_row_data * gastr_change_pass_page_rows[]= {&gstr_change_pass_row1,&gstr_change_pass_row2,&gstr_change_pass_row3 ,&gstr_change_pass_row4};
tstr_lcd_mangr_inst gstr_change_password_page = {
				.pastr_row_data = (tstr_row_data **)gastr_change_pass_page_rows,
				.enu_page_type = CHANGE_PASS_PAGE,
				.u8_rows_num = 4,
				.u8_row_idx = 0,
				.u16_time_out = 200,
				.pstr_prev_page = NULL,				
		};
#endif

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/*Timers Call back functions */
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

static void lcd_mangr_speedy_action_timeout_cb(void *arg)
{
	if (gu8_speedy_action!=255)
	{
		gu8_speedy_action++;
	}
}

static void lcd_mangr_pop_up_timeout_cb(void *arg)
{
	b_pop_up_timeout =TRUE ;
}

static void lcd_mangr_battery_charging_timeout_cb(void *arg)
{
	b_battery_charging_timeout = TRUE ;
}
/*******************************************************************************************************************/

static void lcd_magr_cursor_show(uint_8 pos)
{
	lcd_goto_xy(gu8_screen_pointer, (11 + pos));
	lcd_enable_cursor();
}
static void lcd_mangr_pop_up_massage(sint_8 * row1_str,sint_8 * row2_str)
{
	start_timer(&str_pop_up_timeout,POP_UP_TIMEOUT,lcd_mangr_pop_up_timeout_cb,NULL);
	lcd_clear();
	lcd_string_xy(0,1,(uint_8 *)row1_str);
	lcd_string_xy(1,1,(uint_8 *)row2_str);
}

static void lcd_mangr_custom_char_init(void)
{
	uint_8 battery_empty[] = {0x0E,0x1B,0x11,0x11,0x11,0x11,0x1F,0x00};
	lcd_custom_char(BATTERY_EMPTY_CHARGE,battery_empty);
	uint_8 battery_25_charge[] = {0x0E,0x1B,0x11,0x11,0x11,0x1F,0x1F,0x00};
	lcd_custom_char(BATTERY_25_PER_CHARGE,battery_25_charge);
	uint_8 battery_50_charge[] = {0x0E,0x1B,0x11,0x11,0x1F,0x1F,0x1F,0x00};
	lcd_custom_char(BATTERY_50_PER_CHARGE,battery_50_charge);
	uint_8 battery_75_charge[] = {0x0E,0x1B,0x11,0x1F,0x1F,0x1F,0x1F,0x00};
	lcd_custom_char(BATTERY_75_PER_CHARGE,battery_75_charge);
	uint_8 battery_full_charge[] = {0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00};
	lcd_custom_char(BATTERY_FULL_CHARGE,battery_full_charge);
	uint_8 link_pointer[] = {0x10,0x18,0x1C,0x1E,0x1C,0x18,0x10,0x00};
	lcd_custom_char(LINK_POINTER_CUST_IDX,link_pointer);
	uint_8 dot_mark[] = {0x00,0x0E,0x1F,0x1F,0x1F,0x0E,0x00,0x00};
	lcd_custom_char(DOT_MARK_IDX,dot_mark);
}

static void lcd_mangr_set_battery_level(void)
{
	lcd_goto_xy(0,15);
	lcd_char(genu_battery_level);
}


static void lcd_mangr_move_next(uint_8 u8_to)
{
	if(u8_to == NEXT)
	{
#ifdef LCD_PASSWORD_ENABLE
		if ((gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page)->enu_page_type == CHANGE_PASS_PAGE)
		{
			gstr_change_password_page.pstr_prev_page = gpstr_current_lcd_page;
			gpstr_current_lcd_page = &gstr_change_password_page;
		}
		else
#endif
		{
			gpstr_current_lcd_page = gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page;
		}
		gpstr_current_lcd_page->u8_row_idx = 0 ;
		gu8_screen_pointer = 0;
		if (gpstr_current_lcd_page->u16_time_out != 0)
		{
			start_timer(&str_screen_timeout,gpstr_current_lcd_page->u16_time_out,lcd_mangr_screen_timeout_cb,NULL);
		}
		gb_update = TRUE;
	}
	else
	{
		if (gpstr_current_lcd_page->pstr_prev_page != NULL)
		{
			gpstr_current_lcd_page = gpstr_current_lcd_page->pstr_prev_page;
			gpstr_current_lcd_page->u8_row_idx = 0 ;
			gu8_screen_pointer = 0;
			if (gpstr_current_lcd_page->u16_time_out != 0)
			{
				start_timer(&str_screen_timeout,gpstr_current_lcd_page->u16_time_out,lcd_mangr_screen_timeout_cb,NULL);
			}
			gb_update = TRUE;
		}
	}
	gu8_button_function = SELECT_ROW;
}


#ifdef LCD_PASSWORD_ENABLE
static void lcd_mangr_move_to_pass_page( tstr_lcd_mangr_inst * str_next_page)
{
	gstr_pass_row2.pstr_next_page = str_next_page;
	gstr_password_page.pstr_prev_page= gpstr_current_lcd_page ;
	gpstr_current_lcd_page = &gstr_password_page;
	gu8_screen_pointer = 1;
	gb_update = TRUE;
}
#endif



static void lcd_mangr_update(bool need_update)
{
	if (need_update)
	{
		lcd_clear();
		uint_16 u16_i = 0;
		 
		for (u16_i = gpstr_current_lcd_page->u8_row_idx; u16_i < gpstr_current_lcd_page->u8_row_idx + MIN(SCREEN_ROWS,gpstr_current_lcd_page->u8_rows_num); u16_i++)
		{
			uint_16 u16_lcd_index = (u16_i - (gpstr_current_lcd_page->u8_row_idx));
			if (gu8_screen_pointer == u16_lcd_index)
			{
				if(gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type != DATA_WITH_LINK && gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type !=DATA_WITH_ACTION)
				{
					lcd_string_xy(u16_lcd_index,0,(uint_8*)">");
				}else
				{
					lcd_goto_xy(u16_lcd_index,0);
					lcd_char(LINK_POINTER_CUST_IDX);
				}
			}
			else
			{
				lcd_string_xy(u16_lcd_index,0,(uint_8*)" ");
			}
			lcd_string_xy(u16_lcd_index,1,(uint_8*)gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			//LCD_MANG_LOG("%s\r\n",gpstr_current_lcd_page->pastr_row_data[u16_i]->au8_data);
			if (gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == DATA_WITH_INPUT || gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == DATA_WITH_VARIABLE)
			{
				uint_8 au8_data_buffer[5];
				itoa ((uint_32)(gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data % 10000),(sint_8*)au8_data_buffer,(uint_32)10);
				lcd_string_xy(u16_lcd_index,11,(uint_8*)au8_data_buffer);
			}
#ifdef LCD_PASSWORD_ENABLE
			else if (gpstr_current_lcd_page->pastr_row_data[u16_i]->enu_data_type == PASS_WITH_INPUT)
			{
				lcd_string_xy(u16_lcd_index,11,(uint_8*)"0000");
				if (gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data > 0)
				{
					uint_8 au8_data_buffer[5];
					itoa ((uint_32)(gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data % 10000),(sint_8*)au8_data_buffer,(uint_32)10);
					lcd_string_xy(u16_lcd_index,10+(4-data_log(gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data)),(uint_8*)au8_data_buffer);
				
				}
			}
#endif
			else if(gpstr_current_lcd_page->enu_page_type == CHOOSE_PAGE)
			{
				if (gpstr_current_lcd_page->pastr_row_data[u16_i]->u16_var_data > 0)
				{
					lcd_goto_xy(u16_lcd_index,14);
					lcd_char(DOT_MARK_IDX);
				}
			}
		}
		lcd_mangr_set_battery_level();
		if (gu8_button_function == UPDATE_VALUE)
		{
			lcd_magr_cursor_show(0);
		}
#ifdef LCD_PASSWORD_ENABLE
		else if(gu8_button_function == WRITE_PASSWORD)
		{
			lcd_magr_cursor_show((0==u8_lcd_indexer?3:4-u8_lcd_indexer));
		}
#endif

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
			lcd_mangr_custom_char_init();
			gpstr_default_lcd_page = pstr_lcd_header_page;
			gpstr_current_lcd_page = gpstr_default_lcd_page;
			lcd_mangr_update(TRUE);
			gpio_set_port_direction(GPIO_PORTF,GPIO_ALL_INPUT);
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






void lcd_mangr_battery_charging(bool data)
{
	if (data)
	{
		start_timer(&str_battery_chargeing_timeout,BATTERY_CHARGINH_TIMEOUT,lcd_mangr_battery_charging_timeout_cb,NULL);
	}
	else
	{
		stop_timer(&str_battery_chargeing_timeout);
	}
	
}





















void lcd_mangr_dispatch(void)
{
	
	if (UP_BUTTON)
	{
		if (gu8_button_state != UP_CODE || (gu8_speedy_action > 0))
		{
			start_timer(&str_screen_speedy_timeout,SPEEDY_ACTION_TIME,lcd_mangr_speedy_action_timeout_cb,NULL);
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
				if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data < ( 9999-gu8_speedy_action))
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data += (1 + (gu8_speedy_action));
				}
				else
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data = 9999 ;
				}
				_delay_ms(20);
			}
#ifdef LCD_PASSWORD_ENABLE
			else if (gu8_button_function == WRITE_PASSWORD)
			{
				if ((gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data% data_pow(10,(u8_lcd_indexer)))< (9*data_pow(10,(u8_lcd_indexer-1))))
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data += data_pow(10,(u8_lcd_indexer-1));
				}
			}
#endif
			gu8_button_state = UP_CODE;
		}		
		b_action= TRUE;
	}
	else
	if (DOWN_BUTTON)
	{
		if (gu8_button_state != DOWN_CODE || (gu8_speedy_action > 0))
		{
			start_timer(&str_screen_speedy_timeout,SPEEDY_ACTION_TIME,lcd_mangr_speedy_action_timeout_cb,NULL);
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
				if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data > (0+gu8_speedy_action))
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data -= (1 + (gu8_speedy_action));
				}
				else
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data = 0 ;
				}
			}
#ifdef LCD_PASSWORD_ENABLE
			else if (gu8_button_function == WRITE_PASSWORD)
			{
				if ((gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data% data_pow(10,(u8_lcd_indexer))) > 0)
				{
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data -= data_pow(10,(u8_lcd_indexer-1));
				}
			}
#endif
			gu8_button_state = DOWN_CODE;
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
					lcd_magr_cursor_show(0);
				}
			}
			else if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type == DATA_WITH_LINK)
			{
				if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page != NULL)
				{
#ifdef LCD_PASSWORD_ENABLE
					if ((gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page)->enu_page_type == NEED_PASS_PAGE)
					{
						lcd_mangr_move_to_pass_page(gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->pstr_next_page);
					}
					else
#endif
					{
						lcd_mangr_move_next(NEXT);
					}
					
				}
			}
			else if (gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type == DATA_WITH_ACTION)
			{
	
				if (gpstr_current_lcd_page->enu_page_type == CHOOSE_PAGE)
				{
					uint_8 u8_i = 0;
					for (u8_i = 0 ; u8_i < gpstr_current_lcd_page->u8_rows_num ; u8_i++)
					{
						gpstr_current_lcd_page->pastr_row_data[u8_i]->u16_var_data = 0;
					}
					gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->u16_var_data = 1;
					gb_update= TRUE;
				}
#ifdef LCD_PASSWORD_ENABLE
				else if (gpstr_current_lcd_page->enu_page_type == CHANGE_PASS_PAGE)
				{
					if(gstr_change_pass_row3.u16_var_data != gstr_change_pass_row2.u16_var_data)
					{
						lcd_mangr_pop_up_massage("TWO PASSWORDS","NOT MACHES");
					}
					else if(gstr_change_pass_row1.u16_var_data != gu16_password)
					{
						lcd_mangr_pop_up_massage("OLD PASSWORD","IS WRONG");
					}
					else
					{
						lcd_mangr_pop_up_massage("PASSWORD","CHANGED");
						gu16_password = gstr_change_pass_row3.u16_var_data;
						gstr_change_pass_row1.u16_var_data = 0;
						gstr_change_pass_row2.u16_var_data = 0;
						gstr_change_pass_row3.u16_var_data = 0;
					}
				}
#endif
			}
#ifdef LCD_PASSWORD_ENABLE
			else if(gpstr_current_lcd_page->pastr_row_data[(gpstr_current_lcd_page->u8_row_idx+gu8_screen_pointer)]->enu_data_type == PASS_WITH_INPUT)
			{
				if (u8_lcd_indexer == 0)
				{
					u8_lcd_indexer = 4;
					if (gpstr_current_lcd_page->enu_page_type == ENTER_PASS_PAGE)
					{
						if(gu16_password == gstr_pass_row2.u16_var_data)
						{
							lcd_mangr_move_next(NEXT);
						}
						gstr_pass_row2.u16_var_data = 0;
					}
					if (gpstr_current_lcd_page->enu_page_type == CHANGE_PASS_PAGE)
					{
						lcd_disable_cursor();
						gu8_button_function = SELECT_ROW;
					}
				}
				else if(gu8_button_function == WRITE_PASSWORD)
				{
					u8_lcd_indexer--;
				}		
				else
				{
					gu8_button_function = WRITE_PASSWORD;
				}
				
				gb_update = TRUE;
			}
			else if(gpstr_current_lcd_page->enu_page_type == PASS_WITH_INPUT)
			{
				
			}
#endif
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
					lcd_mangr_move_next(BACK);
				}
			}
			gu8_button_state = BACK_CODE;
		}
		b_action= TRUE;
	}
	else
	{
		gu8_button_state = IDLE_CODE;
		if(gu8_speedy_action > 0)
		{
			stop_timer(&str_screen_speedy_timeout);
			gu8_speedy_action = 0;
		}
		
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
	if(b_pop_up_timeout)
	{
		b_pop_up_timeout = FALSE;
		gb_update = TRUE;
	}
	if (b_battery_charging_timeout)
	{
		b_battery_charging_timeout = FALSE;
		start_timer(&str_battery_chargeing_timeout,BATTERY_CHARGINH_TIMEOUT,lcd_mangr_battery_charging_timeout_cb,NULL);
		genu_battery_level = (genu_battery_level+1)%BATTERY_INVALID;
		lcd_mangr_set_battery_level();
		if (gu8_button_function == UPDATE_VALUE)
		{
			lcd_magr_cursor_show(0);
		}
#ifdef LCD_PASSWORD_ENABLE
		else if(gu8_button_function == WRITE_PASSWORD)
		{
			lcd_magr_cursor_show((0==u8_lcd_indexer?3:4-u8_lcd_indexer));
		}
#endif
	}
			
			
	
	
	lcd_mangr_update(gb_update);
}



