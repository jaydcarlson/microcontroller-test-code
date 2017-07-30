/**************************************************************************//**
 * @file     spi_flash_fifo.c
 * @version  V0.10
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series SPI Flash driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M051Series.h"



/**
  * @brief  Read SPI flash manufacturer ID and device ID.
  * @param  spi is the base address of SPI module.
  * @return High byte is manufacturer ID; low byte is device ID.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
uint32_t SpiFlash_ReadMidDid(SPI_T *spi)
{
    uint32_t u32MID_DID;

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x90: Read Manufacturer/Device ID */
    SPI_WRITE_TX0(spi, 0x90);
    /* Send 24 '0' dummy bits */
    SPI_WRITE_TX0(spi, 0x00);
    SPI_WRITE_TX0(spi, 0x00);
    SPI_WRITE_TX0(spi, 0x00);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);
    /* Clear RX FIFO */
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;

    /* Get the MID & DID */
    SPI_WRITE_TX0(spi, 0x00);
    SPI_WRITE_TX0(spi, 0x00);
    while(SPI_GET_RX_FIFO_EMPTY_FLAG(spi));
    u32MID_DID = spi->RX0 << 8;
    while(SPI_GET_RX_FIFO_EMPTY_FLAG(spi));
    u32MID_DID |= spi->RX0;

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    return u32MID_DID;
}

/**
  * @brief  Erase whole SPI flash memory.
  * @param  spi is the base address of SPI module.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_ChipErase(SPI_T *spi)
{

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x06: Write enable */
    SPI_WRITE_TX0(spi, 0x06);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    __NOP();

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0xC7: Chip erase */
    SPI_WRITE_TX0(spi, 0xC7);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    /* Clear RX FIFO */
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;
}

/**
  * @brief  Read SPI flash status register.
  * @param  spi is the base address of SPI module.
  * @return Status register value.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
uint32_t SpiFlash_ReadStatusReg(SPI_T *spi)
{
    /* Clear RX FIFO */
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x05: Read status register */
    SPI_WRITE_TX0(spi, 0x05);
    SPI_WRITE_TX0(spi, 0x00);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    /* Read out the dummy datum */
    spi->RX0;
    /* Return the status register value */
    return (spi->RX0);
}

/**
  * @brief  Write SPI flash status register.
  * @param  spi is the base address of SPI module.
  * @param  u32Value is the value attempt to write to status register.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_WriteStatusReg(SPI_T *spi, uint32_t u32Value)
{
    /* /CS: active */
    SPI_SET_SS_LOW(spi);
    /* Send command 0x06: Write enable */
    SPI_WRITE_TX0(spi, 0x06);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);
    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    __NOP();

    /* /CS: active */
    SPI_SET_SS_LOW(spi);
    /* Send command 0x01: Write status register */
    SPI_WRITE_TX0(spi, 0x01);
    /* write to status register 1 */
    SPI_WRITE_TX0(spi, u32Value & 0xFF);
    /* write to status register 2 */
    SPI_WRITE_TX0(spi, (u32Value >> 8) & 0xFF);

    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);
    /* Clear RX FIFO */
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);
}

/**
  * @brief  Wait SPI flash ready.
  * @param  spi is the base address of SPI module.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_WaitReady(SPI_T *spi)
{
    while((SpiFlash_ReadStatusReg(spi)) & 1); /* check the busy status bit */
}

/**
  * @brief  Perform SPI flash page program.
  * @param  spi is the base address of SPI module.
  * @param  u32StartAddress is the start address.
  * @param  au8DataBuffer is the pointer of source data.
  * @param  u32ByteCount is the total data count. The maximum number is 256.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_PageProgram(SPI_T *spi, uint32_t u32StartAddress, uint8_t *au8DataBuffer, uint32_t u32ByteCount)
{
    uint32_t u32Counter;

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x06: Write enable */
    SPI_WRITE_TX0(spi, 0x06);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    __NOP();

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x02: Page program */
    SPI_WRITE_TX0(spi, 0x02);
    /* Send 24-bit start address */
    SPI_WRITE_TX0(spi, (u32StartAddress >> 16) & 0xFF);
    SPI_WRITE_TX0(spi, (u32StartAddress >> 8) & 0xFF);
    SPI_WRITE_TX0(spi, u32StartAddress & 0xFF);

    u32Counter = 0;
    while(u32Counter < u32ByteCount)
    {
        if(SPI_GET_TX_FIFO_FULL_FLAG(spi) != 1)
            SPI_WRITE_TX0(spi, au8DataBuffer[u32Counter++]);
    }
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);
    /* Clear RX FIFO */
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;
    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);
}

/**
  * @brief  Read SPI flash memory.
  * @param  spi is the base address of SPI module.
  * @param  u32StartAddress is the start address.
  * @param  au8DataBuffer is the pointer of destination buffer.
  * @param  u32ByteCount is the total data count.
  * @return None.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
void SpiFlash_ReadData(SPI_T *spi, uint32_t u32StartAddress, uint8_t *au8DataBuffer, uint32_t u32ByteCount)
{
    uint32_t u32RxCounter, u32TxCounter;

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x03: Read data */
    SPI_WRITE_TX0(spi, 0x03);
    /* Send 24-bit start address */
    SPI_WRITE_TX0(spi, (u32StartAddress >> 16) & 0xFF);
    SPI_WRITE_TX0(spi, (u32StartAddress >> 8) & 0xFF);
    SPI_WRITE_TX0(spi, u32StartAddress & 0xFF);
    /* Check the BUSY status and TX empty flag */
    while((spi->CNTRL & (SPI_CNTRL_GO_BUSY_Msk | SPI_CNTRL_TX_EMPTY_Msk)) != SPI_CNTRL_TX_EMPTY_Msk);
    /* Clear RX FIFO */
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;

    u32RxCounter = 0;
    u32TxCounter = 0;
    while(u32RxCounter < u32ByteCount)
    {
        while(SPI_GET_RX_FIFO_EMPTY_FLAG(spi) == 0)
        {
            au8DataBuffer[u32RxCounter] = SPI_READ_RX0(spi);
            u32RxCounter++;
        }
        if((SPI_GET_TX_FIFO_FULL_FLAG(spi) != 1) && (u32TxCounter < u32ByteCount))
        {
            SPI_WRITE_TX0(spi, 0x00);
            u32TxCounter++;
        }
    }

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);
}





/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
