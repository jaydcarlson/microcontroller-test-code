/**
 * \file
 *
 * \brief USART init driver.
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

#include <usart.h>
#include "clock_config.h"

/**
 * \brief Initialize usart interface
 */
int8_t USART_0_init()
{

	// Module is in UART mode

	/* Enable USART0 */
	PRR &= ~(1 << PRUSART0);

#define BAUD 250000

#include <utils/setbaud.h>

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	UCSR0A = USE_2X << U2X0 /*  */
	         | 0 << MPCM0;  /* Multi-processor Communication Mode: disabled */

	UCSR0B = 1 << RXCIE0    /* RX Complete Interrupt Enable: enabled */
	         | 0 << TXCIE0  /* TX Complete Interrupt Enable: disabled */
	         | 0 << UDRIE0  /* USART Data Register Empty Interupt Enable: disabled */
	         | 1 << RXEN0   /* Receiver Enable: enabled */
	         | 0 << TXEN0   /* Transmitter Enable: disabled */
	         | 0 << UCSZ02; /*  */

	// UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) /*  */
	//		 | (0 << UPM01) | (0 << UPM00) /* Disabled */
	//		 | 0 << USBS0 /* USART Stop Bit Select: disabled */
	//		 | (1 << UCSZ01) | (1 << UCSZ00); /* 8-bit */

	// UCSR0D = 0 << RXSIE /* USART RX Start Interrupt Enable: disabled */
	//		 | 0 << SFDE; /* Start Frame Detection Enable: disabled */

	return 0;
}
