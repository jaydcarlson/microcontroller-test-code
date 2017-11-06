/*******************************************************************************
* File Name: BLUE.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the BLUE
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

#if !defined(CY_TCPWM_BLUE_H)
#define CY_TCPWM_BLUE_H


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
} BLUE_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  BLUE_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define BLUE_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define BLUE_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define BLUE_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define BLUE_QUAD_ENCODING_MODES            (0lu)
#define BLUE_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define BLUE_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define BLUE_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define BLUE_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define BLUE_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define BLUE_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define BLUE_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define BLUE_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define BLUE_TC_RUN_MODE                    (0lu)
#define BLUE_TC_COUNTER_MODE                (0lu)
#define BLUE_TC_COMP_CAP_MODE               (2lu)
#define BLUE_TC_PRESCALER                   (0lu)

/* Signal modes */
#define BLUE_TC_RELOAD_SIGNAL_MODE          (0lu)
#define BLUE_TC_COUNT_SIGNAL_MODE           (3lu)
#define BLUE_TC_START_SIGNAL_MODE           (0lu)
#define BLUE_TC_STOP_SIGNAL_MODE            (0lu)
#define BLUE_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define BLUE_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define BLUE_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define BLUE_TC_START_SIGNAL_PRESENT        (0lu)
#define BLUE_TC_STOP_SIGNAL_PRESENT         (0lu)
#define BLUE_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BLUE_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define BLUE_PWM_KILL_EVENT                 (0lu)
#define BLUE_PWM_STOP_EVENT                 (0lu)
#define BLUE_PWM_MODE                       (4lu)
#define BLUE_PWM_OUT_N_INVERT               (0lu)
#define BLUE_PWM_OUT_INVERT                 (1lu)
#define BLUE_PWM_ALIGN                      (0lu)
#define BLUE_PWM_RUN_MODE                   (0lu)
#define BLUE_PWM_DEAD_TIME_CYCLE            (0lu)
#define BLUE_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define BLUE_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define BLUE_PWM_COUNT_SIGNAL_MODE          (3lu)
#define BLUE_PWM_START_SIGNAL_MODE          (0lu)
#define BLUE_PWM_STOP_SIGNAL_MODE           (0lu)
#define BLUE_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define BLUE_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define BLUE_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define BLUE_PWM_START_SIGNAL_PRESENT       (0lu)
#define BLUE_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define BLUE_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BLUE_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define BLUE_TC_PERIOD_VALUE                (65535lu)
#define BLUE_TC_COMPARE_VALUE               (65535lu)
#define BLUE_TC_COMPARE_BUF_VALUE           (65535lu)
#define BLUE_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define BLUE_PWM_PERIOD_VALUE               (255lu)
#define BLUE_PWM_PERIOD_BUF_VALUE           (65535lu)
#define BLUE_PWM_PERIOD_SWAP                (0lu)
#define BLUE_PWM_COMPARE_VALUE              (128lu)
#define BLUE_PWM_COMPARE_BUF_VALUE          (65535lu)
#define BLUE_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define BLUE__LEFT 0
#define BLUE__RIGHT 1
#define BLUE__CENTER 2
#define BLUE__ASYMMETRIC 3

#define BLUE__X1 0
#define BLUE__X2 1
#define BLUE__X4 2

#define BLUE__PWM 4
#define BLUE__PWM_DT 5
#define BLUE__PWM_PR 6

#define BLUE__INVERSE 1
#define BLUE__DIRECT 0

#define BLUE__CAPTURE 2
#define BLUE__COMPARE 0

#define BLUE__TRIG_LEVEL 3
#define BLUE__TRIG_RISING 0
#define BLUE__TRIG_FALLING 1
#define BLUE__TRIG_BOTH 2

#define BLUE__INTR_MASK_TC 1
#define BLUE__INTR_MASK_CC_MATCH 2
#define BLUE__INTR_MASK_NONE 0
#define BLUE__INTR_MASK_TC_CC 3

