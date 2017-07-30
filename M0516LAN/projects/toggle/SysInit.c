/****************************************************************************
 * @file     SysInit.c
 * @version  V1.09
 * @Date     2017/07/28-20:02:33 
 * @brief    NuMicro generated code file
 *
 * Copyright (C) 2013-2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU: M0516LAN(LQFP48)
Pin Configuration:
Pin 30: ICE_CLK
Pin 31: ICE_DAT
Pin 40: P0.0
Module Configuration:
ICE_CLK(Pin:30)
ICE_DAT(Pin:31)
P0.0(Pin:40)
GPIO Configuration:
P0.0: P0.0(Pin:40)
P4.6: ICE_CLK(Pin:30)
P4.7: ICE_DAT(Pin:31)
********************/

#include "M051Series.h"

/*
 * @brief This function provides the configued MFP registers
 * @param None
 * @return None
 */
void SYS_Init(void)
{
    SYS_UnlockReg(); // this is stupid
    CLK_SetCoreClock(50000000U); // full speed, plz!
    
    //SYS->P0_MFP = 0x00000000;
    //SYS->P1_MFP = 0x00000000;
    //SYS->P2_MFP = 0x00000000;
    //SYS->P3_MFP = 0x00000000;
    //SYS->P4_MFP = 0x000000C0;

    //If the defines do not exist in your project, please refer to the related sys.h in the sys_h folder appended to the tool package.
    SYS->P0_MFP = 0x00000000;
    SYS->P1_MFP = 0x00000000;
    SYS->P2_MFP = 0x00000000;
    SYS->P3_MFP = 0x00000000;
    SYS->P4_MFP = SYS_MFP_P47_ICE_DAT | SYS_MFP_P46_ICE_CLK;

    return;
}

/*** (C) COPYRIGHT 2013-2017 Nuvoton Technology Corp. ***/