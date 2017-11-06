/**
 * \file
 *
 * \brief Port
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

#ifndef _PORT_INCLUDED_
#define _PORT_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>

enum port_pull_mode {
	PORT_PULL_OFF,
	PORT_PULL_UP,
};

enum port_dir {
	PORT_DIR_IN,
	PORT_DIR_OUT,
	PORT_DIR_OFF,
};

/**
 * \brief Set port pin pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull modes are defined by device used
 *
 * \param[in] pin       The pin number within port
 * \param[in] pull_mode Pin pull mode
 */
static inline void PORTA_set_pin_pull_mode(const uint8_t pin, const enum port_pull_mode pull_mode)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTA + 0x10 + pin);

	if (pull_mode == PORT_PULL_UP) {
		*port_pin_ctrl |= PORT_PULLUPEN_bm;
	} else if (pull_mode == PORT_PULL_OFF) {
		*port_pin_ctrl &= ~PORT_PULLUPEN_bm;
	}
}

/**
 * \brief Set port pin inverted mode
 *
 * Configure pin invert I/O or not
 *
 * \param[in] pin       The pin number within port
 * \param[in] inverted  Pin inverted mode
 */
static inline void PORTA_pin_set_inverted(const uint8_t pin, const bool inverted)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTA + 0x10 + pin);

	if (inverted) {
		*port_pin_ctrl |= PORT_INVEN_bm;
	} else {
		*port_pin_ctrl &= ~PORT_INVEN_bm;
	}
}

/**
 * \brief Set port pin input/sense configuration
 *
 * Enable/disable digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] pin pin number within port
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 *
 */
static inline void PORTA_pin_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTA + 0x10 + pin);

	*port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}

/**
 * \brief Set port data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * \param[in] dir       PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORTA_set_port_dir(const uint8_t mask, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTA.DIR &= ~mask;
		break;
	case PORT_DIR_OUT:
		VPORTA.DIR |= mask;
		break;
	case PORT_DIR_OFF:
		/*/ should activate the pullup for power saving
		  but a bit costly to do it here */
		{
			for (uint8_t i = 0; i < 8; i++) {
				if (mask & 1 << i) {
					*((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
				}
			}
		}
		break;
	default:
		break;
	}
}

/**
 * \brief Set port pin data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] pin       The pin number within port
 * \param[in] dir       PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORTA_set_pin_dir(const uint8_t pin, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTA.DIR &= ~(1 << pin);
		break;
	case PORT_DIR_OUT:
		VPORTA.DIR |= (1 << pin);
		break;
	case PORT_DIR_OFF:
		*((uint8_t *)&PORTA + 0x10 + pin) |= 1 << PORT_PULLUPEN_bp;
		break;
	default:
		break;
	}
}

/**
 * \brief Set port level
 *
 * Sets output level on the pins defined by the bit mask
 *
 * \param[in] mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin
 * \param[in] level true  = Pin levels set to "high" state
 *                  false = Pin levels set to "low" state
 */
static inline void PORTA_set_port_level(const uint8_t mask, const bool level)
{
	if (level == true) {
		VPORTA.OUT |= mask;
	} else {
		VPORTA.OUT &= ~mask;
	}
}

/**
 * \brief Set port level
 *
 * Sets output level on a pin
 *
 * \param[in] pin       The pin number within port
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PORTA_set_pin_level(const uint8_t pin, const bool level)
{
	if (level == true) {
		VPORTA.OUT |= (1 << pin);
	} else {
		VPORTA.OUT &= ~(1 << pin);
	}
}

/**
 * \brief Toggle out level on pins
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 */
static inline void PORTA_toggle_port_level(const uint8_t mask)
{
	PORTA.OUTTGL = mask;
}

/**
 * \brief Toggle output level on pin
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] pin       The pin number within port
 */
static inline void PORTA_toggle_pin_level(const uint8_t pin)
{
	PORTA.OUTTGL = 1 << pin;
}

/**
 * \brief Get input level on pins
 *
 * Read the input level on pins connected to a port
 *
 */
static inline uint8_t PORTA_get_port_level()
{
	return VPORTA.IN;
}

/**
 * \brief Get level on pin
 *
 * Reads the level on pins connected to a port
 */
static inline bool PORTA_get_pin_level(const uint8_t pin)
{
	return VPORTA.IN & (1 << pin);
}

