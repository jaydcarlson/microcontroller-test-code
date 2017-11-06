/*
 * File:   main.c
 * Author: JayLocal
 *
 * Created on September 12, 2017, 10:55 PM
 */

// Configuration bits: selected in the GUI
#define _XTAL_FREQ  32000000UL
// FBS
#pragma config BWRP = OFF    // Table Write Protect Boot->Boot segment may be written
#pragma config BSS = OFF    // Boot segment Protect->No boot program Flash segment

// FGS
#pragma config GWRP = OFF    // General Segment Code Flash Write Protection bit->General segment may be written

// FOSCSEL
#pragma config FNOSC = FRCDIV    // Oscillator Select->Fast RC oscillator with divide-by-N with PLL module (FRCDIV+PLL)
#pragma config IESO = ON    // Internal External Switch Over bit->Internal External Switchover mode enabled (Two-Speed Start-up enabled)

// FOSC
#pragma config OSCIOFNC = ON    // CLKO Enable Configuration bit->CLKO output disabled; pin functions as port I/O
#pragma config POSCMD   = HS
#pragma config POSCFREQ = MS    // Primary Oscillator Frequency Range Configuration bits->Primary oscillator/external clock input frequency greater than 8 MHz
#pragma config SOSCSEL = SOSCHP    // SOSC Power Selection Configuration bits->Secondary oscillator configured for high-power operation
#pragma config FCKSM = CSDCMD    // Clock Switching and Monitor Selection->Both Clock Switching and Fail-safe Clock Monitor are disabled

// FWDT
#pragma config WDTPS = PS32768    // Watchdog Timer Postscale Select bits->1:32,768
#pragma config FWPSA = PR128    // WDT Prescaler->WDT prescaler ratio of 1:128
#pragma config WINDIS = OFF    // Windowed Watchdog Timer Disable bit->Standard WDT selected; windowed WDT disabled
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bit->WDT disabled (control is placed on the SWDTEN bit)

// FPOR
#pragma config BOREN = BOR3    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware; SBOREN bit disabled
#pragma config PWRTEN = ON    // Power-up Timer Enable bit->PWRT enabled
#pragma config I2C1SEL = PRI    // Alternate I2C1 Pin Mapping bit->Default location for SCL1/SDA1 pins
#pragma config BORV = V18    // Brown-out Reset Voltage bits->Brown-out Reset set to lowest voltage (1.8V)
#pragma config MCLRE = ON    // MCLR Pin Enable bit->MCLR pin enabled; RA5 input pin disabled

// FICD
#pragma config ICS = PGx2    // ICD Pin Placement Select bits->PGC2/PGD2 are used for programming and debugging the device
//#pragma config COE = OFF    // Set Clip On Emulation bit->Device will reset into Operational Mode
//#pragma config BKBUG = OFF    // Background Debugger Enable bit->Background debugger disabled
//
//// FDS
//#pragma config DSWDTPS = DSWDTPSF    // Deep Sleep Watchdog Timer Postscale Select bits->1:2,147,483,648 (25.7 Days)
//#pragma config DSWDTOSC = LPRC    // DSWDT Reference Clock Select bit->DSWDT uses LPRC as reference clock
//#pragma config RTCOSC = SOSC    // RTCC Reference Clock Select bit->RTCC uses SOSC as reference clock
//#pragma config DSBOREN = ON    // Deep Sleep Zero-Power BOR Enable bit->Deep Sleep BOR enabled in Deep Sleep
//#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer Enable bit->DSWDT enabled

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include <p24F04KL100.h>

int16_t index = -1;
uint8_t address = 1;

uint8_t data[256];

void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void)
{
    _LATB8 = 1;
    if(U1STAbits.FERR == 1)
    {
        index = 0;
    }
    
    // Receive Data Ready
    while (U1STAbits.URXDA)
    {
        uint8_t temp = U1RXREG;

        if(U1STAbits.OERR == 1)
        {
            U1STAbits.OERR = 0;
            continue;
        }
        
        if (index >= 0)
        {
            data[index++] = temp;
        }
        
        if(index > 255)
        {
            CCPR1L = 255 - data[address + 1];
            CCPR2L = 255 - data[address + 2];
            index = -1;
        }
    }    

    IFS0bits.U1RXIF = 0;        // clear rx interrupt flag 
    _LATB8 = 0;
}

void main(void) {
        // NOSC FRCPLL; SOSCEN disabled; OSWEN Switch is Complete; 
    __builtin_write_OSCCONL((uint8_t) (0x0100 & 0x00FF));
    // RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3200;
    // TUN Center frequency; 
    OSCTUN = 0x0000;

    ANSBbits.ANSB15 = 0;    // RX
    IPC2bits.U1RXIP = 4;            //interrupt priority level for receive
    IPC3bits.U1TXIP = 4;            //interrupt ptiority level for transmit
    U1STA = 0;
    U1BRG = 0;                      //Baud rate set to 250 kbaud
    U1MODE = 0;                     //8-bit data, no parity, 1 stop bit
    U1MODEbits.BRGH = 1;
    U1MODEbits.UARTEN = 1;          //enable the module
    U1STAbits.URXISEL0 = 0;
    U1STAbits.URXISEL1 = 0;         //interrupt generated when RX is complete
    IFS0bits.U1RXIF = 0;            //clear receive interrupt flag
    IEC0bits.U1RXIE = 1;            //UART receiver interrupt enabled
    IPC2bits.U1RXIP = 1;
    
    _TRISB8 = 0;
    // PWM config
    T2CONbits.TMR2ON = 1;
    CCP1CONbits.CCP1M = 0x0c;
    
    CCP2CONbits.CCP2M = 0x0c;
    while(1)
    {
        Idle();
    }
}
