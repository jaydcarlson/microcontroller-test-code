/**************************************************************************//**
 * @file     ebi_nor.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 14/01/28 11:43a $
 * @brief    NOR Flash - W39L040P Driver Source File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"
#include "ebi_nor.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint8_t *g_pu8NorBaseAddr;


/**
 * @brief       NOR Flash Initial
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     Initial and reset NOR Flash - W39L040P.
 */
void NOR_Init(void)
{
    g_pu8NorBaseAddr = (uint8_t *)EBI_BASE_ADDR;

    /* Reset NOR Flash */
    NOR_Reset();
}

/**
 * @brief       Reset NOR Flash
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     Reset NOR Flash - W39L040P.
 */
void NOR_Reset(void)
{
    *(g_pu8NorBaseAddr + 0x5555) = 0xAA;
    *(g_pu8NorBaseAddr + 0x2AAA) = 0x55;
    *(g_pu8NorBaseAddr + 0x0000) = 0xF0;
}

/**
 * @brief       Get ID of NOR Flash
 *
 * @param[in]   None
 *
 * @return      Return Manufacture ID and Device ID
 *
 * @details     Return the ID of W39L040P and Manufacture ID should be 0xDA, Device ID should be 0x31.
 */
uint32_t NOR_GetID(void)
{
    uint8_t u8ManuFactureID, u8DeviceID;

    *(g_pu8NorBaseAddr + 0x5555) = 0xAA;
    *(g_pu8NorBaseAddr + 0x2AAA) = 0x55;
    *(g_pu8NorBaseAddr + 0x5555) = 0x90;
    CLK_SysTickDelay(10);

    u8ManuFactureID = *(g_pu8NorBaseAddr + 0x0);
    u8DeviceID      = *(g_pu8NorBaseAddr + 0x1);

    *(g_pu8NorBaseAddr + 0x5555) = 0xAA;
    *(g_pu8NorBaseAddr + 0x2AAA) = 0x55;
    *(g_pu8NorBaseAddr + 0x5555) = 0xF0;
    CLK_SysTickDelay(10);

    return ((u8ManuFactureID << 8) | u8DeviceID);
}

/**
 * @brief       NOR Flash Chip Erase
 *
 * @param[in]   None
 *
 * @retval      FALSE       Erase command fail
 * @retval      TRUE        Erase command pass
 *
 * @details     W39L040P whole chip erase.
 */
uint8_t NOR_Erase(void)
{
    uint8_t u8Status;

    *(g_pu8NorBaseAddr + 0x5555) = 0xAA;
    *(g_pu8NorBaseAddr + 0x2AAA) = 0x55;
    *(g_pu8NorBaseAddr + 0x5555) = 0x80;
    *(g_pu8NorBaseAddr + 0x5555) = 0xAA;
    *(g_pu8NorBaseAddr + 0x2AAA) = 0x55;
    *(g_pu8NorBaseAddr + 0x5555) = 0x10;

    u8Status = NOR_CheckCMDComplete(0x0, 0x0);
    if(u8Status == FALSE)
        return FALSE;

    CLK_SysTickDelay(200000);

    return TRUE;
}

/**
 * @brief       Check Command Complete
 *
 * @param[in]   u32Addr     The address to read out data to check if command complete
 * @param[in]   u8Data      The data to be compared with the read out data
 *
 * @retval      FALSE       Command fail
 * @retval      TRUE        Command complete
 *
 * @details     Check if the specified command is complete or not.
 */
uint8_t NOR_CheckCMDComplete(uint32_t u32Addr, uint8_t u8Data)
{
    /* Using Data Polling Algorithm to check if command is complete or not */
    uint8_t u8CurData;
    volatile uint32_t u32TimeOutCnts = 0;

    /* Command timeout period is 200 ms */
    u8Data = u8Data & (1 << 7); // read D7
    while(u32TimeOutCnts < 200000)
    {
        u8CurData = NOR_ReadData(u32Addr);
        u8CurData = u8CurData & (1 << 7); // read DQ7
        if(u8Data == u8CurData)
        {
            return TRUE;
        }
        CLK_SysTickDelay(1);
        u32TimeOutCnts++;
    }

    return FALSE;
}

/**
 * @brief       Read Data from NOR Flash
 *
 * @param[in]   u32DstAddr The target address of read command
 *
 * @return      Return the data
 *
 * @details     Read the date from specified address.
 */
uint8_t NOR_ReadData(uint32_t u32DestAddr)
{
    return *(g_pu8NorBaseAddr + u32DestAddr);
}

/**
 * @brief       Write Data to NOR Flash
 *
 * @param[in]   u32DstAddr The target address of write command
 * @param[in]   u8Data      The target data for write command
 *
 * @retval      FALSE       Write command fail
 * @retval      TRUE        Write command pass
 *
 * @details     Write the date to specified address.
 */
uint8_t NOR_WriteData(uint32_t u32DestAddr, uint8_t u8Data)
{
    *(g_pu8NorBaseAddr + 0x5555) = 0xAA;
    *(g_pu8NorBaseAddr + 0x2AAA) = 0x55;
    *(g_pu8NorBaseAddr + 0x5555) = 0xA0;

    *(g_pu8NorBaseAddr + u32DestAddr) = u8Data;

    return NOR_CheckCMDComplete(u32DestAddr, u8Data);
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
