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
* File Name    : r_cg_port.h
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MPG
* Tool-Chain   : gccrl78
* Description  : This file implements device driver for Port module.
* Creation Date: 7/20/2017
***********************************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Port mode registers (PMn) 
*/
/* Pn0 pin I/O mode selection (PMn0) */
#define _00_PMn0_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _01_PMn0_MODE_INPUT               (0x01U) /* input mode (output buffer off) */
/* Pn1 pin I/O mode selection (PMn1) */
#define _00_PMn1_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _02_PMn1_MODE_INPUT               (0x02U) /* input mode (output buffer off) */
/* Pn2 pin I/O mode selection (PMn2) */
#define _00_PMn2_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _04_PMn2_MODE_INPUT               (0x04U) /* input mode (output buffer off) */
/* Pn3 pin I/O mode selection (PMn3) */
#define _00_PMn3_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _08_PMn3_MODE_INPUT               (0x08U) /* input mode (output buffer off) */
/* Pn4 pin I/O mode selection (PMn4) */
#define _00_PMn4_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _10_PMn4_MODE_INPUT               (0x10U) /* input mode (output buffer off) */
/* Pn5 pin I/O mode selection (PMn5) */
#define _00_PMn5_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _20_PMn5_MODE_INPUT               (0x20U) /* input mode (output buffer off) */
/* Pn6 pin I/O mode selection (PMn6) */
#define _00_PMn6_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _40_PMn6_MODE_INPUT               (0x40U) /* input mode (output buffer off) */
/* Pn7 pin I/O mode selection (PMn7) */
#define _00_PMn7_MODE_OUTPUT              (0x00U) /* output mode (output buffer on) */
#define _80_PMn7_MODE_INPUT               (0x80U) /* input mode (output buffer off) */

/*
    Port mode registers (Pn) 
*/
/* Pn0 pin I/O mode selection (Pn0) */
#define _00_Pn0_OUTPUT_0                  (0x00U) /* Pn0 output 0 */
#define _01_Pn0_OUTPUT_1                  (0x01U) /* Pn0 output 1 */
/* Pn1 pin I/O mode selection (Pn1) */
#define _00_Pn1_OUTPUT_0                  (0x00U) /* Pn1 output 0 */
#define _02_Pn1_OUTPUT_1                  (0x02U) /* Pn1 output 1 */
/* Pn2 pin I/O mode selection (Pn2) */
#define _00_Pn2_OUTPUT_0                  (0x00U) /* Pn2 output 0 */
#define _04_Pn2_OUTPUT_1                  (0x04U) /* Pn2 output 1 */
/* Pn3 pin I/O mode selection (Pn3) */
#define _00_Pn3_OUTPUT_0                  (0x00U) /* Pn3 output 0 */
#define _08_Pn3_OUTPUT_1                  (0x08U) /* Pn3 output 1 */
/* Pn4 pin I/O mode selection (Pn4) */
#define _00_Pn4_OUTPUT_0                  (0x00U) /* Pn4 output 0 */
#define _10_Pn4_OUTPUT_1                  (0x10U) /* Pn4 output 1 */
/* Pn5 pin I/O mode selection (Pn5) */
#define _00_Pn5_OUTPUT_0                  (0x00U) /* Pn5 output 0 */
#define _20_Pn5_OUTPUT_1                  (0x20U) /* Pn5 output 1 */
/* Pn6 pin I/O mode selection (Pn6) */
#define _00_Pn6_OUTPUT_0                  (0x00U) /* Pn6 output 0 */
#define _40_Pn6_OUTPUT_1                  (0x40U) /* Pn6 output 1 */
/* Pn7 pin I/O mode selection (Pn7) */
#define _00_Pn7_OUTPUT_0                  (0x00U) /* Pn7 output 0 */
#define _80_Pn7_OUTPUT_1                  (0x80U) /* Pn7 output 1 */