#define BLUE__UNCONFIG 8
#define BLUE__TIMER 1
#define BLUE__QUAD 3
#define BLUE__PWM_SEL 7

#define BLUE__COUNT_UP 0
#define BLUE__COUNT_DOWN 1
#define BLUE__COUNT_UPDOWN0 2
#define BLUE__COUNT_UPDOWN1 3


/* Prescaler */
#define BLUE_PRESCALE_DIVBY1                ((uint32)(0u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY2                ((uint32)(1u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY4                ((uint32)(2u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY8                ((uint32)(3u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY16               ((uint32)(4u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY32               ((uint32)(5u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY64               ((uint32)(6u << BLUE_PRESCALER_SHIFT))
#define BLUE_PRESCALE_DIVBY128              ((uint32)(7u << BLUE_PRESCALER_SHIFT))

/* TCPWM set modes */
#define BLUE_MODE_TIMER_COMPARE             ((uint32)(BLUE__COMPARE         <<  \
                                                                  BLUE_MODE_SHIFT))
#define BLUE_MODE_TIMER_CAPTURE             ((uint32)(BLUE__CAPTURE         <<  \
                                                                  BLUE_MODE_SHIFT))
#define BLUE_MODE_QUAD                      ((uint32)(BLUE__QUAD            <<  \
                                                                  BLUE_MODE_SHIFT))
#define BLUE_MODE_PWM                       ((uint32)(BLUE__PWM             <<  \
                                                                  BLUE_MODE_SHIFT))
#define BLUE_MODE_PWM_DT                    ((uint32)(BLUE__PWM_DT          <<  \
                                                                  BLUE_MODE_SHIFT))
#define BLUE_MODE_PWM_PR                    ((uint32)(BLUE__PWM_PR          <<  \
                                                                  BLUE_MODE_SHIFT))

/* Quad Modes */
#define BLUE_MODE_X1                        ((uint32)(BLUE__X1              <<  \
                                                                  BLUE_QUAD_MODE_SHIFT))
#define BLUE_MODE_X2                        ((uint32)(BLUE__X2              <<  \
                                                                  BLUE_QUAD_MODE_SHIFT))
#define BLUE_MODE_X4                        ((uint32)(BLUE__X4              <<  \
                                                                  BLUE_QUAD_MODE_SHIFT))

/* Counter modes */
#define BLUE_COUNT_UP                       ((uint32)(BLUE__COUNT_UP        <<  \
                                                                  BLUE_UPDOWN_SHIFT))
#define BLUE_COUNT_DOWN                     ((uint32)(BLUE__COUNT_DOWN      <<  \
                                                                  BLUE_UPDOWN_SHIFT))
#define BLUE_COUNT_UPDOWN0                  ((uint32)(BLUE__COUNT_UPDOWN0   <<  \
                                                                  BLUE_UPDOWN_SHIFT))
#define BLUE_COUNT_UPDOWN1                  ((uint32)(BLUE__COUNT_UPDOWN1   <<  \
                                                                  BLUE_UPDOWN_SHIFT))

/* PWM output invert */
#define BLUE_INVERT_LINE                    ((uint32)(BLUE__INVERSE         <<  \
                                                                  BLUE_INV_OUT_SHIFT))
#define BLUE_INVERT_LINE_N                  ((uint32)(BLUE__INVERSE         <<  \
                                                                  BLUE_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define BLUE_TRIG_RISING                    ((uint32)BLUE__TRIG_RISING)
#define BLUE_TRIG_FALLING                   ((uint32)BLUE__TRIG_FALLING)
#define BLUE_TRIG_BOTH                      ((uint32)BLUE__TRIG_BOTH)
#define BLUE_TRIG_LEVEL                     ((uint32)BLUE__TRIG_LEVEL)

