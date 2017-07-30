#include "M051Series.h"

extern void SYS_Init(void);

int main()
{
    SYS_Init();
    GPIO_SetMode(P0, BIT0, GPIO_PMD_OUTPUT);
 while(1) {
    P00 ^= 1;
 }     
}    