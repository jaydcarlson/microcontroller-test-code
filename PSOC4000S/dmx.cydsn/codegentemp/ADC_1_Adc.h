/***************************************************************************//**
* \file ADC_1_Adc.h
* \version 4.0
*
* \brief
*   This file provides the sources of APIs specific to the ADC implementation.
*
* \see CapSense P4 v4.0 Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_CAPSENSE_ADC_1_ADC_H)
#define CY_CAPSENSE_ADC_1_ADC_H


#include "cytypes.h"
#include "ADC_1_Structure.h"
#include "ADC_1_Configuration.h"

#if (ADC_1_ADC_EN)
    
/*******************************************************************************
* Function Prototypes 
*******************************************************************************/ 

/**
* \if SECTION_STANDALONE_ADC
* \addtogroup group_adc_public
* \{
*/
#if (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
    void ADC_1_Start(void);
    void ADC_1_Sleep(void);
    void ADC_1_Wakeup(void);
#endif  /* (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN) */
/** \}
* \endif */
/**
* \if SECTION_ADC_PUBLIC
* \addtogroup group_adc_public
* \{
*/
cystatus ADC_1_StartConvert(uint8 chId);
uint8 ADC_1_IsBusy(void);
uint16 ADC_1_ReadResult_mVolts(uint8 chId);
uint16 ADC_1_GetResult_mVolts(uint8 chId);
cystatus ADC_1_Calibrate(void);

void ADC_1_Stop(void);
void ADC_1_Resume(void);
/** \}
* \endif */


CY_ISR_PROTO(ADC_1_IntrHandler);

/**
* \if SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

void ADC_1_Initialize(void);
void ADC_1_SetAdcChannel(uint8 chId, uint32 state);
void ADC_1_ConfigAdcResources(void);
void ADC_1_StartAdcFSM(uint32 measureMode);
cystatus ADC_1_AdcCaptureResources(void);
cystatus ADC_1_AdcReleaseResources(void);
void ADC_1_ClearAdcChannels(void);

#define ADC_1_OFFSETNSIZE2MASK(o, s)  (((1uL << (s)) - 1uL) << (o))
/** \}
* \endif */

/**************************************
*           API Constants
**************************************/
#ifdef CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1
    #define ADC_1_CALIBRATE_VREF                             (ADC_1_ENABLE)
#else
    #define ADC_1_CALIBRATE_VREF                             (ADC_1_DISABLE)
#endif

/* Error value if given bad channel ID. */
#define ADC_1_VALUE_BAD_CHAN_ID            (0x0000FFFFuL)
#define ADC_1_VALUE_BAD_RESULT             (0x0000FFFFuL)
/* Obsolete */
#define ADC_1_VALUE_BADCHANID              (0x0000FFFFuL)
#define ADC_1_VALUE_BADRESULT              (0x0000FFFFuL)

/* Statuses defined for use with IsBusy */
#define ADC_1_STATUS_LASTCHAN_MASK         (0x0000000FuL)
#define ADC_1_STATUS_FSM_MASK              (0x000000F0uL)
#define ADC_1_STATUS_IDLE                  (0x0u)
#define ADC_1_STATUS_CALIBPH1              (0x10u)
#define ADC_1_STATUS_CALIBPH2              (0x20u)
#define ADC_1_STATUS_CALIBPH3              (0x30u)
#define ADC_1_STATUS_CONVERTING            (0x40u)
#define ADC_1_STATUS_OVERFLOW              (0x80u)

/* Potential channel states */
#define ADC_1_CHAN_CONNECT                 (1uL)
#define ADC_1_CHAN_DISCONNECT              (0uL)

/* Input/Output constants */
#define ADC_1_HSIOM_PRTSEL_MASK            (0xFuL)
#define ADC_1_HSIOM_PRTSEL_GPIO            (0x0uL)
#define ADC_1_HSIOM_PRTSEL_AMUXBUSB        (0x7uL)

#define ADC_1_GPIO_PC_MASK                 (0x7uL)
#define ADC_1_GPIO_PC_DISCONNECT           (0x0uL)
#define ADC_1_GPIO_PC_INPUT                (0x1uL)

