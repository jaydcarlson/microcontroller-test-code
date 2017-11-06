/***************************************************************************//**
* \file ADC_1_Structure.c
* \version 4.0
*
* \brief
*   This file defines the data structure global variables and provides implementation
*   for the high-level and low-level APIs of the Data Structure module.
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

#include <string.h>
#include <cytypes.h>
#include "CyLib.h"
#include "ADC_1_Structure.h"

#if (ADC_1_ENABLE == ADC_1_ADC_EN)
    #include "ADC_1_Adc.h"
#endif /* (ADC_1_ENABLE == ADC_1_ADC_EN) */

/*******************************************************************************
* Define the RAM Data Structure variables and their init data in flash
*******************************************************************************/
/**
* \if SECTION_GLOBAL_VARIABLES
* \addtogroup group_global_variables
* \{
*/

/**
* The variable that contains the ADC_1 configuration, settings and scanning results.
* ADC_1_dsRam represents RAM Data Structure.
*/
ADC_1_RAM_STRUCT ADC_1_dsRam;
/** \}
* \endif */

/**
* \if SECTION_API_CONSTANTS
* \addtogroup group_api_constants
* \{
*/


/**
 *  The array of the pointers to the ADC input channels specific register.
 */
const ADC_1_FLASH_IO_STRUCT ADC_1_adcIoList[ADC_1_ADC_TOTAL_CHANNELS] =
{
    {
        (reg32 *)ADC_1_AdcInput__0__HSIOM,
        (reg32 *)ADC_1_AdcInput__0__PC,
        (reg32 *)ADC_1_AdcInput__0__DR,
        (reg32 *)ADC_1_AdcInput__0__PS,
        ADC_1_AdcInput__0__HSIOM_MASK,
        ADC_1_AdcInput__0__MASK,
        ADC_1_AdcInput__0__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__0__SHIFT,
        (uint8)ADC_1_AdcInput__0__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__1__HSIOM,
        (reg32 *)ADC_1_AdcInput__1__PC,
        (reg32 *)ADC_1_AdcInput__1__DR,
        (reg32 *)ADC_1_AdcInput__1__PS,
        ADC_1_AdcInput__1__HSIOM_MASK,
        ADC_1_AdcInput__1__MASK,
        ADC_1_AdcInput__1__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__1__SHIFT,
        (uint8)ADC_1_AdcInput__1__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__2__HSIOM,
        (reg32 *)ADC_1_AdcInput__2__PC,
        (reg32 *)ADC_1_AdcInput__2__DR,
        (reg32 *)ADC_1_AdcInput__2__PS,
        ADC_1_AdcInput__2__HSIOM_MASK,
        ADC_1_AdcInput__2__MASK,
        ADC_1_AdcInput__2__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__2__SHIFT,
        (uint8)ADC_1_AdcInput__2__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__3__HSIOM,
        (reg32 *)ADC_1_AdcInput__3__PC,
        (reg32 *)ADC_1_AdcInput__3__DR,
        (reg32 *)ADC_1_AdcInput__3__PS,
        ADC_1_AdcInput__3__HSIOM_MASK,
        ADC_1_AdcInput__3__MASK,
        ADC_1_AdcInput__3__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__3__SHIFT,
        (uint8)ADC_1_AdcInput__3__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__4__HSIOM,
        (reg32 *)ADC_1_AdcInput__4__PC,
        (reg32 *)ADC_1_AdcInput__4__DR,
        (reg32 *)ADC_1_AdcInput__4__PS,
        ADC_1_AdcInput__4__HSIOM_MASK,
        ADC_1_AdcInput__4__MASK,
        ADC_1_AdcInput__4__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__4__SHIFT,
        (uint8)ADC_1_AdcInput__4__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__5__HSIOM,
        (reg32 *)ADC_1_AdcInput__5__PC,
        (reg32 *)ADC_1_AdcInput__5__DR,
        (reg32 *)ADC_1_AdcInput__5__PS,
        ADC_1_AdcInput__5__HSIOM_MASK,
        ADC_1_AdcInput__5__MASK,
        ADC_1_AdcInput__5__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__5__SHIFT,
        (uint8)ADC_1_AdcInput__5__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__6__HSIOM,
        (reg32 *)ADC_1_AdcInput__6__PC,
        (reg32 *)ADC_1_AdcInput__6__DR,
        (reg32 *)ADC_1_AdcInput__6__PS,
        ADC_1_AdcInput__6__HSIOM_MASK,
        ADC_1_AdcInput__6__MASK,
        ADC_1_AdcInput__6__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__6__SHIFT,
        (uint8)ADC_1_AdcInput__6__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__7__HSIOM,
        (reg32 *)ADC_1_AdcInput__7__PC,
        (reg32 *)ADC_1_AdcInput__7__DR,
        (reg32 *)ADC_1_AdcInput__7__PS,
        ADC_1_AdcInput__7__HSIOM_MASK,
        ADC_1_AdcInput__7__MASK,
        ADC_1_AdcInput__7__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__7__SHIFT,
        (uint8)ADC_1_AdcInput__7__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__8__HSIOM,
        (reg32 *)ADC_1_AdcInput__8__PC,
        (reg32 *)ADC_1_AdcInput__8__DR,
        (reg32 *)ADC_1_AdcInput__8__PS,
        ADC_1_AdcInput__8__HSIOM_MASK,
        ADC_1_AdcInput__8__MASK,
        ADC_1_AdcInput__8__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__8__SHIFT,
        (uint8)ADC_1_AdcInput__8__SHIFT * 3u,
    },
    {
        (reg32 *)ADC_1_AdcInput__9__HSIOM,
        (reg32 *)ADC_1_AdcInput__9__PC,
        (reg32 *)ADC_1_AdcInput__9__DR,
        (reg32 *)ADC_1_AdcInput__9__PS,
        ADC_1_AdcInput__9__HSIOM_MASK,
        ADC_1_AdcInput__9__MASK,
        ADC_1_AdcInput__9__HSIOM_SHIFT,
        (uint8)ADC_1_AdcInput__9__SHIFT,
        (uint8)ADC_1_AdcInput__9__SHIFT * 3u,
    },
};


/** \}
* \endif */


/*******************************************************************************
* Function Name: ADC_1_DsInitialize
****************************************************************************//**
*
* \brief
*   This function initializes the Data Structure storage.
*
* \details
*   Configures the initial Adc datastructure members.
*
*******************************************************************************/
void ADC_1_DsInitialize(void)
{
    /* Reset RAM data structure content */
    (void)memset(&ADC_1_dsRam, 0, sizeof(ADC_1_dsRam));

    ADC_1_dsRam.adcResolution = ADC_1_ADC_RESOLUTION;
    ADC_1_dsRam.adcIdac = (uint8)(ADC_1_ADC_IDAC_DEFAULT);
}

/* [] END OF FILE */
