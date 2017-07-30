/**************************************************************************//**
 * @file     lcd_driver.h
 * @version  V3.0
 * $Revision: 3 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series LCD Module library header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

extern void LCD_ClearScreen(void);
extern void LCD_Print(uint8_t line, char *str);
extern void LCD_EnableBackLight(void);
extern void LCD_DisableBackLight(void);
extern void LCD_Init(void);
#endif /* __LCD_DRIVER_H__ */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
