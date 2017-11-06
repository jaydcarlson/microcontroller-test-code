/*
===============================================================================
 Name        : biquad.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

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

int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    Chip_GPIO_Init(LPC_GPIO_PORT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 0);
    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 0);
		for(int i=0;i<64;i++)
		{
			inTemp = in[i];
			outTemp = inTemp * a0 + z1;
			z1 = inTemp * a1 + z2 - b1 * outTemp;
			z2 = inTemp * a2 - b2 * outTemp;
			out[i] = outTemp;
		}
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 0);

    }
    return 0 ;
}
