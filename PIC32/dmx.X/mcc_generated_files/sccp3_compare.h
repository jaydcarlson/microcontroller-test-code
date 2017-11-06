/**
  SCCP3 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    sccp3.h

  @Summary
    This is the generated header file for the SCCP3 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for SCCP3.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC32MM0064GPL028
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB 	          :  MPLAB X 3.60
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

#ifndef _SCCP3_COMPARE_H
#define _SCCP3_COMPARE_H
/**
  Section: Included Files
*/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
/**
  Section: Interface Routines
*/

/**
  @Summary
    This function initializes MCCP instance : 3

  @Description
    This routine initializes the SCCP3 driver instance for : 3
    index, making it ready for clients to open and use it.
    This routine must be called before any other SCCP3 routine is called.
	
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Comment
    
 
  @Example
    <code>
    uint16_t priVal,secVal;
    bool completeCycle = false;
    priVal = 0x1000;
    secVal = 0x2000;

    SCCP3_COMPARE_Initializer();
    
    SCCP3_COMPARE_CentreAlignedPWMConfig( priVal, secVal );
  
    SCCP3_COMPARE_Start();

    while(1)
    {
       
        completeCycle = SCCP3_COMPARE_IsCompareCycleComplete( void );
        if(completeCycle)
        {
            SCCP3_COMPARE_Stop();
        }
    }
    </code>
*/

void SCCP3_COMPARE_Initialize (void);
/**
  @Summary
    Maintains the driver's state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal state
    machine and implement its ISR for interrupt-driven implementations.
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    while (true)
    {
        SCCP3_COMPARE_Tasks();

        // Do other tasks
    }
    </code>
    
*/
void SCCP3_COMPARE_Tasks( void );
/**
  @Summary
    Maintains the driver's state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal state
    machine and implement its ISR for interrupt-driven implementations.
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    while (true)
    {
        SCCP3_COMPARE_TimerTasks();

        // Do other tasks
    }
    </code>
    
*/
void SCCP3_COMPARE_TimerTasks( void );
/**
  @Summary
    Enables the OC module with the corresponding operation mode.

  @Description
    This routine enables the OC module with the corresponding operation mode.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    None.
 
  @Returns
    None.

  @Example 
    Refer to SCCP3_COMPARE_Initializer() for an example	
 
*/

void SCCP3_COMPARE_Start( void );
/**
  @Summary
    Disables the OC module.

  @Description
    This routine disables the OC module.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    None.

  @Returns
    None.

*/

void SCCP3_COMPARE_Stop( void );
/**
  @Summary
    Sets the primary compare value.

  @Description
    This routine sets the primary compare value.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    value - 16 bit primary compare value.

  @Returns
    None.

  @Example 
    <code>
        uint16_t value = 0x1000;
        SCCP3_COMPARE_SingleCompareValueSet( value );
    <code>
	
*/
void SCCP3_COMPARE_SingleCompare16ValueSet( uint16_t value );
/**
  @Summary
    Sets the primary and secondary compare value.

  @Description
    This routine sets the primary and secondary compare value.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        SCCP3_COMPARE_DualCompareValueSet( priVal,secVal );
    <code>
  	
*/

void SCCP3_COMPARE_DualCompareValueSet( uint16_t priVal, uint16_t secVal );

/**
  @Summary
    Sets the primary and secondary compare value for Center Aligned PWM

  @Description
    This routine sets the primary and secondary compare value for Center Aligned PWM.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	
	
  @Returns
    None.

  @Example 
    Refer to SCCP3_COMPARE_Initializer() for an example

*/

void SCCP3_COMPARE_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal );
/**
  @Summary
    Sets the primary and secondary compare value for Edge Aligned PWM.

  @Description
    This routine sets the primary and secondary compare value for Edge Aligned PWM.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        SCCP3_COMPARE_EdgeAlignedPWMConfig( priVal,secVal );
    <code> 
 	
*/

void SCCP3_COMPARE_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal );
/**
  @Summary
    Gets the status of the compare cycle completion.

  @Description
    This routine gets the status of the compare cycle completion.

  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 

  @Param
    None.

  @Returns
    Boolean value describing the current status of the cycle completion. Returns
    true  : When the compare cycle has completed. 
    false : When the compare cycle has not completed. 

  @Example 
    Refer to SCCP3_COMPARE_Initializer() for an example
	

*/

bool SCCP3_COMPARE_IsCompareCycleComplete( void );
/**
  @Summary
    Gets the status of the timer trigger.

  @Description
    This routine gets the status of the timer trigger source if it has been triggered.
	
  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called 
	
  @Param
    None
	
  @Returns
    Boolean value describing the timer trigger status.
    true  : When the timer source has triggered and is running 
    false : When the timer has not triggered and being held clear 

   @Example 
    <\code>	
    if(SCCP3_COMPARE_TriggerStatusGet())
    {
        SCCP3_COMPARE_TriggerStatusClear();
    }
    <\code>	
*/

bool SCCP3_COMPARE_TriggerStatusGet( void );
/**
  @Summary
    Clears the status of the timer trigger.

  @Description
    This routine clears the status of the timer trigger.
	
  @Preconditions
    SCCP3_COMPARE_Initializer function should have been called

  @Param
    None.

  @Returns
    None.
	
  @Example 
    Refer to SCCP3_COMPARE_TriggerStatusGet() for an example	

*/

void SCCP3_COMPARE_TriggerStatusClear( void );
/**
  @Summary
    Gets the status of the timer trigger.

  @Description
    This routine gets the status of the timer trigger source if it has been triggered.

  @Param
    None.

  @Returns
    Gets the status of the single compare set
*/

bool SCCP3_COMPARE_SingleCompareStatusGet( void );
/**
  @Summary
    Clears the status of the timer trigger source.

  @Description
    This routine clears the status of the timer trigger source.

  @Param
    None.

  @Returns
    None.
*/

void SCCP3_COMPARE_SingleCompareStatusClear( void );
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_SCCP3_H
    
/**
 End of File
*/
