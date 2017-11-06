/*******************************************************************************
* File Name: GreenPin.h  
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

#if !defined(CY_PINS_GreenPin_ALIASES_H) /* Pins GreenPin_ALIASES_H */
#define CY_PINS_GreenPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GreenPin_0			(GreenPin__0__PC)
#define GreenPin_0_PS		(GreenPin__0__PS)
#define GreenPin_0_PC		(GreenPin__0__PC)
#define GreenPin_0_DR		(GreenPin__0__DR)
#define GreenPin_0_SHIFT	(GreenPin__0__SHIFT)
#define GreenPin_0_INTR	((uint16)((uint16)0x0003u << (GreenPin__0__SHIFT*2u)))

#define GreenPin_INTR_ALL	 ((uint16)(GreenPin_0_INTR))


#endif /* End Pins GreenPin_ALIASES_H */


/* [] END OF FILE */
