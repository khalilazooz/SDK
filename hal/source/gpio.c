/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include"gpio.h"
#include"gpio_register.h"

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
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


#define PORT_SELECT(port)			gau8_port_select[port]=0xff
#define PORT_DESELECT(port)			gau8_port_select[port]=0x00
#define PIN_SELECT(port,pin)		SET_BIT(gau8_port_select[port],pin)
#define PIN_DESELECT(port,pin)		CLR_BIT(gau8_port_select[port],pin)
#define PORT_NUMBERS				7
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static uint_8 gau8_port_select[PORT_NUMBERS]={0};

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/



sint_16  gpio_set_port_direction( uint_8 GPIO_PortID,uint_8 GPIO_Direction)
{
	sint_16 s16_retval = SUCCESS;

	if(GPIO_PortID < 7)
	{
		if(gau8_port_select[GPIO_PortID]!=0xff){
			PORT_SELECT(GPIO_PortID);
			switch(GPIO_PortID)
			{
			case GPIO_PORT_A: GPIO_DDRA = GPIO_Direction;break;
			case GPIO_PORT_B: GPIO_DDRB = GPIO_Direction; break;
			case GPIO_PORT_C: GPIO_DDRC = GPIO_Direction; break;
			case GPIO_PORT_D: GPIO_DDRD = GPIO_Direction; break;
			case GPIO_PORT_E: GPIO_DDRE = GPIO_Direction; break;
			case GPIO_PORT_F: GPIO_DDRF = GPIO_Direction; break;
			case GPIO_PORT_G: GPIO_DDRG = GPIO_Direction; break;
			}}
		else{
			s16_retval= GPIO_RE_SELECTED;
		}
	}
	else
	{
		s16_retval=GPIO_INVALED_ARGUMENT;
	}
	return s16_retval;
}
/******************************************************************************/
sint_16  gpio_set_pin_direction( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Direction)
{
	sint_16 s16_retval = SUCCESS;
	if((GPIO_PortID < 7)&&(GPIO_PinID <8))
	{
		if(!GET_BIT(gau8_port_select[GPIO_PortID],GPIO_PinID))
		{
			PIN_SELECT(GPIO_PortID,GPIO_PinID);

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


		}
		else
					{
						s16_retval= GPIO_RE_SELECTED;
					}
	}
	else
	{
		s16_retval= GPIO_INVALED_ARGUMENT;
	}
	return s16_retval;
}
/**************************************************************************/
sint_16  gpio_set_port_value( uint_8 GPIO_PortID,uint_8 GPIO_Value)
{

	sint_16 s16_retval = SUCCESS;

	if(GPIO_PortID < 7)
	{
		if(gau8_port_select[GPIO_PortID]==0xff){
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
		else{
			s16_retval=GPIO_NOT_SELECTED;
		}

	}
	else
	{
		s16_retval=GPIO_INVALED_ARGUMENT;
	}
	return s16_retval;
}
/*********************************************************************************************************************/
sint_16  gpio_set_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8 GPIO_Value)
{

	sint_16 s16_retval = SUCCESS;

	if((GPIO_PortID < 7)&&(GPIO_PinID<8))
	{
		if(GET_BIT(gau8_port_select[GPIO_PortID],GPIO_PinID)){
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
			s16_retval= GPIO_NOT_SELECTED;
		}

	}
	else
	{
		s16_retval= GPIO_INVALED_ARGUMENT;
	}
	return s16_retval;
}
/*********************************************************************************************************************/
sint_16 gpio_get_pin_value( uint_8 GPIO_PortID,uint_8 GPIO_PinID,uint_8* p)
{

	sint_16 s16_retval = SUCCESS;

	uint_8 Local_value = 0;
	if((GPIO_PortID < 7)&&(GPIO_PinID<8))
	{
		if(GET_BIT(gau8_port_select[GPIO_PortID],GPIO_PinID))
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
			s16_retval= GPIO_NOT_SELECTED;
		}
	}
	else
	{
		s16_retval= GPIO_INVALED_ARGUMENT;
	}
	*p=Local_value;
	return s16_retval;

}
void gpio_de_selsct_port(uint_8 GPIO_PortID)
{
	gpio_set_port_value(GPIO_PortID,GPIO_ALL_LOW);
	PORT_DESELECT(GPIO_PortID);
}
void gpio_de_select_pin(uint_8 GPIO_PortID,uint_8 GPIO_PinID)
{
	gpio_set_pin_value(GPIO_PortID,GPIO_PinID,GPIO_LOW);
	PIN_DESELECT(GPIO_PortID,GPIO_PinID);
}
