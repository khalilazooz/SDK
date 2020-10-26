/***************************************************************/
/**************             includes               *************/
/***************************************************************/

#include "app.h"
#include "debug.h"
#include "timer_mngr.h"
#include "lcd_mngr.h"
#include "flash.h"
#include <avr/io.h>
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/



/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/


static tstr_timer_mgmt_ins timer1;
static tstr_timer_mgmt_ins timer2;

tstr_row_data g_row1 = {
						.u8_id = 0,
						.au8_data="HI KHALIL ",
						.enu_data_type = DATA_WITH_VARIABLE,
						.u16_var_data = 2,
						.pstr_next_page = NULL,
						};

tstr_row_data g_row2 = {
						.u8_id = 1,
						.au8_data="HI AZOOZ",
						.enu_data_type = DATA,
						.u16_var_data = 3,
						.pstr_next_page = NULL,
						};
tstr_row_data g_row3 = {
						.u8_id = 2,
						.au8_data="HI WORLD",
						.enu_data_type = DATA,
						.u16_var_data = 3,
						.pstr_next_page = NULL,
};
						
tstr_row_data * a_rows[]={&g_row1 , &g_row2, &g_row3};
	
	
tstr_lcd_mangr_inst lcd_inst = {
								.pastr_row_data = a_rows,
								.u8_rows_num = 2,
								.u8_row_idx = 1,
								.u16_time_out = 0,
								.pstr_prev_page = NULL,
								};

bool b_done = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
void t_cb1(void *arg)
{
	lcd_mangr_change_row_data(&lcd_inst,15,0);
}
void t_cb2(void *arg)
{
	b_done = TRUE;
}

/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

void app_init(void)
{
	DDRB = 0xff;
	uint_16 data = 2056;
	
	flash_init();
	lcd_mangr_init(&lcd_inst);
	flash_save(INTERNAL_EEPROM,TEMPERATURE_SET_POINT,(uint_8 *) &data,2);
	timer_mgmt_init();
	start_timer(&timer1,50,t_cb1 , NULL);
	start_timer(&timer2,30,t_cb2 , NULL);
}

void app_dispatch(void)
{
	if(b_done)
	{
		b_done=FALSE;
		uint_16 data = 0;
		flash_load(INTERNAL_EEPROM,TEMPERATURE_SET_POINT,(uint_8 *) &data,2);
		SYS_LOGGER("%d\r\n",data);
	}
	
	lcd_mangr_dispatch();
}