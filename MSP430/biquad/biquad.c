#include <msp430.h>				
#include <cs.h>
#include <stdint.h>
#include <pmm.h>
/**
 * biquad.c
 */
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

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer

    CS_initClockSignal(
        CS_FLLREF,
        CS_REFOCLK_SELECT,
        CS_CLOCK_DIVIDER_1
        );

    CS_initFLLSettle(
        16000,
        487
        );

    CS_initClockSignal(
        CS_MCLK,
        CS_DCOCLKDIV_SELECT,
        CS_CLOCK_DIVIDER_1
        );

	P1DIR |= 0x01;					// configure P1.0 as output

	PMM_unlockLPM5();

	volatile unsigned int i;		// volatile to prevent optimization

//    for(;;) {
//        P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR
//    }

	while(1)
	{
	    uint8_t i;
		P1OUT = 0x01;				// toggle P1.0
        for(i=0;i<64;i++)
        {
            inTemp = in[i];
            outTemp = inTemp * a0 + z1;
            z1 = inTemp * a1 + z2 - b1 * outTemp;
            z2 = inTemp * a2 - b2 * outTemp;
            out[i] = outTemp;
        }
        P1OUT = 0x00;               // toggle P1.0
	}
}
