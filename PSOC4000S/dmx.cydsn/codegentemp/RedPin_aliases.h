/*******************************************************************************
* File Name: RedPin.h  
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

#if !defined(CY_PINS_RedPin_ALIASES_H) /* Pins RedPin_ALIASES_H */
#define CY_PINS_RedPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define RedPin_0			(RedPin__0__PC)
#define RedPin_0_PS		(RedPin__0__PS)
#define RedPin_0_PC		(RedPin__0__PC)
#define RedPin_0_DR		(RedPin__0__DR)
#define RedPin_0_SHIFT	(RedPin__0__SHIFT)
#define RedPin_0_INTR	((uint16)((uint16)0x0003u << (RedPin__0__SHIFT*2u)))

#define RedPin_INTR_ALL	 ((uint16)(RedPin_0_INTR))


#endif /* End Pins RedPin_ALIASES_H */


/* [] END OF FILE */
