

/**
 * \file
 *
 * \brief System
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
 */

/**
 * \addtogroup doc_driver_system
 *
 * \section doc_driver_system_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#ifndef _SYSTEM_INCLUDED_
#define _SYSTEM_INCLUDED_

#include "port.h"
#include <protected_io.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MCU_RESET_CAUSE_POR (1 << PORF)
#define MCU_RESET_CAUSE_EXT (1 << EXTRF)
#define MCU_RESET_CAUSE_BOR (1 << BORF)
#define MCU_RESET_CAUSE_WDT (1 << WDRF)

static inline void mcu_init(void)
{
	/* On AVR devices all peripherals are enabled from power on reset, this
	 * disables all peripherals to save power. Driver shall enable
	 * peripheral if used */

	PRR = (1 << PRSPI) | (1 << PRTIM2) | (1 << PRTIM0) | (1 << PRTIM1) | (1 << PRTWI) | (1 << PRUSART0) | (1 << PRADC);

	/* Set all pins to low power mode */
	PORTB_set_port_dir(0xff, PORT_DIR_OFF);
	PORTC_set_port_dir(0x7f, PORT_DIR_OFF);
	PORTD_set_port_dir(0xff, PORT_DIR_OFF);
	PORTE_set_port_dir(0x0f, PORT_DIR_OFF);
}

#ifdef __cplusplus
}
#endif

#endif
