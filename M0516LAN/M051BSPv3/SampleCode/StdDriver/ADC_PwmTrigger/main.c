/****************************************************************************
 * @file    main.c
 * @version  V3.0
 * $Revision: 5 $
 * $Date: 15/05/22 2:04p $
 * @brief    Demonstrate how to trigger ADC by PWM.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLL_CLOCK       50000000


/*---------------------------------------------------------------------------------------------------------*/
/* Define Function Prototypes                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
void SYS_Init(void);
void UART0_Init(void);
void ADC_PWMTrigTest_SingleOpMode(void);


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable ADC module clock */
    CLK_EnableModuleClock(ADC_MODULE);

    /* Enable PWM01 module clock */
    CLK_EnableModuleClock(PWM01_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /* Select PWM01 module clock source */
    CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HXT, 0);

    /* ADC clock source is 22.1184MHz, set divider to 7, ADC clock is 22.1184/7 MHz */
    CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL1_ADC_S_HIRC, CLK_CLKDIV_ADC(7));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;

    /* Disable the P1.0 - P1.3 digital input path to avoid the leakage current */
    GPIO_DISABLE_DIGITAL_PATH(P1, 0xF);

    /* Configure the P1.0 - P1.3 ADC analog input pins */
    SYS->P1_MFP &= ~(SYS_MFP_P10_Msk | SYS_MFP_P11_Msk | SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
    SYS->P1_MFP |= SYS_MFP_P10_AIN0 | SYS_MFP_P11_AIN1 | SYS_MFP_P12_AIN2 | SYS_MFP_P13_AIN3 ;

    /* Configure the P2.0 as PWM0 output pin */
    SYS->P2_MFP &= ~(SYS_MFP_P20_Msk);
    SYS->P2_MFP |= SYS_MFP_P20_PWM0;

}

/*---------------------------------------------------------------------------------------------------------*/
/* Init UART                                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
void UART0_Init()
{
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/* Function: ADC_PWMTrigTest_SingleOpMode                                                                  */
/*                                                                                                         */
/* Parameters:                                                                                             */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Returns:                                                                                                */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Description:                                                                                            */
/*   ADC hardware trigger test.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void ADC_PWMTrigTest_SingleOpMode()
{
    printf("\n<<< PWM trigger test (Single mode) >>>\n");

    /* Set the ADC operation mode as single, input mode as single-end and enable the analog input channel 2 */
    ADC_Open(ADC, ADC_ADCR_DIFFEN_SINGLE_END, ADC_ADCR_ADMD_SINGLE, 0x1 << 2);

    /* Power on ADC module */
    ADC_POWER_ON(ADC);

    /* Configure the hardware trigger condition and enable hardware trigger; PWM trigger delay: (4*10) system clock cycles*/
    ADC_EnableHWTrigger(ADC, ADC_ADCR_TRGS_PWM, 10);

    /* clear the A/D interrupt flag for safe */
    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

    /* Edge-aligned type; one-shot mode. */
    PWM_SET_ALIGNED_TYPE(PWMA, 0x1, PWM_EDGE_ALIGNED);
    /* Clock prescaler */
    PWM_SET_PRESCALER(PWMA, 0, 2);
    /* Timer 0 divisor=1 */
    PWM_SET_DIVIDER(PWMA, 0, PWM_CLK_DIV_1);
    /* PWM counter value */ /* PWM frequency = PWM clock source/(clock prescaler setting + 1)/divisor/(CNR+1) */
    PWM_SET_CNR(PWMA, 0, 5);
    /* PWM compare value */
    PWM_SET_CMR(PWMA, 0, 1);
    /* Enable PWM0 to trigger ADC */
    PWM_EnableADCTrigger(PWMA, 0, PWM_PERIOD_TRIGGER_ADC);
    /* PWM0 pin output enabled. PWM frequency 1MHz, duty 30%. */
    PWM_EnableOutput(PWMA, 0x1);
    /* Start PWM module */
    PWM_Start(PWMA, 0x1);

    /* Wait conversion done */
    while(!ADC_GET_INT_FLAG(ADC, ADC_ADF_INT));

    /* Clear the ADC interrupt flag */
    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

    printf("Channel 2: 0x%X\n", ADC_GET_CONVERSION_DATA(ADC, 2));

    /* Disable ADC */
    ADC_POWER_DOWN(ADC);
    /* Stop PWM generation */
    PWM_ForceStop(PWMA, 0x1);

}





/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
main(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* ADC hardware trigger test */
    ADC_PWMTrigTest_SingleOpMode();

    /* Disable ADC module */
    ADC_Close(ADC);

    /* Disable ADC IP clock */
    CLK_DisableModuleClock(ADC_MODULE);

    /* Disable External Interrupt */
    NVIC_DisableIRQ(ADC_IRQn);

    printf("\nExit ADC sample code\n");

    while(1);

}

