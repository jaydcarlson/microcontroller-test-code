#include "M051Series.h"

#define BIQUAD_NUM_SAMPLES	64
volatile int16_t in[BIQUAD_NUM_SAMPLES];
volatile int16_t out[BIQUAD_NUM_SAMPLES];

const int16_t a0 = 16384;
const int16_t a1 = -32768;
const int16_t a2 = 16384;
const int16_t b1 = -25576;
const int16_t b2 = 10508;

int16_t z1, z2;
int16_t outTemp;
int16_t inTemp;

int main()
{
    SYS_UnlockReg();
    CLK_SetCoreClock(50000000U);
    GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);

    while(1)
	{
		P00 = 1;
		for(int i=0;i<BIQUAD_NUM_SAMPLES;i++)
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
