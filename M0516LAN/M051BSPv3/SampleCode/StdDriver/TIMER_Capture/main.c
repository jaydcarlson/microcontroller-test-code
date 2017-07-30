/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 15/05/22 2:31p $
 * @brief    Show how to use the timer1 capture function to capture timer1 counter value.
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000


/*---------------------------------------------------------------------------------------------------------*/
/* Global Interface Variables Declarations                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
extern int IsDebugFifoEmpty(void);
volatile uint8_t  g_u8IsWDTTimeoutINT = 0;
volatile uint32_t g_au32TMRINTCount[4] = {0};


/**
 * @brief       Timer0 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Timer0 default IRQ, declared in startup_M051Series.s.
 */
void TMR0_IRQHandler(void)
{
    /* Clear Timer0 time-out interrupt flag */
    TIMER_ClearIntFlag(TIMER0);

    g_au32TMRINTCount[0]++;
}

/**
 * @brief       Timer1 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Timer1 default IRQ, declared in startup_M051Series.s.
 */
void TMR1_IRQHandler(void)
{
    if(TIMER_GetCaptureIntFlag(TIMER1) == 1)
    {
        /* Clear Timer1 capture interrupt flag */
        TIMER_ClearCaptureIntFlag(TIMER1);

        g_au32TMRINTCount[1]++;
    }
}

/**
 * @brief       Timer2 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Timer2 default IRQ, declared in startup_M051Series.s.
 */
void TMR2_IRQHandler(void)
{
    /* Clear Timer2 time-out interrupt flag */
    TIMER_GetIntFlag(TIMER2);

    g_au32TMRINTCount[2]++;
}

/**
 * @brief       Timer3 IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The Timer3 default IRQ, declared in startup_M051Series.s.
 */
void TMR3_IRQHandler(void)
{
    /* Clear Timer3 time-out interrupt flag */
    TIMER_GetIntFlag(TIMER3);

    g_au32TMRINTCount[3]++;
}

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

    /* Enable external 12 MHz XTAL, IRC10K */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk | CLK_PWRCON_OSC10K_EN_Msk;

    /* Enable PLL and Set PLL frequency */
    CLK->PLLCON = PLLCON_SETTING;

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_IRC10K_STB_Msk);

    /* Switch HCLK clock source to PLL, STCLK to HCLK/2 */
    CLK->CLKSEL0 = CLK_CLKSEL0_STCLK_S_HCLK_DIV2 | CLK_CLKSEL0_HCLK_S_PLL;

    /* Enable peripheral clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk |
                  CLK_APBCLK_TMR0_EN_Msk | CLK_APBCLK_TMR1_EN_Msk | CLK_APBCLK_TMR2_EN_Msk | CLK_APBCLK_TMR3_EN_Msk;

    /* Peripheral clock source */
    CLK->CLKSEL1 = CLK_CLKSEL1_UART_S_PLL |
                   CLK_CLKSEL1_TMR0_S_HXT | CLK_CLKSEL1_TMR1_S_HCLK | CLK_CLKSEL1_TMR1_S_HIRC | CLK_CLKSEL1_TMR3_S_HXT;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD, TXD, T0, T1 and T1EX */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P34_T0 | SYS_MFP_P35_T1 | SYS_MFP_P33_T1EX;

    /* Set P1 multi-function pins for T3 */
    SYS->P1_MFP = SYS_MFP_P11_T3;
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
/*  MAIN function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    volatile uint32_t u32InitCount;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+---------------------------------------------------+\n");
    printf("|    Timer External Capture Function Sample Code    |\n");
    printf("+---------------------------------------------------+\n\n");

    printf("# Timer Settings:\n");
    printf("  Timer0: Clock source is 12 MHz; Toggle-output mode and frequency is 500 Hz.\n");
    printf("  Timer3: Clock source is 12 MHz; Toggle-output mode and frequency is 1 Hz.\n");
    printf("  Timer1: Clock source is HCLK(50 MHz); Continuous counting mode; TCMP is 0xFFFFFF;\n");
    printf("          Counter pin enable; Capture pin and capture interrupt enable;\n");
    printf("# Generate 500 Hz frequency from T0 and connect T0 pin to Timer1 counter pin.\n");
    printf("# Generate 1 Hz frequency from T3 and connect T3 pin to T1EX capture pin.\n");
    printf("# Get 500 event counts from Timer1 counter pin when each T1EX pin interrupt occurred.\n\n");

    /* Initial Timer0 and Timer3 default setting */
    TIMER_Open(TIMER0, TIMER_TOGGLE_MODE, 1000);
    TIMER_Open(TIMER3, TIMER_TOGGLE_MODE, 2);

    /* Initial Timer1 default setting */
    TIMER_Open(TIMER1, TIMER_CONTINUOUS_MODE, 1);

    /* Configure Timer1 setting for external counter input and capture function */
    TIMER_SET_PRESCALE_VALUE(TIMER1, 0);
    TIMER_SET_CMP_VALUE(TIMER1, 0xFFFFFF);
    TIMER_EnableEventCounter(TIMER1, TIMER_COUNTER_FALLING_EDGE);
    TIMER_EnableCapture(TIMER1, TIMER_CAPTURE_FREE_COUNTING_MODE, TIMER_CAPTURE_FALLING_EDGE);
    TIMER_EnableCaptureInt(TIMER1);

    /* Enable Timer1 NVIC */
    NVIC_EnableIRQ(TMR1_IRQn);

    /* Clear Timer1 interrupt counts to 0 */
    u32InitCount = g_au32TMRINTCount[1] = 0;

    /* Start Timer0, Timer1 and Timer3 counting */
    TIMER_Start(TIMER0);
    TIMER_Start(TIMER1);
    TIMER_Start(TIMER3);

    /* Check T1EX interrupt counts */
    while(g_au32TMRINTCount[1] <= 10)
    {
        if(g_au32TMRINTCount[1] != u32InitCount)
        {
            printf("[%2d] - %4d\n", g_au32TMRINTCount[1], TIMER_GetCaptureData(TIMER1));
            u32InitCount = g_au32TMRINTCount[1];
        }
    }

    /* Stop Timer0, Timer1 and Timer3 counting */
    TIMER_Close(TIMER0);
    TIMER_Close(TIMER1);
    TIMER_Close(TIMER3);

    printf("*** PASS ***\n");

    while(1);
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
