/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_cgc.h
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MPG
* Tool-Chain   : gccrl78
* Description  : This file implements device driver for CGC module.
* Creation Date: 7/20/2017
***********************************************************************************************************************/
#ifndef CGC_H
#define CGC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Clock operation mode control register (CMC) 
*/
/* Control of X1 clock oscillation frequency (AMPH) */
#define _00_CGC_SYSOSC_UNDER10M                   (0x00U) /* 1MHz <= fX <= 10MHz */
#define _01_CGC_SYSOSC_OVER10M                    (0x01U) /* 10MHz < fX <= 20MHz */
/* XT1 oscillator oscillation mode selection (AMPHS1,AMPHS0) */
#define _00_CGC_LOW_OSCILLATION                   (0x00U) /* low power consumption oscillation */
#define _02_CGC_NORMAL_OSCILLATION                (0x02U) /* normal oscillation */
#define _04_CGC_ULTRA_LOW_OSCILLATION             (0x04U) /* ultra-low power consumption oscillation */
/* Subsystem clock pin operation mode (EXCLKS,OSCSELS) */
#define _00_CGC_SUB_PORT                          (0x00U) /* XT1, XT2 as I/O port */
#define _10_CGC_SUB_OSC                           (0x10U) /* XT1, XT2 as crystal connection */
#define _20_CGC_SUB_PORT1                         (0x20U) /* XT1, XT2 as I/O port */
#define _30_CGC_SUB_EXT                           (0x30U) /* XT1 as I/O port, XT2 as external clock input */
#define _30_CGC_SUB_PIN                           (0x30U) /* XT1, XT2 pin setting */
/* High-speed system clock pin operation mode (EXCLK,OSCSEL) */
#define _00_CGC_HISYS_PORT                        (0x00U) /* X1, X2 as I/O port */
#define _40_CGC_HISYS_OSC                         (0x40U) /* X1, X2 as crystal/ceramic resonator connection */
#define _80_CGC_HISYS_PORT1                       (0x80U) /* X1, X2 as I/O port */
#define _C0_CGC_HISYS_EXT                         (0xC0U) /* X1 as I/O port, X2 as external clock input */
#define _C0_CGC_HISYS_PIN                         (0xC0U) /* X1, X2 pin setting */

/*
    System clock control register (CKC) 
*/
/* Main system clock (fMAIN) operation control (MCM0) */
#define _00_CGC_MAINCLK_SELFOCO                   (0x00U) /* selects fIH as the main system clock (fMAIN) */
#define _10_CGC_MAINCLK_SELHISYS                  (0x10U) /* selects fMX as the main system clock (fMAIN) */
/* Status of Main system clock (fMAIN) (MCS) */
#define _00_CGC_MAINCLK_FOCO                      (0x00U) /* high-speed on-chip oscillator clock (fIH) */
#define _20_CGC_MAINCLK_HISYS                     (0x20U) /* high-speed system clock (fMX) */
/* Selection of CPU/peripheral hardware clock (fCLK) (CSS) */
#define _00_CGC_MAINCLK_SELECTED                  (0x00U) /* main system clock (fMAIN) */
#define _40_CGC_MAINCLK_FSUB                      (0x40U) /* subsystem clock (fSUB) */
/* Status of CPU/peripheral hardware clock (fCLK) (CLS) */
#define _00_CGC_MAINCLK_STATUS                    (0x00U) /* main system clock (fMAIN) */
#define _80_CGC_MAINCLK_STATUS                    (0x80U) /* subsystem clock (fSUB) */

