/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

/*! The buffer size for USART */
#define USART_0_BUFFER_SIZE 16

struct usart_async_descriptor USART_0;

static uint8_t USART_0_buffer[USART_0_BUFFER_SIZE];

struct pwm_descriptor PWM_2;

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_0_CLOCK_init()
{

	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM0);
	_gclk_enable_channel(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_0_PORT_init()
{

	gpio_set_pin_function(PA04, PINMUX_PA04D_SERCOM0_PAD0);

	gpio_set_pin_function(PA05, PINMUX_PA05D_SERCOM0_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_async_init(&USART_0, SERCOM0, USART_0_buffer, USART_0_BUFFER_SIZE, (void *)NULL);
	USART_0_PORT_init();
}

void PWM_2_PORT_init(void)
{

	gpio_set_pin_function(PA14, PINMUX_PA14F_TCC0_WO0);

	gpio_set_pin_function(PA15, PINMUX_PA15F_TCC0_WO1);

	gpio_set_pin_function(PA06, PINMUX_PA06F_TCC0_WO2);
}

void PWM_2_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TCC0);
	_gclk_enable_channel(TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC);
}

void PWM_2_init(void)
{
	PWM_2_CLOCK_init();
	PWM_2_PORT_init();
	pwm_init(&PWM_2, TCC0, _tcc_get_pwm());
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA02

	// Set pin direction to output
	gpio_set_pin_direction(toggle1, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(toggle1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(toggle1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA03

	// Set pin direction to output
	gpio_set_pin_direction(toggle2, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(toggle2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(toggle2, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA07

	// Set pin direction to output
	gpio_set_pin_direction(toggle3, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(toggle3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(toggle3, GPIO_PIN_FUNCTION_OFF);

	USART_0_init();

	PWM_2_init();
}
