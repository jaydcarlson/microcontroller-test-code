/**************************************************************************//**
 * @file     main.c
 * @version  V2.00
 * $Revision: 6 $
 * $Date: 15/05/22 2:52p $
 * @brief    Change system clock to different PLL frequency and output system clock from CLKO pin.
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

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
        CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_CLKDIV_HCLK(1));

        /* Set PLL to power down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware. */
        CLK_DisablePLL();

        /* Set PLL frequency */
        CLK->PLLCON = g_au32PllSetting[i];

        /* Waiting for PLL clock ready */
        CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk);

        /* Switch HCLK clock source to PLL */
        CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_PLL, CLK_CLKDIV_HCLK(1));

        printf("  Change system clock to %d Hz ...................... ", SystemCoreClock);

        /* Output selected clock to CKO, CKO Clock = HCLK / 2^(1 + 1) */
        CLK_EnableCKO(CLK_CLKSEL2_FRQDIV_S_HCLK, 1, 0);

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
        CLK_DisableCKO();
    }
}

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

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD , TXD and CKO */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk  | SYS_MFP_P36_Msk);
    SYS->P3_MFP |= (SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P36_CKO);

}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t u32data;

    /* If define INIT_SYSCLK_AT_BOOTING in system_M051Series.h, HCLK will be set to 50MHz in SystemInit(void). */
    /* In end of main function, program issued CPU reset and write-protection will be disabled. */
    if(SYS_IsRegLocked() == 0)
        SYS_LockReg();

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
    printf("Product ID 0x%x\n", SYS_ReadPDID());

    /* Get reset source from last operation */
    u32data = SYS_GetResetSrc();
    printf("Reset Source 0x%x\n", u32data);

    /* Clear reset source */
    SYS_ClearResetSrc(u32data);

    /* Unlock protected registers for Brown-Out Detector settings */
    SYS_UnlockReg();

    /* Check if the write-protected registers are unlocked before BOD setting and CPU Reset */
    if(SYS_IsRegLocked() == 0)
    {
        printf("Protected Address is Unlocked\n");
    }

    /* Enable Brown-Out Detector, and set Brown-Out Detector voltage 2.7V */
    SYS_EnableBOD(SYS_BODCR_BOD_INTERRUPT_EN, SYS_BODCR_BOD_VL_2_7V);

    /* Enable BOD IRQ */
    NVIC_EnableIRQ(BOD_IRQn);

    /* Enable Low Voltage Reset function */
    SYS_ENABLE_LVR();

    /* Run PLL Test */
    SYS_PLL_Test();

    /* Write a signature work to SRAM to check if it is reset by software */
    M32(FLAG_ADDR) = SIGNATURE;
    printf("\n\n  >>> Reset CPU <<<\n");

    /* Waiting for message send out */
    UART_WAIT_TX_EMPTY(UART0);

    /* Switch HCLK clock source to Internal RC 22.1184MHz clock and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Set PLL to Power down mode and HW will also clear PLL_STB bit in CLKSTATUS register */
    CLK_DisablePLL();

    /* Reset CPU */
    SYS_ResetCPU();
}