/* Interrupt mask */
#define BLUE_INTR_MASK_TC                   ((uint32)BLUE__INTR_MASK_TC)
#define BLUE_INTR_MASK_CC_MATCH             ((uint32)BLUE__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define BLUE_CC_MATCH_SET                   (0x00u)
#define BLUE_CC_MATCH_CLEAR                 (0x01u)
#define BLUE_CC_MATCH_INVERT                (0x02u)
#define BLUE_CC_MATCH_NO_CHANGE             (0x03u)
#define BLUE_OVERLOW_SET                    (0x00u)
#define BLUE_OVERLOW_CLEAR                  (0x04u)
#define BLUE_OVERLOW_INVERT                 (0x08u)
#define BLUE_OVERLOW_NO_CHANGE              (0x0Cu)
#define BLUE_UNDERFLOW_SET                  (0x00u)
#define BLUE_UNDERFLOW_CLEAR                (0x10u)
#define BLUE_UNDERFLOW_INVERT               (0x20u)
#define BLUE_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define BLUE_PWM_MODE_LEFT                  (BLUE_CC_MATCH_CLEAR        |   \
                                                         BLUE_OVERLOW_SET           |   \
                                                         BLUE_UNDERFLOW_NO_CHANGE)
#define BLUE_PWM_MODE_RIGHT                 (BLUE_CC_MATCH_SET          |   \
                                                         BLUE_OVERLOW_NO_CHANGE     |   \
                                                         BLUE_UNDERFLOW_CLEAR)
#define BLUE_PWM_MODE_ASYM                  (BLUE_CC_MATCH_INVERT       |   \
                                                         BLUE_OVERLOW_SET           |   \
                                                         BLUE_UNDERFLOW_CLEAR)

#if (BLUE_CY_TCPWM_V2)
    #if(BLUE_CY_TCPWM_4000)
        #define BLUE_PWM_MODE_CENTER                (BLUE_CC_MATCH_INVERT       |   \
                                                                 BLUE_OVERLOW_NO_CHANGE     |   \
                                                                 BLUE_UNDERFLOW_CLEAR)
    #else
        #define BLUE_PWM_MODE_CENTER                (BLUE_CC_MATCH_INVERT       |   \
                                                                 BLUE_OVERLOW_SET           |   \
                                                                 BLUE_UNDERFLOW_CLEAR)
    #endif /* (BLUE_CY_TCPWM_4000) */
#else
    #define BLUE_PWM_MODE_CENTER                (BLUE_CC_MATCH_INVERT       |   \
                                                             BLUE_OVERLOW_NO_CHANGE     |   \
                                                             BLUE_UNDERFLOW_CLEAR)
#endif /* (BLUE_CY_TCPWM_NEW) */

/* Command operations without condition */
#define BLUE_CMD_CAPTURE                    (0u)
#define BLUE_CMD_RELOAD                     (8u)
#define BLUE_CMD_STOP                       (16u)
#define BLUE_CMD_START                      (24u)

/* Status */
#define BLUE_STATUS_DOWN                    (1u)
#define BLUE_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   BLUE_Init(void);
void   BLUE_Enable(void);
void   BLUE_Start(void);
void   BLUE_Stop(void);

void   BLUE_SetMode(uint32 mode);
void   BLUE_SetCounterMode(uint32 counterMode);
void   BLUE_SetPWMMode(uint32 modeMask);
void   BLUE_SetQDMode(uint32 qdMode);

void   BLUE_SetPrescaler(uint32 prescaler);
void   BLUE_TriggerCommand(uint32 mask, uint32 command);
void   BLUE_SetOneShot(uint32 oneShotEnable);
uint32 BLUE_ReadStatus(void);

void   BLUE_SetPWMSyncKill(uint32 syncKillEnable);
void   BLUE_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   BLUE_SetPWMDeadTime(uint32 deadTime);
void   BLUE_SetPWMInvert(uint32 mask);

