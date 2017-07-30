/**************************************************************************//**
 * @file     EEPROM_24LC64.h
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series 24LC64 EEPROM library header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef __EEPROM_24LC64_H__
#define __EEPROM_24LC64_H__

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
extern void EEPROM_Init(void);
extern void EEPROM_Write(uint32_t address, uint8_t data);
extern uint8_t EEPROM_Read(uint32_t address);
extern void EEPROM_PageWrite(uint32_t u32Addr, uint8_t *pu8Buf);
extern uint8_t EEPROM_SequentialRead(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Size);

#endif
