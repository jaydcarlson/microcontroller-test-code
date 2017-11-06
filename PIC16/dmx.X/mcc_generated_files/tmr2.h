/**
  TMR2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.h

  @Summary
    This is the generated header file for the TMR2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  @Description
    This header file provides APIs for TMR2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC16LF18855
        Driver Version    :  1.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _TMR2_H
#define _TMR2_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
 Section: Data Type Definitions
*/

/**
  HLT Mode Setting Enumeration

  @Summary
    Defines the different modes of the HLT.

  @Description
    This defines the several modes of operation of the Timer with
	HLT extension. The modes can be set in a control register associated
	with the timer
*/

typedef enum
{

	/* Roll-over Pulse mode clears the TMRx upon TMRx = PRx, then continue running.
	ON bit must be set and is not affected by Resets
	*/

   /* Roll-over Pulse mode indicates that Timer starts
   immediately upon ON = 1 (Software Control)
   */
   TMR2_ROP_STARTS_TMRON,

   /* Roll-over Pulse mode indicates that the Timer starts
       when ON = 1 and TMRx_ers = 1. Stops when TMRx_ers = 0
     */
   TMR2_ROP_STARTS_TMRON_ERSHIGH,

   /* Roll-over Pulse mode indicates that the Timer starts
      when ON = 1 and TMRx_ers = 0. Stops when TMRx_ers = 1
     */
   TMR2_ROP_STARTS_TMRON_ERSLOW,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon rising or falling edge of TMRx_ers
     */
   TMR2_ROP_RESETS_ERSBOTHEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
    upon rising edge of TMRx_ers
     */
   TMR2_ROP_RESETS_ERSRISINGEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon falling edge of TMRx_ers
     */
   TMR2_ROP_RESETS_ERSFALLINGEDGE,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon TMRx_ers = 0
     */
   TMR2_ROP_RESETS_ERSLOW,

   /* Roll-over Pulse mode indicates that the Timer resets
   upon TMRx_ers = 1
     */
   TMR2_ROP_RESETS_ERSHIGH,

    /*In all One-Shot mode the timer resets and the ON bit is
	cleared when the timer value matches the PRx period
	value. The ON bit must be set by software to start
	another timer cycle.
	*/

   /* One shot mode indicates that the Timer starts
    immediately upon ON = 1 (Software Control)
     */
   TMR2_OS_STARTS_TMRON,

   /* One shot mode indicates that the Timer starts
    when a rising edge is detected on the TMRx_ers
     */
   TMR2_OS_STARTS_ERSRISINGEDGE ,

   /* One shot mode indicates that the Timer starts
    when a falling edge is detected on the TMRx_ers
     */
   TMR2_OS_STARTS_ERSFALLINGEDGE ,

   /* One shot mode indicates that the Timer starts
    when either a rising or falling edge is detected on TMRx_ers
     */
   TMR2_OS_STARTS_ERSBOTHEDGE,

   /* One shot mode indicates that the Timer starts
    upon first TMRx_ers rising edge and resets on all
	subsequent TMRx_ers rising edges
     */
   TMR2_OS_STARTS_ERSFIRSTRISINGEDGE,

   /* One shot mode indicates that the Timer starts
    upon first TMRx_ers falling edge and restarts on all
	subsequent TMRx_ers falling edges
     */
   TMR2_OS_STARTS_ERSFIRSTFALLINGEDGE,

   /* One shot mode indicates that the Timer starts
    when a rising edge is detected on the TMRx_ers,
	resets upon TMRx_ers = 0
     */
   TMR2_OS_STARTS_ERSRISINGEDGEDETECT,
     /* One shot mode indicates that the Timer starts
    when a falling edge is detected on the TMRx_ers,
	resets upon TMRx_ers = 1
     */
   TMR2_OS_STARTS_ERSFALLINGEDGEDETECT,
   
   /* One shot mode indicates that the Timer starts
    when a TMRx_ers = 1,ON =1 and resets upon TMRx_ers =0
    */
   TMR2_OS_STARTS_TMRON_ERSHIGH = 0x16,
           
   /* One shot mode indicates that the Timer starts
     when a TMRx_ers = 0,ON = 1 and resets upon TMRx_ers =1 
    */
   TMR2_OS_STARTS_TMRON_ERSLOW = 0x17,
        
   /*In all Mono-Stable mode the ON bit must be initially set,but
     not cleared upon the TMRx = PRx, and the timer will start upon
     an TMRx_ers start event following TMRx = PRx.*/
               
   /* Mono Stable mode indicates that the Timer starts
      when a rising edge is detected on the TMRx_ers and ON = 1
    */
   TMR2_MS_STARTS_TMRON_ERSRISINGEDGEDETECT = 0x11,
           
   /* Mono Stable mode indicates that the Timer starts
      when a falling edge is detected on the TMRx_ers and ON = 1
    */
   TMR2_MS_STARTS_TMRON_ERSFALLINGEDGEDETECT = 0x12,
           
   /* Mono Stable mode indicates that the Timer starts
      when  either a rising or falling edge is detected on TMRx_ers 
      and ON = 1
    */
   TMR2_MS_STARTS_TMRON_ERSBOTHEDGE = 0x13
           
} TMR2_HLT_MODE;

