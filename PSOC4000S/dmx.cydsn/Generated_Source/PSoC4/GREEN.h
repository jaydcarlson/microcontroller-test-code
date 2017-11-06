/*******************************************************************************
* File Name: GREEN.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the GREEN
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

#if !defined(CY_TCPWM_GREEN_H)
#define CY_TCPWM_GREEN_H


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
} GREEN_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  GREEN_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define GREEN_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define GREEN_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define GREEN_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define GREEN_QUAD_ENCODING_MODES            (0lu)
#define GREEN_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define GREEN_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define GREEN_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define GREEN_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define GREEN_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define GREEN_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define GREEN_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define GREEN_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define GREEN_TC_RUN_MODE                    (0lu)
#define GREEN_TC_COUNTER_MODE                (0lu)
#define GREEN_TC_COMP_CAP_MODE               (2lu)
#define GREEN_TC_PRESCALER                   (0lu)

/* Signal modes */
#define GREEN_TC_RELOAD_SIGNAL_MODE          (0lu)
#define GREEN_TC_COUNT_SIGNAL_MODE           (3lu)
#define GREEN_TC_START_SIGNAL_MODE           (0lu)
#define GREEN_TC_STOP_SIGNAL_MODE            (0lu)
#define GREEN_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define GREEN_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define GREEN_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define GREEN_TC_START_SIGNAL_PRESENT        (0lu)
#define GREEN_TC_STOP_SIGNAL_PRESENT         (0lu)
#define GREEN_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define GREEN_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define GREEN_PWM_KILL_EVENT                 (0lu)
#define GREEN_PWM_STOP_EVENT                 (0lu)
#define GREEN_PWM_MODE                       (4lu)
#define GREEN_PWM_OUT_N_INVERT               (0lu)
#define GREEN_PWM_OUT_INVERT                 (1lu)
#define GREEN_PWM_ALIGN                      (0lu)
#define GREEN_PWM_RUN_MODE                   (0lu)
#define GREEN_PWM_DEAD_TIME_CYCLE            (0lu)
#define GREEN_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define GREEN_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define GREEN_PWM_COUNT_SIGNAL_MODE          (3lu)
#define GREEN_PWM_START_SIGNAL_MODE          (0lu)
#define GREEN_PWM_STOP_SIGNAL_MODE           (0lu)
#define GREEN_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define GREEN_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define GREEN_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define GREEN_PWM_START_SIGNAL_PRESENT       (0lu)
#define GREEN_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define GREEN_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define GREEN_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define GREEN_TC_PERIOD_VALUE                (65535lu)
#define GREEN_TC_COMPARE_VALUE               (65535lu)
#define GREEN_TC_COMPARE_BUF_VALUE           (65535lu)
#define GREEN_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define GREEN_PWM_PERIOD_VALUE               (255lu)
#define GREEN_PWM_PERIOD_BUF_VALUE           (65535lu)
#define GREEN_PWM_PERIOD_SWAP                (0lu)
#define GREEN_PWM_COMPARE_VALUE              (128lu)
#define GREEN_PWM_COMPARE_BUF_VALUE          (65535lu)
#define GREEN_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define GREEN__LEFT 0
#define GREEN__RIGHT 1
#define GREEN__CENTER 2
#define GREEN__ASYMMETRIC 3

#define GREEN__X1 0
#define GREEN__X2 1
#define GREEN__X4 2

#define GREEN__PWM 4
#define GREEN__PWM_DT 5
#define GREEN__PWM_PR 6

#define GREEN__INVERSE 1
#define GREEN__DIRECT 0

#define GREEN__CAPTURE 2
#define GREEN__COMPARE 0

#define GREEN__TRIG_LEVEL 3
#define GREEN__TRIG_RISING 0
#define GREEN__TRIG_FALLING 1
#define GREEN__TRIG_BOTH 2

