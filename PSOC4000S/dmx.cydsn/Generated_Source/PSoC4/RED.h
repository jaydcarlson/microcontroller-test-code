/*******************************************************************************
* File Name: RED.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the RED
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

#if !defined(CY_TCPWM_RED_H)
#define CY_TCPWM_RED_H


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
} RED_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  RED_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define RED_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define RED_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define RED_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define RED_QUAD_ENCODING_MODES            (0lu)
#define RED_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define RED_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define RED_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define RED_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define RED_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define RED_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define RED_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define RED_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define RED_TC_RUN_MODE                    (0lu)
#define RED_TC_COUNTER_MODE                (0lu)
#define RED_TC_COMP_CAP_MODE               (2lu)
#define RED_TC_PRESCALER                   (0lu)

/* Signal modes */
#define RED_TC_RELOAD_SIGNAL_MODE          (0lu)
#define RED_TC_COUNT_SIGNAL_MODE           (3lu)
#define RED_TC_START_SIGNAL_MODE           (0lu)
#define RED_TC_STOP_SIGNAL_MODE            (0lu)
#define RED_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define RED_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define RED_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define RED_TC_START_SIGNAL_PRESENT        (0lu)
#define RED_TC_STOP_SIGNAL_PRESENT         (0lu)
#define RED_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define RED_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define RED_PWM_KILL_EVENT                 (0lu)
#define RED_PWM_STOP_EVENT                 (0lu)
#define RED_PWM_MODE                       (4lu)
#define RED_PWM_OUT_N_INVERT               (1lu)
#define RED_PWM_OUT_INVERT                 (1lu)
#define RED_PWM_ALIGN                      (0lu)
#define RED_PWM_RUN_MODE                   (0lu)
#define RED_PWM_DEAD_TIME_CYCLE            (0lu)
#define RED_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define RED_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define RED_PWM_COUNT_SIGNAL_MODE          (3lu)
#define RED_PWM_START_SIGNAL_MODE          (0lu)
#define RED_PWM_STOP_SIGNAL_MODE           (0lu)
#define RED_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define RED_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define RED_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define RED_PWM_START_SIGNAL_PRESENT       (0lu)
#define RED_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define RED_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define RED_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define RED_TC_PERIOD_VALUE                (65535lu)
#define RED_TC_COMPARE_VALUE               (65535lu)
#define RED_TC_COMPARE_BUF_VALUE           (65535lu)
#define RED_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define RED_PWM_PERIOD_VALUE               (255lu)
#define RED_PWM_PERIOD_BUF_VALUE           (65535lu)
#define RED_PWM_PERIOD_SWAP                (0lu)
#define RED_PWM_COMPARE_VALUE              (128lu)
#define RED_PWM_COMPARE_BUF_VALUE          (65535lu)
#define RED_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define RED__LEFT 0
#define RED__RIGHT 1
#define RED__CENTER 2
#define RED__ASYMMETRIC 3

#define RED__X1 0
#define RED__X2 1
#define RED__X4 2

#define RED__PWM 4
#define RED__PWM_DT 5
#define RED__PWM_PR 6

#define RED__INVERSE 1
#define RED__DIRECT 0

#define RED__CAPTURE 2
#define RED__COMPARE 0

#define RED__TRIG_LEVEL 3
#define RED__TRIG_RISING 0
#define RED__TRIG_FALLING 1
#define RED__TRIG_BOTH 2

#define RED__INTR_MASK_TC 1
#define RED__INTR_MASK_CC_MATCH 2
#define RED__INTR_MASK_NONE 0
#define RED__INTR_MASK_TC_CC 3

#define RED__UNCONFIG 8
#define RED__TIMER 1
#define RED__QUAD 3
#define RED__PWM_SEL 7

#define RED__COUNT_UP 0
#define RED__COUNT_DOWN 1
#define RED__COUNT_UPDOWN0 2
#define RED__COUNT_UPDOWN1 3


