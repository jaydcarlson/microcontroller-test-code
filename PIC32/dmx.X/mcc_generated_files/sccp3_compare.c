
/**
  SCCP3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    sccp3.c

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

/**
  Section: Included Files
*/

#include <xc.h>
#include "sccp3_compare.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gSCCP3Mode;

/**
  Section: Driver Interface
*/


void SCCP3_COMPARE_Initialize (void)
{
    // ON enabled; MOD Dual Edge Compare; ALTSYNC disabled; SIDL disabled; OPS Each Time Base Period Match; CCPSLP disabled; TMRSYNC disabled; RTRGEN disabled; CCSEL disabled; ONESHOT disabled; TRIGEN disabled; T32 16 Bit; SYNC None; OPSSRC Timer Interrupt Event; TMRPS 1:64; CLKSEL SYSCLK; 
    CCP3CON1 = (0x80C4 & 0xFFFF7FFF); //Disabling CCPON bit
    //ASDGM disabled; ICGSM Level-Sensitive mode; ICS ICM3; SSDG disabled; AUXOUT Disabled; ASDG None; PWMRSEN disabled; OCAEN enabled; OENSYNC disabled; 
    CCP3CON2 = 0x1000000;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP3CON3 = 0x0;
    //SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; ICGARM disabled; RBWIP disabled; TRCLR disabled; RAWIP disabled; TMRHWIP disabled; TMRLWIP disabled; PRLWIP disabled; 
    CCP3STAT = 0x0;
    //TMRL 0; TMRH 0; 
    CCP3TMR = 0x0;
    //PRH 0; PRL 255; 
    CCP3PR = 0xFF;
    //CMPA 0; 
    CCP3RA = 0x0;
    //CMPB 240; 
    CCP3RB = 0xF0;
    //BUFL 0; BUFH 0; 
    CCP3BUF = 0x0;

    CCP3CON1bits.ON = 0x1; //Enabling CCP

    gSCCP3Mode = CCP3CON1bits.MOD;

}

void SCCP3_COMPARE_Tasks( void )
{
    if(IFS1bits.CCP3IF)
    {
        IFS1CLR= 1 << _IFS1_CCP3IF_POSITION;
    }
}


void SCCP3_COMPARE_TimerTasks( void )
{
    if(IFS1bits.CCT3IF)
    {
        IFS1CLR= 1 << _IFS1_CCT3IF_POSITION;
    }
}

void SCCP3_COMPARE_Start( void )
{
    /* Start the Timer */
    CCP3CON1SET = (1 << _CCP3CON1_ON_POSITION);
}
void SCCP3_COMPARE_Stop( void )
{
    /* Start the Timer */
    CCP3CON1CLR = (1 << _CCP3CON1_ON_POSITION);
}

void SCCP3_COMPARE_SingleCompare16ValueSet( uint16_t value )
{   
    CCP3RA = value;
}


void SCCP3_COMPARE_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{
    
    CCP3RA = priVal;
	
    CCP3RB = secVal;
}
void SCCP3_COMPARE_DualEdgeBufferedConfig( uint16_t priVal, uint16_t secVal )
{
    
    CCP3RA = priVal;
	
    CCP3RB = secVal;
}
void SCCP3_COMPARE_CenterAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    
    CCP3RA = priVal;
	
    CCP3RB = secVal;
}
void SCCP3_COMPARE_VariableFrequencyPulseConfig( uint16_t priVal )
{
    CCP3RA = priVal;
	
}
bool SCCP3_COMPARE_IsCompareCycleComplete( void )
{
    return(IFS1bits.CCP3IF);
}
bool SCCP3_COMPARE_TriggerStatusGet( void )
{
    return( CCP3STATbits.CCPTRIG );
    
}
void SCCP3_COMPARE_TriggerStatusSet( void )
{
    CCP3STATSET = (1 << _CCP3STAT_TRSET_POSITION);
}
void SCCP3_COMPARE_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    CCP3STATCLR = (1 << _CCP3STAT_TRCLR_POSITION);
}
bool SCCP3_COMPARE_SingleCompareStatusGet( void )
{
    return( CCP3STATbits.SCEVT );
}
void SCCP3_COMPARE_SingleCompareStatusClear( void )
{
    /* Clears the trigger status */
    CCP3STATCLR = (1 << _CCP3STAT_SCEVT_POSITION);
    
}
/**
 End of File
*/
