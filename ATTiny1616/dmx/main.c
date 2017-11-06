#include <atmel_start.h>
#include <avr/sleep.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace with your application code */
	PWM_0_enable_output_ch0();
	PWM_0_enable_output_ch1();
	PWM_0_enable_output_ch2();
	
	// Choose our preferred sleep mode:
	set_sleep_mode(SLEEP_MODE_IDLE);	
	while (1) {
		PORTA.OUTTGL = 4;
		// Put the device to sleep:
		sleep_mode();
		//PORTA.OUTTGL = 4;
	}
}
