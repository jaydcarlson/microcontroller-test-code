#include <N76E003.h>
#include <Function_Define.h>
#include <Common.h>
#include <stdbool.h>
#include <SFR_Macro.h>

uint8_t address = 1;
int currentIndex = -1;
xdata uint8_t buffer[512];

void SerialPort0_ISR(void) interrupt 4 
{
    uint8_t temp;
    P00 = 1;
    temp = SBUF;
    RI = 0; // clear reception interrupt
    if(SM0) // frame error occured
    {
        // start of frame!
        currentIndex = 0;
        SM0 = 0;
                
        CKDIV = 1; // bring the system into 8 MHz mode
        TH1 = 254; // update the UART baud rate accordingly
    }
    else if(currentIndex >= 0)
    {
    //		P01 = 1;
        buffer[currentIndex++] = temp;
    //		P01 = 0;
    }
    if(currentIndex == 513)
    {
        //	P03 = 1;
        PWM0L = 255-buffer[address];
        PWM1L = 255-buffer[address+1];
        PWM2L = 255-buffer[address+2];
        LOAD = true;
        currentIndex = -1;
        CKDIV = 3;	// save some power while we wait for a framing error
        TH1 = 255; // use the fastest baud rate we can (doesn't matter
        //	P03 = 0;
    }
	P00 = 0;
}

void main()
{
    CKDIV = 1;		// run system at 8 MHz

    Set_All_GPIO_Quasi_Mode;

    // pins for debugging
    P00_PushPull_Mode;
    //	P01_PushPull_Mode;
    //	P03_PushPull_Mode;

    PWM0_P12_OUTPUT_ENABLE;
    PWM1_P11_OUTPUT_ENABLE;
    PWM2_P10_OUTPUT_ENABLE;

    PWM_IMDEPENDENT_MODE;
    PWM_CLOCK_DIV_8;
    PWMPH = 0x00;
    PWMPL = 0xFF;

    PWM0L = 0xFE;
    PWM1L = 0xFE;
    PWM2L = 0xFE;

    LOAD = true;
    PWMRUN = true;

    // UART configuration
    // copied from InitialUART0_Timer1() 
    P06_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
    P07_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit

    SCON = 0x50;     	//UART0 Mode1,REN=1,TI=1
    TMOD |= 0x20;    	//Timer1 Mode1

    set_SMOD;        	//UART0 Double Rate Enable
    set_T1M;
    clr_BRCK;        	//Serial port 0 baud rate clock source = Timer1
        
    set_SMOD0; 				// use SM0/FE as a framing error bit
    TH1 = 254;
    TR1 = 1;
    ES = true; 				// enable serial interrupt
    EA = true; 				// enable interrupts
        
    while(1)
    {
        PCON |= 1; // set IDL to go into idle mode
    }
}