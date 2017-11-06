#include <atmel_start.h>

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

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace with your application code */
	while (1) {
		gpio_set_pin_level(toggle1, true);
		for(int i=0;i<64;i++)
		{
			inTemp = in[i];
			outTemp = inTemp * a0 + z1;
			z1 = inTemp * a1 + z2 - b1 * outTemp;
			z2 = inTemp * a2 - b2 * outTemp;
			out[i] = outTemp;
		}
		gpio_set_pin_level(toggle1, false);		
	}
}
