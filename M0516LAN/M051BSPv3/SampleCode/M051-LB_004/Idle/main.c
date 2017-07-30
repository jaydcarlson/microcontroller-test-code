/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "M051Series.h"
#include "LCD_Driver.h"


#define PLLCON_SETTING      CLK_PLLCON_50MHz_HIRC
#define PLL_CLOCK           50191800



void WDT_IRQHandler(void)
{
    /* Clear WDT time-out interrupt flag */
    WDT_CLEAR_TIMEOUT_INT_FLAG();
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

    /* Enable clock of WDT, PWM01 and SPI0 */
    CLK_EnableModuleClock(WDT_MODULE);
    CLK_EnableModuleClock(PWM01_MODULE);
    CLK_EnableModuleClock(SPI0_MODULE);

    /* Select peripheral clock of WDT and PWM01 and SPI0 */
    CLK_SetModuleClock(WDT_MODULE,   CLK_CLKSEL1_WDT_S_LIRC,   MODULE_NoMsk);
    CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HCLK, MODULE_NoMsk);
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

    /* Set P1.4, P1.5, P1.6, P1.7 for SPI0 to driver LCD */
    SYS->P1_MFP &= ~(SYS_MFP_P14_Msk | SYS_MFP_P15_Msk | SYS_MFP_P16_Msk | SYS_MFP_P17_Msk);
    SYS->P1_MFP |= (SYS_MFP_P14_SPISS0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0);

    /* Set P4.0 for PWM0 */
    SYS->P4_MFP = SYS->P4_MFP & (~SYS_MFP_P40_Msk) | SYS_MFP_P40_PWM0;
}

void WDT_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Start WDT. Timeout = (2^14 + 1024) * (1 / 10kHz)*/
    WDT_Open(WDT_TIMEOUT_2POW14, FALSE, FALSE, FALSE);

    /* Enable WDT interrupt function */
    WDT_EnableInt();

    /* Lock protected registers */
    SYS_LockReg();

    /* Enable WDT IRQ */
    NVIC_EnableIRQ(WDT_IRQn);
}

void PWMA_Init(void)
{
    /* Enable PWM Timer 0 and set to auto-reload mode */
    PWMA->PCR = PWM_PCR_CH0EN_Msk | PWM_PCR_CH0MOD_Msk;

    /* Set pre-scale for PWM01 */
    PWM_SET_PRESCALER(PWMA, 0, 1);

    /* Select the divider of PWM01 clock */
    PWM_SET_DIVIDER(PWMA, 0, PWM_CLK_DIV_1);

    /* PWM0 output is HCLK / 2 / 2 */
    PWM_SET_CMR(PWMA, 0, 0);
    PWM_SET_CNR(PWMA, 0, 1);

    /* PWM output enable */
    PWM_EnableOutput(PWMA, 0x1);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init system, peripherial clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init SPI0 and LCD */
    LCD_Init();
    LCD_EnableBackLight();
    LCD_ClearScreen();
    LCD_Print(0, "Idle Sample Code");

    /*----------------------- Enable WDT to wakeup CPU from idle ------------------*/
    WDT_Init();

    /*----------------------- Enable PWM to toggle output -------------------------*/
    PWMA_Init();

    /*
        The Idle sample uses __WFI() instruction to disable CPU clock to enter idle mode.
        In the sample code, CPU will enter idle mode to wait WDT timeout. User may check
        LCD display to know if it is wakeup.
    */

    /* Unlock protected registers */
    SYS_UnlockReg();

    while(1)
    {
        /* Select system clock source as OSC10K(LIRC),
           set HCLK divider as 1 and update current system core clock
        */
        CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_LIRC, CLK_CLKDIV_HCLK(1));

        /* Disable 22.1184MHz IRC */
        CLK_DisableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

        LCD_Print(1, "Idle  ");
        /* Idle to WDT timeout. HCLK should be 10KHz here. PWM0 = 2.5KHz*/
        CLK_Idle();
        LCD_Print(1, "Wakeup");

        /* Enable 22.1184MHz IRC */
        CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

        /* Waiting for clock ready */
        CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

        /* Select system clock source as OSC22M(HIRC),
           set HCLK divider as 1 and update current system core clock
        */
        CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

        LCD_Print(1, "Idle  ");
        /* Idle to WDT timeout. HCLK should be 22.1184MHz here. PWM0 = 5.5MHz*/
        CLK_Idle();
        LCD_Print(1, "Wakeup");
    }
}




