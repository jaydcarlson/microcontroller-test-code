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
//  File Function: N76E885 ADC demo code
//***********************************************************************************************************

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************

double  Bandgap_Voltage,VDD_Voltage;			//please always use "double" mode for this
		
void ADC_Bypass (void)
{
		unsigned char ozc;
		for (ozc=0;ozc<0x03;ozc++)
		{
			clr_ADCF;
			set_ADCS;
			while(ADCF == 0);
		}
}
		
void READ_BANDGAP()
{
		UINT8 BandgapHigh,BandgapLow;
		double Bandgap_Value;
	
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
			
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
		double bgvalue;
		
		InitialUART0_Timer1(115200);
		READ_BANDGAP();														// Read 2 bytes band-gap value after UID .
		Enable_ADC_BandGap;												// Find in "Function_define.h" - "ADC INIT"
		ADC_Bypass();															// For Band-gap convert please bypass the first 3 times.

		clr_ADCF;
		set_ADCS;																	
    while(ADCF == 0);
		bgvalue = (ADCRH<<4) + ADCRL;
		VDD_Voltage = (0xFFF/bgvalue)*Bandgap_Voltage;
		printf ("\n Bandgap voltage = %e", Bandgap_Voltage); 
		printf ("\n VDD voltage = %e", VDD_Voltage); 
    while(1);
}