#define GREEN__INTR_MASK_TC 1
#define GREEN__INTR_MASK_CC_MATCH 2
#define GREEN__INTR_MASK_NONE 0
#define GREEN__INTR_MASK_TC_CC 3

#define GREEN__UNCONFIG 8
#define GREEN__TIMER 1
#define GREEN__QUAD 3
#define GREEN__PWM_SEL 7

#define GREEN__COUNT_UP 0
#define GREEN__COUNT_DOWN 1
#define GREEN__COUNT_UPDOWN0 2
#define GREEN__COUNT_UPDOWN1 3


/* Prescaler */
#define GREEN_PRESCALE_DIVBY1                ((uint32)(0u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY2                ((uint32)(1u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY4                ((uint32)(2u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY8                ((uint32)(3u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY16               ((uint32)(4u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY32               ((uint32)(5u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY64               ((uint32)(6u << GREEN_PRESCALER_SHIFT))
#define GREEN_PRESCALE_DIVBY128              ((uint32)(7u << GREEN_PRESCALER_SHIFT))

/* TCPWM set modes */
#define GREEN_MODE_TIMER_COMPARE             ((uint32)(GREEN__COMPARE         <<  \
                                                                  GREEN_MODE_SHIFT))
#define GREEN_MODE_TIMER_CAPTURE             ((uint32)(GREEN__CAPTURE         <<  \
                                                                  GREEN_MODE_SHIFT))
#define GREEN_MODE_QUAD                      ((uint32)(GREEN__QUAD            <<  \
                                                                  GREEN_MODE_SHIFT))
#define GREEN_MODE_PWM                       ((uint32)(GREEN__PWM             <<  \
                                                                  GREEN_MODE_SHIFT))
#define GREEN_MODE_PWM_DT                    ((uint32)(GREEN__PWM_DT          <<  \
                                                                  GREEN_MODE_SHIFT))
#define GREEN_MODE_PWM_PR                    ((uint32)(GREEN__PWM_PR          <<  \
                                                                  GREEN_MODE_SHIFT))

/* Quad Modes */
#define GREEN_MODE_X1                        ((uint32)(GREEN__X1              <<  \
                                                                  GREEN_QUAD_MODE_SHIFT))
#define GREEN_MODE_X2                        ((uint32)(GREEN__X2              <<  \
                                                                  GREEN_QUAD_MODE_SHIFT))
#define GREEN_MODE_X4                        ((uint32)(GREEN__X4              <<  \
                                                                  GREEN_QUAD_MODE_SHIFT))

/* Counter modes */
#define GREEN_COUNT_UP                       ((uint32)(GREEN__COUNT_UP        <<  \
                                                                  GREEN_UPDOWN_SHIFT))
#define GREEN_COUNT_DOWN                     ((uint32)(GREEN__COUNT_DOWN      <<  \
                                                                  GREEN_UPDOWN_SHIFT))
#define GREEN_COUNT_UPDOWN0                  ((uint32)(GREEN__COUNT_UPDOWN0   <<  \
                                                                  GREEN_UPDOWN_SHIFT))
#define GREEN_COUNT_UPDOWN1                  ((uint32)(GREEN__COUNT_UPDOWN1   <<  \
                                                                  GREEN_UPDOWN_SHIFT))

/* PWM output invert */
#define GREEN_INVERT_LINE                    ((uint32)(GREEN__INVERSE         <<  \
                                                                  GREEN_INV_OUT_SHIFT))
#define GREEN_INVERT_LINE_N                  ((uint32)(GREEN__INVERSE         <<  \
                                                                  GREEN_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define GREEN_TRIG_RISING                    ((uint32)GREEN__TRIG_RISING)
#define GREEN_TRIG_FALLING                   ((uint32)GREEN__TRIG_FALLING)
#define GREEN_TRIG_BOTH                      ((uint32)GREEN__TRIG_BOTH)
#define GREEN_TRIG_LEVEL                     ((uint32)GREEN__TRIG_LEVEL)

