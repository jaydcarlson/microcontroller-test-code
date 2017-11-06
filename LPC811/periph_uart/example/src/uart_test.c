/*
 * @brief UART test using SysTick interrupt
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2015
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define TICKRATE_HZ				100
#define	EV_TICK_CT_DISPLAY		0x01

#define	LED_RED					0
#define	LED_GREEN				1
#define	LED_BLUE				2
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void ansi_clr_screen(void)
{
	Board_UARTPutSTR("\x1B[2J");												// clear screen
	Board_UARTPutSTR("\x1B[0m");												// color mode reset
	Board_UARTPutSTR("\x1B[1;1H");												// set position to 1,1
}

static void Board_LED_clear(void)
{
	Board_LED_Set(LED_RED, false);
	Board_LED_Set(LED_GREEN, false);
	Board_LED_Set(LED_BLUE, false);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
static uint32_t sys_event=0;
static uint32_t tick_ct=0;
static char		out_str[16];
void SysTick_Handler(void)
{
	tick_ct += 1;
	if ((tick_ct % 50) == 0)	Board_LED_Toggle(LED_RED);
	if ((tick_ct % 100) == 0)	Board_LED_Toggle(LED_GREEN);
	if ((tick_ct % 200) == 0)	Board_LED_Toggle(LED_BLUE);

	if ((tick_ct % 100) == 0)	sys_event |= EV_TICK_CT_DISPLAY;
}

/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	Board_LED_clear();
	ansi_clr_screen();
	Board_UARTPutSTR("UART demo:\n");
	Board_UARTPutSTR("build date: " __DATE__ " build time: " __TIME__ "\n");

	/* Enable SysTick Timer */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	/* Loop forever */
	while (1) {
		__WFI();
		if (sys_event & EV_TICK_CT_DISPLAY) {
			sys_event &= ~EV_TICK_CT_DISPLAY;
			Board_UARTPutSTR("system tick: ");
			Board_itoa(tick_ct, out_str, 10);
			Board_UARTPutSTR(out_str);
			Board_UARTPutChar(0x0d);
		}
	}
}
