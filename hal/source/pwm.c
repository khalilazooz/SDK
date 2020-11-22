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

/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
uint_8 gint_prs=0;

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_init = FALSE;

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 pwm_init(uint_16 presc){
	if(gb_init==FALSE){
		gpio_set_pin_direction(GPIO_PORT_B,GPIO_PIN4,GPIO_OUTPUT);
		TCCR0|=1<<WGM1|1<<WGM0;//FAST PWM MODE
		switch(presc){
		case 1:
		{
			gint_prs=1;
		}
		break;
		case 8:
		{
			gint_prs=2;
		}
		break;
		case 64:
		{
			gint_prs=3;
		}
		break;
		case 256:
		{
			gint_prs=4;
		}
		break;
		case 1024:
		{
			gint_prs=5;
		}
		break;
		default:
		{
			PWM_LOG("prescaler out of range");
			return FALSE;
		}
		break;

		}

		uint_16 pwm_freq=0;
		pwm_freq=31250/presc;
		PWM_LOG("pwm_freq=%d\r\n",pwm_freq);
		gb_init=TRUE;

		return SUCCESS;
	}
	return FALSE;

}

sint_16  pwm_start(uint_8 OCR){
	if(gb_init==TRUE){
		uint_8 duty=0;
		duty=((1+OCR)/256.0)*100;
		OCR0=OCR;
		TCCR0|=gint_prs;
		SET_BIT(TCCR0,COM1);
		CLR_BIT(TCCR0,COM0);//NON INVERTED MODE
		PWM_LOG("duty=%d\r\n",duty);
		return SUCCESS;
	}

	else
	{
		return FALSE;
	}
}

sint_16 pwm_stop(void){
	if(gb_init==TRUE){
	CLR_BIT(TCCR0,COM0);
	CLR_BIT(TCCR0,COM1);//DISCONNECTED MODE
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);// TIMER NO PRESCALER STOP
	return SUCCESS;
	}

	else
	{
		return FALSE;
	}

	}
