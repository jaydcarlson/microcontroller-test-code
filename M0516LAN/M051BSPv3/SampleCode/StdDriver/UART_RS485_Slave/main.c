/****************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 10 $
 * $Date: 15/05/22 2:59p $
 * @brief    Transmit and receive data in UART RS485 mode.
 *           This sample code needs to work with UART_RS485_Master.
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"


#define PLL_CLOCK           50000000


#define IS_USE_RS485NMM   0      //1:Select NMM_Mode , 0:Select AAD_Mode
#define MATCH_ADDRSS1     0xC0
#define MATCH_ADDRSS2     0xA2
#define UNMATCH_ADDRSS1   0xB1
#define UNMATCH_ADDRSS2   0xD3


/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
extern char GetChar(void);
int32_t main(void);
void RS485_HANDLE(void);
void RS485_9bitModeSlave(void);


/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART1_IRQHandler(void)
{
    RS485_HANDLE();
}

/*---------------------------------------------------------------------------------------------------------*/
/* RS485 Callback function                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_HANDLE()
{
    volatile uint32_t addr = 0;
    volatile uint32_t u32IntSts = UART1->ISR;

    /* RLS INT & RDA INT */  //For RS485 Detect Address
    if((u32IntSts & UART_ISR_RLS_INT_Msk) && (u32IntSts & UART_ISR_RDA_INT_Msk))
    {
        if(UART1->FSR & UART_FSR_RS485_ADD_DETF_Msk)    /* ADD_IF, RS485 mode */
        {
            addr = UART1->RBR;
            UART_RS485_CLEAR_ADDR_FLAG(UART1);          /* clear ADD_IF flag */
            printf("\nAddr=0x%x,Get:", addr);

#if (IS_USE_RS485NMM ==1) //RS485_NMM

            /* if address match, enable RX to receive data, otherwise to disable RX */
            /* In NMM mode, user can decide multi-address filter */
            /* In AAD mode, only one address can set */
            if((addr == MATCH_ADDRSS1) || (addr == MATCH_ADDRSS2))
            {
                UART1->FCR &= ~ UART_FCR_RX_DIS_Msk;  /* Enable RS485 RX */
            }
            else
            {
                printf("\n");
                UART1->FCR |= UART_FCR_RX_DIS_Msk;    /* Disable RS485 RX */
                UART1->FCR |= UART_FCR_RFR_Msk;       /* Clear data from RX FIFO */
            }
#endif
        }
    }
    else if((u32IntSts & UART_ISR_RDA_INT_Msk) || (u32IntSts & UART_ISR_TOUT_INT_Msk))  /* Rx Ready or Time-out INT */
    {
        /* Handle received data */
        printf("%d,", UART1->RBR);
    }

    else if(u32IntSts & UART_ISR_BUF_ERR_INT_Msk)     /* Buffer Error INT */
    {
        printf("\nBuffer Error...\n");
        UART_ClearIntFlag(UART1, UART_ISR_BUF_ERR_INT_Msk);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Receive Test  (IS_USE_RS485NMM: 0:AAD  1:NMM)                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_9bitModeSlave()
{

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
    printf("|           RS485  Function Test (9-bit Slave)              |\n");
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

    /* Set Data Format, Only need parity enable whenever parity ODD/EVEN */
    UART_SetLine_Config(UART1, 0, UART_WORD_LEN_8, UART_PARITY_EVEN, UART_STOP_BIT_1);

    /* Set RTS pin active level as high level active */
    UART1->MCR &= ~UART_MCR_LEV_RTS_Msk;
    UART1->MCR |= UART_RTS_IS_HIGH_LEV_ACTIVE;

#if(IS_USE_RS485NMM == 1)

    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|    Normal Multidrop Operation Mode                        |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function is used to test 9-bit slave mode.            |\n");
    printf("| Only Address %x and %x,data can receive                   |\n", MATCH_ADDRSS1, MATCH_ADDRSS2);
    printf("+-----------------------------------------------------------+\n");

    /* Set RX_DIS enable before set RS485-NMM mode */
    UART1->FCR |= UART_FCR_RX_DIS_Msk;

    /* Set RS485-NMM Mode */
    UART_SelectRS485Mode(UART1, UART_ALT_CSR_RS485_NMM_Msk | UART_ALT_CSR_RS485_AUD_Msk, 0);

    /* Set RS485 address detection enable */
    UART1->ALT_CSR |= UART_ALT_CSR_RS485_ADD_EN_Msk;

#else
    printf("Auto Address Match Operation Mode\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function is used to test 9-bit slave mode.            |\n");
    printf("|    Auto Address Match Operation Mode                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|Only Address %x,data can receive                           |\n", MATCH_ADDRSS1);
    printf("+-----------------------------------------------------------+\n");

    /* Set RS485-AAD Mode and address match is 0xC0 */
    UART_SelectRS485Mode(UART1, UART_ALT_CSR_RS485_AAD_Msk | UART_ALT_CSR_RS485_AUD_Msk, MATCH_ADDRSS1);

    /* Set RS485 address detection enable */
    UART1->ALT_CSR |= UART_ALT_CSR_RS485_ADD_EN_Msk;

#endif

    /* Enable RDA\RLS\Time-out Interrupt */
    UART_ENABLE_INT(UART1, (UART_IER_RDA_IEN_Msk | UART_IER_RLS_IEN_Msk | UART_IER_RTO_IEN_Msk));

    /* Enable UART1 IRQ */
    NVIC_EnableIRQ(UART1_IRQn);

    printf("Ready to receive data...(Press any key to stop test)\n");
    GetChar();

    /* Flush Rx FIFO */
    UART1->FCR |= UART_FCR_RFR_Msk;

    /* Disable RDA\RLS\Time-out Interrupt */
    UART_DISABLE_INT(UART1, (UART_IER_RDA_IEN_Msk | UART_IER_RLS_IEN_Msk | UART_IER_RTO_IEN_Msk));

    printf("\nEnd test\n");

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
    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

void UART1_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART1 */
    SYS_ResetModule(UART1_RST);

    /* Configure UART1 and set UART1 Baudrate */
    UART_Open(UART1, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
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

    /* UART RS485 sample slave function */
    RS485_9bitModeSlave();
    
    while(1);

}