/* Prescaler */
#define RED_PRESCALE_DIVBY1                ((uint32)(0u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY2                ((uint32)(1u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY4                ((uint32)(2u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY8                ((uint32)(3u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY16               ((uint32)(4u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY32               ((uint32)(5u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY64               ((uint32)(6u << RED_PRESCALER_SHIFT))
#define RED_PRESCALE_DIVBY128              ((uint32)(7u << RED_PRESCALER_SHIFT))

/* TCPWM set modes */
#define RED_MODE_TIMER_COMPARE             ((uint32)(RED__COMPARE         <<  \
                                                                  RED_MODE_SHIFT))
#define RED_MODE_TIMER_CAPTURE             ((uint32)(RED__CAPTURE         <<  \
                                                                  RED_MODE_SHIFT))
#define RED_MODE_QUAD                      ((uint32)(RED__QUAD            <<  \
                                                                  RED_MODE_SHIFT))
#define RED_MODE_PWM                       ((uint32)(RED__PWM             <<  \
                                                                  RED_MODE_SHIFT))
#define RED_MODE_PWM_DT                    ((uint32)(RED__PWM_DT          <<  \
                                                                  RED_MODE_SHIFT))
#define RED_MODE_PWM_PR                    ((uint32)(RED__PWM_PR          <<  \
                                                                  RED_MODE_SHIFT))

/* Quad Modes */
#define RED_MODE_X1                        ((uint32)(RED__X1              <<  \
                                                                  RED_QUAD_MODE_SHIFT))
#define RED_MODE_X2                        ((uint32)(RED__X2              <<  \
                                                                  RED_QUAD_MODE_SHIFT))
#define RED_MODE_X4                        ((uint32)(RED__X4              <<  \
                                                                  RED_QUAD_MODE_SHIFT))

/* Counter modes */
#define RED_COUNT_UP                       ((uint32)(RED__COUNT_UP        <<  \
                                                                  RED_UPDOWN_SHIFT))
#define RED_COUNT_DOWN                     ((uint32)(RED__COUNT_DOWN      <<  \
                                                                  RED_UPDOWN_SHIFT))
#define RED_COUNT_UPDOWN0                  ((uint32)(RED__COUNT_UPDOWN0   <<  \
                                                                  RED_UPDOWN_SHIFT))
#define RED_COUNT_UPDOWN1                  ((uint32)(RED__COUNT_UPDOWN1   <<  \
                                                                  RED_UPDOWN_SHIFT))

/* PWM output invert */
#define RED_INVERT_LINE                    ((uint32)(RED__INVERSE         <<  \
                                                                  RED_INV_OUT_SHIFT))
#define RED_INVERT_LINE_N                  ((uint32)(RED__INVERSE         <<  \
                                                                  RED_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define RED_TRIG_RISING                    ((uint32)RED__TRIG_RISING)
#define RED_TRIG_FALLING                   ((uint32)RED__TRIG_FALLING)
#define RED_TRIG_BOTH                      ((uint32)RED__TRIG_BOTH)
#define RED_TRIG_LEVEL                     ((uint32)RED__TRIG_LEVEL)

/* Interrupt mask */
#define RED_INTR_MASK_TC                   ((uint32)RED__INTR_MASK_TC)
#define RED_INTR_MASK_CC_MATCH             ((uint32)RED__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define RED_CC_MATCH_SET                   (0x00u)
#define RED_CC_MATCH_CLEAR                 (0x01u)
#define RED_CC_MATCH_INVERT                (0x02u)
#define RED_CC_MATCH_NO_CHANGE             (0x03u)
#define RED_OVERLOW_SET                    (0x00u)
#define RED_OVERLOW_CLEAR                  (0x04u)
#define RED_OVERLOW_INVERT                 (0x08u)
#define RED_OVERLOW_NO_CHANGE              (0x0Cu)
#define RED_UNDERFLOW_SET                  (0x00u)
#define RED_UNDERFLOW_CLEAR                (0x10u)
#define RED_UNDERFLOW_INVERT               (0x20u)
#define RED_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define RED_PWM_MODE_LEFT                  (RED_CC_MATCH_CLEAR        |   \
                                                         RED_OVERLOW_SET           |   \
                                                         RED_UNDERFLOW_NO_CHANGE)
