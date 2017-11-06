/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.26
        Device            :  PIC16LF18855
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set TOGGLE aliases
#define TOGGLE_TRIS               TRISAbits.TRISA0
#define TOGGLE_LAT                LATAbits.LATA0
#define TOGGLE_PORT               PORTAbits.RA0
#define TOGGLE_WPU                WPUAbits.WPUA0
#define TOGGLE_OD                ODCONAbits.ODCA0
#define TOGGLE_ANS                ANSELAbits.ANSA0
#define TOGGLE_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define TOGGLE_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define TOGGLE_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define TOGGLE_GetValue()           PORTAbits.RA0
#define TOGGLE_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define TOGGLE_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define TOGGLE_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define TOGGLE_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define TOGGLE_SetPushPull()    do { ODCONAbits.ODCA0 = 1; } while(0)
#define TOGGLE_SetOpenDrain()   do { ODCONAbits.ODCA0 = 0; } while(0)
#define TOGGLE_SetAnalogMode()  do { ANSELAbits.ANSA0 = 1; } while(0)
#define TOGGLE_SetDigitalMode() do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()    do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()   do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()   do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()         PORTBbits.RB0
#define RB0_SetDigitalInput()   do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()  do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()     do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()   do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode() do { ANSELBbits.ANSB0 = 1; } while(0)
#define RB0_SetDigitalMode()do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()    do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()   do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()   do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()         PORTBbits.RB1
#define RB1_SetDigitalInput()   do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()  do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()     do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()   do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode() do { ANSELBbits.ANSB1 = 1; } while(0)
#define RB1_SetDigitalMode()do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()    do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()   do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()   do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()         PORTBbits.RB2
#define RB2_SetDigitalInput()   do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()  do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()     do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()   do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode() do { ANSELBbits.ANSB2 = 1; } while(0)
#define RB2_SetDigitalMode()do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()    do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()   do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()   do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()         PORTCbits.RC3
#define RC3_SetDigitalInput()   do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()  do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()     do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()   do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode() do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()     do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()   do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()     do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()   do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode() do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/