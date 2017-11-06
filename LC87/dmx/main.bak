#include "c87.h"
#include "Lc87f1m.sfr"

typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t ;
typedef int int16_t;

uint8_t buffer[515];
int16_t index = -1;
uint8_t address = 1;

void _interrupt(0x33) _isr(void)
{
    uint8_t data;
    _P0 = 1;
    data = _SCRBUF;

    if(_SCCNT1 & 0x08) { // SCRFERR set
        index = 0;
        _SCCNT1 &= ~0x08; // clear SCRFERR
    }

    if(index >= 0) {
        buffer[index++] = data;
    }

    if(index > 514) {
        _T1LR = buffer[address + 2]; // red
        _T1HR = buffer[address + 3]; // green
        _PWM0H = 255 - buffer[address + 4]; // blue
        index = -1;
    }

    _SCCNT1 &= ~0x02; // clear SCREND
     _P0 = 0;
}

void main() 
{
    _P0DDR = 0x1; // P0.1 output
    _OCR = 0x90; // divide-by-1 main clock

    // red and green LEDs are on PWML and PWMH (8-bit PWM)
    _T1CNT = 0xD0; // T1PWM = true
    _P1FCR = 0xC0; // enable Timer 1 PWML and PWMH outputs
    _P1DDR = 0xC0; // must be an (open-drain) output

    // Blue LED is on PWM0 (10-bit PWM)
    _PWM0C = 0x04; // ENPWM0 = 1
    _PWM0L = 0x0F; // Set low bits to true	  

    // turn LEDs off initially
    _T1LR = 0x00; // red
    _T1HR = 0x00; // green
    _PWM0H = 0xFF; // blue

    _SCBRG = 11; // 250 kbps @ 12 MHz
    // _SCBRG = 5; // 250 kbps @ 6 MHz... doesn't work
    _SCCNT1 = 0x21; // SCRRUN = 1, SCRENDIE = 1

    // _SCCNT0 = 0xA0;

    _IE = 0x80; // global enable interrupts

   while(1)
   {
        // _SCTBUF = 0x55;
        // while(_SCCNT0 & 0x02);
        _PCON = 0x01;
   }
}