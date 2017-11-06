/***************************************************************************//**
* \file ADC_1_Adc.c
* \version 4.0
*
* \brief
*   This file provides implementation for the ADC module of the CapSense 
*   component.
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
#include <cytypes.h>
#include "CyLib.h"

#include "ADC_1_Structure.h"
#include "ADC_1_Configuration.h"
#include "ADC_1_Adc.h"
#include "ADC_1_ISR.h"

#if (ADC_1_DISABLE == ADC_1_ADC_STANDALONE_EN)
    #include "ADC_1_Sensing.h"
#endif /* (ADC_1_DISABLE == ADC_1_ADC_STANDALONE_EN) */

#if (ADC_1_ENABLE == ADC_1_SELF_TEST_EN)
    #include "ADC_1_SelfTest.h"
#endif

#if (ADC_1_ADC_EN)

static uint8 ADC_1_initVar;
uint16 ADC_1_Vref_mV = ADC_1_ADC_VREF_MV;
    
/*******************************************************************************
* Module local function declarations
*******************************************************************************/
/**
* \if SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

static void ADC_1_SetNonDedicatedAdcChannel(uint8 chId, uint32 state);
#if (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
    void ADC_1_SetModClkClockDivider(uint32 modClk);
#endif  /* (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN) */

/** \}
* \endif */

/*******************************************************************************
* Local definition
*******************************************************************************/
#define ADC_1_INIT_DONE   (1u)
#define ADC_1_INIT_NEEDED (0u)
#define ADC_1_CAL_WATCHDOG_CYCLES_NUM   (0x0000FFFFLu)

#if (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
    /*******************************************************************************
    * Function Name: ADC_1_Start
    ****************************************************************************//**
    * \if SECTION_STANDALONE_ADC
    * \brief
    *   Configures the hardware and performs calibration.
    *
    * \details
    *   Configures the hardware and performs calibration.
    * \endif
    *
    *******************************************************************************/
    void ADC_1_Start(void)
    {
        ADC_1_ClearAdcChannels();
        
        if (ADC_1_INIT_DONE != ADC_1_initVar)
        {
            ADC_1_DsInitialize();
        }
        ADC_1_ConfigAdcResources();
        (void) ADC_1_Calibrate();
        while(ADC_1_IsBusy() != ADC_1_STATUS_IDLE)
        {
        }
    }

    /*******************************************************************************
    * Function Name: ADC_1_Sleep
    ****************************************************************************//**
    * \if SECTION_STANDALONE_ADC
    * \brief
    *  Prepares the component for deep sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates, 
    *  this function shall be used to prepare the component to enter deep sleep.
    * \endif
    *
    *******************************************************************************/
    void ADC_1_Sleep(void)
    {
    }


    /*******************************************************************************
    * Function Name: ADC_1_Wakeup
    ****************************************************************************//**
    * \if SECTION_STANDALONE_ADC
    * \brief
    *  This function resumes the component after sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates,
    *  this function shall be used to resume the component after exiting deep sleep.
    * \endif
    *
    *******************************************************************************/
    void ADC_1_Wakeup(void)
    {
    }
#endif  /* (ADC_1_ENABLE != ADC_1_ADC_STANDALONE_EN) */

