/**************************************************************************//**
 * @file     Smpl_DrvFMC_SimpleLD.c
 * @version  V2.00
 * $Revision: 2 $
 * $Date: 14/01/28 11:43a $
 * @brief    M051 Series Flash Memory Controller Driver Sample Code on LDROM
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000

#define KEY_ADDR            0x20000FFC  /* The location of signature */
#define SIGNATURE           0x21557899  /* The signature word is used by AP code to check if simple LD is finished */

#define CONFIG0_TEST_CODE   0x0F9000FF

#define FUN_TBL_BASE        0x00100E00

int32_t IAP_Func0(int32_t n);
int32_t IAP_Func1(int32_t n);
int32_t IAP_Func2(int32_t n);
int32_t IAP_Func3(int32_t n);

#if defined ( __ICCARM__ )
# pragma location = "FunTblSection" /* The location of FunTblSection is defined in FMC_IAP_LD.icf file. */
__root const uint32_t g_funcTable[4] =
{
    (uint32_t)IAP_Func0, (uint32_t)IAP_Func1, (uint32_t)IAP_Func2, (uint32_t)IAP_Func3
} ;
#else
__attribute__((at(FUN_TBL_BASE))) const uint32_t g_funcTable[4] =
{
    (uint32_t)IAP_Func0, (uint32_t)IAP_Func1, (uint32_t)IAP_Func2, (uint32_t)IAP_Func3
};
#endif


void SysTickDelay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  = (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
}

void SYS_Init(void)
{
    int32_t i;
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable External XTAL (4~24 MHz) and IRC 22.1184 MHz */
    CLK->PWRCON |= (CLK_PWRCON_XTL12M_EN_Msk | CLK_PWRCON_IRC22M_EN_Msk);

    CLK->PLLCON = PLLCON_SETTING;

    /* Waiting for clock ready */
    i = 22000000; // For timeout
    while(i-- > 0)
    {
        if((CLK->CLKSTATUS & (CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_IRC22M_STB_Msk)) ==
                (CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_IRC22M_STB_Msk))
            break;
    }


    /* Switch HCLK clock source to IRC 22.1184 MHz */
    CLK->CLKSEL0 = CLK_CLKSEL0_HCLK_S_HIRC;

    /* Enable IP clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk;

    /* Select IP clock source */
    CLK->CLKSEL1 = CLK_CLKSEL1_UART_S_PLL;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD and TXD  */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;

    /* Lock protected registers */
    SYS_LockReg();
}


void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

    /* Configure UART0 and set UART0 Baudrate */
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(PLL_CLOCK, 115200);
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}

int32_t IAP_Func0(int32_t n)
{
    int32_t i;

    for(i = 0; i < n; i++)
    {
        printf("Hello IAP0! #%d\n", i);
    }

    return n;
}

int32_t IAP_Func1(int32_t n)
{
    int32_t i;

    for(i = 0; i < n; i++)
    {
        printf("Hello IAP1! #%d\n", i);
    }

    return n;
}
int32_t IAP_Func2(int32_t n)
{
    int32_t i;

    for(i = 0; i < n; i++)
    {
        printf("Hello IAP2! #%d\n", i);
    }

    return n;
}
int32_t IAP_Func3(int32_t n)
{
    int32_t i;

    for(i = 0; i < n; i++)
    {
        printf("Hello IAP3! #%d\n", i);
    }

    return n;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    int32_t i;

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    /*
        This is a simple sample code for LDROM in new IAP mode.
        The base address is 0x100000.
        The base address for function table is defined by FUN_TBL_BASE.
    */

    printf("+------------------------------------------------------------------+\n");
    printf("|    M05xx Flash Memory Controller Driver Sample Code for LDROM    |\n");
    printf("+------------------------------------------------------------------+\n");

    printf("\nCPU @ %dHz\n\n", SystemCoreClock);

    // Delay 3 seconds
    for(i = 0; i < 30; i++)
    {
        printf(".");
        SysTickDelay(10000);
    }
    printf("\n");

    printf("Function table @ 0x%08x\n", g_funcTable);

    while(SYS->PDID)__WFI();
}




