/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 15/05/22 2:06p $
 * @brief    Capture the PWMB Channel 1 waveform by PWMB Channel 2.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000

/**
 * @brief       PWMA IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle PWMA interrupt event
 */
void PWMA_IRQHandler(void)
{
    /*In this sample code, user will not use PWMA channel 0~3 PIIR interrupt and CAPIF capture interrupt.
      Defined following code as 0 for reducing interrupt execution time and code size. */
#if 0
    uint32_t u32PwmIntFlag, u32CapIntFlag0, u32CapIntFlag1;

    /* Handle PWMA Capture function */
    u32CapIntFlag0 = PWMA->CCR0;
    u32CapIntFlag1 = PWMA->CCR2;

    if(u32CapIntFlag0 & PWM_CCR0_CAPIF0_Msk)
    {
        PWMA->CCR0 &= (PWM_CCR_MASK | PWM_CCR0_CAPIF0_Msk);
    }

    else if(u32CapIntFlag0 & PWM_CCR0_CAPIF1_Msk)
    {
        PWMA->CCR0 &= (PWM_CCR_MASK | PWM_CCR0_CAPIF1_Msk);
    }

    else if(u32CapIntFlag1 & PWM_CCR2_CAPIF2_Msk)
    {
        PWMA->CCR2 &= (PWM_CCR_MASK | PWM_CCR2_CAPIF2_Msk);
    }

    else if(u32CapIntFlag1 & PWM_CCR2_CAPIF3_Msk)
    {
        PWMA->CCR2 &= (PWM_CCR_MASK | PWM_CCR2_CAPIF3_Msk);
    }

    /* Handle PWMA Timer function */
    u32PwmIntFlag = PWMA->PIIR;

    if(u32PwmIntFlag & PWM_PIIR_PWMIF0_Msk)
    {
        PWMA->PIIR = PWM_PIIR_PWMIF0_Msk;
    }

    else if(u32PwmIntFlag & PWM_PIIR_PWMIF1_Msk)
    {
        PWMA->PIIR = PWM_PIIR_PWMIF1_Msk;
    }

    else if(u32PwmIntFlag & PWM_PIIR_PWMIF2_Msk)
    {
        PWMA->PIIR = PWM_PIIR_PWMIF2_Msk;
    }

    else if(u32PwmIntFlag & PWM_PIIR_PWMIF3_Msk)
    {
        PWMA->PIIR = PWM_PIIR_PWMIF3_Msk;
    }
#endif
}

/**
 * @brief       PWMB IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle PWMB interrupt event
 */
void PWMB_IRQHandler(void)
{
//    uint32_t u32PwmIntFlag;
    uint32_t u32CapIntFlag1;

    /* Handle PWMB Capture function */
    u32CapIntFlag1 = PWMB->CCR2;

    /* PWMB channel 2 Capture interrupt */
    if(u32CapIntFlag1 & PWM_CCR2_CAPIF2_Msk)
    {
        PWMB->CCR2 &= (PWM_CCR_MASK | PWM_CCR2_CAPIF2_Msk);
    }
}