/**
 * \brief Write value to Port
 *
 * Write directly to the port OUT register
 *
 * \param[in] value Value to write to the port register
 */
static inline void PORTA_write_port(const uint8_t value)
{
	VPORTA.OUT = value;
}

/**
 * \brief Set port pin pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull modes are defined by device used
 *
 * \param[in] pin       The pin number within port
 * \param[in] pull_mode Pin pull mode
 */
static inline void PORTB_set_pin_pull_mode(const uint8_t pin, const enum port_pull_mode pull_mode)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTB + 0x10 + pin);

	if (pull_mode == PORT_PULL_UP) {
		*port_pin_ctrl |= PORT_PULLUPEN_bm;
	} else if (pull_mode == PORT_PULL_OFF) {
		*port_pin_ctrl &= ~PORT_PULLUPEN_bm;
	}
}

/**
 * \brief Set port pin inverted mode
 *
 * Configure pin invert I/O or not
 *
 * \param[in] pin       The pin number within port
 * \param[in] inverted  Pin inverted mode
 */
static inline void PORTB_pin_set_inverted(const uint8_t pin, const bool inverted)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTB + 0x10 + pin);

	if (inverted) {
		*port_pin_ctrl |= PORT_INVEN_bm;
	} else {
		*port_pin_ctrl &= ~PORT_INVEN_bm;
	}
}

/**
 * \brief Set port pin input/sense configuration
 *
 * Enable/disable digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] pin pin number within port
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 *
 */
static inline void PORTB_pin_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTB + 0x10 + pin);

	*port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}

/**
 * \brief Set port data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * \param[in] dir       PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORTB_set_port_dir(const uint8_t mask, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTB.DIR &= ~mask;
		break;
	case PORT_DIR_OUT:
		VPORTB.DIR |= mask;
		break;
	case PORT_DIR_OFF:
		/*/ should activate the pullup for power saving
		  but a bit costly to do it here */
		{
			for (uint8_t i = 0; i < 8; i++) {
				if (mask & 1 << i) {
					*((uint8_t *)&PORTB + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
				}
			}
		}
		break;
	default:
		break;
	}
}

/**
 * \brief Set port pin data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] pin       The pin number within port
 * \param[in] dir       PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORTB_set_pin_dir(const uint8_t pin, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTB.DIR &= ~(1 << pin);
		break;
	case PORT_DIR_OUT:
		VPORTB.DIR |= (1 << pin);
		break;
	case PORT_DIR_OFF:
		*((uint8_t *)&PORTB + 0x10 + pin) |= 1 << PORT_PULLUPEN_bp;
		break;
	default:
		break;
	}
}

/**
 * \brief Set port level
 *
 * Sets output level on the pins defined by the bit mask
 *
 * \param[in] mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin
 * \param[in] level true  = Pin levels set to "high" state
 *                  false = Pin levels set to "low" state
 */
static inline void PORTB_set_port_level(const uint8_t mask, const bool level)
{
	if (level == true) {
		VPORTB.OUT |= mask;
	} else {
		VPORTB.OUT &= ~mask;
	}
}

/**
 * \brief Set port level
 *
 * Sets output level on a pin
 *
 * \param[in] pin       The pin number within port
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PORTB_set_pin_level(const uint8_t pin, const bool level)
{
	if (level == true) {
		VPORTB.OUT |= (1 << pin);
	} else {
		VPORTB.OUT &= ~(1 << pin);
	}
}

/**
 * \brief Toggle out level on pins
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 */
static inline void PORTB_toggle_port_level(const uint8_t mask)
{
	PORTB.OUTTGL = mask;
}

/**
 * \brief Toggle output level on pin
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] pin       The pin number within port
 */
static inline void PORTB_toggle_pin_level(const uint8_t pin)
{
	PORTB.OUTTGL = 1 << pin;
}

/**
 * \brief Get input level on pins
 *
 * Read the input level on pins connected to a port
 *
 */
static inline uint8_t PORTB_get_port_level()
{
	return VPORTB.IN;
}

/**
 * \brief Get level on pin
 *
 * Reads the level on pins connected to a port
 */
static inline bool PORTB_get_pin_level(const uint8_t pin)
{
	return VPORTB.IN & (1 << pin);
}

/**
 * \brief Write value to Port
 *
 * Write directly to the port OUT register
 *
 * \param[in] value Value to write to the port register
 */
