/**
 * This is template for main module created by MCUXpresso Project Generator. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_flash.h"

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

/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitDebugConsole();
  flash_prefetch_speculation_status_t speculationStatus;
  speculationStatus.dataOption = kFLASH_prefetchSpeculationOptionEnable;
  speculationStatus.instructionOption = kFLASH_prefetchSpeculationOptionEnable;
  FLASH_PflashSetPrefetchSpeculation(&speculationStatus);

  /* Add your code here */
  gpio_pin_config_t config = { kGPIO_DigitalOutput, 0, };

GPIO_PinInit(GPIOA, 12, &config);
  while(1) { /* Infinite loop to avoid leaving the main function */
	int i;
	FGPIOA->PSOR = 4096; // set pin high

	for(i=0;i<64;i++)
	{
		inTemp = in[i];
		outTemp = inTemp * a0 + z1;
		z1 = inTemp * a1 + z2 - b1 * outTemp;
		z2 = inTemp * a2 - b2 * outTemp;
		out[i] = outTemp;
	}

	FGPIOA->PCOR = 4096; // set pin low
	}
}
