/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "common.h"
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
//#define TIMER0_LOG_ENABLE

#ifdef TIMER0_LOG_ENABLE
#define TMR0_LOG(...)				SYS_LOGGER("[TM0]: "__VA_ARGS__)
#define TMR0_LOG_ERR(...)			SYS_LOGGER_ERR("[TM0]: "__VA_ARGS__)
#define TMR0_LOG_WRN(...)			SYS_LOGGER_WRN("[TM0]: "__VA_ARGS__)
#define TMR0_LOG_INFO(...)			SYS_LOGGER_INFO("[TM0]: "__VA_ARGS__)
#define TMR0_LOG_SUCC(...)			SYS_LOGGER_SUCC("[TM0]: "__VA_ARGS__)
#else
#define TMR0_LOG(...)				 
#define TMR0_LOG_ERR(...)			 
#define TMR0_LOG_WRN(...)			 
#define TMR0_LOG_INFO(...)			 
#define TMR0_LOG_SUCC(...)			 
#endif


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static bool gb_timer_init = FALSE;
static void(*gpf_timer_cb)(void);
static uint_32 gu32_timer_ms = 0 ;
static bool  gb_timer_enabled = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(gb_timer_enabled == TRUE)
	{
		TMR0_LOG_SUCC("Interrupt");
		#if(F_CPU == 8000000)
		TCNT1 = 53036;
		#elif(F_CPU == 16000000)
		TCNT1 = 40536 ;
		#endif
		gu32_timer_ms--;
		
		if (gu32_timer_ms == 0)
		{
			gb_timer_enabled = FALSE;
			TIMSK  = 0;
			gpf_timer_cb();
		}
	}	
}

/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 timer_init(void(*pf_timer_cb)(void))
{
	sint_16 s16_retval = SUCCESS;
	if(gb_timer_init == FALSE)
	{
		if(pf_timer_cb != NULL)
		{
			gb_timer_init = TRUE;
			TCCR1B |= (1 << CS11)|(1 << CS10);
			SREG  |= (1<< 7); // enable global interrupt
#if(F_CPU == 8000000)
			TCNT1 = 53036;
#elif(F_CPU == 16000000)
			TCNT1 = 40536 ;
#else
#error "Not developed yet"
#endif
			gpf_timer_cb = pf_timer_cb ;
			TMR0_LOG_SUCC("Initialized Successfully");
		}
		else
		{
			TMR0_LOG_ERR("Invalid Arguments");
		}		
	}

	return s16_retval;
}

sint_16 timer_deinit(void)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_timer_init == TRUE)
	{
		gb_timer_init = FALSE;
		TCCR1B = 0 ;
		TCNT1 = 0;
		TIMSK = 0;
	}
	return s16_retval;
}

sint_16 start_hal_timer(uint_32 u32_ms)
{
	sint_16 s16_retval = SUCCESS;
	/*Enable and Rest timer*/
	if(u32_ms !=0)
	{
		
#if(F_CPU == 8000000)
		TCNT1 = 53036;
#elif(F_CPU == 16000000)
		TCNT1 = 40536 ;
#endif
		gb_timer_enabled = TRUE;
		gu32_timer_ms = u32_ms;
		TIMSK  = (1<<TOIE1);
		TMR0_LOG_SUCC("timer start successfully");
	}
	else
	{
		TMR0_LOG_ERR("Invalid Argument");
		s16_retval = ERROR;
	}	
	return s16_retval;
}

sint_16 stop_hal_timer(void)
{
	sint_16 s16_retval = SUCCESS;
	gb_timer_enabled = FALSE;
	return s16_retval;
}

