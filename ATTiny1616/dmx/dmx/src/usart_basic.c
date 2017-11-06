/**
 * \file
 *
 * \brief USART basic driver.
 *
 *
 * Copyright (C) 2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 *
 */
#include <compiler.h>
#include <clock_config.h>
#include <usart_basic.h>
#include <atomic.h>

int8_t USART_0_init()
{

	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(250000); /* set baud rate register */

	// USART0.CTRLA = 0 << USART_ABEIE_bp /* Auto-baud Error Interrupt Enable: disabled */
	//		 | 0 << USART_DREIE_bp /* Data Register Empty Interrupt Enable: disabled */
	//		 | 0 << USART_LBME_bp /* Loop-back Mode Enable: disabled */
	//		 | USART_RS485_OFF_gc /* RS485 Mode disabled */
	//		 | 0 << USART_RXCIE_bp /* Receive Complete Interrupt Enable: disabled */
	//		 | 0 << USART_RXSIE_bp /* Receiver Start Frame Interrupt Enable: disabled */
	//		 | 0 << USART_TXCIE_bp; /* Transmit Complete Interrupt Enable: disabled */

	USART0.CTRLB = 0 << USART_MPCM_bp       /* Multi-processor Communication Mode: disabled */
	               | 0 << USART_ODME_bp     /* Open Drain Mode Enable: disabled */
	               | 1 << USART_RXEN_bp     /* Reciever enable: enabled */
	               | USART_RXMODE_NORMAL_gc /* Normal mode */
	               | 0 << USART_SFDEN_bp    /* Start Frame Detection Enable: disabled */
	               | 1 << USART_TXEN_bp;    /* Transmitter Enable: enabled */

	// USART0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc /* Asynchronous Mode */
	//		 | USART_CHSIZE_8BIT_gc /* Character size: 8 bit */
	//		 | USART_PMODE_DISABLED_gc /* No Parity */
	//		 | USART_SBMODE_1BIT_gc; /* 1 stop bit */

	// USART0.DBGCTRL = 0 << USART_ABMBP_bp /* Autobaud majority voter bypass: disabled */
	//		 | 0 << USART_DBGRUN_bp; /* Debug Run: disabled */

	// USART0.EVCTRL = 0 << USART_IREI_bp; /* IrDA Event Input Enable: disabled */

	// USART0.RXPLCTRL = 0 << USART_RXPL_gp; /* Receiver Pulse Length: 0 */

	// USART0.TXPLCTRL = 0 << USART_TXPL_gp; /* Transmit pulse length: 0 */

	return 0;
}

void USART_0_enable()
{
	USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART_0_enable_rx()
{
	USART0.CTRLB |= USART_RXEN_bm;
}

void USART_0_enable_tx()
{
	USART0.CTRLB |= USART_TXEN_bm;
}

void USART_0_disable()
{
	USART0.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

bool USART_0_is_tx_ready()
{
	return (USART0.STATUS & USART_DREIF_bm);
}

bool USART_0_is_rx_ready()
{
	return (USART0.STATUS & USART_RXCIF_bm);
}

bool USART_0_is_tx_busy()
{
	return (!(USART0.STATUS & USART_TXCIF_bm));
}

uint8_t USART_0_read()
{
	while (!(USART0.STATUS & USART_RXCIF_bm))
		;
	return USART0.RXDATAL;
}

void USART_0_write(const uint8_t data)
{
	while (!(USART0.STATUS & USART_DREIF_bm))
		;
	USART0.TXDATAL = data;
}