/*******************************************************************************
* Function Name: ADC_1_SetNonDedicatedAdcChannel
****************************************************************************//**
*
* \brief
*   Sets the non dedicated channel to the given state.
*
* \details
*   Connects/disconnects the pin and the analog muxbus B. Sets the drive mode
*   of the pin as well.
*
* \param chId  The ID of the non dedicated channel to be set.
* \param state The state in which the channel is to be put:
*         - (0) ADC_1_CHAN_DISCONNECT
*         - (1) ADC_1_CHAN_CONNECT
*
*******************************************************************************/
static void ADC_1_SetNonDedicatedAdcChannel(uint8 chId, uint32 state)
{
    ADC_1_FLASH_IO_STRUCT const *ptr2adcIO;
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 pinHSIOMShift;
    uint32 pinModeShift;
    uint32 tmpVal;

    ptr2adcIO = &ADC_1_adcIoList[chId];
    pinHSIOMShift = (uint32)ptr2adcIO->hsiomShift;
    pinModeShift = (uint32)ptr2adcIO->shift;
    
    /* Clear port connections. */
    tmpVal = CY_GET_REG32(ptr2adcIO->hsiomPtr);
    tmpVal &= ~(ADC_1_HSIOM_PRTSEL_MASK << pinHSIOMShift);
    
    interruptState = CyEnterCriticalSection();

    switch (state)
    {
    case ADC_1_CHAN_CONNECT:
        
        /* Connect AMuxBusB to the selected port. */
        CY_SET_REG32(ptr2adcIO->hsiomPtr, (tmpVal | (ADC_1_HSIOM_PRTSEL_AMUXBUSB << pinHSIOMShift)));
    
        /* Update port configuration register (drive mode) to HiZ output, buffered input */
        newRegisterValue = CY_GET_REG32(ptr2adcIO->pcPtr);
        newRegisterValue &= ~(ADC_1_GPIO_PC_MASK << pinModeShift);
        newRegisterValue |= (ADC_1_GPIO_PC_INPUT << pinModeShift);
        CY_SET_REG32(ptr2adcIO->pcPtr, newRegisterValue);
    
        /* Cmod and Ctank are not typical GPIO, require CSD setting. */
        if (0u != ((uint32)(ptr2adcIO->hsiomPtr) & ADC_1_SW_CMOD_PORT_MASK))
        {
            if (ADC_1_SW_CTANK_PINSHIFT == pinModeShift)
            {
                CY_SET_REG32(ADC_1_SW_DSI_SEL_PTR, \
                    ADC_1_SW_DSI_CTANK);  
            }
            else if (ADC_1_SW_CMOD_PINSHIFT == pinModeShift)
            {
                CY_SET_REG32(ADC_1_SW_DSI_SEL_PTR, \
                    ADC_1_SW_DSI_CMOD);  
            }
            else { /* No action */ }
        }
        break;
        
    /* Disconnection is a safe default state. Fall-through is intentional. */
    case ADC_1_CHAN_DISCONNECT:
    default:
        /* tmpVal contains cleared hsiom state. */
        CY_SET_REG32(ptr2adcIO->hsiomPtr, tmpVal);
    
        /* Update port configuration register (drive mode) to HiZ input/output by clearing PC*/
        newRegisterValue = CY_GET_REG32(ptr2adcIO->pcPtr);
        newRegisterValue &= ~(ADC_1_GPIO_PC_MASK << pinModeShift);
        CY_SET_REG32(ptr2adcIO->pcPtr, newRegisterValue);
        
        /* Cmod and Ctank are not typical GPIO, require CSD setting. */
        if (0u != ((uint32)(ptr2adcIO->hsiomPtr) & ADC_1_SW_CMOD_PORT_MASK))
        {
            if ((ADC_1_SW_CTANK_PINSHIFT == pinModeShift) ||
                (ADC_1_SW_CMOD_PINSHIFT == pinModeShift ))
            {
                CY_SET_REG32(ADC_1_SW_DSI_SEL_PTR, 0u);  
            }
        }
        break;
    }

    CyExitCriticalSection(interruptState);
    
    /* Set logic 0 to port data register */
    tmpVal = CY_GET_REG32(ptr2adcIO->drPtr);
    tmpVal &= (uint32)~(uint32)((uint32)1u << ptr2adcIO->drShift);
    CY_SET_REG32(ptr2adcIO->drPtr, tmpVal);
}


/*******************************************************************************
* Function Name: ADC_1_SetAdcChannel
****************************************************************************//**
*
* \brief
*   Sets the given channel to the given state.
*
* \details
*   Connects/disconnects the pin and the analog muxbus B.  Sets the drive mode
*   of the pin as well.
*
* \param chId  The ID of the channel to be set.
* \param state The state in which the channel is to be put:
*         - (0) ADC_1_CHAN_DISCONNECT
*         - (1) ADC_1_CHAN_CONNECT
*
*******************************************************************************/
void ADC_1_SetAdcChannel(uint8 chId, uint32 state)
{
    #if (0u != ADC_1_ADC_AMUXB_INPUT_EN)
        if(ADC_1_ADC_SELECT_AMUXB_CH != chId)
        {
            ADC_1_SetNonDedicatedAdcChannel(chId, state);
        }
    #else
        ADC_1_SetNonDedicatedAdcChannel(chId, state);   
    #endif /* (0u != ADC_1_ADC_AMUXB_INPUT_EN) */
}


