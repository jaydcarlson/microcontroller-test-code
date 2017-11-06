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
* Copyright (C) 2011, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_dmac.h
* Version      : CodeGenerator for RL78/G12 V2.03.04.01 [11 Nov 2016]
* Device(s)    : R5F102A8
* Tool-Chain   : CCRL
* Description  : This file implements device driver for DMAC module.
* Creation Date: 7/25/2017
***********************************************************************************************************************/

#ifndef DMAC_H
#define DMAC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    DMA Mode Control Register n (DMCn)
*/
/* Setting of DMA transfer start software trigger (STGn) */
#define _00_DMA_TRIGGER_OPERATION_NO        (0x00U) /* no trigger operation */
#define _80_DMA_TRIGGER_OPERATION_SOFTWARE  (0x80U) /* DMA transfer is started when DMA operation is enabled */
/* Selection of DMA transfer direction (DRSn) */
#define _00_DMA_TRANSFER_DIR_SFR2RAM        (0x00U) /* SFR to internal RAM  */
#define _40_DMA_TRANSFER_DIR_RAM2SFR        (0x40U) /* internal RAM to SFR */
/* Specification of transfer data size for DMA transfer (DSn) */
#define _00_DMA_DATA_SIZE_8                 (0x00U) /* 8 bits */
#define _20_DMA_DATA_SIZE_16                (0x20U) /* 16 bits */
/* Pending of DMA transfer(DWAITn) */
#define _00_DMA_PENDING_NOTHELD             (0x00U) /* executes DMA transfer upon DMA start request */
#define _10_DMA_PENDING_HOLDS               (0x10U) /* hold DMA start request pending if any */
/* Selection of DMA stat source (IFCn3 - IFCn0) */
#define _00_DMA_TRIGGER_SOFTWARE            (0x00U) /* disable DMA transfer by interrupt */
#define _01_DMA_TRIGGER_AD                  (0x01U) /* A/D conversion end interrupt */
#define _02_DMA_TRIGGER_TM00                (0x02U) /* timer channel 0 interrupt */
#define _03_DMA_TRIGGER_TM01                (0x03U) /* timer channel 1 interrupt */
#define _04_DMA_TRIGGER_TM02                (0x04U) /* timer channel 2 interrupt */
#define _05_DMA_TRIGGER_TM03                (0x05U) /* timer channel 3 interrupt */
#define _06_DMA_TRIGGER_ST0_CSI00           (0x06U) /* UART0 transmission end / CSI00 transfer end */
#define _07_DMA_TRIGGER_SR0                 (0x07U) /* UART0 reception end interrupt */
#define _08_DMA_TRIGGER_ST1                 (0x08U) /* UART1 transmission end interrupt */
#define _09_DMA_TRIGGER_SR1_CSI11           (0x09U) /* UART1 reception end / CSI11 transfer end */
#define _0A_DMA_TRIGGER_ST2_CSI20           (0x0AU) /* UART2 transmission end / CSI20 transfer end */
#define _0B_DMA_TRIGGER_SR2                 (0x0BU) /* UART2 reception end interrupt */

/*
    DMA operation control register n (DRCn)
*/
/* DMA operation enable flag (DENn) */
#define _80_DMA_OPERATION_ENABLE            (0x80U) /* enable operation of DMA */
#define _00_DMA_OPERATION_DISABLE           (0x00U) /* disable operation of DMA */ 
/* DMA transfer mode flag (DSTn) */
#define _01_DMA_TRANSFER_UNDEREXEC          (0x01U) /* DMA transfer is not completed */ 
#define _00_DMA_TRANSFER_COMPLETED          (0x00U) /* DMA transfer is completed */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _12_DMA0_SFR_ADDRESS                (0x12U)
#define _FC00_DMA0_RAM_ADDRESS              (0xFC00U)
#define _0200_DMA0_BYTE_COUNT               (0x0200U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_DMAC0_Create(void);
void R_DMAC0_Start(void);
void R_DMAC0_Stop(void);
void R_DMAC0_Set_SoftwareTriggerOn(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
