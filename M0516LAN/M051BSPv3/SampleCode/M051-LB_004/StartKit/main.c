/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2014 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "M051Series.h"
#include "lcd_Driver.h"
#include "EEPROM_24LC64.h"
#include "spi_flash.h"

#define PLLCON_SETTING      CLK_PLLCON_50MHz_HXT
#define PLL_CLOCK           50000000

void Delay(int32_t ms)
{
    int32_t i;

    for(i = 0; i < ms; i++)
        CLK_SysTickDelay(1000);/* SysTick to generate the delay time and the UNIT is in us.  */
}

void EINT0_IRQHandler(void)
{
    /* Clear GPIO Pin Interrupt Flag */
    GPIO_CLR_INT_FLAG(P3, 0x1 << 2);

    /* Toggle PWM3 enable/disable */
    PWM_EnableOutput(PWMA, 1 << 3);

    printf("EINT0 Interrupt!\n");
}

void TMR0_IRQHandler(void)
{
    /* Clears Timer time-out interrupt flag */
    TIMER_ClearIntFlag(TIMER0);
}

void SPIFLASH_Init(void)
{
    /* Configure SPI1 as a master, MSB first, 8-bit transaction, SPI Mode-0 timing, clock is 2MHz */
    SPI_Open(SPI1, SPI_MASTER, SPI_MODE_0, 8, 2000000);

    /* Enable the automatic hardware slave select function. Select the SS0 pin and configure as low-active. */
    SPI_EnableAutoSS(SPI1, SPI_SS, SPI_SS_ACTIVE_LOW);
    SPI_EnableFIFO(SPI1, 2, 2);

    /* Wait ready */
    SpiFlash_WaitReady(SPI1);
}

void PWM_Init(void)
{
    /* PWM0 = 2Hz, duty cycle = 25 % */
    /* PWM1 = 2Hz, duty cycle = 50 % */
    /* PWM2 = 4Hz, duty cycle = 25 % */
    /* PWM3 = 4Hz, duty cycle = 50 % */
    /* Config PWM generator and get the nearest frequency in edge aligned auto-reload mode */
    PWM_ConfigOutputChannel(PWMA, 0, 2, 25);
    PWM_ConfigOutputChannel(PWMA, 1, 2, 50);
    PWM_ConfigOutputChannel(PWMA, 2, 4, 25);
    PWM_ConfigOutputChannel(PWMA, 3, 4, 50);

    /* PWMA pin output enabled */
    PWM_EnableOutput(PWMA, 0xF);

    /* Start PWMA module */
    PWM_Start(PWMA, 0xF);

}

void TMR0_Init(void)
{
    /* Configure timer to operate in periodic mode and frequency = 10Hz*/
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 10);

    /* Enable the Timer time-out interrupt */
    TIMER_EnableInt(TIMER0);

    /* Start Timer counting */
    TIMER_Start(TIMER0);

    /* Enable TMR0 Interrupt */
    NVIC_EnableIRQ(TMR0_IRQn);
}

void EINT0_Init(void)
{
    /* Debounce function control */
    GPIO_SET_DEBOUNCE_TIME(GPIO_DBCLKSRC_HCLK, GPIO_DBCLKSEL_32768);
    /* Enable Pin De-bounce Function */
    GPIO_ENABLE_DEBOUNCE(P3, 0x1 << 2);

    /* Configure external interrupt */
    GPIO_EnableInt(P3, 2, GPIO_INT_FALLING);
    /* Enable EINT0 Interrupt */
    NVIC_EnableIRQ(EINT0_IRQn);
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

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(SPI0_MODULE);
    CLK_EnableModuleClock(SPI1_MODULE);
    CLK_EnableModuleClock(ADC_MODULE);
    CLK_EnableModuleClock(I2C0_MODULE);
    CLK_EnableModuleClock(PWM01_MODULE);
    CLK_EnableModuleClock(PWM23_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);

    /* IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1));
    CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL1_ADC_S_HCLK, CLK_CLKDIV_ADC(4));
    CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HXT, 0);
    CLK_SetModuleClock(PWM23_MODULE, CLK_CLKSEL1_PWM23_S_HXT, 0);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0_S_HXT, 0);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;            // PLL
    SystemCoreClock = PLL_CLOCK / 1;        // HCLK
    CyclesPerUs     = PLL_CLOCK / 1000000;  // For SYS_SysTickDelay()

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set P3 multi-function pins for UART0 RXD and TXD. Set P3.4 P3.5 for I2C  */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0 | SYS_MFP_P34_SDA0 | SYS_MFP_P35_SCL0;

    /* Set P1.4, P1.5, P1.6, P1.7 for SPI0 */
    SYS->P1_MFP = SYS_MFP_P14_SPISS0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0;

    /* Set P0.4, P0.5, P0.6, P0.7 for SPI1. Set P0.0 for AD0 */
    SYS->P0_MFP = SYS_MFP_P04_SPISS1 | SYS_MFP_P05_MOSI_1 | SYS_MFP_P06_MISO_1 |
                  SYS_MFP_P07_SPICLK1 | SYS_MFP_P00_AD0;

    /* Set P4.0, P4.1 for PWM0, PWM1, PWM2, PWM3. Set P4.6, P4.7 for ICE */
    SYS->P4_MFP = SYS_MFP_P40_PWM0 | SYS_MFP_P41_PWM1 | SYS_MFP_P42_PWM2 | SYS_MFP_P43_PWM3 |
                  SYS_MFP_P46_ICE_CLK | SYS_MFP_P47_ICE_DAT;

}