/**
  HLT Reset Source Enumeration

  @Summary
    Defines the different reset source of the HLT.

  @Description
    This source can control starting and stopping of the
	timer, as well as resetting the timer, depending on
	which mode the timer is in. The mode of the timer is
	controlled by the HLT_MODE
*/

typedef enum
{
     /* T2INPPS is the Timer external reset source
     */
    TMR2_T2INPPS,

    /* Reserved enum cannot be used 
     */
    TMR2_RESERVED,
    
    /* Timer4 Postscale is the Timer external reset source 
     */
    TMR2_T4POSTSCALED,
    
    /* Timer6 Postscale is the Timer external reset source 
     */
    TMR2_T6POSTSCALED,
     /* CCP1_OUT is the Timer external reset source 
     */
    TMR2_CCP1_OUT,

    /* CCP2_OUT is the Timer external reset source 
     */
    TMR2_CCP2_OUT,

     /* CCP3_OUT is the Timer external reset source 
     */
    TMR2_CCP3_OUT,

    /* CCP4_OUT is the Timer external reset source 
     */
    TMR2_CCP4_OUT,

    /* CCP5_OUT is the Timer external reset source 
     */
    TMR2_CCP5_OUT,

    /* PWM6_out is the Timer external reset source 
     */
    TMR2_PWM6_OUT,

     /* PWM7_out is the Timer external reset source 
     */
    TMR2_PWM7_OUT,

    /* C1_OUT_SYNC is the Timer external reset source 
     */
    TMR2_C1_OUT_SYNC,	

    /* C2_OUT_SYNC is the Timer external reset source 
     */
    TMR2_C2_OUT_SYNC,

    /* ZCD_Output is the Timer external reset source 
     */
    TMR2_ZCD_OUTPUT,

    /* LC1_out is the Timer external reset source 
     */
    TMR2_LC1_OUT,
         
    /* LC2_out is the Timer external reset source 
     */
    TMR2_LC2_OUT,
            
    /* LC3_out is the Timer external reset source 
     */
    TMR2_LC3_OUT,

    /* LC4_out is the Timer external reset source 
     */
    TMR2_LC4_OUT

} TMR2_HLT_EXT_RESET_SOURCE;


/**
  Section: Macro Declarations
*/

/**
  Section: TMR2 APIs
*/

/**
  @Summary
    Initializes the TMR2 module.

  @Description
    This function initializes the TMR2 Registers.
    This function must be called before any other TMR2 function is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    main()
    {
        // Initialize TMR2 module
        TMR2_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR2_Initialize(void);

/**
  @Summary
    Configures the Hardware Limit Timer mode.

  @Description
    Writes the T2HLTbits.MODE bits.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    mode - Value to write into T2HLTbits.MODE bits.

  @Returns
    None

  @Example
    <code>
	main()
    {

	    TMR2_HLT_MODE hltmode;
		hltmode = TMR2_ROP_STARTS_TMRON_EN;

		// Initialize TMR2 module
		 TMR2.Initialize();

		// Set the HLT mode
		TMR2_ModeSet (hltmode);

		// Do something else...
    }
    </code>
*/
void TMR2_ModeSet(TMR2_HLT_MODE mode);

/**
  @Summary
    Configures the HLT external reset source.

  @Description
    Writes the T2RSTbits.RSEL bits.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    reset - Value to write into T2RSTbits.RSEL bits.

  @Returns
    None

  @Example
    <code>
	main()
    {

	    TMR2_HLT_EXT_RESET_SOURCE hltresetsrc;
		hltresetsrc = T2IN;

        // Initialize TMR2 module

		// Set the HLT mode
		TMR2_ExtResetSourceSet(hltresetsrc);

		// Do something else...
    }
    </code>
*/
void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset);

