/****************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 10 $
 * $Date: 15/05/22 3:59p $
 * @brief    Transmit and receive data in UART RS485 mode. 
 *           This sample code needs to work with UART_RS485_Slave.
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"


#define PLL_CLOCK           50000000


#define MATCH_ADDRSS1     0xC0
#define MATCH_ADDRSS2     0xA2
#define UNMATCH_ADDRSS1   0xB1
#define UNMATCH_ADDRSS2   0xD3


/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
extern char GetChar(void);
int32_t main(void);
void RS485_SendAddressByte(uint8_t u8data);
void RS485_SendDataByte(uint8_t *pu8TxBuf, uint32_t u32WriteBytes);
void RS485_9bitModeMaster(void);


/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Transmit Control  (Address Byte: Parity Bit =1 , Data Byte:Parity Bit =0)                        */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_SendAddressByte(uint8_t u8data)
{
    /* Set UART parity as MARK and ship baud rate setting */
    UART_SetLine_Config(UART1, 0, UART_WORD_LEN_8, UART_PARITY_MARK, UART_STOP_BIT_1);

    /* Send data */
    UART_WRITE(UART1, u8data);
}

void RS485_SendDataByte(uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    /* Set UART parity as SPACE and ship baud rate setting */
    UART_SetLine_Config(UART1, 0, UART_WORD_LEN_8, UART_PARITY_SPACE, UART_STOP_BIT_1);

    /* Send data */
    UART_Write(UART1, pu8TxBuf, u32WriteBytes);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Transmit Test                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_9bitModeMaster()
{
    int32_t i32;
    uint8_t g_u8SendDataGroup1[10] = {0};
    uint8_t g_u8SendDataGroup2[10] = {0};
    uint8_t g_u8SendDataGroup3[10] = {0};
    uint8_t g_u8SendDataGroup4[10] = {0};

    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|     Pin Configure                                         |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|    _______                                    _______     |\n");
    printf("|   |       |                                  |       |    |\n");
    printf("|   |Master |---TXD1(P1.3) <====> RXD1(P1.2)---| Slave |    |\n");
    printf("|   |       |---RTS1(P0.1) <====> RTS1(P0.1)---|       |    |\n");
    printf("|   |_______|                                  |_______|    |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");

    /*
        The sample code is used to test RS485 9-bit mode and needs
        two Module test board to complete the test.
        Master:
            1.Set AUD mode and HW will control RTS pin. LEV_RTS is set to '0'.
            2.Master will send four different address with 10 bytes data to test Slave.
            3.Address bytes : the parity bit should be '1'. (Set UA_LCR = 0x2B)
            4.Data bytes : the parity bit should be '0'. (Set UA_LCR = 0x3B)
            5.RTS pin is low in idle state. When master is sending,
              RTS pin will be pull high.

        Slave:
            1.Set AAD and AUD mode firstly. LEV_RTS is set to '0'.
            2.The received byte, parity bit is '1' , is considered "ADDRESS".
            3.The received byte, parity bit is '0' , is considered "DATA".  (Default)
            4.AAD: The slave will ignore any data until ADDRESS match ADDR_MATCH value.
              When RLS and RDA interrupt is happened,it means the ADDRESS is received.
              Check if RS485_ADD_DETF is set and read UA_RBR to clear ADDRESS stored in rx_fifo.

              NMM: The slave will ignore data byte until disable RX_DIS.
              When RLS and RDA interrupt is happened,it means the ADDRESS is received.
              Check the ADDRESS is match or not by user in UART_IRQHandler.
              If the ADDRESS is match,clear RX_DIS bit to receive data byte.
              If the ADDRESS is not match,set RX_DIS bit to avoid data byte stored in FIFO.
    */

    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|           RS485  Function Test (9-bit Master)             |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function will send different address with 10 data     |\n");
    printf("| bytes to test RS485 9-bit mode. Please connect TX/RX to   |\n");
    printf("| another board and wait its ready to receive.              |\n");
    printf("| Press any key to start...                                 |\n");
    printf("+-----------------------------------------------------------+\n\n");
    GetChar();

    /* Set RS485-Master as AUD mode */
    /* Enable AUD mode to HW control RTS pin automatically */
    /* You also can use GPIO to control RTS pin for replacing AUD mode*/
    UART_SelectRS485Mode(UART1, UART_ALT_CSR_RS485_AUD_Msk, 0);

    /* Set RTS pin active level as high level active */
    UART1->MCR &= ~UART_MCR_LEV_RTS_Msk;
    UART1->MCR |= UART_RTS_IS_HIGH_LEV_ACTIVE;

    /* Prepare Data to transmit */
    for(i32 = 0; i32 < 10; i32++)
    {
        g_u8SendDataGroup1[i32] = i32;
        g_u8SendDataGroup2[i32] = i32 + 10;
        g_u8SendDataGroup3[i32] = i32 + 20;
        g_u8SendDataGroup4[i32] = i32 + 30;
    }

    /* Send For different Address and data for test */
    printf("Send Address %x and data 0~9\n", MATCH_ADDRSS1);
    RS485_SendAddressByte(MATCH_ADDRSS1);
    RS485_SendDataByte(g_u8SendDataGroup1, 10);

    printf("Send Address %x and data 10~19\n", UNMATCH_ADDRSS1);
    RS485_SendAddressByte(UNMATCH_ADDRSS1);
    RS485_SendDataByte(g_u8SendDataGroup2, 10);

    printf("Send Address %x and data 20~29\n", MATCH_ADDRSS2);
    RS485_SendAddressByte(MATCH_ADDRSS2);
    RS485_SendDataByte(g_u8SendDataGroup3, 10);

    printf("Send Address %x and data 30~39\n", UNMATCH_ADDRSS2);
    RS485_SendAddressByte(UNMATCH_ADDRSS2);
    RS485_SendDataByte(g_u8SendDataGroup4, 10);

    printf("\nTransfer Done\n");

}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(UART1_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD */
    SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
    SYS->P3_MFP |= (SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0);

    /* Set P1 multi-function pins for UART1 RXD and TXD */
    SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
    SYS->P1_MFP |= (SYS_MFP_P12_RXD1 | SYS_MFP_P13_TXD1);

    /* Set P0 multi-function pins for UART1 RTS */
    SYS->P0_MFP = SYS->P0_MFP & (~SYS_MFP_P01_Msk) | SYS_MFP_P01_RTS1;


}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 module */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

void UART1_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART1 module */
    SYS_ResetModule(UART1_RST);

    /* Configure UART1 and set UART1 Baudrate */
    UART_Open(UART1, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init UART1 for testing */
    UART1_Init();

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\n\nCPU @ %dHz\n", SystemCoreClock);

    printf("\n\nUART Sample Program\n");

    /* UART RS485 sample master function */
    RS485_9bitModeMaster();

    while(1);

}
