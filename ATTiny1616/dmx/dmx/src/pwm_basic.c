/**
 * \file
 *
 * \brief PWM Basic driver implementation.
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

#include <pwm_basic.h>

pwm_irq_cb_t PWM_0_cb = NULL;

/**
 * \brief Initialize PWM
 */
int8_t PWM_0_init()
{

	TCA0.SINGLE.CMP0 = 127; /* Setting: 127 */

	TCA0.SINGLE.CMP1 = 127; /* Setting: 127 */

	TCA0.SINGLE.CMP2 = 127; /* Setting: 127 */

	// TCA0.SINGLE.CNT = 0; /* Count: 0 */

	TCA0.SINGLE.CTRLB = 0 << TCA_SINGLE_ALUPD_bp      /* Auto Lock Update: disabled */
	                    | 1 << TCA_SINGLE_CMP0EN_bp   /* Setting: enabled */
	                    | 1 << TCA_SINGLE_CMP1EN_bp   /* Setting: enabled */
	                    | 1 << TCA_SINGLE_CMP2EN_bp   /* Setting: enabled */
	                    | TCA_SINGLE_WGMODE_DSTOP_gc; /*  */

	// TCA0.SINGLE.CTRLC = 0 << TCA_SINGLE_CMP0OV_bp /* Setting: disabled */
	//		 | 0 << TCA_SINGLE_CMP1OV_bp /* Setting: disabled */
	//		 | 0 << TCA_SINGLE_CMP2OV_bp; /* Setting: disabled */

	// TCA0.SINGLE.DBGCTRL = 0 << TCA_SINGLE_DBGRUN_bp; /* Debug Run: disabled */

	// TCA0.SINGLE.EVCTRL = 0 << TCA_SINGLE_CNTEI_bp /* Count on Event Input: disabled */
	//		 | TCA_SINGLE_EVACT_POSEDGE_gc; /* Count on positive edge event */

	// TCA0.SINGLE.INTCTRL = 0 << TCA_SINGLE_CMP0_bp /* Compare 0 Interrupt: disabled */
	//		 | 0 << TCA_SINGLE_CMP1_bp /* Compare 1 Interrupt: disabled */
	//		 | 0 << TCA_SINGLE_CMP2_bp /* Compare 2 Interrupt: disabled */
	//		 | 0 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt Enable: disabled */

	TCA0.SINGLE.PER = 255; /* Top Value: 255 */

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc    /* System Clock */
	                    | 1 << TCA_SINGLE_ENABLE_bp; /* Module Enable: enabled */

	return 0;
}

void PWM_0_enable()
{
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void PWM_0_disable()
{
	TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
}

void PWM_0_enable_output_ch0()
{
	TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP0EN_bp);
}

void PWM_0_disable_output_ch0()
{
	TCA0.SINGLE.CTRLB &= (~1 << TCA_SINGLE_CMP0EN_bp);
}

void PWM_0_enable_output_ch1()
{
	TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP1EN_bp);
}

void PWM_0_disable_output_ch1()
{
	TCA0.SINGLE.CTRLB &= (~1 << TCA_SINGLE_CMP1EN_bp);
}

void PWM_0_enable_output_ch2()
{
	TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP2EN_bp);
}

void PWM_0_disable_output_ch2()
{
	TCA0.SINGLE.CTRLB &= (~1 << TCA_SINGLE_CMP2EN_bp);
}

void PWM_0_load_counter(PWM_0_register_t counter_value)
{
	TCA0.SINGLE.CNT = counter_value;
}

void PWM_0_load_top(PWM_0_register_t top_value)
{
	TCA0.SINGLE.PERBUF = top_value;
}

void PWM_0_load_duty_cycle_ch0(PWM_0_register_t duty_value)
{
	TCA0.SINGLE.CMP0BUF = duty_value;
}

void PWM_0_load_duty_cycle_ch1(PWM_0_register_t duty_value)
{
	TCA0.SINGLE.CMP1BUF = duty_value;
}

void PWM_0_load_duty_cycle_ch2(PWM_0_register_t duty_value)
{
	TCA0.SINGLE.CMP2BUF = duty_value;
}

void PWM_0_register_callback(pwm_irq_cb_t f)
{
	PWM_0_cb = f;
}

ISR(TCA0_OVF_vect)
{
	static volatile uint8_t callback_count = 0;

	// Clear the interrupt flag
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;

	// callback function - called every 0 passes
	if ((++callback_count >= PWM_0_INTERRUPT_CB_RATE) && (PWM_0_INTERRUPT_CB_RATE != 0)) {
		if (PWM_0_cb != NULL) {
			PWM_0_cb();
		}
	}
}
