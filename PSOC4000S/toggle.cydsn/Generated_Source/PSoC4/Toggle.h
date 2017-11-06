/*******************************************************************************
* File Name: Toggle.h  
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

#if !defined(CY_PINS_Toggle_H) /* Pins Toggle_H */
#define CY_PINS_Toggle_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Toggle_aliases.h"


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
} Toggle_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Toggle_Read(void);
void    Toggle_Write(uint8 value);
uint8   Toggle_ReadDataReg(void);
#if defined(Toggle__PC) || (CY_PSOC4_4200L) 
    void    Toggle_SetDriveMode(uint8 mode);
#endif
void    Toggle_SetInterruptMode(uint16 position, uint16 mode);
uint8   Toggle_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Toggle_Sleep(void); 
void Toggle_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Toggle__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Toggle_DRIVE_MODE_BITS        (3)
    #define Toggle_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Toggle_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Toggle_SetDriveMode() function.
         *  @{
         */
        #define Toggle_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Toggle_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Toggle_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Toggle_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Toggle_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Toggle_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Toggle_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Toggle_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Toggle_MASK               Toggle__MASK
#define Toggle_SHIFT              Toggle__SHIFT
#define Toggle_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Toggle_SetInterruptMode() function.
     *  @{
     */
        #define Toggle_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Toggle_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Toggle_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Toggle_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Toggle__SIO)
    #define Toggle_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Toggle__PC) && (CY_PSOC4_4200L)
    #define Toggle_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Toggle_USBIO_DISABLE              ((uint32)(~Toggle_USBIO_ENABLE))
    #define Toggle_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Toggle_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Toggle_USBIO_ENTER_SLEEP          ((uint32)((1u << Toggle_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Toggle_USBIO_SUSPEND_DEL_SHIFT)))
    #define Toggle_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Toggle_USBIO_SUSPEND_SHIFT)))
    #define Toggle_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Toggle_USBIO_SUSPEND_DEL_SHIFT)))
    #define Toggle_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Toggle__PC)
    /* Port Configuration */
    #define Toggle_PC                 (* (reg32 *) Toggle__PC)
#endif
/* Pin State */
#define Toggle_PS                     (* (reg32 *) Toggle__PS)
/* Data Register */
#define Toggle_DR                     (* (reg32 *) Toggle__DR)
/* Input Buffer Disable Override */
#define Toggle_INP_DIS                (* (reg32 *) Toggle__PC2)

/* Interrupt configuration Registers */
#define Toggle_INTCFG                 (* (reg32 *) Toggle__INTCFG)
#define Toggle_INTSTAT                (* (reg32 *) Toggle__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Toggle_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Toggle__SIO)
    #define Toggle_SIO_REG            (* (reg32 *) Toggle__SIO)
#endif /* (Toggle__SIO_CFG) */

/* USBIO registers */
#if !defined(Toggle__PC) && (CY_PSOC4_4200L)
    #define Toggle_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Toggle_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Toggle_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Toggle_DRIVE_MODE_SHIFT       (0x00u)
#define Toggle_DRIVE_MODE_MASK        (0x07u << Toggle_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Toggle_H */


/* [] END OF FILE */
