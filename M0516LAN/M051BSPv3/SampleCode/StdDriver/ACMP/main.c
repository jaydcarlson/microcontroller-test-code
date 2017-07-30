/******************************************************************************
 * @file     main.c
 * @version  V3.00
 * $Revision: 7 $
 * $Date: 15/05/22 2:56p $
 * @brief    Demonstrate how ACMP works with internal band-gap voltage.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "M051Series.h"

/* Function prototype declaration */
void SYS_Init(void);

int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();
    /* Lock protected registers */
    SYS_LockReg();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    printf("\n\n");
    printf("+---------------------------------------+\n");
    printf("|         M051 ACMP Sample Code         |\n");
    printf("+---------------------------------------+\n");

    printf("\nThis sample code demonstrates ACMP0 function. Using ACMP0_P (P1.5) as ACMP0\n");
    printf("positive input and using internal band-gap voltage as the negative input\n");
    printf("The compare result reflects on ACMP0_O (P3.6)\n");

    /* Configure ACMP0. Enable ACMP0 and select internal reference voltage as negative input. */
    ACMP_Open(ACMP01, 0, ACMP_CR_VNEG_BANDGAP, ACMP_CR_HYSTERESIS_DISABLE);
    /* Enable ACMP0 interrupt function */
    ACMP_ENABLE_INT(ACMP01, 0);

    /* Enable ACMP01 interrupt */
    NVIC_EnableIRQ(ACMP01_IRQn);

    while(1);

}

void ACMP01_IRQHandler(void)
{
    static uint32_t u32Cnt = 0;

    /* Clear ACMP 0 interrupt flag */
    ACMP_CLR_INT_FLAG(ACMP01, 0);
    /* Check Comparator 0 Output Status */
    if(ACMP_GET_OUTPUT(ACMP01, 0))
        printf("ACMP0_P voltage > Band-gap voltage (%d)\n", u32Cnt);
    else
        printf("ACMP0_P voltage <= Band-gap voltage (%d)\n", u32Cnt);

    u32Cnt++;
}


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable external 12MHz XTAL */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Select HXT as the clock source of UART */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    /* Enable ACMP01 peripheral clock */
    CLK_EnableModuleClock(ACMP01_MODULE);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();


    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P1.5 multi-function pin for ACMP0 positive input pin */
    SYS->P1_MFP = SYS_MFP_P15_ACMP0_P;

    /* Disable digital input path of analog pin ACMP0_P to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(P1, BIT5);

    /* Set P3 multi-function pins for UART0 RXD, TXD and ACMP0 output */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P36_ACMP0_O;
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/


