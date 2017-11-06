/**
 * This is template for main module created by MCUXpresso Project Generator. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_flash.h"

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
  while(1) {
	  FGPIOA->PTOR = 4096;
  }
}
