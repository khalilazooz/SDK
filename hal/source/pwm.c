/*
 * Pulse width modulation module is using timer 3 as it has 3 output OC3A , OC3B , OC3C
 */


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


#define TCNT3H   	*((volatile uint_8*)(0x89))
#define TCNT3L   	*((volatile uint_8*)(0x88))

#define TCCR3A   	*((volatile uint_8*)(0x8B))
#define TCCR3B		*((volatile uint_8*)(0x8A))

#define OCR3AH		*((volatile uint_8*)(0x87))
#define OCR3AL		*((volatile uint_8*)(0x86))
#define OCR3BH		*((volatile uint_8*)(0x85))
#define OCR3BL		*((volatile uint_8*)(0x84))
#define OCR3CH		*((volatile uint_8*)(0x83))
#define OCR3CL		*((volatile uint_8*)(0x82))

#define TIMSK   	*((volatile uint_8*)(0x57))

#define TIFR    	*((volatile uint_8*)(0x56))
#define SREG    	*((volatile uint_8*)(0X5F)) //global interrupt

#define WGM33				(4)
#define WGM32				(3)
#define WGM31				(1)
#define WGM30				(0)
#define COM3A1				(7)
#define COM3A0				(6)
#define COM3B1				(5)
#define COM3B0				(4)
#define COM3C1				(3)
#define COM3C0				(2)
#define CS30				(0)
#define CS31				(1)
#define CS32				(2)
#define  CLOCKS				(256)
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
static tenu_pwm_prescaler  genu_pwm_prescaler= 0;

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

sint_16 pwm_init(tenu_pwm_prescaler lenu_pwm_prescaler)
{
	sint_16 s16_retval = SUCCESS;
	uint_16 u16_pwm_prescaler=0;
	if(gb_pwm_initialized==FALSE)
	{
		if(lenu_pwm_prescaler < PWM_INVALID_PRESCALER)
		{
			switch(lenu_pwm_prescaler)
			{
				case PWM_1_PRESCALER:
				{
					u16_pwm_prescaler=1;
				}
					break;
				case PWM_8_PRESCALER:
				{
					u16_pwm_prescaler = 8;
				}
					break;
				case PWM_64_PRESCALER:
				{
					u16_pwm_prescaler = 64;
				}
					break;
				case PWM_256_PRESCALER:
				{
					u16_pwm_prescaler = 256;
				}
					break;
				case PWM_1024_PRESCALER:
				{
					u16_pwm_prescaler = 1024;
				}
					break;
				default:
					break;
			}
			genu_pwm_prescaler = lenu_pwm_prescaler;
			PWM_LOG("pwm_freq = %ld \r\n",(uint_32)((float)F_CPU/((float)CLOCKS * (float)u16_pwm_prescaler)));

			gb_pwm_initialized = TRUE;

			gpio_init();

			gpio_select(GPIO_PORTE,GPIO_PIN3);
			gpio_select(GPIO_PORTE,GPIO_PIN4);
			gpio_select(GPIO_PORTE,GPIO_PIN5);

			gpio_set_pin_direction(GPIO_PORTE,GPIO_PIN3,GPIO_OUTPUT);
			gpio_set_pin_direction(GPIO_PORTE,GPIO_PIN4,GPIO_OUTPUT);
			gpio_set_pin_direction(GPIO_PORTE,GPIO_PIN5,GPIO_OUTPUT);

			//FAST PWM MODE 8 bits
			/*	WGMn3	Value = 0		>>  TCCR3B	(Bit-> 4) // WGM33
			 *  WGMn2	Value = 1		>>	TCCR3B	(Bit-> 3) // WGM32
			 *  WGMn1	Value = 0		>>	TCCR3A	(Bit-> 1) // WGM31
			 *  WGMn0	Value = 1		>>	TCCR3A	(Bit-> 0) // WGM30
			 *  */
			TCCR3A |= (0<<WGM31)|(1<<WGM30);
			TCCR3B |= (1<<WGM32)|(0<<WGM33);

			TCNT3L = 0 ;
			TCNT3H = 0 ;
		}
		else
		{
			s16_retval = PWM_INVALID_PARAMETER;
			PWM_LOG("prescaler out of range");
		}

	}
	return s16_retval;

}

