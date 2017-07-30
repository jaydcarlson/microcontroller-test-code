/**************************************************************************//**
 * @file     LCD_Driver.c
 * @version  V3.0
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series LCD Module library source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "M051Series.h"
#include "LCD_Driver.h"

extern  const char Ascii[];

/**
  * @brief  For SPI write method
  * @param  u32Data    Data will be written by SPI0
  * @return None
  */
static __INLINE void SpiWrite(uint32_t u32Data)
{
    SPI0->TX0 = u32Data;
    SPI0->CNTRL |= SPI_CNTRL_GO_BUSY_Msk;
    while((SPI0->CNTRL & SPI_CNTRL_GO_BUSY_Msk));
    SPI0->CNTRL |= SPI_CNTRL_IF_Msk;
}

/**
  * @brief  Use SPI0 interface to configure LCD module
  * @param  None
  * @return None
  */
void LCD_Init(void)
{
    /* Use SPI0 for LCD */
    SYS->P1_MFP &= ~(SYS_MFP_P17_Msk | SYS_MFP_P16_Msk | SYS_MFP_P15_Msk | SYS_MFP_P14_Msk);
    SYS->P1_MFP |= SYS_MFP_P17_SPICLK0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P14_SPISS0;

    CLK->APBCLK |= CLK_APBCLK_SPI0_EN_Msk;

    SYS->IPRSTC2 |= SYS_IPRSTC2_SPI0_RST_Msk;
    SYS->IPRSTC2 &= (~SYS_IPRSTC2_SPI0_RST_Msk);

    /* Initial SPI0 data format and SPI0 clock */
    SPI0->CNTRL = SPI_CNTRL_CLKP_Msk | SPI_CNTRL_TX_NEG_Msk | (9 << SPI_CNTRL_TX_BIT_LEN_Pos);
    SPI0->DIVIDER = ((12000000 / 2000000) >> 1) - 1;

    /* Enable the automatic hardware slave select function. Select the SS pin and configure as low-active. */
    SPI0->SSR = SPI_SSR_AUTOSS_Msk | SPI_SSR_SSR_Msk ;

    // Set BR
    SpiWrite(0xEB);

    // Set PM
    SpiWrite(0x81);
    SpiWrite(0xA0);

    SpiWrite(0xC0);

    // Set Display Enable
    SpiWrite(0xAF);
}

/**
  * @brief Configure start address of LCD
  * @param PA PA value for LCD
  * @param CA CA value for LCD
  * @return None
  */
static void SetPACA(uint8_t PA, uint8_t CA)
{
    // Set PA
    SpiWrite(0xB0 | PA);

    // Set CA MSB
    SpiWrite(0x10 | (CA >> 4) & 0xF);

    // Set CA LSB
    SpiWrite(0x00 | (CA & 0xF));
}

/**
  * @brief Show a char on LCD
  * @param x X position
  * @param y Y position
  * @param ascii_word    ASCII character that will be shown on LCD
  * @return None
  */
static void ShowChar(uint8_t x, uint8_t y, uint8_t ascii_word)
{
    int i = 0, k = 0;
    unsigned char temp;
    k = (ascii_word - 32) * 16;

    for(i = 0; i < 8; i++)
    {
        SetPACA((x * 2), (129 - (y * 8) - i));
        temp = Ascii[k + i];
        SpiWrite(0x100 | temp);
    }

    for(i = 0; i < 8; i++)
    {
        SetPACA((x * 2) + 1, (129 - (y * 8) - i));
        temp = Ascii[k + i + 8];
        SpiWrite(0x100 | temp);
    }
}

/**
  * @brief Enable back-light of LCD
  * @param None
  * @return None
  */
void LCD_EnableBackLight(void)
{
    GPIO_SetMode(P1, 0x02, GPIO_PMD_OUTPUT);
    P11 = 0;
}

/**
  * @brief Disable back-light of LCD
  * @param None
  * @return None
  */
void LCD_DisableBackLight(void)
{
    GPIO_SetMode(P1, 0x02, GPIO_PMD_OUTPUT);
    P11 = 1;
}

/**
  * @brief Show a string on specific line
  * @param line Line number
  * @param str string
  * @return None
  */
void LCD_Print(uint8_t line, char *str)
{
    int i = 0;
    do
    {
        ShowChar(line, i, *str++);
        i++;
        if(i > 15)
            break;
    }
    while(*str != '\0');
}

/**
  * @brief Clear screen to background color
  * @param None
  * @return None
  */
void LCD_ClearScreen(void)
{
    int i = 0;
    /*CLEAR ALL PANEL*/
    SetPACA(0x0, 0x0);

    for(i = 0; i < 132 * 8; i++)
    {
        SpiWrite(0x100);
    }
    SpiWrite(0x10f);
}


