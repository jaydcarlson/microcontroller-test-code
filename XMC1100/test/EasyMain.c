/******************************************************************************
 * @file     EasyMain.c
 * @brief    Uses a system timer to toggle the  ports P0.5, P0.6, P1.5 and P1.6 with 200ms frequency.
 *			 LEDs that are connected to these ports will toggle respectively.
 * 			 In addition it uses the UART of USIC Channel 1 to send a message every 2s to a terminal
 *			 emulator. The communication settings are 57.6kbps/8N1
 *			 P1.3 is configured as input (RXD) and P1.2 is configured as output(TXD)
 *			 This project runs without modifications on the XMC1100 kit for ARDUINO
 * @version  V1.0
 * @date     20. February 2015
 * @note
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 ******************************************************************************
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon�s microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/

#include <string.h>

#include "XMC1100.h"
#include "GPIO.h"

// Ticks are generated every 100ms
#define TICKS_PER_SECOND 10UL
// Update LED status every 200ms
#define TICKS_LED_EVENT 2UL
// Update message 2s
#define TICKS_UART_EVENT 20UL

// UART baud rate constants for 57.8kbps @ MCLK=8MHz
#define FDR_STEP 590UL
#define BRG_PDIV 4UL
#define BRG_DCTQ 15UL
#define BRG_PCTQ 0UL
#include "xmc_uart.h"
void UART_Init();

int main(void)
{
	// Clock configuration
	SCU_GENERAL->PASSWD = 0x000000C0UL; // disable bit protection
	SCU_CLK->CLKCR = 0x3FF00400UL; // MCLK = 8MHz, PCLK = 8MHz
	while((SCU_CLK->CLKCR & SCU_CLK_CLKCR_VDDC2LOW_Msk));
	SCU_GENERAL->PASSWD = 0x000000C3UL; // enable bit protection
	SystemCoreClockUpdate();

	// Initialize and start UART
	XMC_UART_CH_CONFIG_t uartConfig = { .baudrate = 115200 };
	XMC_UART_CH_Init(USIC0_CH1, &uartConfig );
	char message[] = "hello, world!";
	char* c = message;
	while(*c != 0)
		XMC_UART_CH_Transmit(USIC0_CH1, *c++);

	// LEDs configuration (P1.2 and P1.3 are used for serial comm)
	P0_5_set_mode(OUTPUT_OD_GP);
	P0_6_set_mode(OUTPUT_OD_GP);
	P1_4_set_mode(OUTPUT_OD_GP);
	P1_5_set_mode(OUTPUT_OD_GP);

	// Turn ON all LEDs
	P0_5_reset();
	P0_6_reset();
	P1_4_reset();
	P1_5_reset();

	// System Timer initialization
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	while(1);
}

void UART_Init()
{
	// Disable clock gating to USIC0
	SCU_GENERAL->PASSWD = 0x000000C0UL; // disable bit protection
	SCU_CLK->CGATCLR0 |= SCU_CLK_CGATCLR0_USIC0_Msk;
	SCU_GENERAL->PASSWD = 0x000000C3UL; // enable bit protection

    /* Enable the module kernel clock and the module functionality  */
    USIC0_CH1->KSCFG |= USIC_CH_KSCFG_MODEN_Msk | USIC_CH_KSCFG_BPMODEN_Msk;

    /* fFD = fPB */
    /* FDR.DM = 02b (Fractional divider mode) */
    USIC0_CH1->FDR &= ~(USIC_CH_FDR_DM_Msk | USIC_CH_FDR_STEP_Msk);
    USIC0_CH1->FDR |= (0x02UL << USIC_CH_FDR_DM_Pos) | (FDR_STEP << USIC_CH_FDR_STEP_Pos);

    /* Configure baud rate generator */
    /* BAUDRATE = fCTQIN/(BRG.PCTQ x BRG.DCTQ) */
    /* CLKSEL = 0 (fPIN = fFD), CTQSEL = 00b (fCTQIN = fPDIV), PPPEN = 0 (fPPP=fPIN) */
    USIC0_CH0->BRG &= ~(USIC_CH_BRG_PCTQ_Msk | USIC_CH_BRG_DCTQ_Msk | USIC_CH_BRG_PDIV_Msk | USIC_CH_BRG_CLKSEL_Msk | USIC_CH_BRG_PPPEN_Msk);
    USIC0_CH1->BRG |= (BRG_PCTQ << USIC_CH_BRG_PCTQ_Pos) | (BRG_DCTQ << USIC_CH_BRG_DCTQ_Pos) | (BRG_PDIV << USIC_CH_BRG_PDIV_Pos);

    /* Configuration of USIC Shift Control */
    /* SCTR.FLE = 8 (Frame Length) */
    /* SCTR.WLE = 8 (Word Length) */
    /* SCTR.TRM = 1 (Transmission Mode) */
    /* SCTR.PDL = 1 (This bit defines the output level at the shift data output signal when no data is available for transmission) */
    USIC0_CH1->SCTR &= ~(USIC_CH_SCTR_TRM_Msk | USIC_CH_SCTR_FLE_Msk | USIC_CH_SCTR_WLE_Msk);
    USIC0_CH1->SCTR |= USIC_CH_SCTR_PDL_Msk | (0x01UL << USIC_CH_SCTR_TRM_Pos) | (0x07UL << USIC_CH_SCTR_FLE_Pos) | (0x07UL << USIC_CH_SCTR_WLE_Pos);

    /* Configuration of USIC Transmit Control/Status Register */
    /* TBUF.TDEN = 1 (TBUF Data Enable: A transmission of the data word in TBUF can be started if TDV = 1 */
    /* TBUF.TDSSM = 1 (Data Single Shot Mode: allow word-by-word data transmission which avoid sending the same data several times*/
    USIC0_CH1->TCSR &= ~(USIC_CH_TCSR_TDEN_Msk);
    USIC0_CH1->TCSR |= USIC_CH_TCSR_TDSSM_Msk | (0x01UL << USIC_CH_TCSR_TDEN_Pos);

    /* Configuration of Protocol Control Register */
    /* PCR.SMD = 1 (Sample Mode based on majority) */
    /* PCR.STPB = 0 (1x Stop bit) */
    /* PCR.SP = 5 (Sample Point) */
    /* PCR.PL = 0 (Pulse Length is equal to the bit length) */
    USIC0_CH1->PCR &= ~(USIC_CH_PCR_ASCMode_STPB_Msk | USIC_CH_PCR_ASCMode_SP_Msk | USIC_CH_PCR_ASCMode_PL_Msk);
    USIC0_CH1->PCR |= USIC_CH_PCR_ASCMode_SMD_Msk | (9 << USIC_CH_PCR_ASCMode_SP_Pos);

    /* Configure Transmit Buffer */
    /* Standard transmit buffer event is enabled */
    /* Define start entry of Transmit Data FIFO buffer DPTR = 0*/
    USIC0_CH1->TBCTR &= ~(USIC_CH_TBCTR_SIZE_Msk | USIC_CH_TBCTR_DPTR_Msk);

    /* Set Transmit Data Buffer to 64 */
    USIC0_CH1->TBCTR |= 0x06UL << USIC_CH_TBCTR_SIZE_Pos;

    /* Initialize UART_RX (DX0)*/
    /* P1.3 as input */
    P1_3_set_mode(INPUT);

    /* Select P1.3 as input for USIC DX0 */
    USIC0_CH1->DX0CR &= ~(USIC_CH_DX0CR_DSEL_Msk);

    /* Initialize UART_TX (DOUT)*/
    /* P1.2 as output controlled by ALT7 = U0C1.DOUT0 */
    P1_2_set_mode(OUTPUT_PP_AF7);

    /* Configuration of Channel Control Register */
    /* CCR.PM = 00 ( Disable parity generation) */
    /* CCR.MODE = 2 (ASC mode enabled. Note: 0 (USIC channel is disabled)) */
    USIC0_CH1->CCR &= ~(USIC_CH_CCR_PM_Msk | USIC_CH_CCR_MODE_Msk);
    USIC0_CH1->CCR |= 0x02UL << USIC_CH_CCR_MODE_Pos;


}

void SysTick_Handler(void)
{
	static uint32_t ticks_uart = 0;
	static uint32_t ticks_led = 0;
	static uint8_t led_group = 0;
	static uint8_t message = 0;
	static const char *messages[] = {
			"Visit www.infineon.com/XMC\r\n",
			"Visit www.infineonforums.com\r\n\r\n"
	};

	uint8_t i;

	// Update LED status
	ticks_led++;
	if (ticks_led == TICKS_LED_EVENT) {
		if (led_group) {
			P0_6_toggle();
			P1_4_toggle();
		}
		else {
			P0_5_toggle();
			P1_5_toggle();
		}

		led_group ^= 1;
		ticks_led = 0;
	}

	// Update UART message
	ticks_uart++;
	if (ticks_uart == TICKS_UART_EVENT) {
		for(i = 0; i < strlen(messages[message]); i++) {
			USIC0_CH1->IN[0] = messages[message][i];
		}
		message ^= 1;
		ticks_uart = 0;
	}

}
