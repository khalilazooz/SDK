
#ifndef _FLASH_H_
#define _FLASH_H_
/***************************************************************/
/**************             includes               *************/
/***************************************************************/
#include "Basictypes.h"

#include <avr/eeprom.h>

/***************************************************************/
/**************              Macros                *************/
/***************************************************************/


#define FLASH_INVALID_ARGUMENT			FLASH_ERROR_BASE-1	

#define FLASH_EXCEED_MEMORY_SIZE		FLASH_ERROR_BASE-2

#define FLASH_NO_LOADED_DATA			FLASH_ERROR_BASE-3
/***************************************************************/
/**************       Global Extern Variables      *************/
/***************************************************************/

/***************************************************************/
/************         Structure and Unions         *************/
/***************************************************************/


/***************************************************************/
/**************					Enumes		       *************/
/***************************************************************/

typedef enum _enu_memory_type
{
	INTERNAL_EEPROM = 0,
	EXTERNAL_I2C_EEPROM,
	EXTERNAL_SPI_EEPROM,
	INVALID_EEPROM,
}enu_memory_type;


typedef enum _enu_saved_data
{
	TEMPERATURE_SET_POINT = 0,
	TEMPERATURE_SET_POINT2,
	TEMPERATURE_SET_POINT3,
	INVALID_SAVED_DATA,
}enu_saved_data;


/***************************************************************/
/**************     Global APIs DECELERATIONs      *************/
/***************************************************************/
sint_16 flash_init(void);
sint_16 flash_save(enu_memory_type mem_typ , enu_saved_data svd_data , uint_8 * data ,uint_16 data_size);
sint_16 flash_load(enu_memory_type mem_typ , enu_saved_data svd_data , uint_8 * data ,uint_16 data_size);

#endif /*_FLASH_H_*/







