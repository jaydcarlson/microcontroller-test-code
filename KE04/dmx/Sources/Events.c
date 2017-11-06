/* ###################################################################
**     Filename    : Events.c
**     Project     : dmx
**     Processor   : MKE04Z8VWJ4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-08-03, 19:59, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "BreakReceived.h"
#include "ByteReceived.h"
#include "BufferFull.h"

#ifdef __cplusplus
extern "C" {
#endif 

uint8_t data[513];
uint8_t address = 1;
int16_t dataIndex = -1;
/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  UART_OnError (module Events)
**
**     Component   :  UART [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  UART_OnRxChar (module Events)
**
**     Component   :  UART [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART_OnRxChar(void)
{
  /* Write your code here ... */
//	ByteReceived_SetVal(); // tooo sloow
	GPIOA_PSOR = 1 << 14;

	if(dataIndex != -1)
		UART_RecvChar(&data[dataIndex++]);

	if(dataIndex > 512)
	{
		RED_SetRatio8(data[address + 0]);
		GREEN_SetRatio8(data[address + 1]);
		BLUE_SetRatio8(data[address + 2]);
		dataIndex = -1;
	}

//	ByteReceived_ClrVal();
	GPIOA_PCOR = 1 << 14;

}

/*
** ===================================================================
**     Event       :  UART_OnFullRxBuf (module Events)
**
**     Component   :  UART [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART_OnFullRxBuf(void)
{
  /* Write your code here ... */
//	word count;
//	BufferFull_SetVal();
//	UART_RecvBlock(data, 128, &count);
//	BufferFull_ClrVal();
}

/*
** ===================================================================
**     Event       :  UART_OnBreak (module Events)
**
**     Component   :  UART [AsynchroSerial]
**     Description :
**         This event is called when a break occurs on the input
**         channel.
**         The event is available only when both <Interrupt
**         service/event> and <Break signal> properties are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART_OnBreak(void)
{
  /* Write your code here ... */
//	BreakReceived_SetVal(); // slooow
//	GPIOA_PSOR = 1 << 15;
	dataIndex = 0;
	UART_ClearRxBuf();
//	BreakReceived_ClrVal();
//	GPIOA_PCOR = 1 << 15;
}

/*
** ===================================================================
**     Event       :  Cpu_OnHardFault (module Events)
**
**     Component   :  Cpu [MKE04Z8WJ4]
*/
/*!
**     @brief
**         This event is called when the Hard Fault exception had
**         occurred. This event is automatically enabled when the [Hard
**         Fault] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnHardFault(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnSupervisorCall (module Events)
**
**     Component   :  Cpu [MKE04Z8WJ4]
*/
/*!
**     @brief
**         This event is called when the Supervisor Call exception had
**         occurred. This event is automatically enabled when the
**         [Supervisor Call] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnSupervisorCall(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnPendableService (module Events)
**
**     Component   :  Cpu [MKE04Z8WJ4]
*/
/*!
**     @brief
**         This event is called when the Pendable Service exception had
**         occurred. This event is automatically enabled when the
**         [Pendable Service] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnPendableService(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
