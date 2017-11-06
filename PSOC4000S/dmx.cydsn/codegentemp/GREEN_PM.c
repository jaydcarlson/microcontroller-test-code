/*******************************************************************************
* File Name: GREEN_PM.c
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

#include "GREEN.h"

static GREEN_BACKUP_STRUCT GREEN_backup;


/*******************************************************************************
* Function Name: GREEN_SaveConfig
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
void GREEN_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: GREEN_Sleep
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
void GREEN_Sleep(void)
{
    if(0u != (GREEN_BLOCK_CONTROL_REG & GREEN_MASK))
    {
        GREEN_backup.enableState = 1u;
    }
    else
    {
        GREEN_backup.enableState = 0u;
    }

    GREEN_Stop();
    GREEN_SaveConfig();
}


/*******************************************************************************
* Function Name: GREEN_RestoreConfig
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
void GREEN_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: GREEN_Wakeup
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
void GREEN_Wakeup(void)
{
    GREEN_RestoreConfig();

    if(0u != GREEN_backup.enableState)
    {
        GREEN_Enable();
    }
}


/* [] END OF FILE */
