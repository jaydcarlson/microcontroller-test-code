/*	BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *	Copyright (c) 2007 STMicroelectronics
 */

#include "stm8s_conf.h"

uint8_t address = 1;
uint8_t data[513];
int16_t dataIndex = -1;

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};

@far @interrupt void UART2_RX_IRQHandler (void)
{
	uint8_t temp;
	GPIO_WriteHigh(GPIOD, GPIO_PIN_0);
	temp = UART2_ReceiveData8();
	
	if(UART2_GetFlagStatus(UART2_FLAG_FE) == SET)
	{
		// break
		dataIndex = 0;
	} else {
		if(dataIndex != -1)
		{
			// GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
			data[dataIndex++] = temp;
			// GPIO_WriteLow(GPIOD, GPIO_PIN_2);
		}
	}
	
	if(dataIndex > 400)
	{
		TIM1->CCR1L = data[address + 0];
		TIM1->CCR2L = data[address + 1];
		TIM1->CCR3L = data[address + 2];
		dataIndex = -1;
	}
	
	// UART2_GetFlagStatus(UART2_FLAG_OR_LHE); // just in case we have an overflow
			GPIO_WriteLow(GPIOD, GPIO_PIN_0);
	return;
}

@far @interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}

extern void _stext();     /* startup routine */

struct interrupt_vector const _vectab[] = {
	{0x82, (interrupt_handler_t)_stext}, /* reset */
	{0x82, NonHandledInterrupt}, /* trap  */
	{0x82, NonHandledInterrupt}, /* irq0  */
	{0x82, NonHandledInterrupt}, /* irq1  */
	{0x82, NonHandledInterrupt}, /* irq2  */
	{0x82, NonHandledInterrupt}, /* irq3  */
	{0x82, NonHandledInterrupt}, /* irq4  */
	{0x82, NonHandledInterrupt}, /* irq5  */
	{0x82, NonHandledInterrupt}, /* irq6  */
	{0x82, NonHandledInterrupt}, /* irq7  */
	{0x82, NonHandledInterrupt}, /* irq8  */
	{0x82, NonHandledInterrupt}, /* irq9  */
	{0x82, NonHandledInterrupt}, /* irq10 */
	{0x82, NonHandledInterrupt}, /* irq11 */
	{0x82, NonHandledInterrupt}, /* irq12 */
	{0x82, NonHandledInterrupt}, /* irq13 */
	{0x82, NonHandledInterrupt}, /* irq14 */
	{0x82, NonHandledInterrupt}, /* irq15 */
	{0x82, NonHandledInterrupt}, /* irq16 */
	{0x82, NonHandledInterrupt}, /* irq17 */
	{0x82, NonHandledInterrupt}, /* irq18 */
	{0x82, NonHandledInterrupt}, /* irq19 */
	{0x82, NonHandledInterrupt}, /* irq20 */
	{0x82, UART2_RX_IRQHandler}, /* irq21 */
	{0x82, NonHandledInterrupt}, /* irq22 */
	{0x82, NonHandledInterrupt}, /* irq23 */
	{0x82, NonHandledInterrupt}, /* irq24 */
	{0x82, NonHandledInterrupt}, /* irq25 */
	{0x82, NonHandledInterrupt}, /* irq26 */
	{0x82, NonHandledInterrupt}, /* irq27 */
	{0x82, NonHandledInterrupt}, /* irq28 */
	{0x82, NonHandledInterrupt}, /* irq29 */
};
