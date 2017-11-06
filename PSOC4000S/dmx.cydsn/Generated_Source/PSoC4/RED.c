/*******************************************************************************
* File Name: RED.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the RED
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

#include "RED.h"

uint8 RED_initVar = 0u;


/*******************************************************************************
* Function Name: RED_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default RED configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RED_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (RED__QUAD == RED_CONFIG)
        RED_CONTROL_REG = RED_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        RED_TRIG_CONTROL1_REG  = RED_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        RED_SetInterruptMode(RED_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        RED_SetCounterMode(RED_COUNT_DOWN);
        RED_WritePeriod(RED_QUAD_PERIOD_INIT_VALUE);
        RED_WriteCounter(RED_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (RED__QUAD == RED_CONFIG) */

    #if (RED__TIMER == RED_CONFIG)
        RED_CONTROL_REG = RED_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        RED_TRIG_CONTROL1_REG  = RED_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        RED_SetInterruptMode(RED_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        RED_WritePeriod(RED_TC_PERIOD_VALUE );

        #if (RED__COMPARE == RED_TC_COMP_CAP_MODE)
            RED_WriteCompare(RED_TC_COMPARE_VALUE);

            #if (1u == RED_TC_COMPARE_SWAP)
                RED_SetCompareSwap(1u);
                RED_WriteCompareBuf(RED_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == RED_TC_COMPARE_SWAP) */
        #endif  /* (RED__COMPARE == RED_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (RED_CY_TCPWM_V2 && RED_TIMER_UPDOWN_CNT_USED && !RED_CY_TCPWM_4000)
            RED_WriteCounter(1u);
        #elif(RED__COUNT_DOWN == RED_TC_COUNTER_MODE)
            RED_WriteCounter(RED_TC_PERIOD_VALUE);
        #else
            RED_WriteCounter(0u);
        #endif /* (RED_CY_TCPWM_V2 && RED_TIMER_UPDOWN_CNT_USED && !RED_CY_TCPWM_4000) */
    #endif  /* (RED__TIMER == RED_CONFIG) */

    #if (RED__PWM_SEL == RED_CONFIG)
        RED_CONTROL_REG = RED_CTRL_PWM_BASE_CONFIG;

        #if (RED__PWM_PR == RED_PWM_MODE)
            RED_CONTROL_REG |= RED_CTRL_PWM_RUN_MODE;
            RED_WriteCounter(RED_PWM_PR_INIT_VALUE);
        #else
            RED_CONTROL_REG |= RED_CTRL_PWM_ALIGN | RED_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (RED_CY_TCPWM_V2 && RED_PWM_UPDOWN_CNT_USED && !RED_CY_TCPWM_4000)
                RED_WriteCounter(1u);
            #elif (RED__RIGHT == RED_PWM_ALIGN)
                RED_WriteCounter(RED_PWM_PERIOD_VALUE);
            #else 
                RED_WriteCounter(0u);
            #endif  /* (RED_CY_TCPWM_V2 && RED_PWM_UPDOWN_CNT_USED && !RED_CY_TCPWM_4000) */
        #endif  /* (RED__PWM_PR == RED_PWM_MODE) */

        #if (RED__PWM_DT == RED_PWM_MODE)
            RED_CONTROL_REG |= RED_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (RED__PWM_DT == RED_PWM_MODE) */

        #if (RED__PWM == RED_PWM_MODE)
            RED_CONTROL_REG |= RED_CTRL_PWM_PRESCALER;
        #endif  /* (RED__PWM == RED_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        RED_TRIG_CONTROL1_REG  = RED_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        RED_SetInterruptMode(RED_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (RED__PWM_PR == RED_PWM_MODE)
            RED_TRIG_CONTROL2_REG =
                    (RED_CC_MATCH_NO_CHANGE    |
                    RED_OVERLOW_NO_CHANGE      |
                    RED_UNDERFLOW_NO_CHANGE);
        #else
            #if (RED__LEFT == RED_PWM_ALIGN)
                RED_TRIG_CONTROL2_REG = RED_PWM_MODE_LEFT;
            #endif  /* ( RED_PWM_LEFT == RED_PWM_ALIGN) */

            #if (RED__RIGHT == RED_PWM_ALIGN)
                RED_TRIG_CONTROL2_REG = RED_PWM_MODE_RIGHT;
            #endif  /* ( RED_PWM_RIGHT == RED_PWM_ALIGN) */

            #if (RED__CENTER == RED_PWM_ALIGN)
                RED_TRIG_CONTROL2_REG = RED_PWM_MODE_CENTER;
            #endif  /* ( RED_PWM_CENTER == RED_PWM_ALIGN) */

            #if (RED__ASYMMETRIC == RED_PWM_ALIGN)
                RED_TRIG_CONTROL2_REG = RED_PWM_MODE_ASYM;
            #endif  /* (RED__ASYMMETRIC == RED_PWM_ALIGN) */
        #endif  /* (RED__PWM_PR == RED_PWM_MODE) */

        /* Set other values from customizer */
        RED_WritePeriod(RED_PWM_PERIOD_VALUE );
        RED_WriteCompare(RED_PWM_COMPARE_VALUE);

        #if (1u == RED_PWM_COMPARE_SWAP)
            RED_SetCompareSwap(1u);
            RED_WriteCompareBuf(RED_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == RED_PWM_COMPARE_SWAP) */

        #if (1u == RED_PWM_PERIOD_SWAP)
            RED_SetPeriodSwap(1u);
            RED_WritePeriodBuf(RED_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == RED_PWM_PERIOD_SWAP) */
    #endif  /* (RED__PWM_SEL == RED_CONFIG) */
    
}


