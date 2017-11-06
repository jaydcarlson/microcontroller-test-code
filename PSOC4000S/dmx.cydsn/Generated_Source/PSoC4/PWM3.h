/*******************************************************************************
* File Name: PWM3.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the PWM3
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_PWM3_H)
#define CY_TCPWM_PWM3_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PWM3_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWM3_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PWM3_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define PWM3_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define PWM3_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWM3_QUAD_ENCODING_MODES            (0lu)
#define PWM3_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define PWM3_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWM3_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWM3_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWM3_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWM3_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWM3_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWM3_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWM3_TC_RUN_MODE                    (0lu)
#define PWM3_TC_COUNTER_MODE                (0lu)
#define PWM3_TC_COMP_CAP_MODE               (2lu)
#define PWM3_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWM3_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWM3_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWM3_TC_START_SIGNAL_MODE           (0lu)
#define PWM3_TC_STOP_SIGNAL_MODE            (0lu)
#define PWM3_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM3_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWM3_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWM3_TC_START_SIGNAL_PRESENT        (0lu)
#define PWM3_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWM3_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM3_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWM3_PWM_KILL_EVENT                 (0lu)
#define PWM3_PWM_STOP_EVENT                 (0lu)
#define PWM3_PWM_MODE                       (4lu)
#define PWM3_PWM_OUT_N_INVERT               (0lu)
#define PWM3_PWM_OUT_INVERT                 (0lu)
#define PWM3_PWM_ALIGN                      (0lu)
#define PWM3_PWM_RUN_MODE                   (0lu)
#define PWM3_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWM3_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWM3_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWM3_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWM3_PWM_START_SIGNAL_MODE          (0lu)
#define PWM3_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWM3_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM3_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWM3_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWM3_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWM3_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWM3_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM3_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWM3_TC_PERIOD_VALUE                (65535lu)
#define PWM3_TC_COMPARE_VALUE               (65535lu)
#define PWM3_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWM3_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWM3_PWM_PERIOD_VALUE               (65535lu)
#define PWM3_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWM3_PWM_PERIOD_SWAP                (0lu)
#define PWM3_PWM_COMPARE_VALUE              (65535lu)
#define PWM3_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWM3_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWM3__LEFT 0
#define PWM3__RIGHT 1
#define PWM3__CENTER 2
#define PWM3__ASYMMETRIC 3

#define PWM3__X1 0
#define PWM3__X2 1
#define PWM3__X4 2

#define PWM3__PWM 4
#define PWM3__PWM_DT 5
#define PWM3__PWM_PR 6

#define PWM3__INVERSE 1
#define PWM3__DIRECT 0

#define PWM3__CAPTURE 2
#define PWM3__COMPARE 0

#define PWM3__TRIG_LEVEL 3
#define PWM3__TRIG_RISING 0
#define PWM3__TRIG_FALLING 1
#define PWM3__TRIG_BOTH 2

#define PWM3__INTR_MASK_TC 1
#define PWM3__INTR_MASK_CC_MATCH 2
#define PWM3__INTR_MASK_NONE 0
#define PWM3__INTR_MASK_TC_CC 3

#define PWM3__UNCONFIG 8
#define PWM3__TIMER 1
#define PWM3__QUAD 3
#define PWM3__PWM_SEL 7

#define PWM3__COUNT_UP 0
#define PWM3__COUNT_DOWN 1
#define PWM3__COUNT_UPDOWN0 2
#define PWM3__COUNT_UPDOWN1 3


/* Prescaler */
#define PWM3_PRESCALE_DIVBY1                ((uint32)(0u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY2                ((uint32)(1u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY4                ((uint32)(2u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY8                ((uint32)(3u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY16               ((uint32)(4u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY32               ((uint32)(5u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY64               ((uint32)(6u << PWM3_PRESCALER_SHIFT))
#define PWM3_PRESCALE_DIVBY128              ((uint32)(7u << PWM3_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWM3_MODE_TIMER_COMPARE             ((uint32)(PWM3__COMPARE         <<  \
                                                                  PWM3_MODE_SHIFT))
#define PWM3_MODE_TIMER_CAPTURE             ((uint32)(PWM3__CAPTURE         <<  \
                                                                  PWM3_MODE_SHIFT))
#define PWM3_MODE_QUAD                      ((uint32)(PWM3__QUAD            <<  \
                                                                  PWM3_MODE_SHIFT))
