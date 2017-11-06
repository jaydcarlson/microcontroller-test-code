/*******************************************************************************
* File Name: RED_PM.c
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

#include "RED.h"

static RED_BACKUP_STRUCT RED_backup;


/*******************************************************************************
* Function Name: RED_SaveConfig
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
void RED_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: RED_Sleep
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
void RED_Sleep(void)
{
    if(0u != (RED_BLOCK_CONTROL_REG & RED_MASK))
    {
        RED_backup.enableState = 1u;
    }
    else
    {
        RED_backup.enableState = 0u;
    }

    RED_Stop();
    RED_SaveConfig();
}


/*******************************************************************************
* Function Name: RED_RestoreConfig
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
void RED_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: RED_Wakeup
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
void RED_Wakeup(void)
{
    RED_RestoreConfig();

    if(0u != RED_backup.enableState)
    {
        RED_Enable();
    }
}


/* [] END OF FILE */
