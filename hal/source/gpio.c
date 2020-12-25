
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "gpio.h"
#include "gpio_register.h"
#include "debug.h"
#include "common.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define gpio_LOG_ENABLE
#ifdef gpio_LOG_ENABLE
#define gpio_LOG(...)              SYS_LOGGER("[GPIO]: "__VA_ARGS__)
#define gpio_LOG_ERR(...)          SYS_LOGGER_ERR("[GPIO]: "__VA_ARGS__)
#define gpio_LOG_WRN(...)          SYS_LOGGER_WRN("[GPIO]: "__VA_ARGS__)
#define gpio_LOG_INFO(...)         SYS_LOGGER_INFO("[GPIO]: "__VA_ARGS__)
#define gpio_LOG_SUCC(...)         SYS_LOGGER_SUCC("[GPIO]: "__VA_ARGS__)
#else
#define gpio_LOG(...)
#define gpio_LOG_ERR(...)
#define gpio_LOG_WRN(...)
#define gpio_LOG_INFO(...)
#define gpio_LOG_SUCC(...)
#endif


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static uint_64 u64_selection = 0;
static bool b_gpio_initialized = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

/************************** FUNCTIONS IMPLEMENTATION **************************/
sint_16 gpio_init(void)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == FALSE)
	{
		b_gpio_initialized = TRUE;
		u64_selection = 0;
		/*Set all Ports to Zeros*/
		PORTA = 0x00 ;
		PORTB = 0x00 ;
		PORTC = 0x00 ;
		PORTD = 0x00 ;
		PORTE = 0x00 ;
		PORTF = 0x00 ;
		PORTG = 0x00 ;
	}
	return u16_retval;
}
sint_16 gpio_select(uint_8 u8_gpio_port,uint_8 u8_gpio_pin)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		if((u8_gpio_port < INVALID_PORT) && (u8_gpio_pin < INVALID_PIN))
		{
			if(!GET_BIT(u64_selection,((u8_gpio_port*INVALID_PIN)+u8_gpio_pin)))
			{
				SET_BIT(u64_selection ,(((u8_gpio_port*INVALID_PIN)+u8_gpio_pin)) );

			}
			else
			{
				u16_retval = GPIO_PIN_RESEVED ;
			}
		}
		else
		{
			u16_retval =  GPIO_INVALED_ARGUMENT;
		}
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}

sint_16 gpio_deselect(uint_8 u8_gpio_port,uint_8 u8_gpio_pin)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		if((u8_gpio_port < INVALID_PORT) && (u8_gpio_pin < INVALID_PIN))
		{
			CLR_BIT(u64_selection,((u8_gpio_port*INVALID_PIN)+u8_gpio_pin));
		}
		else
		{
			u16_retval =  GPIO_INVALED_ARGUMENT;
		}
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}


