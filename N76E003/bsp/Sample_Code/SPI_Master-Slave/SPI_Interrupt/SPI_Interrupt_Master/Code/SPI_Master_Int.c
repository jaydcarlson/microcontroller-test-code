/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 SPI in Master mode demo code
//***********************************************************************************************************

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

//***********************************************************************************************************
//  Application: SPI Function 
//  Master send 0x90 and recevie 0x4E
//  Master send 0x01 and recevie 0x55
//  Master send 0x02 and recevie 0x56
//  Master send 0x03 and recevie 0x4F
//  Master send 0x04 and recevie 0x54
//
//  Master recevie 0x4E and 0x4F form slave after transmitting
//
//  Output : P1.4 & P2.1 flash when SPI pass
//           UART show result on hyper-terminal
//           P0.7 flash when SPI error
//***********************************************************************************************************

#if 0
///*****************************************************************************************
//* For ADC INIT setting 
//*****************************************************************************************/
//#define		SPICLK_DIV2			clr_SPR0;clr_SPR1
//#define		SPICLK_DIV4			set_SPR0;clr_SPR1
//#define		SPICLK_DIV8			clr_SPR0;set_SPR1
//#define		SPICLK_DIV16		set_SPR0;set_SPR1
//#define		Enable_SPI_Interrupt		set_ESPI;set_EA
//#define		SS		P15
#endif

//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    printf ("\nSPI error.\n");
    while(1)                                    // SPI error and P0.7 flash/
    {
        P07 = 1;
        Timer0_Delay1ms(500);
        P07 = 0;
        Timer0_Delay1ms(500);
    }
	}
//-----------------------------------------------------------------------------------------------------------
void SPI_Initial(void)
{              
		P15_Quasi_Mode;														// P15 (SS) Quasi mode
		P10_Quasi_Mode;														// P10(SPCLK) Quasi mode
		P00_Quasi_Mode;														// P00 (MOSI) Quasi mode
    P01_Quasi_Mode;														// P22 (MISO) Quasi mode
            
    set_DISMODF;															// SS General purpose I/O ( No Mode Fault ) 
    clr_SSOE;
   
    clr_LSBFE;																// MSB first         

    clr_CPOL;																	// The SPI clock is low in idle mode
    set_CPHA;																	// The data is sample on the second edge of SPI clock 
    
    set_MSTR;																	// SPI in Master mode 
     
    SPICLK_DIV2;															// Select SPI clock
    Enable_SPI_Interrupt;											// Enable SPI interrupt
    set_SPIEN;																// Enable SPI function 
}
//-----------------------------------------------------------------------------------------------------------
void Start_Sending_SPI(UINT8 *pu8MID,UINT8 *pu8DID)
{
    SS = 0;

    SPDR = 0x90;                                // Send 0x90 to Slave 
    PCON |= SET_BIT0;                           // Enter idle mode
    if(SPDR != 0x4E)                            // Receive slave 1st DATA 
       SPI_Error(); 
    printf ("\nSlave Return %c!\n",SPDR);
                                          
    SPDR = 0x01;                                // Send 0x01 to Slave 
    PCON |= SET_BIT0;                           // Enter idle mode
    if(SPDR != 0x55)                            // Receive slave 2nd DATA  
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x02;                                // Send 0x02 to Slave 
    PCON |= SET_BIT0;                           // Enter idle mode
    if(SPDR != 0x56)                            // Receive slave 3rd DATA 
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x03;                                // Send 0x03 to Slave 
    PCON |= SET_BIT0;                           // Enter idle mode
    if(SPDR != 0x4F)                            // Receive slave 4th DATA
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x04;                                // Send 0x04 to Slave 
    PCON |= SET_BIT0;                           // Enter idle mode
    if(SPDR != 0x54)                            // Receive slave 5th DATA 
       SPI_Error();
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x4F;                   
    PCON |= SET_BIT0;                           // Enter idle mode
    *pu8MID = SPDR;                             // Receive Slave 1st DATA fron Slave       
    printf ("\nSlave Return %c!\n",SPDR);

    SPDR = 0x4E;                   
    PCON |= SET_BIT0;                           // Enter idle mode             
    *pu8DID = SPDR;                             // Receive Slave 2nd DATA from Slave 
    printf ("\nSlave Return %c!\n",SPDR);

    SS = 1;    
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{      
    UINT8 u8MID,u8DID;
    
    Set_All_GPIO_Quasi_Mode;
    InitialUART0_Timer1(115200);             /* 115200 Baud Rate*/

    SPI_Initial();

    printf ("\nSPI Start Transmit...\n");

    Start_Sending_SPI(&u8MID,&u8DID);
        
    if((u8MID != 0x4F)&&(u8DID != 0x4E))
        SPI_Error();

    printf ("\nSPI Test OK!\n");
    while(1)                                    // SPI transmission finish
    {
        P12 = 1;
        Timer0_Delay1ms(500);
        P12 = 0;
        Timer0_Delay1ms(500);
    }
}
//-----------------------------------------------------------------------------------------------------------
void SPI_ISR(void) interrupt 9                  // Vecotr @  0x4B
{
    clr_SPIF;
    Timer3_Delay10us(1); 
}
//-----------------------------------------------------------------------------------------------------------
