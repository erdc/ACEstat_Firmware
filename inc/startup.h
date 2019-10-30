/*!
 *****************************************************************************
 * @file:    startup.h
 * @brief:   CMSIS Cortex-M3 Core Peripheral Access Layer Header File for
 *           ADI ADuCxxx Device Series
 * @version: $Revision: 29310 $
 * @date:    $Date: 2014-12-18 03:31:03 -0500 (Thu, 18 Dec 2014) $
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2010-2014 Analog Devices, Inc.

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

/*
ATTRIBUTE_INTERRUPT
   If this is available for a compiler, flag that a function is an interrupt
   function. This can allow a compiler do some special handling.
KEEP_VAR(var)
   If this is available for a compiler, flag that "var" should NOT be
   optimised away by the compiler even if the compiler thinks that it is not
   used.
WEAK_PROTO(proto)
   If this is available for a compiler, apply whatever attributes are needed
   to a function prototype ("proto") to flag that the function is a "weak" one.
WEAK_FUNC(func)
   If this is available for a compiler, apply whatever attributes are needed
   to a function definition ("func") to flag that the function is a "weak" one.
VECTOR_SECTION
   A particular setup may have a requirement that the vector table be placed
   in a particular section. This specifies the name of that section
SECTION_PLACE(def,sectionname)
   Place the "def" variable in the named section.
RESET_EXCPT_HNDLR
   A particular setup may have a requirement for a different reset handler.
   This specifies the name of that handler.
ALIGN_VAR
   Align a variable to a specific alignment. Note that some compilers do this
   using pragma which can't be included in a macro expansion.(IAR)
*/

#ifndef __STARTUP_H__
#define __STARTUP_H__

//#include <adi_processor.h>
#include <adi_types.h>

//*****************************************************************************
//
// GCC. GNU Compiler.
//
//*****************************************************************************
#ifdef __GNUC__
#define ATTRIBUTE_INTERRUPT            __attribute__((__interrupt__))
#define KEEP_VAR(var)                  var __attribute__((used))
#define WEAK_PROTO(proto)              __attribute__((weak)) proto
#define WEAK_FUNC(func)                __attribute__((weak)) func
#define VECTOR_SECTION                 ".isr_vector"
#define SECTION_PLACE(def,sectionname) __attribute__ ((section(sectionname))) def
#define RESET_EXCPT_HNDLR ResetISR
#define COMPILER_NAME                  "GNUC"
#endif // __GNUC__

//*****************************************************************************
//
// RV-MDK. Realview Compiler
//
//*****************************************************************************
#ifdef __ARMCC_VERSION
#define ATTRIBUTE_INTERRUPT
#define KEEP_VAR(var)                  var __attribute__((used))
#define WEAK_PROTO(proto)              proto __attribute__((weak))
#define WEAK_FUNC(func)                func
#define VECTOR_SECTION                 "RESET"
#define SECTION_PLACE(def,sectionname) __attribute__ ((section(sectionname))) def
#define RESET_EXCPT_HNDLR              __main
#define COMPILER_NAME                  "ARMCC"

#endif // __ARMCC_VERSION

//*****************************************************************************
//
// EW-ARM. IAR ARM Compiler.
//
//*****************************************************************************
#ifdef __ICCARM__
#define ATTRIBUTE_INTERRUPT
#define KEEP_VAR(var)                  __root var
#define WEAK_PROTO(proto)              __weak proto
#define WEAK_FUNC(func)                __weak func
#define VECTOR_SECTION                 ".intvec"
#define SECTION_PLACE(def,sectionname) def @ sectionname
#define RESET_EXCPT_HNDLR              __iar_program_start
#define COMPILER_NAME                  "ICCARM"

#endif // __ICCARM__

#define ADI_SRAM_RETENTION_SIZE_8K   BITM_PMG_SRAMRET_BNK1EN

#define ADI_SRAM_RETENTION_SIZE_16K  BITM_PMG_SRAMRET_BNK2EN

#include "adi_config.h"

#if !defined(ATTRIBUTE_INTERRUPT) || !defined(KEEP_VAR) || !defined(WEAK_PROTO) || !defined(WEAK_FUNC) || !defined(VECTOR_SECTION) || !defined(SECTION_PLACE) || !defined(RESET_EXCPT_HNDLR)
#error "This compiler is not yet supported"
#endif

//*****************************************************************************
//
// Local helpers for consistent ISR prototypes and implementations.
//
// The only Interrupts that should vector through the OSAL are the driver interrupts for which
// ADI has provided drivers which can operate in both an RTOS and a non-RTOS context.
//
// When operating in an RTOS context interrupts are vectord from the NVIC controller
// to a second level dispatch function known as the OSAL (operating system abstraction layer) dispatch.
// The OSAL dispatch has common code that will interact with the RTOS.
//
// OSAL dispatched interrupts must pass their Interrupt ID (iid) to the common OSAL dispatch.
//
// System interrupts (Reset through SysTick) should never dispatch through the OSAL.
//
// The WEAK_PROTOTYPE and WEAK_FUNCTION macros are used for System interrupts handlers. These
// handlers will always have a 'void' paramater list.
//
// The ADI_WEAK_PROTOTYPE and ADI_WEAK_PROTOTYPE macros will change the declaration of the Driver Interrupts Handlers
// depending on whether or not they are operating in an RTOS context. In an RTOS context the IID (interrupy ID)
// paramater and a driver specific 'void *' paramater are required. In a non-RTOS context there is no OSAL dispatch
// and the paramater list is simply 'void'.
//
//*****************************************************************************
#define WEAK_PROTOTYPE(x) WEAK_PROTO ( void x (void)) ATTRIBUTE_INTERRUPT ;
#define WEAK_FUNCTION(x)  WEAK_FUNC  ( void x (void)) { while(1); }

