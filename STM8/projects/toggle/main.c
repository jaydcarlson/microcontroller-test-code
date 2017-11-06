/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "stm8s_conf.h"

main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // GO REAL FAST!
	GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
	while (1)
	{
		GPIOD->ODR ^= 1;
	}
}