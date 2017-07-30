/**************************************************************************//**
 * @file     main.c
 * @version  V2.00
 * $Revision: 10 $
 * $Date: 15/07/13 1:27p $
 * @brief    Change system clock to different PLL frequency and output system clock from CLKO pin.
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

#define SIGNATURE       0x125ab234
#define FLAG_ADDR       0x20000FFC

/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector IRQ Handler                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void BOD_IRQHandler(void)
{
    /* Clear BOD Interrupt Flag */
    SYS_CLEAR_BOD_INT_FLAG();

    printf("Brown Out is Detected\n");
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Simple calculation test function                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define PI_NUM  256
int32_t f[PI_NUM + 1];
uint32_t piTbl[19] =
{
    3141,
    5926,
    5358,
    9793,
    2384,
    6264,
    3383,
    2795,
    288,
    4197,
    1693,
    9937,
    5105,
    8209,
    7494,
    4592,
    3078,
    1640,
    6284
};

int32_t piResult[19];

int32_t pi(void)
{
    int32_t i, i32Err;
    int32_t a = 10000, b = 0, c = PI_NUM, d = 0, e = 0, g = 0;

    for(; b - c;)
        f[b++] = a / 5;

    i = 0;
    for(; d = 0, g = c * 2; c -= 14,/*printf("%.4d\n",e+d/a),*/ piResult[i++] = e + d / a, e = d % a)
    {
        if(i == 19)
            break;

        for(b = c; d += f[b] * a, f[b] = d % --g, d /= g--, --b; d *= b);
    }
    i32Err = 0;
    for(i = 0; i < 19; i++)
    {
        if(piTbl[i] != piResult[i])
            i32Err = -1;
    }

    return i32Err;
}

void Delay(uint32_t x)
{
    int32_t i;

    for(i = 0; i < x; i++)
    {
        __NOP();
        __NOP();
    }
}

uint32_t g_au32PllSetting[] =
{
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(25) | CLK_PLLCON_NO_4,  /* PLL = 25MHz */
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(29) | CLK_PLLCON_NO_4,  /* PLL = 29MHz */
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(33) | CLK_PLLCON_NO_4,  /* PLL = 33MHz */
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(37) | CLK_PLLCON_NO_4,  /* PLL = 37MHz */
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(41) | CLK_PLLCON_NO_4,  /* PLL = 41MHz */
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(45) | CLK_PLLCON_NO_4,  /* PLL = 45MHz */
    CLK_PLLCON_PLL_SRC_HXT | CLK_PLLCON_NR(3) | CLK_PLLCON_NF(49) | CLK_PLLCON_NO_4   /* PLL = 49MHz */
};

