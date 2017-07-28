/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef STDINT_H
#define STDINT_H

#if defined __C51__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef uint32_t uint64_t[2];

typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef int32_t int64_t[2];


#elif defined __ICC8051__

/* Fixed size types. These are all optional. */
#ifdef __INT8_T_TYPE__
  typedef __INT8_T_TYPE__   int8_t;
  typedef __UINT8_T_TYPE__ uint8_t;
#endif /* __INT8_T_TYPE__ */

#ifdef __INT16_T_TYPE__
  typedef __INT16_T_TYPE__   int16_t;
  typedef __UINT16_T_TYPE__ uint16_t;
#endif /* __INT16_T_TYPE__ */

#ifdef __INT32_T_TYPE__
  typedef __INT32_T_TYPE__   int32_t;
  typedef __UINT32_T_TYPE__ uint32_t;
#endif /* __INT32_T_TYPE__ */

#ifdef __INT64_T_TYPE__
  #pragma language=save
  #pragma language=extended
  typedef __INT64_T_TYPE__   int64_t;
  typedef __UINT64_T_TYPE__ uint64_t;
  #pragma language=restore
#endif /* __INT64_T_TYPE__ */

#endif

#endif