/* Adc Config */
#define ADC_1_CONFIG_FILTER_DELAY_MASK     ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_FILTER_DELAY__OFFSET, \
                                                                        CYFLD_CSD_FILTER_DELAY__SIZE)
#define ADC_1_CONFIG_SHIELD_DELAY_MASK     ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_SHIELD_DELAY__OFFSET, \
                                                                        CYFLD_CSD_SHIELD_DELAY__SIZE)
#define ADC_1_CONFIG_SENSE_EN_MASK         ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_SENSE_EN__OFFSET, \
                                                                        CYFLD_CSD_SENSE_EN__SIZE)
#define ADC_1_CONFIG_CHARGE_MODE_MASK      ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_CHARGE_MODE__OFFSET, \
                                                                        CYFLD_CSD_CHARGE_MODE__SIZE)
#define ADC_1_CONFIG_MUTUAL_CAP_MASK       ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_MUTUAL_CAP__OFFSET, \
                                                                        CYFLD_CSD_MUTUAL_CAP__SIZE)
#define ADC_1_CONFIG_CSX_DUAL_CNT_MASK     ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_CSX_DUAL_CNT__OFFSET, \
                                                                        CYFLD_CSD_CSX_DUAL_CNT__SIZE)
#define ADC_1_CONFIG_DSI_COUNT_SEL_MASK    ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_DSI_COUNT_SEL__OFFSET, \
                                                                        CYFLD_CSD_DSI_COUNT_SEL__SIZE)
#define ADC_1_CONFIG_DSI_SAMPLE_EN_MASK    ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_DSI_SAMPLE_EN__OFFSET, \
                                                                        CYFLD_CSD_DSI_SAMPLE_EN__SIZE)
#define ADC_1_CONFIG_SAMPLE_SYNC_MASK      ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_SAMPLE_SYNC__OFFSET, \
                                                                        CYFLD_CSD_SAMPLE_SYNC__SIZE)
#define ADC_1_CONFIG_DSI_SENSE_EN_MASK     ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_DSI_SENSE_EN__OFFSET, \
                                                                        CYFLD_CSD_DSI_SENSE_EN__SIZE)
#define ADC_1_CONFIG_LP_MODE_MASK          ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_LP_MODE__OFFSET, \
                                                                        CYFLD_CSD_LP_MODE__SIZE)
#define ADC_1_CONFIG_ENABLE_MASK           ADC_1_OFFSETNSIZE2MASK(\
                                                                        CYFLD_CSD_ENABLE__OFFSET, \
                                                                        CYFLD_CSD_ENABLE__SIZE)
#define ADC_1_CONFIG_DEFAULT               (ADC_1_CONFIG_ENABLE_MASK | \
                                                                        (2uL << CYFLD_CSD_FILTER_DELAY__OFFSET) | \
                                                                        ADC_1_CONFIG_SAMPLE_SYNC_MASK | \
                                                                        ADC_1_CONFIG_SENSE_EN_MASK | \
                                                                        ADC_1_CONFIG_DSI_COUNT_SEL_MASK)

/* Measurement modes */
#define ADC_1_MEASMODE_SHIFT               (CYFLD_CSD_ADC_MODE__OFFSET)
#define ADC_1_MEASMODE_MASK                (0x3uL << ADC_1_MEASMODE_SHIFT)
#define ADC_1_MEASMODE_OFF                 (0x0uL << ADC_1_MEASMODE_SHIFT)
#define ADC_1_MEASMODE_VREF                (0x1uL << ADC_1_MEASMODE_SHIFT)
#define ADC_1_MEASMODE_VREFBY2             (0x2uL << ADC_1_MEASMODE_SHIFT)
#define ADC_1_MEASMODE_VIN                 (0x3uL << ADC_1_MEASMODE_SHIFT)

/* Clock defines */
#define ADC_1_SENSE_DIV_DEFAULT            (0x4uL)
#define ADC_1_TOTAL_CLOCK_DIV              (ADC_1_ADC_MODCLK_DIV_DEFAULT * \
                                                                         ADC_1_SENSE_DIV_DEFAULT)
