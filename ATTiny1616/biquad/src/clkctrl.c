/**
 * \file
 *
 * \brief CLKCTRL related functionality implementation.
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

#include <clkctrl.h>
#include <ccp.h>
/**
 * \brief Initialize clkctrl interface
 */
int8_t CLKCTRL_init()
{

	// ccp_write_io((void*)&(CLKCTRL.OSC32KCTRLA),0 << CLKCTRL_RUNSTDBY_bp /* Run standby: disabled */);

	// ccp_write_io((void*)&(CLKCTRL.XOSC32KCTRLA),CLKCTRL_CSUT_1K_gc /* 1k cycles */
	//		 | 0 << CLKCTRL_ENABLE_bp /* Enable: disabled */
	//		 | 0 << CLKCTRL_RUNSTDBY_bp /* Run standby: disabled */
	//		 | 0 << CLKCTRL_SEL_bp /* Select: disabled */);

	// ccp_write_io((void*)&(CLKCTRL.OSC20MCTRLA),0 << CLKCTRL_RUNSTDBY_bp /* Run standby: disabled */);

	ccp_write_io((void *)&(CLKCTRL.MCLKCTRLB),
	             CLKCTRL_PDIV_2X_gc /* 2 */
	                 | 1 << CLKCTRL_PEN_bp /* Prescaler enable: enabled */);

	// ccp_write_io((void*)&(CLKCTRL.MCLKCTRLA),CLKCTRL_CLKSEL_OSC20M_gc /* 20MHz Internal Oscillator (OSC20M) */
	//		 | 0 << CLKCTRL_CLKOUT_bp /* System clock out: disabled */);

	// ccp_write_io((void*)&(CLKCTRL.MCLKLOCK),0 << CLKCTRL_LOCKEN_bp /* lock enable: disabled */);

	return 0;
}
