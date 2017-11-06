/*******************************************************************************
* File Name: Toggle3.h  
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

#if !defined(CY_PINS_Toggle3_ALIASES_H) /* Pins Toggle3_ALIASES_H */
#define CY_PINS_Toggle3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Toggle3_0			(Toggle3__0__PC)
#define Toggle3_0_PS		(Toggle3__0__PS)
#define Toggle3_0_PC		(Toggle3__0__PC)
#define Toggle3_0_DR		(Toggle3__0__DR)
#define Toggle3_0_SHIFT	(Toggle3__0__SHIFT)
#define Toggle3_0_INTR	((uint16)((uint16)0x0003u << (Toggle3__0__SHIFT*2u)))

#define Toggle3_INTR_ALL	 ((uint16)(Toggle3_0_INTR))


#endif /* End Pins Toggle3_ALIASES_H */


/* [] END OF FILE */
