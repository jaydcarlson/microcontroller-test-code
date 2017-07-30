/**************************************************************************//**
 * @file     i2c_software_gpio_with_timer.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 14/02/10 3:08p $
 * @brief    M051 series software I2C driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "i2c_software_gpio_with_timer.h"

/* SDA = GP3.4, CLK = GP3.5 */
#define I2C_SW_SDA P34
#define I2C_SW_CLK P35

typedef void (*TIMER_CALLBACK)(void);

TIMER_CALLBACK funPtr;
I2C_SW_FLAG_T I2C_SW_STATUS;

uint8_t u8I2C_Buffer;
uint8_t* p8I2C_Data;
uint32_t u32I2C_ByteSize, u32I2C_ByteSizeCount;

/**
  * @brief Prepare to start software I2C
  * @param u32BusClock     I2C Bus Clock (Hz)
  * @retval 0             Success
  */
uint32_t I2C_SW_I_Open(uint32_t u32BusClock)
{
    /* Setup TIMER0 clock source */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_TMR0_S_Msk) | CLK_CLKSEL1_TMR0_S_HXT;

    /* Enable TIMER0's clock */
    CLK->APBCLK |= CLK_APBCLK_TMR0_EN_Msk;

    NVIC_EnableIRQ(TMR0_IRQn);

    if(u32BusClock > 50000)
        u32BusClock = 50000;

    outpw((uint32_t)&I2C_SW_STATUS, 0);
    funPtr = NULL;

    TIMER0->TCMPR = ((__HIRC / 2) / u32BusClock) - 1;
    TIMER0->TCSR = 0x28000000;

    /* Configure P3.4 and P3.5 as open-drain mode */
    GPIO_SetMode(P3, 0x30, GPIO_PMD_OPEN_DRAIN);

    I2C_SW_SDA = 1;
    I2C_SW_CLK = 1;
    return 0;
}

/**
  * @brief  ISR to handle TIMER0 interrupt event
  * @param  None
  * @return None
  */
void TMR0_IRQHandler(void)
{
    TIMER0->TISR |= TIMER_TISR_TIF_Msk;

    if(funPtr != NULL)
    {
        (*funPtr)();
    }
}

/**
  * @brief Send I2C STOP signal
  * @param None
  * @return None
  */

void I2C_SW_I_Send_Stop(void)
{
    if(I2C_SW_CLK)
    {
        I2C_SW_SDA = 1;
        I2C_SW_STATUS.STOP = 1;
        I2C_SW_STATUS.BUSY = 0;
        funPtr = NULL;
    }
    else if(I2C_SW_SDA)
    {
        I2C_SW_SDA = 0;
    }
    else
    {
        I2C_SW_CLK = 1;
    }
}

/**
  * @brief Read a byte
  * @param None
  * @return None
  */
void I2C_SW_I_Get_Byte(void)
{
    if(I2C_SW_STATUS.COUNT < 8)
    {
        if(I2C_SW_CLK)
        {
            u8I2C_Buffer |= I2C_SW_SDA << (7 - I2C_SW_STATUS.COUNT++);
            I2C_SW_CLK = 0;
        }
        else
        {
            I2C_SW_CLK = 1;
        }
    }
    else
    {
        if(I2C_SW_CLK)
        {
            I2C_SW_CLK = 0;
            I2C_SW_SDA = 1;
            if(u32I2C_ByteSizeCount == u32I2C_ByteSize)
            {
                funPtr = I2C_SW_I_Send_Stop;
            }
            else
            {
                I2C_SW_STATUS.COUNT = 0;
                u8I2C_Buffer = 0;
            }
        }
        else
        {
            *(p8I2C_Data + u32I2C_ByteSizeCount++) = u8I2C_Buffer;
            I2C_SW_SDA = (u32I2C_ByteSizeCount == u32I2C_ByteSize) ? 1 : 0;
            I2C_SW_CLK = 1;
        }
    }
}

/**
  * @brief Send a byte
  * @param None
  * @return None
  */
