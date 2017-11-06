/*******************************************************************************
* File Name: BluePin.h  
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

#if !defined(CY_PINS_BluePin_H) /* Pins BluePin_H */
#define CY_PINS_BluePin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BluePin_aliases.h"


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
} BluePin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BluePin_Read(void);
void    BluePin_Write(uint8 value);
uint8   BluePin_ReadDataReg(void);
#if defined(BluePin__PC) || (CY_PSOC4_4200L) 
    void    BluePin_SetDriveMode(uint8 mode);
#endif
void    BluePin_SetInterruptMode(uint16 position, uint16 mode);
uint8   BluePin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BluePin_Sleep(void); 
void BluePin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BluePin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BluePin_DRIVE_MODE_BITS        (3)
    #define BluePin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BluePin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BluePin_SetDriveMode() function.
         *  @{
         */
        #define BluePin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BluePin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BluePin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BluePin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BluePin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BluePin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BluePin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BluePin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BluePin_MASK               BluePin__MASK
#define BluePin_SHIFT              BluePin__SHIFT
#define BluePin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BluePin_SetInterruptMode() function.
     *  @{
     */
        #define BluePin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BluePin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BluePin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BluePin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BluePin__SIO)
    #define BluePin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BluePin__PC) && (CY_PSOC4_4200L)
    #define BluePin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BluePin_USBIO_DISABLE              ((uint32)(~BluePin_USBIO_ENABLE))
    #define BluePin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BluePin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BluePin_USBIO_ENTER_SLEEP          ((uint32)((1u << BluePin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BluePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define BluePin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BluePin_USBIO_SUSPEND_SHIFT)))
    #define BluePin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BluePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define BluePin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BluePin__PC)
    /* Port Configuration */
    #define BluePin_PC                 (* (reg32 *) BluePin__PC)
#endif
/* Pin State */
#define BluePin_PS                     (* (reg32 *) BluePin__PS)
/* Data Register */
#define BluePin_DR                     (* (reg32 *) BluePin__DR)
/* Input Buffer Disable Override */
#define BluePin_INP_DIS                (* (reg32 *) BluePin__PC2)

/* Interrupt configuration Registers */
#define BluePin_INTCFG                 (* (reg32 *) BluePin__INTCFG)
#define BluePin_INTSTAT                (* (reg32 *) BluePin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BluePin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BluePin__SIO)
    #define BluePin_SIO_REG            (* (reg32 *) BluePin__SIO)
#endif /* (BluePin__SIO_CFG) */

/* USBIO registers */
#if !defined(BluePin__PC) && (CY_PSOC4_4200L)
    #define BluePin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BluePin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BluePin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BluePin_DRIVE_MODE_SHIFT       (0x00u)
#define BluePin_DRIVE_MODE_MASK        (0x07u << BluePin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BluePin_H */


/* [] END OF FILE */
