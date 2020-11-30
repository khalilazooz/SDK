/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "queue.h"
#include "common.h"
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/

//#define QUEUE_LOG_ENABLE
#ifdef QUEUE_LOG_ENABLE
#define QUEUE_LOG(...)				SYS_LOGGER("[QUEUE]: "__VA_ARGS__)
#define QUEUE_LOG_ERR(...)			SYS_LOGGER_ERR("[QUEUE]: "__VA_ARGS__)
#define QUEUE_LOG_WRN(...)			SYS_LOGGER_WRN("[QUEUE]: "__VA_ARGS__)
#define QUEUE_LOG_INFO(...)			SYS_LOGGER_INFO("[QUEUE]: "__VA_ARGS__)
#define QUEUE_LOG_SUCC(...)			SYS_LOGGER_SUCC("[QUEUE]: "__VA_ARGS__)
#else
#define QUEUE_LOG(...)
#define QUEUE_LOG_ERR(...)
#define QUEUE_LOG_WRN(...)
#define QUEUE_LOG_INFO(...)
#define QUEUE_LOG_SUCC(...)
#endif
/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/


/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/

static bool queue_is_full(tstr_queue * str_queue)
{
	return (str_queue->u16_current_size == str_queue->u16_capacity);
}

static bool queue_is_empty(tstr_queue * str_queue)
{
	return (str_queue->u16_current_size == 0);
}

/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 queue_init(tstr_queue * str_queue, uint_8 * pau8_queue_array,uint_8 u8_array_size ,uint_8 u8_element_size)
{
	sint_16 s32_retval = SUCCESS;
	if((str_queue != NULL) && (pau8_queue_array != NULL) && (u8_array_size != 0) && (u8_element_size != 0))
	{
		str_queue->u16_current_size = 0;
		str_queue->u16_front = 0;
		str_queue->u16_capacity = (u8_array_size * u8_element_size);
		str_queue->u16_rear = ((u8_array_size-1) * u8_element_size);
		str_queue->u8_element_size = u8_element_size;
		str_queue->pu8_queue_array = pau8_queue_array ;
		str_queue->b_queue_is_initialized = TRUE;
	}
	else
	{
		s32_retval = QUEUE_INVALID_ARRGUMENT ;
	}
	return s32_retval;
}

sint_16 queue_enqueue(tstr_queue * str_queue, void * item)
{
	sint_16 s32_retval = SUCCESS;
	if(str_queue != NULL && item != NULL)
	{
		if(str_queue->b_queue_is_initialized)
		{
			if(!queue_is_full(str_queue))
			{
				str_queue->u16_rear = (str_queue->u16_rear + str_queue->u8_element_size) % str_queue->u16_capacity;
				MEMCPY(&str_queue->pu8_queue_array[str_queue->u16_rear],item,str_queue->u8_element_size);
				str_queue->u16_current_size += str_queue->u8_element_size;
				QUEUE_LOG("the element added in the queue\r\n");
			}
			else
			{
				s32_retval = QUEUE_IS_FULL ;
			}
		}
		else
		{
			s32_retval = QUEUE_NOT_INTIALIZED ;
		}
	}
	else
	{
		s32_retval = QUEUE_INVALID_ARRGUMENT ;
	}
	return s32_retval;
}


sint_16 queue_dequeue(tstr_queue * str_queue, void * item)
{
	sint_16 s32_retval = SUCCESS;
	if(str_queue != NULL && item != NULL)
	{
		if(str_queue->b_queue_is_initialized)
		{
			if(!queue_is_empty(str_queue))
			{
				MEMCPY(item,&str_queue->pu8_queue_array[str_queue->u16_front],str_queue->u8_element_size);
				str_queue->u16_front = (str_queue->u16_front + str_queue->u8_element_size) % str_queue->u16_capacity;
				str_queue->u16_current_size -= str_queue->u8_element_size;
				QUEUE_LOG("the element returned from the queue\r\n");
			}
			else
			{
				s32_retval = QUEUE_IS_EMPTY ;
			}
		}
		else
		{
			s32_retval = QUEUE_NOT_INTIALIZED ;
		}
	}
	else
	{
		s32_retval = QUEUE_INVALID_ARRGUMENT ;
	}
	return s32_retval;
}


sint_16 queue_element_existance(tstr_queue * str_queue, void * item ,bool * b_found)
{
	sint_16 s32_retval = SUCCESS;
	*b_found = FALSE;
	if(str_queue != NULL && item != NULL)
	{
		if(str_queue->b_queue_is_initialized)
		{
			if(!queue_is_empty(str_queue))
			{
				uint_16 u16_i = 0 ;
				for(u16_i = str_queue->u16_front ; u16_i< str_queue->u16_rear ;u16_i=(u16_i+str_queue->u8_element_size))
				{
					if(0==MEMCMP(&str_queue->pu8_queue_array[u16_i] , item,str_queue->u8_element_size))
					{
						*b_found = TRUE;
						break;
					}
				}
			}
			else
			{
				s32_retval = QUEUE_IS_EMPTY ;
			}
		}
		else
		{
			s32_retval = QUEUE_NOT_INTIALIZED ;
		}
	}
	else
	{
		s32_retval = QUEUE_INVALID_ARRGUMENT ;
	}
	return s32_retval;
}


sint_16 queue_get_fornt(tstr_queue * str_queue, void * item )
{
	sint_16 s32_retval = SUCCESS;
	if(str_queue != NULL && item != NULL)
	{
		if(str_queue->b_queue_is_initialized)
		{
			if(!queue_is_empty(str_queue))
			{
				MEMCPY(item,&str_queue->pu8_queue_array[str_queue->u16_front],str_queue->u8_element_size);
			}
			else
			{
				s32_retval = QUEUE_IS_EMPTY ;
			}
		}
		else
		{
			s32_retval = QUEUE_NOT_INTIALIZED ;
		}
	}
	else
	{
		s32_retval = QUEUE_INVALID_ARRGUMENT ;
	}
	return s32_retval;
}

