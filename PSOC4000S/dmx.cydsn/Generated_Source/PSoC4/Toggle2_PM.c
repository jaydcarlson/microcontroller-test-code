/*******************************************************************************
* File Name: Toggle2.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Toggle2.h"

static Toggle2_BACKUP_STRUCT  Toggle2_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Toggle2_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Toggle2_SUT.c usage_Toggle2_Sleep_Wakeup
*******************************************************************************/
void Toggle2_Sleep(void)
{
    #if defined(Toggle2__PC)
        Toggle2_backup.pcState = Toggle2_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Toggle2_backup.usbState = Toggle2_CR1_REG;
            Toggle2_USB_POWER_REG |= Toggle2_USBIO_ENTER_SLEEP;
            Toggle2_CR1_REG &= Toggle2_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Toggle2__SIO)
        Toggle2_backup.sioState = Toggle2_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Toggle2_SIO_REG &= (uint32)(~Toggle2_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Toggle2_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Toggle2_Sleep() for an example usage.
*******************************************************************************/
void Toggle2_Wakeup(void)
{
    #if defined(Toggle2__PC)
        Toggle2_PC = Toggle2_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Toggle2_USB_POWER_REG &= Toggle2_USBIO_EXIT_SLEEP_PH1;
            Toggle2_CR1_REG = Toggle2_backup.usbState;
            Toggle2_USB_POWER_REG &= Toggle2_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Toggle2__SIO)
        Toggle2_SIO_REG = Toggle2_backup.sioState;
    #endif
}


/* [] END OF FILE */
