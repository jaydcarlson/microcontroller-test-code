/*******************************************************************************
* \file       ADC_1_Configuration.h
* \version    4.0
*
* \brief
*   This file provides the customizer parameters definitions.
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

#if !defined(CY_CAPSENSE_ADC_1_CONFIGURATION_H)
#define CY_CAPSENSE_ADC_1_CONFIGURATION_H

#include <cytypes.h>

/*******************************************************************************
* Customizer-generated defines
*******************************************************************************/
#define ADC_1_ENABLE                   (1u)
#define ADC_1_DISABLE                  (0u)

/*******************************************************************************
* Creator-global defines
*******************************************************************************/
#ifdef CYIPBLOCK_m0s8csdv2_VERSION
    #define ADC_1_CSDV2                              (1u)
#else
    #define ADC_1_CSDV2                              (0u)
#endif  /* CYIPBLOCK_m0s8csdv2_VERSION */

#define ADC_1_2000_MV                            (2000u)

#ifdef CYDEV_VDDA_MV
    #define ADC_1_CYDEV_VDDA_MV                  (CYDEV_VDDA_MV)
#else
    #define ADC_1_CYDEV_VDDA_MV                  (CYDEV_VDD_MV)
#endif  /* #ifdef CYDEV_VDDA_MV */

#define ADC_1_BAD_CONVERSIONS_NUM                (1u)
#define ADC_1_RESAMPLING_CYCLES_MAX_NUMBER       (1u)

/*******************************************************************************
* Enabled Scan Methods
*******************************************************************************/
#define ADC_1_CSD_EN                   (0u)
#define ADC_1_CSX_EN                   (0u)
#define ADC_1_CSD_CSX_EN               (ADC_1_CSD_EN & ADC_1_CSX_EN)
#define ADC_1_CSD2X_EN                 (0u)
#define ADC_1_CSX2X_EN                 (0u)

/*******************************************************************************
* Definitions for number of widgets and sensors
*******************************************************************************/
#define ADC_1_TOTAL_WIDGETS            (0u)
#define ADC_1_TOTAL_CSD_WIDGETS        (0u)
#define ADC_1_TOTAL_CSD_SENSORS        (0u)
#define ADC_1_TOTAL_CSX_WIDGETS        (0u)
#define ADC_1_TOTAL_CSX_NODES          (0u)

/*******************************************************************************
* Total number of CSD sensors + CSX nodes
*******************************************************************************/
#define ADC_1_TOTAL_SENSORS            (ADC_1_TOTAL_CSD_SENSORS + \
                                                   ADC_1_TOTAL_CSX_NODES)

/*******************************************************************************
* Total number of scan slots (used only when dual-channel scan is enabled)
*******************************************************************************/
#define ADC_1_TOTAL_SCAN_SLOTS         (0u)

/*******************************************************************************
* Define widget IDs
*******************************************************************************/

/*******************************************************************************
* Define sensor IDs
*******************************************************************************/


/*******************************************************************************
* Define ADC channel IDs
*******************************************************************************/
#define ADC_1_CHANNEL_0                         (0u)
#define ADC_1_CHANNEL_1                         (1u)
#define ADC_1_CHANNEL_2                         (2u)
#define ADC_1_CHANNEL_3                         (3u)
#define ADC_1_CHANNEL_4                         (4u)
#define ADC_1_CHANNEL_5                         (5u)
#define ADC_1_CHANNEL_6                         (6u)
#define ADC_1_CHANNEL_7                         (7u)
#define ADC_1_CHANNEL_8                         (8u)
#define ADC_1_CHANNEL_9                         (9u)


/*******************************************************************************
* Enabled widget types
*******************************************************************************/
#define ADC_1_BUTTON_WIDGET_EN         (0u)
#define ADC_1_SLIDER_WIDGET_EN         (0u)
#define ADC_1_MATRIX_WIDGET_EN         (0u)
#define ADC_1_PROXIMITY_WIDGET_EN      (0u)
#define ADC_1_TOUCHPAD_WIDGET_EN       (0u)

#define ADC_1_CSD_MATRIX_WIDGET_EN     (0u)
#define ADC_1_CSD_TOUCHPAD_WIDGET_EN   (0u)

#define ADC_1_CSX_MATRIX_WIDGET_EN     (0u)
#define ADC_1_CSX_TOUCHPAD_WIDGET_EN   (0u)

