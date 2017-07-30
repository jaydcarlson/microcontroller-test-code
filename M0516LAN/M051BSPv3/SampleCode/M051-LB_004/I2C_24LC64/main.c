/******************************************************************************
 * @file     main.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 14/01/28 11:43a $
 * @brief    This demo access EEPROM and show message on LCD panel.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "M051Series.h"
#include "LCD_Driver.h"
#include "EEPROM_24LC64.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000


uint8_t gu8Count = 0, isPress = FALSE;
uint8_t g_u8Buf[256] = {0};

void EINT0_IRQHandler(void)
{
    /* Clear P3.2 interrupt flag */
    P3->ISRC = 1 << 2;
    gu8Count++;
    isPress = TRUE;
}


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk | CLK_PWRCON_IRC10K_EN_Msk;

    /* Waiting for 12MHz & IRC10kHz clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk | CLK_CLKSTATUS_IRC10K_STB_Msk);

    /* Switch HCLK clock source to XTAL */
    CLK->CLKSEL0 = CLK_CLKSEL0_HCLK_S_HXT;

    /* Set PLL to power down mode and PLL_STB bit in CLKSTATUS register will be cleared by hardware.*/
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;

    /* Set PLL frequency */
    CLK->PLLCON = PLLCON_SETTING;

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk);

    /* Switch HCLK clock source to PLL */
    CLK->CLKSEL0 = CLK_CLKSEL0_HCLK_S_PLL;

    /* Enable IP clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk | CLK_APBCLK_SPI0_EN_Msk |
                  CLK_APBCLK_I2C_EN_Msk;

    /* Select IP clock source */
    CLK->CLKSEL1 = CLK_CLKSEL1_UART_S_HXT;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;

    /* Set P1.4, P1.5, P1.6, P1.7 for SPI0 to driver LCD */
    SYS->P1_MFP &= ~(SYS_MFP_P14_Msk | SYS_MFP_P15_Msk | SYS_MFP_P16_Msk | SYS_MFP_P17_Msk);
    SYS->P1_MFP = SYS_MFP_P14_SPISS0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0;

    /* Configure the SDA0 & SCL0 of I2C0 pins */
    SYS->P3_MFP &= ~(SYS_MFP_P34_Msk | SYS_MFP_P35_Msk);
    SYS->P3_MFP |= SYS_MFP_P34_SDA0 | SYS_MFP_P35_SCL0;
}


void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

void GPIO_Init(void)
{
    /* Enable debounce function of P3.2 (EINT0) */
    //P3->DBEN = GPIO_DBEN_ENABLE(2);
    GPIO_ENABLE_DEBOUNCE(P3, 2);

    /* Set debounce time. it is about 6.4 ms */
    GPIO->DBNCECON = GPIO_DBCLKSRC_LIRC | GPIO_DBCLKSEL_64;

    /* Enable P3.2 to be EINT0 */
    GPIO_EnableInt(P3, 2, GPIO_INT_RISING);
    NVIC_EnableIRQ(EINT0_IRQn);
}