/*
    Pull-up resistor option registers (PUn) 
*/
/* Pn0 pin on-chip pull-up resistor selection (PUn0) */
#define _00_PUn0_PULLUP_OFF               (0x00U) /* Pn0 pull-up resistor not connected */
#define _01_PUn0_PULLUP_ON                (0x01U) /* Pn0 pull-up resistor connected */
/* Pn1 pin on-chip pull-up resistor selection (PUn1) */
#define _00_PUn1_PULLUP_OFF               (0x00U) /* Pn1 pull-up resistor not connected */
#define _02_PUn1_PULLUP_ON                (0x02U) /* Pn1 pull-up resistor connected */
/* Pn2 pin on-chip pull-up resistor selection (PUn2) */
#define _00_PUn2_PULLUP_OFF               (0x00U) /* Pn2 pull-up resistor not connected */
#define _04_PUn2_PULLUP_ON                (0x04U) /* Pn2 pull-up resistor connected */
/* Pn3 pin on-chip pull-up resistor selection (PUn3) */
#define _00_PUn3_PULLUP_OFF               (0x00U) /* Pn3 pull-up resistor not connected */
#define _08_PUn3_PULLUP_ON                (0x08U) /* Pn3 pull-up resistor connected */
/* Pn4 pin on-chip pull-up resistor selection (PUn4) */
#define _00_PUn4_PULLUP_OFF               (0x00U) /* Pn4 pull-up resistor not connected */
#define _10_PUn4_PULLUP_ON                (0x10U) /* Pn4 pull-up resistor connected */
/* Pn5 pin on-chip pull-up resistor selection (PUn5) */
#define _00_PUn5_PULLUP_OFF               (0x00U) /* Pn5 pull-up resistor not connected */
#define _20_PUn5_PULLUP_ON                (0x20U) /* Pn5 pull-up resistor connected */
/* Pn6 pin on-chip pull-up resistor selection (PUn6) */
#define _00_PUn6_PULLUP_OFF               (0x00U) /* Pn6 pull-up resistor not connected */
#define _40_PUn6_PULLUP_ON                (0x40U) /* Pn6 pull-up resistor connected */
/* Pn7 pin on-chip pull-up resistor selection (PUn7) */
#define _00_PUn7_PULLUP_OFF               (0x00U) /* Pn7 pull-up resistor not connected */
#define _80_PUn7_PULLUP_ON                (0x80U) /* Pn7 pull-up resistor connected */

/*
    Port input mode registers (PIMn) 
*/
/* Pn0 pin input buffer selection (PIMn0) */
#define _00_PIMn0_TTL_OFF                 (0x00U) /* Pn0 normal input buffer */
#define _01_PIMn0_TTL_ON                  (0x01U) /* Pn0 TTL input buffer */
/* Pn1 pin input buffer selection (PIMn1) */
#define _00_PIMn1_TTL_OFF                 (0x00U) /* Pn1 normal input buffer */
#define _02_PIMn1_TTL_ON                  (0x02U) /* Pn1 TTL input buffer */
/* Pn4 pin input buffer selection (PIMn4) */
#define _00_PIMn4_TTL_OFF                 (0x00U) /* Pn4 normal input buffer */
#define _10_PIMn4_TTL_ON                  (0x10U) /* Pn4 TTL input buffer */
/* Pn5 pin input buffer selection (PIMn5) */
#define _00_PIMn5_TTL_OFF                 (0x00U) /* Pn5 normal input buffer */
#define _20_PIMn5_TTL_ON                  (0x20U) /* Pn5 TTL input buffer */
/* Pn6 pin input buffer selection (PIMn6) */
#define _00_PIMn6_TTL_OFF                 (0x00U) /* Pn6 normal input buffer */
#define _40_PIMn6_TTL_ON                  (0x40U) /* Pn6 TTL input buffer */