#define RED_PWM_MODE_RIGHT                 (RED_CC_MATCH_SET          |   \
                                                         RED_OVERLOW_NO_CHANGE     |   \
                                                         RED_UNDERFLOW_CLEAR)
#define RED_PWM_MODE_ASYM                  (RED_CC_MATCH_INVERT       |   \
                                                         RED_OVERLOW_SET           |   \
                                                         RED_UNDERFLOW_CLEAR)

#if (RED_CY_TCPWM_V2)
    #if(RED_CY_TCPWM_4000)
        #define RED_PWM_MODE_CENTER                (RED_CC_MATCH_INVERT       |   \
                                                                 RED_OVERLOW_NO_CHANGE     |   \
                                                                 RED_UNDERFLOW_CLEAR)
    #else
        #define RED_PWM_MODE_CENTER                (RED_CC_MATCH_INVERT       |   \
                                                                 RED_OVERLOW_SET           |   \
                                                                 RED_UNDERFLOW_CLEAR)
    #endif /* (RED_CY_TCPWM_4000) */
#else
    #define RED_PWM_MODE_CENTER                (RED_CC_MATCH_INVERT       |   \
                                                             RED_OVERLOW_NO_CHANGE     |   \
                                                             RED_UNDERFLOW_CLEAR)
#endif /* (RED_CY_TCPWM_NEW) */

/* Command operations without condition */
#define RED_CMD_CAPTURE                    (0u)
#define RED_CMD_RELOAD                     (8u)
#define RED_CMD_STOP                       (16u)
#define RED_CMD_START                      (24u)

/* Status */
#define RED_STATUS_DOWN                    (1u)
#define RED_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   RED_Init(void);
void   RED_Enable(void);
void   RED_Start(void);
void   RED_Stop(void);

void   RED_SetMode(uint32 mode);
void   RED_SetCounterMode(uint32 counterMode);
void   RED_SetPWMMode(uint32 modeMask);
void   RED_SetQDMode(uint32 qdMode);

void   RED_SetPrescaler(uint32 prescaler);
void   RED_TriggerCommand(uint32 mask, uint32 command);
void   RED_SetOneShot(uint32 oneShotEnable);
uint32 RED_ReadStatus(void);

void   RED_SetPWMSyncKill(uint32 syncKillEnable);
void   RED_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   RED_SetPWMDeadTime(uint32 deadTime);
void   RED_SetPWMInvert(uint32 mask);

void   RED_SetInterruptMode(uint32 interruptMask);
uint32 RED_GetInterruptSourceMasked(void);
uint32 RED_GetInterruptSource(void);
void   RED_ClearInterrupt(uint32 interruptMask);
void   RED_SetInterrupt(uint32 interruptMask);

void   RED_WriteCounter(uint32 count);
uint32 RED_ReadCounter(void);

uint32 RED_ReadCapture(void);
uint32 RED_ReadCaptureBuf(void);

void   RED_WritePeriod(uint32 period);
uint32 RED_ReadPeriod(void);
void   RED_WritePeriodBuf(uint32 periodBuf);
uint32 RED_ReadPeriodBuf(void);

void   RED_WriteCompare(uint32 compare);
uint32 RED_ReadCompare(void);
void   RED_WriteCompareBuf(uint32 compareBuf);
uint32 RED_ReadCompareBuf(void);

void   RED_SetPeriodSwap(uint32 swapEnable);
void   RED_SetCompareSwap(uint32 swapEnable);

