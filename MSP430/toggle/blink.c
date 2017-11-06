//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  Texas Instruments, Inc
//  July 2013
//***************************************************************************************

#include <msp430.h>
#include <stdint.h>
#include <driverlib.h>

void main(void) {
    int i;
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    CS_initClockSignal(
        CS_FLLREF,
        CS_REFOCLK_SELECT,
        CS_CLOCK_DIVIDER_1
        );

    CS_initFLLSettle(
        16000,
        487
        );

    CS_initClockSignal(
        CS_MCLK,
        CS_DCOCLKDIV_SELECT,
        CS_CLOCK_DIVIDER_1
        );

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= 0x01;                          // Set P1.0 to output direction

    for(;;) {
        P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR
    }
}
