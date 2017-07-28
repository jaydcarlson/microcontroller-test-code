#include <stdio.h>
#include "N76E003.h"
#include "Define.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"


double  Bandgap_Value,Bandgap_Voltage;

void READ_BANDGAP()
{
		UINT8 BandgapHigh,BandgapLow;
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
		Bandgap_Voltage = 3072/(0x1000/Bandgap_Value);
}

void main(void)
{

	READ_BANDGAP();

	while(1);

}