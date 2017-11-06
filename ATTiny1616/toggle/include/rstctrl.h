/**
 * \file
 *
 * \brief RSTCTRL
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

/**
 * \defgroup doc_driver_system_rstctrl Reset Controller
 * \ingroup doc_driver_system
 *
 * \section doc_driver_rstctrl_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#ifndef _RSTCTRL_INCLUDED_
#define _RSTCTRL_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <ccp.h>

static inline void RSTCTRL_reset(void)
{
	/* SWRR is protectd with CCP */
	ccp_write_io((void *)&RSTCTRL.SWRR, 0x1);
}

static inline uint8_t RSTCTRL_get_reset_cause(void)
{
	return RSTCTRL.RSTFR;
}

static inline void RSTCTRL_clear_reset_cause(void)
{
	RSTCTRL.RSTFR
	    = RSTCTRL_UPDIRF_bm | RSTCTRL_SWRF_bm | RSTCTRL_WDRF_bm | RSTCTRL_EXTRF_bm | RSTCTRL_BORF_bm | RSTCTRL_PORF_bm;
}

#ifdef __cplusplus
}
#endif

#endif
