/**
  CCP3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp3.h

  @Summary
    This is the generated driver implementation file for the CCP3 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  @Description
    This header file provides implementations for driver APIs for CCP3.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC16LF18855
        Driver Version    :  2.00
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

#ifndef _PWM3_H
#define _PWM3_H

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
  Section: PWM Module APIs
*/

/**
  @Summary
    Initializes the CCP3

  @Description
    This routine initializes the CCP3 module.
    This routine must be called before any other CCP3 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

 @Example
    <code>
    uint16_t dutycycle;

    PWM3_Initialize();
	PWM3_LoadDutyValue(dutycycle);
    </code>
 */
void PWM3_Initialize(void);

/**
  @Summary
    Loads 16-bit duty cycle.

  @Description
    This routine loads the 16 bit duty cycle value.

  @Preconditions
    PWM3_Initialize() function should have been called
    before calling this function.

  @Param
    Pass 16bit duty cycle value.

  @Returns
    None

  @Example
    <code>
    uint16_t dutycycle;

    PWM3_Initialize();
    PWM3_LoadDutyValue(dutycycle);
    </code>
*/
void PWM3_LoadDutyValue(uint16_t dutyValue);

/**
  @Summary
    Read pwm output status.

  @Description
    This routine returns the pwm output status.

  @Preconditions
    PWM3_Initialize() function should have been
    called before calling this function.

  @Param
    None

  @Returns
    true : output high
    false: output low

  @Example
    <code>
    uint16_t dutyCycle;
    bool status;
    PWM3_Initialize();
    PWM3_LoadDutyValue(dutyCycle);
    while(1)
    {
            status = PWM3_OutputStatusGet();
    }
    </code>
*/
bool PWM3_OutputStatusGet(void);
        
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	//PWM3_H
/**
 End of File
*/