/* SEQ_TIME field definitions: AZ Time */
#define ADC_1_ADC_MAX_AZ_TIME                                (21u)
#if (ADC_1_ADC_MAX_AZ_TIME < ADC_1_ADC_AZ_TIME)
    #define ADC_1_SEQ_TIME_BASE            (((CYDEV_BCLK__HFCLK__HZ * ADC_1_ADC_MAX_AZ_TIME) / \
                                                                         ADC_1_TOTAL_CLOCK_DIV) / 1000000uL)
#else
    #define ADC_1_SEQ_TIME_BASE            (((CYDEV_BCLK__HFCLK__HZ * ADC_1_ADC_AZ_TIME) / \
                                                                         ADC_1_TOTAL_CLOCK_DIV) / 1000000uL)
#endif

#if (0 == ADC_1_SEQ_TIME_BASE)
    #define ADC_1_SEQ_TIME_DEFAUL          (1u)
#else
    #define ADC_1_SEQ_TIME_DEFAUL          (ADC_1_SEQ_TIME_BASE)
#endif

/* Acquisition time definitions: ADC_CTL */
#define ADC_1_ACQUISITION_TIME_US          (10uL)
#define ADC_1_ACQUISITION_BASE             ((ADC_1_ACQUISITION_TIME_US * \
                                                                        (CYDEV_BCLK__HFCLK__MHZ)) / \
                                                                         ADC_1_TOTAL_CLOCK_DIV)

/* SEQ_START field definitions */
#define ADC_1_FSMSETTING_START_SHIFT       (CYFLD_CSD_START__OFFSET)
#define ADC_1_FSMSETTING_START_MASK        (ADC_1_OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_START__OFFSET, CYFLD_CSD_START__SIZE))
#define ADC_1_FSMSETTING_STARTSEQ          (0x1uL << ADC_1_FSMSETTING_START_SHIFT)
#define ADC_1_FSMSETTING_SEQ_MODE_SHIFT    (CYFLD_CSD_SEQ_MODE__OFFSET)
#define ADC_1_FSMSETTING_SEQ_MODE_MASK     (ADC_1_OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_SEQ_MODE__OFFSET, CYFLD_CSD_SEQ_MODE__SIZE))
#define ADC_1_FSMSETTING_SEQ_MODE_ADC      (0x0uL)
#define ADC_1_FSMSETTING_SEQ_MODE_COARSE   (0x1uL << ADC_1_FSMSETTING_SEQ_MODE_SHIFT)
#define ADC_1_FSMSETTING_ABORT_SHIFT       (CYFLD_CSD_ABORT__OFFSET)
#define ADC_1_FSMSETTING_ABORT_MASK        (ADC_1_OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_ABORT__OFFSET, CYFLD_CSD_ABORT__SIZE))
#define ADC_1_FSMSETTING_ABORT             (0x1uL << ADC_1_FSMSETTING_ABORT_SHIFT)
#define ADC_1_FSMSETTING_DSI_START_EN_SHIFT (CYFLD_CSD_DSI_START_EN__OFFSET)
#define ADC_1_FSMSETTING_DSI_START_EN_MASK (ADC_1_OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_DSI_START_EN__OFFSET, CYFLD_CSD_DSI_START_EN__SIZE))
#define ADC_1_FSMSETTING_DSI_START_EN      (0x1uL << ADC_1_FSMSETTING_DSI_START_EN_SHIFT)
#define ADC_1_FSMSETTING_AZ0SKIP_SHIFT     (CYFLD_CSD_AZ0_SKIP__OFFSET)
#define ADC_1_FSMSETTING_AZ0SKIP_MASK      (ADC_1_OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_AZ0_SKIP__OFFSET, CYFLD_CSD_AZ0_SKIP__SIZE))
#define ADC_1_FSMSETTING_AZ0SKIP           (0x1uL << ADC_1_FSMSETTING_AZ0SKIP_SHIFT)
#define ADC_1_FSMSETTING_AZ1SKIP_SHIFT     (CYFLD_CSD_AZ1_SKIP__OFFSET)
#define ADC_1_FSMSETTING_AZ1SKIP_MASK      (ADC_1_OFFSETNSIZE2MASK \
                                                                        (CYFLD_CSD_AZ1_SKIP__OFFSET, CYFLD_CSD_AZ1_SKIP__SIZE))
