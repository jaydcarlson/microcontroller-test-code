/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC32MM0064GPL028
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
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

#include "mcc_generated_files/mcc.h"


uint8_t data[514];
uint16_t address = 1;
int16_t currentByte = -1;

void __attribute__ ((vector(_UART1_ERR_VECTOR), interrupt(IPL1SOFT))) _UART1_ERR ( void )
{
    currentByte = 0;

    if ((U1STAbits.OERR == 1))
    {
        U1STACLR = _U1STA_OERR_MASK; 
    }

     IFS0CLR= 1 << _IFS0_U1EIF_POSITION;
     
}

void __attribute__ ((vector(_UART1_RX_VECTOR), interrupt(IPL1SOFT))) _UART1_RX( void )
{
    TOGGLE_SetHigh();
    while((U1STAbits.URXDA == 1))
    {
        uint8_t temp = U1RXREG;

        if(currentByte >= 0)
        {
            data[currentByte++] = temp;
        }
    
        if(currentByte > 512)
        {
            MCCP1_COMPARE_DualCompareValueSet(0, 255 - data[address + 0]);
            SCCP2_COMPARE_DualCompareValueSet(0, 255 - data[address + 1]);
            SCCP3_COMPARE_DualCompareValueSet(0, 255 - data[address + 2]);
            currentByte = -1;
        }
    }
      IFS0CLR= 1 << _IFS0_U1RXIF_POSITION;
      TOGGLE_SetLow();
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // MCC can't be bothered to generate this interrupt-enable code for us:
    IPC6bits.U1EIP = 1;
    IPC6bits.U1EIS = 0;
    IPC6bits.U1TXIP = 1;
    IPC6bits.U1TXIS = 0;
    IPC5bits.U1RXIP = 1;
    IPC5bits.U1RXIS = 0;  
   
    IEC0bits.U1EIE = true;
    IEC0bits.U1RXIE = true;
    
    INTERRUPT_GlobalEnable();

    while (1)
    {
        asm("wait");
//        TOGGLE_Toggle();
        // Add your application code
    }
}
/**
 End of File
*/