/*
    Clock operation status control register (CSC) 
*/
/* Default value (bit 7, bit 6) */
#define _C0_CGC_DEFAULT_VALUE                     (0xC0U) /* CSC default value */
/* High-speed on-chip oscillator clock operation control (HIOSTOP) */
#define _00_CGC_HIO_OPER                          (0x00U) /* high-speed on-chip oscillator operating */
#define _01_CGC_HIO_STOP                          (0x01U) /* high-speed on-chip oscillator stopped */
/* Subsystem clock operation control (XTSTOP) */
#define _00_CGC_FSUB_OPER                         (0x00U) /* XT1 oscillator/external clock operating */
#define _40_CGC_FSUB_STOP                         (0x40U) /* XT1 oscillator/external clock stopped */
/* High-speed system clock operation control (MSTOP) */
#define _00_CGC_HISYS_OPER                        (0x00U) /* X1 oscillator/external clock operating */
#define _80_CGC_HISYS_STOP                        (0x80U) /* X1 oscillator/external clock stopped */

/*
    Oscillation stabilization time counter status register (OSTC) 
*/
/* Oscillation stabilization time status (MOST8,MOST9,MOST10,MOST11,MOST13,MOST15,MOST17,MOST18) */
#define _00_CGC_OSCSTAB_STA0                      (0x00U) /* 2^8/fX max. */
#define _80_CGC_OSCSTAB_STA8                      (0x80U) /* 2^8/fX */
#define _C0_CGC_OSCSTAB_STA9                      (0xC0U) /* 2^9/fX */
#define _E0_CGC_OSCSTAB_STA10                     (0xE0U) /* 2^10/fX */
#define _F0_CGC_OSCSTAB_STA11                     (0xF0U) /* 2^11/fX */
#define _F8_CGC_OSCSTAB_STA13                     (0xF8U) /* 2^13/fX */
#define _FC_CGC_OSCSTAB_STA15                     (0xFCU) /* 2^15/fX */
#define _FE_CGC_OSCSTAB_STA17                     (0xFEU) /* 2^17/fX */
#define _FF_CGC_OSCSTAB_STA18                     (0xFFU) /* 2^18/fX */

/*
    Oscillation stabilization time select register (OSTS) 
*/
/* Oscillation stabilization time selection (OSTS2,OSTS1,OSTS0) */
#define _00_CGC_OSCSTAB_SEL8                      (0x00U) /* 2^8/fX */
#define _01_CGC_OSCSTAB_SEL9                      (0x01U) /* 2^9/fX */
#define _02_CGC_OSCSTAB_SEL10                     (0x02U) /* 2^10/fX */
#define _03_CGC_OSCSTAB_SEL11                     (0x03U) /* 2^11/fX */
#define _04_CGC_OSCSTAB_SEL13                     (0x04U) /* 2^13/fX */
#define _05_CGC_OSCSTAB_SEL15                     (0x05U) /* 2^15/fX */
#define _06_CGC_OSCSTAB_SEL17                     (0x06U) /* 2^17/fX */
#define _07_CGC_OSCSTAB_SEL18                     (0x07U) /* 2^18/fX */

/*
    Subsystem clock supply mode control register (OSMC) 
*/
/* Setting in STOP mode or HALT mode while subsystem clock is selected as CPU clock (RTCLPC) */
#define _00_CGC_CLK_ENABLE                        (0x00U) /* enables supply of subsystem clock to peripheral functions */
#define _80_CGC_CLK_STOP                          (0x80U) /* stops supply of subsystem clock to peripheral functions */
/* Selection of operation clock for real-time clock 2,
12-bit interval timer, 8-bit interval timer, and LCD controller/driver (WUTMMCK0) */
#define _00_CGC_RTC_IT_CLK_SUBSYSTEM_CLK          (0x00U) /* subsystem clock */
#define _10_CGC_RTC_IT_CLK_FIL                    (0x10U) /* low-speed on-chip oscillator clock */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define CGC_SUBWAITTIME                           (360U)  /* change the waiting time according to the system */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    HIOCLK,
    SYSX1CLK,
    SYSEXTCLK,
    SUBXT1CLK,
    SUBEXTCLK
} clock_mode_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CGC_Create(void);
void R_CGC_Get_ResetSource(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