/*--------------------------------------------------------------------------------------*/
/* Capture function to calculate the input waveform information                         */
/* u32Count[4] : Keep the internal counter value when input signal rising / falling     */
/*               happens                                                                */
/*                                                                                      */
/* time    A    B     C     D                                                           */
/*           ___   ___   ___   ___   ___   ___   ___   ___                              */
/*      ____|   |_|   |_|   |_|   |_|   |_|   |_|   |_|   |_____                        */
/* index              0 1   2 3                                                         */
/*                                                                                      */
/* The capture internal counter down count from 0x10000, and reload to 0x10000 after    */
/* input signal falling happens (Time B/C/D)                                            */
/*--------------------------------------------------------------------------------------*/
void CalPeriodTime(PWM_T *PWM, uint32_t u32Ch)
{
    uint16_t u32Count[4];
    uint32_t u32i;
    uint16_t u16RisingTime, u16FallingTime, u16HighPeroid, u16LowPeroid, u16TotalPeroid;

    /* Clear Capture Falling Indicator (Time A) */
    PWM_ClearCaptureIntFlag(PWM, u32Ch, PWM_CAPTURE_INT_FALLING_LATCH);

    /* Wait for Capture Falling Indicator  */
    while(PWM_GetCaptureIntFlag(PWM, u32Ch) < 2);

    /* Clear Capture Falling Indicator (Time B)*/
    PWM_ClearCaptureIntFlag(PWM, u32Ch, PWM_CAPTURE_INT_FALLING_LATCH);

    u32i = 0;

    while(u32i < 4)
    {
        /* Wait for Capture Falling Indicator */
        while(PWM_GetCaptureIntFlag(PWM, u32Ch) < 2);

        /* Clear Capture Falling and Rising Indicator */
        PWM_ClearCaptureIntFlag(PWM, u32Ch, PWM_CAPTURE_INT_FALLING_LATCH | PWM_CAPTURE_INT_RISING_LATCH);

        /* Get Capture Falling Latch Counter Data */
        u32Count[u32i++] = PWM_GET_CAPTURE_FALLING_DATA(PWM, u32Ch);

        /* Wait for Capture Rising Indicator */
        while(PWM_GetCaptureIntFlag(PWM, u32Ch) < 2);

        /* Clear Capture Rising Indicator */
        PWM_ClearCaptureIntFlag(PWM, u32Ch, PWM_CAPTURE_INT_RISING_LATCH);

        /* Get Capture Rising Latch Counter Data */
        u32Count[u32i++] = PWM_GET_CAPTURE_RISING_DATA(PWM, u32Ch);
    }

    u16RisingTime = u32Count[1];

    u16FallingTime = u32Count[0];

    u16HighPeroid = u32Count[1] - u32Count[2];

    u16LowPeroid = 0x10000 - u32Count[1];

    u16TotalPeroid = 0x10000 - u32Count[2];

    printf("\nPWM generate: \nHigh Period=7199 ~ 7201, Low Period=16799 ~ 16801, Total Period=23999 ~ 24001\n");
    printf("\nCapture Result: Rising Time = %d, Falling Time = %d \nHigh Period = %d, Low Period = %d, Total Period = %d.\n\n",
           u16RisingTime, u16FallingTime, u16HighPeroid, u16LowPeroid, u16TotalPeroid);
    if((u16HighPeroid < 7199) || (u16HighPeroid > 7201) || (u16LowPeroid < 16799) || (u16LowPeroid > 16801) || (u16TotalPeroid < 23999) || (u16TotalPeroid > 24001))
        printf("Capture Test Fail!!\n");
    else
        printf("Capture Test Pass!!\n");
}


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC clock */
    CLK->PWRCON |= CLK_PWRCON_OSC22M_EN_Msk;

    /* Waiting for IRC22M clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_OSC22M_STB_Msk));

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_HIRC;
    CLK->CLKDIV &= ~CLK_CLKDIV_HCLK_N_Msk;

    /* Set PLL to power down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware.*/
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;

    /* Enable external 12MHz XTAL, internal 22.1184MHz */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk | CLK_PWRCON_OSC22M_EN_Msk;

    /* Enable PLL and Set PLL frequency */
    CLK->PLLCON = PLLCON_SETTING;

    /* Waiting for clock ready */
    while(!(CLK->CLKSTATUS & (CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_OSC22M_STB_Msk)));

    /* Switch HCLK clock source to PLL, STCLK to HCLK/2 */
    CLK->CLKSEL0 = CLK_CLKSEL0_STCLK_S_HCLK_DIV2 | CLK_CLKSEL0_HCLK_S_PLL;

    /* Enable IP clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk | CLK_APBCLK_PWM45_EN_Msk | CLK_APBCLK_PWM67_EN_Msk;

    /* IP clock source */
    CLK->CLKSEL1 = CLK_CLKSEL1_UART_S_PLL;

    /* IP clock source */
    CLK->CLKSEL2 = CLK_CLKSEL2_PWM45_S_HXT | CLK_CLKSEL2_PWM67_S_HXT;

    /* Reset PWMB channel0~channel3 */
    SYS->IPRSTC2 = SYS_IPRSTC2_PWM47_RST_Msk;
    SYS->IPRSTC2 = 0;

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
    /* Set P2 multi-function pins for PWMB Channel0~3  */
    SYS->P2_MFP = SYS_MFP_P25_PWM5 | SYS_MFP_P26_PWM6;
}


void UART0_Init(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(PLL_CLOCK, 115200);
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}



