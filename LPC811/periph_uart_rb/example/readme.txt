UART Interrupt with Ring Buffers Example
========================================

Example Description
-------------------
The UART example shows how to use the UART in interrupt mode with transmit
and receive ring buffers.

To use the example, connect a serial cable to the board's RS232/UART port and
start a terminal program to monitor the port.  The terminal program on the host
PC should be setup for 115200-8-N-1.
Once the example is started, a brief message is sent to the terminal. Any data
received will be displayed on the terminal.

Special connection requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:

Board [NXP_812_MAX]:
See LPC812_max-UART.txt for UART configuration details.

Board [NXP_LPCXPRESSO_824]:
See LPC824_xpresso-UART.txt for UART configuration details.

Build procedures:
Visit the <a href="http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides">LPCOpen quickstart guides</a>
to get started building LPCOpen projects.
