/*******************************************************************************
* File Name: Toggle1.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Toggle1_ALIASES_H) /* Pins Toggle1_ALIASES_H */
#define CY_PINS_Toggle1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Toggle1_0			(Toggle1__0__PC)
#define Toggle1_0_PS		(Toggle1__0__PS)
#define Toggle1_0_PC		(Toggle1__0__PC)
#define Toggle1_0_DR		(Toggle1__0__DR)
#define Toggle1_0_SHIFT	(Toggle1__0__SHIFT)
#define Toggle1_0_INTR	((uint16)((uint16)0x0003u << (Toggle1__0__SHIFT*2u)))

#define Toggle1_INTR_ALL	 ((uint16)(Toggle1_0_INTR))


#endif /* End Pins Toggle1_ALIASES_H */


/* [] END OF FILE */