/*******************************************************************************
* Function Name: ADC_1_ConfigAdcResources
****************************************************************************//**
*
* \brief
*   Configures the CSD block to be used as an ADC.
*
* \details
*   Configures the IDACB, internal switches, REFGEN, HSCOMP, enables CSD
*   block interrupt and set interrupt vector to ADC sensing method.
*
*******************************************************************************/
void ADC_1_ConfigAdcResources(void)
{   
    uint8  interruptState;
    uint32 newRegValue;

    /* Configure clocks */
    #if (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
        ADC_1_SetModClkClockDivider(ADC_1_ADC_MODCLK_DIV_DEFAULT);
    #else
        ADC_1_SsSetModClkClockDivider(ADC_1_ADC_MODCLK_DIV_DEFAULT);
    #endif /* (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN) */

    CY_SET_REG32(ADC_1_SENSE_PERIOD_PTR, (ADC_1_SENSE_DIV_DEFAULT - 1u));

    /* Configure the IDAC */
    CY_SET_REG32(ADC_1_CONFIG_PTR, ADC_1_CONFIG_DEFAULT);
    CY_SET_REG32(ADC_1_IDACB_PTR, ADC_1_IDACB_CONFIG | ADC_1_dsRam.adcIdac);

    /* Configure AZ Time */
    CY_SET_REG32(ADC_1_SEQ_TIME_PTR, (uint32)(ADC_1_SEQ_TIME_DEFAUL - 1u));

    CY_SET_REG32(ADC_1_CSDCMP_PTR, 0);
    CY_SET_REG32(ADC_1_SW_DSI_SEL_PTR, 0);
    
    CY_SET_REG32(ADC_1_SENSE_DUTY_PTR, 0);
    CY_SET_REG32(ADC_1_SEQ_INIT_CNT_PTR, 1u);
    CY_SET_REG32(ADC_1_SEQ_NORM_CNT_PTR, 2u);
    
    /* Configure the block-level routing */
    CY_SET_REG32(ADC_1_SW_HS_P_SEL_PTR, ADC_1_SW_HSP_DEFAULT);
    CY_SET_REG32(ADC_1_SW_HS_N_SEL_PTR, ADC_1_SW_HSN_DEFAULT);
    CY_SET_REG32(ADC_1_SW_SHIELD_SEL_PTR, ADC_1_SW_SHIELD_DEFAULT);
    CY_SET_REG32(ADC_1_SW_CMP_P_SEL_PTR, ADC_1_SW_CMPP_DEFAULT);
    CY_SET_REG32(ADC_1_SW_CMP_N_SEL_PTR, ADC_1_SW_CMPN_DEFAULT);
    CY_SET_REG32(ADC_1_SW_FW_MOD_SEL_PTR, ADC_1_SW_FWMOD_DEFAULT);
    CY_SET_REG32(ADC_1_SW_FW_TANK_SEL_PTR, ADC_1_SW_FWTANK_DEFAULT);
    CY_SET_REG32(ADC_1_SW_REFGEN_SEL_PTR, ADC_1_SW_REFGEN_DEFAULT);

    interruptState = CyEnterCriticalSection();
    newRegValue = CY_GET_REG32(ADC_1_SW_BYP_SEL_PTR);
    newRegValue |= ADC_1_SW_BYP_DEFAULT;
    CY_SET_REG32(ADC_1_SW_BYP_SEL_PTR, newRegValue);
    CyExitCriticalSection(interruptState);
    
    /* Config RefGen.  The routing of the HS_N and AMUXBUF switches depend on RefGen. */
    #if (ADC_1_CYDEV_VDDA_MV < ADC_1_LVTHRESH)

        CY_SET_REG32(ADC_1_REFGEN_PTR, ADC_1_REFGEN_LV);
        CY_SET_REG32(ADC_1_SW_AMUXBUF_SEL_PTR, ADC_1_SW_AMUBUF_LV);
        CY_SET_REG32(ADC_1_AMBUF_PTR, ADC_1_AMBUF_LV);
    #else
        CY_SET_REG32(ADC_1_REFGEN_PTR, ADC_1_REFGEN_NORM);
        CY_SET_REG32(ADC_1_SW_AMUXBUF_SEL_PTR, ADC_1_SW_AMUBUF_NORM);
    #endif /* ADC_1__CYDEV_VDDA_MV < ADC_1_LVTHRESH */
    
    /* Configure HSCOMP */
    CY_SET_REG32(ADC_1_HSCMP_PTR, ADC_1_HSCMP_AZ_DEFAULT);
    
    /* Set the ISR vector */
    ADC_1_ISR_StartEx(&ADC_1_IntrHandler);
    
    /* Component is initialized */
    ADC_1_initVar = ADC_1_INIT_DONE;
}


