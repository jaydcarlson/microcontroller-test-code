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
* File Name    : r_cg_vector_table.c
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MPG
* Tool-Chain   : gccrl78
* Description  : This file implements interrupt vector.
* Creation Date: 7/20/2017
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Set option bytes */
const uint8_t Option_Bytes[] __attribute__ ((section (".option_bytes"))) = 
    {0xEFU, 0xFFU, 0xE0U, 0x84U};

/* Set security ID */
const uint8_t Security_Id[] __attribute__ ((section (".security_id"))) = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

/* Secure trace RAM area */
uint8_t Ocd_TraceRam[1024] __attribute__ ((section (".ocd_traceram")));


#define VEC          __attribute__ ((section (".vec")))
const void *HardwareVectors[] VEC  = {
    /* Address 0x0 */
    PowerON_Reset,
    // Secure for Debugging
    (void*)0xFFFF
};

#define VECT_SECT          __attribute__ ((section (".vects")))
const void *Vectors[] VECT_SECT  = {
    /* Address 0x4 */
    R_Dummy,
    /* Address 0x6 */
    R_Dummy,
    /* Address 0x8 */
    R_Dummy,
    /* Address 0xA */
    R_Dummy,
    /* Address 0xC */
    R_Dummy,
    /* Address 0xE */
    R_Dummy,
    /* Address 0x10 */
    R_Dummy,
    /* Address 0x12 */
    R_Dummy,
    /* Address 0x14 */
    R_Dummy,
    /* Address 0x16 */
    R_Dummy,
    /* Address 0x18 */
    R_Dummy,
    /* Address 0x1A */
    R_Dummy,
    /* Address 0x1C */
    R_Dummy,
    /* Address 0x1E */
    R_Dummy,
    /* Address 0x20 */
    R_Dummy,
    /* Address 0x22 */
    R_Dummy,
    /* Address 0x24 */
    R_Dummy,
    /* Address 0x26 */
    R_Dummy,
    /* Address 0x28 */
    R_Dummy,
    /* Address 0x2A*/
    R_Dummy,
    /* Address 0x2C */
    R_Dummy,
    /* Address 0x2E */
    R_Dummy,
    /* Address 0x30 */
    R_Dummy,
    /* Address 0x32 */
    R_Dummy,
    /* Address 0x34 */
    R_Dummy,
    /* Address 0x36 */
    R_Dummy,
    /* Address 0x38 */
    R_Dummy,
    /* Address 0x3A */
    R_Dummy,
    /* Address 0x3C */
    R_Dummy,
    /* Address 0x3E */
    R_Dummy,
    /* Address 0x40 */
    R_Dummy,
    /* Address 0x42 */
    R_Dummy,
    /* Address 0x44 */
    R_Dummy,
    /* Address 0x46 */
    R_Dummy,
    /* Address 0x48 */
    R_Dummy,
    /* Address 0x4A */
    R_Dummy,
    /* Address 0x4C */
    R_Dummy,
    /* Address 0x4E */
    R_Dummy,
    /* Address 0x50 */
    R_Dummy,
    /* Address 0x52 */
    R_Dummy,
    /* Address 0x54 */
    R_Dummy,
    /* Address 0x56 */
    R_Dummy,
    /* Address 0x58 */
    R_Dummy,
    /* Address 0x5A */
    R_Dummy,
    /* Address 0x5C */
    R_Dummy,
    /* Address 0x5E */
    R_Dummy,
    /* Address 0x60 */
    R_Dummy,
    /* Address 0x62 */
    R_Dummy,
    /* Address 0x64 */
    R_Dummy,
    /* Address 0x66 */
    R_Dummy,
    /* Address 0x68 */
    R_Dummy,
    /* Address 0x6A */
    R_Dummy,
    /* Address 0x6C */
    R_Dummy,
    /* Address 0x6E */
    R_Dummy,
    /* Address 0x70 */
    R_Dummy,
    /* Address 0x72 */
    R_Dummy,
    /* Address 0x74 */
    R_Dummy,
    /* Address 0x76 */
    R_Dummy,
    /* Address 0x78 */
    R_Dummy,
    /* Address 0x7A */
    R_Dummy,
    /* Address 0x7C */
    R_Dummy,
    /* Address 0x7E */
    R_Dummy
};
/***********************************************************************************************************************
* Function Name: R_Dummy
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Dummy(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