void   RED_SetCaptureMode(uint32 triggerMode);
void   RED_SetReloadMode(uint32 triggerMode);
void   RED_SetStartMode(uint32 triggerMode);
void   RED_SetStopMode(uint32 triggerMode);
void   RED_SetCountMode(uint32 triggerMode);

void   RED_SaveConfig(void);
void   RED_RestoreConfig(void);
void   RED_Sleep(void);
void   RED_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define RED_BLOCK_CONTROL_REG              (*(reg32 *) RED_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define RED_BLOCK_CONTROL_PTR              ( (reg32 *) RED_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define RED_COMMAND_REG                    (*(reg32 *) RED_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define RED_COMMAND_PTR                    ( (reg32 *) RED_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define RED_INTRRUPT_CAUSE_REG             (*(reg32 *) RED_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define RED_INTRRUPT_CAUSE_PTR             ( (reg32 *) RED_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define RED_CONTROL_REG                    (*(reg32 *) RED_cy_m0s8_tcpwm_1__CTRL )
#define RED_CONTROL_PTR                    ( (reg32 *) RED_cy_m0s8_tcpwm_1__CTRL )
#define RED_STATUS_REG                     (*(reg32 *) RED_cy_m0s8_tcpwm_1__STATUS )
#define RED_STATUS_PTR                     ( (reg32 *) RED_cy_m0s8_tcpwm_1__STATUS )
#define RED_COUNTER_REG                    (*(reg32 *) RED_cy_m0s8_tcpwm_1__COUNTER )
#define RED_COUNTER_PTR                    ( (reg32 *) RED_cy_m0s8_tcpwm_1__COUNTER )
#define RED_COMP_CAP_REG                   (*(reg32 *) RED_cy_m0s8_tcpwm_1__CC )
#define RED_COMP_CAP_PTR                   ( (reg32 *) RED_cy_m0s8_tcpwm_1__CC )
#define RED_COMP_CAP_BUF_REG               (*(reg32 *) RED_cy_m0s8_tcpwm_1__CC_BUFF )
#define RED_COMP_CAP_BUF_PTR               ( (reg32 *) RED_cy_m0s8_tcpwm_1__CC_BUFF )
#define RED_PERIOD_REG                     (*(reg32 *) RED_cy_m0s8_tcpwm_1__PERIOD )
#define RED_PERIOD_PTR                     ( (reg32 *) RED_cy_m0s8_tcpwm_1__PERIOD )
#define RED_PERIOD_BUF_REG                 (*(reg32 *) RED_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define RED_PERIOD_BUF_PTR                 ( (reg32 *) RED_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define RED_TRIG_CONTROL0_REG              (*(reg32 *) RED_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define RED_TRIG_CONTROL0_PTR              ( (reg32 *) RED_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define RED_TRIG_CONTROL1_REG              (*(reg32 *) RED_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define RED_TRIG_CONTROL1_PTR              ( (reg32 *) RED_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define RED_TRIG_CONTROL2_REG              (*(reg32 *) RED_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define RED_TRIG_CONTROL2_PTR              ( (reg32 *) RED_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define RED_INTERRUPT_REQ_REG              (*(reg32 *) RED_cy_m0s8_tcpwm_1__INTR )
#define RED_INTERRUPT_REQ_PTR              ( (reg32 *) RED_cy_m0s8_tcpwm_1__INTR )
#define RED_INTERRUPT_SET_REG              (*(reg32 *) RED_cy_m0s8_tcpwm_1__INTR_SET )
#define RED_INTERRUPT_SET_PTR              ( (reg32 *) RED_cy_m0s8_tcpwm_1__INTR_SET )
#define RED_INTERRUPT_MASK_REG             (*(reg32 *) RED_cy_m0s8_tcpwm_1__INTR_MASK )
#define RED_INTERRUPT_MASK_PTR             ( (reg32 *) RED_cy_m0s8_tcpwm_1__INTR_MASK )
#define RED_INTERRUPT_MASKED_REG           (*(reg32 *) RED_cy_m0s8_tcpwm_1__INTR_MASKED )
#define RED_INTERRUPT_MASKED_PTR           ( (reg32 *) RED_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define RED_MASK                           ((uint32)RED_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define RED_RELOAD_CC_SHIFT                (0u)
#define RED_RELOAD_PERIOD_SHIFT            (1u)
#define RED_PWM_SYNC_KILL_SHIFT            (2u)
#define RED_PWM_STOP_KILL_SHIFT            (3u)
#define RED_PRESCALER_SHIFT                (8u)
#define RED_UPDOWN_SHIFT                   (16u)
#define RED_ONESHOT_SHIFT                  (18u)
#define RED_QUAD_MODE_SHIFT                (20u)
#define RED_INV_OUT_SHIFT                  (20u)
#define RED_INV_COMPL_OUT_SHIFT            (21u)
#define RED_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define RED_RELOAD_CC_MASK                 ((uint32)(RED_1BIT_MASK        <<  \
                                                                            RED_RELOAD_CC_SHIFT))
#define RED_RELOAD_PERIOD_MASK             ((uint32)(RED_1BIT_MASK        <<  \
                                                                            RED_RELOAD_PERIOD_SHIFT))
#define RED_PWM_SYNC_KILL_MASK             ((uint32)(RED_1BIT_MASK        <<  \
                                                                            RED_PWM_SYNC_KILL_SHIFT))