/*******************************************************************************
* Centroid APIs
*******************************************************************************/
#define ADC_1_CENTROID_EN              (0u)
#define ADC_1_TOTAL_DIPLEXED_SLIDERS   (0u)
#define ADC_1_TOTAL_LINEAR_SLIDERS     (0u)
#define ADC_1_TOTAL_RADIAL_SLIDERS     (0u)
#define ADC_1_TOTAL_TOUCHPADS          (0u)
#define ADC_1_MAX_CENTROID_LENGTH      (0u)

/*******************************************************************************
* Enabled sensor types
*******************************************************************************/
#define ADC_1_REGULAR_SENSOR_EN        (0u)
#define ADC_1_PROXIMITY_SENSOR_EN      (0u)

/*******************************************************************************
* Sensor ganging
*******************************************************************************/
#define ADC_1_GANGED_SNS_EN            (0u)
#define ADC_1_CSD_GANGED_SNS_EN        (0u)
#define ADC_1_CSX_GANGED_SNS_EN        (0u)

/*******************************************************************************
* Max number of sensors used among all widgets
*******************************************************************************/
#define ADC_1_MAX_SENSORS_PER_WIDGET   (0u)

/*******************************************************************************
* Total number of all used electrodes (NOT unique)
*******************************************************************************/
#define ADC_1_TOTAL_ELECTRODES         (0u)
/* Obsolete */
#define ADC_1_TOTAL_SENSOR_IOS         ADC_1_TOTAL_ELECTRODES

/*******************************************************************************
* Total number of used physical IOs (unique)
*******************************************************************************/
#define ADC_1_TOTAL_IO_CNT             (0u)

/*******************************************************************************
* Array length for widget status registers
*******************************************************************************/
#define ADC_1_WDGT_STATUS_WORDS        \
                        (((uint8)((ADC_1_TOTAL_WIDGETS - 1u) / 32u)) + 1u)


/*******************************************************************************
* Auto-tuning mode selection
*******************************************************************************/
#define ADC_1_CSD_SS_DIS         (0x00ul)
#define ADC_1_CSD_SS_HW_EN       (0x01ul)
#define ADC_1_CSD_SS_TH_EN       (0x02ul)
#define ADC_1_CSD_SS_HWTH_EN     (ADC_1_CSD_SS_HW_EN | \
                                             ADC_1_CSD_SS_TH_EN)

#define ADC_1_CSD_AUTOTUNE       ADC_1_CSD_SS_DIS


/*******************************************************************************
* General settings
*******************************************************************************/

#define ADC_1_AUTO_RESET_METHOD_LEGACY (0u)
#define ADC_1_AUTO_RESET_METHOD_SAMPLE (1u)

#define ADC_1_MULTI_FREQ_SCAN_EN       (0u)
#define ADC_1_SENSOR_AUTO_RESET_EN     (0u)
#define ADC_1_SENSOR_AUTO_RESET_METHOD (0u)
#define ADC_1_NUM_CENTROIDS            (1u)
#define ADC_1_4PTS_LOCAL_MAX_EN        (0u)
#define ADC_1_OFF_DEBOUNCE_EN          (0u)
#define ADC_1_CUSTOM_DS_RAM_SIZE       (0u)

/* Define power status of HW IP block after scanning */
#define ADC_1_BLOCK_OFF_AFTER_SCAN_EN  (0u)

/* Define number of scan frequencies */
#if (ADC_1_DISABLE != ADC_1_MULTI_FREQ_SCAN_EN)
    #define ADC_1_NUM_SCAN_FREQS       (3u)
#else
    #define ADC_1_NUM_SCAN_FREQS       (1u)
#endif /* #if (ADC_1_DISABLE != ADC_1_MULTI_FREQ_SCAN_EN) */

/* Data size for thresholds / low baseline reset */
#define ADC_1_SIZE_8BITS               (8u)
#define ADC_1_SIZE_16BITS              (16u)

#define ADC_1_THRESHOLD_SIZE           ADC_1_SIZE_16BITS
typedef uint16 ADC_1_THRESHOLD_TYPE;

#if (ADC_1_AUTO_RESET_METHOD_LEGACY == ADC_1_SENSOR_AUTO_RESET_METHOD)
    #define ADC_1_LOW_BSLN_RST_SIZE        ADC_1_SIZE_8BITS
    typedef uint8 ADC_1_LOW_BSLN_RST_TYPE;
#else
    #define ADC_1_LOW_BSLN_RST_SIZE    (16u)
    typedef uint16 ADC_1_LOW_BSLN_RST_TYPE;
