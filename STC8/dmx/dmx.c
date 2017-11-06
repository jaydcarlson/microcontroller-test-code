#define MAIN_Fosc   4000000
#include <stc\stc8.h>
#include <stdint.h>

uint8_t address = 1;
int currentIndex = -1;
xdata uint8_t buffer[512];

void UART_ISR(void) interrupt UART1_VECTOR using 2
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
    }
    
    else if(currentIndex >= 0)
    {
        P01 = 1;
        buffer[currentIndex++] = temp;
    	P01 = 0;
    }
    
    if(currentIndex == 513)
    {
        P03 = 1;
        CCAP0H = buffer[address];
        CCAP1H = buffer[address+1];
        CCAP2H = buffer[address+2];
        currentIndex = -1;
        P03 = 0;
    }
    
    P00 = 0;
}

void main()
{
    CLKDIV = 0x04; // divide 4 MHz clock by 4 = 1 MHz (doesn't work?)
    S1_USE_P36P37(); // debugger is attached to default S1 pins, so use alt
    // pins for debugging
    // P1n_push_pull(0xFF);
    P0n_push_pull(0x07);
    CCON = 0x00;
    CMOD = 0x08;
    CL = 0;
    CH = 0;
    PCA0_PWM(8);
    PCA1_PWM(8);
    PCA2_PWM(8);
    CR = 1;

    // UART configuration
	SCON = 0x50;		//8bit and variable baudrate
	AUXR |= 0x40;		//Timer1's clock is Fosc (1T)
	AUXR &= 0xFE;		//Use Timer1 as baudrate generator
	TMOD &= 0x0F;		//Set Timer1 as 16-bit auto reload mode
	TL1 = 0xFC;		//Initial timer value
	TH1 = 0xFF;		//Initial timer value
	ET1 = 0;		//Disable Timer1 interrupt
	TR1 = 1;		//Timer1 running
    
    S1_Int_Enable();
    EA = 1; 				// enable interrupts
    PCON |= SCON_SMOD0;     // enable framing error
    while(1)
    {
        _nop_();
        _nop_();
        PCON |= 1; // set IDL to go into idle mode
        _nop_();
        _nop_();
    }
}