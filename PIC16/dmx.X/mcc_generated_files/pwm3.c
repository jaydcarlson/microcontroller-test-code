/**
  CCP3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp3.c

  @Summary
    This is the generated driver implementation file for the CCP3 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  @Description
    This source file provides implementations for driver APIs for CCP3.
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "pwm3.h"

/**
  Section: Macro Declarations
*/

#define PWM3_INITIALIZE_DUTY_VALUE    255

/**
  Section: PWM Module APIs
*/

void PWM3_Initialize(void)
{
    // Set the PWM to the options selected in the PIC10 / PIC12 / PIC16 / PIC18 MCUs 

    // MODE PWM; EN enabled; CCP3FMT right_aligned; 
    CCP3CON = 0x8F;    

    // RH 0; 
    CCPR3H = 0x00;    

    // RL 255; 
    CCPR3L = 0xFF;    

    // Selecting Timer 2
    CCPTMRS0bits.C3TSEL = 0x1;
}

void PWM3_LoadDutyValue(uint16_t dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP3CONbits.CCP3FMT)
    {
        dutyValue <<= 6;
        CCPR3H = dutyValue >> 8;
        CCPR3L = dutyValue;
    }
    else
    {
        CCPR3H = dutyValue >> 8;
        CCPR3L = dutyValue;
    }
}

bool PWM3_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP3CONbits.OUT);
}
/**
 End of File
*/

