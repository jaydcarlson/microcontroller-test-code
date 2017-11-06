#include <atmel_start.h>
#define __AVR_ATmega168P__
#include <avr/power.h>
#include <avr/sleep.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	DDRB |= 7;
	sei();
	clock_prescale_set(clock_div_4); // 2 MHz

	// Choose our preferred sleep mode:
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	while (1) {
	    sleep_mode();
	}
}
