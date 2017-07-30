/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 15/05/22 2:05p $
 * @brief    Generate different frequency(Tenor C Do ~ Si) waveform by PWM.
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

// Scale frequency and unit is Hz
#define TENOR_C 523
#define TENOR_D 587
#define TENOR_E 659
#define TENOR_F 698
#define TENOR_G 784
#define TENOR_A 880
#define TENOR_B 988

void PWM_PwmIRQHandler(void);
/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint8_t g_u8PWMCount = 1;
volatile uint16_t g_u16Frequency;
volatile uint32_t g_u32Pulse = 0;

/* Assume PWM output frequency is 523Hz and duty ratio is 60%, user can calculate PWM settings by follows.
   PWM clock source frequency = __HXT = 12000000 in the sample code.
   (CNR+1) = PWM clock source frequency/prescaler/clock source divider/PWM output frequency
           = 12000000/2/1/523 = 11472 < 65536  (Note: If calculated value is larger than 65536, user should increase prescale value.)
   CNR = 11471 =>g_au16ScaleCnr[0] = 11471
   duty ratio = 60% = (CMR+1)/(CNR+1) ==> CMR = (CNR+1)*60/100-1 = 11472*60/100-1
   CMR = 6882 =>g_au16ScaleCmr[0] = 6882
*/
static const uint16_t g_au16ScaleFreq[7] = {TENOR_C, TENOR_D, TENOR_E, TENOR_F, TENOR_G, TENOR_A, TENOR_B};
// static const uint16_t g_au16ScaleCnr[7] =  {11471,10220,9103,8594,7652,6817,6071};
// static const uint16_t g_au16ScaleCmr[7] =  {6882 ,6131 ,5461,5156,4590,4089,3642};

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
    uint32_t u32PwmIntFlag;

    /* Handle PWMA Timer function */
    u32PwmIntFlag = PWMA->PIIR;

    /* PWMB channel 0 PWM timer interrupt */
    if(u32PwmIntFlag & PWM_PIIR_PWMIF0_Msk)
    {
        PWMA->PIIR = PWM_PIIR_PWMIF0_Msk;
        PWM_PwmIRQHandler();
    }
}


/*---------------------------------------------------------------------------------------------------------*/
/* PWM Timer function                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
void PWM_PwmIRQHandler(void)
{
    if(g_u32Pulse == 1 * g_u16Frequency / 10)
    {
        /*--------------------------------------------------------------------------------------*/
        /* Stop PWMA channel 0 Timer (Recommended procedure method 2)                           */
        /* Set PWM Timer counter as 0, When interrupt request happen, disable PWM Timer         */
        /*--------------------------------------------------------------------------------------*/
        PWMA->CNR0 = 0;
    }

    if(g_u32Pulse == 1 * g_u16Frequency / 10 + 1)
        g_u8PWMCount = 0;
    g_u32Pulse++;
}


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for IRC22M clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Enable external 12MHz XTAL, internal 22.1184MHz */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk | CLK_PWRCON_OSC22M_EN_Msk);

    /* Enable PLL and Set PLL frequency */
    CLK_SetCoreClock(PLLCON_SETTING);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk | CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to PLL, STCLK to HCLK/2 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_PLL, CLK_CLKDIV_HCLK(2));

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable PWM module clock */
    CLK_EnableModuleClock(PWM01_MODULE);
    CLK_EnableModuleClock(PWM23_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /* Select PWM module clock source */
    CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HXT, 0);
    CLK_SetModuleClock(PWM23_MODULE, CLK_CLKSEL1_PWM23_S_HXT, 0);

    /* Reset PWMA channel0~channel3 */
    SYS_ResetModule(PWM03_RST);

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
    /* Set P4 multi-function pins for PWMA Channel0 */
    SYS->P4_MFP = SYS_MFP_P40_PWM0;
}


void UART0_Init(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}



/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint8_t u8Item, u8ItemOK;

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
    printf("  This sample code will use PWMA channel 0 to drive Buzzer\n");
    printf("  I/O configuration:\n");
    printf("    PWM0(P4.0 PWMA channel 0) <--> Buzzer\n");
    printf("\nPWM Timer Waveform Test. Waveform output(P4.0 PWMA channel 0) to Buzzer\n");
    /* P4.0 PWMA channel 0 generates PWM frequency Do - Si */

    printf("Select Test Item\n");
    printf(" 1: Do (523Hz)Tenor C\n");
    printf(" 2: Re (587Hz)\n");
    printf(" 3: Mi (659Hz)\n");
    printf(" 4: Fa (698Hz)\n");
    printf(" 5: Sol(784Hz)\n");
    printf(" 6: La (880Hz)\n");
    printf(" 7: Si (988Hz)\n");

    while(1)
    {
        u8ItemOK = 1;
        u8Item = getchar();
        printf("\t");

        switch(u8Item)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            g_u16Frequency = g_au16ScaleFreq[(u8Item - '1')];
            break;
        default:
            u8ItemOK = 0;
            break;
        }

        if(u8ItemOK)
        {
            g_u32Pulse = 0;
            g_u8PWMCount = 1;

            /* Assume PWM output frequency is 523Hz and duty ratio is 60%, user can calculate PWM settings by follows.
               duty ratio = (CMR+1)/(CNR+1)
               cycle time = CNR+1
               High level = CMR+1
               PWM clock source frequency = __HXT = 12000000
               (CNR+1) = PWM clock source frequency/prescaler/clock source divider/PWM output frequency
                       = 12000000/2/1/523 = 11472
               (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
               CNR = 11471
               duty ratio = 60% ==> (CMR+1)/(CNR+1) = 60% ==> CMR = (CNR+1)*0.6-1 = 11472*60/100-1
               CMR = 6882
               Prescale value is 1 : prescaler = 2
               Clock divider is PWM_CSR_DIV1 : clock divider = 1
            */

            /* Enable PWM Output pin */
            PWM_EnableOutput(PWMA, 0x1);

            PWM_ConfigOutputChannel(PWMA, PWM_CH0, g_u16Frequency, 60);

            /* Enable Timer period Interrupt */
            PWM_EnablePeriodInt(PWMA, PWM_CH0, PWM_PERIOD_INT_UNDERFLOW);

            /* Enable PWMB NVIC */
            NVIC_EnableIRQ((IRQn_Type)(PWMA_IRQn));

            /* Enable PWM Timer */
            PWM_Start(PWMA, 0x1);

            while(g_u8PWMCount);

            /*--------------------------------------------------------------------------------------*/
            /* Stop PWM Timer (Recommended procedure method 2)                                      */
            /* Set PWM Timer counter as 0, When interrupt request happen, disable PWM Timer         */
            /* Set PWM Timer counter as 0 in Call back function                                     */
            /*--------------------------------------------------------------------------------------*/

            /* Disable PWMB NVIC */
            NVIC_DisableIRQ((IRQn_Type)(PWMA_IRQn));

            /* Wait until PWMB channel 0 Timer Stop */
            while(PWMA->PDR0 != 0);

            /* Disable the PWM Timer */
            PWM_Stop(PWMA, 0x1);

            /* Disable PWM Output pin */
            PWM_DisableOutput(PWMA, 0x1);
        }
    }
}




