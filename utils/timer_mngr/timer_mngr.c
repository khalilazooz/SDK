/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include <avr/io.h>
#include "common.h"
#include "timer.h"
#include "timer_mngr.h"
#include "debug.h"
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
//#define TIMER_MGMT_LOG_ENABLE

#ifdef TIMER_MGMT_LOG_ENABLE
#define TMR_LOG(...)				SYS_LOGGER("[TM]: "__VA_ARGS__)
#define TMR_LOG_ERR(...)			SYS_LOGGER_ERR("[TM]: "__VA_ARGS__)
#define TMR_LOG_WRN(...)			SYS_LOGGER_WRN("[TM]: "__VA_ARGS__)
#define TMR_LOG_INFO(...)			SYS_LOGGER_INFO("[TM]: "__VA_ARGS__)
#define TMR_LOG_SUCC(...)			SYS_LOGGER_SUCC("[TM]: "__VA_ARGS__)
#else
#define TMR_LOG(...)
#define TMR_LOG_ERR(...)
#define TMR_LOG_WRN(...)
#define TMR_LOG_INFO(...)
#define TMR_LOG_SUCC(...)
#endif


/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/


static tstr_timer_mgmt_ins * gstr_head = NULL ;
static bool gb_init = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/
static void remove_timer_lst(tstr_timer_mgmt_ins **head,tstr_timer_mgmt_ins * node)
{
	if (node == (*head))
	{
		(*head)= (*head)->next;
	}else
	{
		tstr_timer_mgmt_ins * temp = *head ;
		while (temp->next != NULL && temp->next != node)
		{
			temp = temp->next;
		}
		if (temp->next == node)
		{
			temp->next = node->next;
		}
	}
	if (*head == NULL)
	{
		stop_hal_timer();
	}
}


static bool timer_exist(tstr_timer_mgmt_ins ** head,tstr_timer_mgmt_ins * node)
{
	bool b_retval = FALSE;
	tstr_timer_mgmt_ins * temp = (*head);
	while(temp != NULL)
	{
		if(temp == node)
		{
			b_retval = TRUE;
			break;
		}
		temp = temp->next;
	}
	return b_retval;
}
static void add_timer_lst(tstr_timer_mgmt_ins ** head,tstr_timer_mgmt_ins * node)
{
	tstr_timer_mgmt_ins * temp = *head ;
	if (*head == NULL)
	{
		*head = node;
	}
	else if((*head)->u16_timer_100ms_remain > node->u16_timer_100ms_remain)
	{
		node->next = *head;
		*head = node;
	}
	else
	{
		while (temp->next != NULL && temp->next->u16_timer_100ms_remain < node->u16_timer_100ms_remain)
		{
			temp = temp->next;
		}
		if (temp->next != NULL)
		{
			node->next = temp->next;
			temp->next = node;
		}
		else
		{
			temp->next = node;
		}
		
	}
}


static void timer_cb(void)
{
	tstr_timer_mgmt_ins *temp = gstr_head;
	while(temp != NULL)
	{
		temp->u16_timer_100ms_remain--;
		if (temp->u16_timer_100ms_remain == 0)
		{
			temp->pf_timer_cb(temp->arg_cb);
			temp->timer_enable = FALSE;
			remove_timer_lst(&gstr_head , temp);
		}
		temp = temp->next;
	}
	start_hal_timer(1);
}
/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 timer_mgmt_init(void)
{
	timer_init(timer_cb);
	gb_init = TRUE;
	return SUCCESS;
}
sint_16 timer_mgmt_deinit()
{
	return SUCCESS;
}
sint_16 start_timer(tstr_timer_mgmt_ins * timer_inst, uint_16 time_100ms  , void(*pf_cb)(void * arg) , void * arg)
{
	if (timer_inst->timer_enable == FALSE)
	{
		if (!timer_exist(&gstr_head,timer_inst))
		{
			if (gstr_head == NULL)
			{
				if (gb_init)
				{
					start_hal_timer(1);
				}else
				{
					TMR_LOG_ERR("Can not start before timer init");
				}
			}
			timer_inst->u16_timer_100ms_remain = time_100ms;
			timer_inst->u16_timer_100ms = time_100ms;
			timer_inst->pf_timer_cb = pf_cb ;
			timer_inst->arg_cb = arg;
			timer_inst->timer_enable = TRUE;
			timer_inst->next = NULL;
			add_timer_lst(&gstr_head,timer_inst);

		}
	}
	else
	{
		TMR_LOG_INFO("This timer is aready exist!");
	}
	return SUCCESS;
}
sint_16 stop_timer(tstr_timer_mgmt_ins * timer_inst)
{
	if (timer_inst != NULL)
	{
		if(timer_inst->timer_enable == TRUE)
		{
			if (timer_exist(&gstr_head,timer_inst))
			{
				remove_timer_lst(&gstr_head,timer_inst);
				timer_inst->timer_enable = FALSE;
			}
		}
	}
	return SUCCESS;
}

sint_16 reset_timer(tstr_timer_mgmt_ins * timer_inst)
{
	if (timer_inst != NULL)
	{
		if (timer_exist(&gstr_head,timer_inst))
		{
			timer_inst->u16_timer_100ms_remain = timer_inst->u16_timer_100ms;
		}
	}
	return SUCCESS;
}
sint_16 get_time()
{
	return SUCCESS;
}
