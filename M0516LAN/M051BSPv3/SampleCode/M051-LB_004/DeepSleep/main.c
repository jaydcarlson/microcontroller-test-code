/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "M051Series.h"
#include "LCD_Driver.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000


volatile int8_t gi8Key = 1;
char g_strBuf[32] = {0};


void EINT0_IRQHandler(void)
{
    /* Clear P3.2 interrupt flag */
    GPIO_CLR_INT_FLAG(P3, BIT2);

    if(P32)
    {
        /* P3.2 is from low to high */
        gi8Key = 1;
    }
    else
    {
        /* P3.2 is from high to low */
        gi8Key = 0;
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
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_PLL,  CLK_CLKDIV_UART(1));
    CLK_SetModuleClock(SPI0_MODULE,  CLK_CLKSEL1_SPI0_S_HCLK, MODULE_NoMsk);

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
    /* Enable debounce function of P3.2 (EINT0) */
    GPIO_ENABLE_DEBOUNCE(P3, BIT2);

    /* Set debounce time. it is about 6.4 ms */
    GPIO_SET_DEBOUNCE_TIME(GPIO_DBCLKSRC_LIRC, GPIO_DBCLKSEL_64);

    /* Enable P3.2 to be EINT0 */
    GPIO_EnableEINT0(P3, 2, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(EINT0_IRQn);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    uint32_t u32Cnt;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init system, peripherial clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init SPI0 and LCD */
    LCD_Init();
    LCD_EnableBackLight();
    LCD_ClearScreen();

    printf("CPU @ %d Hz\n", SystemCoreClock);

    LCD_Print(0, "Smpl_DeepSleep");

    /*Initialize external interrupt*/
    GPIO_Init();

    /*  P3.2 is used as EINT0 for deep sleep (power down) control.
        Press P3.2 will toggle power down/wakeup state to show how to enter power down.
    */
    LCD_Print(1, "Press INT ");

    while(1)
    {
        char strClearVal[15] = "Count:         ";
        /* Enter power when key change from low to high */
        u32Cnt = 0;
        while(gi8Key == 1)
        {
            sprintf(g_strBuf, "Count:%d", u32Cnt++);
            LCD_Print(3, strClearVal);
            LCD_Print(3, g_strBuf);
        }
        while(gi8Key == 0)
        {
            sprintf(g_strBuf, "Count:%d", u32Cnt++);
            LCD_Print(3, strClearVal);
            LCD_Print(3, g_strBuf);
        }

        LCD_Print(2, "Deep Sleeping...");

        /* We need to disable debounce function before power down, otherwise, there would be twice interrupt when wakeup */
        GPIO_DISABLE_DEBOUNCE(P3, BIT2);

        /* Unlock protected registers */
        SYS_UnlockReg();

        /* Prepare to enter power down */
        /* Use WFI instruction to idle the CPU.
           NOTE: If ICE is attached, system will wakeup immediately because ICE is a wakeup event.
        */
        CLK_PowerDown();

        /* Lock protected registers */
        SYS_LockReg();

        /* Re-enable debounce function if necessary */
        GPIO_ENABLE_DEBOUNCE(P3, BIT2);

        LCD_Print(2, "Working...      ");

        /* Make sure the key is return to high before next key action */
        while(gi8Key == 0);

        gi8Key = 0;
    }
}

