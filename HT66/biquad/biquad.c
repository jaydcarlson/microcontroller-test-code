#include "HT66F0185.h"
#include "stdint.h"

volatile int16_t in[25];
volatile int16_t out[25];

const int16_t a0 = 16384;
const int16_t a1 = -32768;
const int16_t a2 = 16384;
const int16_t b1 = -25576;
const int16_t b2 = 10508;

int16_t z1, z2;
int16_t outTemp;
int16_t inTemp;

void main()
{
	uint8_t i;
	_wdtc =0b10101000;
	_pac1 = 0;

	while(1) {
		_pa = 2;
		for(i=0;i<25;i++)
		{
			inTemp = in[i];
			outTemp = inTemp * a0 + z1;
			z1 = inTemp * a1 + z2 - b1 * outTemp;
			z2 = inTemp * a2 - b2 * outTemp;
			out[i] = outTemp;
		}
		
		_pa = 0;
	}

}