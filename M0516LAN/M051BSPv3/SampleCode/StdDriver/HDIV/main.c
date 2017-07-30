/**************************************************************************//**
 * @file     main.c
 * @version  V2.10
 * $Revision: 3 $
 * $Date: 14/01/28 11:44a $
 * @brief    M051 Series Timer Controller and Watchdog Timer Driver Sample Code
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_XTAL
#define PLL_CLOCK           50000000

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCON &= ~CLK_PWRCON_XTL12M_EN_Msk;
    CLK->PWRCON |= (0x1 << CLK_PWRCON_XTL12M_EN_Pos); // XTAL12M (HXT) Enabled

    /* Waiting for 12MHz clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTL12M_STB_Msk));

    /* Enable IP clock */
    CLK->APBCLK |= CLK_APBCLK_UART0_EN_Msk; // UART Clock Enable

    /* Select IP clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= (0x0 << CLK_CLKSEL1_UART_S_Pos);// Clock source from external 12 MHz

    /* Set P30(RXD0),P31(TXD0) multi-function pins for UART0 RXD and TXD  */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;

}


void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure UART0 and set UART0 Baudrate */
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
}

void HDIV_Init(void)
{
    /* Enable Hardware Divider Clock */
    CLK->AHBCLK |= CLK_AHBCLK_HDIV_EN_Msk;
}


/*---------------------------------------------------------------------------------------------------------*/
/*  MAIN function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    /* Disable register write-protection function */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init Divider */
    HDIV_Init();

    printf("+----------------------------------------------+\n");
    printf("|    M05xx Divider Sample Code                 |\n");
    printf("+----------------------------------------------+\n");
    printf("\n");

    printf("12341 / 123 = %d\n", HDIV_Div(12341, 123));
    printf("12341 %% 123 = %d\n", HDIV_Mod(12341, 123));

    /* Lock protected registers */
    SYS_LockReg();

    printf("Done\n");

    while(SYS->PDID);
    return 0;
}