#define RED_PWM_STOP_KILL_MASK             ((uint32)(RED_1BIT_MASK        <<  \
                                                                            RED_PWM_STOP_KILL_SHIFT))
#define RED_PRESCALER_MASK                 ((uint32)(RED_8BIT_MASK        <<  \
                                                                            RED_PRESCALER_SHIFT))
#define RED_UPDOWN_MASK                    ((uint32)(RED_2BIT_MASK        <<  \
                                                                            RED_UPDOWN_SHIFT))
#define RED_ONESHOT_MASK                   ((uint32)(RED_1BIT_MASK        <<  \
                                                                            RED_ONESHOT_SHIFT))
#define RED_QUAD_MODE_MASK                 ((uint32)(RED_3BIT_MASK        <<  \
                                                                            RED_QUAD_MODE_SHIFT))
#define RED_INV_OUT_MASK                   ((uint32)(RED_2BIT_MASK        <<  \
                                                                            RED_INV_OUT_SHIFT))
#define RED_MODE_MASK                      ((uint32)(RED_3BIT_MASK        <<  \
                                                                            RED_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define RED_CAPTURE_SHIFT                  (0u)
#define RED_COUNT_SHIFT                    (2u)
#define RED_RELOAD_SHIFT                   (4u)
#define RED_STOP_SHIFT                     (6u)
#define RED_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define RED_CAPTURE_MASK                   ((uint32)(RED_2BIT_MASK        <<  \
                                                                  RED_CAPTURE_SHIFT))
#define RED_COUNT_MASK                     ((uint32)(RED_2BIT_MASK        <<  \
                                                                  RED_COUNT_SHIFT))
#define RED_RELOAD_MASK                    ((uint32)(RED_2BIT_MASK        <<  \
                                                                  RED_RELOAD_SHIFT))
#define RED_STOP_MASK                      ((uint32)(RED_2BIT_MASK        <<  \
                                                                  RED_STOP_SHIFT))
#define RED_START_MASK                     ((uint32)(RED_2BIT_MASK        <<  \
                                                                  RED_START_SHIFT))

/* MASK */
#define RED_1BIT_MASK                      ((uint32)0x01u)
#define RED_2BIT_MASK                      ((uint32)0x03u)
#define RED_3BIT_MASK                      ((uint32)0x07u)
#define RED_6BIT_MASK                      ((uint32)0x3Fu)
#define RED_8BIT_MASK                      ((uint32)0xFFu)
#define RED_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define RED_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define RED_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(RED_QUAD_ENCODING_MODES     << RED_QUAD_MODE_SHIFT))       |\
         ((uint32)(RED_CONFIG                  << RED_MODE_SHIFT)))