void   BLUE_SetInterruptMode(uint32 interruptMask);
uint32 BLUE_GetInterruptSourceMasked(void);
uint32 BLUE_GetInterruptSource(void);
void   BLUE_ClearInterrupt(uint32 interruptMask);
void   BLUE_SetInterrupt(uint32 interruptMask);

void   BLUE_WriteCounter(uint32 count);
uint32 BLUE_ReadCounter(void);

uint32 BLUE_ReadCapture(void);
uint32 BLUE_ReadCaptureBuf(void);

void   BLUE_WritePeriod(uint32 period);
uint32 BLUE_ReadPeriod(void);
void   BLUE_WritePeriodBuf(uint32 periodBuf);
uint32 BLUE_ReadPeriodBuf(void);

void   BLUE_WriteCompare(uint32 compare);
uint32 BLUE_ReadCompare(void);
void   BLUE_WriteCompareBuf(uint32 compareBuf);
uint32 BLUE_ReadCompareBuf(void);

void   BLUE_SetPeriodSwap(uint32 swapEnable);
void   BLUE_SetCompareSwap(uint32 swapEnable);

void   BLUE_SetCaptureMode(uint32 triggerMode);
void   BLUE_SetReloadMode(uint32 triggerMode);
void   BLUE_SetStartMode(uint32 triggerMode);
void   BLUE_SetStopMode(uint32 triggerMode);
void   BLUE_SetCountMode(uint32 triggerMode);

void   BLUE_SaveConfig(void);
void   BLUE_RestoreConfig(void);
void   BLUE_Sleep(void);
void   BLUE_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define BLUE_BLOCK_CONTROL_REG              (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BLUE_BLOCK_CONTROL_PTR              ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BLUE_COMMAND_REG                    (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BLUE_COMMAND_PTR                    ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BLUE_INTRRUPT_CAUSE_REG             (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BLUE_INTRRUPT_CAUSE_PTR             ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BLUE_CONTROL_REG                    (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__CTRL )
#define BLUE_CONTROL_PTR                    ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__CTRL )
#define BLUE_STATUS_REG                     (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__STATUS )
#define BLUE_STATUS_PTR                     ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__STATUS )
#define BLUE_COUNTER_REG                    (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__COUNTER )
#define BLUE_COUNTER_PTR                    ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__COUNTER )
#define BLUE_COMP_CAP_REG                   (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__CC )
#define BLUE_COMP_CAP_PTR                   ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__CC )
#define BLUE_COMP_CAP_BUF_REG               (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__CC_BUFF )
#define BLUE_COMP_CAP_BUF_PTR               ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__CC_BUFF )
#define BLUE_PERIOD_REG                     (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__PERIOD )
#define BLUE_PERIOD_PTR                     ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__PERIOD )
#define BLUE_PERIOD_BUF_REG                 (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BLUE_PERIOD_BUF_PTR                 ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BLUE_TRIG_CONTROL0_REG              (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BLUE_TRIG_CONTROL0_PTR              ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BLUE_TRIG_CONTROL1_REG              (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BLUE_TRIG_CONTROL1_PTR              ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BLUE_TRIG_CONTROL2_REG              (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BLUE_TRIG_CONTROL2_PTR              ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BLUE_INTERRUPT_REQ_REG              (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR )
#define BLUE_INTERRUPT_REQ_PTR              ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR )
#define BLUE_INTERRUPT_SET_REG              (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR_SET )
#define BLUE_INTERRUPT_SET_PTR              ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR_SET )
#define BLUE_INTERRUPT_MASK_REG             (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR_MASK )
#define BLUE_INTERRUPT_MASK_PTR             ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR_MASK )
#define BLUE_INTERRUPT_MASKED_REG           (*(reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR_MASKED )
#define BLUE_INTERRUPT_MASKED_PTR           ( (reg32 *) BLUE_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define BLUE_MASK                           ((uint32)BLUE_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define BLUE_RELOAD_CC_SHIFT                (0u)
#define BLUE_RELOAD_PERIOD_SHIFT            (1u)
#define BLUE_PWM_SYNC_KILL_SHIFT            (2u)
#define BLUE_PWM_STOP_KILL_SHIFT            (3u)
#define BLUE_PRESCALER_SHIFT                (8u)
#define BLUE_UPDOWN_SHIFT                   (16u)
#define BLUE_ONESHOT_SHIFT                  (18u)
#define BLUE_QUAD_MODE_SHIFT                (20u)
#define BLUE_INV_OUT_SHIFT                  (20u)
#define BLUE_INV_COMPL_OUT_SHIFT            (21u)
#define BLUE_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define BLUE_RELOAD_CC_MASK                 ((uint32)(BLUE_1BIT_MASK        <<  \
                                                                            BLUE_RELOAD_CC_SHIFT))
#define BLUE_RELOAD_PERIOD_MASK             ((uint32)(BLUE_1BIT_MASK        <<  \
                                                                            BLUE_RELOAD_PERIOD_SHIFT))
