/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include "common.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/



/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/



/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/




/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

void sys_memcpy(void * ps8_dest ,const void * ps8_src , uint_16 u16_sz )
{
	uint_8 * ps8_cdest = (uint_8 *) ps8_dest ;
	const uint_8 * ps8_csrc = (const uint_8 *) ps8_src ;
	uint_8 u16_i = 0 ;
	for(u16_i = 0 ; u16_i < u16_sz;u16_i++)
	{
		ps8_cdest[u16_i] = ps8_csrc[u16_i];
	}
}


void sys_memset(void * ps8_dest ,const uint_8 u8_watermark, uint_16 u16_sz )
{
	uint_8 * ps8_cdest = (uint_8 *) ps8_dest ;
	uint_8 u16_i = 0 ;
	for(u16_i = 0 ; u16_i < u16_sz;u16_i++)
	{
		ps8_cdest[u16_i] = u8_watermark;
	}
}

sint_8 sys_memcmp(const void * str1 ,const void * str2 , uint_8 u8_sz )
{
	  register const unsigned char *s1 = (const unsigned char*)str1;
	  register const unsigned char *s2 = (const unsigned char*)str2;
	  while (u8_sz-- > 0)
	    {
	      if (*s1++ != *s2++)
	          return s1[-1] < s2[-1] ? -1 : 1;
	    }
	  return 0;
}

double sys_pow(uint_16 u16_data1 , uint_16 u16_data2)
{
	uint_16 u16_i;
	double retval = 1;
	for(u16_i = 0 ; u16_i< u16_data2; u16_i++)
	{
		retval *=u16_data1;
	}
	return retval;
}