#define PWM3_MODE_PWM                       ((uint32)(PWM3__PWM             <<  \
                                                                  PWM3_MODE_SHIFT))
#define PWM3_MODE_PWM_DT                    ((uint32)(PWM3__PWM_DT          <<  \
                                                                  PWM3_MODE_SHIFT))
#define PWM3_MODE_PWM_PR                    ((uint32)(PWM3__PWM_PR          <<  \
                                                                  PWM3_MODE_SHIFT))

/* Quad Modes */
#define PWM3_MODE_X1                        ((uint32)(PWM3__X1              <<  \
                                                                  PWM3_QUAD_MODE_SHIFT))
#define PWM3_MODE_X2                        ((uint32)(PWM3__X2              <<  \
                                                                  PWM3_QUAD_MODE_SHIFT))
#define PWM3_MODE_X4                        ((uint32)(PWM3__X4              <<  \
                                                                  PWM3_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWM3_COUNT_UP                       ((uint32)(PWM3__COUNT_UP        <<  \
                                                                  PWM3_UPDOWN_SHIFT))
#define PWM3_COUNT_DOWN                     ((uint32)(PWM3__COUNT_DOWN      <<  \
                                                                  PWM3_UPDOWN_SHIFT))
#define PWM3_COUNT_UPDOWN0                  ((uint32)(PWM3__COUNT_UPDOWN0   <<  \
                                                                  PWM3_UPDOWN_SHIFT))
#define PWM3_COUNT_UPDOWN1                  ((uint32)(PWM3__COUNT_UPDOWN1   <<  \
                                                                  PWM3_UPDOWN_SHIFT))

/* PWM output invert */
#define PWM3_INVERT_LINE                    ((uint32)(PWM3__INVERSE         <<  \
                                                                  PWM3_INV_OUT_SHIFT))
#define PWM3_INVERT_LINE_N                  ((uint32)(PWM3__INVERSE         <<  \
                                                                  PWM3_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWM3_TRIG_RISING                    ((uint32)PWM3__TRIG_RISING)
#define PWM3_TRIG_FALLING                   ((uint32)PWM3__TRIG_FALLING)
#define PWM3_TRIG_BOTH                      ((uint32)PWM3__TRIG_BOTH)
#define PWM3_TRIG_LEVEL                     ((uint32)PWM3__TRIG_LEVEL)

/* Interrupt mask */
#define PWM3_INTR_MASK_TC                   ((uint32)PWM3__INTR_MASK_TC)
#define PWM3_INTR_MASK_CC_MATCH             ((uint32)PWM3__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWM3_CC_MATCH_SET                   (0x00u)
#define PWM3_CC_MATCH_CLEAR                 (0x01u)
#define PWM3_CC_MATCH_INVERT                (0x02u)
#define PWM3_CC_MATCH_NO_CHANGE             (0x03u)
#define PWM3_OVERLOW_SET                    (0x00u)
#define PWM3_OVERLOW_CLEAR                  (0x04u)
#define PWM3_OVERLOW_INVERT                 (0x08u)
#define PWM3_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWM3_UNDERFLOW_SET                  (0x00u)
#define PWM3_UNDERFLOW_CLEAR                (0x10u)
#define PWM3_UNDERFLOW_INVERT               (0x20u)
#define PWM3_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWM3_PWM_MODE_LEFT                  (PWM3_CC_MATCH_CLEAR        |   \
                                                         PWM3_OVERLOW_SET           |   \
                                                         PWM3_UNDERFLOW_NO_CHANGE)
#define PWM3_PWM_MODE_RIGHT                 (PWM3_CC_MATCH_SET          |   \
                                                         PWM3_OVERLOW_NO_CHANGE     |   \
                                                         PWM3_UNDERFLOW_CLEAR)
#define PWM3_PWM_MODE_ASYM                  (PWM3_CC_MATCH_INVERT       |   \
                                                         PWM3_OVERLOW_SET           |   \
                                                         PWM3_UNDERFLOW_CLEAR)

#if (PWM3_CY_TCPWM_V2)
    #if(PWM3_CY_TCPWM_4000)
        #define PWM3_PWM_MODE_CENTER                (PWM3_CC_MATCH_INVERT       |   \
                                                                 PWM3_OVERLOW_NO_CHANGE     |   \
                                                                 PWM3_UNDERFLOW_CLEAR)
    #else
        #define PWM3_PWM_MODE_CENTER                (PWM3_CC_MATCH_INVERT       |   \
                                                                 PWM3_OVERLOW_SET           |   \
                                                                 PWM3_UNDERFLOW_CLEAR)
    #endif /* (PWM3_CY_TCPWM_4000) */
