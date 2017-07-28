/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2016
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 UART-0 Mode1 demo code
//***********************************************************************************************************

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"


#define BUFFER_SIZE		16
UINT8  UART_BUFFER[BUFFER_SIZE],temp;
UINT16 u16CNT=0,u16CNT1=0;
bit riflag;


/******************************************************************************
 * FUNCTION_PURPOSE: Serial port 1 interrupt, echo received data.
 * FUNCTION_INPUTS : P0.2(RXD) serial input
 * FUNCTION_OUTPUTS: P1.6(TXD) serial output
 * Following setting in Common.c
 ******************************************************************************/
#if 0
//void InitialUART1_Timer3(UINT32 u32Baudrate) //use timer3 as Baudrate generator
//{
//		P02_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
//		P16_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
//	
//	  SCON_1 = 0x50;   	//UART1 Mode1,REN_1=1,TI_1=1
//    T3CON = 0x08;   	//T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
//		clr_BRCK;
//	
//#ifdef FOSC_160000
//		RH3    = HIBYTE(65536 - (1000000/u32Baudrate)-1);  		/*16 MHz */
//		RL3    = LOBYTE(65536 - (1000000/u32Baudrate)-1);			/*16 MHz */
//#endif
//#ifdef FOSC_166000
//		RH3    = HIBYTE(65536 - (1037500/u32Baudrate));  			/*16.6 MHz */
//		RL3    = LOBYTE(65536 - (1037500/u32Baudrate));				/*16.6 MHz */
//#endif
//    set_TR3;         //Trigger Timer3
//}
#endif

void SerialPort1_ISR(void) interrupt 15 
{
    if (RI_1==1) 
    {                                       /* if reception occur */
        clr_RI_1;                             /* clear reception flag for next reception */
        UART_BUFFER[u16CNT] = SBUF_1;
        u16CNT ++;
				riflag =1;
    }
    if(TI_1==1)
    {
        clr_TI_1;                             /* if emission occur */
    }
}


/****************************************************************************************************************
 * FUNCTION_PURPOSE: Main function 
  
 !!! N76E003 UART1 pin also occupied by debug pin, 
 please remove Nu-link or not in debug mode to test UART1 function.

 External UART1 connect also disturb debug download

 ***************************************************************************************************************/
void main (void)
{
	P12_PushPull_Mode;		// For I/O toggle display
	
#if 0	
//for Simple use UART1 transmit out
		InitialUART1_Timer3(115200);		
    while(1)
    Send_Data_To_UART1(0x55);
		
#else			
// For interrupt setting check receive 
		InitialUART1_Timer3(115200);
		set_ES_1;					//For interrupt enable
		set_EA;
		
		while(1)
		{
			if (riflag)
			{
					P12 = ~ P12;			//Receive each byte P12 toggle, never work under debug mode
					riflag = 0;
			}
		}

#endif
			
	
		
}
  
