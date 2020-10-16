/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include "timer.h"
#include "common.h"
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define TIMER0_LOG_ENABLE
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
ISR(TIMER0_OVF_vect)
{
	if(gb_timer_enabled == TRUE)
	{
		#if(F_CPU == 8000000)
		TCNT0 = 131;
		#elif(F_CPU == 16000000)
		TCNT0 = 6 ;
		#endif
		gu32_timer_ms--;
		if (gu32_timer_ms == 0)
		{
			gb_timer_enabled = FALSE;
			gpf_timer_cb();
		}
	}	
}

/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 timer_init(void)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_timer_init == FALSE)
	{
		gb_timer_init = TRUE;
		TCCR0 |= (1 << CS01)|(1 << CS00);
#if(F_CPU == 8000000)
		TCNT0 = 131;
#elif(F_CPU == 16000000)
		TCNT0 = 6 ;
#else
#error "Not developed yet"
#endif
		TMR0_LOG_SUCC("Initialized Successfully");
	}
	return s16_retval;
}

sint_16 timer_deinit(void)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_timer_init == TRUE)
	{
		gb_timer_init = FALSE;
		TCCR0 = 0 ;
		TCNT0 = 0;
	}
	return s16_retval;
}

sint_16 start_timer(uint_32 u32_ms,void(*pf_timer_cb)(void))
{
	sint_16 s16_retval = SUCCESS;
	/*Enable and Rest timer*/
	if(u32_ms !=0 && pf_timer_cb != NULL)
	{
		(void)timer_init();
#if(F_CPU == 8000000)
		TCNT0 = 131;
#elif(F_CPU == 16000000)
		TCNT0 = 6 ;
#endif
		gb_timer_enabled = TRUE;
		gu32_timer_ms = u32_ms;
		gpf_timer_cb = pf_timer_cb ;
	}
	else
	{
		TMR0_LOG_ERR("Invalid Argument");
		s16_retval = ERROR;
	}	
	return s16_retval;
}

sint_16 stop_timer(void)
{
	sint_16 s16_retval = SUCCESS;
	gb_timer_enabled = FALSE;
	s16_retval = timer_deinit();
	return s16_retval;
}
