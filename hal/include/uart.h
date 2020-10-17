#ifndef _UART_H_
#define _UART_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define MAX_BUFF_NUM	150
#define uart_printf(...)	{	\
								sint_8 sBuff[MAX_BUFF_NUM]={0};\
								sprintf(sBuff,__VA_ARGS__);\
								uart_send(sBuff,MAX_BUFF_NUM);\
								\
							}
							
							
							
							
#define UART_INITIALIZATION_ERROR		UART_ERROR_BASE - 1
#define UART_INVALID_ARGUMENT			UART_ERROR_BASE - 2							
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/

typedef enum _tenu_uart_baudrate
{
	UART_BAUDRATE_4800,
	UART_BAUDRATE_9600,
	UART_BAUDRATE_14400 ,
	UART_BAUDRATE_19200 ,
	UART_BAUDRATE_38400,
	UART_BAUDRATE_57600 ,
	UART_BAUDRATE_115200 ,
	UART_BAUDRATE_INVALID,
}tenu_uart_baudrate;


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/


sint_16 uart_init(tenu_uart_baudrate enu_boadrate);



sint_16 uart_deinit(void);



sint_16 uart_send(sint_8 * s8_data , uint_8 len);

#endif  /*_UART_H_*/