/**************************************************************************//**
 * @file     i2c_software_gpio_with_timer.h
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 14/01/28 10:49a $
 * @brief    This is the header file of i2c_software_gpio_with_timer.c
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __I2C_SOFTWARE_GPIO_WITH_TIMER_H__
#define __I2C_SOFTWARE_GPIO_WITH_TIMER_H__

#include "M051Series.h"

typedef struct
{
    uint32_t     COUNT: 4;  /*!< Data Bit Count */
    uint32_t     NACK: 1;       /*!< I2C NACK */
    uint32_t     START: 1;      /*!< I2C START */
    uint32_t     STOP: 1;       /*!< I2C STOP */
    uint32_t     RW: 1;         /*!< I2C Read/Write Bit */
    uint32_t     BUSY: 1;       /*!< I2C Busy flag */
    uint32_t     RESERVE: 23;   /*!< Reserve */
} I2C_SW_FLAG_T;     /*!< I2C Software GPIO Control Structure */

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t I2C_SW_I_Open(uint32_t u32BusClock);
uint32_t I2C_SW_I_Send(uint8_t u8Address, uint8_t* p8Data, uint32_t u32ByteSize);
uint32_t I2C_SW_I_Get(uint8_t u8Address, uint8_t* p8Data, uint32_t u32ByteSize);
uint32_t I2C_SW_I_IsBZ(void);
uint32_t I2C_SW_I_Count(void);
#endif

