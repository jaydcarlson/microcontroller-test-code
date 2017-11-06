/*******************************************************************************
* File Name: BLUE.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the BLUE
*  component
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

#include "BLUE.h"

uint8 BLUE_initVar = 0u;


/*******************************************************************************
* Function Name: BLUE_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default BLUE configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (BLUE__QUAD == BLUE_CONFIG)
        BLUE_CONTROL_REG = BLUE_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        BLUE_TRIG_CONTROL1_REG  = BLUE_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        BLUE_SetInterruptMode(BLUE_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        BLUE_SetCounterMode(BLUE_COUNT_DOWN);
        BLUE_WritePeriod(BLUE_QUAD_PERIOD_INIT_VALUE);
        BLUE_WriteCounter(BLUE_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (BLUE__QUAD == BLUE_CONFIG) */

    #if (BLUE__TIMER == BLUE_CONFIG)
        BLUE_CONTROL_REG = BLUE_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        BLUE_TRIG_CONTROL1_REG  = BLUE_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        BLUE_SetInterruptMode(BLUE_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        BLUE_WritePeriod(BLUE_TC_PERIOD_VALUE );

        #if (BLUE__COMPARE == BLUE_TC_COMP_CAP_MODE)
            BLUE_WriteCompare(BLUE_TC_COMPARE_VALUE);

            #if (1u == BLUE_TC_COMPARE_SWAP)
                BLUE_SetCompareSwap(1u);
                BLUE_WriteCompareBuf(BLUE_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == BLUE_TC_COMPARE_SWAP) */
        #endif  /* (BLUE__COMPARE == BLUE_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (BLUE_CY_TCPWM_V2 && BLUE_TIMER_UPDOWN_CNT_USED && !BLUE_CY_TCPWM_4000)
            BLUE_WriteCounter(1u);
        #elif(BLUE__COUNT_DOWN == BLUE_TC_COUNTER_MODE)
            BLUE_WriteCounter(BLUE_TC_PERIOD_VALUE);
        #else
            BLUE_WriteCounter(0u);
        #endif /* (BLUE_CY_TCPWM_V2 && BLUE_TIMER_UPDOWN_CNT_USED && !BLUE_CY_TCPWM_4000) */
    #endif  /* (BLUE__TIMER == BLUE_CONFIG) */

    #if (BLUE__PWM_SEL == BLUE_CONFIG)
        BLUE_CONTROL_REG = BLUE_CTRL_PWM_BASE_CONFIG;

        #if (BLUE__PWM_PR == BLUE_PWM_MODE)
            BLUE_CONTROL_REG |= BLUE_CTRL_PWM_RUN_MODE;
            BLUE_WriteCounter(BLUE_PWM_PR_INIT_VALUE);
        #else
            BLUE_CONTROL_REG |= BLUE_CTRL_PWM_ALIGN | BLUE_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (BLUE_CY_TCPWM_V2 && BLUE_PWM_UPDOWN_CNT_USED && !BLUE_CY_TCPWM_4000)
                BLUE_WriteCounter(1u);
            #elif (BLUE__RIGHT == BLUE_PWM_ALIGN)
                BLUE_WriteCounter(BLUE_PWM_PERIOD_VALUE);
            #else 
                BLUE_WriteCounter(0u);
            #endif  /* (BLUE_CY_TCPWM_V2 && BLUE_PWM_UPDOWN_CNT_USED && !BLUE_CY_TCPWM_4000) */
        #endif  /* (BLUE__PWM_PR == BLUE_PWM_MODE) */

        #if (BLUE__PWM_DT == BLUE_PWM_MODE)
            BLUE_CONTROL_REG |= BLUE_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (BLUE__PWM_DT == BLUE_PWM_MODE) */

        #if (BLUE__PWM == BLUE_PWM_MODE)
            BLUE_CONTROL_REG |= BLUE_CTRL_PWM_PRESCALER;
        #endif  /* (BLUE__PWM == BLUE_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        BLUE_TRIG_CONTROL1_REG  = BLUE_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        BLUE_SetInterruptMode(BLUE_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (BLUE__PWM_PR == BLUE_PWM_MODE)
            BLUE_TRIG_CONTROL2_REG =
                    (BLUE_CC_MATCH_NO_CHANGE    |
                    BLUE_OVERLOW_NO_CHANGE      |
                    BLUE_UNDERFLOW_NO_CHANGE);
        #else
            #if (BLUE__LEFT == BLUE_PWM_ALIGN)
                BLUE_TRIG_CONTROL2_REG = BLUE_PWM_MODE_LEFT;
            #endif  /* ( BLUE_PWM_LEFT == BLUE_PWM_ALIGN) */

            #if (BLUE__RIGHT == BLUE_PWM_ALIGN)
                BLUE_TRIG_CONTROL2_REG = BLUE_PWM_MODE_RIGHT;
            #endif  /* ( BLUE_PWM_RIGHT == BLUE_PWM_ALIGN) */

            #if (BLUE__CENTER == BLUE_PWM_ALIGN)
                BLUE_TRIG_CONTROL2_REG = BLUE_PWM_MODE_CENTER;
            #endif  /* ( BLUE_PWM_CENTER == BLUE_PWM_ALIGN) */

            #if (BLUE__ASYMMETRIC == BLUE_PWM_ALIGN)
                BLUE_TRIG_CONTROL2_REG = BLUE_PWM_MODE_ASYM;
            #endif  /* (BLUE__ASYMMETRIC == BLUE_PWM_ALIGN) */
        #endif  /* (BLUE__PWM_PR == BLUE_PWM_MODE) */

        /* Set other values from customizer */
        BLUE_WritePeriod(BLUE_PWM_PERIOD_VALUE );
        BLUE_WriteCompare(BLUE_PWM_COMPARE_VALUE);

        #if (1u == BLUE_PWM_COMPARE_SWAP)
            BLUE_SetCompareSwap(1u);
            BLUE_WriteCompareBuf(BLUE_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == BLUE_PWM_COMPARE_SWAP) */

        #if (1u == BLUE_PWM_PERIOD_SWAP)
            BLUE_SetPeriodSwap(1u);
            BLUE_WritePeriodBuf(BLUE_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == BLUE_PWM_PERIOD_SWAP) */
    #endif  /* (BLUE__PWM_SEL == BLUE_CONFIG) */
    
}


