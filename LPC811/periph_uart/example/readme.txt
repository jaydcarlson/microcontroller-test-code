UART Test with LEDs
========================================

Example Description
-------------------
The UART example shows how to use the UART.

To use the example, connect a serial cable to the board's RS232/UART port and
start a terminal program to monitor the port.  The terminal program on the host
PC should be setup for 115200-8-N-1.
Once the example is started, a brief message is sent to the terminal. Any data
received will be displayed on the terminal.

Special connection requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:

Board [NXP_812_MAX]:
See LPC812_max-UART.txt for details on configuring the UART.

Board [NXP_LPCXPRESSO_824]:
Connect the board to a base board. The output will appear at USB-mini port X3.
Make sure that the jumpers on J7 are configured correctly.
Or, connect TX, RX and GND from J2 [Arduino Digital Header] to an FTDI Cable.
LPC824            FTDI cable
 GND: J1-4         black
 RX:  J2-8 (D0)    orange
 TX:  J2-7 (D1)    yellow

Build procedures:
Visit the <a href="http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides">LPCOpen quickstart guides</a>
to get started building LPCOpen projects.
