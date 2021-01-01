
#ifndef _COMMON_H_
#define _COMMON_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define MEMCPY				sys_memcpy
#define MEMCMP				sys_memcmp
#define POW					sys_pow
#define MEMSET				sys_memset
#define LN					sys_ln
#define EXP					sys_exp

#define ERROR_BREAK(input)	{\
								if(input != SUCCESS)\
								{\
									break;\
								}\
							}

/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/

void sys_memcpy(void * ps8_dest ,const void * ps8_src , uint_16 u16_sz );
void sys_memset(void * ps8_dest ,const uint_8 u8_watermark, uint_16 u16_sz);
sint_8 sys_memcmp(const void * str1 ,const void * str2 , uint_8 u8_sz );
double sys_pow(double u16_data1 , uint_16 u16_data2);
float sys_ln(float y);
float sys_exp(float data);
#endif /*_COMMON_H_*/