#if (ADI_CFG_ENABLE_RTOS_SUPPORT == 1)
#define ADI_WEAK_PROTOTYPE(x)      WEAK_PROTO ( void x (uint32_t, void*)) ATTRIBUTE_INTERRUPT ;
#define ADI_WEAK_FUNCTION(x)      WEAK_FUNC  ( void x (uint32_t iid, void* handlerArg)) { while(1); }
#else
#define ADI_WEAK_PROTOTYPE(x)     WEAK_PROTO ( void x (void)) ATTRIBUTE_INTERRUPT ;
#define ADI_WEAK_FUNCTION(x)      WEAK_FUNC  ( void x (void)) { while(1); }
#endif

#ifndef PENDSV_HANDLER
#define PENDSV_HANDLER  PendSV_Handler
#endif
//*****************************************************************************
//
// Forward declaration of the system exceptions.
//
//*****************************************************************************
WEAK_PROTOTYPE( ResetISR                  )
WEAK_PROTOTYPE( NmiSR                     )
WEAK_PROTOTYPE( HardFault_Handler         )
WEAK_PROTOTYPE( MemManage_Handler         )
WEAK_PROTOTYPE( BusFault_Handler          )
WEAK_PROTOTYPE( UsageFault_Handler        )
WEAK_PROTOTYPE( SVC_Handler               )
WEAK_PROTOTYPE( DebugMon_Handler          )
WEAK_PROTOTYPE( PENDSV_HANDLER            )
WEAK_PROTOTYPE( SysTick_Handler           )

//*****************************************************************************
//
// Forward declaration of the programmable device interrupt handlers.
//
//*****************************************************************************
ADI_WEAK_PROTOTYPE( WakeUp_Int_Handler       )
ADI_WEAK_PROTOTYPE( Ext_Int0_Handler         )
ADI_WEAK_PROTOTYPE( Ext_Int1_Handler         )
ADI_WEAK_PROTOTYPE( Ext_Int2_Handler         )
ADI_WEAK_PROTOTYPE( Ext_Int3_Handler         )
ADI_WEAK_PROTOTYPE( WDog_Tmr_Int_Handler     )
ADI_WEAK_PROTOTYPE( Vreg_over_Int_Handler     )
ADI_WEAK_PROTOTYPE( Battery_Voltage_Int_Handler     )
ADI_WEAK_PROTOTYPE( RTC0_Int_Handler          )
ADI_WEAK_PROTOTYPE( GPIO_A_Int_Handler       )
ADI_WEAK_PROTOTYPE( GPIO_B_Int_Handler       )
ADI_WEAK_PROTOTYPE( GP_Tmr0_Int_Handler      )
ADI_WEAK_PROTOTYPE( GP_Tmr1_Int_Handler      )
ADI_WEAK_PROTOTYPE( Flash0_Int_Handler       )
ADI_WEAK_PROTOTYPE( UART_Int_Handler         )
ADI_WEAK_PROTOTYPE( SPI0_Int_Handler         )
ADI_WEAK_PROTOTYPE( SPI2_Int_Handler         )
ADI_WEAK_PROTOTYPE( I2C0_Slave_Int_Handler   )
ADI_WEAK_PROTOTYPE( I2C0_Master_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_Err_Int_Handler      )
ADI_WEAK_PROTOTYPE( DMA_SPI2_TX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPI2_RX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPORT0A_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPORT0B_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPI0_TX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPI0_RX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPI1_TX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_SPI1_RX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_UART_TX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_UART_RX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_I2C0_STX_Int_Handler )
ADI_WEAK_PROTOTYPE( DMA_I2C0_SRX_Int_Handler )
ADI_WEAK_PROTOTYPE( DMA_I2C0_MX_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_AES0_IN_Int_Handler  )
ADI_WEAK_PROTOTYPE( DMA_AES0_OUT_Int_Handler )
ADI_WEAK_PROTOTYPE( DMA_FLASH0_Int_Handler   )
ADI_WEAK_PROTOTYPE( SPORT0A_Int_Handler      )
ADI_WEAK_PROTOTYPE( SPORT0B_Int_Handler      )
ADI_WEAK_PROTOTYPE( Crypto_Int_Handler       )
/** Placeholder: IRQn = 39 is reserved on the ADuM302X                                   */
ADI_WEAK_PROTOTYPE( GP_Tmr2_Int_Handler      )
ADI_WEAK_PROTOTYPE( Crystal_osc_Int_Handler  )
ADI_WEAK_PROTOTYPE( SPI1_Int_Handler         )
ADI_WEAK_PROTOTYPE( PLL_Int_Handler          )
ADI_WEAK_PROTOTYPE( RNG_Int_Handler          )
ADI_WEAK_PROTOTYPE( Beep_Int_Handler         )
/** Placeholder: IRQn = 46 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 47 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 48 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 49 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 50 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 51 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 52 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 53 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 54 is reserved on the ADuM302X                                   */
/** Placeholder: IRQn = 55 is reserved on the ADuM302x                                    */
ADI_WEAK_PROTOTYPE( DMA_SIP0_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP1_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP2_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP3_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP4_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP5_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP6_Int_Handler     )
ADI_WEAK_PROTOTYPE( DMA_SIP7_Int_Handler     )
WEAK_PROTOTYPE( RESERVED_VECTOR              )

#endif // __STARTUP_H__
