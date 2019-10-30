/*!
 *****************************************************************************
 * @file:    system.h
 * @brief:   CMSIS Cortex-M3 Device Peripheral Access Layer Header File
 *           for the ADI ADuCxxx Device Series
 * @version: $Revision: 29716 $
 * @date:    $Date: 2015-02-13 00:54:38 -0500 (Fri, 13 Feb 2015) $
 *-----------------------------------------------------------------------------
 *
 * Copyright (C) 2009-2013 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *****************************************************************************/


/*! \addtogroup SYS_Driver System Interfaces
 *  @{
 * add result types to doxygen
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stddef.h>     /* for 'NULL' */
#include <adi_types.h>
#include <ADuCM355.h>

#define SUCCESS 0
#define FAILURE 1

/* System clock constant */
#define __HFOSC     26000000u

/* System clock constant (may also be 16000000) */
#define __HFXTAL    26000000u

 /*System clock constant (same whether internal osc or external xtal) */
#define __LFCLK        32768u

 /*Selecting HFOSC as input for generating root clock*/
#define HFMUX_INTERNAL_OSC_VAL      (0u << BITP_CLKG_CLK_CTL0_CLKMUX)

 /*Selecting HFXTL as input for generating root clock*/
#define HFMUX_EXTERNAL_XTAL_VAL     (1u << BITP_CLKG_CLK_CTL0_CLKMUX)

 /*Selecting SPLL as input for generating root clock*/
#define HFMUX_SYSTEM_SPLL_VAL       (2u << BITP_CLKG_CLK_CTL0_CLKMUX)

 /*Selecting GPIO as input for generating root clock*/
#define HFMUX_GPIO_VAL              (3u << BITP_CLKG_CLK_CTL0_CLKMUX)

/*! Cache controller key */
#define CACHE_CONTROLLER_KEY 0xF123F456
/*! Power  key */
#define PWRKEY_VALUE_KEY 0x4859
/**
 *  Enumeration of different channel of the SPORT
 *
 */
typedef enum
{
    /*! SRAM_BANK_0 */
    ADI_SRAM_BANK_0      = 1,
    /*! SRAM_BANK_1 */
    ADI_SRAM_BANK_1      = 2,
    /*! SRAM_BANK_2 */
    ADI_SRAM_BANK_2      = 4,
    /*! SRAM_BANK_3 */
    ADI_SRAM_BANK_3      = 8,
    /*! SRAM_BANK_4 */
    ADI_SRAM_BANK_4      = 16,
    /*! SRAM_BANK_5 */
    ADI_SRAM_BANK_5      = 32

} ADI_SRAM_BANK;
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
void adi_system_EnableCache(bool_t bEnable);
uint32_t  adi_system_EnableRetention(ADI_SRAM_BANK eBank,bool_t bEnable);
void adi_system_EnableISRAM(bool_t bEnable);
void adi_default_setting(void);
#endif /* __SYSTEM_H__ */


/*@}*//*
** EOF
*/
