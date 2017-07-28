/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2016 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2016
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 UART-0 Mode3 demo code
//***********************************************************************************************************

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Function_define.h"

#define BUFFER_SIZE		16
UINT8  UART_BUFFER[BUFFER_SIZE],temp;
UINT16 u16CNT=0,u16CNT1=0;
bit riflag;


/**
 * FUNCTION_PURPOSE: serial interrupt, echo received data.
 * FUNCTION_INPUTS: P0.7(RXD) serial input
 * FUNCTION_OUTPUTS: P0.6(TXD) serial output
 */
void SerialPort0_ISR(void) interrupt 4 
{
    if (RI==1) 
    {                                       /* if reception occur */
        clr_RI;                             /* clear reception flag for next reception */
        UART_BUFFER[u16CNT] = SBUF;
        u16CNT ++;
				riflag =1;
    }
    if(TI==1)
    {
        clr_TI;                             /* if emission occur */
    }
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
		P12_PushPull_Mode;
		P06_Quasi_Mode;
		P07_Quasi_Mode;
	
		SCON = 0xD0;			// Special setting the mode 3 and 
		TMOD |= 0x20;    	//Timer1 Mode1
    
    set_SMOD;        	//UART0 Double Rate Enable
    set_T1M;
    clr_BRCK;        	//Serial port 0 baud rate clock source = Timer1
		TH1 = 256 - (1000000/115200+1);               /*16 MHz */
		set_TR1;
	
		set_RB8;					//This bit is for setting the stop bit 2 high/low status, 
	
		clr_TI; 
    set_ES;           //enable UART interrupt
    set_EA;           //enable global interrupt

    while(1)
		{
			if (riflag)
			{
				P12 = ~P12;		//In debug mode check UART_BUFFER[u16CNT] to check receive data
				riflag = 0;
			}
		}
	
}