/*
    Port output mode registers (POMn) 
*/
/* Pn0 pin output mode selection (POMn0) */
#define _00_POMn0_NCH_OFF                 (0x00U) /* Pn0 normal output mode */
#define _01_POMn0_NCH_ON                  (0x01U) /* Pn0 N-ch open-drain output (VDD tolerance) mode */
/* Pn1 pin output mode selection (POMn1) */
#define _00_POMn1_NCH_OFF                 (0x00U) /* Pn1 normal output mode */
#define _02_POMn1_NCH_ON                  (0x02U) /* Pn1 N-ch open-drain output (VDD tolerance) mode */
/* Pn2 pin output mode selection (POMn2) */
#define _00_POMn2_NCH_OFF                 (0x00U) /* Pn2 normal output mode */
#define _04_POMn2_NCH_ON                  (0x04U) /* Pn2 N-ch open-drain output (VDD tolerance) mode */
/* Pn3 pin output mode selection (POMn3) */
#define _00_POMn3_NCH_OFF                 (0x00U) /* Pn3 normal output mode */
#define _08_POMn3_NCH_ON                  (0x08U) /* Pn3 N-ch open-drain output (VDD tolerance) mode */
/* Pn4 pin output mode selection (POMn4) */
#define _00_POMn4_NCH_OFF                 (0x00U) /* Pn4 normal output mode */
#define _10_POMn4_NCH_ON                  (0x10U) /* Pn4 N-ch open-drain output (VDD tolerance) mode */
/* Pn5 pin output mode selection (POMn5) */
#define _00_POMn5_NCH_OFF                 (0x00U) /* Pn5 normal output mode */
#define _20_POMn5_NCH_ON                  (0x20U) /* Pn5 N-ch open-drain output (VDD tolerance) mode */
/* Pn6 pin output mode selection (POMn6) */
#define _00_POMn6_NCH_OFF                 (0x00U) /* Pn6 normal output mode */
#define _40_POMn6_NCH_ON                  (0x40U) /* Pn6 N-ch open-drain output (VDD tolerance) mode */
/* Pn7 pin output mode selection (POMn7) */
#define _00_POMn7_NCH_OFF                 (0x00U) /* Pn7 normal output mode */
#define _80_POMn7_NCH_ON                  (0x80U) /* Pn7 N-ch open-drain output (VDD tolerance) mode */

/*
    Port mode control registers (PMCn) 
*/
/* Pn0 pin digital I/O/analog input selection (PMCn0) */
#define _00_PMCn0_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _01_PMCn0_DI_ON                   (0x01U) /* analog input */
/* Pn1 pin digital I/O/analog input selection (PMCn1) */
#define _00_PMCn1_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _02_PMCn1_DI_ON                   (0x02U) /* analog input */
/* Pn2 pin digital I/O/analog input selection (PMCn2) */
#define _00_PMCn2_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _04_PMCn2_DI_ON                   (0x04U) /* analog input */
/* Pn3 pin digital I/O/analog input selection (PMCn3) */
#define _00_PMCn3_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _08_PMCn3_DI_ON                   (0x08U) /* analog input */
/* Pn4 pin digital I/O/analog input selection (PMCn4) */
#define _00_PMCn4_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _10_PMCn4_DI_ON                   (0x10U) /* analog input */
/* Pn5 pin digital I/O/analog input selection (PMCn5) */
#define _00_PMCn5_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _20_PMCn5_DI_ON                   (0x20U) /* analog input */
/* Pn6 pin digital I/O/analog input selection (PMCn6) */
#define _00_PMCn6_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _40_PMCn6_DI_ON                   (0x40U) /* analog input */
/* Pn7 pin digital I/O/analog input selection (PMCn7) */
#define _00_PMCn7_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _80_PMCn7_DI_ON                   (0x80U) /* analog input */

