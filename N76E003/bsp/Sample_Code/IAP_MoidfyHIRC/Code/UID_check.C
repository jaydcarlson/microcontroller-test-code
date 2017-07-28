#include <stdio.h>
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

sfr RCTRIM0		= 0x84;
sfr RCTRIM1		= 0x85;	


UINT8 hircmap0,hircmap1;
UINT16 trimvalue16bit;

void MODIFY_HIRC_VLAUE(void)
{
		set_IAPEN;
		IAPAL = 0x30;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPGO;
		hircmap0 = IAPFD;
		IAPAL = 0x31;
    IAPAH = 0x00;
    set_IAPGO;
		hircmap1 = IAPFD;
		clr_IAPEN;
		trimvalue16bit = ((hircmap0<<1)+(hircmap1&0x01));
		trimvalue16bit = trimvalue16bit - 15;
		hircmap1 = trimvalue16bit&0x01;
		hircmap0 = trimvalue16bit>>1;
		TA=0XAA;
		TA=0X55;
		RCTRIM0 = hircmap0;
		TA=0XAA;
		TA=0X55;
		RCTRIM1 = hircmap1;
}

void main(void)
{
	CKDIV = 0X00;
	P11_PushPull_Mode;
	MODIFY_HIRC_VLAUE();
	CKDIV = 0x50;
	set_CLOEN;
	while(1);
	

}