sint_16  gpio_set_port_direction( uint_8 u8_gpio_port,uint_8 u8_gpio_direction)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		if(u8_gpio_port < INVALID_PORT)
		{
			if(GET_BYTE(u64_selection,(u8_gpio_port*INVALID_PIN)))
			{
				switch(u8_gpio_port)
				{
					case GPIO_PORTA: DDRA = u8_gpio_direction; break;
					case GPIO_PORTB: DDRB = u8_gpio_direction; break;
					case GPIO_PORTC: DDRC = u8_gpio_direction; break;
					case GPIO_PORTD: DDRD = u8_gpio_direction; break;
					case GPIO_PORTE: DDRE = u8_gpio_direction; break;
					case GPIO_PORTF: DDRF = u8_gpio_direction; break;
					case GPIO_PORTG: DDRG = u8_gpio_direction; break;
				}
			}
			else
			{
				u16_retval = GPIO_PIN_NOT_SELECTED;
			}
		}
		else
		{
			u16_retval =  GPIO_INVALED_ARGUMENT;
		}
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}
/******************************************************************************/
sint_16  gpio_set_pin_direction( uint_8 u8_gpio_port,uint_8 u8_gpio_pin,bool b_gpio_direction)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		if((u8_gpio_port < INVALID_PORT) && (u8_gpio_pin < INVALID_PIN))
		{
			if(GET_BIT(u64_selection,((u8_gpio_port * INVALID_PIN) + u8_gpio_pin)))
			{
				if(b_gpio_direction == GPIO_OUTPUT)
				{
					switch(u8_gpio_port)
					{
						case GPIO_PORTA: SET_BIT(DDRA,u8_gpio_pin); break;
						case GPIO_PORTB: SET_BIT(DDRB,u8_gpio_pin); break;
						case GPIO_PORTC: SET_BIT(DDRC,u8_gpio_pin); break;
						case GPIO_PORTD: SET_BIT(DDRD,u8_gpio_pin); break;
						case GPIO_PORTE: SET_BIT(DDRE,u8_gpio_pin); break;
						case GPIO_PORTF: SET_BIT(DDRF,u8_gpio_pin); break;
						case GPIO_PORTG: SET_BIT(DDRG,u8_gpio_pin); break;
					}

				}

				else if(b_gpio_direction == GPIO_INPUT)
				{
					switch(u8_gpio_port)
					{
						case GPIO_PORTA: CLR_BIT(DDRA,u8_gpio_pin); break;
						case GPIO_PORTB: CLR_BIT(DDRB,u8_gpio_pin); break;
						case GPIO_PORTC: CLR_BIT(DDRC,u8_gpio_pin); break;
						case GPIO_PORTD: CLR_BIT(DDRD,u8_gpio_pin); break;
						case GPIO_PORTE: CLR_BIT(DDRE,u8_gpio_pin); break;
						case GPIO_PORTF: CLR_BIT(DDRF,u8_gpio_pin); break;
						case GPIO_PORTG: CLR_BIT(DDRG,u8_gpio_pin); break;
					}
				}
				else
				{
						u16_retval = GPIO_INVALED_ARGUMENT;
				}
			}
			else
			{
				u16_retval = GPIO_PIN_NOT_SELECTED;
			}
		}
		else
		{
			u16_retval =  GPIO_INVALED_ARGUMENT;
		}
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}
/**************************************************************************/
sint_16  gpio_set_port_value( uint_8 u8_gpio_port,uint_8 u8_portval)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		if(u8_gpio_port < INVALID_PORT)
		{
			if(GET_BYTE(u64_selection,(u8_gpio_port * INVALID_PIN)))
			{
				switch(u8_gpio_port)
				{
					case GPIO_PORTA: PORTA =  u8_portval; break;
					case GPIO_PORTB: PORTB =  u8_portval; break;
					case GPIO_PORTC: PORTC =  u8_portval; break;
					case GPIO_PORTD: PORTD =  u8_portval; break;
					case GPIO_PORTE: PORTE =  u8_portval; break;
					case GPIO_PORTF: PORTF =  u8_portval; break;
					case GPIO_PORTG: PORTG =  u8_portval; break;
				}
			}
			else
			{
				u16_retval = GPIO_PIN_NOT_SELECTED;
			}

		}
		else
		{
			u16_retval =  GPIO_INVALED_ARGUMENT;
		}
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}
/*********************************************************************************************************************/
sint_16  gpio_set_pin_value( uint_8 u8_gpio_port,uint_8 u8_gpio_pin,bool b_pinval)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		if((u8_gpio_port < INVALID_PORT) && (u8_gpio_pin < INVALID_PIN))
		{
			if(GET_BIT(u64_selection,((u8_gpio_port * INVALID_PIN) + u8_gpio_pin)))
			{
				if(b_pinval == GPIO_HIGH)
				{
					switch(u8_gpio_port)
					{
						case GPIO_PORTA: SET_BIT(PORTA,u8_gpio_pin); break;
						case GPIO_PORTB: SET_BIT(PORTB,u8_gpio_pin); break;
						case GPIO_PORTC: SET_BIT(PORTC,u8_gpio_pin); break;
						case GPIO_PORTD: SET_BIT(PORTD,u8_gpio_pin); break;
						case GPIO_PORTE: SET_BIT(PORTE,u8_gpio_pin); break;
						case GPIO_PORTF: SET_BIT(PORTF,u8_gpio_pin); break;
						case GPIO_PORTG: SET_BIT(PORTG,u8_gpio_pin); break;
					}
				}
				else if(b_pinval == GPIO_LOW)
				{
					switch(u8_gpio_port)
					{
						case GPIO_PORTA: CLR_BIT(PORTA,u8_gpio_pin); break;
						case GPIO_PORTB: CLR_BIT(PORTB,u8_gpio_pin); break;
						case GPIO_PORTC: CLR_BIT(PORTC,u8_gpio_pin); break;
						case GPIO_PORTD: CLR_BIT(PORTD,u8_gpio_pin); break;
						case GPIO_PORTE: CLR_BIT(PORTE,u8_gpio_pin); break;
						case GPIO_PORTF: CLR_BIT(PORTF,u8_gpio_pin); break;
						case GPIO_PORTG: CLR_BIT(PORTG,u8_gpio_pin); break;
					}

				}
			}
			else
			{
				u16_retval = GPIO_PIN_NOT_SELECTED;
			}
			
		}
		else
		{
			u16_retval =  GPIO_INVALED_ARGUMENT;
		}
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}
/*********************************************************************************************************************/
sint_16 gpio_toggle(uint_8 u8_gpio_port,uint_8 u8_gpio_pin)
{
	sint_16 u16_retval = SUCCESS;
		if(b_gpio_initialized == TRUE)
		{
			if((u8_gpio_port < INVALID_PORT) && (u8_gpio_pin < INVALID_PIN))
			{
				if(GET_BIT(u64_selection,((u8_gpio_port * INVALID_PIN) + u8_gpio_pin)))
				{
						switch(u8_gpio_port)
						{
							case GPIO_PORTA: TOG_BIT(PORTA,u8_gpio_pin); break;
							case GPIO_PORTB: TOG_BIT(PORTB,u8_gpio_pin); break;
							case GPIO_PORTC: TOG_BIT(PORTC,u8_gpio_pin); break;
							case GPIO_PORTD: TOG_BIT(PORTD,u8_gpio_pin); break;
							case GPIO_PORTE: TOG_BIT(PORTE,u8_gpio_pin); break;
							case GPIO_PORTF: TOG_BIT(PORTF,u8_gpio_pin); break;
							case GPIO_PORTG: TOG_BIT(PORTG,u8_gpio_pin); break;
						}

				}
				else
				{
					u16_retval = GPIO_PIN_NOT_SELECTED;
				}

			}
			else
			{
				u16_retval =  GPIO_INVALED_ARGUMENT;
			}
		}
		else
		{
			u16_retval = GPIO_NOT_INTIALIZED;
		}
		return u16_retval;
}


