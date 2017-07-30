/****************************************************************************
 * @file     main.c
 * @version  V3.0
 * $Revision: 5 $
 * $Date: 15/05/22 2:02p $
 * @brief    Monitor the conversion result of channel 2 by the digital compare function.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000


/*---------------------------------------------------------------------------------------------------------*/
/* Define Function Prototypes                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
void SYS_Init(void);
void UART0_Init(void);
void AdcResultMonitorTest(void);


/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint32_t g_u32AdcCmp0IntFlag;
volatile uint32_t g_u32AdcCmp1IntFlag;


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK->PWRCON |= CLK_PWRCON_OSC22M_EN_Msk;

    /* Waiting for Internal RC clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_OSC22M_STB_Msk));

    /* Switch HCLK clock source to Internal RC */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_HIRC;

    /* Enable external XTAL 12MHz clock */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk;

    /* Waiting for external XTAL clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTL12M_STB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCON = PLLCON_SETTING;
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_PLL_STB_Msk));
    CLK->CLKSEL0 &= (~CLK_CLKSEL0_HCLK_S_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_PLL;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /* Enable UART module clock */
    CLK->APBCLK |= CLK_APBCLK_UART0_EN_Msk;

    /* Enable ADC module clock */
    CLK->APBCLK |= CLK_APBCLK_ADC_EN_Msk ;

    /* Select UART module clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= CLK_CLKSEL1_UART_S_HXT;

    /* Select ADC module clock source */
    CLK->CLKSEL1 &= CLK_CLKSEL1_ADC_S_Msk ;
    CLK->CLKSEL1 |= CLK_CLKSEL1_ADC_S_HIRC ;

    /* ADC clock source is 22.1184MHz, set divider to 7, ADC clock is 22.1184/7 MHz */
    CLK->CLKDIV  = (CLK->CLKDIV & ~CLK_CLKDIV_ADC_N_Msk) | (((7) - 1) << CLK_CLKDIV_ADC_N_Pos);


    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= (SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0);

    /* Disable the P1.0 - P1.3 digital input path to avoid the leakage current. */
    P1->OFFD = 0xF << GPIO_OFFD_OFFD_Pos;
    /* Configure the P1.0 - P1.3 ADC analog input pins */
    SYS->P1_MFP &= ~(SYS_MFP_P10_Msk | SYS_MFP_P11_Msk | SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
    SYS->P1_MFP |= SYS_MFP_P10_AIN0 | SYS_MFP_P11_AIN1 | SYS_MFP_P12_AIN2 | SYS_MFP_P13_AIN3 ;

}

/*---------------------------------------------------------------------------------------------------------*/
/* Init UART                                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
void UART0_Init()
{
    /* Reset UART IP */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

    /* Configure UART0 and set UART0 Baudrate */
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}

