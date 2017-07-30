/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * $Revision: 5 $
 * $Date: 14/11/14 10:17a $
 * @brief    M051 Series I2C Driver Sample Code for Wake-up (Slave)
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M051Series.h"

#define PLLCON_SETTING  CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK       50000000

uint32_t slave_buff_addr;
uint8_t g_au8SlvData[256];
uint8_t g_au8SlvRxData[3];
uint8_t g_u8SlvPWRDNWK, g_u8SlvI2CWK;
/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint8_t g_u8DeviceAddr;
volatile uint8_t g_u8SlvDataLen;

typedef void (*I2C_FUNC)(uint32_t u32Status);

static I2C_FUNC s_I2C0HandlerFn = NULL;

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C0 IRQ Handler                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C0_IRQHandler(void)
{
    uint32_t u32Status;

    /* Check I2C Wake-up interrupt flag set or not */
    if((I2C0->I2CWKUPSTS) == 0x01)
    {
        /* Clear I2C Wake-up interrupt flag */
        I2C0->I2CWKUPSTS = 1;

			  g_u8SlvI2CWK = 1;

        return;
    }

    u32Status = I2C0->I2CSTATUS;

    if(I2C0->I2CTOC & I2C_I2CTOC_TIF_Msk)
    {
        /* Clear I2C0 Timeout Flag */
        I2C0->I2CTOC |= I2C_I2CTOC_TIF_Msk;
    }
    else
    {
        if(s_I2C0HandlerFn != NULL)
            s_I2C0HandlerFn(u32Status);
    }
}
/*---------------------------------------------------------------------------------------------------------*/
/*  Power Wake-up IRQ Handler                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void PWRWU_IRQHandler(void)
{
    /* Check system power down mode wake-up interrupt flag */
    if(((CLK->PWRCON) & CLK_PWRCON_PD_WU_STS_Msk) != 0)
    {
        /* Clear system power down wake-up interrupt flag */
        CLK->PWRCON |= CLK_PWRCON_PD_WU_STS_Msk;
        
			  g_u8SlvPWRDNWK = 1;
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Slave Transmit/Receive Callback Function                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_SlaveTRx(uint32_t u32Status)
{
    if(u32Status == 0x60)                       /* Own SLA+W has been receive; ACK has been return */
    {
        g_u8SlvDataLen = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0x80)                 /* Previously address with own SLA address
                                                   Data has been received; ACK has been returned*/
    {
        g_au8SlvRxData[g_u8SlvDataLen] = (unsigned char)(I2C0->I2CDAT);
        g_u8SlvDataLen++;

        if(g_u8SlvDataLen == 2)
        {
            slave_buff_addr = (g_au8SlvRxData[0] << 8) + g_au8SlvRxData[1];
        }
        if(g_u8SlvDataLen == 3)
        {
            g_au8SlvData[slave_buff_addr] = g_au8SlvRxData[2];
            g_u8SlvDataLen = 0;
        }
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0xA8)                  /* Own SLA+R has been receive; ACK has been return */
    {

        I2C0->I2CDAT = g_au8SlvData[slave_buff_addr];
        slave_buff_addr++;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0xC0)                 /* Data byte or last data in I2CDAT has been transmitted
                                                   Not ACK has been received */
    {
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0x88)                 /* Previously addressed with own SLA address; NOT ACK has
                                                   been returned */
    {
        g_u8SlvDataLen = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else if(u32Status == 0xA0)                 /* A STOP or repeated START has been received while still
                                                   addressed as Slave/Receiver*/
    {
        g_u8SlvDataLen = 0;
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK->PWRCON |= CLK_PWRCON_OSC22M_EN_Msk;

    /* Waiting for Internal RC clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_OSC22M_STB_Msk));

    /* Switch HCLK clock source to Internal RC */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLK_S_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_HIRC;

    /* Enable external XTAL 12MHz clock */
    CLK->PWRCON |= CLK_PWRCON_XTL12M_EN_Msk;

    /* Waiting for external XTAL clock ready */
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_XTL12M_STB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCON = PLLCON_SETTING;
    while(!(CLK->CLKSTATUS & CLK_CLKSTATUS_PLL_STB_Msk));
    CLK->CLKSEL0 &= (~CLK_CLKSEL0_HCLK_S_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLK_S_PLL;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /* Enable UART module clock */
    CLK->APBCLK |= CLK_APBCLK_UART0_EN_Msk | CLK_APBCLK_I2C0_EN_Msk;

    /* Select UART module clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART_S_Msk;
    CLK->CLKSEL1 |= CLK_CLKSEL1_UART_S_HXT;

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set P3 multi-function pins for UART0 RXD and TXD, and set P3.4 and P3.5 for I2C0 SDA and SCL */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P34_SDA0 | SYS_MFP_P35_SCL0;
}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART IP */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_UART0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_UART0_RST_Msk;

    /* Configure UART0 and set UART0 Baudrate */
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HXT, 115200);
    UART0->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}

void I2C0_Init(void)
{
    /* Reset I2C0 */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_I2C0_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_I2C0_RST_Msk;

    /* Enable I2C0 Controller */
    I2C0->I2CON |= I2C_I2CON_ENS1_Msk;

    /* I2C0 clock divider, I2C Bus Clock = PCLK / (4*125) = 100kHz */
    I2C0->I2CLK = 125 - 1;

    /* Get I2C0 Bus Clock */
    printf("I2C clock %d Hz\n", (SystemCoreClock / (((I2C0->I2CLK) + 1) << 2)));

    /* Set I2C0 4 Slave Addresses */
    /* Slave Address : 0x15 */
    I2C0->I2CADDR0 = (I2C0->I2CADDR0 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x15 << I2C_I2CADDR_I2CADDR_Pos);
    /* Slave Address : 0x35 */
    I2C0->I2CADDR1 = (I2C0->I2CADDR1 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x35 << I2C_I2CADDR_I2CADDR_Pos);
    /* Slave Address : 0x55 */
    I2C0->I2CADDR2 = (I2C0->I2CADDR2 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x55 << I2C_I2CADDR_I2CADDR_Pos);
    /* Slave Address : 0x75 */
    I2C0->I2CADDR3 = (I2C0->I2CADDR3 & ~I2C_I2CADDR_I2CADDR_Msk) | (0x75 << I2C_I2CADDR_I2CADDR_Pos);

    /* Set I2C0 4 Slave Addresses Mask Bits*/
    /* Slave Address Mask Bits: 0x01 */
    I2C0->I2CADM0 = (I2C0->I2CADM0 & ~I2C_I2CADM_I2CADM_Msk) | (0x01 << I2C_I2CADM_I2CADM_Pos);
    /* Slave Address Mask Bits: 0x04 */
    I2C0->I2CADM1 = (I2C0->I2CADM1 & ~I2C_I2CADM_I2CADM_Msk) | (0x04 << I2C_I2CADM_I2CADM_Pos);
    /* Slave Address Mask Bits: 0x01 */
    I2C0->I2CADM2 = (I2C0->I2CADM2 & ~I2C_I2CADM_I2CADM_Msk) | (0x01 << I2C_I2CADM_I2CADM_Pos);
    /* Slave Address Mask Bits: 0x04 */
    I2C0->I2CADM3 = (I2C0->I2CADM3 & ~I2C_I2CADM_I2CADM_Msk) | (0x04 << I2C_I2CADM_I2CADM_Pos);

    /* Enable I2C0 interrupt and set corresponding NVIC bit */
    I2C0->I2CON |= I2C_I2CON_EI_Msk;
    NVIC_EnableIRQ(I2C0_IRQn);
}

void I2C0_Close(void)
{
    /* Disable I2C0 interrupt and clear corresponding NVIC bit */
    I2C0->I2CON &= ~I2C_I2CON_EI_Msk;
    NVIC_DisableIRQ(I2C0_IRQn);

    /* Disable I2C0 and close I2C0 clock */
    I2C0->I2CON &= ~I2C_I2CON_ENS1_Msk;
    CLK->APBCLK &= ~CLK_APBCLK_I2C0_EN_Msk;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t i;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /*
        This sample code is I2C SLAVE mode and it simulates EEPROM function
    */
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("| M05xx I2C Driver Sample Code (Slave) for wake-up & access Slave test |\n");
    printf("|                                                                      |\n");
    printf("| I2C Master (I2C0) <---> I2C Slave(I2C0)                              |\n");
    printf("+----------------------------------------------------------------------+\n");

    printf("Configure I2C0 as a slave.\n");
    printf("The I/O connection for I2C0:\n");
    printf("I2C0_SDA(P3.4), I2C0_SCL(P3.5)\n");

    /* Init I2C0 */
    I2C0_Init();

    for(i = 0; i < 0x100; i++)
    {
        g_au8SlvData[i] = 0;
    }

    /* I2C function to Transmit/Receive data as slave */
    s_I2C0HandlerFn = I2C_SlaveTRx;
		
    /* Set I2C0 enter Not Address SLAVE mode */
    I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI_AA);

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable power wake-up interrupt */
    CLK->PWRCON |= CLK_PWRCON_PD_WU_INT_EN_Msk;
    NVIC_EnableIRQ(PWRWU_IRQn);
    g_u8SlvPWRDNWK = 0;
		
    /* Enable I2C wake-up */
    I2C0-> I2CWKUPCON |= I2C_I2CWKUPCON_WKUPEN_Msk;
    g_u8SlvI2CWK = 0;
		
    /* Enable Chip enter power down mode */
    CLK->PWRCON |= CLK_PWRCON_PD_WAIT_CPU_Msk;
	
    /* Processor use deep sleep */
    SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;

    /* System power down enable */
    CLK->PWRCON |= CLK_PWRCON_PWR_DOWN_EN_Msk;

    printf("\n");
    printf("Enter PD 0x%x 0x%x\n", I2C0->I2CON , I2C0->I2CSTATUS);

    printf("\n");
    printf("CHIP enter power down status.\n");
    /* Waiting for UART printf finish*/
    while(((UART0->FSR) & UART_FSR_TE_FLAG_Msk) == 0);

    if(((I2C0->I2CON)&I2C_I2CON_SI_Msk) != 0)
    {
        I2C_SET_CONTROL_REG(I2C0, I2C_I2CON_SI);
    }

    /*  Use WFI instruction to idle the CPU. NOTE:
        If ICE is attached, system will wakeup immediately because ICE is a wakeup event. */
    __WFI();
    __NOP();
    __NOP();
    __NOP();

    while((g_u8SlvPWRDNWK & g_u8SlvI2CWK) == 0);		
    printf("Power-down Wake-up INT 0x%x\n", ((CLK->PWRCON) & CLK_PWRCON_PD_WU_STS_Msk));		
		printf("I2C0 WAKE INT 0x%x\n", I2C0->I2CWKUPSTS);
		
		
		
    /* Disable power wake-up interrupt */
    CLK->PWRCON &= ~CLK_PWRCON_PD_WU_INT_EN_Msk;
    NVIC_DisableIRQ(PWRWU_IRQn);

    /* Lock protected registers */
    SYS_LockReg();

    printf("\n");
    printf("Slave wake-up from power down status.\n");

    printf("\n");
    printf("Slave Waiting for receiving data.\n");

    while(1);
}