/*******************************************************************************
* Function Name: BLUE_Enable
********************************************************************************
*
* Summary:
*  Enables the BLUE.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    BLUE_BLOCK_CONTROL_REG |= BLUE_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (BLUE__PWM_SEL == BLUE_CONFIG)
        #if (0u == BLUE_PWM_START_SIGNAL_PRESENT)
            BLUE_TriggerCommand(BLUE_MASK, BLUE_CMD_START);
        #endif /* (0u == BLUE_PWM_START_SIGNAL_PRESENT) */
    #endif /* (BLUE__PWM_SEL == BLUE_CONFIG) */

    #if (BLUE__TIMER == BLUE_CONFIG)
        #if (0u == BLUE_TC_START_SIGNAL_PRESENT)
            BLUE_TriggerCommand(BLUE_MASK, BLUE_CMD_START);
        #endif /* (0u == BLUE_TC_START_SIGNAL_PRESENT) */
    #endif /* (BLUE__TIMER == BLUE_CONFIG) */
    
    #if (BLUE__QUAD == BLUE_CONFIG)
        #if (0u != BLUE_QUAD_AUTO_START)
            BLUE_TriggerCommand(BLUE_MASK, BLUE_CMD_RELOAD);
        #endif /* (0u != BLUE_QUAD_AUTO_START) */
    #endif  /* (BLUE__QUAD == BLUE_CONFIG) */
}


/*******************************************************************************
* Function Name: BLUE_Start
********************************************************************************
*
* Summary:
*  Initializes the BLUE with default customizer
*  values when called the first time and enables the BLUE.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BLUE_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time BLUE_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the BLUE_Start() routine.
*
*******************************************************************************/
void BLUE_Start(void)
{
    if (0u == BLUE_initVar)
    {
        BLUE_Init();
        BLUE_initVar = 1u;
    }

    BLUE_Enable();
}


