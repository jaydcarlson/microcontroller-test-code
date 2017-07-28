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
//  File Function: N76E003 GPIO demo code
//***********************************************************************************************************
#include "N76E885.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
#if 0
////------------------- Define Port as Quasi mode  -------------------
//#define P00_Quasi_Mode				P0M1&=~SET_BIT0;P0M2&=~SET_BIT0
//#define P01_Quasi_Mode				P0M1&=~SET_BIT1;P0M2&=~SET_BIT1
//#define P02_Quasi_Mode				P0M1&=~SET_BIT2;P0M2&=~SET_BIT2
//#define P03_Quasi_Mode				P0M1&=~SET_BIT3;P0M2&=~SET_BIT3
//#define P04_Quasi_Mode				P0M1&=~SET_BIT4;P0M2&=~SET_BIT4
//#define P05_Quasi_Mode				P0M1&=~SET_BIT5;P0M2&=~SET_BIT5
//#define P06_Quasi_Mode				P0M1&=~SET_BIT6;P0M2&=~SET_BIT6
//#define P07_Quasi_Mode				P0M1&=~SET_BIT7;P0M2&=~SET_BIT7
//#define P10_Quasi_Mode				P1M1&=~SET_BIT0;P1M2&=~SET_BIT0
//#define P11_Quasi_Mode				P1M1&=~SET_BIT1;P1M2&=~SET_BIT1
//#define P12_Quasi_Mode				P1M1&=~SET_BIT2;P1M2&=~SET_BIT2
//#define P13_Quasi_Mode				P1M1&=~SET_BIT3;P1M2&=~SET_BIT3
//#define P14_Quasi_Mode				P1M1&=~SET_BIT4;P1M2&=~SET_BIT4
//#define P15_Quasi_Mode				P1M1&=~SET_BIT5;P1M2&=~SET_BIT5
//#define P16_Quasi_Mode				P1M1&=~SET_BIT6;P1M2&=~SET_BIT6
//#define P17_Quasi_Mode				P1M1&=~SET_BIT7;P1M2&=~SET_BIT7
//#define P20_Quasi_Mode				P2M1&=~SET_BIT0;P2M2&=~SET_BIT0
//#define P30_Quasi_Mode				P3M1&=~SET_BIT0;P3M2&=~SET_BIT0
////------------------- Define Port as Push Pull mode -------------------
//#define P00_PushPull_Mode			P0M1|=SET_BIT0;P0M2&=~SET_BIT0
//#define P01_PushPull_Mode			P0M1|=SET_BIT1;P0M2&=~SET_BIT1
//#define P02_PushPull_Mode			P0M1&=~SET_BIT2;P0M2|=SET_BIT2
//#define P03_PushPull_Mode			P0M1&=~SET_BIT3;P0M2|=SET_BIT3
//#define P04_PushPull_Mode			P0M1&=~SET_BIT4;P0M2|=SET_BIT4
//#define P05_PushPull_Mode			P0M1&=~SET_BIT5;P0M2|=SET_BIT5
//#define P06_PushPull_Mode			P0M1&=~SET_BIT6;P0M2|=SET_BIT6
//#define P07_PushPull_Mode			P0M1&=~SET_BIT7;P0M2|=SET_BIT7
//#define P10_PushPull_Mode			P1M1&=~SET_BIT0;P1M2|=SET_BIT0
//#define P11_PushPull_Mode			P1M1&=~SET_BIT1;P1M2|=SET_BIT1
//#define P12_PushPull_Mode			P1M1&=~SET_BIT2;P1M2|=SET_BIT2
//#define P13_PushPull_Mode			P1M1&=~SET_BIT3;P1M2|=SET_BIT3
//#define P14_PushPull_Mode			P1M1&=~SET_BIT4;P1M2|=SET_BIT4
//#define P15_PushPull_Mode			P1M1&=~SET_BIT5;P1M2|=SET_BIT5
//#define P16_PushPull_Mode			P1M1&=~SET_BIT6;P1M2|=SET_BIT6
//#define P17_PushPull_Mode			P1M1&=~SET_BIT7;P1M2|=SET_BIT7
//#define P20_PushPull_Mode			P2M1&=~SET_BIT0;P2M2|=SET_BIT0
//#define P30_PushPull_Mode			P3M1&=~SET_BIT0;P3M2|=SET_BIT0
////------------------- Define Port as Input Only mode -------------------
//#define P00_Input_Mode				P0M1|=SET_BIT0;P0M2&=~SET_BIT0
//#define P01_Input_Mode				P0M1|=SET_BIT1;P0M2&=~SET_BIT1
//#define P02_Input_Mode				P0M1|=SET_BIT2;P0M2&=~SET_BIT2
//#define P03_Input_Mode				P0M1|=SET_BIT3;P0M2&=~SET_BIT3
//#define P04_Input_Mode				P0M1|=SET_BIT4;P0M2&=~SET_BIT4
//#define P05_Input_Mode				P0M1|=SET_BIT5;P0M2&=~SET_BIT5
//#define P06_Input_Mode				P0M1|=SET_BIT6;P0M2&=~SET_BIT6
//#define P07_Input_Mode				P0M1|=SET_BIT7;P0M2&=~SET_BIT7
//#define P10_Input_Mode				P1M1|=SET_BIT0;P1M2&=~SET_BIT0
//#define P11_Input_Mode				P1M1|=SET_BIT1;P1M2&=~SET_BIT1
//#define P12_Input_Mode				P1M1|=SET_BIT2;P1M2&=~SET_BIT2
//#define P13_Input_Mode				P1M1|=SET_BIT3;P1M2&=~SET_BIT3
//#define P14_Input_Mode				P1M1|=SET_BIT4;P1M2&=~SET_BIT4
//#define P15_Input_Mode				P1M1|=SET_BIT5;P1M2&=~SET_BIT5
//#define P16_Input_Mode				P1M1|=SET_BIT6;P1M2&=~SET_BIT6
//#define P17_Input_Mode				P1M1|=SET_BIT7;P1M2&=~SET_BIT7
//#define P20_Input_Mode				P2M1|=SET_BIT0;P2M2&=~SET_BIT0
//#define P30_Input_Mode				P3M1|=SET_BIT0;P3M2&=~SET_BIT0
////-------------------Define Port as Open Drain mode -------------------
//#define P00_OpenDrain_Mode		P0M1|=SET_BIT0;P0M2|=SET_BIT0
//#define P01_OpenDrain_Mode		P0M1|=SET_BIT1;P0M2|=SET_BIT1
//#define P02_OpenDrain_Mode		P0M1|=SET_BIT2;P0M2|=SET_BIT2
//#define P03_OpenDrain_Mode		P0M1|=SET_BIT3;P0M2|=SET_BIT3
//#define P04_OpenDrain_Mode		P0M1|=SET_BIT4;P0M2|=SET_BIT4
//#define P05_OpenDrain_Mode		P0M1|=SET_BIT5;P0M2|=SET_BIT5
//#define P06_OpenDrain_Mode		P0M1|=SET_BIT6;P0M2|=SET_BIT6
//#define P07_OpenDrain_Mode		P0M1|=SET_BIT7;P0M2|=SET_BIT7
//#define P10_OpenDrain_Mode		P1M1|=SET_BIT0;P1M2|=SET_BIT0
//#define P11_OpenDrain_Mode		P1M1|=SET_BIT1;P1M2|=SET_BIT1
//#define P12_OpenDrain_Mode		P1M1|=SET_BIT2;P1M2|=SET_BIT2
//#define P13_OpenDrain_Mode		P1M1|=SET_BIT3;P1M2|=SET_BIT3
//#define P14_OpenDrain_Mode		P1M1|=SET_BIT4;P1M2|=SET_BIT4
//#define P15_OpenDrain_Mode		P1M1|=SET_BIT5;P1M2|=SET_BIT5
//#define P16_OpenDrain_Mode		P1M1|=SET_BIT6;P1M2|=SET_BIT6
//#define P17_OpenDrain_Mode		P1M1|=SET_BIT7;P1M2|=SET_BIT7
//#define P20_OpenDrain_Mode		P2M1|=SET_BIT0;P2M2|=SET_BIT0
//#define P30_OpenDrain_Mode		P3M1|=SET_BIT0;P3M2|=SET_BIT0
////--------- Define all port as quasi mode ---------
//#define Set_All_GPIO_Quasi_Mode			P0M1=0;P0M1=0;P1M1=0;P1M2=0;P2M1=0;P2M2=0;P3M1=0;P3M2=0
#endif

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/

