/**************************************************************************//**
 * @file     i2c_software_gpio.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series software I2C driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include "i2c_software_gpio.h"

/* SDA = GP1.4, CLK = GP1.5 */
#define I2C_SW_SDA     P14
#define I2C_SW_CLK     P15

uint32_t u32_I2C_SW_Delay;

/**
  * @brief Prepare to start software I2C
  * @param u32BusClock    I2C Bus Clock (Hz)
  * @retval 0     Success
  */
int32_t I2C_SW_Open(uint32_t u32BusClock)
{
    if(u32BusClock > 500000)
        u32_I2C_SW_Delay = 1;
    else
        u32_I2C_SW_Delay = 500000 / u32BusClock; /* Compute proper divider for I2C clock */

    /* Configure P1.4 and P1.5 as open-drain mode */
    GPIO_SetMode(P1, 0x30, GPIO_PMD_OPEN_DRAIN);

    I2C_SW_SDA = 1;
    I2C_SW_CLK = 1;
    return 0;
}

/**
  * @brief Send a byte
  * @param u8Data    Data
  * @retval 0        Receive ACK
  * @retval 1        Receive NACK
  */
int32_t I2C_SW_Send_byte(uint8_t u8Data)
{
    uint32_t u32count;
    for(u32count = 0; u32count < 8; u32count++)
    {
        I2C_SW_SDA = u8Data >> (7 - u32count);
        CLK_SysTickDelay(u32_I2C_SW_Delay);
        I2C_SW_CLK = 1;
        CLK_SysTickDelay(u32_I2C_SW_Delay);
        I2C_SW_CLK = 0;
    }
    I2C_SW_SDA = 1;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 1;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    u32count = I2C_SW_SDA;
    I2C_SW_CLK = 0;

    return u32count;
}

/**
  * @brief Send data
  * @param u8Address    I2C slave address
  * @param p8Data        data address
  * @param u32ByteSize    data length
  * @return data length
  */
int32_t I2C_SW_Send(uint8_t u8Address, uint8_t* p8Data, uint32_t u32ByteSize)
{
    uint32_t u32count = 0;
    if(u32ByteSize == 0)
        return 0;

    I2C_SW_SDA = 1;
    I2C_SW_CLK = 1;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_SDA = 0;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 0;
    CLK_SysTickDelay(u32_I2C_SW_Delay);

    if(I2C_SW_Send_byte(u8Address << 1))
        goto I2C_SW_Stop_Send;

    while(u32count < u32ByteSize)
    {
        if(I2C_SW_Send_byte(*(p8Data + u32count++)))
            goto I2C_SW_Stop_Send;
    }
I2C_SW_Stop_Send:
    I2C_SW_SDA = 0;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 1;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_SDA = 1;

    return u32count;
}

/**
  * @brief Read a byte
  * @param u32Ack    Configure to ACK or NACK
  * @return data
  */
uint8_t I2C_SW_Get_byte(uint32_t u32Ack)
{
    uint32_t u32count;
    uint8_t u8Data = 0;


    for(u32count = 0; u32count < 8; u32count++)
    {
        CLK_SysTickDelay(u32_I2C_SW_Delay);
        I2C_SW_CLK = 1;
        CLK_SysTickDelay(u32_I2C_SW_Delay);
        u8Data |= I2C_SW_SDA << (7 - u32count);
        I2C_SW_CLK = 0;
    }
    I2C_SW_SDA = u32Ack;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 1;
    u32count = I2C_SW_SDA;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 0;
    I2C_SW_SDA = 1;

    return u8Data;
}

/**
  * @brief Read data
  * @param u8Address    I2C slave address
  * @param p8Data        data address
  * @param u32ByteSize    data length
  * @return data length
  */
int32_t I2C_SW_Get(uint8_t u8Address, uint8_t* p8Data, uint32_t u32ByteSize)
{
    uint32_t u32count = 0;
    if(u32ByteSize == 0)
        return 0;

    I2C_SW_SDA = 1;
    I2C_SW_CLK = 1;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_SDA = 0;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 0;
    CLK_SysTickDelay(u32_I2C_SW_Delay);

    if(I2C_SW_Send_byte((u8Address << 1) | 1))
        goto I2C_SW_Stop_Get;

    while(u32count < (u32ByteSize - 1))
    {
        *(p8Data + u32count++) = I2C_SW_Get_byte(0);
    }
    *(p8Data + u32count++) = I2C_SW_Get_byte(1);
I2C_SW_Stop_Get:
    I2C_SW_SDA = 0;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_CLK = 1;
    CLK_SysTickDelay(u32_I2C_SW_Delay);
    I2C_SW_SDA = 1;

    return u32count;
}


