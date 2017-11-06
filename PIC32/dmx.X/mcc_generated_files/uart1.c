/**
  UART1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.c

  @Summary
    This is the generated driver implementation file for the UART1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for UART1.
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

/**
  Section: Included Files
*/
#include "uart1.h"

/**
  Section: UART1 APIs
*/

void UART1_Initialize(void)
{
    // Set the UART1 module to the options selected in the user interface.

    // STSEL 1; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL PBCLK; 
    U1MODE = (0x8008 & ~(1<<15)); // disabling UART ON bit  
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x0;
    // BaudRate = 250000; Frequency = 1000000 Hz; BRG 0; 
    U1BRG = 0x0;
     
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1STASET = _U1STA_UTXEN_MASK;
    U1MODESET = _U1MODE_ON_MASK;  // enabling UART ON bit
    U1STASET = _U1STA_URXEN_MASK; 

    
    
}


uint8_t UART1_Read(void)
{
    while(!(U1STAbits.URXDA == 1))
    {
        
    }

    if ((U1STAbits.OERR == 1))
    {
        U1STACLR = _U1STA_OERR_MASK;
    }

    

    return U1RXREG;
}

void UART1_Write(uint8_t txData)
{
    while(U1STAbits.UTXBF == 1)
    {
        
    }

    U1TXREG = txData;    // Write the data byte to the USART.
}

UART1_STATUS UART1_StatusGet (void)
{
    return U1STA;
}


/**
  End of File
*/