/*******************************************************************************
* Function Name: BLUE_Stop
********************************************************************************
*
* Summary:
*  Disables the BLUE.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_BLOCK_CONTROL_REG &= (uint32)~BLUE_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the BLUE. This function is used when
*  configured as a generic BLUE and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the BLUE to operate in
*   Values:
*   - BLUE_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - BLUE_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - BLUE_MODE_QUAD - Quadrature decoder
*         - BLUE_MODE_PWM - PWM
*         - BLUE_MODE_PWM_DT - PWM with dead time
*         - BLUE_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_MODE_MASK;
    BLUE_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - BLUE_MODE_X1 - Counts on phi 1 rising
*         - BLUE_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - BLUE_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_QUAD_MODE_MASK;
    BLUE_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - BLUE_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - BLUE_PRESCALE_DIVBY2    - Divide by 2
*         - BLUE_PRESCALE_DIVBY4    - Divide by 4
*         - BLUE_PRESCALE_DIVBY8    - Divide by 8
*         - BLUE_PRESCALE_DIVBY16   - Divide by 16
*         - BLUE_PRESCALE_DIVBY32   - Divide by 32
*         - BLUE_PRESCALE_DIVBY64   - Divide by 64
*         - BLUE_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_PRESCALER_MASK;
    BLUE_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the BLUE runs
*  continuously or stops when terminal count is reached.  By default the
*  BLUE operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_ONESHOT_MASK;
    BLUE_CONTROL_REG |= ((uint32)((oneShotEnable & BLUE_1BIT_MASK) <<
                                                               BLUE_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPWMMode(uint32 modeMask)
{
    BLUE_TRIG_CONTROL2_REG = (modeMask & BLUE_6BIT_MASK);
}



/*******************************************************************************
* Function Name: BLUE_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_PWM_SYNC_KILL_MASK;
    BLUE_CONTROL_REG |= ((uint32)((syncKillEnable & BLUE_1BIT_MASK)  <<
                                               BLUE_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_PWM_STOP_KILL_MASK;
    BLUE_CONTROL_REG |= ((uint32)((stopOnKillEnable & BLUE_1BIT_MASK)  <<
                                                         BLUE_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_PRESCALER_MASK;
    BLUE_CONTROL_REG |= ((uint32)((deadTime & BLUE_8BIT_MASK) <<
                                                          BLUE_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - BLUE_INVERT_LINE   - Inverts the line output
*         - BLUE_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_INV_OUT_MASK;
    BLUE_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: BLUE_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_WriteCounter(uint32 count)
{
    BLUE_COUNTER_REG = (count & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 BLUE_ReadCounter(void)
{
    return (BLUE_COUNTER_REG & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - BLUE_COUNT_UP       - Counts up
*     - BLUE_COUNT_DOWN     - Counts down
*     - BLUE_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - BLUE_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_UPDOWN_MASK;
    BLUE_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_WritePeriod(uint32 period)
{
    BLUE_PERIOD_REG = (period & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 BLUE_ReadPeriod(void)
{
    return (BLUE_PERIOD_REG & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_RELOAD_CC_MASK;
    BLUE_CONTROL_REG |= (swapEnable & BLUE_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_WritePeriodBuf(uint32 periodBuf)
{
    BLUE_PERIOD_BUF_REG = (periodBuf & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 BLUE_ReadPeriodBuf(void)
{
    return (BLUE_PERIOD_BUF_REG & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_CONTROL_REG &= (uint32)~BLUE_RELOAD_PERIOD_MASK;
    BLUE_CONTROL_REG |= ((uint32)((swapEnable & BLUE_1BIT_MASK) <<
                                                            BLUE_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void BLUE_WriteCompare(uint32 compare)
{
    #if (BLUE_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (BLUE_CY_TCPWM_4000) */

    #if (BLUE_CY_TCPWM_4000)
        currentMode = ((BLUE_CONTROL_REG & BLUE_UPDOWN_MASK) >> BLUE_UPDOWN_SHIFT);

        if (((uint32)BLUE__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)BLUE__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (BLUE_CY_TCPWM_4000) */
    
    BLUE_COMP_CAP_REG = (compare & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 BLUE_ReadCompare(void)
{
    #if (BLUE_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (BLUE_CY_TCPWM_4000) */

    #if (BLUE_CY_TCPWM_4000)
        currentMode = ((BLUE_CONTROL_REG & BLUE_UPDOWN_MASK) >> BLUE_UPDOWN_SHIFT);
        
        regVal = BLUE_COMP_CAP_REG;
        
        if (((uint32)BLUE__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)BLUE__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & BLUE_16BIT_MASK);
    #else
        return (BLUE_COMP_CAP_REG & BLUE_16BIT_MASK);
    #endif /* (BLUE_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: BLUE_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void BLUE_WriteCompareBuf(uint32 compareBuf)
{
    #if (BLUE_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (BLUE_CY_TCPWM_4000) */

    #if (BLUE_CY_TCPWM_4000)
        currentMode = ((BLUE_CONTROL_REG & BLUE_UPDOWN_MASK) >> BLUE_UPDOWN_SHIFT);

        if (((uint32)BLUE__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)BLUE__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (BLUE_CY_TCPWM_4000) */
    
    BLUE_COMP_CAP_BUF_REG = (compareBuf & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 BLUE_ReadCompareBuf(void)
{
    #if (BLUE_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (BLUE_CY_TCPWM_4000) */

    #if (BLUE_CY_TCPWM_4000)
        currentMode = ((BLUE_CONTROL_REG & BLUE_UPDOWN_MASK) >> BLUE_UPDOWN_SHIFT);

        regVal = BLUE_COMP_CAP_BUF_REG;
        
        if (((uint32)BLUE__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)BLUE__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & BLUE_16BIT_MASK);
    #else
        return (BLUE_COMP_CAP_BUF_REG & BLUE_16BIT_MASK);
    #endif /* (BLUE_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: BLUE_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 BLUE_ReadCapture(void)
{
    return (BLUE_COMP_CAP_REG & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 BLUE_ReadCaptureBuf(void)
{
    return (BLUE_COMP_CAP_BUF_REG & BLUE_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLUE_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLUE_TRIG_LEVEL     - Level
*     - BLUE_TRIG_RISING    - Rising edge
*     - BLUE_TRIG_FALLING   - Falling edge
*     - BLUE_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_TRIG_CONTROL1_REG &= (uint32)~BLUE_CAPTURE_MASK;
    BLUE_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLUE_TRIG_LEVEL     - Level
*     - BLUE_TRIG_RISING    - Rising edge
*     - BLUE_TRIG_FALLING   - Falling edge
*     - BLUE_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_TRIG_CONTROL1_REG &= (uint32)~BLUE_RELOAD_MASK;
    BLUE_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLUE_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLUE_TRIG_LEVEL     - Level
*     - BLUE_TRIG_RISING    - Rising edge
*     - BLUE_TRIG_FALLING   - Falling edge
*     - BLUE_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_TRIG_CONTROL1_REG &= (uint32)~BLUE_START_MASK;
    BLUE_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLUE_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLUE_TRIG_LEVEL     - Level
*     - BLUE_TRIG_RISING    - Rising edge
*     - BLUE_TRIG_FALLING   - Falling edge
*     - BLUE_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_TRIG_CONTROL1_REG &= (uint32)~BLUE_STOP_MASK;
    BLUE_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLUE_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLUE_TRIG_LEVEL     - Level
*     - BLUE_TRIG_RISING    - Rising edge
*     - BLUE_TRIG_FALLING   - Falling edge
*     - BLUE_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_TRIG_CONTROL1_REG &= (uint32)~BLUE_COUNT_MASK;
    BLUE_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLUE_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - BLUE_CMD_CAPTURE    - Trigger Capture/Switch command
*     - BLUE_CMD_RELOAD     - Trigger Reload/Index command
*     - BLUE_CMD_STOP       - Trigger Stop/Kill command
*     - BLUE_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLUE_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLUE_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the BLUE.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - BLUE_STATUS_DOWN    - Set if counting down
*     - BLUE_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 BLUE_ReadStatus(void)
{
    return ((BLUE_STATUS_REG >> BLUE_RUNNING_STATUS_SHIFT) |
            (BLUE_STATUS_REG & BLUE_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: BLUE_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - BLUE_INTR_MASK_TC       - Terminal count mask
*     - BLUE_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetInterruptMode(uint32 interruptMask)
{
    BLUE_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: BLUE_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - BLUE_INTR_MASK_TC       - Terminal count mask
*     - BLUE_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 BLUE_GetInterruptSourceMasked(void)
{
    return (BLUE_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: BLUE_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - BLUE_INTR_MASK_TC       - Terminal count mask
*     - BLUE_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 BLUE_GetInterruptSource(void)
{
    return (BLUE_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: BLUE_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - BLUE_INTR_MASK_TC       - Terminal count mask
*     - BLUE_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_ClearInterrupt(uint32 interruptMask)
{
    BLUE_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: BLUE_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - BLUE_INTR_MASK_TC       - Terminal count mask
*     - BLUE_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void BLUE_SetInterrupt(uint32 interruptMask)
{
    BLUE_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
