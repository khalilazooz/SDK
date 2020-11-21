/** STD LIB DIRECTIVES **/


/************************/
/** COMPONENT DIRECTIVES **/
#include"gpio.h"
#include"gpio_register.h"
#include "debug.h"

#define gpio_LOG_ENABLE

#ifdef gpio_LOG_ENABLE
#define gpio_LOG(...)              SYS_LOGGER("[LCD_MANG]: "__VA_ARGS__)
#define gpio_LOG_ERR(...)          SYS_LOGGER_ERR("[LCD_MANG]: "__VA_ARGS__)
#define gpio_LOG_WRN(...)          SYS_LOGGER_WRN("[LCD_MANG]: "__VA_ARGS__)
#define gpio_LOG_INFO(...)         SYS_LOGGER_INFO("[LCD_MANG]: "__VA_ARGS__)
#define gpio_LOG_SUCC(...)         SYS_LOGGER_SUCC("[LCD_MANG]: "__VA_ARGS__)
#else
#define gpio_LOG(...)
#define gpio_LOG_ERR(...)
#define gpio_LOG_WRN(...)
#define gpio_LOG_INFO(...)
#define gpio_LOG_SUCC(...)
#endif

/************************** FUNCTIONS IMPLEMENTATION **************************/

sint_16  gpio_set_port_direction( uint_8 GPIO_PortID,uint_8 GPIO_Direction)
{
	
	if(GPIO_PortID < 7)
	{
		switch(GPIO_PortID)
		{
			case GPIO_PORT_A: GPIO_DDRA = GPIO_Direction; break;
			case GPIO_PORT_B: GPIO_DDRB = GPIO_Direction; break;
			case GPIO_PORT_C: GPIO_DDRC = GPIO_Direction; break;
			case GPIO_PORT_D: GPIO_DDRD = GPIO_Direction; break;
			case GPIO_PORT_E: GPIO_DDRE = GPIO_Direction; break;
			case GPIO_PORT_F: GPIO_DDRF = GPIO_Direction; break;
			case GPIO_PORT_G: GPIO_DDRG = GPIO_Direction; break;
		}
		
	}
	else
	{
		return gpio_invaled_argument;
	}
	return gpio_success;
}
/******************************************************************************/
sint_16  gpio_set_pin_direction( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Direction)
{
	
	if((GPIO_PortID < 7)&&(GPIO_PinID <8))
	{
		if(GPIO_Direction==GPIO_OUTPUT)
		{
			switch(GPIO_PortID)
			{
				case GPIO_PORT_A: SET_BIT(GPIO_DDRA,GPIO_PinID); break;
				case GPIO_PORT_B: SET_BIT(GPIO_DDRB,GPIO_PinID); break;
				case GPIO_PORT_C: SET_BIT(GPIO_DDRC,GPIO_PinID); break;
				case GPIO_PORT_D: SET_BIT(GPIO_DDRD,GPIO_PinID); break;
				case GPIO_PORT_E: SET_BIT(GPIO_DDRE,GPIO_PinID); break;
				case GPIO_PORT_F: SET_BIT(GPIO_DDRF,GPIO_PinID); break;
				case GPIO_PORT_G: SET_BIT(GPIO_DDRG,GPIO_PinID); break;
			}
			
			}
			
			else if(GPIO_Direction==GPIO_INPUT)
			{
				switch(GPIO_PortID)
				{
					case GPIO_PORT_A: CLR_BIT(GPIO_DDRA,GPIO_PinID); break;
					case GPIO_PORT_B: CLR_BIT(GPIO_DDRB,GPIO_PinID); break;
					case GPIO_PORT_C: CLR_BIT(GPIO_DDRC,GPIO_PinID); break;
					case GPIO_PORT_D: CLR_BIT(GPIO_DDRD,GPIO_PinID); break;
					case GPIO_PORT_E: CLR_BIT(GPIO_DDRE,GPIO_PinID); break;
					case GPIO_PORT_F: CLR_BIT(GPIO_DDRF,GPIO_PinID); break;
					case GPIO_PORT_G: CLR_BIT(GPIO_DDRG,GPIO_PinID); break;
				}
				
			}			
			else
		{
			return gpio_invaled_argument;
		}
		
	}
	else
	{
		return gpio_invaled_argument;
	}
	return gpio_success;
}
/**************************************************************************/
sint_16  gpio_set_port_value( uint_8 GPIO_PortID,uint_8 GPIO_Value)
{
	
	if(GPIO_PortID < 7)
	{
		switch(GPIO_PortID)
		{
			case GPIO_PORT_A: GPIO_PORTA =  GPIO_Value; break;
			case GPIO_PORT_B: GPIO_PORTB =  GPIO_Value; break;
			case GPIO_PORT_C: GPIO_PORTC =  GPIO_Value; break;
			case GPIO_PORT_D: GPIO_PORTD =  GPIO_Value; break;
			case GPIO_PORT_E: GPIO_PORTE =  GPIO_Value; break;
			case GPIO_PORT_F: GPIO_PORTF =  GPIO_Value; break;
			case GPIO_PORT_G: GPIO_PORTG =  GPIO_Value; break;
		}
		
	}
	else
	{
	return gpio_invaled_argument;	
	}
	return gpio_success;
}
/*********************************************************************************************************************/
sint_16  gpio_set_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Value)
{
	
	if((GPIO_PortID < 7)&&(GPIO_PinID<8))
	{
		if(GPIO_Value==GPIO_HIGH)
		switch(GPIO_PortID)
		{
			case GPIO_PORT_A: SET_BIT(GPIO_PORTA,GPIO_PinID); break;
			case GPIO_PORT_B: SET_BIT(GPIO_PORTB,GPIO_PinID); break;
			case GPIO_PORT_C: SET_BIT(GPIO_PORTC,GPIO_PinID); break;
			case GPIO_PORT_D: SET_BIT(GPIO_PORTD,GPIO_PinID); break;
			case GPIO_PORT_E: SET_BIT(GPIO_PORTE,GPIO_PinID); break;
			case GPIO_PORT_F: SET_BIT(GPIO_PORTF,GPIO_PinID); break;
			case GPIO_PORT_G: SET_BIT(GPIO_PORTG,GPIO_PinID); break;
		}
		else if(GPIO_Value==GPIO_LOW)
		{
			switch(GPIO_PortID)
			{
				case GPIO_PORT_A: CLR_BIT(GPIO_PORTA,GPIO_PinID); break;
				case GPIO_PORT_B: CLR_BIT(GPIO_PORTB,GPIO_PinID); break;
				case GPIO_PORT_C: CLR_BIT(GPIO_PORTC,GPIO_PinID); break;
				case GPIO_PORT_D: CLR_BIT(GPIO_PORTD,GPIO_PinID); break;
				case GPIO_PORT_E: CLR_BIT(GPIO_PORTE,GPIO_PinID); break;
				case GPIO_PORT_F: CLR_BIT(GPIO_PORTF,GPIO_PinID); break;
				case GPIO_PORT_G: CLR_BIT(GPIO_PORTG,GPIO_PinID); break;
			}
			
		}
		
	}
	else
	{
		return gpio_invaled_argument;
	}
	return gpio_success;
}
/*********************************************************************************************************************/
sint_16 gpio_get_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8* p)
{

	uint_8 Local_value = 0;
	if((GPIO_PortID < 7)&&(GPIO_PinID<8))
	{
		switch(GPIO_PortID)
		{
			case GPIO_PORT_A: Local_value = GET_BIT(GPIO_PINA,GPIO_PinID); break;
			case GPIO_PORT_B: Local_value = GET_BIT(GPIO_PINB,GPIO_PinID); break;
			case GPIO_PORT_C: Local_value = GET_BIT(GPIO_PINC,GPIO_PinID); break;
			case GPIO_PORT_D: Local_value = GET_BIT(GPIO_PIND,GPIO_PinID); break;
			case GPIO_PORT_E: Local_value = GET_BIT(GPIO_PINE,GPIO_PinID); break;
			case GPIO_PORT_F: Local_value = GET_BIT(GPIO_PINF,GPIO_PinID); break;
			case GPIO_PORT_G: Local_value = GET_BIT(GPIO_PING,GPIO_PinID); break;
		}
	}
	else
	{
return gpio_invaled_argument;
	}
	*p=Local_value;
	return gpio_success;
	
}