/*---------------------------------------------------------------------------------------------------------*/
/* Init UART                                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
void UART0_Init()
{
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}


/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/

int main(void)
{
    uint32_t u32Counter = 0, u32AdcData = 0, u32I2cData, u32LedOn = 0;
    uint32_t u32Id;
    int32_t i32BuzzerCnt;
    char AdcValue[15] = "ADC Value:";
    char TestOk[15] = "Test OK:";
    char strClearAdcValue[15] = "ADC Value:     ";

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init Other peripherals                                                                                  */
    /*---------------------------------------------------------------------------------------------------------*/
    LCD_Init();
    SPIFLASH_Init();
    EEPROM_Init();
    PWM_Init();
    TMR0_Init();
    EINT0_Init();

    /*
        StartKit is used to demo Nu-LB_004 learning board. This sample will test EEPROM, SPI Flash read/write by
        I2C, SPI. And test LED by GPIO and PWM. Test KEY by EINT0. Use ADC to convert the voltage of
        variable resistor by AD0. Generate 4kHz key sound by buzzer with PWM. LCD display is enabled to show working
        message. CPU will be idle by __WFI() when a loop has been done. Timer events (every 100ms) or key events are
        used to wakeup CPU to execute next loop.
    */

    LCD_EnableBackLight();
    LCD_ClearScreen();

    printf("CPU @ %dHz\n", SystemCoreClock);

    // SPI0 test
    LCD_Print(0, "Welcome! Nuvoton");
    LCD_Print(1, "This is LB test ");

    i32BuzzerCnt = 1;
    while(1)
    {
        /* Key sound */
        if(PWMA->POE & PWM_POE_PWM3_Msk)
        {
            if(i32BuzzerCnt-- <= 0)
            {
                /* Disable Buzzer */
                PWM_DisableOutput(PWMA, 0x1 << 3);
            }
        }
        else
            i32BuzzerCnt = 1;

        printf("\nTest time: %d\n", u32Counter++);

        /* LED test */
        if(u32Counter % 8 == 0)
            u32LedOn = 0x01;
        GPIO_SET_OUT_DATA(P2, ~u32LedOn); /* Set GPIO Port OUT Data */
        u32LedOn <<= 1;

        /* Check ADC is idle */
        if((ADC->ADCR & ADC_ADCR_ADST_Msk) == 0)
        {
            /* Read the result from last ADC convert */
            u32AdcData = ADC_GET_CONVERSION_DATA(ADC, 0);

            printf("ADC value: %d\n", u32AdcData);
            sprintf(AdcValue + 10, "%d", u32AdcData);
            LCD_Print(3, strClearAdcValue);
            LCD_Print(3, AdcValue);

            /* Set the ADC operation mode as single, input mode as single-end and enable the analog input channel 0 */
            ADC_Open(ADC, ADC_ADCR_DIFFEN_SINGLE_END, ADC_ADCR_ADMD_SINGLE, 0x1);

            /* Power on ADC module */
            ADC_POWER_ON(ADC);

            /* Start A/D conversion */
            ADC_START_CONV(ADC);
        }

        /*I2C test*/
        u32AdcData = (u32Counter + u32AdcData) & 0xFF;
        EEPROM_Write(u32Counter, u32AdcData);/* Write data to EEPROM */
        u32I2cData = EEPROM_Read(u32Counter);/* Read data from EEPROM */
        if(u32I2cData != u32AdcData)
        {
            LCD_Print(2, "I2C fail ");
            while(1);
        }
        else
            printf("I2C address:0x%x, Data:0x%x\n", u32Counter, u32I2cData);

        /*SPI1 test*/
        u32Id = SpiFlash_ReadMidDid(SPI1) & 0xFFFFUL;
        if(u32Id != 0xEF14)  /*Get flash ID*/
        {
            LCD_Print(2, "SPI fail ");
            while(1);
        }

        //Test OK
        sprintf(TestOk + 8, "%d", u32Counter);
        LCD_Print(2, TestOk);

        /* Waiting for events */
        __WFI();
    }
}




