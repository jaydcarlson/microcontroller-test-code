/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_serial.c
* Version      : CodeGenerator for RL78/G12 V2.03.04.01 [11 Nov 2016]
* Device(s)    : R5F102A8
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Serial module.
* Creation Date: 8/4/2017
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_uart0_tx_address;        /* uart0 transmit buffer address */
volatile uint16_t  g_uart0_tx_count;           /* uart0 transmit data number */
volatile uint8_t * gp_uart0_rx_address;        /* uart0 receive buffer address */
volatile uint16_t  g_uart0_rx_count;           /* uart0 receive data number */
volatile uint16_t  g_uart0_rx_length;          /* uart0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SAU0_Create
* Description  : This function initializes the SAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Create(void)
{
    SAU0EN = 1U;    /* supply SAU0 clock */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS0 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
    R_UART0_Create();
}

/***********************************************************************************************************************
* Function Name: R_UART0_Create
* Description  : This function initializes the UART0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Create(void)
{
    ST0 |= _0002_SAU_CH1_STOP_TRG_ON;    /* disable UART0 receive operation */
    STMK0 = 1U;    /* disable INTST0 interrupt */
    STIF0 = 0U;    /* clear INTST0 interrupt flag */
    SRMK0 = 1U;    /* disable INTSR0 interrupt */
    SRIF0 = 0U;    /* clear INTSR0 interrupt flag */
    SREMK0 = 1U;   /* disable INTSRE0 interrupt */
    SREIF0 = 0U;   /* clear INTSRE0 interrupt flag */
    /* Set INTSR0 low priority */
    SRPR10 = 1U;
    SRPR00 = 1U;
    /* Set INTSRE0 low priority */
    SREPR10 = 1U;
    SREPR00 = 1U;
    SIR01 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    NFEN0 |= _01_SAU_RXD0_FILTER_ON;
    SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_TRIGGER_SOFTWARE |
            _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SMR01 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL |
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR01 = _4000_SAU_RECEPTION | _0400_SAU_INTSRE_ENABLE | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 |
            _0007_SAU_LENGTH_8;
    SDR01 = _0600_UART0_RECEIVE_DIVISOR;
    SOE0 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable UART0 output */
    /* Set RxD0 pin */
    PM1 |= 0x02U;
}

/***********************************************************************************************************************
* Function Name: R_UART0_Start
* Description  : This function starts the UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Start(void)
{
    SS0 |= _0002_SAU_CH1_START_TRG_ON;    /* enable UART0 receive */
    SRIF0 = 0U;    /* clear INTSR0 interrupt flag */
    SREIF0 = 0U;   /* clear INTSRE0 interrupt flag */
    SRMK0 = 0U;    /* enable INTSR0 interrupt */
    SREMK0 = 0U;   /* enable INTSRE0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_UART0_Stop
* Description  : This function stops the UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Stop(void)
{
    SRMK0 = 1U;    /* disable INTSR0 interrupt */
    SREMK0 = 1U;   /* disable INTSRE0 interrupt */
    ST0 |= _0002_SAU_CH1_STOP_TRG_ON;    /* disable UART0 receive */
    SRIF0 = 0U;    /* clear INTSR0 interrupt flag */
    SREIF0 = 0U;   /* clear INTSRE0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UART0_Receive
* Description  : This function receives UART0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart0_rx_count = 0U;
        g_uart0_rx_length = rx_num;
        gp_uart0_rx_address = rx_buf;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