void SYS_PLL_Test(void)
{
    int32_t  i;

    /*---------------------------------------------------------------------------------------------------------*/
    /* PLL clock configuration test                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\n-------------------------[ Test PLL ]-----------------------------\n");

    for(i = 0; i < sizeof(g_au32PllSetting) / sizeof(g_au32PllSetting[0]) ; i++)
    {
        /* Switch HCLK clock source to HXT and HCLK source divide 1 */
        CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLK_S_Msk)) | CLK_CLKSEL0_HCLK_S_HXT;
        CLK->CLKDIV = (CLK->CLKDIV & (~CLK_CLKDIV_HCLK_N_Msk)) | CLK_CLKDIV_HCLK(1);

        /* Set PLL to power down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware. */
        CLK->PLLCON |= CLK_PLLCON_PD_Msk;

        /* Set PLL frequency */
        CLK->PLLCON = g_au32PllSetting[i];

        /* Waiting for PLL clock ready */
        while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_PLL_STB_Msk));

        /* Switch HCLK clock source to PLL */
        CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLK_S_Msk)) | CLK_CLKSEL0_HCLK_S_PLL;

        /* Update System Core Clock */
        SystemCoreClockUpdate();

        printf("  Change system clock to %d Hz ...................... ", SystemCoreClock);

        /* Enable CKO clock source */
        CLK->APBCLK |= CLK_APBCLK_FDIV_EN_Msk;

        /* CKO = clock source / 2^(1 + 1) */
        CLK->FRQDIV = CLK_FRQDIV_DIVIDER_EN_Msk | (1);

        /* Select CKO clock source as HCLK */
        CLK->CLKSEL2 = (CLK->CLKSEL2 & (~CLK_CLKSEL2_FRQDIV_S_Msk)) | CLK_CLKSEL2_FRQDIV_S_HCLK;

        /* The delay loop is used to check if the CPU speed is increasing */
        Delay(0x400000);

        if(pi())
        {
            printf("[FAIL]\n");
        }
        else
        {
            printf("[OK]\n");
        }

        /* Disable CKO clock */
        CLK->APBCLK &= (~CLK_APBCLK_FDIV_EN_Msk);
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
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_OSC22M_STB_Msk));

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLK_S_Msk)) | CLK_CLKSEL0_HCLK_S_HIRC ;
    CLK->CLKDIV = (CLK->CLKDIV & (~CLK_CLKDIV_HCLK_N_Msk)) | CLK_CLKDIV_HCLK(1);

    /* Set PLL to Power down mode and HW will also clear PLL_STB bit in CLKSTATUS register */
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;  
    
    /* Enable external XTAL 12MHz clock */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk;

    /* Waiting for external XTAL clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTL12M_STB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCON = PLLCON_SETTING;
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_PLL_STB_Msk));
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLK_S_Msk)) | CLK_CLKSEL0_HCLK_S_PLL;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For CLK_SysTickDelay()

    /* Enable UART module clock */
    CLK->APBCLK |= CLK_APBCLK_UART0_EN_Msk;

    /* Select UART module clock source */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_UART_S_Msk)) | CLK_CLKSEL1_UART_S_HXT;

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD, TXD and CKO */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk  | SYS_MFP_P36_Msk);
    SYS->P3_MFP |= (SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P36_CKO);

}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

    /* Configure UART0 and set UART0 Baudrate */
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t u32data;

    /* If define INIT_SYSCLK_AT_BOOTING in system_M051Series.h, HCLK will be set to 50MHz in SystemInit(void). */
    /* In end of main function, program issued CPU reset and write-protection will be disabled. */
    if(SYS->REGWRPROT == 1)
        SYS->REGWRPROT = 0x0;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %dHz\n", SystemCoreClock);

    /*
        This sample code will show some function about system manager controller and clock controller:
        1. Read PDID
        2. Get and clear reset source
        3. Setting about BOD
        4. Change system clock depended on different PLL settings
        5. Output system clock from CKO pin, and the output frequency = system clock / 4
    */

    printf("+---------------------------------------+\n");
    printf("|    M05xx System Driver Sample Code    |\n");
    printf("+---------------------------------------+\n");

    if(M32(FLAG_ADDR) == SIGNATURE)
    {
        printf("  CPU Reset success!\n");
        M32(FLAG_ADDR) = 0;
        printf("  Press any key to continue ...\n");
        getchar();
    }

    /*---------------------------------------------------------------------------------------------------------*/
    /* Misc system function test                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Read Part Device ID */
    printf("Product ID 0x%x\n", SYS->PDID);

    /* Get reset source from last operation */
    u32data = SYS->RSTSRC;
    printf("Reset Source 0x%x\n", u32data);

    /* Clear reset source */
    SYS->RSTSRC = u32data;

    /* Unlock protected registers for Brown-out Detector settings */
    SYS->REGWRPROT = 0x59;
    SYS->REGWRPROT = 0x16;
    SYS->REGWRPROT = 0x88;

    /* Check if the write-protected registers are unlocked before BOD setting and CPU Reset */
    if(SYS->REGWRPROT != 0)
    {
        printf("Protected Address is Unlocked\n");
    }

    /* Enable Brown-out Detector and Low Voltage Reset function, and set Brown-out Detector voltage 2.7V */
    SYS->BODCR = SYS_BODCR_BOD_EN_Msk | SYS_BODCR_BOD_VL_2_7V | SYS_BODCR_LVR_EN_Msk;

    /* Enable BOD IRQ */
    NVIC_EnableIRQ(BOD_IRQn);

    /* Run PLL Test */
    SYS_PLL_Test();

    /* Write a signature work to SRAM to check if it is reset by software */
    M32(FLAG_ADDR) = SIGNATURE;
    printf("\n\n  >>> Reset CPU <<<\n");

    /* Waiting for message send out */
    while(!(UART0->FSR & UART_FSR_TE_FLAG_Msk));

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLK_S_Msk)) | CLK_CLKSEL0_HCLK_S_HIRC;
    CLK->CLKDIV = (CLK->CLKDIV & (~CLK_CLKDIV_HCLK_N_Msk)) | CLK_CLKDIV_HCLK(1);

    /* Set PLL to Power down mode and HW will also clear PLL_STB bit in CLKSTATUS register */
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;

    /* Reset CPU */
    SYS->IPRSTC1 |= SYS_IPRSTC1_CPU_RST_Msk;
}
