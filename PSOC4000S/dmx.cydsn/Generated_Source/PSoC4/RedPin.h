/*******************************************************************************
* File Name: RedPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RedPin_H) /* Pins RedPin_H */
#define CY_PINS_RedPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RedPin_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} RedPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   RedPin_Read(void);
void    RedPin_Write(uint8 value);
uint8   RedPin_ReadDataReg(void);
#if defined(RedPin__PC) || (CY_PSOC4_4200L) 
    void    RedPin_SetDriveMode(uint8 mode);
#endif
void    RedPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   RedPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void RedPin_Sleep(void); 
void RedPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(RedPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define RedPin_DRIVE_MODE_BITS        (3)
    #define RedPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RedPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the RedPin_SetDriveMode() function.
         *  @{
         */
        #define RedPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define RedPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define RedPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define RedPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define RedPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define RedPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define RedPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define RedPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define RedPin_MASK               RedPin__MASK
#define RedPin_SHIFT              RedPin__SHIFT
#define RedPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RedPin_SetInterruptMode() function.
     *  @{
     */
        #define RedPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define RedPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define RedPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define RedPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(RedPin__SIO)
    #define RedPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(RedPin__PC) && (CY_PSOC4_4200L)
    #define RedPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define RedPin_USBIO_DISABLE              ((uint32)(~RedPin_USBIO_ENABLE))
    #define RedPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define RedPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define RedPin_USBIO_ENTER_SLEEP          ((uint32)((1u << RedPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << RedPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define RedPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << RedPin_USBIO_SUSPEND_SHIFT)))
    #define RedPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << RedPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define RedPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(RedPin__PC)
    /* Port Configuration */
    #define RedPin_PC                 (* (reg32 *) RedPin__PC)
#endif
/* Pin State */
#define RedPin_PS                     (* (reg32 *) RedPin__PS)
/* Data Register */
#define RedPin_DR                     (* (reg32 *) RedPin__DR)
/* Input Buffer Disable Override */
#define RedPin_INP_DIS                (* (reg32 *) RedPin__PC2)

/* Interrupt configuration Registers */
#define RedPin_INTCFG                 (* (reg32 *) RedPin__INTCFG)
#define RedPin_INTSTAT                (* (reg32 *) RedPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define RedPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(RedPin__SIO)
    #define RedPin_SIO_REG            (* (reg32 *) RedPin__SIO)
#endif /* (RedPin__SIO_CFG) */

/* USBIO registers */
#if !defined(RedPin__PC) && (CY_PSOC4_4200L)
    #define RedPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define RedPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define RedPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define RedPin_DRIVE_MODE_SHIFT       (0x00u)
#define RedPin_DRIVE_MODE_MASK        (0x07u << RedPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins RedPin_H */


/* [] END OF FILE */
