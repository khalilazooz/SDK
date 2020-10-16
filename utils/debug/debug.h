#ifndef _DEBUG_H_
#define _DEBUG_H_

/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"
#include "uart.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#ifdef DEBUG_ENABLE

#define SYS_LOGGER_INIT(baudrate)		uart_init(baudrate)

#define SYS_LOGGER_DEINIT()			uart_deinit()

#define SYS_LOGGER(...)					uart_printf(__VA_ARGS__)

#define SYS_LOGGER_ERR(...)				{\
											uart_printf("\033[0;31m Error in fun <%s> Line <%d>",__FUNCTION__,__LINE__);\
											uart_printf(__VA_ARGS__);\
											uart_printf("\033[0m \r\n");\
										}									
#define SYS_LOGGER_WRN(...)				{\
											uart_printf("\033[0;33m"__VA_ARGS__);\
											uart_printf("\033[0m \r\n");\
										}									
#define SYS_LOGGER_INFO(...)			{\
											uart_printf("\033[0;34m"__VA_ARGS__);\
											uart_printf("\033[0m \r\n");\
										}	
#define SYS_LOGGER_SUCC(...)			{\
											uart_printf("\033[0;32m"__VA_ARGS__);\
											uart_printf("\033[0m \r\n");\
										}	
								
								
#else
#define SYS_LOGGER_INIT(baudrate)	
#define SYS_LOGGER_DEINIT()			
#define SYS_LOGGER(...)				    	 
#define SYS_LOGGER_ERR(...)				 
#define SYS_LOGGER_WRM(...)				 
#define SYS_LOGGER_INFO(...)			 
#define SYS_LOGGER_SUCC(...)			 
#endif











/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/










#endif /*_DEBUG_H_*/