#else
    #define PWM3_PWM_MODE_CENTER                (PWM3_CC_MATCH_INVERT       |   \
                                                             PWM3_OVERLOW_NO_CHANGE     |   \
                                                             PWM3_UNDERFLOW_CLEAR)
#endif /* (PWM3_CY_TCPWM_NEW) */

/* Command operations without condition */
#define PWM3_CMD_CAPTURE                    (0u)
#define PWM3_CMD_RELOAD                     (8u)
#define PWM3_CMD_STOP                       (16u)
#define PWM3_CMD_START                      (24u)

/* Status */
#define PWM3_STATUS_DOWN                    (1u)
#define PWM3_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWM3_Init(void);
void   PWM3_Enable(void);
void   PWM3_Start(void);
void   PWM3_Stop(void);

void   PWM3_SetMode(uint32 mode);
void   PWM3_SetCounterMode(uint32 counterMode);
void   PWM3_SetPWMMode(uint32 modeMask);
void   PWM3_SetQDMode(uint32 qdMode);

void   PWM3_SetPrescaler(uint32 prescaler);
void   PWM3_TriggerCommand(uint32 mask, uint32 command);
void   PWM3_SetOneShot(uint32 oneShotEnable);
uint32 PWM3_ReadStatus(void);

void   PWM3_SetPWMSyncKill(uint32 syncKillEnable);
void   PWM3_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWM3_SetPWMDeadTime(uint32 deadTime);
void   PWM3_SetPWMInvert(uint32 mask);

void   PWM3_SetInterruptMode(uint32 interruptMask);
uint32 PWM3_GetInterruptSourceMasked(void);
uint32 PWM3_GetInterruptSource(void);
void   PWM3_ClearInterrupt(uint32 interruptMask);
void   PWM3_SetInterrupt(uint32 interruptMask);

void   PWM3_WriteCounter(uint32 count);
uint32 PWM3_ReadCounter(void);

uint32 PWM3_ReadCapture(void);
uint32 PWM3_ReadCaptureBuf(void);

void   PWM3_WritePeriod(uint32 period);
uint32 PWM3_ReadPeriod(void);
void   PWM3_WritePeriodBuf(uint32 periodBuf);
uint32 PWM3_ReadPeriodBuf(void);

void   PWM3_WriteCompare(uint32 compare);
uint32 PWM3_ReadCompare(void);
void   PWM3_WriteCompareBuf(uint32 compareBuf);
uint32 PWM3_ReadCompareBuf(void);

void   PWM3_SetPeriodSwap(uint32 swapEnable);
void   PWM3_SetCompareSwap(uint32 swapEnable);

void   PWM3_SetCaptureMode(uint32 triggerMode);
void   PWM3_SetReloadMode(uint32 triggerMode);
void   PWM3_SetStartMode(uint32 triggerMode);
void   PWM3_SetStopMode(uint32 triggerMode);
void   PWM3_SetCountMode(uint32 triggerMode);

