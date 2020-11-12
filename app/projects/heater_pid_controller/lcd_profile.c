/***************************************************************/
/**************             includes               *************/
/***************************************************************/

#include "lcd_profile.h"
#include "lcd_mngr.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/

tstr_row_data row1 = {
	.u8_id = 0,
	.au8_data="SP      ",
	.enu_data_type = DATA_WITH_VARIABLE,
	.u16_var_data = 27,
	.pstr_next_page = NULL,
};

tstr_row_data row2 = {
	.u8_id = 1,
	.au8_data="PV      ",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row3 = {
	.u8_id = 2,
	.au8_data="Config",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row4 = {
	.u8_id = 0,
	.au8_data="Adj SP  ",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row6 = {
	.u8_id = 1,
	.au8_data="Out Type",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row9 = {
	.u8_id = 2,
	.au8_data="Ctr Type",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row5 = {
	.u8_id = 0,
	.au8_data="Adj SP    ",
	.enu_data_type = DATA_WITH_INPUT,
	.u16_var_data = 27,
	.pstr_next_page = NULL,
};

tstr_row_data row7 = {
	.u8_id = 0,
	.au8_data="SSR",
	.enu_data_type = DATA_WITH_ACTION,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row8 = {
	.u8_id = 1,
	.au8_data="RLY",
	.enu_data_type = DATA_WITH_ACTION,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row10 = {
	.u8_id = 0,
	.au8_data="AT",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row13 = {
	.u8_id = 1,
	.au8_data="PID",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row17 = {
	.u8_id = 2,
	.au8_data="ON/OFF",
	.enu_data_type = DATA,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row11 = {
	.u8_id = 0,
	.au8_data="ON            ",
	.enu_data_type = DATA_WITH_ACTION,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row12 = {
	.u8_id = 1,
	.au8_data="OFF           ",
	.enu_data_type = DATA_WITH_ACTION,
	.u16_var_data = 1,
	.pstr_next_page = NULL,
};

tstr_row_data row14 = {
	.u8_id = 0,
	.au8_data="P         ",
	.enu_data_type = DATA_WITH_INPUT,
	.u16_var_data = 1,
	.pstr_next_page = NULL,
};

tstr_row_data row15 = {
	.u8_id = 1,
	.au8_data="I         ",
	.enu_data_type = DATA_WITH_INPUT,
	.u16_var_data = 1,
	.pstr_next_page = NULL,
};

tstr_row_data row16 = {
	.u8_id = 2,
	.au8_data="D         ",
	.enu_data_type = DATA_WITH_INPUT,
	.u16_var_data = 1,
	.pstr_next_page = NULL,
};


const tstr_row_data * a_page1_rows[]= {&row1,&row2,&row3};

tstr_lcd_mangr_inst page1 = {
.pastr_row_data = (tstr_row_data **)a_page1_rows,
.u8_rows_num = 3,
.u8_row_idx = 0,
.u16_time_out = 0,
.pstr_prev_page = NULL,
};


const tstr_row_data * a_Page2_rows[]= {&row4,&row6,&row9};

tstr_lcd_mangr_inst Page2 = {
.pastr_row_data = (tstr_row_data **)a_Page2_rows,
.u8_rows_num = 3,
.u8_row_idx = 0,
.u16_time_out = 200,
.pstr_prev_page = &  page1 ,
};


const tstr_row_data * a_Page3_rows[]= {&row5};

tstr_lcd_mangr_inst Page3 = {
#ifdef LCD_PASSWORD_ENABLE
.enu_page_type = NEED_PASS_PAGE,
#endif
.pastr_row_data = (tstr_row_data **)a_Page3_rows,
.u8_rows_num = 1,
.u8_row_idx = 0,
.u16_time_out = 200,
.pstr_prev_page = & Page2 ,
};


const tstr_row_data * a_Page4_rows[]= {&row7,&row8};

tstr_lcd_mangr_inst Page4 = {
.pastr_row_data = (tstr_row_data **)a_Page4_rows,
.enu_page_type = CHOOSE_PAGE ,
.u8_rows_num = 2,
.u8_row_idx = 0,
.u16_time_out = 200,
.pstr_prev_page = &  Page2 ,
};


const tstr_row_data * a_Page5_rows[]= {&row10,&row13,&row17};

tstr_lcd_mangr_inst Page5 = {
.pastr_row_data = (tstr_row_data **)a_Page5_rows,
.u8_rows_num = 3,
.u8_row_idx = 0,
.u16_time_out = 200,
.pstr_prev_page = &  Page2 ,
};


const tstr_row_data * a_Page6_rows[]= {&row11,&row12};

tstr_lcd_mangr_inst Page6 = {
.enu_page_type = CHOOSE_PAGE ,
.pastr_row_data = (tstr_row_data **)a_Page6_rows,
.u8_rows_num = 2,
.u8_row_idx = 0,
.u16_time_out = 200,
.pstr_prev_page = &  Page5 ,
};


const tstr_row_data * a_Page7_rows[]= {&row14,&row15,&row16};

tstr_lcd_mangr_inst Page7 = {
.pastr_row_data = (tstr_row_data **)a_Page7_rows,
.u8_rows_num = 3,
.u8_row_idx = 0,
.u16_time_out = 200,
.pstr_prev_page = &  Page5 ,
};

tstr_lcd_mangr_inst passpage = {
#ifdef LCD_PASSWORD_ENABLE
	.enu_page_type = CHANGE_PASS_PAGE,
#endif
};

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/





void lcd_profile_init(void){
	row3.pstr_next_page = &Page2;
	row4.pstr_next_page = &Page3;
	row6.pstr_next_page = &Page4;
	row9.pstr_next_page = &Page5;
	row10.pstr_next_page = &Page6;
	row13.pstr_next_page = &Page7;
	row2.pstr_next_page = &passpage;
	lcd_mangr_init(&page1);
	lcd_mangr_battery_charging(TRUE);
}

void lcd_profile_dispatch(void)
{
	lcd_mangr_dispatch();
}