/*
    LCD port function registers (PFSEG0) 
*/
/* Port (other than segment output)/segment outputs specification of P50 pins (PFSEG04) */
#define _00_PFSEG04_PORT                  (0x00U) /* used the P50 pin as port */
#define _10_PFSEG04_SEG                   (0x10U) /* used the P50 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P51 pins (PFSEG05) */
#define _00_PFSEG05_PORT                  (0x00U) /* used the P51 pin as port */
#define _20_PFSEG05_SEG                   (0x20U) /* used the P51 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P52 pins (PFSEG06) */
#define _00_PFSEG06_PORT                  (0x00U) /* used the P52 pin as port */
#define _40_PFSEG06_SEG                   (0x40U) /* used the P52 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P53 pins (PFSEG07) */
#define _00_PFSEG07_PORT                  (0x00U) /* used the P53 pin as port */
#define _80_PFSEG07_SEG                   (0x80U) /* used the P53 pin as segment output */

/*
    LCD port function registers (PFSEG1) 
*/
/* Port (other than segment output)/segment outputs specification of P54 pins (PFSEG08) */
#define _00_PFSEG08_PORT                  (0x00U) /* used the P54 pin as port */
#define _01_PFSEG08_SEG                   (0x01U) /* used the P54 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P55 pins (PFSEG09) */
#define _00_PFSEG09_PORT                  (0x00U) /* used the P55 pin as port */
#define _02_PFSEG09_SEG                   (0x02U) /* used the P55 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P56 pins (PFSEG10) */
#define _00_PFSEG10_PORT                  (0x00U) /* used the P56 pin as port */
#define _04_PFSEG10_SEG                   (0x04U) /* used the P56 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P57 pins (PFSEG11) */
#define _00_PFSEG11_PORT                  (0x00U) /* used the P57 pin as port */
#define _08_PFSEG11_SEG                   (0x08U) /* used the P57 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P70 pins (PFSEG12) */
#define _00_PFSEG12_PORT                  (0x00U) /* used the P70 pin as port */
#define _10_PFSEG12_SEG                   (0x10U) /* used the P70 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P71 pins (PFSEG13) */
#define _00_PFSEG13_PORT                  (0x00U) /* used the P71 pin as port */
#define _20_PFSEG13_SEG                   (0x20U) /* used the P71 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P72 pins (PFSEG14) */
#define _00_PFSEG14_PORT                  (0x00U) /* used the P72 pin as port */
#define _40_PFSEG14_SEG                   (0x40U) /* used the P72 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P73 pins (PFSEG15) */
#define _00_PFSEG15_PORT                  (0x00U) /* used the P73 pin as port */
#define _80_PFSEG15_SEG                   (0x80U) /* used the P73 pin as segment output */

/*
    LCD port function registers (PFSEG2) 
*/
/* Port (other than segment output)/segment outputs specification of P74 pins (PFSEG16) */
#define _00_PFSEG16_PORT                  (0x00U) /* used the P74 pin as port */
#define _01_PFSEG16_SEG                   (0x01U) /* used the P74 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P75 pins (PFSEG17) */
#define _00_PFSEG17_PORT                  (0x00U) /* used the P75 pin as port */
#define _02_PFSEG17_SEG                   (0x02U) /* used the P75 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P76 pins (PFSEG18) */
#define _00_PFSEG18_PORT                  (0x00U) /* used the P76 pin as port */
#define _04_PFSEG18_SEG                   (0x04U) /* used the P76 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P77 pins (PFSEG19) */
#define _00_PFSEG19_PORT                  (0x00U) /* used the P77 pin as port */
#define _08_PFSEG19_SEG                   (0x08U) /* used the P77 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P30 pins (PFSEG20) */
#define _00_PFSEG20_PORT                  (0x00U) /* used the P30 pin as port */
#define _10_PFSEG20_SEG                   (0x10U) /* used the P30 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P31 pins (PFSEG21) */
#define _00_PFSEG21_PORT                  (0x00U) /* used the P31 pin as port */
#define _20_PFSEG21_SEG                   (0x20U) /* used the P31 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P32 pins (PFSEG22) */
#define _00_PFSEG22_PORT                  (0x00U) /* used the P32 pin as port */
#define _40_PFSEG22_SEG                   (0x40U) /* used the P32 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P33 pins (PFSEG23) */
#define _00_PFSEG23_PORT                  (0x00U) /* used the P33 pin as port */
#define _80_PFSEG23_SEG                   (0x80U) /* used the P33 pin as segment output */