#define RED_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(RED_PWM_STOP_EVENT          << RED_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(RED_PWM_OUT_INVERT          << RED_INV_OUT_SHIFT))         |\
         ((uint32)(RED_PWM_OUT_N_INVERT        << RED_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(RED_PWM_MODE                << RED_MODE_SHIFT)))

#define RED_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(RED_PWM_RUN_MODE         << RED_ONESHOT_SHIFT))
            
#define RED_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(RED_PWM_ALIGN            << RED_UPDOWN_SHIFT))

#define RED_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(RED_PWM_KILL_EVENT      << RED_PWM_SYNC_KILL_SHIFT))

#define RED_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(RED_PWM_DEAD_TIME_CYCLE  << RED_PRESCALER_SHIFT))

#define RED_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(RED_PWM_PRESCALER        << RED_PRESCALER_SHIFT))

#define RED_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(RED_TC_PRESCALER            << RED_PRESCALER_SHIFT))       |\
         ((uint32)(RED_TC_COUNTER_MODE         << RED_UPDOWN_SHIFT))          |\
         ((uint32)(RED_TC_RUN_MODE             << RED_ONESHOT_SHIFT))         |\
         ((uint32)(RED_TC_COMP_CAP_MODE        << RED_MODE_SHIFT)))
        
#define RED_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(RED_QUAD_PHIA_SIGNAL_MODE   << RED_COUNT_SHIFT))           |\
         ((uint32)(RED_QUAD_INDEX_SIGNAL_MODE  << RED_RELOAD_SHIFT))          |\
         ((uint32)(RED_QUAD_STOP_SIGNAL_MODE   << RED_STOP_SHIFT))            |\
         ((uint32)(RED_QUAD_PHIB_SIGNAL_MODE   << RED_START_SHIFT)))

#define RED_PWM_SIGNALS_MODES                                                              \
        (((uint32)(RED_PWM_SWITCH_SIGNAL_MODE  << RED_CAPTURE_SHIFT))         |\
         ((uint32)(RED_PWM_COUNT_SIGNAL_MODE   << RED_COUNT_SHIFT))           |\
         ((uint32)(RED_PWM_RELOAD_SIGNAL_MODE  << RED_RELOAD_SHIFT))          |\
         ((uint32)(RED_PWM_STOP_SIGNAL_MODE    << RED_STOP_SHIFT))            |\
         ((uint32)(RED_PWM_START_SIGNAL_MODE   << RED_START_SHIFT)))

#define RED_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(RED_TC_CAPTURE_SIGNAL_MODE  << RED_CAPTURE_SHIFT))         |\
         ((uint32)(RED_TC_COUNT_SIGNAL_MODE    << RED_COUNT_SHIFT))           |\
         ((uint32)(RED_TC_RELOAD_SIGNAL_MODE   << RED_RELOAD_SHIFT))          |\
         ((uint32)(RED_TC_STOP_SIGNAL_MODE     << RED_STOP_SHIFT))            |\
         ((uint32)(RED_TC_START_SIGNAL_MODE    << RED_START_SHIFT)))
        
#define RED_TIMER_UPDOWN_CNT_USED                                                          \
                ((RED__COUNT_UPDOWN0 == RED_TC_COUNTER_MODE)                  ||\
                 (RED__COUNT_UPDOWN1 == RED_TC_COUNTER_MODE))

#define RED_PWM_UPDOWN_CNT_USED                                                            \
                ((RED__CENTER == RED_PWM_ALIGN)                               ||\
                 (RED__ASYMMETRIC == RED_PWM_ALIGN))               
        
#define RED_PWM_PR_INIT_VALUE              (1u)
#define RED_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_RED_H */

/* [] END OF FILE */