/* Interrupt mask */
#define GREEN_INTR_MASK_TC                   ((uint32)GREEN__INTR_MASK_TC)
#define GREEN_INTR_MASK_CC_MATCH             ((uint32)GREEN__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define GREEN_CC_MATCH_SET                   (0x00u)
#define GREEN_CC_MATCH_CLEAR                 (0x01u)
#define GREEN_CC_MATCH_INVERT                (0x02u)
#define GREEN_CC_MATCH_NO_CHANGE             (0x03u)
#define GREEN_OVERLOW_SET                    (0x00u)
#define GREEN_OVERLOW_CLEAR                  (0x04u)
#define GREEN_OVERLOW_INVERT                 (0x08u)
#define GREEN_OVERLOW_NO_CHANGE              (0x0Cu)
#define GREEN_UNDERFLOW_SET                  (0x00u)
#define GREEN_UNDERFLOW_CLEAR                (0x10u)
#define GREEN_UNDERFLOW_INVERT               (0x20u)
#define GREEN_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define GREEN_PWM_MODE_LEFT                  (GREEN_CC_MATCH_CLEAR        |   \
                                                         GREEN_OVERLOW_SET           |   \
                                                         GREEN_UNDERFLOW_NO_CHANGE)
#define GREEN_PWM_MODE_RIGHT                 (GREEN_CC_MATCH_SET          |   \
                                                         GREEN_OVERLOW_NO_CHANGE     |   \
                                                         GREEN_UNDERFLOW_CLEAR)
#define GREEN_PWM_MODE_ASYM                  (GREEN_CC_MATCH_INVERT       |   \
                                                         GREEN_OVERLOW_SET           |   \
                                                         GREEN_UNDERFLOW_CLEAR)

#if (GREEN_CY_TCPWM_V2)
    #if(GREEN_CY_TCPWM_4000)
        #define GREEN_PWM_MODE_CENTER                (GREEN_CC_MATCH_INVERT       |   \
                                                                 GREEN_OVERLOW_NO_CHANGE     |   \
                                                                 GREEN_UNDERFLOW_CLEAR)
    #else
        #define GREEN_PWM_MODE_CENTER                (GREEN_CC_MATCH_INVERT       |   \
                                                                 GREEN_OVERLOW_SET           |   \
                                                                 GREEN_UNDERFLOW_CLEAR)
    #endif /* (GREEN_CY_TCPWM_4000) */
#else
    #define GREEN_PWM_MODE_CENTER                (GREEN_CC_MATCH_INVERT       |   \
                                                             GREEN_OVERLOW_NO_CHANGE     |   \
                                                             GREEN_UNDERFLOW_CLEAR)
#endif /* (GREEN_CY_TCPWM_NEW) */

/* Command operations without condition */
#define GREEN_CMD_CAPTURE                    (0u)
#define GREEN_CMD_RELOAD                     (8u)
#define GREEN_CMD_STOP                       (16u)
#define GREEN_CMD_START                      (24u)

/* Status */
#define GREEN_STATUS_DOWN                    (1u)
#define GREEN_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   GREEN_Init(void);
void   GREEN_Enable(void);
void   GREEN_Start(void);
void   GREEN_Stop(void);

void   GREEN_SetMode(uint32 mode);
void   GREEN_SetCounterMode(uint32 counterMode);
void   GREEN_SetPWMMode(uint32 modeMask);
void   GREEN_SetQDMode(uint32 qdMode);

void   GREEN_SetPrescaler(uint32 prescaler);
void   GREEN_TriggerCommand(uint32 mask, uint32 command);
void   GREEN_SetOneShot(uint32 oneShotEnable);
uint32 GREEN_ReadStatus(void);

void   GREEN_SetPWMSyncKill(uint32 syncKillEnable);
void   GREEN_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   GREEN_SetPWMDeadTime(uint32 deadTime);
void   GREEN_SetPWMInvert(uint32 mask);

