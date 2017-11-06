#include "c87.h"
#include "Lc87f1m.sfr"


typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t ;
typedef int int16_t;

volatile int16_t in[64];
volatile int16_t out[64];

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
   int i;
    _P0DDR = 0x01;
   _OCR = 0x90; // enable main clock and divide-by-1
   while(1) {
	_P0 = 1;
	for(i=0;i<64;i++)
	{
		inTemp = in[i];
		outTemp = inTemp * a0 + z1;
		z1 = inTemp * a1 + z2 - b1 * outTemp;
		z2 = inTemp * a2 - b2 * outTemp;
		out[i] = outTemp;
	}
	_P0 = 0;
   }	
}