/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include "common.h"
#include "lcd_hal.h"
#include "lcd_mngr.h"
#include "debug.h"
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


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/

static tstr_lcd_mangr_inst * apstr_lcd_mangr[MAX_NUM_OF_PAGES] ;
static uint_16 gu16_page_indx = 0;

static tstr_lcd_mangr_inst str_lcd_mang_current_active = apstr_lcd_mangr[0];
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

void lcd_mngr_add_page(tstr_lcd_mangr_inst * str_lcd_mangr_inst ,uint_8  row1_data[16] ,uint_8  row2_data[16] , tenu_type_of_data row1_data_type , tenu_type_of_data row2_data_type ,uint_16 row1_input_data ,uint_16 row2_input_data ,uint_8 active_port,uint_8 active_pin ,tstr_lcd_mangr_inst * apstr_next_pages[MAX_NUM_OF_PAGES_FOR_EACH_INST],uint_16 timeout)
{
	if(gu16_page_indx < MAX_NUM_OF_PAGES)
	{
		apstr_lcd_mangr[gu16_page_indx] = str_lcd_mangr_inst;
		memcpy(str_lcd_mangr_inst->au8_row1,row1_data ,16);
		memcpy(str_lcd_mangr_inst->au8_row2,row2_data ,16);
		str_lcd_mangr_inst->enu_row1_data_type = row1_data_type ;
		str_lcd_mangr_inst->enu_row2_data_type = row2_data_type ;
		str_lcd_mangr_inst->u16_row1_input_data = row1_input_data ;
		str_lcd_mangr_inst->u16_row2_input_data = row2_input_data ;
		str_lcd_mangr_inst->u8_active_pin = active_pin;
		
		str_lcd_mangr_inst->u8_active_port = active_port;
		
		str_lcd_mangr_inst->u8_page_selector = 0;
		
		str_lcd_mangr_inst->next_pages = apstr_next_pages;
		
		str_lcd_mangr_inst->u16_time_out = timeout;
		
		gu16_page_indx++;
	}
	else
	{
		LCD_LOG_ERR("Exceed The maximum number");
	}
}

void lcd_mangr_init(void)
{
	
}

void dispatch(void)
{
	
	
}