/*********************************************************************************************************************/
sint_16 gpio_get_pin_value( uint_8 u8_gpio_port,uint_8 u8_gpio_pin,bool* pb_pinval)
{
	sint_16 u16_retval = SUCCESS;
	if(b_gpio_initialized == TRUE)
	{
		bool b_pinval = 0;
		if((u8_gpio_port < 7)&&(u8_gpio_pin<8))
		{
			if(GET_BIT(u64_selection,((u8_gpio_port * INVALID_PIN) + u8_gpio_pin)))
			{
				switch(u8_gpio_port)
				{
					case GPIO_PORTA: b_pinval = GET_BIT(PINA,u8_gpio_pin); break;
					case GPIO_PORTB: b_pinval = GET_BIT(PINB,u8_gpio_pin); break;
					case GPIO_PORTC: b_pinval = GET_BIT(PINC,u8_gpio_pin); break;
					case GPIO_PORTD: b_pinval = GET_BIT(PIND,u8_gpio_pin); break;
					case GPIO_PORTE: b_pinval = GET_BIT(PINE,u8_gpio_pin); break;
					case GPIO_PORTF: b_pinval = GET_BIT(PINF,u8_gpio_pin); break;
					case GPIO_PORTG: b_pinval = GET_BIT(PING,u8_gpio_pin); break;
				}
			}
			else
			{
				u16_retval = GPIO_PIN_NOT_SELECTED;
			}
		}
		else
		{
			u16_retval = GPIO_INVALED_ARGUMENT;
		}
		*pb_pinval=b_pinval;
	}
	else
	{
		u16_retval = GPIO_NOT_INTIALIZED;
	}
	return u16_retval;
}
