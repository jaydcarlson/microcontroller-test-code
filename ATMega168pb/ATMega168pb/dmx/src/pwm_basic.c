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

	/* Enable TC0 */
	PRR &= ~(1 << PRTIM0);

	TCCR0A = (1 << COM0A1) | (1 << COM0A0)   /* Set OCA on up-couting, clear OCA on down-counting */
	         | (1 << COM0B1) | (1 << COM0B0) /* Set OCB on up-couting, clear OCB on down-counting */
	         | (0 << WGM01) | (1 << WGM00);  /* TC8 Mode 1 Phase Correct */

	TCCR0B = 0                                          /* TC8 Mode 1 Phase Correct */
	         | (0 << CS02) | (1 << CS01) | (0 << CS00); /* IO clock divided by 8 */

	// TIMSK0 = 0 << OCIE0B /* Output Compare B Match Interrupt Enable: disabled */
	//		 | 0 << OCIE0A /* Output Compare A Match Interrupt Enable: disabled */
	//		 | 0 << TOIE0; /* Overflow Interrupt Enable: disabled */

	OCR0A = 127; /* Output compare A: 127 */

	OCR0B = 127; /* Output compare B: 127 */

	return 0;
}

void PWM_0_enable()
{
}

void PWM_0_disable()
{
}

void PWM_0_enable_output_ch0()
{

	TCCR0A |= ((1 << COM0A1) | (1 << COM0A0));
}

void PWM_0_disable_output_ch0()
{

	TCCR0A &= ~((0 << COM0A1) | (0 << COM0A0));
}

void PWM_0_enable_output_ch1()
{

	TCCR0A |= ((1 << COM0B1) | (1 << COM0B0));
}

void PWM_0_disable_output_ch1()
{

	TCCR0A &= ~((0 << COM0B1) | (0 << COM0B0));
}

void PWM_0_load_counter(PWM_0_register_t counter_value)
{
	TCNT0 = counter_value;
}

void PWM_0_load_duty_cycle_ch0(PWM_0_register_t duty_value)
{
	OCR0A = duty_value;
}

void PWM_0_load_duty_cycle_ch1(PWM_0_register_t duty_value)
{
	OCR0B = duty_value;
}

void PWM_0_register_callback(pwm_irq_cb_t f)
{
	PWM_0_cb = f;
}

ISR(TIMER0_OVF_vect)
{
	static volatile uint8_t callback_count = 0;

	// Clear the interrupt flag
	TIFR0 |= (1 << TOV0);

	// callback function - called every 0 passes
	if ((++callback_count >= PWM_0_INTERRUPT_CB_RATE) && (PWM_0_INTERRUPT_CB_RATE != 0)) {
		if (PWM_0_cb != NULL) {
			PWM_0_cb();
		}
	}
}

pwm_irq_cb_t PWM_1_cb = NULL;

/**
 * \brief Initialize PWM
 */
int8_t PWM_1_init()
{

	/* Enable TC2 */
	PRR &= ~(1 << PRTIM2);

	TCCR2A = (1 << COM2A1) | (1 << COM2A0)   /* Set OCA on up-couting, clear OCA on down-counting */
	         | (0 << COM2B1) | (0 << COM2B0) /* Normal port operation, OCB disconnected */
	         | (0 << WGM21) | (1 << WGM20);  /* TC8 Mode 1 Phase Correct */

	TCCR2B = 0                                          /* TC8 Mode 1 Phase Correct */
	         | (0 << CS22) | (1 << CS21) | (0 << CS20); /* IO clock divided by 8 */

	// TIMSK2 = 0 << OCIE2B /* Output Compare B Match Interrupt Enable: disabled */
	//		 | 0 << OCIE2A /* Output Compare A Match Interrupt Enable: disabled */
	//		 | 0 << TOIE2; /* Overflow Interrupt Enable: disabled */

	OCR2A = 127; /* Output compare A: 127 */

	// OCR2B = 0; /* Output compare B: 0 */

	return 0;
}

void PWM_1_enable()
{
}

void PWM_1_disable()
{
}

void PWM_1_enable_output_ch0()
{

	TCCR2A |= ((1 << COM2A1) | (1 << COM2A0));
}

void PWM_1_disable_output_ch0()
{

	TCCR2A &= ~((0 << COM2A1) | (0 << COM2A0));
}

void PWM_1_enable_output_ch1()
{

	TCCR2A |= ((0 << COM2B1) | (0 << COM2B0));
}

void PWM_1_disable_output_ch1()
{

	TCCR2A &= ~((0 << COM2B1) | (0 << COM2B0));
}

void PWM_1_load_counter(PWM_1_register_t counter_value)
{
	TCNT2 = counter_value;
}

void PWM_1_load_duty_cycle_ch0(PWM_1_register_t duty_value)
{
	OCR2A = duty_value;
}

void PWM_1_load_duty_cycle_ch1(PWM_1_register_t duty_value)
{
	OCR2B = duty_value;
}

void PWM_1_register_callback(pwm_irq_cb_t f)
{
	PWM_1_cb = f;
}

ISR(TIMER2_OVF_vect)
{
	static volatile uint8_t callback_count = 0;

	// Clear the interrupt flag
	TIFR2 |= (1 << TOV2);

	// callback function - called every 0 passes
	if ((++callback_count >= PWM_1_INTERRUPT_CB_RATE) && (PWM_1_INTERRUPT_CB_RATE != 0)) {
		if (PWM_1_cb != NULL) {
			PWM_1_cb();
		}
	}
}
