/**************************************************************************//**
 * @file     ebi_nor.h
 * @version  V2.00
 * $Revision: 2 $
 * $Date: 14/01/28 11:44a $
 * @brief    NOR Flash - W39L040P Driver Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EBI_NOR_H__
#define __EBI_NOR_H__

#ifdef __cplusplus
extern "C"
{
#endif


/*---------------------------------------------------------------------------------------------------------*/
/* Define EBI_NOR Functions Prototype                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
void NOR_Init(void);
void NOR_Reset(void);
uint32_t NOR_GetID(void);
uint8_t NOR_Erase(void);
uint8_t NOR_CheckCMDComplete(uint32_t u32DestAddr, uint8_t u8Data);
uint8_t NOR_ReadData(uint32_t u32DestAddr);
uint8_t NOR_WriteData(uint32_t u32DestAddr, uint8_t u8Data);

#ifdef __cplusplus
}
#endif

#endif //__EBI_NOR_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
