/*
 * main.c
 *
 *  Created on: 2017 Aug 05 19:12:05
 *  Author: JayLocal
 */
#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

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


/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
// __attribute__ ((section (".ram_code")))
int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
	for (int i = 0; i < NUM_SAMPLES; i++) {
		inTemp = in[i];
		outTemp = inTemp * a0 + z1;
		z1 = inTemp * a1 + z2 - b1 * outTemp;
		z2 = inTemp * a2 - b2 * outTemp;
		out[i] = outTemp;
	}
	DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
  }
}
