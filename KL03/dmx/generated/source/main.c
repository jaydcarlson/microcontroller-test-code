/**
 * This is template for main module created by MCUXpresso Project Generator. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_lpuart.h"
#include "fsl_tpm.h"
#include "fsl_smc.h"
#include "fsl_gpio.h"

uint8_t data[513];
uint8_t address = 1;
int32_t currentIndex = -1;

void LPUART0_IRQHandler(void)
{
	FGPIO_WritePinOutput(FGPIOB, 10, true); // used for interrupt checking
	uint32_t flags = LPUART_GetStatusFlags(LPUART0);
	if(flags & kLPUART_FramingErrorFlag)
	{
		currentIndex = 0;
	}

	if(flags & kLPUART_RxDataRegFullFlag)
	{
		uint8_t temp = LPUART_ReadByte(LPUART0);
		if(currentIndex != -1)
			data[currentIndex++] = temp;
	}

	if(currentIndex > 512)
	{
		TPM_UpdatePwmDutycycle(TPM0, kTPM_Chnl_0, kTPM_EdgeAlignedPwm, (data[address + 1] * 100) / 255);
		TPM_UpdatePwmDutycycle(TPM0, kTPM_Chnl_1, kTPM_EdgeAlignedPwm, (data[address + 2] * 100) / 255);
		TPM_UpdatePwmDutycycle(TPM1, kTPM_Chnl_0, kTPM_EdgeAlignedPwm, (data[address + 3] * 100) / 255);
		currentIndex = -1; // reset to idle
	}

	LPUART_ClearStatusFlags(LPUART0, flags);
	FGPIO_WritePinOutput(FGPIOB, 10, false);
}

const gpio_pin_config_t out = {
		.pinDirection = kGPIO_DigitalOutput
};

int main(void) {
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	GPIO_PinInit(GPIOB, 10, &out); // used for interrupt checking

	// Timer Config
	tpm_config_t tpmInfo;
	TPM_GetDefaultConfig(&tpmInfo);
	TPM_Init(TPM0, &tpmInfo);
	TPM_Init(TPM1, &tpmInfo);

	uint8_t updatedDutycycle = 0U;
	tpm_chnl_pwm_signal_param_t tpmParam[2];

	tpmParam[0].chnlNumber = kTPM_Chnl_0;
	tpmParam[0].level = kTPM_LowTrue;
	tpmParam[0].dutyCyclePercent = 0U;

	tpmParam[1].chnlNumber = kTPM_Chnl_1;
	tpmParam[1].level = kTPM_LowTrue;
	tpmParam[1].dutyCyclePercent = 0U;

	TPM_SetupPwm(TPM0, tpmParam, 2, kTPM_EdgeAlignedPwm, 100, 1000000);
	TPM_SetupPwm(TPM1, tpmParam, 1, kTPM_EdgeAlignedPwm, 100, 1000000);
	TPM_StartTimer(TPM0, kTPM_SystemClock);
	TPM_StartTimer(TPM1, kTPM_SystemClock);

	lpuart_config_t user_config;
	LPUART_GetDefaultConfig(&user_config);
	user_config.baudRate_Bps = 250000;
	user_config.enableRx = true;
	user_config.enableTx = true;
	LPUART_Init(LPUART0,&user_config, 1000000);

	LPUART_EnableInterrupts(LPUART0,
			kLPUART_RxDataRegFullInterruptEnable|
			kLPUART_FramingErrorInterruptEnable|
			kLPUART_RxOverrunInterruptEnable);

	EnableIRQ(LPUART0_IRQn);

	for(;;) {
//		SMC_PreEnterWaitModes();
//		SMC_SetPowerModeWait(SMC);
//		SMC_PostExitStopModes();
	}
}
