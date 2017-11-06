/*******************************************************************************
* File Name: Toggle2.h  
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

#if !defined(CY_PINS_Toggle2_H) /* Pins Toggle2_H */
#define CY_PINS_Toggle2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Toggle2_aliases.h"


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
} Toggle2_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Toggle2_Read(void);
void    Toggle2_Write(uint8 value);
uint8   Toggle2_ReadDataReg(void);
#if defined(Toggle2__PC) || (CY_PSOC4_4200L) 
    void    Toggle2_SetDriveMode(uint8 mode);
#endif
void    Toggle2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Toggle2_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Toggle2_Sleep(void); 
void Toggle2_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Toggle2__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Toggle2_DRIVE_MODE_BITS        (3)
    #define Toggle2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Toggle2_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Toggle2_SetDriveMode() function.
         *  @{
         */
        #define Toggle2_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Toggle2_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Toggle2_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Toggle2_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Toggle2_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Toggle2_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Toggle2_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Toggle2_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Toggle2_MASK               Toggle2__MASK
#define Toggle2_SHIFT              Toggle2__SHIFT
#define Toggle2_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Toggle2_SetInterruptMode() function.
     *  @{
     */
        #define Toggle2_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Toggle2_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Toggle2_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Toggle2_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Toggle2__SIO)
    #define Toggle2_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Toggle2__PC) && (CY_PSOC4_4200L)
    #define Toggle2_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Toggle2_USBIO_DISABLE              ((uint32)(~Toggle2_USBIO_ENABLE))
    #define Toggle2_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Toggle2_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Toggle2_USBIO_ENTER_SLEEP          ((uint32)((1u << Toggle2_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Toggle2_USBIO_SUSPEND_DEL_SHIFT)))
    #define Toggle2_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Toggle2_USBIO_SUSPEND_SHIFT)))
    #define Toggle2_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Toggle2_USBIO_SUSPEND_DEL_SHIFT)))
    #define Toggle2_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Toggle2__PC)
    /* Port Configuration */
    #define Toggle2_PC                 (* (reg32 *) Toggle2__PC)
#endif
/* Pin State */
#define Toggle2_PS                     (* (reg32 *) Toggle2__PS)
/* Data Register */
#define Toggle2_DR                     (* (reg32 *) Toggle2__DR)
/* Input Buffer Disable Override */
#define Toggle2_INP_DIS                (* (reg32 *) Toggle2__PC2)

/* Interrupt configuration Registers */
#define Toggle2_INTCFG                 (* (reg32 *) Toggle2__INTCFG)
#define Toggle2_INTSTAT                (* (reg32 *) Toggle2__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Toggle2_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Toggle2__SIO)
    #define Toggle2_SIO_REG            (* (reg32 *) Toggle2__SIO)
#endif /* (Toggle2__SIO_CFG) */

/* USBIO registers */
#if !defined(Toggle2__PC) && (CY_PSOC4_4200L)
    #define Toggle2_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Toggle2_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Toggle2_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Toggle2_DRIVE_MODE_SHIFT       (0x00u)
#define Toggle2_DRIVE_MODE_MASK        (0x07u << Toggle2_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Toggle2_H */


/* [] END OF FILE */
