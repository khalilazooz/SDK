/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/interrupt.h>
#include "gpio.h"
#include "common.h"
#include "uart.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define BAUDRATE(BAUD) ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/
static bool gb_uart_init = FALSE;

/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
volatile uint_8 tx_buffer[3];
volatile uint_8 rx_buffer[16];
volatile uint_8 tx_bytes = 0;
volatile uint_16 rx_bytes = 0;
volatile uint_16 tx_buffer_pos = 0;
volatile uint_8 rx_buffer_pos = 0;
volatile bool gb_error_handle = FALSE;

/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/
ISR(USART0__UDRE_vect) {
	if (tx_buffer_pos < tx_bytes && gb_error_handle == FALSE) {
		UDR0 = tx_buffer[(tx_buffer_pos++ & 0x03)];
	}
	else {
		UCSR0B &= ~(1 << UDRIE0);
		tx_bytes = 0;
		tx_buffer_pos = 0;
		gb_error_handle = FALSE;
	}
}
#ifdef UART_RECEIVE_ENABLE
ISR(USART0__RX_vect) {
	rx_buffer[rx_buffer_pos++ & 0x0F] = UDR0;
}
#endif


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 uart_init(tenu_uart_baudrate enu_boadrate)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_uart_init == FALSE)
	{
		if(enu_boadrate < UART_BAUDRATE_INVALID)
		{
		//	DDRE |= (1 << PORTE1);     // set pin 3 of Port B as output
			uint_32 baud;
			switch (enu_boadrate)
			{
				case UART_BAUDRATE_4800:
				baud= 4800;
				break;
				case UART_BAUDRATE_9600:
				baud= 9600;
				break;
				case UART_BAUDRATE_14400:
				baud= 14400;
				break;
				case UART_BAUDRATE_19200:
				baud= 19200;
				break;
				case UART_BAUDRATE_38400:
				baud= 38400;
				break;
				case UART_BAUDRATE_57600:
				baud= 57600;
				break;
				case UART_BAUDRATE_115200:
				baud= 115200;
				break;
				default:
				baud= 9600;
				break;
			};
			gb_uart_init = TRUE;
			UBRR0H = (BAUDRATE(baud)>>8);
			UBRR0L = BAUDRATE(baud);
			UCSR0B|= (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
			UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01);
			SREG  |= (1<< 7); // enable global interrupt
		}
		else
		{
			s16_retval = UART_INITIALIZATION_ERROR;
		}
	}
	return s16_retval;
}
sint_16 uart_deinit(void)
{
	sint_16 s16_retval = SUCCESS;
	if(gb_uart_init == TRUE)
	{
		gb_uart_init = FALSE;
		UBRR0H = 0;                     
		UBRR0L = 0;                          
		UCSR0B = 0;                
		UCSR0C = 0;   
	}
	return s16_retval;
}

sint_16 uart_send(sint_8 * s8_data , uint_8 len)
{
	sint_16 s16_retval = SUCCESS;
	
	if(len != 0 && s8_data != NULL)
	{
		uint_8 i = 0;
		
		for(i = 0; i < len; i++) {
			if (s8_data[i] == '\0' )
			{
				break;
			}
			while (tx_bytes >= (tx_buffer_pos + 0x03) && ((UCSR0A & (1<< UDRE0)) == 0));
			if(tx_bytes >= (tx_buffer_pos + 0x03))
			{
				gb_error_handle = TRUE;
			}
			uint_8 index = tx_bytes & 0x03;
			tx_buffer[index] = s8_data[i];
			tx_bytes++;
			UCSR0B |= (1 << UDRIE0);
		}
		
	}		
	else
	{
		s16_retval =UART_INVALID_ARGUMENT;
	}
	
	return s16_retval;
}

#if UART_RECEIVE_ENABLE
uint_8 usart_recv(char * data, uint_8 len, uint_16 o_timeout) {
	uint_8 i;
	uint_16 timeout = o_timeout;
	for (i = 0; i < len; i++) {
		while (rx_bytes >= rx_buffer_pos) {
			_delay_us(250);
			if ((timeout-- == 0) && (o_timeout > 0)) {
				return i;
			}
		}
		timeout = o_timeout;
		if (rx_bytes < rx_buffer_pos) {
			data[i] = rx_buffer[rx_bytes & 0x0F];
			rx_bytes++;
		}
	}
	return i;
}
#endif