void   GREEN_SetInterruptMode(uint32 interruptMask);
uint32 GREEN_GetInterruptSourceMasked(void);
uint32 GREEN_GetInterruptSource(void);
void   GREEN_ClearInterrupt(uint32 interruptMask);
void   GREEN_SetInterrupt(uint32 interruptMask);

void   GREEN_WriteCounter(uint32 count);
uint32 GREEN_ReadCounter(void);

uint32 GREEN_ReadCapture(void);
uint32 GREEN_ReadCaptureBuf(void);

void   GREEN_WritePeriod(uint32 period);
uint32 GREEN_ReadPeriod(void);
void   GREEN_WritePeriodBuf(uint32 periodBuf);
uint32 GREEN_ReadPeriodBuf(void);

void   GREEN_WriteCompare(uint32 compare);
uint32 GREEN_ReadCompare(void);
void   GREEN_WriteCompareBuf(uint32 compareBuf);
uint32 GREEN_ReadCompareBuf(void);

void   GREEN_SetPeriodSwap(uint32 swapEnable);
void   GREEN_SetCompareSwap(uint32 swapEnable);

void   GREEN_SetCaptureMode(uint32 triggerMode);
void   GREEN_SetReloadMode(uint32 triggerMode);
void   GREEN_SetStartMode(uint32 triggerMode);
void   GREEN_SetStopMode(uint32 triggerMode);
void   GREEN_SetCountMode(uint32 triggerMode);

void   GREEN_SaveConfig(void);
void   GREEN_RestoreConfig(void);
void   GREEN_Sleep(void);
void   GREEN_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define GREEN_BLOCK_CONTROL_REG              (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define GREEN_BLOCK_CONTROL_PTR              ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define GREEN_COMMAND_REG                    (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define GREEN_COMMAND_PTR                    ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define GREEN_INTRRUPT_CAUSE_REG             (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define GREEN_INTRRUPT_CAUSE_PTR             ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define GREEN_CONTROL_REG                    (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__CTRL )
#define GREEN_CONTROL_PTR                    ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__CTRL )
#define GREEN_STATUS_REG                     (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__STATUS )
#define GREEN_STATUS_PTR                     ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__STATUS )
#define GREEN_COUNTER_REG                    (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__COUNTER )
#define GREEN_COUNTER_PTR                    ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__COUNTER )
#define GREEN_COMP_CAP_REG                   (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__CC )
#define GREEN_COMP_CAP_PTR                   ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__CC )
#define GREEN_COMP_CAP_BUF_REG               (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__CC_BUFF )
#define GREEN_COMP_CAP_BUF_PTR               ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__CC_BUFF )
#define GREEN_PERIOD_REG                     (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__PERIOD )
#define GREEN_PERIOD_PTR                     ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__PERIOD )
#define GREEN_PERIOD_BUF_REG                 (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define GREEN_PERIOD_BUF_PTR                 ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define GREEN_TRIG_CONTROL0_REG              (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define GREEN_TRIG_CONTROL0_PTR              ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define GREEN_TRIG_CONTROL1_REG              (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define GREEN_TRIG_CONTROL1_PTR              ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define GREEN_TRIG_CONTROL2_REG              (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define GREEN_TRIG_CONTROL2_PTR              ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define GREEN_INTERRUPT_REQ_REG              (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR )
#define GREEN_INTERRUPT_REQ_PTR              ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR )
#define GREEN_INTERRUPT_SET_REG              (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR_SET )
#define GREEN_INTERRUPT_SET_PTR              ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR_SET )
#define GREEN_INTERRUPT_MASK_REG             (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR_MASK )
#define GREEN_INTERRUPT_MASK_PTR             ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR_MASK )
#define GREEN_INTERRUPT_MASKED_REG           (*(reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR_MASKED )
#define GREEN_INTERRUPT_MASKED_PTR           ( (reg32 *) GREEN_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define GREEN_MASK                           ((uint32)GREEN_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define GREEN_RELOAD_CC_SHIFT                (0u)
#define GREEN_RELOAD_PERIOD_SHIFT            (1u)
#define GREEN_PWM_SYNC_KILL_SHIFT            (2u)
#define GREEN_PWM_STOP_KILL_SHIFT            (3u)
#define GREEN_PRESCALER_SHIFT                (8u)
#define GREEN_UPDOWN_SHIFT                   (16u)
#define GREEN_ONESHOT_SHIFT                  (18u)
#define GREEN_QUAD_MODE_SHIFT                (20u)
#define GREEN_INV_OUT_SHIFT                  (20u)
#define GREEN_INV_COMPL_OUT_SHIFT            (21u)
#define GREEN_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define GREEN_RELOAD_CC_MASK                 ((uint32)(GREEN_1BIT_MASK        <<  \
                                                                            GREEN_RELOAD_CC_SHIFT))
#define GREEN_RELOAD_PERIOD_MASK             ((uint32)(GREEN_1BIT_MASK        <<  \
                                                                            GREEN_RELOAD_PERIOD_SHIFT))