#define ADC_1_FSMSETTING_AZ1SKIP           (0x1uL << ADC_1_FSMSETTING_AZ1SKIP_SHIFT)

#define ADC_1_FSMSETTING_NOAZSKIP          (0uL)
#define ADC_1_FSMSETTING_AZSKIP_DEFAULT    (ADC_1_FSMSETTING_AZ0SKIP \
                                                                        | ((0u != ADC_1_ADC_AZ_EN) \
                                                                        ? 0u \
                                                                        : ADC_1_FSMSETTING_AZ1SKIP))
#define ADC_1_FSMSETTING_DSIIGNORE         (0x00000000uL)
#define ADC_1_FSMSETTING_NOABORT           (0x00000000uL)
#define ADC_1_FSMSETTING_SEQMODE           (0x00000000uL)
#define ADC_1_FSMSETTING_START             (0x00000001uL)

/* Interrupt definitions */
#define ADC_1_INTERRUPT_SHIFT              (CYFLD_CSD_ADC_RES__OFFSET)
#define ADC_1_INTERRUPT_MASK               (0x1uL << ADC_1_INTERRUPT_SHIFT)
#define ADC_1_INTERRUPT_CLEAR              (0x00000000uL)
#define ADC_1_INTERRUPT_SET                (ADC_1_INTERRUPT_MASK)

/* IDACB definitions */
/* The idac configuration for ADC use is mostly static, with only the VAL field
   varying. 
   Dynamic Polarity = 1 << 7
   Polarity (normal) = 0 << 8
   Balance, Leg1, Leg2 modes = don't care.
   DSI Control Enable (no mix) = 0 << 21
   Range (low) = 0 << 22
   Leg1, Leg2 enable = 0
   Leg3 enable = 1 << 26
   */

#define ADC_1_IDACB_CONFIG                 (0x04000080uL)
#define ADC_1_IDACB_VAL_MASK               (0x7FuL)
#define ADC_1_CLK16_MASK                   (0x0000FFFFuL)
#define ADC_1_CLK16VAL_SHIFT               (8uL)
/* Switch definitions */
#define ADC_1_SW_HSP_DEFAULT               (0x10000000uL)
#define ADC_1_SW_HSN_DEFAULT               (0x00100000uL)
#define ADC_1_SW_HSP_GETINPOL              (0x00010000uL)
#define ADC_1_SW_HSN_GETINPOL              (0x01000000uL)
#define ADC_1_SW_SHIELD_DEFAULT            (0x00000000uL)
#define ADC_1_SW_SHIELD_VDDA2CSDBUSB       (0x00000100uL)
#define ADC_1_SW_BYP_DEFAULT               (0x00110000uL)
#define ADC_1_SW_CMPP_DEFAULT              (0x00000000uL)
#define ADC_1_SW_CMPN_DEFAULT              (0x00000000uL)
#define ADC_1_SW_REFGEN_DEFAULT            (0x10000000uL)
#define ADC_1_SW_FWMOD_DEFAULT             (0x01100000uL)
#define ADC_1_SW_FWTANK_DEFAULT            (0x01100000uL)

#define ADC_1_SW_CTANK_PINSHIFT            (9uL)
#define ADC_1_SW_CMOD_PINSHIFT             (6uL)
#define ADC_1_SW_CMOD_PORT_MASK            (0x400uL)
#define ADC_1_SW_DSI_CMOD                  (1uL << 4)
#define ADC_1_SW_DSI_CTANK                 (1uL << 0)

#define ADC_1_LVTHRESH                     (2700uL)

/* Vrefhi is achieved via a gain applied to a source. Source value is usually 1.2V */
#define ADC_1_VREFSRC_MV                   (1200uL)
/* The reference voltage is measured at nominal 2400 mV. Measured amount is stored in CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1 */
#define ADC_1_VREFCALIB_BASE               (2400uL)

