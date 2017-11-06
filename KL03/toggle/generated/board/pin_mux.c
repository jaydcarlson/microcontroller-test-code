/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MKL03Z32xxx4
package_id: MKL03Z32VFK4
mcu_data: ksdk2_0
processor_version: 2.0.0
pin_labels:
- {pin_num: '20', pin_signal: ADC0_SE0/CMP0_IN0/PTA12/IRQ_13/LPTMR0_ALT2/TPM1_CH0/TPM_CLKIN0/CLKOUT, label: led, identifier: led}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '20', peripheral: GPIOA, signal: 'GPIO, 12', pin_signal: ADC0_SE0/CMP0_IN0/PTA12/IRQ_13/LPTMR0_ALT2/TPM1_CH0/TPM_CLKIN0/CLKOUT, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN12_IDX, kPORT_MuxAsGpio);         /* PORTA12 (pin 20) is configured as PTA12 */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
