/***************************************************************/
/**************             includes               *************/
/***************************************************************/

#include "app.h"
#include "debug.h"
#include "timer_mngr.h"
#include "flash.h"
#include "lcd_profile.h"
#include <avr/io.h>
#include "adc.h"
#include "heater_sensor.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/



/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static float alpha = 0.0003596 ;
static const tstr_heater_sensor str_heater_sensor1 ={.u8_sensor_idx = 1 ,
													.u8_adc_channel = 0,
													.str_heater_sensor_conf =
													{
														.enu_heater_sensor_type = HEATER_SENSOR_RTD,
														.uni_sensor_conf.str_rtd =
														{
															.u16_resistor_val = 100 ,
															.pu16_alpha = &alpha,
															.pu16_referance_resistor = 1000 ,
														},
													},
													.u16_sensor_read_time = 50 ,
													};

static tstr_timer_mgmt_ins timer1;
static tstr_timer_mgmt_ins timer2;

bool b_done = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
static void heater_sensor_notify(uint_8 u8_sensor_idx,void * pv_data)
{
	SYS_LOGGER("id = %d temp = %ld\r\n",u8_sensor_idx,*((uint_32 *)pv_data));
}

void t_cb1(void *arg)
{

}
void t_cb2(void *arg)
{
	b_done = TRUE;
	PORTB = 0xff;
}


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

void app_init(void)
{
	DDRB = 0xff;
	uint_16 data = 2056;

	lcd_profile_init();
	SYS_LOGGER("%d\r\n",heater_sensor_init(heater_sensor_notify));
	SYS_LOGGER("%d\r\n",heater_sensor_add(&str_heater_sensor1));
	flash_init();
	flash_save(INTERNAL_EEPROM,TEMPERATURE_SET_POINT,(uint_8 *) &data,2);
	timer_mgmt_init();
	start_timer(&timer1,51,t_cb1 , NULL);
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
	adc_dispatch();
	lcd_profile_dispatch();
}