/*---------------------------------------------------------------------------------------------------------*/
/* Function: AdcResultMonitorTest                                                                          */
/*                                                                                                         */
/* Parameters:                                                                                             */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Returns:                                                                                                */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Description:                                                                                            */
/*   ADC result monitor function test.                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void AdcResultMonitorTest()
{
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|           ADC compare function (result monitor) sample code          |\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("\nIn this test, software will compare the conversion result of channel 2.\n");

    /* Set the ADC operation mode as continuous scan, input mode as single-end and enable the ADC converter */
    ADC->ADCR = (ADC_ADCR_ADMD_CONTINUOUS | ADC_ADCR_DIFFEN_SINGLE_END | ADC_ADCR_ADEN_Msk);
    /* Set the ADC channel 2 */
    ADC->ADCHER |= ((ADC->ADCHER & ~ADC_ADCHER_CHEN_Msk) | (1 << 2));

    /* Enable ADC comparator 0. Compare condition: conversion result < 0x800; match Count=5. */
    printf("   Set the compare condition of comparator 0: channel 2 is less than 0x800; match count is 5.\n");
    ADC->ADCMPR[0] = (ADC->ADCMPR[0] & ~(ADC_ADCMPR_CMPD_Msk | ADC_ADCMPR_CMPMATCNT_Msk | ADC_ADCMPR_CMPCH_Msk | ADC_ADCMPR_CMPCOND_Msk)) | \
                     ((0x800) << ADC_ADCMPR_CMPD_Pos) | \
                     (((5) - 1) << ADC_ADCMPR_CMPMATCNT_Pos) | \
                     ((2) << ADC_ADCMPR_CMPCH_Pos) | \
                     ((ADC_LESS_THAN) << ADC_ADCMPR_CMPCOND_Pos) | ADC_ADCMPR_CMPEN_Msk;

    /* Enable ADC comparator 1. Compare condition: conversion result >= 0x800; match Count=5. */
    printf("   Set the compare condition of comparator 1 : channel 2 is greater than or equal to 0x800; match count is 5.\n");
    ADC->ADCMPR[1] = (ADC->ADCMPR[1] & ~(ADC_ADCMPR_CMPD_Msk | ADC_ADCMPR_CMPMATCNT_Msk | ADC_ADCMPR_CMPCH_Msk | ADC_ADCMPR_CMPCOND_Msk)) | \
                     ((0x800) << ADC_ADCMPR_CMPD_Pos) | \
                     (((5) - 1) << ADC_ADCMPR_CMPMATCNT_Pos) | \
                     ((2) << ADC_ADCMPR_CMPCH_Pos) | \
                     ((ADC_GREATER_OR_EQUAL) << ADC_ADCMPR_CMPCOND_Pos) | ADC_ADCMPR_CMPEN_Msk;

    /* clear the ADC comparator 0 interrupt flag for safe */
    ADC->ADSR = ADC_ADSR_CMPF0_Msk;
    /* enable ADC comparator 0 interrupt */
    ADC->ADCMPR[(0)] |= ADC_ADCMPR_CMPIE_Msk;

    /* clear the ADC comparator 1 interrupt flag for safe */
    ADC->ADSR = ADC_ADSR_CMPF1_Msk;
    /* enable ADC comparator 1 interrupt */
    ADC->ADCMPR[(1)] |= ADC_ADCMPR_CMPIE_Msk;

    NVIC_EnableIRQ(ADC_IRQn);

    g_u32AdcCmp0IntFlag = 0;
    g_u32AdcCmp1IntFlag = 0;

    /* Clear the ADC interrupt flag */
    ADC->ADSR = ADC_ADSR_ADF_Msk;

    /* start A/D conversion */
    ADC->ADCR |= ADC_ADCR_ADST_Msk;

    /* Wait ADC compare interrupt */
    while((g_u32AdcCmp0IntFlag == 0) && (g_u32AdcCmp1IntFlag == 0));

    /* Stop A/D conversion */
    ADC->ADCR &= ~ADC_ADCR_ADST_Msk;
    /* Disable ADC comparator interrupt */
    ADC->ADCMPR[(0)] &= ~ADC_ADCMPR_CMPIE_Msk;
    ADC->ADCMPR[(1)] &= ~ADC_ADCMPR_CMPIE_Msk;
    /* Disable compare function */
    ADC->ADCMPR[(0)] &= ~ADC_ADCMPR_CMPEN_Msk;
    ADC->ADCMPR[(1)] &= ~ADC_ADCMPR_CMPEN_Msk;

    if(g_u32AdcCmp0IntFlag == 1)
    {
        printf("Comparator 0 interrupt occurs.\nThe conversion result of channel 2 is less than 0x800\n");
    }
    else
    {
        printf("Comparator 1 interrupt occurs.\nThe conversion result of channel 2 is greater than or equal to 0x800\n");
    }
}


/*---------------------------------------------------------------------------------------------------------*/
/* ADC interrupt handler                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
void ADC_IRQHandler(void)
{
    if(ADC->ADSR & ADC_ADSR_CMPF0_Msk)
    {
        g_u32AdcCmp0IntFlag = 1;
        ADC->ADSR = ADC_ADSR_CMPF0_Msk;     /* clear the A/D compare flag 0 */
    }

    if(ADC->ADSR & ADC_ADSR_CMPF1_Msk)
    {
        g_u32AdcCmp1IntFlag = 1;
        ADC->ADSR = ADC_ADSR_CMPF1_Msk;     /* clear the A/D compare flag 1 */
    }
}


/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
main(void)
{

    /* Unlock protected registers */
    SYS->REGWRPROT = 0x59;
    SYS->REGWRPROT = 0x16;
    SYS->REGWRPROT = 0x88;

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS->REGWRPROT = 0x0;

    /* Init UART0 for printf */
    UART0_Init();

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* Result monitor test */
    AdcResultMonitorTest();

    /* Reset ADC module */
    SYS->IPRSTC2 |= (1 << SYS_IPRSTC2_ADC_RST_Pos) ;
    SYS->IPRSTC2 &= ~(1 << (SYS_IPRSTC2_ADC_RST_Pos)) ;

    /* Disable ADC IP clock */
    CLK->APBCLK &= ~CLK_APBCLK_ADC_EN_Msk;

    /* Disable External Interrupt */
    NVIC_DisableIRQ(ADC_IRQn);

    printf("Exit ADC sample code\n");

    while(1);

}

