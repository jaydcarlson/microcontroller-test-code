/*******************************************************************************
* File Name: BLUE_PM.c
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

#include "BLUE.h"

static BLUE_BACKUP_STRUCT BLUE_backup;


/*******************************************************************************
* Function Name: BLUE_SaveConfig
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
void BLUE_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BLUE_Sleep
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
void BLUE_Sleep(void)
{
    if(0u != (BLUE_BLOCK_CONTROL_REG & BLUE_MASK))
    {
        BLUE_backup.enableState = 1u;
    }
    else
    {
        BLUE_backup.enableState = 0u;
    }

    BLUE_Stop();
    BLUE_SaveConfig();
}


/*******************************************************************************
* Function Name: BLUE_RestoreConfig
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
void BLUE_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BLUE_Wakeup
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
void BLUE_Wakeup(void)
{
    BLUE_RestoreConfig();

    if(0u != BLUE_backup.enableState)
    {
        BLUE_Enable();
    }
}


/* [] END OF FILE */