/*******************************************************************************
* Function Name: RED_Enable
********************************************************************************
*
* Summary:
*  Enables the RED.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RED_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    RED_BLOCK_CONTROL_REG |= RED_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (RED__PWM_SEL == RED_CONFIG)
        #if (0u == RED_PWM_START_SIGNAL_PRESENT)
            RED_TriggerCommand(RED_MASK, RED_CMD_START);
        #endif /* (0u == RED_PWM_START_SIGNAL_PRESENT) */
    #endif /* (RED__PWM_SEL == RED_CONFIG) */

    #if (RED__TIMER == RED_CONFIG)
        #if (0u == RED_TC_START_SIGNAL_PRESENT)
            RED_TriggerCommand(RED_MASK, RED_CMD_START);
        #endif /* (0u == RED_TC_START_SIGNAL_PRESENT) */
    #endif /* (RED__TIMER == RED_CONFIG) */
    
    #if (RED__QUAD == RED_CONFIG)
        #if (0u != RED_QUAD_AUTO_START)
            RED_TriggerCommand(RED_MASK, RED_CMD_RELOAD);
        #endif /* (0u != RED_QUAD_AUTO_START) */
    #endif  /* (RED__QUAD == RED_CONFIG) */
}


/*******************************************************************************
* Function Name: RED_Start
********************************************************************************
*
* Summary:
*  Initializes the RED with default customizer
*  values when called the first time and enables the RED.
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
*  RED_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time RED_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the RED_Start() routine.
*
*******************************************************************************/
void RED_Start(void)
{
    if (0u == RED_initVar)
    {
        RED_Init();
        RED_initVar = 1u;
    }

    RED_Enable();
}


