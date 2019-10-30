/*!
 *****************************************************************************
 * @file:    ADuCM355.h
 * @brief:   CMSIS Cortex-M3 Core Peripheral Access Layer Header File for
 *           ADI ADuCM355 Device Series
 * @version: $Revision: 32405 $
 * @date:    $Date: 2015-10-13 14:24:03 -0400 (Tue, 13 Oct 2015) $
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2010-2016 Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  - Modified versions of the software must be conspicuously marked as such.
  - This software is licensed solely and exclusively for use with processors
    manufactured by or for Analog Devices, Inc.
  - This software may not be combined or merged with other code in any manner
    that would cause the software to become subject to terms and conditions
    which differ from those listed here.
  - Neither the name of Analog Devices, Inc. nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.
  - The use of this software may or may not infringe the patent rights of one
    or more patent holders.  This license does not release you from the
    requirement that you obtain separate licenses from these patent holders
    to use this software.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
TITLE, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
NO EVENT SHALL ANALOG DEVICES, INC. OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, PUNITIVE OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, DAMAGES ARISING OUT OF CLAIMS OF INTELLECTUAL
PROPERTY RIGHTS INFRINGEMENT; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

/*!  \addtogroup MMR_Layout MMR/ISR Mappings
 *  @{
 */

#ifndef __ADUCM355_H__
#define __ADUCM355_H__
/* verify presence of a supported compiler (Keil or IAR at this time) */
#if !defined(__ICCARM__) && !defined(__CC_ARM)  && !defined (__ADSPGCC__) && !defined(M355VERI_EN)
#error "No supported compiler found, please install one of the minimum required compilers."
#endif

/* verify minimum required IAR compiler */
#ifdef __ICCARM__
#define MIN_CC_VERSION 07010001  /* known value for release 7.10.1 */
#if (MIN_CC_VERSION > __VER__)
#error "Unsupported compiler version, please install minimum required compiler version."
#endif
#endif

#define _LANGUAGE_C
#include <ADuCM355_cdef.h>
#include <ADuCM355_device.h>


/* pickup register bitfield and bit mask macros */
#include <ADuCM355_bitm.h>

#define __MPU_PRESENT          0u  /*!< MPU is not present                   */
#define __FPU_PRESENT          0u  /*!< FPU is not present                   */
#define __NVIC_PRIO_BITS       3u  /*!< Number of Bits for Priority Levels   */
#define __Vendor_SysTickConfig 0  /*!< 1 if different SysTick Config is used */
#include "core_cm3.h"




#endif /* __ADUCM355_H__ */

/*
** EOF
*/

/*@}*/
