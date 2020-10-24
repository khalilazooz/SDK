/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "flash.h"
#include "debug.h"
#include <util/delay.h>
/***************************************************************/
/**************              Macros                *************/
/***************************************************************/
#define FLASH_LOG_ENABLE
#ifdef FLASH_LOG_ENABLE
#define FLASH_LOG(...)				SYS_LOGGER("[FLASH]: "__VA_ARGS__)
#define FLASH_LOG_ERR(...)			SYS_LOGGER_ERR("[FLASH]: "__VA_ARGS__)
#define FLASH_LOG_WRN(...)			SYS_LOGGER_WRN("[FLASH]: "__VA_ARGS__)
#define FLASH_LOG_INFO(...)			SYS_LOGGER_INFO("[FLASH]: "__VA_ARGS__)
#define FLASH_LOG_SUCC(...)			SYS_LOGGER_SUCC("[FLASH]: "__VA_ARGS__)
#else
#define FLASH_LOG(...)
#define FLASH_LOG_ERR(...)
#define FLASH_LOG_WRN(...)
#define FLASH_LOG_INFO(...)
#define FLASH_LOG_SUCC(...)
#endif


#define DATA_HEADER(data,size) {'D','=',data,'S','=',size}
#define DATA_HEADER_SZ			6	
#define EEPROM_START_ADDRESS	0x01


/*this for Atmega128 and should be under flag*/
#define MAX_EXCEED_EEPROM		(4086-DATA_HEADER_SZ)

/***************************************************************/
/**************            Global Variable         *************/
/***************************************************************/


/***************************************************************/
/**************            Static Variable         *************/
/***************************************************************/
static uint_16  pu16_data_exist_location[(uint_16)INVALID_SAVED_DATA] = {0};
static bool gb_flash_init = FALSE;
/***************************************************************/
/**************    Local APIs Impelementation     *************/
/***************************************************************/


static bool check_if_exist(enu_memory_type mem_typ,enu_saved_data svd_data,uint_16 * pu16_saving_address)
{
	bool b_retval = FALSE;
	switch(mem_typ)
	{
		case INTERNAL_EEPROM:
		{
			if (pu16_data_exist_location[svd_data] == 0)
			{
				bool b_found = FALSE;
				uint_16  u16_inc_address = EEPROM_START_ADDRESS;
				*pu16_saving_address = 0;
				while(!b_found)
				{
					uint_8	au8_header[DATA_HEADER_SZ]={0};
					eeprom_read_block((void *)au8_header,(const void *)u16_inc_address,DATA_HEADER_SZ);
					FLASH_LOG("%d %d\r\n",u16_inc_address,au8_header[1]);
					if(au8_header[0] == 'D' && au8_header[1] == '=' &&au8_header[3] == 'S' && au8_header[4] == '=')
						{
							if (au8_header[2]==svd_data)
							{
								b_retval = TRUE;
								b_found = TRUE;
								*pu16_saving_address = u16_inc_address;
							}
							else
							{
								u16_inc_address = u16_inc_address+DATA_HEADER_SZ+au8_header[5];
							}
						}
						else
						{
							b_found = TRUE;
							*pu16_saving_address = u16_inc_address;
						}
				}
			}
			else
			{
				b_retval = TRUE;
				*pu16_saving_address = pu16_data_exist_location[svd_data];
			}
		}
		break;
		case EXTERNAL_I2C_EEPROM:
		/*Not Developed yet*/
		break;
		case EXTERNAL_SPI_EEPROM:
		/*Not Developed yet*/
		break;
		default:
		break;
	}
	
	return b_retval;
}
/***************************************************************/
/**************      Interrupt Handler function    *************/
/***************************************************************/


/***************************************************************/
/**************    Global APIs Impelementation     *************/
/***************************************************************/

sint_16 flash_init(void)
{
	if (!gb_flash_init)
	{
		gb_flash_init = TRUE;
		memset((void *)pu16_data_exist_location,0,(uint_16)INVALID_SAVED_DATA);
	}
	return SUCCESS;
}


sint_16 flash_save(enu_memory_type mem_typ , enu_saved_data svd_data , uint_8 * data ,uint_16 data_size)
{
	sint_16 s16_retval = SUCCESS;
	if (mem_typ < INVALID_EEPROM && svd_data < INVALID_SAVED_DATA 
		&& data != NULL && data_size != 0)
	{
		switch(mem_typ)
		{
			case INTERNAL_EEPROM :
			{
				uint_16 u16_save_address;
				bool b_existance = check_if_exist(INTERNAL_EEPROM,svd_data,&u16_save_address);
				if (b_existance)
				{
					eeprom_write_block((const void *)data,( void *)(u16_save_address+DATA_HEADER_SZ),data_size);
					pu16_data_exist_location[svd_data]=u16_save_address;
				}
				else
				{
					if(u16_save_address < (MAX_EXCEED_EEPROM - data_size))
					{
						
						uint_8 header_data[DATA_HEADER_SZ] = DATA_HEADER(svd_data,data_size);
						eeprom_write_block((const void *)header_data,(void *)u16_save_address,DATA_HEADER_SZ);
						eeprom_write_block((const void *)data,( void *)(u16_save_address+DATA_HEADER_SZ),data_size);
						pu16_data_exist_location[svd_data]=u16_save_address;
					}
					else
					{
						FLASH_LOG_ERR("Exceed Maxmum Size");
						s16_retval = FLASH_EXCEED_MEMORY_SIZE;
					}
				}
			}
			break;
			case EXTERNAL_I2C_EEPROM:
			/*Not Developed yet*/
			break;
			case EXTERNAL_SPI_EEPROM:
			/*Not Developed yet*/
			break;
			default:
			break;
		}
	}
	else
	{
		s16_retval = FLASH_INVALID_ARGUMENT;
	}
	return s16_retval;
}


sint_16 flash_load(enu_memory_type mem_typ , enu_saved_data svd_data , uint_8 * data ,uint_16 data_size)
{
	sint_16 s16_retval = SUCCESS;
	if (mem_typ < INVALID_EEPROM && svd_data < INVALID_SAVED_DATA
	&& data != NULL && data_size != 0)
	{
		switch(mem_typ)
		{
			case INTERNAL_EEPROM:
			{
				uint_16 u16_save_address;
				bool b_existance = check_if_exist(INTERNAL_EEPROM,svd_data,&u16_save_address);
				if (b_existance)
				{
					eeprom_read_block((void *)data,(const void *)(u16_save_address+DATA_HEADER_SZ),data_size);
				}
				else
				{
					s16_retval = FLASH_NO_LOADED_DATA;
					FLASH_LOG_ERR("No loaded data");
				}
			}
			break;
			case EXTERNAL_I2C_EEPROM:
			/*Not Developed yet*/
			break;
			case EXTERNAL_SPI_EEPROM:
			/*Not Developed yet*/
			break;
			default:
			break;
		}
	}
	else
	{
		s16_retval = FLASH_INVALID_ARGUMENT;
	}
	return s16_retval;
}








