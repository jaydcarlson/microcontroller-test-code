/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "UART.h"
#include "ASerialLdd1.h"
#include "RED.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "GREEN.h"
#include "PwmLdd2.h"
#include "BLUE.h"
#include "PwmLdd3.h"
#include "BreakReceived.h"
#include "BitIoLdd1.h"
#include "ByteReceived.h"
#include "BitIoLdd2.h"
#include "BufferFull.h"
#include "BitIoLdd3.h"

#ifdef __cplusplus
extern "C" {
#endif 

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
void UART_OnError(void);

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
void UART_OnRxChar(void);

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
void UART_OnFullRxBuf(void);

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
void UART_OnBreak(void);

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
void Cpu_OnHardFault(void);

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
void Cpu_OnSupervisorCall(void);

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
void Cpu_OnPendableService(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
