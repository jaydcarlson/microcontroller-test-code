//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8LB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$
#define NUM_SAMPLES	64
xdata volatile int16_t in[NUM_SAMPLES];
xdata volatile int16_t out[NUM_SAMPLES];

#define a0 (int16_t)16384
#define a1 (int16_t)-32768
#define a2 (int16_t)16384
#define b1 (int16_t)-25576
#define b2 (int16_t)10508

int16_t z1, z2;
int16_t outTemp;
int16_t inTemp;
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {
	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	while (1) {
		uint8_t i;
		P0_B0 = 1;
		for (i = 0; i < NUM_SAMPLES; i++) {
			inTemp = in[i];
			outTemp = inTemp * a0 + z1;
			z1 = inTemp * a1 + z2 - b1 * outTemp;
			z2 = inTemp * a2 - b2 * outTemp;
			out[i] = outTemp;
		}
		P0_B0 = 0;
// $[Generated Run-time code]
// [Generated Run-time code]$
	}
}