#endif /* #if (ADC_1_AUTO_RESET_METHOD_LEGACY == ADC_1_SENSOR_AUTO_RESET_METHOD) */

/* Coefficient to define touch threshold for proximity sensors */
#define ADC_1_PROX_TOUCH_COEFF         (300u)

/*******************************************************************************
* General Filter Constants
*******************************************************************************/

/* Baseline algorithm options */
#define ADC_1_IIR_BASELINE                 (0u)
#define ADC_1_BUCKET_BASELINE              (1u)

#define ADC_1_BASELINE_TYPE                ADC_1_IIR_BASELINE

/* IIR baseline filter algorithm for regular sensors*/
#define ADC_1_REGULAR_IIR_BL_TYPE          ADC_1_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for regular sensors */
#define ADC_1_REGULAR_IIR_BL_N             (1u)
#define ADC_1_REGULAR_IIR_BL_SHIFT         (8u)

/* IIR baseline filter algorithm for proximity sensors*/
#define ADC_1_PROX_IIR_BL_TYPE             ADC_1_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for proximity sensors */
#define ADC_1_PROX_IIR_BL_N                (1u)
#define ADC_1_PROX_IIR_BL_SHIFT            (8u)


/* IIR filter constants */
#define ADC_1_IIR_COEFFICIENT_K            (256u)

/* IIR filter type */
#define ADC_1_IIR_FILTER_STANDARD          (1u)
#define ADC_1_IIR_FILTER_PERFORMANCE       (2u)
#define ADC_1_IIR_FILTER_MEMORY            (3u)

/* Regular sensor raw-count filters */
#define ADC_1_REGULAR_RC_FILTER_EN         (0u)
#define ADC_1_REGULAR_RC_IIR_FILTER_EN     (0u)
#define ADC_1_REGULAR_RC_MEDIAN_FILTER_EN  (0u)
#define ADC_1_REGULAR_RC_AVERAGE_FILTER_EN (0u)
#define ADC_1_REGULAR_RC_CUSTOM_FILTER_EN  (0u)
#define ADC_1_REGULAR_RC_ALP_FILTER_EN     (0u)

/* Proximity sensor raw-count filters */
#define ADC_1_PROX_RC_FILTER_EN            (0u)
#define ADC_1_PROX_RC_IIR_FILTER_EN        (0u)
#define ADC_1_PROX_RC_MEDIAN_FILTER_EN     (0u)
#define ADC_1_PROX_RC_AVERAGE_FILTER_EN    (0u)
#define ADC_1_PROX_RC_CUSTOM_FILTER_EN     (0u)
#define ADC_1_PROX_RC_ALP_FILTER_EN        (0u)

#define ADC_1_ALP_FILTER_EN                (0u)
#define ADC_1_REGULAR_RC_ALP_FILTER_COEFF  (2u)
#define ADC_1_PROX_RC_ALP_FILTER_COEFF     (2u)

/* IIR raw-count filter algorithm for regular sensors */
#define ADC_1_REGULAR_IIR_RC_TYPE          (ADC_1_IIR_FILTER_STANDARD)

/* IIR raw-count filter coefficients for regular sensors */
#define ADC_1_REGULAR_IIR_RC_N             (128u)
#define ADC_1_REGULAR_IIR_RC_SHIFT         (0u)

/* IIR raw-count filter algorithm for proximity sensors*/
#define ADC_1_PROX_IIR_RC_TYPE             (ADC_1_IIR_FILTER_STANDARD)

/* IIR raw-count filter coefficients for proximity sensors */
#define ADC_1_PROX_IIR_RC_N                (128u)
#define ADC_1_PROX_IIR_RC_SHIFT            (0u)

/* Median filter constants */

/* Order of regular sensor median filter */
#define ADC_1_REGULAR_MEDIAN_LEN           (2u)

/* Order of proximity sensor median filter */
#define ADC_1_PROX_MEDIAN_LEN              (2u)

/* Average filter constants*/
#define ADC_1_AVERAGE_FILTER_LEN_2         (1u)
#define ADC_1_AVERAGE_FILTER_LEN_4         (3u)

/* Order of regular sensor average filter */
#define ADC_1_REGULAR_AVERAGE_LEN          (ADC_1_AVERAGE_FILTER_LEN_4)

/* Order of proximity sensor average filter */
#define ADC_1_PROX_AVERAGE_LEN             (ADC_1_AVERAGE_FILTER_LEN_4)

