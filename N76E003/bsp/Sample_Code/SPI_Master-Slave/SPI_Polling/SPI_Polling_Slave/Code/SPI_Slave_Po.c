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
//  File Function: N76E003 SPI in Slave mode demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

//***********************************************************************************************************
//  Application: SPI Function 
//  Slave receive 0x90 and return 0x4E
//  Slave receive 0x01 and return 0x55
//  Slave receive 0x02 and return 0x56
//  Slave receive 0x03 and return 0x4F
//  Slave receive 0x04 and return 0x54
//
//  Slave send 0x4F and 0x4E to Master after receiving
//  
//  Output : P1.2 (GPIO1) flash when SPI pass.
//           P0.7 flash when SPI error 
//***********************************************************************************************************


//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
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
            
    set_P0S_5;                                  //Schmitt triggered input select.
    
    clr_MSTR;                                   // SPI in Slave mode 
    clr_LSBFE;                                  // MSB first 

    clr_CPOL;                                   // The SPI clock is low in idle mode
    set_CPHA;                                   // The data is sample on the second edge of SPI clock     
       
    set_SPIEN;                                  // Enable SPI function
    clr_SPIF; 
}
//-----------------------------------------------------------------------------------------------------------
void Slave_Receive_Data(void)
{
    SPDR = 0x4E;                                // Receive Master 1st DATA 
    while(!(SPSR & SET_BIT7));          
    clr_SPIF;
    if(SPDR != 0x90)                      
       SPI_Error(); 
                                                
    SPDR = 0x55;                                // Receive Master 2nd DATA 
    while(!(SPSR & SET_BIT7));          
    clr_SPIF;
    if(SPDR != 0x01)
       SPI_Error();
                                                 
    SPDR = 0x56;                                // Receive Master 3rd DATA
    while(!(SPSR & SET_BIT7));                  
    clr_SPIF;
    if(SPDR != 0x02)
        SPI_Error();
    
    SPDR = 0x4F;                                // Receive Master 4th DATA 
    while(!(SPSR & SET_BIT7));                  
    clr_SPIF;
    if(SPDR != 0x03)
        SPI_Error();
                                                
    SPDR = 0x54;                                // Receive Master 5th DATA
    while(!(SPSR & SET_BIT7));                   
    clr_SPIF;
    if(SPDR != 0x04)
        SPI_Error();
}
//-----------------------------------------------------------------------------------------------------------
void Slave_tranmit_Data(void)
{
    SPDR = 0x4F;                                // Send 1st data (0x4F) to Master 
    while(!(SPSR & SET_BIT7));      
    clr_SPIF;
    if(SPDR != 0xFF)
        SPI_Error();
    
    SPDR = 0x4E;                                // Send 2nd data (0x4E) to Master 
    while(!(SPSR & SET_BIT7));      
    clr_SPIF;
    if(SPDR != 0xFF)
        SPI_Error();
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{   
     Set_All_GPIO_Quasi_Mode;
    InitialUART0_Timer1(115200);             /* 9600 Baud Rate*/

    SPI_Initial();

    printf ("\nSPI Start Receive...\n");    
         
    Slave_Receive_Data();                       // Slave receive data from master
    Slave_tranmit_Data();                       // Slave transmit data to master
    while(1)                                    
    {
        P12 = 1;
        Timer0_Delay1ms(500);
        P12 = 0;
        Timer0_Delay1ms(500);
    }
}
//-----------------------------------------------------------------------------------------------------------