/*
    LCD port function registers (PFSEG3) 
*/
/* Port (other than segment output)/segment outputs specification of P34 pins (PFSEG24) */
#define _00_PFSEG24_PORT                  (0x00U) /* used the P34 pin as port */
#define _01_PFSEG24_SEG                   (0x01U) /* used the P34 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P35 pins (PFSEG25) */
#define _00_PFSEG25_PORT                  (0x00U) /* used the P35 pin as port */
#define _02_PFSEG25_SEG                   (0x02U) /* used the P35 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P36 pins (PFSEG26) */
#define _00_PFSEG26_PORT                  (0x00U) /* used the P36 pin as port */
#define _04_PFSEG26_SEG                   (0x04U) /* used the P36 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P37 pins (PFSEG27) */
#define _00_PFSEG27_PORT                  (0x00U) /* used the P37 pin as port */
#define _08_PFSEG27_SEG                   (0x08U) /* used the P37 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P13 pins (PFSEG28) */
#define _00_PFSEG28_PORT                  (0x00U) /* used the P13 pin as port */
#define _10_PFSEG28_SEG                   (0x10U) /* used the P13 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P14 pins (PFSEG29) */
#define _00_PFSEG29_PORT                  (0x00U) /* used the P14 pin as port */
#define _20_PFSEG29_SEG                   (0x20U) /* used the P14 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P15 pins (PFSEG30) */
#define _00_PFSEG30_PORT                  (0x00U) /* used the P15 pin as port */
#define _40_PFSEG30_SEG                   (0x40U) /* used the P15 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P16 pins (PFSEG31) */
#define _00_PFSEG31_PORT                  (0x00U) /* used the P16 pin as port */
#define _80_PFSEG31_SEG                   (0x80U) /* used the P16 pin as segment output */

/*
    LCD port function registers (PFSEG4) 
*/
/* Port (other than segment output)/segment outputs specification of P17 pins (PFSEG32) */
#define _00_PFSEG32_PORT                  (0x00U) /* used the P17 pin as port */
#define _01_PFSEG32_SEG                   (0x01U) /* used the P17 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P00 pins (PFSEG33) */
#define _00_PFSEG33_PORT                  (0x00U) /* used the P00 pin as port */
#define _02_PFSEG33_SEG                   (0x02U) /* used the P00 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P01 pins (PFSEG34) */
#define _00_PFSEG34_PORT                  (0x00U) /* used the P01 pin as port */
#define _04_PFSEG34_SEG                   (0x04U) /* used the P01 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P02 pins (PFSEG35) */
#define _00_PFSEG35_PORT                  (0x00U) /* used the P02 pin as port */
#define _08_PFSEG35_SEG                   (0x08U) /* used the P02 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P03 pins (PFSEG36) */
#define _00_PFSEG36_PORT                  (0x00U) /* used the P03 pin as port */
#define _10_PFSEG36_SEG                   (0x10U) /* used the P03 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P04 pins (PFSEG37) */
#define _00_PFSEG37_PORT                  (0x00U) /* used the P04 pin as port */
#define _20_PFSEG37_SEG                   (0x20U) /* used the P04 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P05 pins (PFSEG38) */
#define _00_PFSEG38_PORT                  (0x00U) /* used the P05 pin as port */
#define _40_PFSEG38_SEG                   (0x40U) /* used the P05 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P06 pins (PFSEG39) */
#define _00_PFSEG39_PORT                  (0x00U) /* used the P06 pin as port */
#define _80_PFSEG39_SEG                   (0x80U) /* used the P06 pin as segment output */

