/******************************************************************************
 * @file     i2c_hardware.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 14/01/28 11:43a $
 * @brief    M051 series hardware I2C driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "M051Series.h"
#include "i2c_hardware.h"

uint8_t Tx_Data[4] = {0xaa, 0x22, 0x33, 0x44};
uint8_t Rx_Data[5];
uint8_t DataLen;

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Tx Callback Function                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void I2C0_IRQHandler(void)
{
    uint32_t u32Status;

    u32Status = I2C_GET_STATUS(I2C0);

    switch(u32Status)
    {
    /* Slave Transmitter Mode */
    case 0xC0:                        /* DATA has been transmitted and NACK has been returned */
    case 0xC8:                        /* DATA has been transmitted and ACK has been returned */
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI | I2C_I2CON_AA);
        printf("Slave Transmitter Success\n");
        break;

    case 0xA8:                        /* SLA+R has been received and ACK has been returned */
    case 0xB0:
        DataLen = 0;
    case 0xB8:                        /* DATA has been transmitted and ACK has been returned */
        I2C_SET_DATA(I2C0, Tx_Data[DataLen++]);
        if(DataLen < sizeof(Tx_Data))
            I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI | I2C_I2CON_AA);
        else
            I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI);
        break;

    /* Slave Receiver Mode*/
    case 0x68:                        /* SLA+W has been received and ACK has been returned */
    case 0x60:
        DataLen = 0;
        Rx_Data[0] = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI | I2C_I2CON_AA);
        break;
    case 0x80:                        /* DATA has been received and ACK has been returned */
        Rx_Data[DataLen++] = I2C_GET_DATA(I2C0);
        if(DataLen < (sizeof(Rx_Data) - 1))
            I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI | I2C_I2CON_AA);
        else
            I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI);
        break;
    case 0x88:                        /* DATA has been received and NACK has been returned */
        Rx_Data[DataLen++] = I2C_GET_DATA(I2C0);
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI | I2C_I2CON_AA);
        break;

    case 0xA0:                      /* STOP or Repeat START has been received */
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI | I2C_I2CON_AA);
        printf("Slave Receiver Success\n");
        break;
    }
}

void InitI2C_HW(void)
{
    /* Open I2C module and set bus clock */
    I2C_Open(I2C0, 100);

    /* Set I2C 4 Slave Addresses */
    I2C_SetSlaveAddr(I2C0, 0, 0x15, 0);   /* Slave Address : 0x15 */
    I2C_SetSlaveAddr(I2C0, 1, 0x35, 0);   /* Slave Address : 0x35 */
    I2C_SetSlaveAddr(I2C0, 2, 0x55, 0);   /* Slave Address : 0x55 */
    I2C_SetSlaveAddr(I2C0, 3, 0x75, 0);   /* Slave Address : 0x75 */

    /* Enable I2C interrupt */
    I2C_EnableInt(I2C0);
    NVIC_EnableIRQ(I2C0_IRQn);

    /* I2C as slave */
    I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
}