/* RefGen settings */
#define ADC_1_REFGEN_GAIN_SHIFT            (CYFLD_CSD_GAIN__OFFSET)

/* At low voltage, REFGEN is enabled and bypassed. */
#define ADC_1_REFGEN_LV                    (0x00000011uL)
#define ADC_1_SW_AMUBUF_LV                 (0x01000100uL)
#define ADC_1_AMBUF_LV                     (0x00000002uL)
/* At normal voltage, REFGEN uses customizer-defined gain */
#define ADC_1_REFGEN_NORM                  (0x00000041uL | \
                                                                        (ADC_1_ADC_GAIN << \
                                                                        ADC_1_REFGEN_GAIN_SHIFT))

#define ADC_1_SW_AMUBUF_NORM               (0x00000000uL)

#if (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
    #define ADC_1_MODCLK_CMD_DIV_SHIFT     (0u)
    #define ADC_1_MODCLK_CMD_PA_DIV_SHIFT  (8u)
    #define ADC_1_MODCLK_CMD_DISABLE_SHIFT (30u)
    #define ADC_1_MODCLK_CMD_ENABLE_SHIFT  (31u)
    /* No ADC prefix */
    #define ADC_1_MODCLK_CMD_DISABLE_MASK  ((uint32)((uint32)1u << ADC_1_MODCLK_CMD_DISABLE_SHIFT))
    #define ADC_1_MODCLK_CMD_ENABLE_MASK   ((uint32)((uint32)1u << ADC_1_MODCLK_CMD_ENABLE_SHIFT))

    #define ADC_1_MODCLK_DIV_REG           (*(reg32 *)ADC_1_ModClk__DIV_REGISTER)
    #define ADC_1_MODCLK_DIV_PTR           ( (reg32 *)ADC_1_ModClk__DIV_REGISTER)
    #define ADC_1_MODCLK_CMD_REG           (*(reg32 *)CYREG_PERI_DIV_CMD)
    #define ADC_1_MODCLK_CMD_PTR           ( (reg32 *)CYREG_PERI_DIV_CMD)
#endif /* (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN) */

/* HSCOMP definitions */
#define ADC_1_HSCMP_AZ_SHIFT               (31uL)
#define ADC_1_HSCMP_AZ_DEFAULT             (0x00000001uL | \
                                                                        (ADC_1_ADC_AZ_EN << \
                                                                        ADC_1_HSCMP_AZ_SHIFT))

#define ADC_1_STATUS_HSCMP_OUT_MASK        (0x1uL << 2uL)

/* ADC_RES definitions */
#define ADC_1_RES_MAX                      ((1uL << ADC_1_ADC_RESOLUTION) - 1uL)
#define ADC_1_ADC_RES_OVERFLOW_MASK        (0x40000000uL)
#define ADC_1_ADC_RES_ABORT_MASK           (0x80000000uL)
#define ADC_1_ADC_RES_HSCMPPOL_MASK        (0x00010000uL)
#define ADC_1_ADC_RES_VALUE_MASK           (0x0000FFFFuL)
#define ADC_1_UNDERFLOW_LIMIT              (8000u)

/* Actual VREFHI is used in calculations. */
#define ADC_1_VREFHI_MV                    (ADC_1_ADC_VREF_MV)

