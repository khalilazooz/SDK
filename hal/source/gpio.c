/** STD LIB DIRECTIVES **/


/************************/
/** COMPONENT DIRECTIVES **/
#include"gpio.h"
#include"gpio_register.h"

/************************** FUNCTIONS IMPLEMENTATION **************************/

ErrorStatus  GPIO_enumSetPortDirection( uint_8 GPIO_u8PortID,uint_8 GPIO_u8Direction)
{
	ErrorStatus Local_error= ES_NOK;
	if(GPIO_u8PortID < 7)
	{
		switch(GPIO_u8PortID)
		{
			case GPIO_U8_PORT_A: GPIO_U8_DDRA = GPIO_u8Direction; break;
			case GPIO_U8_PORT_B: GPIO_U8_DDRB = GPIO_u8Direction; break;
			case GPIO_U8_PORT_C: GPIO_U8_DDRC = GPIO_u8Direction; break;
			case GPIO_U8_PORT_D: GPIO_U8_DDRD = GPIO_u8Direction; break;
			case GPIO_U8_PORT_E: GPIO_U8_DDRE = GPIO_u8Direction; break;
			case GPIO_U8_PORT_F: GPIO_U8_DDRF = GPIO_u8Direction; break;
			case GPIO_U8_PORT_G: GPIO_U8_DDRG = GPIO_u8Direction; break;
		}
		Local_error= ES_OK;
	}
	else
	{
		Local_error= ES_OUT_OF_RANGE;
	}
	return Local_error;
}
/******************************************************************************/
ErrorStatus  GPIO_enumSetPinDirection( uint_8 GPIO_u8PortID,uint_8 GPIO_u8PinID,uint_8 GPIO_u8Direction)
{
	ErrorStatus Local_error= ES_NOK;
	if((GPIO_u8PortID < 7)&&(GPIO_u8PinID <8))
	{
		if(GPIO_u8Direction==GPIO_U8_OUTPUT)
		{
			switch(GPIO_u8PortID)
			{
				case GPIO_U8_PORT_A: SET_BIT(GPIO_U8_DDRA,GPIO_u8PinID); break;
				case GPIO_U8_PORT_B: SET_BIT(GPIO_U8_DDRB,GPIO_u8PinID); break;
				case GPIO_U8_PORT_C: SET_BIT(GPIO_U8_DDRC,GPIO_u8PinID); break;
				case GPIO_U8_PORT_D: SET_BIT(GPIO_U8_DDRD,GPIO_u8PinID); break;
				case GPIO_U8_PORT_E: SET_BIT(GPIO_U8_DDRE,GPIO_u8PinID); break;
				case GPIO_U8_PORT_F: SET_BIT(GPIO_U8_DDRF,GPIO_u8PinID); break;
				case GPIO_U8_PORT_G: SET_BIT(GPIO_U8_DDRG,GPIO_u8PinID); break;
			}
			
			}
			
			else if(GPIO_u8Direction==GPIO_U8_INPUT)
			{
				switch(GPIO_u8PortID)
				{
					case GPIO_U8_PORT_A: CLR_BIT(GPIO_U8_DDRA,GPIO_u8PinID); break;
					case GPIO_U8_PORT_B: CLR_BIT(GPIO_U8_DDRB,GPIO_u8PinID); break;
					case GPIO_U8_PORT_C: CLR_BIT(GPIO_U8_DDRC,GPIO_u8PinID); break;
					case GPIO_U8_PORT_D: CLR_BIT(GPIO_U8_DDRD,GPIO_u8PinID); break;
					case GPIO_U8_PORT_E: CLR_BIT(GPIO_U8_DDRE,GPIO_u8PinID); break;
					case GPIO_U8_PORT_F: CLR_BIT(GPIO_U8_DDRF,GPIO_u8PinID); break;
					case GPIO_U8_PORT_G: CLR_BIT(GPIO_U8_DDRG,GPIO_u8PinID); break;
				}
				
			}			
			else
		{
			Local_error= ES_OUT_OF_RANGE;
		}
		Local_error= ES_OK;
	}
	else
	{
		Local_error= ES_OUT_OF_RANGE;
	}
	return Local_error;
}
/**************************************************************************/
ErrorStatus  GPIO_enumSetPortValue( uint_8 GPIO_u8PortID,uint_8 GPIO_u8Value)
{
	ErrorStatus Local_error= ES_NOK;
	if(GPIO_u8PortID < 7)
	{
		switch(GPIO_u8PortID)
		{
			case GPIO_U8_PORT_A: GPIO_U8_PORTA =  GPIO_u8Value; break;
			case GPIO_U8_PORT_B: GPIO_U8_PORTB =  GPIO_u8Value; break;
			case GPIO_U8_PORT_C: GPIO_U8_PORTC =  GPIO_u8Value; break;
			case GPIO_U8_PORT_D: GPIO_U8_PORTD =  GPIO_u8Value; break;
			case GPIO_U8_PORT_E: GPIO_U8_PORTE =  GPIO_u8Value; break;
			case GPIO_U8_PORT_F: GPIO_U8_PORTF =  GPIO_u8Value; break;
			case GPIO_U8_PORT_G: GPIO_U8_PORTG =  GPIO_u8Value; break;
		}
		Local_error= ES_OK;
	}
	else
	{
		Local_error= ES_OUT_OF_RANGE;
	}
	return Local_error;
}
/*********************************************************************************************************************/
ErrorStatus  GPIO_enumSetPinValue( uint_8 GPIO_u8PortID,uint_8 GPIO_u8PinID,uint_8 GPIO_u8Value)
{
	ErrorStatus Local_error= ES_NOK;
	if((GPIO_u8PortID < 7)&&(GPIO_u8PinID<8))
	{
		if(GPIO_u8Value==GPIO_U8_HIGH)
		switch(GPIO_u8PortID)
		{
			case GPIO_U8_PORT_A: SET_BIT(GPIO_U8_PORTA,GPIO_u8PinID); break;
			case GPIO_U8_PORT_B: SET_BIT(GPIO_U8_PORTB,GPIO_u8PinID); break;
			case GPIO_U8_PORT_C: SET_BIT(GPIO_U8_PORTC,GPIO_u8PinID); break;
			case GPIO_U8_PORT_D: SET_BIT(GPIO_U8_PORTD,GPIO_u8PinID); break;
			case GPIO_U8_PORT_E: SET_BIT(GPIO_U8_PORTE,GPIO_u8PinID); break;
			case GPIO_U8_PORT_F: SET_BIT(GPIO_U8_PORTF,GPIO_u8PinID); break;
			case GPIO_U8_PORT_G: SET_BIT(GPIO_U8_PORTG,GPIO_u8PinID); break;
		}
		else if(GPIO_u8Value==GPIO_U8_LOW)
		{
			switch(GPIO_u8PortID)
			{
				case GPIO_U8_PORT_A: CLR_BIT(GPIO_U8_PORTA,GPIO_u8PinID); break;
				case GPIO_U8_PORT_B: CLR_BIT(GPIO_U8_PORTB,GPIO_u8PinID); break;
				case GPIO_U8_PORT_C: CLR_BIT(GPIO_U8_PORTC,GPIO_u8PinID); break;
				case GPIO_U8_PORT_D: CLR_BIT(GPIO_U8_PORTD,GPIO_u8PinID); break;
				case GPIO_U8_PORT_E: CLR_BIT(GPIO_U8_PORTE,GPIO_u8PinID); break;
				case GPIO_U8_PORT_F: CLR_BIT(GPIO_U8_PORTF,GPIO_u8PinID); break;
				case GPIO_U8_PORT_G: CLR_BIT(GPIO_U8_PORTG,GPIO_u8PinID); break;
			}
			Local_error= ES_OK;
		}
		
	}
	else
	{
		Local_error= ES_OUT_OF_RANGE;
	}
	return Local_error;
}
/*********************************************************************************************************************/
uint_8  GPIO_enumGetPinValue( uint_8 GPIO_u8PortID,uint_8 GPIO_u8PinID)
{

	uint_8 Local_u8value = 0;
	if((GPIO_u8PortID < 7)&&(GPIO_u8PinID<8))
	{
		switch(GPIO_u8PortID)
		{
			case GPIO_U8_PORT_A: Local_u8value = GET_BIT(GPIO_U8_PINA,GPIO_u8PinID); break;
			case GPIO_U8_PORT_B: Local_u8value = GET_BIT(GPIO_U8_PINB,GPIO_u8PinID); break;
			case GPIO_U8_PORT_C: Local_u8value = GET_BIT(GPIO_U8_PINC,GPIO_u8PinID); break;
			case GPIO_U8_PORT_D: Local_u8value = GET_BIT(GPIO_U8_PIND,GPIO_u8PinID); break;
			case GPIO_U8_PORT_E: Local_u8value = GET_BIT(GPIO_U8_PINE,GPIO_u8PinID); break;
			case GPIO_U8_PORT_F: Local_u8value = GET_BIT(GPIO_U8_PINF,GPIO_u8PinID); break;
			case GPIO_U8_PORT_G: Local_u8value = GET_BIT(GPIO_U8_PING,GPIO_u8PinID); break;
		}
	}
	else
	{

	}
	return Local_u8value;
	
}
