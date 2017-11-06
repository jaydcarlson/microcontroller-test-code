/**
 * \file
 *
 * \brief PWM Basic driver example.
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

#include <atmel_start.h>
#include <pwm_basic_example.h>
#include <pwm_basic.h>
#include <atomic.h>

volatile uint16_t         PWM_0_isr_executed_counter = 0;
volatile PWM_0_register_t PWM_0_duty;

void PWM_0_pwm_handler_cb(void)
{
	PWM_0_duty++;
	// Output duty cycle on PWM CH0
	PWM_0_load_duty_cycle_ch0(PWM_0_duty);
	PWM_0_isr_executed_counter++;
}

uint8_t PWM_0_test_pwm_basic(void)
{

	// Enable pin output
	PWM_0_enable_output_ch0();

	// Set channel 0 duty cycle value register value to 0x3f
	PWM_0_load_duty_cycle_ch0(0x3f);

	// Set counter register value to 0
	PWM_0_load_counter(0);

	// Test IRQ mode

	ENABLE_INTERRUPTS();

	PWM_0_register_callback(PWM_0_pwm_handler_cb);

	// Wait for ISR to be executed 65000 times
	while (PWM_0_isr_executed_counter < 65000)
		;

	return 1;
}
