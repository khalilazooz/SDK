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
	.au8_data="",
	.enu_data_type = DATA,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row2 = {
	.u8_id = 1,
	.au8_data="",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row3 = {
	.u8_id = 2,
	.au8_data="",
	.enu_data_type = DATA_WITH_LINK,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row4 = {
	.u8_id = 0,
	.au8_data="",
	.enu_data_type = DATA,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row6 = {
	.u8_id = 1,
	.au8_data="",
	.enu_data_type = DATA,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row5 = {
	.u8_id = 0,
	.au8_data="",
	.enu_data_type = DATA,
	.u16_var_data = 0,
	.pstr_next_page = NULL,
};

tstr_row_data row7 = {
	.u8_id = 1,
	.au8_data="",
	.enu_data_type = DATA,
	.u16_var_data = 0,
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


const tstr_row_data * a_Page2_rows[]= {&row4,&row6};

tstr_lcd_mangr_inst Page2 = {
.pastr_row_data = (tstr_row_data **)a_Page2_rows,
.u8_rows_num = 2,
.u8_row_idx = 0,
.u16_time_out = 0,
.pstr_prev_page = &  page1 ,
};


const tstr_row_data * a_Page3_rows[]= {&row5,&row7};

tstr_lcd_mangr_inst Page3 = {
.pastr_row_data = (tstr_row_data **)a_Page3_rows,
.u8_rows_num = 2,
.u8_row_idx = 0,
.u16_time_out = 0,
.pstr_prev_page = &  page1 ,
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
	row2.pstr_next_page = &Page2;
	row3.pstr_next_page = &Page3;
	lcd_mangr_init(&page1);
}

void lcd_profile_dispatch(void)
{
	lcd_mangr_dispatch();
}