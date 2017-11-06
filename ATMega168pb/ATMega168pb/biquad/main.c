/*
 * biquad.c
 *
 * Created: 9/12/2017 7:11:34 PM
 * Author : JayLocal
 */ 

#include <avr/io.h>

#define NUM_SAMPLES	64

volatile int16_t in[NUM_SAMPLES];
volatile int16_t out[NUM_SAMPLES];

const int16_t a0 = 16384;
const int16_t a1 = -32768;
const int16_t a2 = 16384;
const int16_t b1 = -25576;
const int16_t b2 = 10508;

int16_t z1, z2;
int16_t outTemp;
int16_t inTemp;

int main(void)
{
	DDRB |= 1;
	while (1)
	{
		uint8_t i;
		PORTB = 1;
		for (i = 0; i < NUM_SAMPLES; i++) {
			inTemp = in[i];
			outTemp = inTemp * a0 + z1;
			z1 = inTemp * a1 + z2 - b1 * outTemp;
			z2 = inTemp * a2 - b2 * outTemp;
			out[i] = outTemp;
		}
		PORTB = 0;
	}
}