/*******************************************************************************
* Function Name: RED_Stop
********************************************************************************
*
* Summary:
*  Disables the RED.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RED_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_BLOCK_CONTROL_REG &= (uint32)~RED_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the RED. This function is used when
*  configured as a generic RED and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the RED to operate in
*   Values:
*   - RED_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - RED_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - RED_MODE_QUAD - Quadrature decoder
*         - RED_MODE_PWM - PWM
*         - RED_MODE_PWM_DT - PWM with dead time
*         - RED_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_MODE_MASK;
    RED_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - RED_MODE_X1 - Counts on phi 1 rising
*         - RED_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - RED_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_QUAD_MODE_MASK;
    RED_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - RED_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - RED_PRESCALE_DIVBY2    - Divide by 2
*         - RED_PRESCALE_DIVBY4    - Divide by 4
*         - RED_PRESCALE_DIVBY8    - Divide by 8
*         - RED_PRESCALE_DIVBY16   - Divide by 16
*         - RED_PRESCALE_DIVBY32   - Divide by 32
*         - RED_PRESCALE_DIVBY64   - Divide by 64
*         - RED_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_PRESCALER_MASK;
    RED_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the RED runs
*  continuously or stops when terminal count is reached.  By default the
*  RED operates in the continuous mode.
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
void RED_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_ONESHOT_MASK;
    RED_CONTROL_REG |= ((uint32)((oneShotEnable & RED_1BIT_MASK) <<
                                                               RED_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetPWMMode
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
void RED_SetPWMMode(uint32 modeMask)
{
    RED_TRIG_CONTROL2_REG = (modeMask & RED_6BIT_MASK);
}



/*******************************************************************************
* Function Name: RED_SetPWMSyncKill
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
void RED_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_PWM_SYNC_KILL_MASK;
    RED_CONTROL_REG |= ((uint32)((syncKillEnable & RED_1BIT_MASK)  <<
                                               RED_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetPWMStopOnKill
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
void RED_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_PWM_STOP_KILL_MASK;
    RED_CONTROL_REG |= ((uint32)((stopOnKillEnable & RED_1BIT_MASK)  <<
                                                         RED_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetPWMDeadTime
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
void RED_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_PRESCALER_MASK;
    RED_CONTROL_REG |= ((uint32)((deadTime & RED_8BIT_MASK) <<
                                                          RED_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetPWMInvert
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
*         - RED_INVERT_LINE   - Inverts the line output
*         - RED_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_INV_OUT_MASK;
    RED_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: RED_WriteCounter
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
void RED_WriteCounter(uint32 count)
{
    RED_COUNTER_REG = (count & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_ReadCounter
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
uint32 RED_ReadCounter(void)
{
    return (RED_COUNTER_REG & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - RED_COUNT_UP       - Counts up
*     - RED_COUNT_DOWN     - Counts down
*     - RED_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - RED_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_UPDOWN_MASK;
    RED_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_WritePeriod
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
void RED_WritePeriod(uint32 period)
{
    RED_PERIOD_REG = (period & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_ReadPeriod
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
uint32 RED_ReadPeriod(void)
{
    return (RED_PERIOD_REG & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_SetCompareSwap
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
void RED_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_RELOAD_CC_MASK;
    RED_CONTROL_REG |= (swapEnable & RED_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_WritePeriodBuf
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
void RED_WritePeriodBuf(uint32 periodBuf)
{
    RED_PERIOD_BUF_REG = (periodBuf & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_ReadPeriodBuf
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
uint32 RED_ReadPeriodBuf(void)
{
    return (RED_PERIOD_BUF_REG & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_SetPeriodSwap
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
void RED_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_CONTROL_REG &= (uint32)~RED_RELOAD_PERIOD_MASK;
    RED_CONTROL_REG |= ((uint32)((swapEnable & RED_1BIT_MASK) <<
                                                            RED_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_WriteCompare
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
void RED_WriteCompare(uint32 compare)
{
    #if (RED_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (RED_CY_TCPWM_4000) */

    #if (RED_CY_TCPWM_4000)
        currentMode = ((RED_CONTROL_REG & RED_UPDOWN_MASK) >> RED_UPDOWN_SHIFT);

        if (((uint32)RED__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)RED__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (RED_CY_TCPWM_4000) */
    
    RED_COMP_CAP_REG = (compare & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_ReadCompare
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
uint32 RED_ReadCompare(void)
{
    #if (RED_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (RED_CY_TCPWM_4000) */

    #if (RED_CY_TCPWM_4000)
        currentMode = ((RED_CONTROL_REG & RED_UPDOWN_MASK) >> RED_UPDOWN_SHIFT);
        
        regVal = RED_COMP_CAP_REG;
        
        if (((uint32)RED__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)RED__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & RED_16BIT_MASK);
    #else
        return (RED_COMP_CAP_REG & RED_16BIT_MASK);
    #endif /* (RED_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: RED_WriteCompareBuf
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
void RED_WriteCompareBuf(uint32 compareBuf)
{
    #if (RED_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (RED_CY_TCPWM_4000) */

    #if (RED_CY_TCPWM_4000)
        currentMode = ((RED_CONTROL_REG & RED_UPDOWN_MASK) >> RED_UPDOWN_SHIFT);

        if (((uint32)RED__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)RED__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (RED_CY_TCPWM_4000) */
    
    RED_COMP_CAP_BUF_REG = (compareBuf & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_ReadCompareBuf
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
uint32 RED_ReadCompareBuf(void)
{
    #if (RED_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (RED_CY_TCPWM_4000) */

    #if (RED_CY_TCPWM_4000)
        currentMode = ((RED_CONTROL_REG & RED_UPDOWN_MASK) >> RED_UPDOWN_SHIFT);

        regVal = RED_COMP_CAP_BUF_REG;
        
        if (((uint32)RED__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)RED__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & RED_16BIT_MASK);
    #else
        return (RED_COMP_CAP_BUF_REG & RED_16BIT_MASK);
    #endif /* (RED_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: RED_ReadCapture
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
uint32 RED_ReadCapture(void)
{
    return (RED_COMP_CAP_REG & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_ReadCaptureBuf
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
uint32 RED_ReadCaptureBuf(void)
{
    return (RED_COMP_CAP_BUF_REG & RED_16BIT_MASK);
}


/*******************************************************************************
* Function Name: RED_SetCaptureMode
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
*     - RED_TRIG_LEVEL     - Level
*     - RED_TRIG_RISING    - Rising edge
*     - RED_TRIG_FALLING   - Falling edge
*     - RED_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_TRIG_CONTROL1_REG &= (uint32)~RED_CAPTURE_MASK;
    RED_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RED_TRIG_LEVEL     - Level
*     - RED_TRIG_RISING    - Rising edge
*     - RED_TRIG_FALLING   - Falling edge
*     - RED_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_TRIG_CONTROL1_REG &= (uint32)~RED_RELOAD_MASK;
    RED_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RED_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RED_TRIG_LEVEL     - Level
*     - RED_TRIG_RISING    - Rising edge
*     - RED_TRIG_FALLING   - Falling edge
*     - RED_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_TRIG_CONTROL1_REG &= (uint32)~RED_START_MASK;
    RED_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RED_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RED_TRIG_LEVEL     - Level
*     - RED_TRIG_RISING    - Rising edge
*     - RED_TRIG_FALLING   - Falling edge
*     - RED_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_TRIG_CONTROL1_REG &= (uint32)~RED_STOP_MASK;
    RED_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RED_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - RED_TRIG_LEVEL     - Level
*     - RED_TRIG_RISING    - Rising edge
*     - RED_TRIG_FALLING   - Falling edge
*     - RED_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_TRIG_CONTROL1_REG &= (uint32)~RED_COUNT_MASK;
    RED_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << RED_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_TriggerCommand
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
*     - RED_CMD_CAPTURE    - Trigger Capture/Switch command
*     - RED_CMD_RELOAD     - Trigger Reload/Index command
*     - RED_CMD_STOP       - Trigger Stop/Kill command
*     - RED_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void RED_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    RED_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: RED_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the RED.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - RED_STATUS_DOWN    - Set if counting down
*     - RED_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 RED_ReadStatus(void)
{
    return ((RED_STATUS_REG >> RED_RUNNING_STATUS_SHIFT) |
            (RED_STATUS_REG & RED_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: RED_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - RED_INTR_MASK_TC       - Terminal count mask
*     - RED_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetInterruptMode(uint32 interruptMask)
{
    RED_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: RED_GetInterruptSourceMasked
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
*     - RED_INTR_MASK_TC       - Terminal count mask
*     - RED_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 RED_GetInterruptSourceMasked(void)
{
    return (RED_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: RED_GetInterruptSource
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
*     - RED_INTR_MASK_TC       - Terminal count mask
*     - RED_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 RED_GetInterruptSource(void)
{
    return (RED_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: RED_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - RED_INTR_MASK_TC       - Terminal count mask
*     - RED_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void RED_ClearInterrupt(uint32 interruptMask)
{
    RED_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: RED_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - RED_INTR_MASK_TC       - Terminal count mask
*     - RED_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void RED_SetInterrupt(uint32 interruptMask)
{
    RED_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
