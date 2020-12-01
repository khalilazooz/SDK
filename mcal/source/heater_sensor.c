/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "heater_sensor.h"
#include "common.h"
#include "debug.h"
#include "adc.h"

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


#define HEATER_SESOR_LOG_ENABLE
#ifdef HEATER_SESOR_LOG_ENABLE
#define HEATER_SESOR_LOG(...)				SYS_LOGGER("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_ERR(...)			SYS_LOGGER_ERR("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_WRN(...)			SYS_LOGGER_WRN("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_INFO(...)			SYS_LOGGER_INFO("[HS]: "__VA_ARGS__)
#define HEATER_SESOR_LOG_SUCC(...)			SYS_LOGGER_SUCC("[HS]: "__VA_ARGS__)
#else
#define HEATER_SESOR_LOG(...)
#define HEATER_SESOR_LOG_ERR(...)
#define HEATER_SESOR_LOG_WRN(...)
#define HEATER_SESOR_LOG_INFO(...)
#define HEATER_SESOR_LOG_SUCC(...)
#endif


#define D1(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+1])
#define D2(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+2])
#define D3(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+3])
#define D4(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+4])
#define D5(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+5])
#define D6(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+6])
#define D7(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+7])
#define D8(TC_TYPE)							(gadouble_temperture_coefficients[TC_TYPE+8])

#define HEATER_SENSOR_MAX_NUM				(8)
#define THERM_FOLLOWED_RESISTANCE_DEGREE	(25.0)
#define CELSIUS_TO_KELVIN(DATA)				(DATA + 273.15)

#define THERMOCOUPLE_GAIN					(1000.0)
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
static const double gadouble_temperture_coefficients[] =
{
		/*Type K Coefficients*/
		0 ,25.08355		 	, 0.07860106		 	, -0.2503131		 	, 0.08315270			 ,
		-0.01228034		 	, 0.0009804036		 	, -0.00004413030	 	, 0.000001057734		 ,
		/*Type E Coefficients*/
		0 ,17.057035	 	, -0.23301759		 	, 	0.0065435585		 	, -.000073562749	 	 ,
		-0.0000017896001 	, 0.000000084036165 	, -0.0000000013735879	, 0.000000000010629823	 ,
		/*Type J Coefficients*/
		0 , 19.78425		, -0.2001204			, 0.01036969			, -0.0002549687			 ,
		0.000003585153 		, -0.00000005344285		, 0.0000000005099890 	, 0						 ,
};

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool 						gb_heater_sensor_init  = FALSE ;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/


sint_16 heater_sensor_init(void)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_sensor_init == FALSE)
	{
			gb_heater_sensor_init = TRUE;
			u16_retval = adc_init(F_CPU_DIV_128_MODE);
	}
	return u16_retval;
}

sint_16 heater_sensor_read(tstr_heater_sensor const * str_heater_sensor,uint_32 * u32_milli_celsius)
{
	sint_16 u16_retval = SUCCESS;
	if(gb_heater_sensor_init == TRUE)
	{
		if((str_heater_sensor != NULL) && (str_heater_sensor->u8_adc_channel < ADC_INVALID_CHANNEL)
				&& (str_heater_sensor->str_heater_sensor_conf.enu_heater_sensor_type < HEATER_SENSOR_INVALID))
		{
			*u32_milli_celsius = 0;
			uint_16 u16_adc_read ;
			uint_16 u16_volt_ref;
			u16_volt_ref = get_reference_voltage();
			adc_read(str_heater_sensor->u8_adc_channel,&u16_adc_read,10);

			switch(str_heater_sensor->str_heater_sensor_conf.enu_heater_sensor_type)
			{
				case HEATER_SENSOR_RTD:
				{
					float u16_resistance;
					float alpha = (*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_rtd.pu16_alpha));
					float ref_res = (float)(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_rtd.u16_referance_resistor);
					float zero_res = (float)(*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_rtd.pu16_resistor_val)) ;
					u16_resistance = (((ref_res)*((float)u16_adc_read))/((float)u16_volt_ref - ((float)u16_adc_read)));
					*(u32_milli_celsius) = (uint_32)(((u16_resistance- zero_res)/(zero_res * alpha))*(1000.0));
					break;
				}
				case HEATER_SENSOR_THERMISTOR:
				{
					float u16_resistance;
					float beta = (float)(*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_therm.pfloat_therm_beta));
					float ref_res = (float)(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_therm.u16_referance_resistor);
					float resistance_25_degree = (float)(*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_therm.pu16_resistance_25_degree));
					u16_resistance = (((ref_res)*((float)u16_adc_read))/((float)u16_volt_ref - ((float)u16_adc_read)));
					*(u32_milli_celsius) = (uint_32)((((beta*CELSIUS_TO_KELVIN(THERM_FOLLOWED_RESISTANCE_DEGREE))/((LN((float)u16_resistance/resistance_25_degree)*CELSIUS_TO_KELVIN(THERM_FOLLOWED_RESISTANCE_DEGREE))+beta))-CELSIUS_TO_KELVIN(1.0))*1000.0);
					break;
				}
				case HEATER_SENSOR_THERMOCOUPLE:
				{

					tenu_tc_types tc_type = (*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_tc.penu_thermocouple_type));
					double D0 = (*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_tc.thermocouple_d0));
					double E = (double)u16_adc_read/THERMOCOUPLE_GAIN ;

					*(u32_milli_celsius) =
							(uint_32)((
							(D0)+
							(D1(tc_type) * POW(E,1)) +
							(D2(tc_type) * POW(E,2)) +
							(D3(tc_type) * POW(E,3)) +
							(D4(tc_type) * POW(E,4)) +
							(D5(tc_type) * POW(E,5)) +
							(D6(tc_type) * POW(E,6)) +
							(D7(tc_type) * POW(E,7)) +
							(D8(tc_type) * POW(E,8)))*1000);
					break;
				}
				case HEATER_SENSOR_SEMICONDUCTOR:
				{
					float mv_t = (float)(*(str_heater_sensor->str_heater_sensor_conf.uni_sensor_conf.str_semi.pu16_mvoltage_to_temp));
					*(u32_milli_celsius) = (uint_32)(((float)u16_adc_read/mv_t)*1000.0);
					break;
				}
				default :
					break;
			}

		}
		else
		{
			u16_retval = HEATER_SESOR_INVALID_ARGUMENT ;
		}
	}
	else
	{
		u16_retval = HEATER_SESOR_NOT_INITIALIZED_YET;
	}
	return u16_retval;
}

sint_16 heater_sensor_calibrate(tstr_heater_sensor_conf * str_heater_sensor)
{
	sint_16 u16_retval = SUCCESS;
	switch(str_heater_sensor->enu_heater_sensor_type)
	{
		case HEATER_SENSOR_RTD:
		{

			break;
		}
		case HEATER_SENSOR_THERMISTOR:
		{

			break;
		}
		case HEATER_SENSOR_THERMOCOUPLE:
		{

			break;
		}
		case HEATER_SENSOR_SEMICONDUCTOR:
		{

			break;
		}
		default :
			break;
	}
	return u16_retval;
}