/**
  @Summary
    This function starts the TMR2.

  @Description
    This function starts the TMR2 operation.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_Start();

    // Do something else...
    </code>
*/
void TMR2_Start(void);

/**
  @Summary
    This function starts the TMR2.

  @Description
    This function starts the TMR2 operation.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_StartTimer();

    // Do something else...
    </code>
*/
void TMR2_StartTimer(void);

/**
  @Summary
    This function stops the TMR2.

  @Description
    This function stops the TMR2 operation.
    This function must be called after the start of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_Start();

    // Do something else...

    // Stop TMR2;
    TMR2_Stop();
    </code>
*/
void TMR2_Stop(void);

/**
  @Summary
    This function stops the TMR2.

  @Description
    This function stops the TMR2 operation.
    This function must be called after the start of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_StartTimer();

    // Do something else...

    // Stop TMR2;
    TMR2_StopTimer();
    </code>
*/
void TMR2_StopTimer(void);

/**
  @Summary
    Reads the TMR2 register.

  @Description
    This function reads the TMR2 register value and return it.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR2 register.

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_Start();

    // Read the current value of TMR2
    if(0 == TMR2_Counter8BitGet())
    {
        // Do something else...

        // Reload the TMR value
        TMR2_Period8BitSet();
    }
    </code>
*/
uint8_t TMR2_Counter8BitGet(void);

/**
  @Summary
    Reads the TMR2 register.

  @Description
    This function reads the TMR2 register value and return it.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR2 register.

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_StartTimer();

    // Read the current value of TMR2
    if(0 == TMR2_ReadTimer())
    {
        // Do something else...

        // Reload the TMR value
        TMR2_LoadPeriodRegister();
    }
    </code>
*/
uint8_t TMR2_ReadTimer(void);

/**
  @Summary
    Writes the TMR2 register.

  @Description
    This function writes the TMR2 register.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    timerVal - Value to write into TMR2 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR2 register
        if(ZERO == TMR2_Counter8BitGet())
        {
            // Do something else...

            // Write the TMR2 register
            TMR2_Counter8BitSet(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR2_Counter8BitSet(uint8_t timerVal);

/**
  @Summary
    Writes the TMR2 register.

  @Description
    This function writes the TMR2 register.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    timerVal - Value to write into TMR2 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR2 register
        if(ZERO == TMR2_ReadTimer())
        {
            // Do something else...

            // Write the TMR2 register
            TMR2_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR2_WriteTimer(uint8_t timerVal);

/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to PR2 register.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    periodVal - Value to load into TMR2 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD1 0x80
    #define PERIOD2 0x40
    #define ZERO    0x00

    while(1)
    {
        // Read the TMR2 register
        if(ZERO == TMR2_Counter8BitGet())
        {
            // Do something else...

            if(flag)
            {
                flag = 0;

                // Load Period 1 value
                TMR2_Period8BitSet(PERIOD1);
            }
            else
            {
                 flag = 1;

                // Load Period 2 value
                TMR2_Period8BitSet(PERIOD2);
            }
        }

        // Do something else...
    }
    </code>
*/
void TMR2_Period8BitSet(uint8_t periodVal);

/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to PR2 register.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    periodVal - Value to load into TMR2 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD1 0x80
    #define PERIOD2 0x40
    #define ZERO    0x00

    while(1)
    {
        // Read the TMR2 register
        if(ZERO == TMR2_ReadTimer())
        {
            // Do something else...

            if(flag)
            {
                flag = 0;

                // Load Period 1 value
                TMR2_LoadPeriodRegister(PERIOD1);
            }
            else
            {
                 flag = 1;

                // Load Period 2 value
                TMR2_LoadPeriodRegister(PERIOD2);
            }
        }

        // Do something else...
    }
    </code>
*/
void TMR2_LoadPeriodRegister(uint8_t periodVal);

/**
  @Summary
    Boolean routine to poll or to check for the match flag on the fly.

  @Description
    This function is called to check for the timer match flag.
    This function is usd in timer polling method.

  @Preconditions
    Initialize  the TMR2 module before calling this routine.

  @Param
    None

  @Returns
    true - timer match has occured.
    false - timer match has not occured.

  @Example
    <code>
    while(1)
    {
        // check the match flag
        if(TMR2_HasOverflowOccured())
        {
            // Do something else...

            // clear the TMR2 match interrupt flag
            TMR2IF = 0;

            // Reload the TMR2 value
            TMR2_Reload();
        }
    }
    </code>
*/
bool TMR2_HasOverflowOccured(void);

 #ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _TMR2_H
/**
 End of File
*/

