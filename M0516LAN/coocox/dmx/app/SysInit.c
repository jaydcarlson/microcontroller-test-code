/*************************************************************
 * @file      : Init.c
 * @brief     : Peripheral Init Functions
 * @version   : 1.2.4
 * @date      : 07/29/2017  19:50
 * @author    : Created by CoSmart 1.2.4
**************************************************************/
#include "M051Series.h"

/*************************************************************
* PWMA Initialization Code Template
**************************************************************/
void PWMA_Init()
{
    /* Unlock protected registers */
    SYS_UnlockReg();



    CLK_EnableModuleClock(PWM01_MODULE);
    CLK_EnableModuleClock(PWM23_MODULE);

    CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HIRC, 0);
    CLK_SetModuleClock(PWM23_MODULE, CLK_CLKSEL1_PWM23_S_HIRC, 0);

    PWM_EnableOutput(PWMA, BIT0 | BIT1 | BIT2);

	PWMA->PPR |= 0xffff;

	// Disable one-shot mode and invert the channels, as LEDs are open-drain
	PWMA->PCR |= PWM_PCR_CH0MOD_Msk | PWM_PCR_CH1MOD_Msk | PWM_PCR_CH2MOD_Msk |
				 PWM_PCR_CH0INV_Msk | PWM_PCR_CH1INV_Msk | PWM_PCR_CH2INV_Msk;
//
	PWMA->CMR0 = 10;
	PWMA->CMR1 = 10;
	PWMA->CMR2 = 10;

	PWMA->CNR0 = 255;
	PWMA->CNR1 = 255;
	PWMA->CNR2 = 255;

	/* Enable PWM Timer */
	PWM_Start(PWMA, BIT0 | BIT1 | BIT2);

    SYS->P2_MFP |= SYS_MFP_P20_PWM0;
    SYS->P2_MFP |= SYS_MFP_P21_PWM1;
    SYS->P2_MFP |= SYS_MFP_P22_PWM2;
}

/*************************************************************
 * GPIO0 Initialization
**************************************************************/
void GPIO0_Init()
{
	GPIO_SetMode(P0, 0, GPIO_PMD_OUTPUT);
	GPIO_SetMode(P0, 1, GPIO_PMD_OUTPUT);
	GPIO_SetMode(P0, 2, GPIO_PMD_OUTPUT);
}


/*************************************************************
 * UART0 Initialization
**************************************************************/
void UART0_Init()
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    SYS->P3_MFP |= SYS_MFP_P30_RXD0;

    CLK_EnableModuleClock(UART0_MODULE);

    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HIRC, CLK_CLKDIV_UART(1));

    UART_Open(UART0, 250000);

    UART_EnableInt(UART0, UART_IER_RDA_IEN_Msk | UART_IER_RLS_IEN_Msk | UART_IER_BUF_ERR_IEN_Msk);
    NVIC_EnableIRQ(UART0_IRQn);

}
/*************************************************************
 * SYS Initialization Code Template
**************************************************************/
void SYS_Init()
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    CLK_SetCoreClock(50000000);
    /* Lock protected registers */
    SYS_LockReg();
}

void Init()
{
    SYS_Init();
	PWMA_Init();
    GPIO0_Init();
    UART0_Init();

}
