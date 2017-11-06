#include "HT66F0185.h"

typedef unsigned char uint8_t;
typedef char int8_t;
typedef int int16_t;

uint8_t address = 1;

uint8_t data[5];
int16_t currentIndex = -1;

void __attribute((interrupt(0x2C))) _UartISR()
{
	_pa1 = 1;
	if(_ferr) { // framing error 
		_pa6 = 1;
		currentIndex = 0;
		_pa6 = 0;
	}
	
	while(_rxif) {
		uint8_t temp = _txr_rxr;
		
		if(currentIndex >= 0)
		{
			// if(currentIndex < 5) 
			{
				data[currentIndex] = temp;
			}
			
			currentIndex++;
		}
		
		if(currentIndex > 5) {
			
			_tm0al = data[address + 1]; // green
			_tm1al = data[address + 2]; // green
			_tm2al = data[address + 3]; // blue
			 
			_tm0ah = 0;
			_tm1ah = 0;
			_tm2ah = 0;
			
			currentIndex = -1;
		}	
	}
	_pa1 = 0;
}

void main()
{
	_wdtc =0b10101000; // disable watchdog
	_acerl = 0x00; // set all ADC pins to digital I/O
	_smod = 0b11100010;
	_uarten = 1; // enable UART
	_brg = 0; // set baud to 250 kbps
	_rxen = 1; // enable RX
	_brgh = 1; // fast baud (/16)
	_rie = 1; // uart RX interrupt enable
	_ure = 1; // uart interrupt enable
	_emi = 1; // global interrupt enable
	_pac = 0;
	_pbc = 0;
	_pcc = 0;
	_pdc = 0;
	
	_pa = 0;
	_pb = 0;
	_pc = 0;
	_pd = 0;

//	16-bit STM
// 	red
	_t0cp = 1;
	_t0m1 = 1;
	_t0m0 = 0;
	_t0dpx = 0;
	_t0io1 = 1;
	_tm0rp = 1;
	_tm0al = 0;
	_tm0ah = 0;
	_t0on = 1;
	
//	10-bit PTM	
//	green
	_t1cp = 1;
	_t1m1 = 1;
	_t1m0 = 0;
	_t1io1 = 1;
	_tm1rpl = 0xFF;
	_tm1rph = 0x00;
	_tm1al = 0;
	_tm1ah = 0;
	_t1on = 1;
	
// 	16-bit CTM	
//	blue
	_t2cp = 1;
	_t2m1 = 1;
	_t2m0 = 0;
	_t2dpx = 0; // use RP for period, RA for duty
	_t2io1 = 1;
	_tm2rp = 1; // 8-bit PWM
	_tm2al = 0;
	_tm1ah = 0;
	_t2on = 1;
	

	_idlen = 1; // idle mode on halt
	_fsyson = 1; // keep clock on in halt

	while(1) {
		_halt();
	}

}