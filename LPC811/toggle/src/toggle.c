/*
===============================================================================
 Name        : toggle.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "chip.h"
#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();


    // TODO: insert code here
    Chip_GPIO_Init(LPC_GPIO_PORT);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 0, false);
    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, 0, 0);
    }
    return 0 ;
}
