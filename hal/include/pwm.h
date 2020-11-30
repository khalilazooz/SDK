
#ifndef _PWM_H_
#define _PWM_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define TCNT0   *((volatile uint_8*)0x52)
#define TCCR0   *((volatile uint_8*)0x53)
#define TIMSK   *((volatile uint_8*)0x57)
#define OCR0    *((volatile uint_8*)0x51)
#define TIFR    *((volatile uint_8*)0x56)
#define SREG    *((volatile uint_8*)0X5F) //global interrupt

/*******errors macros***/
#define PWM_INVALID_PARAMETER			(PWM_ERROR_BASE-1)
#define PWM_NOT_INTIALIZED_YET			(PWM_ERROR_BASE-2)

/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/
typedef enum  _tenu_pwm_prescaler
{
	PWM_1_PRESCALER=1,
	PWM_8_PRESCALER,
	PWM_64_PRESCALER,
	PWM_256_PRESCALER,
	PWM_1024_PRESCALER,
	PWM_EX_CLK_PRESCALER,
	PWM_INVALID_PRESCALER
} tenu_pwm_prescaler;

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 pwm_init( tenu_pwm_prescaler lenu_pwm_prescaler);
sint_16 pwm_start(uint_8 OCR);
sint_16 pwm_stop(void);
#endif /*_PWM_H_*/