#define GREEN_PWM_SYNC_KILL_MASK             ((uint32)(GREEN_1BIT_MASK        <<  \
                                                                            GREEN_PWM_SYNC_KILL_SHIFT))
#define GREEN_PWM_STOP_KILL_MASK             ((uint32)(GREEN_1BIT_MASK        <<  \
                                                                            GREEN_PWM_STOP_KILL_SHIFT))
#define GREEN_PRESCALER_MASK                 ((uint32)(GREEN_8BIT_MASK        <<  \
                                                                            GREEN_PRESCALER_SHIFT))
#define GREEN_UPDOWN_MASK                    ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                            GREEN_UPDOWN_SHIFT))
#define GREEN_ONESHOT_MASK                   ((uint32)(GREEN_1BIT_MASK        <<  \
                                                                            GREEN_ONESHOT_SHIFT))
#define GREEN_QUAD_MODE_MASK                 ((uint32)(GREEN_3BIT_MASK        <<  \
                                                                            GREEN_QUAD_MODE_SHIFT))
#define GREEN_INV_OUT_MASK                   ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                            GREEN_INV_OUT_SHIFT))
#define GREEN_MODE_MASK                      ((uint32)(GREEN_3BIT_MASK        <<  \
                                                                            GREEN_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define GREEN_CAPTURE_SHIFT                  (0u)
#define GREEN_COUNT_SHIFT                    (2u)
#define GREEN_RELOAD_SHIFT                   (4u)
#define GREEN_STOP_SHIFT                     (6u)
#define GREEN_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define GREEN_CAPTURE_MASK                   ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                  GREEN_CAPTURE_SHIFT))
#define GREEN_COUNT_MASK                     ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                  GREEN_COUNT_SHIFT))
#define GREEN_RELOAD_MASK                    ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                  GREEN_RELOAD_SHIFT))
#define GREEN_STOP_MASK                      ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                  GREEN_STOP_SHIFT))
#define GREEN_START_MASK                     ((uint32)(GREEN_2BIT_MASK        <<  \
                                                                  GREEN_START_SHIFT))

/* MASK */
#define GREEN_1BIT_MASK                      ((uint32)0x01u)
#define GREEN_2BIT_MASK                      ((uint32)0x03u)
#define GREEN_3BIT_MASK                      ((uint32)0x07u)
#define GREEN_6BIT_MASK                      ((uint32)0x3Fu)
#define GREEN_8BIT_MASK                      ((uint32)0xFFu)
#define GREEN_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define GREEN_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define GREEN_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(GREEN_QUAD_ENCODING_MODES     << GREEN_QUAD_MODE_SHIFT))       |\
         ((uint32)(GREEN_CONFIG                  << GREEN_MODE_SHIFT)))

