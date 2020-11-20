
#ifndef _QUEUE_H_
#define _QUEUE_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"


/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

#define QUEUE_INVALID_ARRGUMENT 		(QUEUE_ERROR_BASE-1)
#define QUEUE_NOT_INTIALIZED 			(QUEUE_ERROR_BASE-2)
#define QUEUE_IS_FULL					(QUEUE_ERROR_BASE-3)
#define QUEUE_IS_EMPTY					(QUEUE_ERROR_BASE-4)
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/


/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/
typedef struct _tstr_queue
{
	bool b_queue_is_initialized;
	uint_16 u16_front;
	uint_16 u16_rear;
	uint_16 u16_current_size ;
	uint_16 u16_capacity ;
	uint_8	u8_element_size ;



	/*queue array*/
	uint_8 * pu8_queue_array ;
}tstr_queue;

/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 queue_init(tstr_queue * str_queue, uint_8 * pau8_queue_array,uint_8 u8_array_size ,uint_8 u8_element_size);
sint_16 queue_dequeue(tstr_queue * str_queue, void * item);
sint_16 queue_enqueue(tstr_queue * str_queue, void * item);
sint_16 queue_element_existance(tstr_queue * str_queue, void * item ,bool * b_found);
sint_16 queue_get_fornt(tstr_queue * str_queue, void * item );
#endif /*_QUEUE_H_*/