/* Register definitions */
#define ADC_1_CONFIG_REG                   (*(reg32 *) CYREG_CSD_CONFIG)
#define ADC_1_SPARE_REG                    (*(reg32 *) CYREG_CSD_SPARE)
#define ADC_1_STATUS_REG                   (*(reg32 *) CYREG_CSD_STATUS)
#define ADC_1_STAT_SEQ_REG                 (*(reg32 *) CYREG_CSD_STAT_SEQ)
#define ADC_1_STAT_CNTS_REG                (*(reg32 *) CYREG_CSD_STAT_CNTS)
#define ADC_1_RESULT_VAL1_REG              (*(reg32 *) CYREG_CSD_RESULT_VAL1)
#define ADC_1_RESULT_VAL2_REG              (*(reg32 *) CYREG_CSD_RESULT_VAL2)
#define ADC_1_ADC_RES_REG                  (*(reg32 *) CYREG_CSD_ADC_RES)
#define ADC_1_INTR_REG                     (*(reg32 *) CYREG_CSD_INTR)
#define ADC_1_INTR_SET_REG                 (*(reg32 *) CYREG_CSD_INTR_SET)
#define ADC_1_INTR_MASK_REG                (*(reg32 *) CYREG_CSD_INTR_MASK)
#define ADC_1_INTR_MASKED_REG              (*(reg32 *) CYREG_CSD_INTR_MASKED)
#define ADC_1_HSCMP_REG                    (*(reg32 *) CYREG_CSD_HSCMP)
#define ADC_1_AMBUF_REG                    (*(reg32 *) CYREG_CSD_AMBUF)
#define ADC_1_REFGEN_REG                   (*(reg32 *) CYREG_CSD_REFGEN)
#define ADC_1_CSDCMP_REG                   (*(reg32 *) CYREG_CSD_CSDCMP)
#define ADC_1_IDACA_REG                    (*(reg32 *) CYREG_CSD_IDACA)
#define ADC_1_IDACB_REG                    (*(reg32 *) CYREG_CSD_IDACB)
#define ADC_1_SW_RES_REG                   (*(reg32 *) CYREG_CSD_SW_RES)
#define ADC_1_SENSE_PERIOD_REG             (*(reg32 *) CYREG_CSD_SENSE_PERIOD)
#define ADC_1_SENSE_DUTY_REG               (*(reg32 *) CYREG_CSD_SENSE_DUTY)
#define ADC_1_SW_HS_P_SEL_REG              (*(reg32 *) CYREG_CSD_SW_HS_P_SEL)
#define ADC_1_SW_HS_N_SEL_REG              (*(reg32 *) CYREG_CSD_SW_HS_N_SEL)
#define ADC_1_SW_SHIELD_SEL_REG            (*(reg32 *) CYREG_CSD_SW_SHIELD_SEL)
#define ADC_1_SW_AMUXBUF_SEL_REG           (*(reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)
#define ADC_1_SW_BYP_SEL_REG               (*(reg32 *) CYREG_CSD_SW_BYP_SEL)
#define ADC_1_SW_CMP_P_SEL_REG             (*(reg32 *) CYREG_CSD_SW_CMP_P_SEL)
#define ADC_1_SW_CMP_N_SEL_REG             (*(reg32 *) CYREG_CSD_SW_CMP_N_SEL)
#define ADC_1_SW_REFGEN_SEL_REG            (*(reg32 *) CYREG_CSD_SW_REFGEN_SEL)
#define ADC_1_SW_FW_MOD_SEL_REG            (*(reg32 *) CYREG_CSD_SW_FW_MOD_SEL)
#define ADC_1_SW_FW_TANK_SEL_REG           (*(reg32 *) CYREG_CSD_SW_FW_TANK_SEL)
#define ADC_1_SW_DSI_SEL_REG               (*(reg32 *) CYREG_CSD_SW_DSI_SEL)
#define ADC_1_SEQ_TIME_REG                 (*(reg32 *) CYREG_CSD_SEQ_TIME)
#define ADC_1_SEQ_INIT_CNT_REG             (*(reg32 *) CYREG_CSD_SEQ_INIT_CNT)
#define ADC_1_SEQ_NORM_CNT_REG             (*(reg32 *) CYREG_CSD_SEQ_NORM_CNT)
#define ADC_1_ADC_CTL_REG                  (*(reg32 *) CYREG_CSD_ADC_CTL)
#define ADC_1_SEQ_START_REG                (*(reg32 *) CYREG_CSD_SEQ_START)