//void PinInterrupt_ISR (void) interrupt 7
//{
//	if (PIF == 0x80)
//	{
//			clr_GPIO1;
//			Timer1_Delay10ms(10);
//			set_GPIO1;
//			Timer1_Delay10ms(10);
//			clr_GPIO1;
//			Timer1_Delay10ms(10);
//			set_GPIO1;
//			Timer1_Delay10ms(10);   
//			clr_GPIO1;
//			Timer1_Delay10ms(10);
//			set_GPIO1;
//			Timer1_Delay10ms(10);
//			clr_GPIO1;
//			Timer1_Delay10ms(10);
//			set_GPIO1;
//			Timer1_Delay10ms(10);    
//	}
//}



sfr PORDIS	= 0xFD;


void LED_DATA0(void)
{
	P10 = 1 ;
	P10 = 0;
	P10 = 0;
}

void LED_DATA1(void)
{
	P10 = 1 ;
	P10 = 1;
	P10 = 1;
		P10 = 1;
		P10 = 1;
	P10 = 0;
}


void main (void) 
{
	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	

	P10_PushPull_Mode;
P1SR = 0x01;
  


		LED_DATA0();
		LED_DATA1();
		LED_DATA0();
		LED_DATA1();
		LED_DATA0();
		LED_DATA1();	
		LED_DATA0();
		LED_DATA1();
		LED_DATA0();
		LED_DATA1();
		LED_DATA0();
		LED_DATA1();
		LED_DATA0();
		LED_DATA1();

		LED_DATA0();
		LED_DATA1();
				LED_DATA0();
		LED_DATA1();
				LED_DATA0();
		LED_DATA1();
while(1);

	
	
}