/* Widget baseline coefficient enable */
#define ADC_1_WD_BSLN_COEFF_EN             (0u)

/* Centroid position filters */
#define ADC_1_POS_IIR_FILTER_EN            (0x00u)
#define ADC_1_POS_MEDIAN_FILTER_EN         (0x00u)
#define ADC_1_POS_AVERAGE_FILTER_EN        (0x00u)
#define ADC_1_POS_JITTER_FILTER_EN         (0x00u)
#define ADC_1_CSX_TOUCHPAD_POS_MEDIAN_FILTER_EN (0x00u)

#define ADC_1_POS_IIR_COEFF                (128u)
#define ADC_1_CSX_TOUCHPAD_UNDEFINED       (40u)


/* IDAC options */

/* CSDv1 IDAC gain */
#define ADC_1_IDAC_GAIN_4X                 (4u)
#define ADC_1_IDAC_GAIN_8X                 (8u)

/* CSDv2 IDAC gain */
#define ADC_1_IDAC_GAIN_LOW                (0uL)
#define ADC_1_IDAC_GAIN_MEDIUM             (1uL)
#define ADC_1_IDAC_GAIN_HIGH               (2uL)

#define ADC_1_IDAC_SOURCING                (0u)
#define ADC_1_IDAC_SINKING                 (1u)

/* Shield tank capacitor precharge source */
#define ADC_1_CSH_PRECHARGE_VREF           (0u)
#define ADC_1_CSH_PRECHARGE_IO_BUF         (1u)

/* Shield electrode delay */
#define ADC_1_NO_DELAY                     (0u)
/* CSDv1 */
#define ADC_1_SH_DELAY_50NS                (1u)
#define ADC_1_SH_DELAY_100NS               (2u)
/* CSDv2 */
#define ADC_1_SH_DELAY_5NS                 (1u)
#define ADC_1_SH_DELAY_10NS                (2u)
#define ADC_1_SH_DELAY_20NS                (3u)

/* Inactive sensor connection options */
#define ADC_1_SNS_CONNECTION_GROUND        (0x00000006Lu)
#define ADC_1_SNS_CONNECTION_HIGHZ         (0x00000000Lu)
#define ADC_1_SNS_CONNECTION_SHIELD        (0x00000002Lu)

/* Sense clock selection options */
#if defined(ADC_1_TAPEOUT_STAR_USED)
    #define ADC_1_CSDV2_REF9P6UA_EN            (0u)
#else
    #define ADC_1_CSDV2_REF9P6UA_EN            (1u)
#endif /* defined(ADC_1_TAPEOUT_STAR_USED) */

#define ADC_1_CLK_SOURCE_DIRECT            (0x00000000Lu)

#define ADC_1_CLK_SOURCE_SSC1              (0x01u)
#define ADC_1_CLK_SOURCE_SSC2              (0x02u)
#define ADC_1_CLK_SOURCE_SSC3              (0x03u)
#define ADC_1_CLK_SOURCE_SSC4              (0x04u)

/* CSDv1 and CSDv2 */
#define ADC_1_CLK_SOURCE_PRS8              (0x05u)
#define ADC_1_CLK_SOURCE_PRS12             (0x06u)
#define ADC_1_CLK_SOURCE_PRSAUTO           (0xFFu)

/* Defines scan resolutions */
#define ADC_1_RES6BIT                      (6u)
#define ADC_1_RES7BIT                      (7u)
#define ADC_1_RES8BIT                      (8u)
#define ADC_1_RES9BIT                      (9u)
#define ADC_1_RES10BIT                     (10u)
#define ADC_1_RES11BIT                     (11u)
#define ADC_1_RES12BIT                     (12u)
#define ADC_1_RES13BIT                     (13u)
#define ADC_1_RES14BIT                     (14u)
#define ADC_1_RES15BIT                     (15u)
#define ADC_1_RES16BIT                     (16u)

/* CSDv2: Initialization switch resistance */
#define ADC_1_INIT_SW_RES_LOW              (0x00000000Lu)
#define ADC_1_INIT_SW_RES_MEDIUM           (0x00000001Lu)
#define ADC_1_INIT_SW_RES_HIGH             (0x00000002Lu)

/* CSDv2: Initialization switch resistance */
#define ADC_1_SCAN_SW_RES_LOW              (0x00000000Lu)
#define ADC_1_SCAN_SW_RES_MEDIUM           (0x00000001Lu)
#define ADC_1_SCAN_SW_RES_HIGH             (0x00000002Lu)

