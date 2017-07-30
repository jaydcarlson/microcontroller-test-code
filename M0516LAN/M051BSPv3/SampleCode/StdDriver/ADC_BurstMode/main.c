/****************************************************************************
 * @file     main.c
 * @version  V3.0
 * $Revision: 8 $
 * $Date: 15/05/22 2:04p $
 * @brief    Demonstrate A/D conversion with burst mode.
 *           In burst mode, ADC will sample and convert a specified channel continuously and
 *           store the conversion result in FIFO buffers.
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
void AdcBurstModeTest(void);


/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define BURST_COUNT 20
volatile uint32_t g_u32AdcDataCount;
uint16_t g_au16AdcData[BURST_COUNT];


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

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

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
/* Function: ADC_GetConversionRate                                                                         */
/*                                                                                                         */
/* Parameters:                                                                                             */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Returns:                                                                                                */
/*      Return the A/D conversion rate (sample/second)                                                     */
/*                                                                                                         */
/* Description:                                                                                            */
/*   The conversion rate depends on the clock source of ADC clock.                                         */
/*   It only needs 21 ADC clocks to complete an A/D conversion.                                            */
/*---------------------------------------------------------------------------------------------------------*/
static __INLINE uint32_t ADC_GetConversionRate()
{
    uint32_t u32AdcClkSrcSel;
    uint32_t u32ClkTbl[4] = {__HXT, 0, 0, __HIRC};

    /* Set the PLL clock frequency */
    u32ClkTbl[1] = PllClock;
    /* Set the system core clock frequency */
    u32ClkTbl[2] = SystemCoreClock;
    /* Get the clock source setting */
    u32AdcClkSrcSel = ((CLK->CLKSEL1 & CLK_CLKSEL1_ADC_S_Msk) >> CLK_CLKSEL1_ADC_S_Pos);
    /* Return the ADC conversion rate */
    return ((u32ClkTbl[u32AdcClkSrcSel]) / (((CLK->CLKDIV & CLK_CLKDIV_ADC_N_Msk) >> CLK_CLKDIV_ADC_N_Pos) + 1) / 21);
}

/*---------------------------------------------------------------------------------------------------------*/
/* Function: AdcBurstModeTest                                                                              */
/*                                                                                                         */
/* Parameters:                                                                                             */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Returns:                                                                                                */
/*   None.                                                                                                 */
/*                                                                                                         */
/* Description:                                                                                            */
/*   ADC burst mode test.                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void AdcBurstModeTest()
{
    uint8_t  u8Option;
    uint32_t u32Count;

    printf("\n\nConversion rate: %d samples/second\n", ADC_GetConversionRate());
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                      ADC burst mode sample code                      |\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("\nIn this test, software will get %d conversion results from the specified channel.\n", BURST_COUNT);

    while(1)
    {
        printf("\nSelect input mode:\n");
        printf("  [1] Single end input (channel 2 only)\n");
        printf("  [2] Differential input (channel pair 1 only)\n");
        printf("  Other keys: exit burst mode test\n");
        u8Option = getchar();
        if(u8Option == '1')
        {
            printf("%d conversion results of channel 2:\n", BURST_COUNT);
            /* Set the ADC operation mode as burst, input mode as single-end and enable the analog input channel 2 */
            ADC_Open(ADC, ADC_ADCR_DIFFEN_SINGLE_END, ADC_ADCR_ADMD_BURST, 0x1 << 2);

            /* Power on ADC module */
            ADC_POWER_ON(ADC);

            /* clear the A/D interrupt flag for safe */
            ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

            /* Enable the ADC interrupt */
            ADC_EnableInt(ADC, ADC_ADF_INT);
            NVIC_EnableIRQ(ADC_IRQn);

            /* Reset the ADC data counter and start A/D conversion */
            g_u32AdcDataCount = 0;
            ADC_START_CONV(ADC);

            while(g_u32AdcDataCount < BURST_COUNT);

            /* Stop A/D conversion */
            ADC_STOP_CONV(ADC);
            /* Disable the ADC interrupt */
            ADC_DisableInt(ADC, ADC_ADF_INT);
        }
        else if(u8Option == '2')
        {
            printf("%d conversion results of differential input channel pair 1:\n", BURST_COUNT);
            /* Set the ADC operation mode as burst, input mode as differential and
                             enable analog input channel 2 for differential input channel pair 1*/
            ADC_Open(ADC, ADC_ADCR_DIFFEN_DIFFERENTIAL, ADC_ADCR_ADMD_BURST, 1 << 2);

            /* Power on ADC module */
            ADC_POWER_ON(ADC);

            /* clear the A/D interrupt flag for safe */
            ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

            /* Enable the ADC interrupt */
            ADC_EnableInt(ADC, ADC_ADF_INT);
            NVIC_EnableIRQ(ADC_IRQn);

            /* Reset the ADC data counter and start A/D conversion */
            g_u32AdcDataCount = 0;
            ADC_START_CONV(ADC);

            while(g_u32AdcDataCount < BURST_COUNT);

            /* Stop A/D conversion */
            ADC_STOP_CONV(ADC);
            /* Disable the ADC interrupt */
            ADC_DisableInt(ADC, ADC_ADF_INT);
        }
        else
            return ;

        for(u32Count = 0; u32Count < BURST_COUNT; u32Count++)
        {
            printf("Conversion result: 0x%X\n", g_au16AdcData[u32Count]);
        }

        /* Change operation mode to clear burst mode FIFO buffers */
        ADC_Open(ADC, ADC_ADCR_DIFFEN_DIFFERENTIAL, ADC_ADCR_ADMD_SINGLE, 2);

    }
}

/*---------------------------------------------------------------------------------------------------------*/
/* ADC interrupt handler                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
void ADC_IRQHandler(void)
{
    while(ADC_IS_DATA_VALID(ADC, 0)) /* Check the VALID bits */
    {
        if(g_u32AdcDataCount >= BURST_COUNT)
            return;
        /* In burst mode, the software always gets the conversion result of the specified channel from channel 0 */
        g_au16AdcData[g_u32AdcDataCount++] = (uint16_t)ADC_GET_CONVERSION_DATA(ADC, 0);
    }

    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT); /* clear the A/D conversion flag */
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

    /* Burst Mode test */
    AdcBurstModeTest();

    /* Disable ADC module */
    ADC_Close(ADC);

    /* Disable ADC IP clock */
    CLK_DisableModuleClock(ADC_MODULE);

    /* Disable External Interrupt */
    NVIC_DisableIRQ(ADC_IRQn);

    printf("\nExit ADC sample code\n");

    while(1);

}

