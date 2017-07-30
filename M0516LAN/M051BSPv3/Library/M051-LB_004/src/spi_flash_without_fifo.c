/**************************************************************************//**
 * @file     spi_flash_without_fifo.c
 * @version  V0.10
 * $Revision: 2 $
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
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* Send total 24 '0' dummy bits */
    /* Send the first 8 dummy bits */
    SPI_WRITE_TX0(spi, 0x00);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send the second 8 dummy bits */
    SPI_WRITE_TX0(spi, 0x00);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send the third 8 dummy bits */
    SPI_WRITE_TX0(spi, 0x00);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* Send SPI bus clock to get the Manufacturer ID */
    SPI_WRITE_TX0(spi, 0x00);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Get the Manufacturer ID */
    u32MID_DID = spi->RX0 << 8;

    /* Send SPI bus clock to get the Device ID */
    SPI_WRITE_TX0(spi, 0x00);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Get the Device ID */
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
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    __NOP();

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0xC7: Chip erase */
    SPI_WRITE_TX0(spi, 0xC7);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

}

/**
  * @brief  Read SPI flash status register.
  * @param  spi is the base address of SPI module.
  * @return Status register value.
  * @note   Before calling this function, the transaction length (data width) must be configured as 8 bits.
  */
uint32_t SpiFlash_ReadStatusReg(SPI_T *spi)
{
    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x05: Read status register */
    SPI_WRITE_TX0(spi, 0x05);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send SPI bus clock to read status register */
    SPI_WRITE_TX0(spi, 0x00);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

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
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    __NOP();

    /* /CS: active */
    SPI_SET_SS_LOW(spi);
    /* Send command 0x01: Write status register */
    SPI_WRITE_TX0(spi, 0x01);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* write to status register 1 */
    SPI_WRITE_TX0(spi, u32Value & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* write to status register 2 */
    SPI_WRITE_TX0(spi, (u32Value >> 8) & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

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
    while((SpiFlash_ReadStatusReg(spi)) & 1); /* check the BUSY status bit */
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
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);

    __NOP();

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x02: Page program */
    SPI_WRITE_TX0(spi, 0x02);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send 24-bit start address */
    /* Send the first 8 address bits */
    SPI_WRITE_TX0(spi, (u32StartAddress >> 16) & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send the second 8 address bits */
    SPI_WRITE_TX0(spi, (u32StartAddress >> 8) & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send the third 8 address bits */
    SPI_WRITE_TX0(spi, u32StartAddress & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    u32Counter = 0;
    while(u32Counter < u32ByteCount)
    {
        /* Check busy state */
        while(SPI_IS_BUSY(spi));
        /* Write one byte to SPI flash */
        SPI_WRITE_TX0(spi, au8DataBuffer[u32Counter++]);
        /* Trigger SPI transfer */
        SPI_TRIGGER(spi);
    }
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
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
    uint32_t u32RxCounter;

    /* /CS: active */
    SPI_SET_SS_LOW(spi);

    /* Send command 0x03: Read data */
    SPI_WRITE_TX0(spi, 0x03);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send 24-bit start address */
    /* Send the first 8 address bits */
    SPI_WRITE_TX0(spi, (u32StartAddress >> 16) & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send the second 8 address bits */
    SPI_WRITE_TX0(spi, (u32StartAddress >> 8) & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));
    /* Send the third 8 address bits */
    SPI_WRITE_TX0(spi, u32StartAddress & 0xFF);
    /* Trigger SPI transfer */
    SPI_TRIGGER(spi);
    /* Check busy state */
    while(SPI_IS_BUSY(spi));

    /* Reset RX data counter */
    u32RxCounter = 0;
    while(u32RxCounter < u32ByteCount)
    {
        /* Send SPI bus clock to get data from SPI flash */
        SPI_WRITE_TX0(spi, 0x00);
        /* Trigger SPI transfer */
        SPI_TRIGGER(spi);
        /* Check busy state */
        while(SPI_IS_BUSY(spi));
        /* Read data */
        au8DataBuffer[u32RxCounter++] = SPI_READ_RX0(spi);
    }

    /* /CS: inactive */
    SPI_SET_SS_HIGH(spi);
}





/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
