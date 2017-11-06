/**
 * \file
 *
 * \brief PWM Normal mode (i.e. non-split) declaration.
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
 * \defgroup doc_driver_pwm_basic PWM Basic Driver
 * \ingroup doc_driver_pwm
 *
 * \section doc_driver_pwm_normal_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#ifndef _PWM_BASIC_H_INCLUDED
#define _PWM_BASIC_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Function pointer to callback function called by IRQ.
    NULL=default value: No callback function is to be used.
*/
typedef void (*pwm_irq_cb_t)(void);

#define PWM_0_INTERRUPT_CB_RATE 0

/** The datatype matching the bitwidth of the PWM hardware */
typedef uint16_t PWM_0_register_t;

/**
 * \brief Initialize PWM
 * If module is configured to disabled state, the clock to the PWM is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 */
int8_t PWM_0_init(void);

/**
 * \brief Enable PWM_0
 * 1. If supported by the clock system, enables the clock to the PWM
 * 2. Enables the PWM module by setting the enable-bit in the PWM control register
 *
 * \return Nothing
 */
void PWM_0_enable();

/**
 * \brief Disable PWM_0
 * 1. Disables the PWM module by clearing the enable-bit in the PWM control register
 * 2. If supported by the clock system, disables the clock to the PWM
 *
 * \return Nothing
 */
void PWM_0_disable();

/**
 * \brief Enable PWM output on channel 0
 *
 * \return Nothing
 */
void PWM_0_enable_output_ch0();

/**
 * \brief Disable PWM output on channel 0
 *
 * \return Nothing
 */
void PWM_0_disable_output_ch0();

/**
 * \brief Enable PWM output on channel 1
 *
 * \return Nothing
 */
void PWM_0_enable_output_ch1();

/**
 * \brief Disable PWM output on channel 1
 *
 * \return Nothing
 */
void PWM_0_disable_output_ch1();

/**
 * \brief Enable PWM output on channel 2
 *
 * \return Nothing
 */
void PWM_0_enable_output_ch2();

/**
 * \brief Disable PWM output on channel 2
 *
 * \return Nothing
 */
void PWM_0_disable_output_ch2();

/**
 * \brief Load COUNTER register in PWM_0
 *
 * \param[in] counter_value The value to load into COUNTER
 *
 * \return Nothing
 */
void PWM_0_load_counter(PWM_0_register_t counter_value);

/**
 * \brief Load TOP register in PWM_0.
 * The physical register may different names, depending on the hardware and module mode.
 *
 * \param[in] counter_value The value to load into TOP.
 *
 * \return Nothing
 */
void PWM_0_load_top(PWM_0_register_t top_value);

/**
 * \brief Load duty cycle register in for channel 0.
 * The physical register may have different names, depending on the hardware.
 * This is not the duty cycle as percentage of the whole period, but the actual
 * counter compare value.
 *
 * \param[in] counter_value The value to load into the duty cycle register.
 *
 * \return Nothing
 */
void PWM_0_load_duty_cycle_ch0(PWM_0_register_t duty_value);

/**
 * \brief Load duty cycle register in for channel 1.
 * The physical register may have different names, depending on the hardware.
 * This is not the duty cycle as percentage of the whole period, but the actual
 * counter compare value.
 *
 * \param[in] counter_value The value to load into the duty cycle register.
 *
 * \return Nothing
 */
void PWM_0_load_duty_cycle_ch1(PWM_0_register_t duty_value);

/**
 * \brief Load duty cycle register in for channel 2.
 * The physical register may have different names, depending on the hardware.
 * This is not the duty cycle as percentage of the whole period, but the actual
 * counter compare value.
 *
 * \param[in] counter_value The value to load into the duty cycle register.
 *
 * \return Nothing
 */
void PWM_0_load_duty_cycle_ch2(PWM_0_register_t duty_value);

/**
 * \brief Register a callback function to be called at the end of the overflow ISR.
 *
 * \param[in] f Pointer to function to be called
 *
 * \return Nothing.
 */
void PWM_0_register_callback(pwm_irq_cb_t f);

#ifdef __cplusplus
}
#endif

#endif /* _PWM_BASIC_H_INCLUDED */