sint_16  pwm_start(uint_8 u8_pwm_output, tenu_pwm_output enu_pwm_output)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_pwm_initialized ==TRUE)
	{
		if(u8_pwm_output > 0 && enu_pwm_output < PWM_OUTPUT_INVALID)
		{
			uint_8 u8_duty = 0;
			u8_duty= ((1 + u8_pwm_output)/256.0)*100;//equation
			PWM_LOG("duty = %d\r\n",u8_duty);
			TCCR3B = (TCCR3B & 0xF8) | genu_pwm_prescaler;
			switch(enu_pwm_output)
			{
				case PWM_OUTPUT_A:
				{
					OCR3AL = u8_pwm_output;
					OCR3AH = 0;
					SET_BIT(TCCR3A,COM3A1);
					CLR_BIT(TCCR3A,COM3A0);//NON INVERTED MODE
					break;
				}
				case PWM_OUTPUT_B:
				{
					OCR3BL = u8_pwm_output;
					OCR3BH = 0;
					SET_BIT(TCCR3A,COM3B1);
					CLR_BIT(TCCR3A,COM3B0);//NON INVERTED MODE
					break;
				}
				case PWM_OUTPUT_C:
				{
					OCR3CL = u8_pwm_output;
					OCR3CH = 0;
					SET_BIT(TCCR3A,COM3C1);
					CLR_BIT(TCCR3A,COM3C0);//NON INVERTED MODE
					break;
				}
				case PWM_OUTPUT_ALL:
				{
					OCR3AL = u8_pwm_output;
					OCR3AH = 0;
					SET_BIT(TCCR3A,COM3A1);
					CLR_BIT(TCCR3A,COM3A0);//NON INVERTED MODE


					OCR3BL = u8_pwm_output;
					OCR3BH = 0;
					SET_BIT(TCCR3A,COM3B1);
					CLR_BIT(TCCR3A,COM3B0);//NON INVERTED MODE

					OCR3CL = u8_pwm_output;
					OCR3CH = 0;
					SET_BIT(TCCR3A,COM3C1);
					CLR_BIT(TCCR3A,COM3C0);//NON INVERTED MODE
					break;
				}
				default:
				{
					break;
				}
			}

		}
		else
		{
			s16_retval=PWM_INVALID_PARAMETER;
		}
	}

	else
	{
		s16_retval=PWM_NOT_INTIALIZED_YET;
	}

return s16_retval;
}

sint_16 pwm_stop(tenu_pwm_output enu_pwm_output)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_pwm_initialized==TRUE)
	{
		if(enu_pwm_output < PWM_OUTPUT_INVALID)
		{
			switch(enu_pwm_output)
			{
				case PWM_OUTPUT_A:
				{
					OCR3AL = 0;
					OCR3AH = 0;
					CLR_BIT(TCCR3A,COM3A1);
					CLR_BIT(TCCR3A,COM3A0);//DISCONNECTED MODE
					break;
				}
				case PWM_OUTPUT_B:
				{
					OCR3BL = 0;
					OCR3BH = 0;
					CLR_BIT(TCCR3A,COM3B1);
					CLR_BIT(TCCR3A,COM3B0);//DISCONNECTED MODE
					break;
				}
				case PWM_OUTPUT_C:
				{
					OCR3CL = 0;
					OCR3CH = 0;
					CLR_BIT(TCCR3A,COM3C1);
					CLR_BIT(TCCR3A,COM3C0);//DISCONNECTED MODE
					break;
				}
				case PWM_OUTPUT_ALL:
				{
					OCR3AL = 0;
					OCR3AH = 0;

					OCR3BL = 0;
					OCR3BH = 0;

					OCR3CL = 0;
					OCR3CH = 0;

					CLR_BIT(TCCR3A,COM3A1);
					CLR_BIT(TCCR3A,COM3A1);//DISCONNECTED MODE
					CLR_BIT(TCCR3A,COM3B1);
					CLR_BIT(TCCR3A,COM3B0);//DISCONNECTED MODE
					CLR_BIT(TCCR3A,COM3C1);
					CLR_BIT(TCCR3A,COM3C0);//DISCONNECTED MODE
					CLR_BIT(TCCR3B,CS30);
					CLR_BIT(TCCR3B,CS31);
					CLR_BIT(TCCR3B,CS32);// TIMER NO PRESCALER STOP
					break;
				}
				default:
				{
					break;
				}
			}

		}
		else
		{
			s16_retval=PWM_INVALID_PARAMETER;
		}
	}

	else
	{
		s16_retval=PWM_NOT_INTIALIZED_YET;
	}

	return s16_retval;
}
