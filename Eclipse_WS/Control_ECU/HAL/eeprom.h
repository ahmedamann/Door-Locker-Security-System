 /******************************************************************************
 *
 * Module: eeprom
 *
 * File Name: eeprom.h
 *
 * Description: The Header File for the eeprom Driver.
 *
 ********************************************************************************/

#ifndef HAL_EEPROM_H_
#define HAL_EEPROM_H_

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/
#include "../lib/std_types.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);


#endif /* HAL_EEPROM_H_ */