void   PWM3_SaveConfig(void);
void   PWM3_RestoreConfig(void);
void   PWM3_Sleep(void);
void   PWM3_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWM3_BLOCK_CONTROL_REG              (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM3_BLOCK_CONTROL_PTR              ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM3_COMMAND_REG                    (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM3_COMMAND_PTR                    ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM3_INTRRUPT_CAUSE_REG             (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM3_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM3_CONTROL_REG                    (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__CTRL )
#define PWM3_CONTROL_PTR                    ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__CTRL )
#define PWM3_STATUS_REG                     (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__STATUS )
#define PWM3_STATUS_PTR                     ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__STATUS )
#define PWM3_COUNTER_REG                    (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__COUNTER )
#define PWM3_COUNTER_PTR                    ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__COUNTER )
#define PWM3_COMP_CAP_REG                   (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__CC )
#define PWM3_COMP_CAP_PTR                   ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__CC )
#define PWM3_COMP_CAP_BUF_REG               (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM3_COMP_CAP_BUF_PTR               ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM3_PERIOD_REG                     (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__PERIOD )
#define PWM3_PERIOD_PTR                     ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__PERIOD )
#define PWM3_PERIOD_BUF_REG                 (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM3_PERIOD_BUF_PTR                 ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM3_TRIG_CONTROL0_REG              (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM3_TRIG_CONTROL0_PTR              ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM3_TRIG_CONTROL1_REG              (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM3_TRIG_CONTROL1_PTR              ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM3_TRIG_CONTROL2_REG              (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM3_TRIG_CONTROL2_PTR              ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM3_INTERRUPT_REQ_REG              (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR )
#define PWM3_INTERRUPT_REQ_PTR              ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR )
#define PWM3_INTERRUPT_SET_REG              (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM3_INTERRUPT_SET_PTR              ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM3_INTERRUPT_MASK_REG             (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM3_INTERRUPT_MASK_PTR             ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM3_INTERRUPT_MASKED_REG           (*(reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWM3_INTERRUPT_MASKED_PTR           ( (reg32 *) PWM3_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWM3_MASK                           ((uint32)PWM3_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWM3_RELOAD_CC_SHIFT                (0u)
#define PWM3_RELOAD_PERIOD_SHIFT            (1u)
#define PWM3_PWM_SYNC_KILL_SHIFT            (2u)
#define PWM3_PWM_STOP_KILL_SHIFT            (3u)
#define PWM3_PRESCALER_SHIFT                (8u)
#define PWM3_UPDOWN_SHIFT                   (16u)
#define PWM3_ONESHOT_SHIFT                  (18u)
#define PWM3_QUAD_MODE_SHIFT                (20u)
#define PWM3_INV_OUT_SHIFT                  (20u)
#define PWM3_INV_COMPL_OUT_SHIFT            (21u)
#define PWM3_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWM3_RELOAD_CC_MASK                 ((uint32)(PWM3_1BIT_MASK        <<  \
                                                                            PWM3_RELOAD_CC_SHIFT))
#define PWM3_RELOAD_PERIOD_MASK             ((uint32)(PWM3_1BIT_MASK        <<  \
                                                                            PWM3_RELOAD_PERIOD_SHIFT))
#define PWM3_PWM_SYNC_KILL_MASK             ((uint32)(PWM3_1BIT_MASK        <<  \
                                                                            PWM3_PWM_SYNC_KILL_SHIFT))
#define PWM3_PWM_STOP_KILL_MASK             ((uint32)(PWM3_1BIT_MASK        <<  \
                                                                            PWM3_PWM_STOP_KILL_SHIFT))
#define PWM3_PRESCALER_MASK                 ((uint32)(PWM3_8BIT_MASK        <<  \
                                                                            PWM3_PRESCALER_SHIFT))
#define PWM3_UPDOWN_MASK                    ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                            PWM3_UPDOWN_SHIFT))
#define PWM3_ONESHOT_MASK                   ((uint32)(PWM3_1BIT_MASK        <<  \
                                                                            PWM3_ONESHOT_SHIFT))
#define PWM3_QUAD_MODE_MASK                 ((uint32)(PWM3_3BIT_MASK        <<  \
                                                                            PWM3_QUAD_MODE_SHIFT))
#define PWM3_INV_OUT_MASK                   ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                            PWM3_INV_OUT_SHIFT))
#define PWM3_MODE_MASK                      ((uint32)(PWM3_3BIT_MASK        <<  \
                                                                            PWM3_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWM3_CAPTURE_SHIFT                  (0u)
#define PWM3_COUNT_SHIFT                    (2u)
#define PWM3_RELOAD_SHIFT                   (4u)
#define PWM3_STOP_SHIFT                     (6u)
#define PWM3_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWM3_CAPTURE_MASK                   ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                  PWM3_CAPTURE_SHIFT))
#define PWM3_COUNT_MASK                     ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                  PWM3_COUNT_SHIFT))
#define PWM3_RELOAD_MASK                    ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                  PWM3_RELOAD_SHIFT))
#define PWM3_STOP_MASK                      ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                  PWM3_STOP_SHIFT))
#define PWM3_START_MASK                     ((uint32)(PWM3_2BIT_MASK        <<  \
                                                                  PWM3_START_SHIFT))

/* MASK */
#define PWM3_1BIT_MASK                      ((uint32)0x01u)
#define PWM3_2BIT_MASK                      ((uint32)0x03u)
#define PWM3_3BIT_MASK                      ((uint32)0x07u)
#define PWM3_6BIT_MASK                      ((uint32)0x3Fu)
#define PWM3_8BIT_MASK                      ((uint32)0xFFu)
#define PWM3_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWM3_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWM3_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(PWM3_QUAD_ENCODING_MODES     << PWM3_QUAD_MODE_SHIFT))       |\
         ((uint32)(PWM3_CONFIG                  << PWM3_MODE_SHIFT)))