void I2C_SW_I_Send_Byte(void)
{
    if(I2C_SW_STATUS.COUNT < 8)
    {
        if(I2C_SW_CLK)
        {
            I2C_SW_CLK = 0;
        }
        else
        {
            I2C_SW_SDA = u8I2C_Buffer >> (7 - I2C_SW_STATUS.COUNT++);
            I2C_SW_CLK = 1;
        }
    }
    else if(I2C_SW_STATUS.COUNT == 8)
    {
        if(I2C_SW_CLK)
        {
            I2C_SW_CLK = 0;
        }
        else
        {
            I2C_SW_SDA = 1;
            I2C_SW_STATUS.COUNT++;
            I2C_SW_CLK = 1;
        }
    }
    else
    {
        I2C_SW_STATUS.NACK = I2C_SW_SDA;
        if(I2C_SW_SDA)
        {
            funPtr = I2C_SW_I_Send_Stop;
        }
        else if(I2C_SW_STATUS.RW)
        {
            I2C_SW_STATUS.COUNT = 0;
            u8I2C_Buffer = 0;
            funPtr = I2C_SW_I_Get_Byte;
        }
        else
        {
            if(u32I2C_ByteSizeCount == u32I2C_ByteSize)
            {
                funPtr = I2C_SW_I_Send_Stop;
            }
            else
            {
                I2C_SW_STATUS.COUNT = 0;
                u8I2C_Buffer = *(p8I2C_Data + u32I2C_ByteSizeCount++);
            }
        }
        I2C_SW_CLK = 0;
    }
}

/**
  * @brief Send I2C START signal
  * @param None
  * @return None
  */
void I2C_SW_I_Send_Start(void)
{
    if(I2C_SW_SDA)
    {
        I2C_SW_SDA = 0;
    }
    else
    {
        I2C_SW_CLK = 0;
        I2C_SW_STATUS.START = 1;
        funPtr = I2C_SW_I_Send_Byte;
    }
}

/**
  * @brief Send data
  * @param u8Address    I2C slave address
  * @param p8Data        data address
  * @param u32ByteSize    data length
  * @retval 1     I2C is busy
  * @retval 0     Success
  */
uint32_t I2C_SW_I_Send(uint8_t u8Address, uint8_t* p8Data, uint32_t u32ByteSize)
{
    if(I2C_SW_STATUS.BUSY)
        return 1;

    I2C_SW_SDA = 1;
    I2C_SW_CLK = 1;

    u8I2C_Buffer = u8Address << 1;
    p8I2C_Data = p8Data;
    u32I2C_ByteSize = u32ByteSize;
    u32I2C_ByteSizeCount = 0;

    outpw((uint32_t)&I2C_SW_STATUS, 0);
    I2C_SW_STATUS.BUSY = 1;
    I2C_SW_STATUS.RW = 0;
    funPtr = I2C_SW_I_Send_Start;

    TIMER0->TCSR |= TIMER_TCSR_CEN_Msk;

    return 0;
}

/**
  * @brief Check if I2C is busy
  * @param None
  * @retval 0    Not Busy
  * @retval 1    Busy
  */
uint32_t I2C_SW_I_IsBZ(void)
{
    return I2C_SW_STATUS.BUSY;
}

/**
  * @brief Return byte counter
  * @param -
  * @retval Byte counter
  */
uint32_t I2C_SW_I_Count(void)
{
    return u32I2C_ByteSizeCount;
}

/**
  * @brief Read data
  * @param u8Address    I2C slave address
  * @param p8Data        data address
  * @param u32ByteSize    data length
  * @retval 0        Success
  * @retval 1        Fail
  */
uint32_t I2C_SW_I_Get(uint8_t u8Address, uint8_t* p8Data, uint32_t u32ByteSize)
{
    if(I2C_SW_STATUS.BUSY)
        return 1;

    I2C_SW_SDA = 1;
    I2C_SW_CLK = 1;

    u8I2C_Buffer = (u8Address << 1) + 1;
    p8I2C_Data = p8Data;
    u32I2C_ByteSize = u32ByteSize;
    u32I2C_ByteSizeCount = 0;

    outpw((uint32_t)&I2C_SW_STATUS, 0);
    I2C_SW_STATUS.BUSY = 1;
    I2C_SW_STATUS.RW = 1;
    funPtr = I2C_SW_I_Send_Start;

    TIMER0->TCSR |= TIMER_TCSR_CEN_Msk;

    return 0;
}


