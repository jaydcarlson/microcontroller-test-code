/****************************************************************************
 * @file     SysInit.c
 * @version  V1.09
 * @Date     2017/07/28-18:36:52 
 * @brief    NuMicro generated code file
 *
 * Copyright (C) 2013-2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU: M0516LAN(LQFP48)
Pin Configuration:
Pin 5: RXD
Pin 19: PWM0
Pin 20: PWM1
Pin 21: PWM2
Pin 30: ICE_CLK
Pin 31: ICE_DAT
Pin 37: P0.3
Pin 38: P0.2
Pin 39: P0.1
Pin 40: P0.0
Module Configuration:
RXD(Pin:5)
PWM0(Pin:19)
PWM1(Pin:20)
PWM2(Pin:21)
ICE_CLK(Pin:30)
ICE_DAT(Pin:31)
P0.0(Pin:40)
P0.1(Pin:39)
P0.2(Pin:38)
P0.3(Pin:37)
GPIO Configuration:
P0.0: P0.0(Pin:40)
P0.1: P0.1(Pin:39)
P0.2: P0.2(Pin:38)
P0.3: P0.3(Pin:37)
P2.0: PWM0(Pin:19)
P2.1: PWM1(Pin:20)
P2.2: PWM2(Pin:21)
P3.0: RXD(Pin:5)
P4.6: ICE_CLK(Pin:30)
P4.7: ICE_DAT(Pin:31)
********************/

#include "M051Series.h";
/*
 * @brief This function provides the configued MFP registers
 * @param None
 * @return None
 */
void SYS_Init(void)
{
    //SYS->P0_MFP = 0x00000000;
    //SYS->P1_MFP = 0x00000000;
    //SYS->P2_MFP = 0x00000700;
    //SYS->P3_MFP = 0x00000001;
    //SYS->P4_MFP = 0x000000C0;

    int test;

    //If the defines do not exist in your project, please refer to the related sys.h in the sys_h folder appended to the tool package.
    SYS->P0_MFP = 0x00000000;
    SYS->P1_MFP = 0x00000000;
    SYS->P2_MFP = SYS_MFP_P22_PWM2 | SYS_MFP_P21_PWM1 | SYS_MFP_P20_PWM0;
    SYS->P3_MFP = SYS_MFP_P30_RXD;
    SYS->P4_MFP = SYS_MFP_P47_ICE_DAT | SYS_MFP_P46_ICE_CLK;

    return;
}

/*** (C) COPYRIGHT 2013-2017 Nuvoton Technology Corp. ***/