/*******************************************************************************
* Function Name: ADC_1_StartAdcFSM
****************************************************************************//**
*
* \brief
*   Starts the CSD state machine with correct parameters to initialize an ADC
*   conversion.
*
* \details
*   Starts the CSD state machine with correct parameters to initialize an ADC
*   conversion.
*
* \param measureMode The FSM mode:
*        - (0) ADC_1_MEASMODE_OFF    
*        - (1) ADC_1_MEASMODE_VREF   
*        - (2) ADC_1_MEASMODE_VREFBY2
*        - (3) ADC_1_MEASMODE_VIN    
*
*******************************************************************************/
void ADC_1_StartAdcFSM(uint32 measureMode)
{
    uint32 tmpStartVal;

    /* Set the mode and acquisition time */
    CY_SET_REG32(ADC_1_ADC_CTL_PTR, (measureMode | (ADC_1_ACQUISITION_BASE - 1u)));
    
    if(ADC_1_MEASMODE_VREF == measureMode)
    {
        tmpStartVal = 
            ADC_1_FSMSETTING_AZSKIP_DEFAULT    |
            ADC_1_FSMSETTING_DSIIGNORE   |
            ADC_1_FSMSETTING_NOABORT     |
            ADC_1_FSMSETTING_SEQMODE     |
            ADC_1_FSMSETTING_START;
    }
    else if (ADC_1_MEASMODE_OFF == measureMode)
    {
        tmpStartVal = ADC_1_FSMSETTING_ABORT;
    }
    /* This setting is used for both MEASMODE_VREFBY2 and MEASMODE_VIN */
    else
    {
        tmpStartVal = 
            ADC_1_FSMSETTING_AZSKIP_DEFAULT    |
            ADC_1_FSMSETTING_DSIIGNORE   |
            ADC_1_FSMSETTING_NOABORT     |
            ADC_1_FSMSETTING_SEQMODE     |
            ADC_1_FSMSETTING_START;
    }
    
    /* Enable HSComp */
    CY_SET_REG32(ADC_1_SEQ_START_PTR, tmpStartVal);
}