#define GREEN_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(GREEN_PWM_STOP_EVENT          << GREEN_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(GREEN_PWM_OUT_INVERT          << GREEN_INV_OUT_SHIFT))         |\
         ((uint32)(GREEN_PWM_OUT_N_INVERT        << GREEN_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(GREEN_PWM_MODE                << GREEN_MODE_SHIFT)))

#define GREEN_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(GREEN_PWM_RUN_MODE         << GREEN_ONESHOT_SHIFT))
            
#define GREEN_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(GREEN_PWM_ALIGN            << GREEN_UPDOWN_SHIFT))

#define GREEN_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(GREEN_PWM_KILL_EVENT      << GREEN_PWM_SYNC_KILL_SHIFT))

#define GREEN_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(GREEN_PWM_DEAD_TIME_CYCLE  << GREEN_PRESCALER_SHIFT))

#define GREEN_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(GREEN_PWM_PRESCALER        << GREEN_PRESCALER_SHIFT))

#define GREEN_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(GREEN_TC_PRESCALER            << GREEN_PRESCALER_SHIFT))       |\
         ((uint32)(GREEN_TC_COUNTER_MODE         << GREEN_UPDOWN_SHIFT))          |\
         ((uint32)(GREEN_TC_RUN_MODE             << GREEN_ONESHOT_SHIFT))         |\
         ((uint32)(GREEN_TC_COMP_CAP_MODE        << GREEN_MODE_SHIFT)))
        
#define GREEN_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(GREEN_QUAD_PHIA_SIGNAL_MODE   << GREEN_COUNT_SHIFT))           |\
         ((uint32)(GREEN_QUAD_INDEX_SIGNAL_MODE  << GREEN_RELOAD_SHIFT))          |\
         ((uint32)(GREEN_QUAD_STOP_SIGNAL_MODE   << GREEN_STOP_SHIFT))            |\
         ((uint32)(GREEN_QUAD_PHIB_SIGNAL_MODE   << GREEN_START_SHIFT)))

#define GREEN_PWM_SIGNALS_MODES                                                              \
        (((uint32)(GREEN_PWM_SWITCH_SIGNAL_MODE  << GREEN_CAPTURE_SHIFT))         |\
         ((uint32)(GREEN_PWM_COUNT_SIGNAL_MODE   << GREEN_COUNT_SHIFT))           |\
         ((uint32)(GREEN_PWM_RELOAD_SIGNAL_MODE  << GREEN_RELOAD_SHIFT))          |\
         ((uint32)(GREEN_PWM_STOP_SIGNAL_MODE    << GREEN_STOP_SHIFT))            |\
         ((uint32)(GREEN_PWM_START_SIGNAL_MODE   << GREEN_START_SHIFT)))

#define GREEN_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(GREEN_TC_CAPTURE_SIGNAL_MODE  << GREEN_CAPTURE_SHIFT))         |\
         ((uint32)(GREEN_TC_COUNT_SIGNAL_MODE    << GREEN_COUNT_SHIFT))           |\
         ((uint32)(GREEN_TC_RELOAD_SIGNAL_MODE   << GREEN_RELOAD_SHIFT))          |\
         ((uint32)(GREEN_TC_STOP_SIGNAL_MODE     << GREEN_STOP_SHIFT))            |\
         ((uint32)(GREEN_TC_START_SIGNAL_MODE    << GREEN_START_SHIFT)))
        
#define GREEN_TIMER_UPDOWN_CNT_USED                                                          \
                ((GREEN__COUNT_UPDOWN0 == GREEN_TC_COUNTER_MODE)                  ||\
                 (GREEN__COUNT_UPDOWN1 == GREEN_TC_COUNTER_MODE))

#define GREEN_PWM_UPDOWN_CNT_USED                                                            \
                ((GREEN__CENTER == GREEN_PWM_ALIGN)                               ||\
                 (GREEN__ASYMMETRIC == GREEN_PWM_ALIGN))               
        
#define GREEN_PWM_PR_INIT_VALUE              (1u)
#define GREEN_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_GREEN_H */

/* [] END OF FILE */
