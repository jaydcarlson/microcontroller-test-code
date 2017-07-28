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
//  File Function: N76E003 Timer0/1 Mode3 demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
#if 0
//#define		TIMER0_MODE0_ENABLE		TMOD&=0x0F
//#define		TIMER0_MODE1_ENABLE		TMOD&=0x0F;TMOD|=0x10
//#define		TIMER0_MODE2_ENABLE		TMOD&=0x0F;TMOD|=0x20
//#define		TIMER0_MODE3_ENABLE		TMOD&=0x0F;TMOD|=0x3F

//#define		TIMER1_MODE0_ENABLE		TMOD&=0xF0
//#define		TIMER1_MODE1_ENABLE		TMOD&=0xF0;TMOD|=0x01
//#define		TIMER1_MODE2_ENABLE		TMOD&=0xF0;TMOD|=0x02
//#define		TIMER1_MODE3_ENABLE		TMOD&=0xF0;TMOD|=0xF3
#endif

#define TH0_INIT        (256-100)
#define TL0_INIT        (256-50)
#define TH1_INIT        0x00
#define TL1_INIT        0x00

/************************************************************************************************************
*    TIMER 0 interrupt subroutine
************************************************************************************************************/
void Timer0_ISR (void) interrupt 1              // interrupt address is 0x000B
{              
    TL0 = TL0_INIT;                             // reload by software    
    P12 = ~P12;                                 // GPIO1 toggle when interrupt
}

/************************************************************************************************************
*    TIMER 1 interrupt subroutine
************************************************************************************************************/
void Timer1_ISR (void) interrupt 3              //interrupt address is 0x001B
{           
    TH0 = TH0_INIT;
		Send_Data_To_UART0(0x54);										//print charater "T" means timer interrupt
		P12 = ~ P12;																//Mark UART output to find the real timer interrupt timming.
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    Set_All_GPIO_Quasi_Mode;
		InitialUART0_Timer3(115200);
	
		TIMER0_MODE3_ENABLE;
		TIMER1_MODE3_ENABLE;
    
    TH0 = TH0_INIT;                             //initial counter values 
    TL0 = TL0_INIT;    
    TH1 = TH1_INIT;
    TL1 = TL1_INIT;    
    
    set_ET0;                                    //enable Timer0 counter interrupt
    set_ET1;                                    //enable Timer1 counter interrupt
    set_EA;                                     //enable interrupts
    set_TR0;                                    //Timer0 run
    set_TR1;                                    //Timer1 run
    
    while(1);
}

