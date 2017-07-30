/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 15/05/22 2:29p $
 * @brief    Configure EBI interface to access BS616LV4017 (SRAM) on EBI interface.
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000


extern void SRAM_BS616LV4017(void);


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Enable IRC22M clock */
    CLK->PWRCON |= CLK_PWRCON_IRC22M_EN_Msk;

    /* Waiting for IRC22M clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_IRC22M_STB_Msk);

    /* Switch HCLK clock source to HIRC */
    CLK->CLKSEL0 = CLK_CLKSEL0_HCLK_S_HIRC;

    /* Set PLL to Power-down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware.*/
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;

    /* Enable external 12MHz XTAL */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk;

    /* Enable PLL and Set PLL frequency */
    CLK->PLLCON = CLK_PLLCON_50MHz_HXT;

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Switch HCLK clock source to PLL, STCLK to HCLK/2 */
    CLK->CLKSEL0 = CLK_CLKSEL0_STCLK_S_HCLK_DIV2 | CLK_CLKSEL0_HCLK_S_PLL;

    /* Enable EBI clock */
    CLK->AHBCLK |= CLK_AHBCLK_EBI_EN_Msk;

    /* Enable UART clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk;

    /* UART clock source */
    CLK->CLKSEL1 = CLK_CLKSEL1_UART_S_PLL;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD, TXD and EBI MCLK, nWR and nRD */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P33_MCLK | SYS_MFP_P36_nWR | SYS_MFP_P37_nRD;

    /* Set P0 multi-function pins for EBI AD0 ~ AD7 */
    SYS->P0_MFP = SYS_MFP_P00_AD0 | SYS_MFP_P01_AD1 | SYS_MFP_P02_AD2 | SYS_MFP_P03_AD3 |
                  SYS_MFP_P04_AD4 | SYS_MFP_P05_AD5 | SYS_MFP_P06_AD6 | SYS_MFP_P07_AD7;

    /* Set P2 multi-function pins for EBI AD8 ~ AD15 */
    SYS->P2_MFP = SYS_MFP_P20_AD8 | SYS_MFP_P21_AD9 | SYS_MFP_P22_AD10 | SYS_MFP_P23_AD11 |
                  SYS_MFP_P24_AD12 | SYS_MFP_P25_AD13 | SYS_MFP_P26_AD14 | SYS_MFP_P27_AD15;

    /* Set P1 multi-function pins for EBI nWRL and nWRH */
    SYS->P1_MFP = SYS_MFP_P10_nWRL | SYS_MFP_P11_nWRH;

    /* Set P4 multi-function pins for EBI nCS, ALE and ICE CLK and DAT */
    SYS->P4_MFP = SYS_MFP_P44_nCS | SYS_MFP_P45_ALE | SYS_MFP_P46_ICE_CLK | SYS_MFP_P47_ICE_DAT;
}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+----------------------------+\n");
    printf("|    EBI SRAM Sample Code    |\n");
    printf("+----------------------------+\n\n");

    printf("***************************************************************************\n");
    printf("* Please connect BS616LV4017 to M051 Series EBI bus before EBI testing !! *\n");
    printf("***************************************************************************\n\n");

    /* Enable EBI function and bus width to 16-bit */
    EBI_Open(0, EBI_BUSWIDTH_16BIT, EBI_TIMING_NORMAL, 0, 0);

    /* Start SRAM test */
    SRAM_BS616LV4017();

    /* Disable EBI function */
    EBI_Close(0);

    /* Disable EBI clock */
    CLK->AHBCLK &= ~CLK_AHBCLK_EBI_EN_Msk;

    printf("*** SRAM Test OK ***\n");

    while(1);
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
