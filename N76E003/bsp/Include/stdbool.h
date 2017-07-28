/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef STDBOOL_H
#define STDBOOL_H

#if defined __C51__

typedef bit bool;
enum{
  false = 0,
  true = 1,
};

#elif defined __ICC8051__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef __cplusplus

#define bool _Bool
#define true 1
#define false 0

#define __bool_true_false_are_defined 1

#endif /* !__cplusplus */

#else  // __SLS_IDE__ : Macros defined to remove syntax errors within Simplicity Studio

typedef bit bool;
enum{
  false = 0,
  true = 1,
};

#endif

#endif //STDBOOL_H

