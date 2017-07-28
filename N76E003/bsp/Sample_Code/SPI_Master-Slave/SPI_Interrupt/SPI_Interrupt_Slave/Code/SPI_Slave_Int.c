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
//  Output : P1.2 GPIO flash when SPI pass.
//           P0.7 flash when SPI error 
//***********************************************************************************************************

UINT8   u8Receive_Data[5];
UINT16  u16CNT = 0;
bit     SPI_Send_Flag = 0;

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
		P15_Quasi_Mode;														//P15 (SS) Quasi mode
		P10_Quasi_Mode;														//P10(SPCLK) Quasi mode
		P00_Quasi_Mode;														//P00 (MOSI) Quasi mode
    P01_Quasi_Mode;														//P22 (MISO) Quasi mode;

    clr_MSTR;                                   // SPI in Slave mode 
    clr_LSBFE;                                  // MSB first 

    clr_CPOL;                                   // The SPI clock is low in idle mode
    set_CPHA;                                   // The data is sample on the second edge of SPI clock     
       
    Enable_SPI_Interrupt;                     	// Enable SPI interrupt
    set_SPIEN;                                  // Enable SPI function
    
    clr_SPIF;                                   // Clear SPI flag
}
//-----------------------------------------------------------------------------------------------------------
void Slave_Receive_Data(void)
{
    SPDR = 0x4E;                             
    PCON |= SET_BIT0;                           // Enter idle mode 
    if(u8Receive_Data[0] != 0x90)               // Receive 1st DATA form master 
        SPI_Error(); 
          
    SPDR = 0x55;
    PCON |= SET_BIT0;                           // Enter idle mode                       
    if(u8Receive_Data[1] != 0x01)               // Receive 2nd DATA form master 
        SPI_Error();

    SPDR = 0x56;
    PCON |= SET_BIT0;                           // Enter idle mode
    if(u8Receive_Data[2] != 0x02)               // Receive 3rd DATA form master 
        SPI_Error();

    SPDR = 0x4F;
    PCON |= SET_BIT0;                           // Enter idle mode
    if(u8Receive_Data[3] != 0x03)               // Receive 4th DATA form master 
        SPI_Error();

    SPDR = 0x54;
    PCON |= SET_BIT0;                           // Enter idle mode
    if(u8Receive_Data[4] != 0x04)               // Receive 5th DATA form master 
        SPI_Error();
}
//-----------------------------------------------------------------------------------------------------------
void Slave_Transmit_Data(void)
{
    SPI_Send_Flag = 1;
    SPDR = 0x4F;                                // Send 1st data (04F) to Master
    PCON |= SET_BIT0;                           // Enter idle mode       

    SPI_Send_Flag = 1;
    SPDR = 0x4E;                                // Send 2nd data (0x4E) to Master 
    PCON |= SET_BIT0;                           // Enter idle mode
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{   
    Set_All_GPIO_Quasi_Mode;
    InitialUART0_Timer1(115200);             /* 115200 Baud Rate*/
 
    SPI_Initial();

    printf ("\nSPI Start Receive...\n");

    Slave_Receive_Data();                       // Slave receive data from master
    Slave_Transmit_Data();                      // Slave transmit data to master

    clr_ESPI;
    SPDR = 0x00;
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
    if(!SPI_Send_Flag)
    {       
        u8Receive_Data[u16CNT] = SPDR;
        u16CNT ++;
    }
    SPI_Send_Flag = 0; 
}
//-----------------------------------------------------------------------------------------------------------