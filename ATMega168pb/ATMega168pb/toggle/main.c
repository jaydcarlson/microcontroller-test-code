/*
 * toggle.c
 *
 * Created: 9/12/2017 7:11:15 PM
 * Author : JayLocal
 */ 

#include <avr/io.h>

void testFunc()
{
	volatile int i = 5;
}


int main(void)
{
	DDRB |= 1;
    /* Replace with your application code */
	volatile int i = 5;
	testFunc();
    while (1) 
    {
		
		PINB = 1;
		i++;
    }
}