int32_t I2C_24LC64_AutoTest(void)
{
    int32_t i, i32Err;

    /* Programming EEPROM */
    for(i = 0; i < 256; i++)
        EEPROM_Write(i, i);

    /* Verify */
    i32Err = 0;
    for(i = 0; i < 256; i++)
    {
        if(EEPROM_Read(i) != i)
        {
            i32Err = 1;
            break;
        }
    }

    LCD_ClearScreen();
    if(i32Err)
    {
        LCD_Print(0, "I2C EEPROM");
        LCD_Print(1, "Write Fail");
        return -1;
    }
    else
    {
        LCD_Print(0, "I2C EEPROM");
        LCD_Print(1, "Verify OK!");
    }

    /* Delay for 2 seconds */
    for(i = 0; i < 20; i++)
        CLK_SysTickDelay(100000);

    EEPROM_SequentialRead(0, g_u8Buf, 256);
    /* Verify */
    i32Err = 0;
    for(i = 0; i < 256; i++)
    {
        if(g_u8Buf[i] != i)
        {
            i32Err = 1;
            break;
        }
    }

    LCD_ClearScreen();
    if(i32Err)
    {
        LCD_Print(0, "I2C EEPROM");
        LCD_Print(1, "Seq. Read Fail");
        return -1;
    }
    else
    {
        LCD_Print(0, "I2C EEPROM");
        LCD_Print(1, "Seq. Read OK!");
    }

    /* Delay for 2 seconds */
    for(i = 0; i < 20; i++)
        CLK_SysTickDelay(100000);

    for(i = 0; i < 256; i++)
        g_u8Buf[i] = i;
    for(i = 0; i < 8; i++)
        EEPROM_PageWrite(i * 32, &g_u8Buf[i * 32]);

    memset(g_u8Buf, 0, 256);

    EEPROM_SequentialRead(0, g_u8Buf, 256);
    /* Verify */
    i32Err = 0;
    for(i = 0; i < 256; i++)
    {
        if(EEPROM_Read(i) != (i & 0xFF))
        {
            i32Err = 1;
            break;
        }
    }

    LCD_ClearScreen();
    if(i32Err)
    {
        LCD_Print(0, "I2C EEPROM");
        LCD_Print(1, "Page Write Fail");
        return -1;
    }
    else
    {
        LCD_Print(0, "I2C EEPROM");
        LCD_Print(1, "Page Write OK!");
    }

    return i32Err;

}

int32_t I2C_24LC64_ManualTest(void)
{
    uint32_t i2cdata = 0, temp;
    char addr[16] = "Address:";
    char Write[16] = "Write:";
    char read[16] = "Read:";

    LCD_Print(0, "I2C with 24LC64");
    LCD_Print(1, "test read and  ");
    LCD_Print(2, "write function ");
    LCD_Print(3, "press INT button");


    temp = 0x55;
    while(1)
    {
        if(isPress)
        {
            isPress = FALSE;
            switch(gu8Count)
            {
            case 1:
                LCD_ClearScreen();
                LCD_Print(0, "Key1 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 11);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 11);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 2:
                LCD_ClearScreen();
                LCD_Print(0, "Key2 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 22);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 22);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 3:
                LCD_ClearScreen();
                LCD_Print(0, "Key3 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 33);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 33);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 4:
                LCD_ClearScreen();
                LCD_Print(0, "Key4 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 44);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 44);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 5:
                LCD_ClearScreen();
                LCD_Print(0, "Key5 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 55);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 55);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 6:
                LCD_ClearScreen();
                LCD_Print(0, "Key6 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 66);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 66);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 7:
                LCD_ClearScreen();
                LCD_Print(0, "Key7 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 77);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 77);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 8:
                LCD_ClearScreen();
                LCD_Print(0, "Key8 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 88);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 88);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                break;
            case 9:
                LCD_ClearScreen();
                LCD_Print(0, "Key9 had pressed ");
                EEPROM_Write(0x00000000 + temp, temp + 99);
                i2cdata = EEPROM_Read(0x00000000 + temp);
                sprintf(addr + 8, "%x", temp);
                sprintf(Write + 6, "%x", temp + 99);
                sprintf(read + 5, "%x", i2cdata);
                LCD_Print(1, addr);
                LCD_Print(2, Write);
                LCD_Print(3, read);
                gu8Count = 0;
                break;
            default:
                break;
            } //End Switch
        } //End if(isPress)
    } //End While

}

int main(void)
{
    int32_t i;


    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init system, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init GPIO P3.2 as EINT0 */
    GPIO_Init();

    /* Init SPI0 and LCD */
    LCD_Init();
    LCD_EnableBackLight();
    LCD_ClearScreen();


    /*
       This sample code should work with EEPROM 24LC64
       to show how to program EEPROM through I2C interface.

       The demo will program EEPROM and verify the written data.
       Finally, user may press "SW_INT" key to write and read a byte.
       And the byte will shown on LCD display
    */

    EEPROM_Init();

    /* Test EEPROM read/write automatically */
    I2C_24LC64_AutoTest();

    /* Delay for 2 seconds */
    for(i = 0; i < 20; i++)
        CLK_SysTickDelay(100000);

    /* Test EEPROM read/write by key pressing */
    I2C_24LC64_ManualTest();

}
