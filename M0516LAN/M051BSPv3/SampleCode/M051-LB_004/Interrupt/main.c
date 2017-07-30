/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "M051Series.h"
#include "LCD_Driver.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000


void GPIOP0P1_IRQHandler(void)
{
    /* Re-enable P1.3 debounce function */
    GPIO_ENABLE_DEBOUNCE(P1, BIT3);

    /* Clear P1.3 interrupt flag */
    GPIO_CLR_INT_FLAG(P1, BIT3);

    /* Toggle LED */
    GPIO_TOGGLE(P20);

    printf("P1.3 Interrupt!\n");
    LCD_Print(3, "P1.3 Interrupt!");
}

void GPIOP2P3P4_IRQHandler(void)
{
    /* Re-enable P4.5 debounce function */
    GPIO_ENABLE_DEBOUNCE(P4, BIT5);

    /* Clear P4.5 interrupt flag */
    GPIO_CLR_INT_FLAG(P4, BIT5);

    /* Toggle LED */
    GPIO_TOGGLE(P20);

    printf("P2P3P4 Interrupt!\n");
    LCD_Print(3, "P4.5 Interrupt!");
}

void EINT0_IRQHandler(void)
{
    /* Re-enable P3.2 debounce function */
    GPIO_ENABLE_DEBOUNCE(P3, BIT2);

    /* Clear P3.2 interrupt flag */
    GPIO_CLR_INT_FLAG(P3, BIT2);

    /* Toggle LED */
    GPIO_TOGGLE(P20);

    printf("EINT0 Interrupt!\n");
    LCD_Print(3, "EINT0 Interrupt!");
}

void EINT1_IRQHandler(void)
{
    /* Re-enable P3.3 debounce function */
    GPIO_ENABLE_DEBOUNCE(P3, BIT3);

    /* Clear P3.3 interrupt flag */
    GPIO_CLR_INT_FLAG(P3, BIT3);

    /* Toggle LED */
    GPIO_TOGGLE(P20);

    printf("EINT1 Interrupt!\n");
    LCD_Print(3, "EINT1 Interrupt!");
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK->PWRCON |= CLK_PWRCON_OSC22M_EN_Msk;

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Set PLL to power down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware.*/
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;

    /* Enable external 12MHz XTAL, 10kHz */
    CLK->PWRCON |= (CLK_PWRCON_XTL12M_EN_Msk | CLK_PWRCON_OSC10K_EN_Msk);

    /* Enable PLL and Set PLL frequency */
    CLK->PLLCON = PLLCON_SETTING;

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_OSC10K_STB_Msk);

    /* Use PLL as system clock source */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_PLL, CLK_CLKDIV_HCLK(1));

    /* Enable clock of UART0 and SPI0 */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(SPI0_MODULE);

    /* Select clock of UART0 and SPI0 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1));
    CLK_SetModuleClock(SPI0_MODULE,  CLK_CLKSEL1_SPI0_S_HCLK,  MODULE_NoMsk);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= (SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0);

    /* Set P1.4, P1.5, P1.6, P1.7 for SPI0 to driver LCD */
    SYS->P1_MFP &= ~(SYS_MFP_P14_Msk | SYS_MFP_P15_Msk | SYS_MFP_P16_Msk | SYS_MFP_P17_Msk);
    SYS->P1_MFP |= (SYS_MFP_P14_SPISS0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0);
}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART_Open(UART0, 115200);
}

void GPIO_Init(void)
{
    /* Set P2.0 as output pin */
    GPIO_SetMode(P2, BIT0, GPIO_PMD_OUTPUT);

    /* Set P1.3, P4.5 as Quasi-bidirectional mode */
    GPIO_SetMode(P1, BIT3, GPIO_PMD_QUASI);
    GPIO_SetMode(P4, BIT5, GPIO_PMD_QUASI);

    /* Set P1.3 as falling edge trigger and enable its interrupt */
    GPIO_EnableInt(P1, 3, GPIO_INT_FALLING);
    NVIC_EnableIRQ(GPIO_P0P1_IRQn);

    /* Set P4.5 as low level trigger and enable its interrupt */
    GPIO_EnableInt(P4, 5, GPIO_INT_LOW);
    NVIC_EnableIRQ(GPIO_P2P3P4_IRQn);

    /* Debounce function control */
    GPIO_SET_DEBOUNCE_TIME(GPIO_DBCLKSRC_HCLK, GPIO_DBCLKSEL_1024);
    GPIO_ENABLE_DEBOUNCE(P1, BIT3);
    GPIO_ENABLE_DEBOUNCE(P3, BIT2 | BIT3);
    GPIO_ENABLE_DEBOUNCE(P4, BIT5);

    /* Configure P3.2 external interrupt */
    GPIO_EnableEINT0(P3, 2, GPIO_INT_FALLING);
    NVIC_EnableIRQ(EINT0_IRQn);

    /* Configure P3.3 external interrupt */
    GPIO_EnableEINT1(P3, 3, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(EINT1_IRQn);

}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripherial clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("CPU @ %dHz\n", SystemCoreClock);

    /* Init SPI0 and LCD */
    LCD_Init();
    LCD_EnableBackLight();
    LCD_ClearScreen();

    LCD_Print(0, "Welcome! Nuvoton");
    LCD_Print(1, "This is INT test");

    /*-----------------------------------------------------------------------------------------------------*/
    /* GPIO Interrupt Test                                                                                 */
    /*-----------------------------------------------------------------------------------------------------*/

    printf("P1.3, P4.5, P3.2(EINT0) and P3.3(EINT1) are used to test interrupt\n  and control LEDs(P20)\n");

    /* Init P2.0 (output), P1.3, P4.5 (Quasi-bidirectional) and relative interrupts */
    GPIO_Init();

    /* Waiting for interrupts */
    while(1)
    {
        /* Disable P3.2, P3.3, P1.3, P4.5 debounce to avoid double interrupts when wakeup */
        GPIO_DISABLE_DEBOUNCE(P1, BIT3);
        GPIO_DISABLE_DEBOUNCE(P3, BIT2 | BIT3);
        GPIO_DISABLE_DEBOUNCE(P4, BIT5);

        /* Clear interrupt message */
        LCD_Print(2, "                ");

        /* Hold in wakeup state when P3.2 or P1.3 or P4.5 is low. */
        while((P32 == 0) || (P33 == 0) || (P13 == 0) || (P45 == 0));

        /* Unlock protected registers */
        SYS_UnlockReg();

        /* Waiting for message send out */
        printf("Deep Sleeping\n");
        LCD_Print(2, "Deep Sleeping...");
        LCD_Print(3, "                ");
        while((UART0->FSR & UART_FSR_TE_FLAG_Msk) == 0);

        /* Enter power down. Only P1.3, P4.5, EINT0 or EINT1 can used to wakeup system */
        CLK_PowerDown();
    }

}




