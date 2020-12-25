/***************************************************************/
/**************             includes               *************/
/***************************************************************/

#include "app.h"
#include "debug.h"
#include "timer_mngr.h"
#include "flash.h"
#include "lcd_profile.h"
#include "adc.h"
#include "heater_sensor.h"
#include "gpio.h"
#include "common.h"
#include "heater_actuator.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/



/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static float alpha = 0.005 ;
static uint_16 u16_res_val = 100 ;
static const tstr_heater_sensor str_heater_sensor1 ={.u8_sensor_idx = 1 ,
													.u8_adc_channel = 0,
													.str_heater_sensor_conf =
													{
														.enu_heater_sensor_type = HEATER_SENSOR_RTD,
														.uni_sensor_conf.str_rtd =
														{
															.pu16_resistor_val = &u16_res_val,
															.pu16_alpha = &alpha,
															.u16_referance_resistor = 100 ,
														},
													},
													};

static const tstr_heater_sensor str_heater_sensor2 ={.u8_sensor_idx = 2 ,
													.u8_adc_channel = 1,
													.str_heater_sensor_conf =
													{
														.enu_heater_sensor_type = HEATER_SENSOR_RTD,
														.uni_sensor_conf.str_rtd =
														{
															.pu16_resistor_val = &u16_res_val,
															.pu16_alpha = &alpha,
															.u16_referance_resistor = 100 ,
														},
													},
													};

static float gs16_beta = -3799.42;
static uint_16 gu16_resist = 10000;
static const tstr_heater_sensor str_heater_sensor3 ={.u8_sensor_idx = 3 ,
													.u8_adc_channel = 2,
													.str_heater_sensor_conf =
													{
														.enu_heater_sensor_type = HEATER_SENSOR_THERMISTOR,
														.uni_sensor_conf.str_therm =
														{
															.pfloat_therm_beta = &gs16_beta,
															.pu16_resistance_25_degree = &gu16_resist,
															.u16_referance_resistor = 10000 ,
														},
													},
													};

static tenu_tc_types tenu_tc_type = TC_TYPE_E;
static float thermocouple_d0 = 0;
static const tstr_heater_sensor str_heater_sensor4 ={.u8_sensor_idx = 4 ,
													.u8_adc_channel = 3,
													.str_heater_sensor_conf =
													{
														.enu_heater_sensor_type = HEATER_SENSOR_THERMOCOUPLE,
														.uni_sensor_conf.str_tc =
														{
															.thermocouple_d0   =  &thermocouple_d0,
															.penu_thermocouple_type = &tenu_tc_type,
														},
													},
													};
static uint_16 mv_t = 10;

static const tstr_heater_sensor str_heater_sensor5 ={.u8_sensor_idx = 5 ,
													.u8_adc_channel = 4,
													.str_heater_sensor_conf =
													{
														.enu_heater_sensor_type = HEATER_SENSOR_SEMICONDUCTOR,
														.uni_sensor_conf.str_semi =
														{
															.pu16_mvoltage_to_temp = &mv_t,
														},
													},
													};

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
	uint_16 data = 2056;
	uint_32 sensor_data = 0;

	SYS_LOGGER("%d\r\n",heater_actuator_init());
	SYS_LOGGER("%d\r\n",heater_actuator_write(20, HA_OUTPUT_A));
	SYS_LOGGER("%d\r\n",heater_actuator_write(50, HA_OUTPUT_B));
	SYS_LOGGER("%d\r\n",heater_actuator_write(70, HA_OUTPUT_C));
	SYS_LOGGER("%d\r\n",heater_actuator_write(101, HA_OUTPUT_C));

	lcd_profile_init();
	SYS_LOGGER("%d\r\n",heater_sensor_init());
	SYS_LOGGER("%d\r\n",heater_sensor_read(&str_heater_sensor3, &sensor_data));
	SYS_LOGGER("%lu\r\n",sensor_data);
	SYS_LOGGER("beta = %d\r\n",(sint_16)gs16_beta);
	SYS_LOGGER("%d\r\n",heater_sensor_calibrate(&str_heater_sensor3,48005,34756,10000,30000));
	SYS_LOGGER("beta = %d\r\n",(sint_16)gs16_beta);
	SYS_LOGGER("gu16_resist = %ld\r\n",(uint_32)gu16_resist);


	SYS_LOGGER("%d\r\n",heater_sensor_read(&str_heater_sensor3, &sensor_data));
	SYS_LOGGER("%lu\r\n",sensor_data);
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
	lcd_profile_dispatch();
}
