/**************************************************************************//**
 * @file     main.c
 * @version  V0.10
 * $Revision: 3 $
 * $Date: 14/01/28 11:43a $
 * @brief    M051 Series SPI Flash Driver Sample Code
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"
#include "spi_flash.h"
#include "lcd_driver.h"

#define TEST_PAGE_NUM 10  /* page numbers */
#define BYTE_PER_PAGE 256 /* byte per page */

uint8_t SrcArray[BYTE_PER_PAGE];
uint8_t DestArray[BYTE_PER_PAGE];
uint32_t g_u32SystickCount;

/* Function prototype declaration */
void SYS_Init(void);

/* ------------- */
/* Main function */
/* ------------- */
int main(void)
{
    uint32_t u32ByteCount, u32FlashAddress, u32PageNumber;
    uint32_t u32Error = 0;
    uint32_t u32ID;
    uint32_t u32Duration_W, u32Duration_R;
    char au8String[20];

    /* Init System, IP clock and multi-function I/O.
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary. */
    SYS_Init();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    /* Configure SPI1 as a master, MSB first, 8-bit transaction, SPI Mode-0 timing, clock is 6MHz */
    SPI_Open(SPI1, SPI_MASTER, SPI_MODE_0, 8, 6000000);

    /* Enable the automatic hardware slave select function. Select the SS0 pin and configure as low-active. */
    SPI_EnableAutoSS(SPI1, SPI_SS, SPI_SS_ACTIVE_LOW);

    printf("\n+---------------------------------------------------------------------+\n");
    printf("|            M051 Series SPI Flash without FIFO Mode Sample           |\n");
    printf("+---------------------------------------------------------------------+\n");
    printf("\n");
    printf("\nThis sample code demonstrates how to access a Winbond 25x16 SPI flash without FIFO buffers.\n");
    printf("The whole SPI flash will be erased. Afterward this sample code will write, read and compare %d-page data.\n", TEST_PAGE_NUM);
    printf("\nThe duration of read operation and write operation will be shown on LCD.\n");

    /* Initial LCD panel. SPI clock and interface is configured in this function. */
    LCD_Init();
    /* Clear LCD screen. Do this before turn back light on */
    LCD_ClearScreen();
    /* Enable LCD back light */
    LCD_EnableBackLight();
    /* Show messages on LCD */
    LCD_Print(0, " SPI flash test");
    LCD_Print(1, "  without FIFO");

    /* Wait ready */
    SpiFlash_WaitReady(SPI1);

    if((u32ID = SpiFlash_ReadMidDid(SPI1)) != 0xEF14)
    {
        printf("Wrong ID, 0x%x\n", u32ID);
        while(1);
    }
    else
    {
        printf("Flash found: W25x16 ...\n");
        LCD_Print(2, "Flash W25x16");
    }

    printf("Erase chip ...");
    LCD_Print(3, "Erase chip ...");

    /* Erase SPI flash */
    SpiFlash_ChipErase(SPI1);

    /* Wait ready */
    SpiFlash_WaitReady(SPI1);

    printf("[OK]\n");

    /* init source data buffer */
    for(u32ByteCount = 0; u32ByteCount < BYTE_PER_PAGE; u32ByteCount++)
    {
        SrcArray[u32ByteCount] = u32ByteCount;
    }

    printf("Start to write data to Flash ...");
    LCD_Print(3, "Write SPI flash");

    g_u32SystickCount = 0;

    /* Configure SysTick */
    /* 1 milli-second per tick */
    SysTick->LOAD = 1000 * CyclesPerUs; /* 1000us */
    /* Clear SysTick current value register and system tick counter flag */
    SysTick->VAL  = (0x00);
    /* Core clock used for SysTick timer; enable system tick interrupt; start counting. */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Program SPI flash */
    u32FlashAddress = 0;
    for(u32PageNumber = 0; u32PageNumber < TEST_PAGE_NUM; u32PageNumber++)
    {
        /* page program */
        SpiFlash_PageProgram(SPI1, u32FlashAddress, SrcArray, BYTE_PER_PAGE);
        SpiFlash_WaitReady(SPI1);
        u32FlashAddress += 0x100;
    }

    /* Log the duration of write operation */
    u32Duration_W = g_u32SystickCount;
    /* Stop SysTick timer */
    SysTick->CTRL = 0;

    printf("[OK]\n");

    /* clear destination data buffer */
    for(u32ByteCount = 0; u32ByteCount < BYTE_PER_PAGE; u32ByteCount++)
    {
        DestArray[u32ByteCount] = 0;
    }

    printf("Read & Compare ...");
    LCD_Print(3, "Read & compare ");

    g_u32SystickCount = 0;
    /* Core clock used for SysTick timer; enable system tick interrupt; start counting. */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Read SPI flash */
    u32FlashAddress = 0;
    for(u32PageNumber = 0; u32PageNumber < TEST_PAGE_NUM; u32PageNumber++)
    {
        /* page read */
        SpiFlash_ReadData(SPI1, u32FlashAddress, DestArray, BYTE_PER_PAGE);
        u32FlashAddress += 0x100;

        for(u32ByteCount = 0; u32ByteCount < BYTE_PER_PAGE; u32ByteCount++)
        {
            if(DestArray[u32ByteCount] != SrcArray[u32ByteCount])
                u32Error ++;
        }
    }

    /* Log the duration of read operation */
    u32Duration_R = g_u32SystickCount;
    /* Stop SysTick timer */
    SysTick->CTRL = 0;

    if(u32Error == 0)
    {
        printf("[OK]\n");
        sprintf(au8String, "R/W: %d/%d ms", u32Duration_R, u32Duration_W);
        LCD_Print(3, au8String);
    }
    else
    {
        printf("[FAIL]\n");
        LCD_Print(3, "[FAIL]         ");
    }

    /* Reset SPI1 and disable SPI1 peripheral clock */
    SPI_Close(SPI1);

    while(1);
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set HCLK source form HXT and HCLK source divide 1  */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_CLKDIV_HCLK(1));

    /* Enable external 12MHz XTAL */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Select HXT as the clock source of UART0 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /* Select HXT as the clock source of SPI1 */
    CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL1_SPI1_S_HCLK, MODULE_NoMsk);

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    /* Enable SPI1 peripheral clock */
    CLK_EnableModuleClock(SPI1_MODULE);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;

    /* Set multi function pin for SPI1 */
    SYS->P0_MFP = SYS_MFP_P04_SPISS1 | SYS_MFP_P05_MOSI_1 | SYS_MFP_P06_MISO_1 | SYS_MFP_P07_SPICLK1;

    /* Lock protected registers */
    SYS_LockReg();
}

void SysTick_Handler(void)
{
    g_u32SystickCount++;
    /* Clear SysTick current value register and system tick counter flag */
    SysTick->VAL  = (0x00);
}


/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/


