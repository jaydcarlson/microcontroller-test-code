/**
 * \file
 *
 * \brief Configuration Change Protection
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

#include <assembler.h>

/*
	 * GNU and IAR use different calling conventions. Since this is
	 * a very small and simple function to begin with, it's easier
	 * to implement it twice than to deal with the differences
	 * within a single implementation.
	 */

	PUBLIC_FUNCTION(protected_write_io)

#if defined(__GNUC__)
  
#ifdef RAMPZ
	out     _SFR_IO_ADDR(RAMPZ), r1         // Clear bits 23:16 of Z
#endif
	movw    r30, r24                // Load addr into Z
	out     CCP, r22                // Start CCP handshake
	st      Z, r20                  // Write value to I/O register
	ret                             // Return to caller

#elif defined(__IAR_SYSTEMS_ASM__)

# if !defined(CONFIG_MEMORY_MODEL_TINY) && !defined(CONFIG_MEMORY_MODEL_SMALL) \
                && !defined(CONFIG_MEMORY_MODEL_LARGE)
#  define CONFIG_MEMORY_MODEL_SMALL
# endif
# if defined(CONFIG_MEMORY_MODEL_LARGE)
	ldi     r20, 0
	out     RAMPZ, r20              // Reset bits 23:16 of Z
	movw    r30, r16                // Load addr into Z
# elif defined(CONFIG_MEMORY_MODEL_TINY)
	ldi     r31, 0                  // Reset bits 8:15 of Z
	mov     r30, r16                // Load addr into Z
# else
	movw    r30, r16                // Load addr into Z
# endif
# if defined(CONFIG_MEMORY_MODEL_TINY)
	out     CCP, r17                // Start CCP handshake
	st      Z, r18                  // Write value to I/O register
# elif defined(CONFIG_MEMORY_MODEL_SMALL)
	out     CCP, r18                // Start CCP handshake
	st      Z, r19                  // Write value to I/O register
# elif defined(CONFIG_MEMORY_MODEL_LARGE)
	out     CCP, r19                // Start CCP handshake
	st      Z, r20                  // Write value to I/O register
# else
#  error Unknown memory model in use, no idea how registers should be accessed
# endif
        ret
#else
# error Unknown assembler
#endif

	END_FUNC(protected_write_io)
	END_FILE()