/*
    LCD port function registers (PFSEG5) 
*/
/* Port (other than segment output)/segment outputs specification of P07 pins (PFSEG40) */
#define _00_PFSEG40_PORT                  (0x00U) /* used the P07 pin as port */
#define _01_PFSEG40_SEG                   (0x01U) /* used the P07 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P12 pins (PFSEG41) */
#define _00_PFSEG41_PORT                  (0x00U) /* used the P12 pin as port */
#define _02_PFSEG41_SEG                   (0x02U) /* used the P12 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P11 pins (PFSEG42) */
#define _00_PFSEG42_PORT                  (0x00U) /* used the P11 pin as port */
#define _04_PFSEG42_SEG                   (0x04U) /* used the P11 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P81 pins (PFSEG43) */
#define _00_PFSEG43_PORT                  (0x00U) /* used the P81 pin as port */
#define _08_PFSEG43_SEG                   (0x08U) /* used the P81 pin as segment output */
/* Port (other than segment output)/segment outputs specification of P80 pins (PFSEG44) */
#define _00_PFSEG44_PORT                  (0x00U) /* used the P80 pin as port */
#define _10_PFSEG44_SEG                   (0x10U) /* used the P80 pin as segment output */

/*
    Port mode control registers (PMC4) 
*/
/* P43 pin digital I/O/analog input selection (PMC43) */
#define _00_PMC43_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _08_PMC43_DI_ON                   (0x08U) /* analog input */
/* P44 pin digital I/O/analog input selection (PMC44) */
#define _00_PMC44_NOT_USE                 (0x00U) /* digital I/O (alternate function other than analog input) */
#define _10_PMC44_DI_ON                   (0x10U) /* analog input */

/*
    LCD input switch control register (ISCLCD) 
*/
/* Control of schmitt trigger buffer of VL3/P125 pin (ISCVL3) */
#define _00_VL3_BUFFER_INVALID            (0x00U) /* makes digital input invalid (used as VL3) */
#define _02_VL3_BUFFER_VALID              (0x02U) /* makes digital input valid */
/* Control of schmitt trigger buffer of CAPL/P126 and CAPH/P127 pins (ISCCAP) */
#define _00_CAPLH_BUFFER_INVALID          (0x00U) /* makes digital input invalid (used as CAPL and CAPH) */
#define _01_CAPLH_BUFFER_VALID            (0x01U) /* makes digital input valid */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _01_PM1_DEFAULT_VALUE             (0x01U) /* PM1 default value */
#define _04_PM2_DEFAULT_VALUE             (0x04U) /* PM2 default value */
#define _E0_PM4_DEFAULT_VALUE             (0xE0U) /* PM4 default value */
#define _FC_PM6_DEFAULT_VALUE             (0xFCU) /* PM6 default value */
#define _FC_PM8_DEFAULT_VALUE             (0xFCU) /* PM8 default value */
#define _04_PM10_DEFAULT_VALUE            (0x04U) /* PM10 default value */
#define _1F_PM12_DEFAULT_VALUE            (0x1FU) /* PM12 default value */
#define _F0_PM14_DEFAULT_VALUE            (0xF0U) /* PM14 default value */
#define _E2_PM15_DEFAULT_VALUE            (0xE2U) /* PM15 default value */
#define _04_PMC2_DEFAULT_VALUE            (0x04U) /* PMC2 default value */
#define _FC_PMC8_DEFAULT_VALUE            (0xFCU) /* PMC8 default value */
#define _04_PMC10_DEFAULT_VALUE           (0x04U) /* PMC10 default value */
#define _F0_PMC14_DEFAULT_VALUE           (0xF0U) /* PMC14 default value */
#define _E2_PMC15_DEFAULT_VALUE           (0xE2U) /* PMC15 default value */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_PORT_Create(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
