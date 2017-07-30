/******************************************************************************
 * @file     main.c
 * @version  V0.10
 * $Revision: 2 $
 * $Date: 14/01/28 11:43a $
 * @brief    ADC and PWM sample for M051 learning board
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "M051Series.h"
#include "lcd_driver.h"

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable ADC and PWM23 clock */
    CLK->APBCLK = CLK_APBCLK_PWM23_EN_Msk | CLK_APBCLK_ADC_EN_Msk;

    /* ADC clock source is 22.1184MHz, set divider to (3 + 1), ADC clock is 22.1184/4 MHz */
    CLK->CLKDIV |= (3 << CLK_CLKDIV_ADC_N_Pos);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P4.3 to PWM3 function */
    SYS->P4_MFP = SYS_MFP_P43_PWM3;
    /* Set P1.0 to AIN0 function */
    SYS->P1_MFP = SYS_MFP_P10_AIN0;

    /* Disable digital input path of analog pin AIN0 to prevent leakage */
    P1->OFFD |= 1 << GPIO_OFFD_OFFD_Pos;

    /* Lock protected registers */
    SYS_LockReg();
}


void PWM_Init(void)
{
    /* Set PWM 3 clock prescale to 60, and divider to 1*/
    PWMA->PPR = 60 << PWM_PPR_CP23_Pos;
    PWMA->CSR = PWM_CLK_DIV_1 << PWM_CSR_CSR3_Pos;

    /* Enable PWM3 and set to auto-reload mode.
       Configure PWM mode before setting CNR, CMR. Otherwise CNR will be reset */
    PWMA->PCR = PWM_PCR_CH3EN_Msk | PWM_PCR_CH3MOD_Msk;
    /* PWM 3 frequency = HCLK / (prescale * divider * (CNR + 1))
       PWM 3 duty ratio = (CMR + 1) / (CNR + 1) */
    PWMA->CNR3 = 1843 - 1;
    PWMA->CMR3 = 1833 - 1;

    /* Enable PWM3 Output */
    PWMA->POE = PWM_POE_PWM3_Msk;

}

void ADC_Init(void)
{
    /* Set to convert ADC channel 0 */
    ADC->ADCHER = 0x1;
    /* Enable the ADC converter */
    ADC->ADCR = ADC_ADCR_ADEN_Msk;

}

/* Main function  */
int main(void)
{
    uint32_t u32Data, u32Sum, u32Count;
    char adc_value[20];

    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Initial LCD panel. SPI clock and interface is configured in this function. */
    LCD_Init();
    /* Clear LCD screen. Do this before turn back light on */
    LCD_ClearScreen();
    /* Enable LCD back light */
    LCD_EnableBackLight();
    /* Show messages on LCD */
    LCD_Print(0, "ADC_PWM");
    LCD_Print(1, "Sample code");
    LCD_Print(2, "ADC Value:");

    /* Init PWM channel 3 */
    PWM_Init();

    /* Init ADC to get the value of variable resistor */
    ADC_Init();

    u32Count = 0;
    u32Sum = 0;

    while(1)
    {
        /* Start convert */
        ADC_START_CONV(ADC);

        /* Waiting for convert complete */
        while(ADC_IS_BUSY(ADC));

        /* Read the result from ADC */
        u32Data = ADC->ADDR[0] & ADC_ADDR_RSLT_Msk;

        /* Determine the sum */
        u32Sum += u32Data;
        u32Count++;
        if(u32Count == 128)
        {
            /* Determine the average */
            u32Data = u32Sum / 128;
            /* Update the average ADC conversion result to LCD */
            sprintf(adc_value, "          %4d", u32Data);
            LCD_Print(3, adc_value);
            /* Adjust the duty cycle of PWM3 according to the average ADC value. */
            PWMA->CMR3 = (u32Data * PWMA->CNR3) / 4096;
            /* Reset count and sum */
            u32Count = 0;
            u32Sum = 0;
        }
    }
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/


