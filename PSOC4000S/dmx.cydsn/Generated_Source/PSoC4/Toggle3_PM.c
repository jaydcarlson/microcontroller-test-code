/*******************************************************************************
* File Name: Toggle3.c  
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
#include "Toggle3.h"

static Toggle3_BACKUP_STRUCT  Toggle3_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Toggle3_Sleep
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
*  \snippet Toggle3_SUT.c usage_Toggle3_Sleep_Wakeup
*******************************************************************************/
void Toggle3_Sleep(void)
{
    #if defined(Toggle3__PC)
        Toggle3_backup.pcState = Toggle3_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Toggle3_backup.usbState = Toggle3_CR1_REG;
            Toggle3_USB_POWER_REG |= Toggle3_USBIO_ENTER_SLEEP;
            Toggle3_CR1_REG &= Toggle3_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Toggle3__SIO)
        Toggle3_backup.sioState = Toggle3_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Toggle3_SIO_REG &= (uint32)(~Toggle3_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Toggle3_Wakeup
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
*  Refer to Toggle3_Sleep() for an example usage.
*******************************************************************************/
void Toggle3_Wakeup(void)
{
    #if defined(Toggle3__PC)
        Toggle3_PC = Toggle3_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Toggle3_USB_POWER_REG &= Toggle3_USBIO_EXIT_SLEEP_PH1;
            Toggle3_CR1_REG = Toggle3_backup.usbState;
            Toggle3_USB_POWER_REG &= Toggle3_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Toggle3__SIO)
        Toggle3_SIO_REG = Toggle3_backup.sioState;
    #endif
}


/* [] END OF FILE */