/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("+------------------------------------------------------------------------+\n");
    printf("|                          PWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will use PWMB channel 2 to capture\n  the signal from PWMB channel 1.\n");
    printf("  I/O configuration:\n");
    printf("    PWM5(P2.5 PWMB channel 1) <--> PWM6(P2.6 PWMB channel 2)\n\n");
    printf("Use PWMB Channel 2(P2.6) to capture the PWMB Channel 1(P2.5) Waveform\n");

    while(1)
    {
        printf("Press any key to start PWM Capture Test\n");
        getchar();

        /*--------------------------------------------------------------------------------------*/
        /* Set the PWMB Channel 1 as PWM output function.                                               */
        /*--------------------------------------------------------------------------------------*/

        /* Assume PWM output frequency is 250Hz and duty ratio is 30%, user can calculate PWM settings by follows.
           duty ratio = (CMR+1)/(CNR+1)
           cycle time = CNR+1
           High level = CMR+1
           PWM clock source frequency = __HXT = 12000000
           (CNR+1) = PWM clock source frequency/prescaler/clock source divider/PWM output frequency
                   = 12000000/2/1/250 = 24000
           (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
           CNR = 23999
           duty ratio = 30% ==> (CMR+1)/(CNR+1) = 30%
           CMR = 7199
           Prescale value is 1 : prescaler= 2
           Clock divider is PWM_CSR_DIV1 : clock divider =1
        */

        /* set PWMB channel 1 output configuration */
        PWM_ConfigOutputChannel(PWMB, PWM_CH1, 250, 30);

        /* Enable PWM Output path for PWMB channel 1 */
        PWM_EnableOutput(PWMB, 0x2);

        /* Enable Timer for PWMB channel 1 */
        PWM_Start(PWMB, 0x2);

        /*--------------------------------------------------------------------------------------*/
        /* Set the PWMB channel 2  for capture function                                         */
        /*--------------------------------------------------------------------------------------*/

        /* If input minimum frequency is 250Hz, user can calculate capture settings by follows.
           Capture clock source frequency = __HXT = 12000000 in the sample code.
           (CNR+1) = Capture clock source frequency/prescaler/clock source divider/minimum input frequency
                   = 12000000/2/1/250 = 24000
           (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
           CNR = 0xFFFF
           (Note: In capture mode, user should set CNR to 0xFFFF to increase capture frequency range.)
        */

        /* set PWMB channel 2 capture configuration */
        PWM_ConfigCaptureChannel(PWMB, PWM_CH2, 166, 0);

        /* Enable capture falling edge interrupt for PWMB channel 2 */
        PWM_EnableCaptureInt(PWMB, PWM_CH2, PWM_CAPTURE_INT_FALLING_LATCH);

        /* Enable PWMB NVIC interrupt */
        NVIC_EnableIRQ((IRQn_Type)(PWMB_IRQn));

        /* Enable Timer for PWMB channel 2  */
        PWM_Start(PWMB, 0x4);

        /* Enable Capture Function for PWMB channel 2 */
        PWM_EnableCapture(PWMB, 0x4);

        /* Wait until PWMB channel 2 Timer start to count */
        while(PWMB->PDR2 == 0);

        /* Capture the Input Waveform Data */
        CalPeriodTime(PWMB, PWM_CH2);
        /*------------------------------------------------------------------------------------------------------*/
        /* Stop PWMB channel 1 (Recommended procedure method 1)                                                 */
        /* Set PWM Timer loaded value(CNR) as 0. When PWM internal counter(PDR) reaches to 0, disable PWM Timer */
        /*------------------------------------------------------------------------------------------------------*/

        /* Set PWMB channel 1 loaded value as 0 */
        PWM_Stop(PWMB, 0x2);

        /* Wait until PWMB channel 1 Timer Stop */
        while(PWMB->PDR1 != 0);

        /* Disable Timer for PWMB channel 1 */
        PWM_ForceStop(PWMB, 0x2);

        /* Disable PWM Output path for PWMB channel 1 */
        PWM_DisableOutput(PWMB, 0x2);

        /*------------------------------------------------------------------------------------------------------*/
        /* Stop PWMB channel 2 (Recommended procedure method 1)                                                 */
        /* Set PWM Timer loaded value(CNR) as 0. When PWM internal counter(PDR) reaches to 0, disable PWM Timer */
        /*------------------------------------------------------------------------------------------------------*/

        /* Disable PWMB NVIC */
        NVIC_DisableIRQ((IRQn_Type)(PWMB_IRQn));

        /* Set loaded value as 0 for PWMB channel 2 */
        PWM_Stop(PWMB, 0x4);

        /* Wait until PWMB channel 2 current counter reach to 0 */
        while(PWMB->PDR2 != 0);

        /* Disable Timer for PWMB channel 2 */
        PWM_ForceStop(PWMB, 0x4);

        /* Disable Capture Function and Capture Input path for  PWMB channel 2*/
        PWM_DisableCapture(PWMB, 0x4);

        /* Clear Capture Interrupt flag for PWMB channel 2*/
        PWM_ClearCaptureIntFlag(PWMB, PWM_CH2, PWM_CAPTURE_INT_FALLING_LATCH);
    }
}




