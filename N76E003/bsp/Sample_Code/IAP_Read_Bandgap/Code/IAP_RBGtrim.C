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
//  File Function: N76E003 Read actual bandgap value by IAP command
//***********************************************************************************************************
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

double  Bandgap_Value,Bandgap_Voltage;			//please always use "double" mode for this
UINT8 BandgapHigh,BandgapLow;
		
void READ_BANDGAP()
{

		set_IAPEN;
		IAPAL = 0x0C;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPGO;
		BandgapHigh = IAPFD;
		IAPAL = 0x0d;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPGO;
		BandgapLow = IAPFD;
		BandgapLow = BandgapLow&0x0F;
		clr_IAPEN;
		Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
		Bandgap_Voltage = 3072/(0x0fff/Bandgap_Value);
}

void main(void)
{
	InitialUART0_Timer3(115200);
	READ_BANDGAP();
	printf ("\n Bandgap voltage = %e", Bandgap_Voltage); 
	printf ("\n Bandgap SFR  = 0x%bx", BandgapHigh);
	printf ("\n Bandgap SFR  = 0x%bx", BandgapLow);
	while(1);
}