#define ADC_1_CONFIG_PTR                   ((reg32 *) CYREG_CSD_CONFIG)
#define ADC_1_SPARE_PTR                    ((reg32 *) CYREG_CSD_SPARE)
#define ADC_1_STATUS_PTR                   ((reg32 *) CYREG_CSD_STATUS)
#define ADC_1_STAT_SEQ_PTR                 ((reg32 *) CYREG_CSD_STAT_SEQ)
#define ADC_1_STAT_CNTS_PTR                ((reg32 *) CYREG_CSD_STAT_CNTS)
#define ADC_1_RESULT_VAL1_PTR              ((reg32 *) CYREG_CSD_RESULT_VAL1)
#define ADC_1_RESULT_VAL2_PTR              ((reg32 *) CYREG_CSD_RESULT_VAL2)
#define ADC_1_ADC_RES_PTR                  ((reg32 *) CYREG_CSD_ADC_RES)
#define ADC_1_INTR_PTR                     ((reg32 *) CYREG_CSD_INTR)
#define ADC_1_INTR_SET_PTR                 ((reg32 *) CYREG_CSD_INTR_SET)
#define ADC_1_INTR_MASK_PTR                ((reg32 *) CYREG_CSD_INTR_MASK)
#define ADC_1_INTR_MASKED_PTR              ((reg32 *) CYREG_CSD_INTR_MASKED)
#define ADC_1_HSCMP_PTR                    ((reg32 *) CYREG_CSD_HSCMP)
#define ADC_1_AMBUF_PTR                    ((reg32 *) CYREG_CSD_AMBUF)
#define ADC_1_REFGEN_PTR                   ((reg32 *) CYREG_CSD_REFGEN)
#define ADC_1_CSDCMP_PTR                   ((reg32 *) CYREG_CSD_CSDCMP)
#define ADC_1_IDACA_PTR                    ((reg32 *) CYREG_CSD_IDACA)
#define ADC_1_IDACB_PTR                    ((reg32 *) CYREG_CSD_IDACB)
#define ADC_1_SW_RES_PTR                   ((reg32 *) CYREG_CSD_SW_RES)
#define ADC_1_SENSE_PERIOD_PTR             ((reg32 *) CYREG_CSD_SENSE_PERIOD)
#define ADC_1_SENSE_DUTY_PTR               ((reg32 *) CYREG_CSD_SENSE_DUTY)
#define ADC_1_SW_HS_P_SEL_PTR              ((reg32 *) CYREG_CSD_SW_HS_P_SEL)
#define ADC_1_SW_HS_N_SEL_PTR              ((reg32 *) CYREG_CSD_SW_HS_N_SEL)
#define ADC_1_SW_SHIELD_SEL_PTR            ((reg32 *) CYREG_CSD_SW_SHIELD_SEL)
#define ADC_1_SW_AMUXBUF_SEL_PTR           ((reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)
#define ADC_1_SW_BYP_SEL_PTR               ((reg32 *) CYREG_CSD_SW_BYP_SEL)
#define ADC_1_SW_CMP_P_SEL_PTR             ((reg32 *) CYREG_CSD_SW_CMP_P_SEL)
#define ADC_1_SW_CMP_N_SEL_PTR             ((reg32 *) CYREG_CSD_SW_CMP_N_SEL)
#define ADC_1_SW_REFGEN_SEL_PTR            ((reg32 *) CYREG_CSD_SW_REFGEN_SEL)
#define ADC_1_SW_FW_MOD_SEL_PTR            ((reg32 *) CYREG_CSD_SW_FW_MOD_SEL)
#define ADC_1_SW_FW_TANK_SEL_PTR           ((reg32 *) CYREG_CSD_SW_FW_TANK_SEL)
#define ADC_1_SW_DSI_SEL_PTR               ((reg32 *) CYREG_CSD_SW_DSI_SEL)
#define ADC_1_SEQ_TIME_PTR                 ((reg32 *) CYREG_CSD_SEQ_TIME)
#define ADC_1_SEQ_INIT_CNT_PTR             ((reg32 *) CYREG_CSD_SEQ_INIT_CNT)
#define ADC_1_SEQ_NORM_CNT_PTR             ((reg32 *) CYREG_CSD_SEQ_NORM_CNT)
#define ADC_1_ADC_CTL_PTR                  ((reg32 *) CYREG_CSD_ADC_CTL)
#define ADC_1_SEQ_START_PTR                ((reg32 *) CYREG_CSD_SEQ_START)


#endif 	/* ADC_1_ADC_EN */

#endif	/* CY_CAPSENSE_ADC_1_ADC_H */


/* [] END OF FILE */
