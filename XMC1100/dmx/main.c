/*
 * main.c
 *
 *  Created on: 2017 Aug 05 21:04:28
 *  Author: JayLocal
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
__attribute__ ((section (".ram_code")))
void DMX512_RD_UserCallBack()
{
	PWM_CCU4_SetDutyCycle(&RED, DMX512_RD_0_rx_array[0] * PWM_CCU4_SYM_DUTY_MAX / 255);
	PWM_CCU4_SetDutyCycle(&GREEN, DMX512_RD_0_rx_array[1] * PWM_CCU4_SYM_DUTY_MAX / 255);
	PWM_CCU4_SetDutyCycle(&BLUE, DMX512_RD_0_rx_array[2] * PWM_CCU4_SYM_DUTY_MAX / 255);
}

__attribute__ ((section (".ram_code")))
int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  asm("wfi");
  }
}
