/**
 * \file
 *
 * \brief Configuration Change Protection write functions
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
 * \defgroup doc_driver_system_ccp Configuration Change Protection
 * \ingroup doc_driver_system
 *
 * \section doc_driver_ccp_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#ifndef CPU_CCP_H
#define CPU_CCP_H

#include <compiler.h>
#include <protected_io.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Write to a CCP-protected 8-bit I/O register
 *
 * \param addr Address of the I/O register
 * \param value Value to be written
 *
 * \note Using IAR Embedded workbench, the choice of memory model has an impact
 *       on calling convention. The memory model is not visible to the
 *       preprocessor, so it must be defined in the Assembler preprocessor directives.
 */
static inline void ccp_write_io(void *addr, uint8_t value)
{
	protected_write_io(addr, CCP_IOREG_gc, value);
}

/** @} */

/**
 * \brief Write to CCP-protected 8-bit SPM register
 *
 * \param addr Address of the SPM register
 * \param value Value to be written
 *
 * \note Using IAR Embedded workbench, the choice of memory model has an impact
 *       on calling convention. The memory model is not visible to the
 *       preprocessor, so it must be defined in the Assembler preprocessor directives.
 */
static inline void ccp_write_spm(void *addr, uint8_t value)
{
	protected_write_io(addr, CCP_SPM_gc, value);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* CPU_CCP_H */
