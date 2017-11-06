#include <msp430.h> 
#include <cs.h>
#include <eusci_a_uart.h>
#include <gpio.h>
#include <pmm.h>
#include <timer_b.h>

#define F_CLK   2000000

#define TIMER_PERIOD 255
#define DUTY_CYCLE1  255
#define DUTY_CYCLE2  255

uint8_t RXData;
uint8_t data[513];
int16_t index = -1;

uint8_t address = 1;

//******************************************************************************
//
//This is the USCI_A0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void EUSCI_A0_ISR(void)
{
    P1OUT = 0x01;
    if(EUSCI_A_UART_queryStatusFlags(EUSCI_A0_BASE, UCBRK))
    {
        index = 0;
    }

    switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            RXData = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
    }

    if(index >= 0)
    {
        data[index++] = RXData;
    }

    if(index > 511)
    {
        Timer_B_setCompareValue(TIMER_B0_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_1, 255-data[address+2]);
        Timer_B_setCompareValue(TIMER_B0_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_2, 255-data[address+3]);
        index = -1;
    }

    P1OUT = 0x00;
}


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    CS_initClockSignal(
        CS_FLLREF,
        CS_REFOCLK_SELECT,
        CS_CLOCK_DIVIDER_1
        );

    CS_initFLLSettle(
            F_CLK/1000,
            F_CLK/32768
        );

    CS_initClockSignal(
        CS_MCLK,
        CS_DCOCLKDIV_SELECT,
        CS_CLOCK_DIVIDER_1
        );

    P1DIR = 0xff;
    P2DIR = 0xff;

    // Configure UART pins
    //Set P1.0 and P1.1 as Secondary Module Function Input.
    /*

     * Select Port 1
     * Set Pin 0, 1 to input with function, (UCA0TXD/UCA0SIMO, UCA0RXD/UCA0SOMI).
     */
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P1,
        GPIO_PIN6 | GPIO_PIN7,
        GPIO_PRIMARY_MODULE_FUNCTION
        );

    //P4.0 as output with module function
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P2,
        GPIO_PIN0 | GPIO_PIN1,
        GPIO_PRIMARY_MODULE_FUNCTION
        );


    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    //Configure UART
    //SMCLK = 1MHz, Baudrate = 250k
    //UCBRx = 4, UCBRFx = 0, UCBRSx = 0, UCOS16 = 0
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = F_CLK/250000;
    param.firstModReg = 0;
    param.secondModReg = 0;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    EUSCI_A_UART_init(EUSCI_A0_BASE, &param);

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE,
                                EUSCI_A_UART_RECEIVE_INTERRUPT);

    // Enable USCI_A0 RX interrupt
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,
                                 EUSCI_A_UART_RECEIVE_INTERRUPT);
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,
                                 EUSCI_A_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT);
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,
                                     EUSCI_A_UART_BREAKCHAR_INTERRUPT);
    __enable_interrupt();

    //Start timer
    Timer_B_initUpModeParam timerParam = {0};
    timerParam.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;
    timerParam.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;
    timerParam.timerPeriod = TIMER_PERIOD;
    timerParam.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_DISABLE;
    timerParam.captureCompareInterruptEnable_CCR0_CCIE =
        TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE;
    timerParam.timerClear = TIMER_B_DO_CLEAR;
    timerParam.startTimer = true;
    Timer_B_initUpMode(TIMER_B0_BASE, &timerParam);

    //Initialize compare mode to generate PWM1
    Timer_B_initCompareModeParam initComp1Param = {0};
    initComp1Param.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_1;
    initComp1Param.compareInterruptEnable =
        TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initComp1Param.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    initComp1Param.compareValue = DUTY_CYCLE1;
    Timer_B_initCompareMode(TIMER_B0_BASE, &initComp1Param);

    //Initialize compare mode to generate PWM2
    Timer_B_initCompareModeParam initComp2Param = {0};
    initComp2Param.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_2;
    initComp2Param.compareInterruptEnable =
        TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initComp2Param.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    initComp2Param.compareValue = DUTY_CYCLE2;
    Timer_B_initCompareMode(TIMER_B0_BASE, &initComp2Param);

    for(;;)
    {
        _low_power_mode_0();
//        LPM0;
    }
}
