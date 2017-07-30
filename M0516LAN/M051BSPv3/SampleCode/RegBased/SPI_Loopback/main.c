/**************************************************************************//**
 * @file     main.c
 * @version  V3.0
 * $Revision: 2 $
 * $Date: 15/05/22 3:00p $
 * @brief    Implement SPI Master loop back transfer. This sample code needs to
 *           connect MISO_0 pin and MOSI_0 pin together. It will compare the
 *           received data with transmitted data.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define TEST_COUNT             64

uint32_t g_au32SourceData[TEST_COUNT];
uint32_t g_au32DestinationData[TEST_COUNT];

/* Function prototype declaration */
void SYS_Init(void);
void UART0_Init(void);
void SPI_Init(void);

/* ------------- */
/* Main function */
/* ------------- */
int main(void)
{
    uint32_t u32DataCount, u32TestCount, u32Err;

    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();
    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init SPI */
    SPI_Init();

    printf("\n\n");
    printf("+--------------------------------------------------------------------+\n");
    printf("|                   M051 SPI Driver Sample Code                      |\n");
    printf("+--------------------------------------------------------------------+\n");
    printf("\n");
    printf("\nThis sample code demonstrates SPI0 self loop back data transfer.\n");
    printf(" SPI0 configuration:\n");
    printf("     Master mode; data width 32 bits.\n");
    printf(" I/O connection:\n");
    printf("     P1.5 MOSI <--> P1.6 MISO \n");

    printf("\nSPI0 Loopback test ");

    u32Err = 0;
    for(u32TestCount = 0; u32TestCount < 0x1000; u32TestCount++)
    {
        /* set the source data and clear the destination buffer */
        for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
        {
            g_au32SourceData[u32DataCount] = u32DataCount;
            g_au32DestinationData[u32DataCount] = 0;
        }

        u32DataCount = 0;

        if((u32TestCount & 0x1FF) == 0)
        {
            putchar('.');
        }

        while(1)
        {
            /* Write to TX register */
            SPI_WRITE_TX0(SPI0, g_au32SourceData[u32DataCount]);
            /* Trigger SPI data transfer */
            SPI_TRIGGER(SPI0);
            /* Check SPI0 busy status */
            while(SPI_IS_BUSY(SPI0));
            /* Read received data */
            g_au32DestinationData[u32DataCount] = SPI_READ_RX0(SPI0);
            u32DataCount++;
            if(u32DataCount >= TEST_COUNT)
                break;
        }

        /*  Check the received data */
        for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
        {
            if(g_au32DestinationData[u32DataCount] != g_au32SourceData[u32DataCount])
                u32Err = 1;
        }

        if(u32Err)
            break;
    }

    if(u32Err)
        printf(" [FAIL]\n\n");
    else
        printf(" [PASS]\n\n");

    /* Disable SPI0 peripheral clock */
    CLK->APBCLK &= (~CLK_APBCLK_SPI0_EN_Msk);

    while(1);
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    
    /* Enable external 12MHz XTAL */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk;

    /* Waiting for clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTL12M_STB_Msk));

    /* Select HXT as the clock source of HCLK */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLK_S_Msk)) | CLK_CLKSEL0_HCLK_S_HXT;

    /* Select HXT as the clock source of UART; select HCLK as the clock source of SPI0. */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~(CLK_CLKSEL1_UART_S_Msk | CLK_CLKSEL1_SPI0_S_Msk))) | (CLK_CLKSEL1_UART_S_HXT | CLK_CLKSEL1_SPI0_S_HCLK);

    /* Enable UART and SPI0 clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk | CLK_APBCLK_SPI0_EN_Msk;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;

    /* Setup SPI0 multi-function pins */
    SYS->P1_MFP = SYS_MFP_P14_SPISS0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0;
}

void UART0_Init(void)
{
    /* Word length is 8 bits; 1 stop bit; no parity bit. */
    UART0->LCR = UART_LCR_WLS_Msk;
    /* Using mode 2 calculation: UART bit rate = UART peripheral clock rate / (BRD setting + 2) */
    /* UART peripheral clock rate 12MHz; UART bit rate 115200 bps. */
    /* 12000000 / 115200 bps ~= 104 */
    /* 104 - 2 = 0x66. */
    UART0->BAUD = UART_BAUD_DIV_X_EN_Msk | UART_BAUD_DIV_X_ONE_Msk | (0x66);
}

void SPI_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init SPI                                                                                                */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure SPI0 as a master, clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    SPI0->CNTRL = SPI_MASTER | SPI_CNTRL_TX_NEG_Msk;
    /* Enable the automatic hardware slave select function. Select the SS pin and configure as low-active. */
    SPI0->SSR = SPI_SSR_AUTOSS_Msk | SPI_SSR_SSR_Msk;
    /* Set IP clock divider. SPI clock rate = HCLK / ((5+1)*2) = 1MHz */
    SPI0->DIVIDER = (SPI0->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | 5;
}


/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

