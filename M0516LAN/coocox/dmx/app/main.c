#include "M051Series.h"

extern void Init();

#define RXBUFSIZE 513

// #define USE_FIFO

uint8_t data[RXBUFSIZE];

volatile int bufferIndex = 0;
volatile uint32_t g_u32comRhead  = 0;
volatile uint32_t g_u32comRtail  = 0;
volatile int32_t g_bWait         = TRUE;
uint8_t address = 1;

void UART0_IRQHandler(void)
{
	P00 = 1;
	uint8_t u8InChar = 0xFF;
	uint32_t IntStatus = UART0->ISR;

	// buffer overflow
	if(IntStatus & UART_ISR_BUF_ERR_INT_Msk)
	{
		UART0->FSR |= UART_FSR_RX_OVER_IF_Msk; // clear the RX overflow
		UART0->FCR |= UART_FCR_RFR_Msk;
	}

	// framing error
	if(IntStatus & UART_ISR_RLS_INT_Msk)
	{
		UART0->FCR |= UART_FCR_RFR_Msk; // clear the frame error interrupt
		bufferIndex = 0;
	}

	// data received
	if(IntStatus & UART_ISR_RDA_INT_Msk)
	{
//		P01 = 1;

#ifdef USE_FIFO
		/* Get all the input characters */
		while(!UART_GET_RX_EMPTY(UART0))
		{
			/* Get the character from UART Buffer */
			u8InChar = UART_READ(UART0);

			if(bufferIndex == -1) continue;

			/* Check if buffer full */
			if(bufferIndex < RXBUFSIZE)
			{
				/* Enqueue the character */
				data[bufferIndex++] = u8InChar;
			}
		}
		if(bufferIndex > 256)
			UART0->FCR &= ~UART_FCR_RFITL_Msk; // reset to no FIFO
		else
			UART0->FCR |= UART_FCR_RFITL_14BYTES;

		UART0->FCR |= UART_FCR_RFR_Msk;
#else
		u8InChar = UART_READ(UART0);

		if(bufferIndex != -1)
			data[bufferIndex++] = u8InChar;
#endif
//		P01 = 0;
	}

	if(bufferIndex > 512)
	{
//		P02 = 1;
		PWMA->CMR0 = data[address + 0];
		PWMA->CMR1 = data[address + 1];
		PWMA->CMR2 = data[address + 2];
		bufferIndex = -1;
#ifdef USE_FIFO
		UART0->FCR &= ~UART_FCR_RFITL_Msk; // reset to no FIFO
		UART0->FCR |= UART_FCR_RFR_Msk;
#endif
//		P02 = 0;
	}

	P00 = 0;
}

int main(void)
{
	Init();
    while(1)
    {
		asm("wfi");
    }

}
