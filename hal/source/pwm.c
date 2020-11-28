/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
#include "BIT_MATH.h"
#include "gpio.h"
#include "pwm.h"
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define PWM_LOG_ENABLE
#ifdef PWM_LOG_ENABLE
#define PWM_LOG(...)				SYS_LOGGER("[PWM]: "__VA_ARGS__)
#define PWM_LOG_ERR(...)			SYS_LOGGER_ERR("[PWM]: "__VA_ARGS__)
#define PWM_LOG_WRN(...)			SYS_LOGGER_WRN("[PWM]: "__VA_ARGS__)
#define PWM_LOG_INFO(...)			SYS_LOGGER_INFO("[PWM]: "__VA_ARGS__)
#define PWM_LOG_SUCC(...)			SYS_LOGGER_SUCC("[PWM]: "__VA_ARGS__)
#else
#define PWM_LOG(...)
#define PWM_LOG_ERR(...)
#define PWM_LOG_WRN(...)
#define PWM_LOG_INFO(...)
#define PWM_LOG_SUCC(...)
#endif




#define  WGM0	3
#define  WGM1	6
#define  COM0	4
#define  COM1	5
#define  FCPU_FREQ        8000000
#define  CLOCKS				256
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
static tenu_pwm_prescaler  genu_pwm_prescaler=0;

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_pwm_initialized = FALSE;

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 pwm_init(tenu_pwm_prescaler lenu_pwm_prescaler){
	sint_16 s16_retval = SUCCESS;
	uint_16 u16_pwm_prescaler=0;
	if(gb_pwm_initialized==FALSE){
		if(lenu_pwm_prescaler<PWM_ERROR_PRESCALER)
		{
			switch(lenu_pwm_prescaler){
			case PWM_1_PRESCALER:
			{
				u16_pwm_prescaler=1;
			}
			break;
			case PWM_8_PRESCALER:
			{
				u16_pwm_prescaler=8;
			}
			break;
			case PWM_64_PRESCALER:
			{
				u16_pwm_prescaler=64;
			}
			break;
			case PWM_256_PRESCALER:
			{
				u16_pwm_prescaler=256;
			}
			break;
			case PWM_1024_PRESCALER:
			{
				u16_pwm_prescaler=1024;
			}
			break;
			}
			genu_pwm_prescaler=lenu_pwm_prescaler;
			uint_16 u16_pwm_freq=0;
			u16_pwm_freq=FCPU_FREQ/(CLOCKS*u16_pwm_prescaler);//equation
			PWM_LOG("pwm_freq=%d\r\n",u16_pwm_freq);
			gb_pwm_initialized=TRUE;
			gpio_set_pin_direction(GPIO_PORT_B,GPIO_PIN4,GPIO_OUTPUT);
			TCCR0|=1<<WGM1|1<<WGM0;//FAST PWM MODE
		}
		else{
			s16_retval = pwm_invaled_presc;
			PWM_LOG("prescaler out of range");
		}

	}
	return s16_retval;

}

sint_16  pwm_start(uint_8 u8_pwm_output){
	sint_16 s16_retval = SUCCESS;
	if(gb_pwm_initialized==TRUE){
		if(u8_pwm_output<256 && u8_pwm_output>0){
		uint_8 u8_duty=0;
		u8_duty=((1+u8_pwm_output)/256.0)*100;//equation
		OCR0=u8_pwm_output;
		TCCR0|=genu_pwm_prescaler;
		SET_BIT(TCCR0,COM1);
		CLR_BIT(TCCR0,COM0);//NON INVERTED MODE
		PWM_LOG("duty=%d\r\n",u8_duty);
	}
		else
		{
		s16_retval=pwm_invaled_output;
		}
	}

	else
	{
		s16_retval=pwm_not_init;
	}

return s16_retval;
}

sint_16 pwm_stop(void){
	sint_16 s16_retval = SUCCESS;
	if(gb_pwm_initialized==TRUE){
		CLR_BIT(TCCR0,COM0);
		CLR_BIT(TCCR0,COM1);//DISCONNECTED MODE
		CLR_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);// TIMER NO PRESCALER STOP
	}

	else
	{
		s16_retval=pwm_not_init;
	}

	return s16_retval;
}
