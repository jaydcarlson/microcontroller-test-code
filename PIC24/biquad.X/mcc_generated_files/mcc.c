/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC24F16KA101
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60
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

// Configuration bits: selected in the GUI

// FBS
#pragma config BWRP = OFF    // Table Write Protect Boot->Boot segment may be written
#pragma config BSS = OFF    // Boot segment Protect->No boot program Flash segment

// FGS
#pragma config GWRP = OFF    // General Segment Code Flash Write Protection bit->General segment may be written
//#pragma config GCP = OFF    // General Segment Code Flash Code Protection bit->No protection

// FOSCSEL
#pragma config FNOSC = FRCPLL    // Oscillator Select->Fast RC oscillator with divide-by-N with PLL module (FRCDIV+PLL)
#pragma config IESO = ON    // Internal External Switch Over bit->Internal External Switchover mode enabled (Two-Speed Start-up enabled)

// FOSC
//#pragma config POSCMOD = NONE    // Primary Oscillator Configuration bits->Primary oscillator disabled
#pragma config OSCIOFNC = ON    // CLKO Enable Configuration bit->CLKO output disabled; pin functions as port I/O
#pragma config POSCFREQ = HS    // Primary Oscillator Frequency Range Configuration bits->Primary oscillator/external clock input frequency greater than 8 MHz
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

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // NOSC FRCPLL; SOSCEN disabled; OSWEN Switch is Complete; 
    __builtin_write_OSCCONL((uint8_t) (0x0100 & 0x00FF));
    // RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // TUN Center frequency; 
    OSCTUN = 0x0000;
}

/**
 End of File
*/