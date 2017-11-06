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
* File Name    : r_cg_port.c
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MPG
* Tool-Chain   : gccrl78
* Description  : This file implements device driver for Port module.
* Creation Date: 7/20/2017
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    PMC14 = _F0_PMC14_DEFAULT_VALUE | _00_PMCn3_NOT_USE | _04_PMCn2_DI_ON | _02_PMCn1_DI_ON | _01_PMCn0_DI_ON;
    PFSEG0 = _80_PFSEG07_SEG | _40_PFSEG06_SEG | _20_PFSEG05_SEG | _10_PFSEG04_SEG;
    PFSEG1 = _80_PFSEG15_SEG | _40_PFSEG14_SEG | _20_PFSEG13_SEG | _10_PFSEG12_SEG | _08_PFSEG11_SEG | 
             _04_PFSEG10_SEG | _02_PFSEG09_SEG | _01_PFSEG08_SEG;
    PFSEG2 = _80_PFSEG23_SEG | _40_PFSEG22_SEG | _20_PFSEG21_SEG | _10_PFSEG20_SEG | _08_PFSEG19_SEG | 
             _04_PFSEG18_SEG | _02_PFSEG17_SEG | _01_PFSEG16_SEG;
    PFSEG3 = _80_PFSEG31_SEG | _40_PFSEG30_SEG | _20_PFSEG29_SEG | _10_PFSEG28_SEG | _08_PFSEG27_SEG | 
             _04_PFSEG26_SEG | _02_PFSEG25_SEG | _01_PFSEG24_SEG;
    PFSEG4 = _80_PFSEG39_SEG | _40_PFSEG38_SEG | _20_PFSEG37_SEG | _10_PFSEG36_SEG | _08_PFSEG35_SEG | 
             _04_PFSEG34_SEG | _02_PFSEG33_SEG | _01_PFSEG32_SEG;
    PFSEG5 = _10_PFSEG44_SEG | _08_PFSEG43_SEG | _04_PFSEG42_SEG | _02_PFSEG41_SEG | _01_PFSEG40_SEG;
    P14 = _08_Pn3_OUTPUT_1 | _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    PM14 = _F0_PM14_DEFAULT_VALUE | _00_PMn3_MODE_OUTPUT | _04_PMn2_MODE_INPUT | _02_PMn1_MODE_INPUT | 
           _01_PMn0_MODE_INPUT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