/* CSDv2: CSD shield switch resistance */
#define ADC_1_SHIELD_SW_RES_LOW            (0x00000000Lu)
#define ADC_1_SHIELD_SW_RES_MEDIUM         (0x00000001Lu)
#define ADC_1_SHIELD_SW_RES_HIGH           (0x00000002Lu)
#define ADC_1_SHIELD_SW_RES_LOW_EMI        (0x00000003Lu)

/* CSDv2: CSD shield switch resistance */
#define ADC_1_INIT_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define ADC_1_INIT_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define ADC_1_INIT_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define ADC_1_INIT_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* CSDv2: CSD shield switch resistance */
#define ADC_1_SCAN_SHIELD_SW_RES_LOW            (0x00000000Lu)
#define ADC_1_SCAN_SHIELD_SW_RES_MEDIUM         (0x00000001Lu)
#define ADC_1_SCAN_SHIELD_SW_RES_HIGH           (0x00000002Lu)
#define ADC_1_SCAN_SHIELD_SW_RES_LOW_EMI        (0x00000003Lu)

/*******************************************************************************
* CSD Specific settings
*******************************************************************************/

#define ADC_1_CSDV2_ANALOG_WAKEUP_DELAY_US (0u)

/* CSD scan method settings */
#define ADC_1_CSD_IDAC_AUTOCAL_EN          (0u)
#define ADC_1_CSD_IDAC_GAIN                (ADC_1_IDAC_GAIN_HIGH)
#define ADC_1_CSD_SHIELD_EN                (0u)
#define ADC_1_CSD_SHIELD_TANK_EN           (0u)
#define ADC_1_CSD_CSH_PRECHARGE_SRC        (ADC_1_CSH_PRECHARGE_VREF)
#define ADC_1_CSD_SHIELD_DELAY             (ADC_1_NO_DELAY)
#define ADC_1_CSD_TOTAL_SHIELD_COUNT       (0u)
#define ADC_1_CSD_SCANSPEED_DIVIDER        (2u)
#define ADC_1_CSD_COMMON_SNS_CLK_EN        (0u)
#define ADC_1_CSD_SNS_CLK_SOURCE           (ADC_1_CLK_SOURCE_PRSAUTO)
#define ADC_1_CSD_SNS_CLK_DIVIDER          (4u)
#define ADC_1_CSD_INACTIVE_SNS_CONNECTION  (ADC_1_SNS_CONNECTION_GROUND)
#define ADC_1_CSD_IDAC_COMP_EN             (0u)
#define ADC_1_CSD_IDAC_CONFIG              (ADC_1_IDAC_SOURCING)
#define ADC_1_CSD_RAWCOUNT_CAL_LEVEL       (85u)
#define ADC_1_CSD_DUALIDAC_LEVEL           (50u)
#define ADC_1_CSD_PRESCAN_SETTLING_TIME    (5u)
#define ADC_1_CSD_SNSCLK_R_CONST           (1000u)
#define ADC_1_CSD_VREF_MV                  (2021u)

/* CSD settings - CSDv2 */
#define ADC_1_CSD_ANALOG_STARTUP_DELAY_US  (0u)
#define ADC_1_CSD_FINE_INIT_TIME           (10u)
#define ADC_1_CSD_DEDICATED_IDAC_COMP_EN   (0u)
#define ADC_1_CSD_AUTO_ZERO_EN             (0u)
#define ADC_1_CSD_AUTO_ZERO_TIME           (15Lu)
#define ADC_1_CSD_NOISE_METRIC_EN          (0u)
#define ADC_1_CSD_NOISE_METRIC_TH          (1Lu)
#define ADC_1_CSD_INIT_SWITCH_RES          (ADC_1_INIT_SW_RES_MEDIUM)
#define ADC_1_CSD_SHIELD_SWITCH_RES        (ADC_1_SHIELD_SW_RES_MEDIUM)
#define ADC_1_CSD_GAIN                     (18Lu)


/*******************************************************************************
* CSX Specific settings
*******************************************************************************/

