/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 15/08/07 2:39p $
 * @brief    M051 Series I2C Driver Sample Code for GC Mode (Slave)
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

volatile uint32_t slave_buff_addr;
volatile uint8_t g_au8SlvData[256];
volatile uint8_t g_au8SlvRxData[3];
/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint8_t g_u8DeviceAddr;
volatile uint8_t g_au8SlvTxData[3];
volatile uint8_t g_u8SlvDataLen;
volatile uint8_t g_u8SlvEndFlag = 0;

typedef void (*I2C_FUNC)(uint32_t u32Status);

static I2C_FUNC s_I2C0HandlerFn = NULL;

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C0 IRQ Handler                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C0_IRQHandler(void)
{
    uint32_t u32Status;

    u32Status = I2C0->I2CSTATUS;
    if(I2C0->I2CTOC & I2C_I2CTOC_TIF_Msk)
    {
        /* Clear I2C0 Timeout Flag */
        I2C0->I2CTOC |= I2C_I2CTOC_TIF_Msk;
    }
    else
    {
        if(s_I2C0HandlerFn != NULL)
            s_I2C0HandlerFn(u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C GC mode Rx Callback Function                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_GCSlaveRx(uint32_t u32Status)
{
    if(u32Status == 0x70)                      /* Reception of the general call address and one more data
                                                   byte; ACK has been return */
    {
        g_u8SlvDataLen = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0x90)                 /* Previously addressed with General Call; Data has been received
                                                   ACK has been returned */
    {
        g_au8SlvRxData[g_u8SlvDataLen] = (unsigned char)(I2C0->I2CDAT);
        g_u8SlvDataLen++;

        if(g_u8SlvDataLen == 2)
        {
            slave_buff_addr = (g_au8SlvRxData[0] << 8) + g_au8SlvRxData[1];
        }
        if(g_u8SlvDataLen == 3)
        {
            g_au8SlvData[slave_buff_addr] = g_au8SlvRxData[2];
            g_u8SlvDataLen = 0;
        }
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0x98)                 /* Previously addressed with General Call; Data byte has been
                                                   received; NOT ACK has been returned */
    {
        g_u8SlvDataLen = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0xA0)                 /* A STOP or repeated START has been received while still addressed
                                                   as SLV receiver */
    {
        g_u8SlvDataLen = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
        if(slave_buff_addr == 0xFF)
        {
            g_u8SlvEndFlag = 1;
        }
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

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
    /* Set P3 multi-function pins for UART0 RXD and TXD, and set P3.4 and P3.5 for I2C0 SDA and SCL */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P34_SDA0 | SYS_MFP_P35_SCL0;
}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART IP */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

    /* Configure UART0 and set UART0 Baudrate */
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}

void I2C0_Init(void)
{
    /* Reset I2C0 */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_I2C0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_I2C0_RST_Msk;

    /* Enable I2C0 Controller */
    I2C0->I2CON |= I2C_I2CON_ENS1_Msk;

    /* I2C0 clock divider, I2C Bus Clock = PCLK / (4*125) = 100kHz */
    I2C0->I2CLK = 125 - 1;

    /* Get I2C0 Bus Clock */
    printf("I2C clock %d Hz\n", (SystemCoreClock / (((I2C0->I2CLK) + 1) << 2)));

    /* Set I2C0 4 Slave Addresses */
    /* Slave Address : 0x15 */
    I2C0->I2CADDR0 = (I2C0->I2CADDR0 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x15 << I2C_I2CADDR_I2CADDR_Pos);
    /* Slave Address : 0x35 */
    I2C0->I2CADDR1 = (I2C0->I2CADDR1 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x35 << I2C_I2CADDR_I2CADDR_Pos);
    /* Slave Address : 0x55 */
    I2C0->I2CADDR2 = (I2C0->I2CADDR2 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x55 << I2C_I2CADDR_I2CADDR_Pos);
    /* Slave Address : 0x75 */
    I2C0->I2CADDR3 = (I2C0->I2CADDR3 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x75 << I2C_I2CADDR_I2CADDR_Pos);

    /* Enable I2C0 interrupt and set corresponding NVIC bit */
    I2C0->I2CON |= I2C_I2CON_EI_Msk;
    NVIC_EnableIRQ(I2C0_IRQn);
}

void I2C0_Close(void)
{
    /* Disable I2C0 interrupt and clear corresponding NVIC bit */
    I2C0->I2CON &= ~I2C_I2CON_EI_Msk;
    NVIC_DisableIRQ(I2C0_IRQn);

    /* Disable I2C0 and close I2C0 clock */
    I2C0->I2CON &= ~I2C_I2CON_ENS1_Msk;
    CLK->APBCLK &= ~CLK_APBCLK_I2C0_EN_Msk;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t i;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /*
        This sample code sets I2C bus clock to 100kHz. Then, accesses Slave (GC Mode) with Byte Write
        and Byte Read operations, and check if the read data is equal to the programmed data.
    */

    printf("\n");
    printf("+----------------------------------------------------------------+\n");
    printf("| M05xx I2C Driver Sample Code (Slave) for access Slave (GC Mode)|\n");
    printf("|                                                                |\n");
    printf("| I2C Master (I2C0) <---> I2C Slave(I2C0)(Address: 0x00)         |\n");
    printf("+----------------------------------------------------------------+\n");

    printf("Configure I2C0 as a slave.\n");
    printf("The I/O connection for I2C0:\n");
    printf("I2C0_SDA(P3.4), I2C0_SCL(P3.5)\n");

    /* Init I2C0 */
    I2C0_Init();

    /* Enable GC Mode */
    I2C0->I2CADDR0 |=  I2C_I2CADDR_GC_Msk;

    /* I2C enter no address SLV mode */
    I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);

    /* Clear receive buffer */
    for(i = 0; i < 0x100; i++)
    {
        g_au8SlvData[i] = 0;
    }

    g_u8SlvEndFlag = 0;

    /* I2C function to Slave receive data */
    s_I2C0HandlerFn = I2C_GCSlaveRx;

    printf("\n");
    printf("Slave(GC Mode) waiting for receiving data.\n");
    while(g_u8SlvEndFlag == 0);

    /* Check receive data correct or not */
    for(i = 0; i < 0x100; i++)
    {
        g_au8SlvTxData[0] = (uint8_t)((i & 0xFF00) >> 8);
        g_au8SlvTxData[1] = (uint8_t)(i & 0x00FF);
        g_au8SlvTxData[2] = (uint8_t)(g_au8SlvTxData[1] + 3);

        if(g_au8SlvData[i] != g_au8SlvTxData[2])
        {
            printf("GC Mode Receive data fail.\n");
            while(1);
        }
    }

    printf("GC Mode receive data OK.\n");

    s_I2C0HandlerFn = NULL;

    /* Close I2C0 */
    I2C0_Close();

    while(1);
}



