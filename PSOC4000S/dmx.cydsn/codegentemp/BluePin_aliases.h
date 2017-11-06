/*******************************************************************************
* File Name: BluePin.h  
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

#if !defined(CY_PINS_BluePin_ALIASES_H) /* Pins BluePin_ALIASES_H */
#define CY_PINS_BluePin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BluePin_0			(BluePin__0__PC)
#define BluePin_0_PS		(BluePin__0__PS)
#define BluePin_0_PC		(BluePin__0__PC)
#define BluePin_0_DR		(BluePin__0__DR)
#define BluePin_0_SHIFT	(BluePin__0__SHIFT)
#define BluePin_0_INTR	((uint16)((uint16)0x0003u << (BluePin__0__SHIFT*2u)))

#define BluePin_INTR_ALL	 ((uint16)(BluePin_0_INTR))


#endif /* End Pins BluePin_ALIASES_H */


/* [] END OF FILE */
