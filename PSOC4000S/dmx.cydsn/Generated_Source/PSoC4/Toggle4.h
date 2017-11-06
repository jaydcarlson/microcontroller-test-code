/*******************************************************************************
* File Name: Toggle4.h  
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

#if !defined(CY_PINS_Toggle4_H) /* Pins Toggle4_H */
#define CY_PINS_Toggle4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Toggle4_aliases.h"


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
} Toggle4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Toggle4_Read(void);
void    Toggle4_Write(uint8 value);
uint8   Toggle4_ReadDataReg(void);
#if defined(Toggle4__PC) || (CY_PSOC4_4200L) 
    void    Toggle4_SetDriveMode(uint8 mode);
#endif
void    Toggle4_SetInterruptMode(uint16 position, uint16 mode);
uint8   Toggle4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Toggle4_Sleep(void); 
void Toggle4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Toggle4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Toggle4_DRIVE_MODE_BITS        (3)
    #define Toggle4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Toggle4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Toggle4_SetDriveMode() function.
         *  @{
         */
        #define Toggle4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Toggle4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Toggle4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Toggle4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Toggle4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Toggle4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Toggle4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Toggle4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Toggle4_MASK               Toggle4__MASK
#define Toggle4_SHIFT              Toggle4__SHIFT
#define Toggle4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Toggle4_SetInterruptMode() function.
     *  @{
     */
        #define Toggle4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Toggle4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Toggle4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Toggle4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Toggle4__SIO)
    #define Toggle4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Toggle4__PC) && (CY_PSOC4_4200L)
    #define Toggle4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Toggle4_USBIO_DISABLE              ((uint32)(~Toggle4_USBIO_ENABLE))
    #define Toggle4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Toggle4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Toggle4_USBIO_ENTER_SLEEP          ((uint32)((1u << Toggle4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Toggle4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Toggle4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Toggle4_USBIO_SUSPEND_SHIFT)))
    #define Toggle4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Toggle4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Toggle4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Toggle4__PC)
    /* Port Configuration */
    #define Toggle4_PC                 (* (reg32 *) Toggle4__PC)
#endif
/* Pin State */
#define Toggle4_PS                     (* (reg32 *) Toggle4__PS)
/* Data Register */
#define Toggle4_DR                     (* (reg32 *) Toggle4__DR)
/* Input Buffer Disable Override */
#define Toggle4_INP_DIS                (* (reg32 *) Toggle4__PC2)

/* Interrupt configuration Registers */
#define Toggle4_INTCFG                 (* (reg32 *) Toggle4__INTCFG)
#define Toggle4_INTSTAT                (* (reg32 *) Toggle4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Toggle4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Toggle4__SIO)
    #define Toggle4_SIO_REG            (* (reg32 *) Toggle4__SIO)
#endif /* (Toggle4__SIO_CFG) */

/* USBIO registers */
#if !defined(Toggle4__PC) && (CY_PSOC4_4200L)
    #define Toggle4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Toggle4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Toggle4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Toggle4_DRIVE_MODE_SHIFT       (0x00u)
#define Toggle4_DRIVE_MODE_MASK        (0x07u << Toggle4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Toggle4_H */


/* [] END OF FILE */
