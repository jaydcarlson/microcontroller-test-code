/*******************************************************************************
* File Name: PWM3_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM3.h"

static PWM3_BACKUP_STRUCT PWM3_backup;


/*******************************************************************************
* Function Name: PWM3_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM3_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM3_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM3_Sleep(void)
{
    if(0u != (PWM3_BLOCK_CONTROL_REG & PWM3_MASK))
    {
        PWM3_backup.enableState = 1u;
    }
    else
    {
        PWM3_backup.enableState = 0u;
    }

    PWM3_Stop();
    PWM3_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM3_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM3_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM3_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM3_Wakeup(void)
{
    PWM3_RestoreConfig();

    if(0u != PWM3_backup.enableState)
    {
        PWM3_Enable();
    }
}


/* [] END OF FILE */