#define PWM3_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(PWM3_PWM_STOP_EVENT          << PWM3_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(PWM3_PWM_OUT_INVERT          << PWM3_INV_OUT_SHIFT))         |\
         ((uint32)(PWM3_PWM_OUT_N_INVERT        << PWM3_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(PWM3_PWM_MODE                << PWM3_MODE_SHIFT)))

#define PWM3_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(PWM3_PWM_RUN_MODE         << PWM3_ONESHOT_SHIFT))
            
#define PWM3_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(PWM3_PWM_ALIGN            << PWM3_UPDOWN_SHIFT))

#define PWM3_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(PWM3_PWM_KILL_EVENT      << PWM3_PWM_SYNC_KILL_SHIFT))

#define PWM3_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(PWM3_PWM_DEAD_TIME_CYCLE  << PWM3_PRESCALER_SHIFT))

#define PWM3_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(PWM3_PWM_PRESCALER        << PWM3_PRESCALER_SHIFT))

#define PWM3_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(PWM3_TC_PRESCALER            << PWM3_PRESCALER_SHIFT))       |\
         ((uint32)(PWM3_TC_COUNTER_MODE         << PWM3_UPDOWN_SHIFT))          |\
         ((uint32)(PWM3_TC_RUN_MODE             << PWM3_ONESHOT_SHIFT))         |\
         ((uint32)(PWM3_TC_COMP_CAP_MODE        << PWM3_MODE_SHIFT)))
        
#define PWM3_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(PWM3_QUAD_PHIA_SIGNAL_MODE   << PWM3_COUNT_SHIFT))           |\
         ((uint32)(PWM3_QUAD_INDEX_SIGNAL_MODE  << PWM3_RELOAD_SHIFT))          |\
         ((uint32)(PWM3_QUAD_STOP_SIGNAL_MODE   << PWM3_STOP_SHIFT))            |\
         ((uint32)(PWM3_QUAD_PHIB_SIGNAL_MODE   << PWM3_START_SHIFT)))

#define PWM3_PWM_SIGNALS_MODES                                                              \
        (((uint32)(PWM3_PWM_SWITCH_SIGNAL_MODE  << PWM3_CAPTURE_SHIFT))         |\
         ((uint32)(PWM3_PWM_COUNT_SIGNAL_MODE   << PWM3_COUNT_SHIFT))           |\
         ((uint32)(PWM3_PWM_RELOAD_SIGNAL_MODE  << PWM3_RELOAD_SHIFT))          |\
         ((uint32)(PWM3_PWM_STOP_SIGNAL_MODE    << PWM3_STOP_SHIFT))            |\
         ((uint32)(PWM3_PWM_START_SIGNAL_MODE   << PWM3_START_SHIFT)))

#define PWM3_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(PWM3_TC_CAPTURE_SIGNAL_MODE  << PWM3_CAPTURE_SHIFT))         |\
         ((uint32)(PWM3_TC_COUNT_SIGNAL_MODE    << PWM3_COUNT_SHIFT))           |\
         ((uint32)(PWM3_TC_RELOAD_SIGNAL_MODE   << PWM3_RELOAD_SHIFT))          |\
         ((uint32)(PWM3_TC_STOP_SIGNAL_MODE     << PWM3_STOP_SHIFT))            |\
         ((uint32)(PWM3_TC_START_SIGNAL_MODE    << PWM3_START_SHIFT)))
        
#define PWM3_TIMER_UPDOWN_CNT_USED                                                          \
                ((PWM3__COUNT_UPDOWN0 == PWM3_TC_COUNTER_MODE)                  ||\
                 (PWM3__COUNT_UPDOWN1 == PWM3_TC_COUNTER_MODE))

#define PWM3_PWM_UPDOWN_CNT_USED                                                            \
                ((PWM3__CENTER == PWM3_PWM_ALIGN)                               ||\
                 (PWM3__ASYMMETRIC == PWM3_PWM_ALIGN))               
        
#define PWM3_PWM_PR_INIT_VALUE              (1u)
#define PWM3_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_PWM3_H */

/* [] END OF FILE */
