/******************************************************************************
 * @file     main.c
 * @version  V3.00
 * $Revision: 5 $
 * $Date: 15/08/07 1:28p $
 * @brief    M051 series software I2C implement source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#include "I2C_Software_GPIO.h"
#include "I2C_Hardware.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK->PWRCON |= CLK_PWRCON_OSC22M_EN_Msk;

    /* Waiting for Internal RC clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_OSC22M_STB_Msk));

    /* Switch HCLK clock source to Internal RC */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_HIRC;

    /* Enable external XTAL 12MHz clock */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk;

    /* Waiting for external XTAL clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTL12M_STB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCON = PLLCON_SETTING;
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_PLL_STB_Msk));
    CLK->CLKSEL0 &= (~CLK_CLKSEL0_HCLK_S_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_PLL;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /* Enable UART module clock */
    CLK->APBCLK |= CLK_APBCLK_UART0_EN_Msk | CLK_APBCLK_I2C0_EN_Msk;

    /* Select UART module clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= CLK_CLKSEL1_UART_S_HXT;

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;


    /* Configure the SDA0 & SCL0 of I2C0 pins */
    SYS->P3_MFP &= ~(SYS_MFP_P34_Msk | SYS_MFP_P35_Msk);
    SYS->P3_MFP |= SYS_MFP_P34_SDA0 | SYS_MFP_P35_SCL0;
}

void UART_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART and set UART Baudrate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    uint8_t Tx_Data[6];
    uint8_t Rx_Data[6];

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();


    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART for printf */
    UART_Init();

    printf("+-------------------------------------------------------+\n");
    printf("|    Software I2C sample code                           |\n");
    printf("|    SW Master                                          |\n");
    printf("|    HW Slave                                           |\n");
    printf("+-------------------------------------------------------+\n");

    printf("Initiate I2C for slave\n");
    InitI2C_HW();

    printf("Initiate software I2C for Master\n");
    I2C_SW_Open(100000);

    printf("Please connect:\n");
    printf("SW SDA - P1.4 (PIN47)  <->   HW SDA - P3.4 (PIN10) \n");
    printf("SW SCL - P1.5 (PIN1)   <->   HW SCL - P3.5 (PIN11) \n");

    Tx_Data[0] = 0;
    Tx_Data[1] = 0;
    Tx_Data[2] = 0xA5;
    Tx_Data[3] = 0xcc;
    Tx_Data[4] = 0xbb;
    Tx_Data[5] = 0xdd;

    printf("Access I2C slave:\n");

    I2C_SW_Send(0x15, Tx_Data, 6);
    CLK_SysTickDelay(5000);
    I2C_SW_Get(0x15, Rx_Data, 4);

    if((Rx_Data[0] != 0xaa) || (Rx_Data[1] != 0x22) || (Rx_Data[2] != 0x33) || (Rx_Data[3] != 0x44))
        printf("Data Error!!\n");
    else
        printf("Pass!!\n");

    while(1);
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
