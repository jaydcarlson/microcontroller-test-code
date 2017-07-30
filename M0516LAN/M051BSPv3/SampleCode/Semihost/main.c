/****************************************************************************
* @file     main.c
* @version  V3.00
* $Revision: 2 $
* $Date: 14/01/28 11:44a $
* @brief    M051 Series Semihost Sample Code
*
* @note
* Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*
******************************************************************************/

#include <stdio.h>
#include "M051Series.h"


/*---------------------------------------------------------------------------------------------------------*/
/* Main Function                                                                                            */
/*---------------------------------------------------------------------------------------------------------*/

int32_t main()
{
    int8_t item;

    /*
        To enable semihost, user must define "DEBUG_ENABLE_SEMIHOST" constant when build code with M051Series BSP.
        This sample code is used to show how to print message/getchar on IDE debug environment.
        It will echo all input character back on UART #1 of KEIL IDE.

        In KEIL MDK, user need to open "View->Serial Window->UART #1" windows in debug mode.
        In IAR Workbench, user need to open "View->Terminal I/O" in debug mode.

        NOTE1: HardFault_Handler handler is implemented in retarget.c when semihost enabled.
        NOTE2: Semihost only works with Nuvoton NuLink ICE Dongle.
    */

    printf("\n Start SEMIHOST test: \n");

    while(1)
    {
        /* Get input character */
        item = getchar();

        /* Print input character back */
        printf("%c\n", item);
    }
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/



