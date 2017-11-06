/*
===============================================================================
 Name        : dmx.c
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

uint8_t data[512];
int16_t idx = -1;
uint8_t address = 1;

void UART0_IRQHandler(void)
{
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 1);
	if(Chip_UART_GetStatus(LPC_USART0) & UART_STAT_FRM_ERRINT)
	{
		idx = 0;

		Chip_UART_ClearStatus(LPC_USART0, UART_STAT_FRM_ERRINT);
	}

	while ((Chip_UART_GetStatus(LPC_USART0) & UART_STAT_RXRDY) != 0) {
		uint8_t ch = Chip_UART_ReadByte(LPC_USART0);

		if(idx >= 0)
		{
			data[idx++] = ch;
		}

		if(idx > 512)
		{
			Chip_SCTPWM_SetDutyCycle(LPC_SCT, 1, 255 - data[address + 1]);
			Chip_SCTPWM_SetDutyCycle(LPC_SCT, 2, 255 - data[address + 2]);
			Chip_SCTPWM_SetDutyCycle(LPC_SCT, 3, 255 - data[address + 3]);
			idx = -1;
		}
	}
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 1);
}

int main(void) {
    SystemCoreClockUpdate();

	// pin muxing
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_SWM_MovablePinAssign(SWM_CTOUT_1_O, 7);
	Chip_SWM_MovablePinAssign(SWM_CTOUT_2_O, 8);
	Chip_SWM_MovablePinAssign(SWM_CTOUT_3_O, 9);
	Chip_SWM_DisableFixedPin(SWM_FIXED_ACMP_I1);
	Chip_SWM_MovablePinAssign(SWM_U0_RXD_I, 0);


    Chip_GPIO_Init(LPC_GPIO_PORT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 1);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 13);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 12);
//    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 6);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 5);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 4);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 3);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 2);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 11);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 10);

    // PWM
	Chip_SCTPWM_Init(LPC_SCT);
	Chip_SCTPWM_SetRate(LPC_SCT, 1000);

	Chip_SCTPWM_SetOutPin(LPC_SCT, 1, 1); // SCT1 -> CTOUT_1
	Chip_SCTPWM_SetOutPin(LPC_SCT, 2, 2); // SCT2 -> CTOUT_2
	Chip_SCTPWM_SetOutPin(LPC_SCT, 3, 3); // SCT3 -> CTOUT_3

	Chip_SCTPWM_SetDutyCycle(LPC_SCT, 1, 250);
	Chip_SCTPWM_SetDutyCycle(LPC_SCT, 2, 250);
	Chip_SCTPWM_SetDutyCycle(LPC_SCT, 3, 250);

	Chip_SCT_SetMatchReload(LPC_SCT, SCT_MATCH_0, 255);

	Chip_SCT_Config(LPC_SCT, SCT_CONFIG_16BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_L);

	Chip_SCTPWM_Start(LPC_SCT);

	// UART
	Chip_UART_Init(LPC_USART0);

	Chip_UART_ConfigData(LPC_USART0, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
	Chip_Clock_SetUSARTNBaseClockRate((250000 * 16), true);
	Chip_UART_SetBaud(LPC_USART0, 250000);
	Chip_UART_Enable(LPC_USART0);
	Chip_UART_IntEnable(LPC_USART0, UART_INTEN_RXRDY);

	NVIC_EnableIRQ(UART0_IRQn);

    while(1) {
//    	__WFI();
    }

    return 0 ;
}
