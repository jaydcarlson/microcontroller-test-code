#define MAIN_Fosc   27000000
#include <stc\stc8.h>
#include <stdint.h>

// let's not penalize the MCU by putting the data in XRAM
//#define BIQUAD_NUM_SAMPLES	25
//volatile int16_t in[BIQUAD_NUM_SAMPLES];
//volatile int16_t out[BIQUAD_NUM_SAMPLES];

// let's process the full 64-byte chunks
#define BIQUAD_NUM_SAMPLES	64
xdata volatile int16_t in[BIQUAD_NUM_SAMPLES];
xdata volatile int16_t out[BIQUAD_NUM_SAMPLES];

#define a0 (int16_t)16384
#define a1 (int16_t)-32768
#define a2 (int16_t)16384
#define b1 (int16_t)-25576
#define b2 (int16_t)10508

int16_t z1, z2;
int16_t outTemp;
int16_t inTemp;

void main()
{
	uint8_t i;
	
	while(1)
	{
		P00 = 1;
		for(i=0;i<BIQUAD_NUM_SAMPLES;i++)
		{
			inTemp = in[i];
			outTemp = inTemp * a0 + z1;
			z1 = inTemp * a1 + z2 - b1 * outTemp;
			z2 = inTemp * a2 - b2 * outTemp;
			out[i] = outTemp;
		}
		P00 = 0;
	}
}