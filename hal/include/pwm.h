
#ifndef _PWM_H_
#define _PWM_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


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

typedef enum  _tenu_pwm_output
{
	PWM_OUTPUT_A,
	PWM_OUTPUT_B,
	PWM_OUTPUT_C,
	PWM_OUTPUT_ALL,
	PWM_OUTPUT_INVALID
}tenu_pwm_output;
/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 pwm_init( tenu_pwm_prescaler lenu_pwm_prescaler);
sint_16 pwm_start(uint_8 u8_pwm_output, tenu_pwm_output enu_pwm_output);
sint_16 pwm_stop(tenu_pwm_output enu_pwm_output);
#endif /*_PWM_H_*/





