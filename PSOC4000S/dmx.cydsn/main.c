/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

uint8_t address = 1;

int16_t idx = -1;

uint8_t data[513];

CY_ISR(UartInterrupt)
{
    //Toggle1_Write(1);
    uint32_t source = UART_GetRxInterruptSourceMasked();
    
    if(source & UART_INTR_RX_BREAK_DETECT)
    {
//        Toggle2_Write(1);
        UART_SpiUartClearRxBuffer();
        idx = 0;
//        Toggle2_Write(0);
    }
    
    while(UART_SpiUartGetRxBufferSize() > 0)
    {
//        Toggle3_Write(1);
        uint8_t temp = UART_SpiUartReadRxData();
        if(idx >= 0)
            data[idx++] = temp;
            
        if(idx > 512)
        {
//            Toggle4_Write(1);
            RED_WriteCompare  (data[address+0]);
            GREEN_WriteCompare(data[address+1]);
            BLUE_WriteCompare (data[address+2]);
            idx = -1;
//            Toggle4_Write(0);
        }
        
//        Toggle3_Write(0);
    }
    
    UART_ClearRxInterruptSource(source);
   // Toggle1_Write(0);
    //Toggle3_Write(0);
}

int main(void)
{
    RED_Start();
    GREEN_Start();
    BLUE_Start();
    
    UART_ISR_StartEx(UartInterrupt);
    
    UART_Start();
    
    UART_UART_RX_CTRL_REG  |= 0xF0000; // set break width to maximum of 17 bits 
    UART_INTR_RX_MASK_REG  = (UART_INTR_RX_BREAK_DETECT | UART_INTR_RX_NOT_EMPTY);
    UART_INTR_RX_SET_REG   = (UART_INTR_RX_BREAK_DETECT | UART_INTR_RX_NOT_EMPTY);
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        CySysPmSleep();
    }
}

/* [] END OF FILE */