/* CSX scan method settings */
#define ADC_1_CSX_SCANSPEED_DIVIDER        (2u)
#define ADC_1_CSX_COMMON_TX_CLK_EN         (0u)
#define ADC_1_CSX_TX_CLK_SOURCE            (ADC_1_CLK_SOURCE_PRSAUTO)
#define ADC_1_CSX_TX_CLK_DIVIDER           (7u)
#define ADC_1_CSX_MAX_FINGERS              (1u)
#define ADC_1_CSX_MAX_LOCAL_PEAKS          (5u)
#define ADC_1_CSX_IDAC_AUTOCAL_EN          (0u)
#define ADC_1_CSX_IDAC_BITS_USED           (7u)
#define ADC_1_CSX_RAWCOUNT_CAL_LEVEL       (40u)
#define ADC_1_CSX_IDAC_GAIN                (ADC_1_IDAC_GAIN_MEDIUM)
#define ADC_1_CSX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define ADC_1_CSX_MULTIPHASE_TX_EN         (0u)
#define ADC_1_CSX_MAX_TX_PHASE_LENGTH      (0u)

/* CSX settings - CSDv2 */
#define ADC_1_CSX_ANALOG_STARTUP_DELAY_US  (0u)
#define ADC_1_CSX_AUTO_ZERO_EN             (0u)
#define ADC_1_CSX_AUTO_ZERO_TIME           (15u)
#define ADC_1_CSX_FINE_INIT_TIME           (4u)
#define ADC_1_CSX_NOISE_METRIC_EN          (0u)
#define ADC_1_CSX_NOISE_METRIC_TH          (1u)
#define ADC_1_CSX_INIT_SWITCH_RES          (ADC_1_INIT_SW_RES_MEDIUM)
#define ADC_1_CSX_SCAN_SWITCH_RES          (ADC_1_SCAN_SW_RES_LOW)
#define ADC_1_CSX_INIT_SHIELD_SWITCH_RES   (ADC_1_INIT_SHIELD_SW_RES_HIGH)
#define ADC_1_CSX_SCAN_SHIELD_SWITCH_RES   (ADC_1_SCAN_SHIELD_SW_RES_LOW)


/*******************************************************************************
* Global Parameter Definitions
*******************************************************************************/

/* RAM Global Parameters Definitions */


/* RAM Sensor Parameters Definitions */

/*******************************************************************************
* ADC Specific Macros
*******************************************************************************/
#define ADC_1_ADC_RES8BIT                  (8u)
#define ADC_1_ADC_RES10BIT                 (10u)

#define ADC_1_ADC_FULLRANGE_MODE           (0u)
#define ADC_1_ADC_VREF_MODE                (1u)

#define ADC_1_ADC_EN                       (1u)
#define ADC_1_ADC_STANDALONE_EN            (1u)
#define ADC_1_ADC_TOTAL_CHANNELS           (10u)
#define ADC_1_ADC_RESOLUTION               (ADC_1_ADC_RES10BIT)
#define ADC_1_ADC_AMUXB_INPUT_EN           (0u)
#define ADC_1_ADC_SELECT_AMUXB_CH          (0u)
#define ADC_1_ADC_AZ_EN                    (1Lu)
#define ADC_1_ADC_AZ_TIME                  (5u)
#define ADC_1_ADC_VREF_MV                  (2133u)
#define ADC_1_ADC_GAIN                     (17Lu)
#define ADC_1_ADC_IDAC_DEFAULT             (2u)
#define ADC_1_ADC_MODCLK_DIV_DEFAULT       (1u)
#define ADC_1_ADC_MEASURE_MODE             (ADC_1_ADC_FULLRANGE_MODE)

/*******************************************************************************
* Built-In Self-Test Configuration
*******************************************************************************/
#define ADC_1_SELF_TEST_EN                   (0Lu)
#define ADC_1_TST_GLOBAL_CRC_EN              (0Lu)
#define ADC_1_TST_WDGT_CRC_EN                (0Lu)
#define ADC_1_TST_BSLN_DUPLICATION_EN        (0Lu)
#define ADC_1_TST_BSLN_RAW_OUT_RANGE_EN      (0Lu)
#define ADC_1_TST_SNS_SHORT_EN               (0Lu)
#define ADC_1_TST_SNS2SNS_SHORT_EN           (0Lu)
#define ADC_1_TST_SNS_CAP_EN                 (0Lu)
#define ADC_1_TST_SH_CAP_EN                  (0Lu)
#define ADC_1_TST_EXTERNAL_CAP_EN            (0Lu)
#define ADC_1_TST_INTERNAL_CAP_EN            (0Lu)
#define ADC_1_TST_VDDA_EN                    (0Lu)
#define ADC_1_TST_FINE_INIT_TIME             (10Lu)


#endif /* CY_CAPSENSE_ADC_1_CONFIGURATION_H */


/* [] END OF FILE */
