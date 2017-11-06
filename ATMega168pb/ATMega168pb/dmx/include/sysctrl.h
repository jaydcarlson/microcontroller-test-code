

/**
 * \file
 *
 * \brief Sysctrl covers power management (PM), system clock (SYSCLK) and system reset functionality
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
 */

/**
 * \defgroup doc_driver_system_sysctrl System Control (PM, SYSCLK, SYSRST)
 * \ingroup doc_driver_system
 *
 * \section doc_driver_sysctrl_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#ifndef _SYSCTRL_H_INCLUDED
#define _SYSCTRL_H_INCLUDED

#include <compiler.h>
#include <protected_io.h>
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ICCAVR__) || defined(__DOXYGEN__)
#include <intrinsics.h>
//! Macro for issuing the sleep instruction.
#define sleep_enter() __sleep()

/**
 * \brief Enable sleep
 */
static inline void sleep_enable(void)
{
	SMCR |= (1 << SE);
}

/**
 * \brief Disable sleep
 */
static inline void sleep_disable(void)
{
	SMCR &= ~(1 << SE);
}

#elif defined(__GNUC__)
#include <avr/sleep.h>
#define sleep_enter() sleep_cpu()

#else
#error Unsupported compiler.
#endif

/**
 * \brief Set sleep mode to use when entering sleep state
 *
 * \param mode Sleep mode
 */
static inline void sleep_set_mode(uint8_t mode)
{
	SMCR = mode | (SMCR & ~((1 << SM0) | (1 << SM1) | (1 << SM2)));
}

/*
 * \brief Initialize sysctrl interface
 *
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialization status.
 */
static inline int8_t sysctrl_init()
{
	/* Set up system clock prescaler according to configuration */
	protected_write_io((void *)&CLKPR, 1 << CLKPCE, (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0));

	SMCR = (0 << SM2) | (0 << SM1) | (0 << SM0) | // Idle
	       (0 << SE);

	MCUCR = (0 << PUD);

	return 0;
}

#endif /* _SYSCTRL_H_INCLUDED */