#define BLUE_PWM_SYNC_KILL_MASK             ((uint32)(BLUE_1BIT_MASK        <<  \
                                                                            BLUE_PWM_SYNC_KILL_SHIFT))
#define BLUE_PWM_STOP_KILL_MASK             ((uint32)(BLUE_1BIT_MASK        <<  \
                                                                            BLUE_PWM_STOP_KILL_SHIFT))
#define BLUE_PRESCALER_MASK                 ((uint32)(BLUE_8BIT_MASK        <<  \
                                                                            BLUE_PRESCALER_SHIFT))
#define BLUE_UPDOWN_MASK                    ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                            BLUE_UPDOWN_SHIFT))
#define BLUE_ONESHOT_MASK                   ((uint32)(BLUE_1BIT_MASK        <<  \
                                                                            BLUE_ONESHOT_SHIFT))
#define BLUE_QUAD_MODE_MASK                 ((uint32)(BLUE_3BIT_MASK        <<  \
                                                                            BLUE_QUAD_MODE_SHIFT))
#define BLUE_INV_OUT_MASK                   ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                            BLUE_INV_OUT_SHIFT))
#define BLUE_MODE_MASK                      ((uint32)(BLUE_3BIT_MASK        <<  \
                                                                            BLUE_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define BLUE_CAPTURE_SHIFT                  (0u)
#define BLUE_COUNT_SHIFT                    (2u)
#define BLUE_RELOAD_SHIFT                   (4u)
#define BLUE_STOP_SHIFT                     (6u)
#define BLUE_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define BLUE_CAPTURE_MASK                   ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                  BLUE_CAPTURE_SHIFT))
#define BLUE_COUNT_MASK                     ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                  BLUE_COUNT_SHIFT))
#define BLUE_RELOAD_MASK                    ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                  BLUE_RELOAD_SHIFT))
#define BLUE_STOP_MASK                      ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                  BLUE_STOP_SHIFT))
#define BLUE_START_MASK                     ((uint32)(BLUE_2BIT_MASK        <<  \
                                                                  BLUE_START_SHIFT))

/* MASK */
#define BLUE_1BIT_MASK                      ((uint32)0x01u)
#define BLUE_2BIT_MASK                      ((uint32)0x03u)
#define BLUE_3BIT_MASK                      ((uint32)0x07u)
#define BLUE_6BIT_MASK                      ((uint32)0x3Fu)
#define BLUE_8BIT_MASK                      ((uint32)0xFFu)
#define BLUE_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define BLUE_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define BLUE_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(BLUE_QUAD_ENCODING_MODES     << BLUE_QUAD_MODE_SHIFT))       |\
         ((uint32)(BLUE_CONFIG                  << BLUE_MODE_SHIFT)))

#define BLUE_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(BLUE_PWM_STOP_EVENT          << BLUE_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(BLUE_PWM_OUT_INVERT          << BLUE_INV_OUT_SHIFT))         |\
         ((uint32)(BLUE_PWM_OUT_N_INVERT        << BLUE_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(BLUE_PWM_MODE                << BLUE_MODE_SHIFT)))

