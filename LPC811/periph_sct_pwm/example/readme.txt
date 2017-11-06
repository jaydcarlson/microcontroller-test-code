State Configurable Timer (SCT) PWM Example
==========================================

Example Description
-------------------
This example, uses the SCT PWM driver to create 2 independent PWMs (running at
the same frequency). The PWM1 is used to output a square wave to an Output pin
and PWM2 is used to control the brightness of the LED, the brightness goes
from 0% to 100% in steps of 0.5% every 20 Milliseconds and goes down to 0% in
the same step. Connect an oscilloscope to the PWM OUT; the waveform displayed
on the o-scope will change duty cycle increasing from 0% to 100% in steps of
10% every second.

Special Connection Requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:
PWM OUT - J6 Pin 6 PIO0_6

Board [NXP_812_MAX]:
PWM OUT - J2 INT Pin PIO0_6

Board [NXP_LPCXPRESSO_824]:
There are no special connection requirements for this example.

Build procedures:
Visit the LPCOpen Quick start guide at
[http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides]
to get started building LPCOpen projects.