/*******************************************************************************
* Function Name: ADC_1_AdcCaptureResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from CapSense mode, and sets it into ADC mode.
*
* \details
*   Releases CSD resources from CapSense mode, and sets it into ADC mode.
*
* \return     The function returns cystatus of its operation.
*   - CYRET_LOCKED  - The CSD hardware is in-use by CapSense, and could not be released.
*   - CYRET_SUCCESS - Block is configured for ADC use.
*
*******************************************************************************/
cystatus ADC_1_AdcCaptureResources(void)
{
    cystatus tmpStatus = CYRET_SUCCESS;

    #if !(ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
        tmpStatus = ADC_1_SsReleaseResources();

        if (ADC_1_INIT_NEEDED == ADC_1_initVar)
        {
            if(CYRET_SUCCESS == tmpStatus) 
            {
                ADC_1_ConfigAdcResources();
            }
            else
            {
                tmpStatus = CYRET_LOCKED;
            }
        }
    #else
        if (ADC_1_INIT_NEEDED == ADC_1_initVar)
        {
            ADC_1_ConfigAdcResources();
        } 
    #endif /* !(ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN) */

    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_1_AdcReleaseResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from ADC mode.
*
* \details
*   Releases CSD resources from ADC mode.
*
* \return     The function returns cystatus of its operation.
*   CYRET_SUCCESS   Block resources no longer in use.
*
*******************************************************************************/
cystatus ADC_1_AdcReleaseResources(void)
{
    uint8  interruptState;
    uint32 newRegValue;
    
    if (ADC_1_INIT_DONE == ADC_1_initVar)
    {
        /* If the FSM is running, shut it down. */
        if(ADC_1_STATUS_IDLE != (ADC_1_dsRam.adcStatus
            & ADC_1_STATUS_FSM_MASK))
        {
            ADC_1_StartAdcFSM(ADC_1_MEASMODE_OFF);
            ADC_1_SetAdcChannel((ADC_1_dsRam.adcStatus
                & (uint8)(ADC_1_STATUS_LASTCHAN_MASK)),
                                            ADC_1_CHAN_DISCONNECT);
            ADC_1_dsRam.adcStatus = ADC_1_STATUS_IDLE;
        }
        
        /* Disable the subblocks. */
        CY_SET_REG32(ADC_1_IDACB_PTR, 0);
        CY_SET_REG32(ADC_1_REFGEN_PTR, 0);
        CY_SET_REG32(ADC_1_AMBUF_PTR,  0);
        CY_SET_REG32(ADC_1_HSCMP_PTR,  0);
        
        /* Reset the block-level routing */
        CY_SET_REG32(ADC_1_SW_HS_P_SEL_PTR,    0);
        CY_SET_REG32(ADC_1_SW_HS_N_SEL_PTR,    0);
        CY_SET_REG32(ADC_1_SW_SHIELD_SEL_PTR,  0);
        CY_SET_REG32(ADC_1_SW_CMP_P_SEL_PTR,   0);
        CY_SET_REG32(ADC_1_SW_CMP_N_SEL_PTR,   0);
        CY_SET_REG32(ADC_1_SW_FW_MOD_SEL_PTR,  0);
        CY_SET_REG32(ADC_1_SW_FW_TANK_SEL_PTR, 0);
        
    
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(ADC_1_SW_BYP_SEL_PTR);
        newRegValue &= (uint32)(~ADC_1_SW_BYP_DEFAULT);
        CY_SET_REG32(ADC_1_SW_BYP_SEL_PTR, newRegValue);
        CyExitCriticalSection(interruptState);
        
         /* Disconnect all ADC channels */
        ADC_1_ClearAdcChannels();
        
        ADC_1_initVar = ADC_1_INIT_NEEDED;
    }
    
    return CYRET_SUCCESS;
}


/*******************************************************************************
* Function Name: ADC_1_StartConvert
****************************************************************************//**
*
* \brief
*  Initializes the hardware and initiates an analog-to-digital conversion on the 
*  selected input channel.
*
* \details
*  Initializes the hardware and initiates an analog-to-digital conversion on the 
*  selected input channel. This API only initiates a conversion and does not 
*  wait for the conversion to be completed, therefore the
*  ADC_1_IsBusy() API must be used to check the
*  status and ensure that the conversion is complete prior to reading the result,
*  starting a new conversion with the same or a different channel or reconfiguring
*  the hardware for different functionality. 
*
* \param chId 
*  The ID of the channel to be converted. 
*
* \return 
*  The function returns cystatus of its operation.
*    - CYRET_SUCCESS - A conversion has started.
*    - CYRET_LOCKED - The hardware is already in-use by a previously initialized 
*      conversion or other functionality. No new conversion is started by this API.
*    - CYRET_BAD_PARAM - An invalid channel Id. No conversion is started.
*
*******************************************************************************/
cystatus ADC_1_StartConvert(uint8 chId)
{
    uint32 tmpStatus = CYRET_SUCCESS;
    
    /* If CapSense, try to Capture resources */
    #if (ADC_1_DISABLE == ADC_1_ADC_STANDALONE_EN)
        tmpStatus = ADC_1_AdcCaptureResources();

        if (CYRET_SUCCESS == tmpStatus)
        {
    #else /* Otherwise, configure resources if needed. */
        if (ADC_1_INIT_NEEDED == ADC_1_initVar)
        {
            ADC_1_ConfigAdcResources();
        } 
    #endif /* (ADC_1_DISABLE == ADC_1_ADC_STANDALONE_EN) */
    
        if(chId >= ADC_1_ADC_TOTAL_CHANNELS)
        {
            tmpStatus = CYRET_BAD_PARAM;
        }
        if (CYRET_SUCCESS == tmpStatus)
        {
            if(ADC_1_STATUS_IDLE != (ADC_1_dsRam.adcStatus & ADC_1_STATUS_FSM_MASK))
            {
                tmpStatus = CYRET_LOCKED;
            }
            
            if(CYRET_SUCCESS == tmpStatus)
            {
                /* Set Component Status */
                ADC_1_dsRam.adcStatus = (ADC_1_STATUS_CONVERTING | chId);
                
                /* Connect desired input */
                ADC_1_SetAdcChannel(chId, ADC_1_CHAN_CONNECT);
                    
                /* Set interrupt request */
                CY_SET_REG32(ADC_1_INTR_MASK_PTR, ADC_1_INTERRUPT_SET);
                ADC_1_StartAdcFSM(ADC_1_MEASMODE_VIN);
            }
        }
    #if (ADC_1_DISABLE == ADC_1_ADC_STANDALONE_EN)
        }
    #endif /* (ADC_1_DISABLE == ADC_1_ADC_STANDALONE_EN) */
    
    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_1_IsBusy
****************************************************************************//**
*
* \brief
*   The function returns the status of the ADC's operation.
*
* \details
*   The function returns the status of the ADC's operation. A new conversion or 
*   calibration must not be started unless the ADC is in the IDLE state.
*
* \return     
*  The function returns the status of the ADC's operation.
*    - ADC_1_STATUS_IDLE - The ADC is not busy, 
*       a new conversion can be initiated.
*    - ADC_1_STATUS_CONVERTING - A previously 
*       initiated conversion is in progress.
*    - ADC_1_STATUS_CALIBPH1 - The ADC is in the 
*      first phase (of 3) of calibration.
*    - ADC_1_STATUS_CALIBPH2 - The ADC is in the 
*      second phase (of 3) of calibration.
*    - ADC_1_STATUS_CALIBPH3 - The ADC is in the 
*      third phase (of 3) of calibration.
*    - ADC_1_STATUS_OVERFLOW - The most recent 
*      measurement caused an overflow. The root cause of the overflow may be 
*	   the previous calibration values being invalid or the VDDA setting in cydwr 
*      and hardware do not match. Perform re-calibration or set the
*	   appropriate VDDA value in cydwr to avoid this error condition.
*
*******************************************************************************/
uint8 ADC_1_IsBusy(void)
{
    uint8 tmpStatus;
    if (0u != (ADC_1_ADC_RES_REG & ADC_1_ADC_RES_OVERFLOW_MASK))
    {
        tmpStatus = ADC_1_STATUS_OVERFLOW;
    }
    else
    {
        tmpStatus = (uint8)((*(volatile uint8 *)&ADC_1_dsRam.adcStatus) & ADC_1_STATUS_FSM_MASK);
    }
    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_1_ReadResult_mVolts
****************************************************************************//**
*
* \brief
*  This is a blocking API. It initiates a conversion, waits for completion and  
*  returns the result.
*
* \details
*  This is a blocking API. Internally, it starts a conversion using 
*  ADC_1_StartConvert(), checks the status using
*  ADC_1_IsBusy(), waits until the conversion is
*  completed and returns the result.
*
* \param chId  
*  The ID of the channel to be measured 
*
* \return
*  The function returns voltage in milli-volts or
*  ADC_1_VALUE_BAD_RESULT if:
*   - chId is invalid
*   - the ADC conversion is not started
*   - the ADC conversion watch-dog triggered.
*
*******************************************************************************/
uint16 ADC_1_ReadResult_mVolts(uint8 chId)
{
    cystatus convertStatus;
    uint16 tmpValue;
    uint32 watchdogAdcCounter;

    convertStatus = ADC_1_StartConvert(chId);
    if (CYRET_SUCCESS == convertStatus)
    {
        /* Initialize Watchdog Counter with time interval which is enough to ADC conversion is completed */
        watchdogAdcCounter = ADC_1_CAL_WATCHDOG_CYCLES_NUM;
        while ((ADC_1_IsBusy() != ADC_1_STATUS_IDLE) &&
               (0u != watchdogAdcCounter))
        {
            /* Wait until conversion complete and decrement Watchdog Counter to prevent unending loop */
            watchdogAdcCounter--;
        }
        if (0u != watchdogAdcCounter)
        {
            tmpValue = ADC_1_GetResult_mVolts(chId);
        }
        else
        {
            tmpValue = (uint16) ADC_1_VALUE_BAD_RESULT;
        }
    }
    else
    {
        tmpValue = (uint16) ADC_1_VALUE_BAD_RESULT;
    }

    return tmpValue;
}


/*******************************************************************************
* Function Name: ADC_1_GetResult_mVolts
****************************************************************************//**
*
* \brief
*  This API does not perform an ADC conversion and returns the last valid result
*  for the specified channel.
*
* \details
*  Returns the last valid result from the data structure for the specified channel.
*  This function can be used to read a previous result of any channel even if the
*  ADC is busy or a conversion is in progress. However, it is highly recommended
*  not to use this function with a channel that is in an active conversion. 
*
* \param chId  
*  The ID of the channel to be measured 
*
* \return     
*  The function returns a voltage in milli-volts or
*  ADC_1_VALUE_BAD_CHAN_ID if chId is invalid.
*
*******************************************************************************/
uint16 ADC_1_GetResult_mVolts(uint8 chId)
{
    uint32 tmpRetVal = ADC_1_VALUE_BAD_CHAN_ID;
    
    if(chId < ADC_1_ADC_TOTAL_CHANNELS)
    {
        tmpRetVal = ADC_1_dsRam.adcResult[chId];
    }
    return (uint16)tmpRetVal;
}


/*******************************************************************************
* Function Name: ADC_1_Calibrate
****************************************************************************//**
*
* \brief
*  Performs calibration of the ADC module.
*
* \details
*  Performs calibration for the ADC to identify the appropriate hardware configuration 
*  to produce accurate results. It is recommended to run the calibration 
*  periodically (for example every 10 seconds) for accuracy and compensations. 
*
* \return  
*  The function returns cystatus of its operation.
*    - CYRET_SUCCESS - The block is configured for the ADC use.
*    - CYRET_LOCKED - The hardware is already in-use by a previously initialized 
*      conversion or other functionality. No new conversion is started by this API.
*   
*******************************************************************************/
cystatus ADC_1_Calibrate(void)
{
    uint32 tmpStatus;
    uint32 watchdogAdcCounter;
    #if (ADC_1_ENABLE == ADC_1_CALIBRATE_VREF)
        uint8 tmpFlashByte0;
        uint8 tmpFlashByte1;
        uint32 tmpVrefCal;
    #endif /* (ADC_1_ENABLE == ADC_1_CALIBRATE_VREF) */

    tmpStatus = ADC_1_AdcCaptureResources();
    if(ADC_1_STATUS_IDLE != (ADC_1_dsRam.adcStatus
        & ADC_1_STATUS_FSM_MASK) )
    {
        tmpStatus = CYRET_LOCKED;
    }
    
    if (CYRET_SUCCESS == tmpStatus)
    {
        #if (ADC_1_ENABLE == ADC_1_CALIBRATE_VREF)
            tmpFlashByte0 = CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1);
            tmpFlashByte1 = CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM2);
            tmpVrefCal = (uint32)tmpFlashByte0 | (((uint32)tmpFlashByte1) << 8u);
            tmpVrefCal = (tmpVrefCal * (uint32)(ADC_1_ADC_VREF_MV)) \
                         / (uint32)(ADC_1_VREFCALIB_BASE);
            ADC_1_Vref_mV = (uint16)tmpVrefCal;
        #endif /* (ADC_1_ENABLE == ADC_1_CALIBRATE_VREF) */

        ADC_1_dsRam.adcIdac = (uint8)ADC_1_ADC_IDAC_DEFAULT;
        CY_SET_REG32(ADC_1_IDACB_PTR, ADC_1_IDACB_CONFIG \
                     | ADC_1_dsRam.adcIdac);
        
        ADC_1_dsRam.adcStatus = (ADC_1_STATUS_CALIBPH1);
        CY_SET_REG32(ADC_1_INTR_MASK_PTR, ADC_1_INTERRUPT_SET);
        ADC_1_StartAdcFSM(ADC_1_MEASMODE_VREF);

        /* Global CRC update */
        #if (ADC_1_ENABLE ==ADC_1_TST_GLOBAL_CRC_EN)
            ADC_1_DsUpdateGlobalCrc();
        #endif /* (ADC_1_ENABLE == ADC_1_TST_GLOBAL_CRC_EN) */
    }
    
    /* Initialize Watchdog Counter with time interval which is enough to ADC calibration is completed */
    watchdogAdcCounter = ADC_1_CAL_WATCHDOG_CYCLES_NUM;
    while (((*(volatile uint8 *)&ADC_1_dsRam.adcStatus & ADC_1_STATUS_FSM_MASK)
            != 0u) &&  (0u != watchdogAdcCounter))
    {
        /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
        watchdogAdcCounter--;
    }
    
    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_1_Initialize
****************************************************************************//**
*
* \brief
*   Configures the hardware to ADC mode and begins a calibration.
*
* \details
*   Configures the hardware to ADC mode and begins a calibration.
*
*******************************************************************************/
void ADC_1_Initialize(void)
{
    ADC_1_ConfigAdcResources();
    (void) ADC_1_Calibrate();
}

/*******************************************************************************
* Function Name: ADC_1_Stop
****************************************************************************//**
*
* \brief
*   Disables the hardware sub-blocks that are in use while in the ADC mode,
*   and frees the routing.
*
* \details
*   This function stops the component operation, no ADC conversion can be 
*   initiated when the component is stopped. Once stopped, the hardware block
*   may be reconfigured by the application program for any other special usage. 
*   The ADC operation can be resumed by calling the 
*   ADC_1_Resume() function or the component can
*   be reset by calling the ADC_1_Start() function. 
*   This function should be called when no ADC conversion is in progress.
*
*******************************************************************************/
void ADC_1_Stop(void)
{
    #if (ADC_1_ENABLE != ADC_1_ADC_STANDALONE_EN)
        (void) ADC_1_AdcReleaseResources();
    #endif /* (ADC_1_ENABLE != ADC_1_ADC_STANDALONE_EN) */
    ADC_1_initVar = ADC_1_INIT_NEEDED;
}


/*******************************************************************************
* Function Name: ADC_1_Resume
****************************************************************************//**
*
* \brief
*   Resumes the ADC operation after a stop call.
*
* \details
*   This function resumes the ADC operation if the operation is stopped 
*   previously by the ADC_1_Stop() API. 
*
*******************************************************************************/
void ADC_1_Resume(void)
{
    ADC_1_Initialize();
}


/*******************************************************************************
* Function Name: ADC_1_ClearAdcChannels
****************************************************************************//**
*
* \brief
*  Resets all the ADC channels to disconnected state.
*
* \details
*   The function goes through all the ADC channels and disconnects the pin 
*   and the analog muxbus B.  Sets the drive mode of the pin as well.
* 
*******************************************************************************/
void ADC_1_ClearAdcChannels(void)
{
    uint32 chId;

    for (chId = 0u; chId < ADC_1_ADC_TOTAL_CHANNELS; chId++)
    {
        ADC_1_SetAdcChannel((uint8)chId, ADC_1_CHAN_DISCONNECT);
    }   
}

#if (ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN)
    /*******************************************************************************
    * Function Name: ADC_1_SetModClkClockDivider
    ****************************************************************************//**
    *
    * \brief
    *   Sets the divider values for the modulator clock and then starts
    *   the modulator clock.
    *
    * \details
    *   It is not recommended to call this function directly by the application layer.
    *   It is used by initialization to enable the clocks.
    *
    * \param
    *   modClk The divider value for the modulator clock.
    *
    *******************************************************************************/
    void ADC_1_SetModClkClockDivider(uint32 modClk)
    {
        /*  Stop modulator clock   */
        CY_SET_REG32(ADC_1_MODCLK_CMD_PTR,
                     ((uint32)ADC_1_ModClk__DIV_ID <<
                     ADC_1_MODCLK_CMD_DIV_SHIFT)|
                     ((uint32)ADC_1_MODCLK_CMD_DISABLE_MASK));

        /*
         * Set divider value for sense modClk.
         * 1u is subtracted from modClk because Divider register value 0 corresponds
         * to dividing by 1.
         */
        CY_SET_REG32(ADC_1_MODCLK_DIV_PTR, ((modClk - 1u) << 8u));

        /*  Check whether previous modulator clock start command has finished. */
        while(0u != (CY_GET_REG32(ADC_1_MODCLK_CMD_PTR) & ADC_1_MODCLK_CMD_ENABLE_MASK))
        {
            /*  Wait until previous modulator clock start command has finished. */
        }

        /*  Start modulator clock, aligned to HFCLK */
        CY_SET_REG32(ADC_1_MODCLK_CMD_PTR,
                     (uint32)(((uint32)ADC_1_ModClk__DIV_ID << ADC_1_MODCLK_CMD_DIV_SHIFT) |
                      ((uint32)ADC_1_ModClk__PA_DIV_ID << ADC_1_MODCLK_CMD_PA_DIV_SHIFT) |
                      ADC_1_MODCLK_CMD_ENABLE_MASK));
    }
#endif /* ADC_1_ENABLE == ADC_1_ADC_STANDALONE_EN */

#endif  /* #if ADC_1_ADC_EN */  


/* [] END OF FILE */