#define BLUE_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(BLUE_PWM_RUN_MODE         << BLUE_ONESHOT_SHIFT))
            
#define BLUE_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(BLUE_PWM_ALIGN            << BLUE_UPDOWN_SHIFT))

#define BLUE_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(BLUE_PWM_KILL_EVENT      << BLUE_PWM_SYNC_KILL_SHIFT))

#define BLUE_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(BLUE_PWM_DEAD_TIME_CYCLE  << BLUE_PRESCALER_SHIFT))

#define BLUE_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(BLUE_PWM_PRESCALER        << BLUE_PRESCALER_SHIFT))

#define BLUE_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(BLUE_TC_PRESCALER            << BLUE_PRESCALER_SHIFT))       |\
         ((uint32)(BLUE_TC_COUNTER_MODE         << BLUE_UPDOWN_SHIFT))          |\
         ((uint32)(BLUE_TC_RUN_MODE             << BLUE_ONESHOT_SHIFT))         |\
         ((uint32)(BLUE_TC_COMP_CAP_MODE        << BLUE_MODE_SHIFT)))
        
#define BLUE_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(BLUE_QUAD_PHIA_SIGNAL_MODE   << BLUE_COUNT_SHIFT))           |\
         ((uint32)(BLUE_QUAD_INDEX_SIGNAL_MODE  << BLUE_RELOAD_SHIFT))          |\
         ((uint32)(BLUE_QUAD_STOP_SIGNAL_MODE   << BLUE_STOP_SHIFT))            |\
         ((uint32)(BLUE_QUAD_PHIB_SIGNAL_MODE   << BLUE_START_SHIFT)))

#define BLUE_PWM_SIGNALS_MODES                                                              \
        (((uint32)(BLUE_PWM_SWITCH_SIGNAL_MODE  << BLUE_CAPTURE_SHIFT))         |\
         ((uint32)(BLUE_PWM_COUNT_SIGNAL_MODE   << BLUE_COUNT_SHIFT))           |\
         ((uint32)(BLUE_PWM_RELOAD_SIGNAL_MODE  << BLUE_RELOAD_SHIFT))          |\
         ((uint32)(BLUE_PWM_STOP_SIGNAL_MODE    << BLUE_STOP_SHIFT))            |\
         ((uint32)(BLUE_PWM_START_SIGNAL_MODE   << BLUE_START_SHIFT)))

#define BLUE_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(BLUE_TC_CAPTURE_SIGNAL_MODE  << BLUE_CAPTURE_SHIFT))         |\
         ((uint32)(BLUE_TC_COUNT_SIGNAL_MODE    << BLUE_COUNT_SHIFT))           |\
         ((uint32)(BLUE_TC_RELOAD_SIGNAL_MODE   << BLUE_RELOAD_SHIFT))          |\
         ((uint32)(BLUE_TC_STOP_SIGNAL_MODE     << BLUE_STOP_SHIFT))            |\
         ((uint32)(BLUE_TC_START_SIGNAL_MODE    << BLUE_START_SHIFT)))
        
#define BLUE_TIMER_UPDOWN_CNT_USED                                                          \
                ((BLUE__COUNT_UPDOWN0 == BLUE_TC_COUNTER_MODE)                  ||\
                 (BLUE__COUNT_UPDOWN1 == BLUE_TC_COUNTER_MODE))

#define BLUE_PWM_UPDOWN_CNT_USED                                                            \
                ((BLUE__CENTER == BLUE_PWM_ALIGN)                               ||\
                 (BLUE__ASYMMETRIC == BLUE_PWM_ALIGN))               
        
#define BLUE_PWM_PR_INIT_VALUE              (1u)
#define BLUE_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_BLUE_H */

/* [] END OF FILE */
