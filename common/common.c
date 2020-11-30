/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include "common.h"
#include "debug.h"
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

double sys_pow(double u16_data1 , uint_16 u16_data2)
{
	uint_16 u16_i;
	double retval = 1;
	for(u16_i = 0 ; u16_i< u16_data2; u16_i++)
	{
		retval *=u16_data1;
	}
	return retval;
}


float sys_ln(float y)
{
    // Algo from: https://stackoverflow.com/a/18454010
    // Accurate between (1 / scaling factor) < y < (2^32  / scaling factor). Read comments below for more info on how to extend this range

	float divisor, x, result;
    const float LN_2 = 0.69314718; //pre calculated constant used in calculations
    sint_32 log2 = 0;
    //handle if input is less than zero
    if (y <= 0)
    {
        return -1;
    }
    //scaling factor. The polynomial below is accurate when the input y>1, therefore using a scaling factor of 256 (aka 2^8) extends this to 1/256 or ~0.04. Given use of uint32_t, the input y must stay below 2^24 or 16777216 (aka 2^(32-8)), otherwise uint_y used below will overflow. Increasing the scaing factor will reduce the lower accuracy bound and also reduce the upper overflow bound. If you need the range to be wider, consider changing uint_y to a uint64_t
    const sint_32 SCALING_FACTOR = 256;
    const float LN_SCALING_FACTOR = 5.545177444; //this is the natural log of the scaling factor and needs to be precalculated
    y = y * SCALING_FACTOR;
    sint_32 uint_y = (sint_32)y;
    while (uint_y >>= 1) // Convert the number to an integer and then find the location of the MSB. This is the integer portion of Log2(y). See: https://stackoverflow.com/a/4970859/6630230
    {
        log2++;
    }
    divisor = sys_pow(2 , log2);
    x = y / divisor;    // FInd the remainder value between [1.0, 2.0] then calculate the natural log of this remainder using a polynomial approximation
    result = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x; //This polynomial approximates ln(x) between [1,2]
    result = result + ((float)log2) * LN_2 - LN_SCALING_FACTOR; // Using the log product rule Log(A) + Log(B) = Log(AB) and the log base change rule log_x(A) = log_y(A)/Log_y(x), calculate all the components in base e and then sum them: = Ln(x_remainder) + (log_2(x_integer) * ln(2)) - ln(SCALING_FACTOR)
    return result;
}