static inline void PORTB_write_port(const uint8_t value)
{
	VPORTB.OUT = value;
}

/**
 * \brief Set port pin pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull modes are defined by device used
 *
 * \param[in] pin       The pin number within port
 * \param[in] pull_mode Pin pull mode
 */
static inline void PORTC_set_pin_pull_mode(const uint8_t pin, const enum port_pull_mode pull_mode)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTC + 0x10 + pin);

	if (pull_mode == PORT_PULL_UP) {
		*port_pin_ctrl |= PORT_PULLUPEN_bm;
	} else if (pull_mode == PORT_PULL_OFF) {
		*port_pin_ctrl &= ~PORT_PULLUPEN_bm;
	}
}

/**
 * \brief Set port pin inverted mode
 *
 * Configure pin invert I/O or not
 *
 * \param[in] pin       The pin number within port
 * \param[in] inverted  Pin inverted mode
 */
static inline void PORTC_pin_set_inverted(const uint8_t pin, const bool inverted)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTC + 0x10 + pin);

	if (inverted) {
		*port_pin_ctrl |= PORT_INVEN_bm;
	} else {
		*port_pin_ctrl &= ~PORT_INVEN_bm;
	}
}

/**
 * \brief Set port pin input/sense configuration
 *
 * Enable/disable digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] pin pin number within port
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 *
 */
static inline void PORTC_pin_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTC + 0x10 + pin);

	*port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}

/**
 * \brief Set port data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * \param[in] dir       PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORTC_set_port_dir(const uint8_t mask, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTC.DIR &= ~mask;
		break;
	case PORT_DIR_OUT:
		VPORTC.DIR |= mask;
		break;
	case PORT_DIR_OFF:
		/*/ should activate the pullup for power saving
		  but a bit costly to do it here */
		{
			for (uint8_t i = 0; i < 8; i++) {
				if (mask & 1 << i) {
					*((uint8_t *)&PORTC + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
				}
			}
		}
		break;
	default:
		break;
	}
}

/**
 * \brief Set port pin data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] pin       The pin number within port
 * \param[in] dir       PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORTC_set_pin_dir(const uint8_t pin, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTC.DIR &= ~(1 << pin);
		break;
	case PORT_DIR_OUT:
		VPORTC.DIR |= (1 << pin);
		break;
	case PORT_DIR_OFF:
		*((uint8_t *)&PORTC + 0x10 + pin) |= 1 << PORT_PULLUPEN_bp;
		break;
	default:
		break;
	}
}

/**
 * \brief Set port level
 *
 * Sets output level on the pins defined by the bit mask
 *
 * \param[in] mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin
 * \param[in] level true  = Pin levels set to "high" state
 *                  false = Pin levels set to "low" state
 */
static inline void PORTC_set_port_level(const uint8_t mask, const bool level)
{
	if (level == true) {
		VPORTC.OUT |= mask;
	} else {
		VPORTC.OUT &= ~mask;
	}
}

/**
 * \brief Set port level
 *
 * Sets output level on a pin
 *
 * \param[in] pin       The pin number within port
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PORTC_set_pin_level(const uint8_t pin, const bool level)
{
	if (level == true) {
		VPORTC.OUT |= (1 << pin);
	} else {
		VPORTC.OUT &= ~(1 << pin);
	}
}

/**
 * \brief Toggle out level on pins
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 */
static inline void PORTC_toggle_port_level(const uint8_t mask)
{
	PORTC.OUTTGL = mask;
}

/**
 * \brief Toggle output level on pin
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] pin       The pin number within port
 */
static inline void PORTC_toggle_pin_level(const uint8_t pin)
{
	PORTC.OUTTGL = 1 << pin;
}

/**
 * \brief Get input level on pins
 *
 * Read the input level on pins connected to a port
 *
 */
static inline uint8_t PORTC_get_port_level()
{
	return VPORTC.IN;
}

/**
 * \brief Get level on pin
 *
 * Reads the level on pins connected to a port
 */
static inline bool PORTC_get_pin_level(const uint8_t pin)
{
	return VPORTC.IN & (1 << pin);
}

/**
 * \brief Write value to Port
 *
 * Write directly to the port OUT register
 *
 * \param[in] value Value to write to the port register
 */
static inline void PORTC_write_port(const uint8_t value)
{
	VPORTC.OUT = value;
}

#ifdef __cplusplus
}
#endif

#endif
