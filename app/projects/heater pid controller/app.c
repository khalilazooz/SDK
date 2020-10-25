/***************************************************************/
/**************             includes               *************/
/***************************************************************/

#include "app.h"
#include "debug.h"
#include "timer_mngr.h"
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
bool b_done = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
void t_cb1(void *arg)
{
	
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
}