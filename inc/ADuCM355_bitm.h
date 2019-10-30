/* ================================================================================

     Project      :   ADuCM355
     File         :   ADuCM355.h
     Description  :   Register Definitions

     Date         :   May 21, 2018

     Copyright (c) 2016-2018 Analog Devices, Inc.  All Rights Reserved.
     This software is proprietary and confidential to Analog Devices, Inc. and
     its licensors.

     This file was auto-generated. Do not make local changes to this file.

   ================================================================================ */

#ifndef _DEF_ADUCM355_H
#define _DEF_ADUCM355_H

#if defined(_LANGUAGE_C) || (defined(__GNUC__) && !defined(__ASSEMBLER__))
#include <stdint.h>
#endif /* _LANGUAGE_C */


#if defined (_MISRA_RULES)
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_1:"Allow names over 32 character limit")
#pragma diag(suppress:misra_rule_19_7:"ADI header allows function-like macros")
#pragma diag(suppress:misra_rule_19_13:"ADI headers can use the # and ## preprocessor operators")
#endif /* _MISRA_RULES */

/* _ADI_MSK_3 might be defined in wrapper includes - otherwise provide a default */
#if !defined(_ADI_MSK_3)
/* do not add casts to literal constants in assembly code */
#if defined(_LANGUAGE_ASM) || defined(__ASSEMBLER__)
/* Use unsuffixed literals for BITM macros */
#define _ADI_MSK_3( mask, smask, type ) (mask) 
#else
/* Use casted suffixed literals for BITM macros */
#define _ADI_MSK_3( mask, smask, type ) ((type)(smask))
#endif
#endif

#ifndef __ADI_GENERATED_DEF_HEADERS__
#define __ADI_GENERATED_DEF_HEADERS__    1
#endif

#define __ADI_HAS_AGPIO__          1
#define __ADI_HAS_AGPIOTEST__      1
#define __ADI_HAS_ALLON__          1
#define __ADI_HAS_BUSM__           1
#define __ADI_HAS_CLKG_OSC__       1
#define __ADI_HAS_CLKG__           1
#define __ADI_HAS_CLKG_CLK__       1
#define __ADI_HAS_AFECRC__         1
#define __ADI_HAS_CRC__            1
#define __ADI_HAS_CRYPT__          1
#define __ADI_HAS_DFT__            1
#define __ADI_HAS_DMA__            1
#define __ADI_HAS_XINT__           1
#define __ADI_HAS_FLCC__           1
#define __ADI_HAS_FLCC_CACHE__     1
#define __ADI_HAS_FLCC_DFT__       1
#define __ADI_HAS_FLCC_TEST__      1
#define __ADI_HAS_GPIO__           1
#define __ADI_HAS_TMR__            1
#define __ADI_HAS_AGPT1__          1
#define __ADI_HAS_AGPT0__          1
#define __ADI_HAS_I2C__            1
#define __ADI_HAS_INTC__           1
#define __ADI_HAS_AFECON__         1
#define __ADI_HAS_NVIC__           1
#define __ADI_HAS_OTP__            1
#define __ADI_HAS_PMG__            1
#define __ADI_HAS_PMG_TST__        1
#define __ADI_HAS_RNG__            1
#define __ADI_HAS_RTC__            1
#define __ADI_HAS_SPI__            1
#define __ADI_HAS_SPII2CS__        1
#define __ADI_HAS_SYS__            1
#define __ADI_HAS_UART__           1
#define __ADI_HAS_AFEWDT__         1
#define __ADI_HAS_WDT__            1
#define __ADI_HAS_WUPTMR__         1
#define __ADI_HAS_AFE__            1

/* ============================================================================================================================
        General Purpose Timer
   ============================================================================================================================ */

/* ============================================================================================================================
        TMR0
   ============================================================================================================================ */
#define REG_TMR0_LOAD                        0x40000000            /*  TMR0 16-bit load value */
#define REG_TMR0_CURCNT                      0x40000004            /*  TMR0 16-bit timer value */
#define REG_TMR0_CTL                         0x40000008            /*  TMR0 Control */
#define REG_TMR0_CLRINT                      0x4000000C            /*  TMR0 Clear Interrupt */
#define REG_TMR0_CAPTURE                     0x40000010            /*  TMR0 Capture */
#define REG_TMR0_ALOAD                       0x40000014            /*  TMR0 16-bit load value, asynchronous */
#define REG_TMR0_ACURCNT                     0x40000018            /*  TMR0 16-bit timer value, asynchronous */
#define REG_TMR0_STAT                        0x4000001C            /*  TMR0 Status */
#define REG_TMR0_PWMCTL                      0x40000020            /*  TMR0 PWM Control Register */
#define REG_TMR0_PWMMATCH                    0x40000024            /*  TMR0 PWM Match Value */

/* ============================================================================================================================
        TMR1
   ============================================================================================================================ */
#define REG_TMR1_LOAD                        0x40000400            /*  TMR1 16-bit load value */
#define REG_TMR1_CURCNT                      0x40000404            /*  TMR1 16-bit timer value */
#define REG_TMR1_CTL                         0x40000408            /*  TMR1 Control */
#define REG_TMR1_CLRINT                      0x4000040C            /*  TMR1 Clear Interrupt */
#define REG_TMR1_CAPTURE                     0x40000410            /*  TMR1 Capture */
#define REG_TMR1_ALOAD                       0x40000414            /*  TMR1 16-bit load value, asynchronous */
#define REG_TMR1_ACURCNT                     0x40000418            /*  TMR1 16-bit timer value, asynchronous */
#define REG_TMR1_STAT                        0x4000041C            /*  TMR1 Status */
#define REG_TMR1_PWMCTL                      0x40000420            /*  TMR1 PWM Control Register */
#define REG_TMR1_PWMMATCH                    0x40000424            /*  TMR1 PWM Match Value */

/* ============================================================================================================================
        TMR2
   ============================================================================================================================ */
#define REG_TMR2_LOAD                        0x40000800            /*  TMR2 16-bit load value */
#define REG_TMR2_CURCNT                      0x40000804            /*  TMR2 16-bit timer value */
#define REG_TMR2_CTL                         0x40000808            /*  TMR2 Control */
#define REG_TMR2_CLRINT                      0x4000080C            /*  TMR2 Clear Interrupt */
#define REG_TMR2_CAPTURE                     0x40000810            /*  TMR2 Capture */
#define REG_TMR2_ALOAD                       0x40000814            /*  TMR2 16-bit load value, asynchronous */
#define REG_TMR2_ACURCNT                     0x40000818            /*  TMR2 16-bit timer value, asynchronous */
#define REG_TMR2_STAT                        0x4000081C            /*  TMR2 Status */
#define REG_TMR2_PWMCTL                      0x40000820            /*  TMR2 PWM Control Register */
#define REG_TMR2_PWMMATCH                    0x40000824            /*  TMR2 PWM Match Value */

/* ============================================================================================================================
        TMR Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          TMR_LOAD                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_LOAD_VALUE                   0            /*  Load value */
#define BITM_TMR_LOAD_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load value */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_CURCNT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_CURCNT_VALUE                 0            /*  Current count */
#define BITM_TMR_CURCNT_VALUE                (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Current count */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_CTL                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_CTL_SYNCBYP                 15            /*  Synchronization bypass */
#define BITP_TMR_CTL_RSTEN                   14            /*  Counter and prescale reset enable */
#define BITP_TMR_CTL_EVTEN                   13            /*  Event select */
#define BITP_TMR_CTL_EVTRANGE                 8            /*  Event select range */
#define BITP_TMR_CTL_RLD                      7            /*  Reload control */
#define BITP_TMR_CTL_CLK                      5            /*  Clock select */
#define BITP_TMR_CTL_EN                       4            /*  Timer enable */
#define BITP_TMR_CTL_MODE                     3            /*  Timer mode */
#define BITP_TMR_CTL_UP                       2            /*  Count up */
#define BITP_TMR_CTL_PRE                      0            /*  Prescaler */
#define BITM_TMR_CTL_SYNCBYP                 (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Synchronization bypass */
#define BITM_TMR_CTL_RSTEN                   (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Counter and prescale reset enable */
#define BITM_TMR_CTL_EVTEN                   (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Event select */
#define BITM_TMR_CTL_EVTRANGE                (_ADI_MSK_3(0x00001F00,0x00001F00U, uint16_t  ))    /*  Event select range */
#define BITM_TMR_CTL_RLD                     (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Reload control */
#define BITM_TMR_CTL_CLK                     (_ADI_MSK_3(0x00000060,0x00000060U, uint16_t  ))    /*  Clock select */
#define BITM_TMR_CTL_EN                      (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Timer enable */
#define BITM_TMR_CTL_MODE                    (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Timer mode */
#define BITM_TMR_CTL_UP                      (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Count up */
#define BITM_TMR_CTL_PRE                     (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Prescaler */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_CLRINT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_CLRINT_EVTCAPT               1            /*  Clear captured event interrupt */
#define BITP_TMR_CLRINT_TIMEOUT               0            /*  Clear timeout interrupt */
#define BITM_TMR_CLRINT_EVTCAPT              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Clear captured event interrupt */
#define BITM_TMR_CLRINT_TIMEOUT              (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Clear timeout interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_CAPTURE                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_CAPTURE_VALUE                0            /*  16-bit captured value */
#define BITM_TMR_CAPTURE_VALUE               (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  16-bit captured value */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_ALOAD                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_ALOAD_VALUE                  0            /*  Load value, asynchronous */
#define BITM_TMR_ALOAD_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load value, asynchronous */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_ACURCNT                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_ACURCNT_VALUE                0            /*  Counter value */
#define BITM_TMR_ACURCNT_VALUE               (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Counter value */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_STAT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_STAT_CNTRST                  8            /*  Counter reset occurring */
#define BITP_TMR_STAT_PDOK                    7            /*  Clear Interrupt Register synchronization */
#define BITP_TMR_STAT_BUSY                    6            /*  Timer Busy */
#define BITP_TMR_STAT_CAPTURE                 1            /*  Capture event pending */
#define BITP_TMR_STAT_TIMEOUT                 0            /*  Timeout event occurred */
#define BITM_TMR_STAT_CNTRST                 (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Counter reset occurring */
#define BITM_TMR_STAT_PDOK                   (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Clear Interrupt Register synchronization */
#define BITM_TMR_STAT_BUSY                   (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Timer Busy */
#define BITM_TMR_STAT_CAPTURE                (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Capture event pending */
#define BITM_TMR_STAT_TIMEOUT                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Timeout event occurred */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_PWMCTL                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_PWMCTL_IDLESTATE             1            /*  PWM Idle State */
#define BITP_TMR_PWMCTL_MATCH                 0            /*  PWM Match enabled */
#define BITM_TMR_PWMCTL_IDLESTATE            (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  PWM Idle State */
#define BITM_TMR_PWMCTL_MATCH                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  PWM Match enabled */

/* -------------------------------------------------------------------------------------------------------------------------
          TMR_PWMMATCH                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_TMR_PWMMATCH_VALUE               0            /*  PWM Match Value */
#define BITM_TMR_PWMMATCH_VALUE              (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  PWM Match Value */


/* ============================================================================================================================
        Real-Time Clock
   ============================================================================================================================ */

/* ============================================================================================================================
        RTC0
   ============================================================================================================================ */
#define REG_RTC0_CR0                         0x40001000            /*  RTC0 RTC Control 0 */
#define REG_RTC0_SR0                         0x40001004            /*  RTC0 RTC Status 0 */
#define REG_RTC0_SR1                         0x40001008            /*  RTC0 RTC Status 1 */
#define REG_RTC0_CNT0                        0x4000100C            /*  RTC0 RTC Count 0 */
#define REG_RTC0_CNT1                        0x40001010            /*  RTC0 RTC Count 1 */
#define REG_RTC0_ALM0                        0x40001014            /*  RTC0 RTC Alarm 0 */
#define REG_RTC0_ALM1                        0x40001018            /*  RTC0 RTC Alarm 1 */
#define REG_RTC0_TRM                         0x4000101C            /*  RTC0 RTC Trim */
#define REG_RTC0_GWY                         0x40001020            /*  RTC0 RTC Gateway */
#define REG_RTC0_CR1                         0x40001028            /*  RTC0 RTC Control 1 */
#define REG_RTC0_SR2                         0x4000102C            /*  RTC0 RTC Status 2 */
#define REG_RTC0_SNAP0                       0x40001030            /*  RTC0 RTC Snapshot 0 */
#define REG_RTC0_SNAP1                       0x40001034            /*  RTC0 RTC Snapshot 1 */
#define REG_RTC0_SNAP2                       0x40001038            /*  RTC0 RTC Snapshot 2 */
#define REG_RTC0_MOD                         0x4000103C            /*  RTC0 RTC Modulo */
#define REG_RTC0_CNT2                        0x40001040            /*  RTC0 RTC Count 2 */
#define REG_RTC0_ALM2                        0x40001044            /*  RTC0 RTC Alarm 2 */
#define REG_RTC0_SR3                         0x40001048            /*  RTC0 RTC Status 3 */
#define REG_RTC0_CR2IC                       0x4000104C            /*  RTC0 RTC Control 2 for Configuring Input Capture Channels */
#define REG_RTC0_CR3OC                       0x40001050            /*  RTC0 RTC Control 3 for Configuring Output Compare Channel */
#define REG_RTC0_CR4OC                       0x40001054            /*  RTC0 RTC Control 4 for Configuring Output Compare Channel */
#define REG_RTC0_OCMSK                       0x40001058            /*  RTC0 RTC Masks for Output Compare Channel */
#define REG_RTC0_OC1ARL                      0x4000105C            /*  RTC0 RTC Auto-Reload for Output Compare Channel 1 */
#define REG_RTC0_IC2                         0x40001064            /*  RTC0 RTC Input Capture Channel 2 */
#define REG_RTC0_IC3                         0x40001068            /*  RTC0 RTC Input Capture Channel 3 */
#define REG_RTC0_IC4                         0x4000106C            /*  RTC0 RTC Input Capture Channel 4 */
#define REG_RTC0_OC1                         0x40001070            /*  RTC0 RTC Output Compare Channel 1 */
#define REG_RTC0_SR4                         0x40001080            /*  RTC0 RTC Status 4 */
#define REG_RTC0_SR5                         0x40001084            /*  RTC0 RTC Status 5 */
#define REG_RTC0_SR6                         0x40001088            /*  RTC0 RTC Status 6 */
#define REG_RTC0_OC1TGT                      0x4000108C            /*  RTC0 RTC Output Compare Channel 1 Target */
#define REG_RTC0_FRZCNT                      0x40001090            /*  RTC0 RTC Freeze Count */

/* ============================================================================================================================
        RTC1
   ============================================================================================================================ */
#define REG_RTC1_CR0                         0x40001400            /*  RTC1 RTC Control 0 */
#define REG_RTC1_SR0                         0x40001404            /*  RTC1 RTC Status 0 */
#define REG_RTC1_SR1                         0x40001408            /*  RTC1 RTC Status 1 */
#define REG_RTC1_CNT0                        0x4000140C            /*  RTC1 RTC Count 0 */
#define REG_RTC1_CNT1                        0x40001410            /*  RTC1 RTC Count 1 */
#define REG_RTC1_ALM0                        0x40001414            /*  RTC1 RTC Alarm 0 */
#define REG_RTC1_ALM1                        0x40001418            /*  RTC1 RTC Alarm 1 */
#define REG_RTC1_TRM                         0x4000141C            /*  RTC1 RTC Trim */
#define REG_RTC1_GWY                         0x40001420            /*  RTC1 RTC Gateway */
#define REG_RTC1_CR1                         0x40001428            /*  RTC1 RTC Control 1 */
#define REG_RTC1_SR2                         0x4000142C            /*  RTC1 RTC Status 2 */
#define REG_RTC1_SNAP0                       0x40001430            /*  RTC1 RTC Snapshot 0 */
#define REG_RTC1_SNAP1                       0x40001434            /*  RTC1 RTC Snapshot 1 */
#define REG_RTC1_SNAP2                       0x40001438            /*  RTC1 RTC Snapshot 2 */
#define REG_RTC1_MOD                         0x4000143C            /*  RTC1 RTC Modulo */
#define REG_RTC1_CNT2                        0x40001440            /*  RTC1 RTC Count 2 */
#define REG_RTC1_ALM2                        0x40001444            /*  RTC1 RTC Alarm 2 */
#define REG_RTC1_SR3                         0x40001448            /*  RTC1 RTC Status 3 */
#define REG_RTC1_CR2IC                       0x4000144C            /*  RTC1 RTC Control 2 for Configuring Input Capture Channels */
#define REG_RTC1_CR3OC                       0x40001450            /*  RTC1 RTC Control 3 for Configuring Output Compare Channel */
#define REG_RTC1_CR4OC                       0x40001454            /*  RTC1 RTC Control 4 for Configuring Output Compare Channel */
#define REG_RTC1_OCMSK                       0x40001458            /*  RTC1 RTC Masks for Output Compare Channel */
#define REG_RTC1_OC1ARL                      0x4000145C            /*  RTC1 RTC Auto-Reload for Output Compare Channel 1 */
#define REG_RTC1_IC2                         0x40001464            /*  RTC1 RTC Input Capture Channel 2 */
#define REG_RTC1_IC3                         0x40001468            /*  RTC1 RTC Input Capture Channel 3 */
#define REG_RTC1_IC4                         0x4000146C            /*  RTC1 RTC Input Capture Channel 4 */
#define REG_RTC1_OC1                         0x40001470            /*  RTC1 RTC Output Compare Channel 1 */
#define REG_RTC1_SR4                         0x40001480            /*  RTC1 RTC Status 4 */
#define REG_RTC1_SR5                         0x40001484            /*  RTC1 RTC Status 5 */
#define REG_RTC1_SR6                         0x40001488            /*  RTC1 RTC Status 6 */
#define REG_RTC1_OC1TGT                      0x4000148C            /*  RTC1 RTC Output Compare Channel 1 Target */
#define REG_RTC1_FRZCNT                      0x40001490            /*  RTC1 RTC Freeze Count */

/* ============================================================================================================================
        RTC Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CR0                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CR0_WPNDINTEN               15            /*  Enable Write Pending sourced interrupts to the CPU */
#define BITP_RTC_CR0_WSYNCINTEN              14            /*  Enable Write synchronization sourced interrupts to the CPU */
#define BITP_RTC_CR0_WPNDERRINTEN            13            /*  Enable Write pending error sourced interrupts to the CPU when an RTC register-write pending error occurs */
#define BITP_RTC_CR0_ISOINTEN                12            /*  Enable RTC power-domain isolation sourced interrupts to the CPU when isolation of the RTC power domain is activated and subsequently de-activated */
#define BITP_RTC_CR0_MOD60ALMINTEN           11            /*  Enable periodic Modulo-60 RTC alarm sourced interrupts to the CPU */
#define BITP_RTC_CR0_MOD60ALM                 5            /*  Periodic, modulo-60 alarm time in prescaled RTC time units beyond a modulo-60 boundary */
#define BITP_RTC_CR0_MOD60ALMEN               4            /*  Enable RTC modulo-60 counting of time past a modulo-60 boundary */
#define BITP_RTC_CR0_TRMEN                    3            /*  Enable RTC digital trimming */
#define BITP_RTC_CR0_ALMINTEN                 2            /*  Enable sourced alarm interrupts to the CPU */
#define BITP_RTC_CR0_ALMEN                    1            /*  Enable the RTC alarm (absolute) operation */
#define BITP_RTC_CR0_CNTEN                    0            /*  Global enable for the RTC */
#define BITM_RTC_CR0_WPNDINTEN               (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Enable Write Pending sourced interrupts to the CPU */
#define BITM_RTC_CR0_WSYNCINTEN              (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Enable Write synchronization sourced interrupts to the CPU */
#define BITM_RTC_CR0_WPNDERRINTEN            (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Enable Write pending error sourced interrupts to the CPU when an RTC register-write pending error occurs */
#define BITM_RTC_CR0_ISOINTEN                (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Enable RTC power-domain isolation sourced interrupts to the CPU when isolation of the RTC power domain is activated and subsequently de-activated */
#define BITM_RTC_CR0_MOD60ALMINTEN           (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Enable periodic Modulo-60 RTC alarm sourced interrupts to the CPU */
#define BITM_RTC_CR0_MOD60ALM                (_ADI_MSK_3(0x000007E0,0x000007E0U, uint16_t  ))    /*  Periodic, modulo-60 alarm time in prescaled RTC time units beyond a modulo-60 boundary */
#define BITM_RTC_CR0_MOD60ALMEN              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Enable RTC modulo-60 counting of time past a modulo-60 boundary */
#define BITM_RTC_CR0_TRMEN                   (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Enable RTC digital trimming */
#define BITM_RTC_CR0_ALMINTEN                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Enable sourced alarm interrupts to the CPU */
#define BITM_RTC_CR0_ALMEN                   (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Enable the RTC alarm (absolute) operation */
#define BITM_RTC_CR0_CNTEN                   (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Global enable for the RTC */
#define ENUM_RTC_CR0_EXAMPLE_1_THIRTY_TIME_UNITS_DECIMAL (_ADI_MSK_3(0x000003C0,0x000003C0U, uint16_t  ))    /*  MOD60ALM: Example of setting a modulo-60 periodic interrupt from the RTC to be issued to the CPU at 30 time units past a modulo-60 boundary. */
#define ENUM_RTC_CR0_EXAMPLE_2_FIFTYFIVE_TIME_UNITS_DECIMAL (_ADI_MSK_3(0x000006E0,0x000006E0U, uint16_t  ))    /*  MOD60ALM: Example of setting a modulo-60 periodic interrupt from the RTC to be issued to the CPU at 55 time units past a modulo-60 boundary. */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR0                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR0_ISOENB                  14            /*  Visibility status of 32 kHz sourced registers, taking account of power-domain isolation */
#define BITP_RTC_SR0_WSYNCTRM                13            /*  Synchronization status of posted writes to RTC Trim Register */
#define BITP_RTC_SR0_WSYNCALM1               12            /*  Synchronization status of posted writes to RTC Alarm 1 Register */
#define BITP_RTC_SR0_WSYNCALM0               11            /*  Synchronization status of posted writes to RTC Alarm 0 Register */
#define BITP_RTC_SR0_WSYNCCNT1               10            /*  Synchronization status of posted writes to RTC Count 1 Register */
#define BITP_RTC_SR0_WSYNCCNT0                9            /*  Synchronization status of posted writes to RTC Count 0 Register */
#define BITP_RTC_SR0_WSYNCSR0                 8            /*  Synchronization status of posted clearances to interrupt sources in RTC Status 0 Register */
#define BITP_RTC_SR0_WSYNCCR0                 7            /*  Synchronization status of posted writes to RTC Control 0 Register */
#define BITP_RTC_SR0_WPNDINT                  6            /*  Write pending interrupt */
#define BITP_RTC_SR0_WSYNCINT                 5            /*  Write synchronization interrupt */
#define BITP_RTC_SR0_WPNDERRINT               4            /*  Write pending error interrupt source */
#define BITP_RTC_SR0_ISOINT                   3            /*  RTC power-domain isolation interrupt source */
#define BITP_RTC_SR0_MOD60ALMINT              2            /*  Modulo-60 RTC alarm interrupt source */
#define BITP_RTC_SR0_ALMINT                   1            /*  Alarm interrupt source */
#define BITM_RTC_SR0_ISOENB                  (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Visibility status of 32 kHz sourced registers, taking account of power-domain isolation */
#define BITM_RTC_SR0_WSYNCTRM                (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Trim Register */
#define BITM_RTC_SR0_WSYNCALM1               (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Alarm 1 Register */
#define BITM_RTC_SR0_WSYNCALM0               (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Alarm 0 Register */
#define BITM_RTC_SR0_WSYNCCNT1               (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Count 1 Register */
#define BITM_RTC_SR0_WSYNCCNT0               (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Count 0 Register */
#define BITM_RTC_SR0_WSYNCSR0                (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Synchronization status of posted clearances to interrupt sources in RTC Status 0 Register */
#define BITM_RTC_SR0_WSYNCCR0                (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Control 0 Register */
#define BITM_RTC_SR0_WPNDINT                 (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Write pending interrupt */
#define BITM_RTC_SR0_WSYNCINT                (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Write synchronization interrupt */
#define BITM_RTC_SR0_WPNDERRINT              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Write pending error interrupt source */
#define BITM_RTC_SR0_ISOINT                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  RTC power-domain isolation interrupt source */
#define BITM_RTC_SR0_MOD60ALMINT             (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Modulo-60 RTC alarm interrupt source */
#define BITM_RTC_SR0_ALMINT                  (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Alarm interrupt source */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR1                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR1_WPNDTRM                 13            /*  Pending status of posted writes to RTC Trim Register */
#define BITP_RTC_SR1_WPNDALM1                12            /*  Pending status of posted writes to RTC ALARM 1 Register */
#define BITP_RTC_SR1_WPNDALM0                11            /*  Pending status of posted writes to RTC ALARM 0 Register */
#define BITP_RTC_SR1_WPNDCNT1                10            /*  Pending status of posted writes to RTC Count 1 Register */
#define BITP_RTC_SR1_WPNDCNT0                 9            /*  Pending status of posted writes to RTC Count 0 Register */
#define BITP_RTC_SR1_WPNDSR0                  8            /*  Pending status of posted clearances of interrupt sources in RTC Status 0 Register */
#define BITP_RTC_SR1_WPNDCR0                  7            /*  Pending status of posted writes to RTC Control 0 Register */
#define BITM_RTC_SR1_WPNDTRM                 (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Pending status of posted writes to RTC Trim Register */
#define BITM_RTC_SR1_WPNDALM1                (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Pending status of posted writes to RTC ALARM 1 Register */
#define BITM_RTC_SR1_WPNDALM0                (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Pending status of posted writes to RTC ALARM 0 Register */
#define BITM_RTC_SR1_WPNDCNT1                (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Pending status of posted writes to RTC Count 1 Register */
#define BITM_RTC_SR1_WPNDCNT0                (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Pending status of posted writes to RTC Count 0 Register */
#define BITM_RTC_SR1_WPNDSR0                 (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Pending status of posted clearances of interrupt sources in RTC Status 0 Register */
#define BITM_RTC_SR1_WPNDCR0                 (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Pending status of posted writes to RTC Control 0 Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CNT0                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CNT0_VALUE                   0            /*  Lower 16 prescaled (non-fractional) bits of the RTC real-time count */
#define BITM_RTC_CNT0_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Lower 16 prescaled (non-fractional) bits of the RTC real-time count */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CNT1                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CNT1_VALUE                   0            /*  Upper 16 prescaled (non-fractional) bits of the RTC real-time count */
#define BITM_RTC_CNT1_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Upper 16 prescaled (non-fractional) bits of the RTC real-time count */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_ALM0                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_ALM0_VALUE                   0            /*  Lower 16 prescaled (that is, non-fractional) bits of the RTC alarm target time */
#define BITM_RTC_ALM0_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Lower 16 prescaled (that is, non-fractional) bits of the RTC alarm target time */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_ALM1                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_ALM1_VALUE                   0            /*  Upper 16 prescaled (non-fractional) bits of the RTC alarm target time */
#define BITM_RTC_ALM1_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Upper 16 prescaled (non-fractional) bits of the RTC alarm target time */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_TRM                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_TRM_IVL2EXPMIN               6            /*  Minimum power-of-two interval of prescaled RTC time units, which RTC Trim Register can select */
#define BITP_RTC_TRM_IVL                      4            /*  Trim interval in prescaled RTC time units */
#define BITP_RTC_TRM_ADD                      3            /*  Trim Polarity */
#define BITP_RTC_TRM_VALUE                    0            /*  Trim value in prescaled RTC time units to be added or subtracted from the RTC count at the end of a periodic interval selected by RTC Trim Register */
#define BITM_RTC_TRM_IVL2EXPMIN              (_ADI_MSK_3(0x000003C0,0x000003C0U, uint16_t  ))    /*  Minimum power-of-two interval of prescaled RTC time units, which RTC Trim Register can select */
#define BITM_RTC_TRM_IVL                     (_ADI_MSK_3(0x00000030,0x00000030U, uint16_t  ))    /*  Trim interval in prescaled RTC time units */
#define BITM_RTC_TRM_ADD                     (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Trim Polarity */
#define BITM_RTC_TRM_VALUE                   (_ADI_MSK_3(0x00000007,0x00000007U, uint16_t  ))    /*  Trim value in prescaled RTC time units to be added or subtracted from the RTC count at the end of a periodic interval selected by RTC Trim Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_GWY                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_GWY_SWKEY                    0            /*  Software-keyed command issued by the CPU */
#define BITM_RTC_GWY_SWKEY                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Software-keyed command issued by the CPU */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CR1                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CR1_PRESCALE2EXP             5            /*  Prescale power of 2 division factor for the RTC base clock */
#define BITP_RTC_CR1_CNTMOD60ROLLINTEN        4            /*  Enable for the RTC modulo-60 count roll-over interrupt source in RTC Status 2 Register */
#define BITP_RTC_CR1_CNTROLLINTEN             3            /*  Enable for the RTC count roll-over interrupt source in RTC Status 2 Register */
#define BITP_RTC_CR1_RTCTRMINTEN              2            /*  Enable for the RTC Trim interrupt source */
#define BITP_RTC_CR1_PSINTEN                  1            /*  Enable for the prescaled, modulo-1 interrupt source */
#define BITP_RTC_CR1_CNTINTEN                 0            /*  Enable for the RTC count interrupt source */
#define BITM_RTC_CR1_PRESCALE2EXP            (_ADI_MSK_3(0x000001E0,0x000001E0U, uint16_t  ))    /*  Prescale power of 2 division factor for the RTC base clock */
#define BITM_RTC_CR1_CNTMOD60ROLLINTEN       (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Enable for the RTC modulo-60 count roll-over interrupt source in RTC Status 2 Register */
#define BITM_RTC_CR1_CNTROLLINTEN            (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Enable for the RTC count roll-over interrupt source in RTC Status 2 Register */
#define BITM_RTC_CR1_RTCTRMINTEN             (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Enable for the RTC Trim interrupt source */
#define BITM_RTC_CR1_PSINTEN                 (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Enable for the prescaled, modulo-1 interrupt source */
#define BITM_RTC_CR1_CNTINTEN                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Enable for the RTC count interrupt source */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR2                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR2_WSYNCALM2MIR            15            /*  Synchronization status of posted writes to RTC Alarm 2 Register */
#define BITP_RTC_SR2_WSYNCCR1MIR             14            /*  Synchronization status of posted writes to RTC Control 1 Register */
#define BITP_RTC_SR2_WPNDALM2MIR             13            /*  Pending status of posted writes to RTC Alarm 2 Register */
#define BITP_RTC_SR2_WPNDCR1MIR              12            /*  Pending status of posted writes to RTC Control 1 Register */
#define BITP_RTC_SR2_TRMBDYMIR                7            /*  Mirror of the RTCTRMBDY field of RTC Modulo Register */
#define BITP_RTC_SR2_CNTMOD60ROLL             6            /*  RTC count modulo-60 roll-over */
#define BITP_RTC_SR2_CNTROLL                  5            /*  RTC count roll-over */
#define BITP_RTC_SR2_CNTMOD60ROLLINT          4            /*  RTC modulo-60 count roll-over interrupt source */
#define BITP_RTC_SR2_CNTROLLINT               3            /*  RTC count roll-over interrupt source */
#define BITP_RTC_SR2_TRMINT                   2            /*  RTC Trim interrupt source */
#define BITP_RTC_SR2_PSINT                    1            /*  RTC prescaled, modulo-1 boundary interrupt source */
#define BITP_RTC_SR2_CNTINT                   0            /*  RTC count interrupt source */
#define BITM_RTC_SR2_WSYNCALM2MIR            (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Alarm 2 Register */
#define BITM_RTC_SR2_WSYNCCR1MIR             (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Control 1 Register */
#define BITM_RTC_SR2_WPNDALM2MIR             (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Pending status of posted writes to RTC Alarm 2 Register */
#define BITM_RTC_SR2_WPNDCR1MIR              (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Pending status of posted writes to RTC Control 1 Register */
#define BITM_RTC_SR2_TRMBDYMIR               (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Mirror of the RTCTRMBDY field of RTC Modulo Register */
#define BITM_RTC_SR2_CNTMOD60ROLL            (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  RTC count modulo-60 roll-over */
#define BITM_RTC_SR2_CNTROLL                 (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  RTC count roll-over */
#define BITM_RTC_SR2_CNTMOD60ROLLINT         (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  RTC modulo-60 count roll-over interrupt source */
#define BITM_RTC_SR2_CNTROLLINT              (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  RTC count roll-over interrupt source */
#define BITM_RTC_SR2_TRMINT                  (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  RTC Trim interrupt source */
#define BITM_RTC_SR2_PSINT                   (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  RTC prescaled, modulo-1 boundary interrupt source */
#define BITM_RTC_SR2_CNTINT                  (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  RTC count interrupt source */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SNAP0                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SNAP0_VALUE                  0            /*  Constituent part of the 47-bit RTC Input Capture Channel 0, containing a sticky snapshot of  RTC Count 0 Register */
#define BITM_RTC_SNAP0_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Constituent part of the 47-bit RTC Input Capture Channel 0, containing a sticky snapshot of  RTC Count 0 Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SNAP1                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SNAP1_VALUE                  0            /*  Constituent part of the 47-bit RTC Input Capture Channel 0, containing a sticky snapshot of  RTC Count 1 Register */
#define BITM_RTC_SNAP1_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Constituent part of the 47-bit RTC Input Capture Channel 0, containing a sticky snapshot of  RTC Count 1 Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SNAP2                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SNAP2_VALUE                  0            /*  Constituent part of the 47-bit RTC Input Capture Channel 0, containing a sticky snapshot of RTC Count 2 Register */
#define BITM_RTC_SNAP2_VALUE                 (_ADI_MSK_3(0x00007FFF,0x00007FFFU, uint16_t  ))    /*  Constituent part of the 47-bit RTC Input Capture Channel 0, containing a sticky snapshot of RTC Count 2 Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_MOD                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_MOD_CNT0_4TOZERO            11            /*  Mirror of RTC Count 0 Register [4:0] */
#define BITP_RTC_MOD_TRMBDY                  10            /*  Trim boundary indicator that the most recent RTC count increment has coincided with trimming of the count value */
#define BITP_RTC_MOD_INCR                     6            /*  Most recent increment value added to the RTC Count in RTC Count 1 and RTC Count 0 Registers */
#define BITP_RTC_MOD_CNTMOD60                 0            /*  Modulo-60 value of prescaled  RTC Count 1 and RTC Count 0 Registers */
#define BITM_RTC_MOD_CNT0_4TOZERO            (_ADI_MSK_3(0x0000F800,0x0000F800U, uint16_t  ))    /*  Mirror of RTC Count 0 Register [4:0] */
#define BITM_RTC_MOD_TRMBDY                  (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Trim boundary indicator that the most recent RTC count increment has coincided with trimming of the count value */
#define BITM_RTC_MOD_INCR                    (_ADI_MSK_3(0x000003C0,0x000003C0U, uint16_t  ))    /*  Most recent increment value added to the RTC Count in RTC Count 1 and RTC Count 0 Registers */
#define BITM_RTC_MOD_CNTMOD60                (_ADI_MSK_3(0x0000003F,0x0000003FU, uint16_t  ))    /*  Modulo-60 value of prescaled  RTC Count 1 and RTC Count 0 Registers */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CNT2                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CNT2_VALUE                   0            /*  Fractional bits of the RTC real-time count */
#define BITM_RTC_CNT2_VALUE                  (_ADI_MSK_3(0x00007FFF,0x00007FFFU, uint16_t  ))    /*  Fractional bits of the RTC real-time count */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_ALM2                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_ALM2_VALUE                   0            /*  Fractional (non-prescaled) bits of the RTC alarm target time */
#define BITM_RTC_ALM2_VALUE                  (_ADI_MSK_3(0x00007FFF,0x00007FFFU, uint16_t  ))    /*  Fractional (non-prescaled) bits of the RTC alarm target time */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR3                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR3_RTCOC1IRQ                9            /*  Sticky Interrupt Source for Output Compare Channel 1 */
#define BITP_RTC_SR3_ALMINTMIR                8            /*  Read-only mirror of the ALMINT interrupt source in RTC Status 0 Register, acting as RTCOC0IRQ */
#define BITP_RTC_SR3_RTCIC4IRQ                4            /*  Sticky Interrupt Source for the RTC Input Capture Channel 4 */
#define BITP_RTC_SR3_RTCIC3IRQ                3            /*  Sticky Interrupt Source for the RTC Input Capture Channel 3 */
#define BITP_RTC_SR3_RTCIC2IRQ                2            /*  Sticky Interrupt Source for the RTC Input Capture Channel 2 */
#define BITP_RTC_SR3_RTCIC0IRQ                0            /*  Sticky Interrupt Source for the RTC Input Capture Channel 0 */
#define BITM_RTC_SR3_RTCOC1IRQ               (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Sticky Interrupt Source for Output Compare Channel 1 */
#define BITM_RTC_SR3_ALMINTMIR               (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Read-only mirror of the ALMINT interrupt source in RTC Status 0 Register, acting as RTCOC0IRQ */
#define BITM_RTC_SR3_RTCIC4IRQ               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Sticky Interrupt Source for the RTC Input Capture Channel 4 */
#define BITM_RTC_SR3_RTCIC3IRQ               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Sticky Interrupt Source for the RTC Input Capture Channel 3 */
#define BITM_RTC_SR3_RTCIC2IRQ               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Sticky Interrupt Source for the RTC Input Capture Channel 2 */
#define BITM_RTC_SR3_RTCIC0IRQ               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Sticky Interrupt Source for the RTC Input Capture Channel 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CR2IC                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CR2IC_RTCICOWUSEN           15            /*  Enable Overwrite of Unread Snapshots for all RTC Input Capture Channels */
#define BITP_RTC_CR2IC_RTCIC4IRQEN           14            /*  Interrupt Enable for the RTC Input Capture Channel 4 */
#define BITP_RTC_CR2IC_RTCIC3IRQEN           13            /*  Interrupt Enable for the RTC Input Capture Channel 3 */
#define BITP_RTC_CR2IC_RTCIC2IRQEN           12            /*  Interrupt Enable for the RTC Input Capture Channel 2 */
#define BITP_RTC_CR2IC_RTCIC0IRQEN           10            /*  Interrupt Enable for the RTC Input Capture Channel 0 */
#define BITP_RTC_CR2IC_RTCIC4LH               9            /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 4 */
#define BITP_RTC_CR2IC_RTCIC3LH               8            /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 3 */
#define BITP_RTC_CR2IC_RTCIC2LH               7            /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 2 */
#define BITP_RTC_CR2IC_RTCIC0LH               5            /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 0 */
#define BITP_RTC_CR2IC_RTCIC4EN               4            /*  Enable for the RTC Input Capture Channel 4 */
#define BITP_RTC_CR2IC_RTCIC3EN               3            /*  Enable for the RTC Input Capture Channel 3 */
#define BITP_RTC_CR2IC_RTCIC2EN               2            /*  Enable for the RTC Input Capture Channel 2 */
#define BITP_RTC_CR2IC_RTCIC0EN               0            /*  Enable for the RTC Input Capture Channel 0 */
#define BITM_RTC_CR2IC_RTCICOWUSEN           (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Enable Overwrite of Unread Snapshots for all RTC Input Capture Channels */
#define BITM_RTC_CR2IC_RTCIC4IRQEN           (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Interrupt Enable for the RTC Input Capture Channel 4 */
#define BITM_RTC_CR2IC_RTCIC3IRQEN           (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Interrupt Enable for the RTC Input Capture Channel 3 */
#define BITM_RTC_CR2IC_RTCIC2IRQEN           (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Interrupt Enable for the RTC Input Capture Channel 2 */
#define BITM_RTC_CR2IC_RTCIC0IRQEN           (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Interrupt Enable for the RTC Input Capture Channel 0 */
#define BITM_RTC_CR2IC_RTCIC4LH              (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 4 */
#define BITM_RTC_CR2IC_RTCIC3LH              (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 3 */
#define BITM_RTC_CR2IC_RTCIC2LH              (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 2 */
#define BITM_RTC_CR2IC_RTCIC0LH              (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Polarity of the active-going capture edge for the RTC Input Capture Channel 0 */
#define BITM_RTC_CR2IC_RTCIC4EN              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Enable for the RTC Input Capture Channel 4 */
#define BITM_RTC_CR2IC_RTCIC3EN              (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Enable for the RTC Input Capture Channel 3 */
#define BITM_RTC_CR2IC_RTCIC2EN              (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Enable for the RTC Input Capture Channel 2 */
#define BITM_RTC_CR2IC_RTCIC0EN              (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Enable for the RTC Input Capture Channel 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CR3OC                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CR3OC_RTCOC1IRQEN            9            /*  Interrupt Enable for Output Compare Channel 1 */
#define BITP_RTC_CR3OC_RTCOC1EN               1            /*  Enable for Output Compare Channel 1 */
#define BITM_RTC_CR3OC_RTCOC1IRQEN           (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Interrupt Enable for Output Compare Channel 1 */
#define BITM_RTC_CR3OC_RTCOC1EN              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Enable for Output Compare Channel 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_CR4OC                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_CR4OC_RTCOC1ARLEN            9            /*  Enable for auto-reloading when output compare match occurs */
#define BITP_RTC_CR4OC_RTCOC1MSKEN            1            /*  Enable for thermometer-code masking of the Output Compare 1 Channel */
#define BITM_RTC_CR4OC_RTCOC1ARLEN           (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Enable for auto-reloading when output compare match occurs */
#define BITM_RTC_CR4OC_RTCOC1MSKEN           (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Enable for thermometer-code masking of the Output Compare 1 Channel */
#define ENUM_RTC_CR4OC_EN000                 (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  RTCOC1MSKEN: Do not apply a mask to the 16-bit Output Compare channel OC1. */
#define ENUM_RTC_CR4OC_EN001                 (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  RTCOC1MSKEN: Apply a thermometer-decoded mask to the 16-bit Output Compare channel OC1 provided that channel is enabled via CR3OC:RTCOC1EN */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_OCMSK                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_OCMSK_RTCOCMSK               0            /*  Concatenation of thermometer-encoded masks for the 16-bit output compare channels */
#define BITM_RTC_OCMSK_RTCOCMSK              (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Concatenation of thermometer-encoded masks for the 16-bit output compare channels */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_OC1ARL                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_OC1ARL_RTCOC1ARL             0            /*  Auto-reload value when output compare match occurs */
#define BITM_RTC_OC1ARL_RTCOC1ARL            (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Auto-reload value when output compare match occurs */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_IC2                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_IC2_RTCIC2                   0            /*  RTC Input Capture Channel 2 */
#define BITM_RTC_IC2_RTCIC2                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  RTC Input Capture Channel 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_IC3                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_IC3_RTCIC3                   0            /*  RTC Input Capture Channel 3 */
#define BITM_RTC_IC3_RTCIC3                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  RTC Input Capture Channel 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_IC4                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_IC4_RTCIC4                   0            /*  RTC Input Capture Channel 4 */
#define BITM_RTC_IC4_RTCIC4                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  RTC Input Capture Channel 4 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_OC1                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_OC1_RTCOC1                   0            /*  RTC Output Compare 1 Channel. Scheduled alarm target time with optional auto-reload */
#define BITM_RTC_OC1_RTCOC1                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  RTC Output Compare 1 Channel. Scheduled alarm target time with optional auto-reload */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR4                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR4_RSYNCIC4                14            /*  Synchronization status of posted reads of RTC Input Channel 4 */
#define BITP_RTC_SR4_RSYNCIC3                13            /*  Synchronization status of posted reads of RTC Input Channel 3 */
#define BITP_RTC_SR4_RSYNCIC2                12            /*  Synchronization status of posted reads of RTC Input Channel 2 */
#define BITP_RTC_SR4_RSYNCIC0                10            /*  Synchronization status of posted reads of RTC Input Channel 0 */
#define BITP_RTC_SR4_WSYNCOC1                 6            /*  Synchronization status of posted writes to RTC Output Compare Channel 1 Register */
#define BITP_RTC_SR4_WSYNCOC1ARL              5            /*  Synchronization status of posted writes to RTC Auto-Reload for Output Compare Channel 1 Register */
#define BITP_RTC_SR4_WSYNCOCMSK               4            /*  Synchronization status of posted writes to RTC Masks for Output Compare Channel Register */
#define BITP_RTC_SR4_WSYNCCR4OC               3            /*  Synchronization status of posted writes to RTC Control 4 for Configuring Output Compare Channel Register */
#define BITP_RTC_SR4_WSYNCCR3OC               2            /*  Synchronization status of posted writes to RTC Control 3 for Configuring Output Compare Channel Register */
#define BITP_RTC_SR4_WSYNCCR2IC               1            /*  Synchronization status of posted writes to RTC Control 2 for Configuring Input Capture Channels Register */
#define BITP_RTC_SR4_WSYNCSR3                 0            /*  Synchronization status of posted clearances to interrupt sources in RTC Status 3 Register */
#define BITM_RTC_SR4_RSYNCIC4                (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Synchronization status of posted reads of RTC Input Channel 4 */
#define BITM_RTC_SR4_RSYNCIC3                (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Synchronization status of posted reads of RTC Input Channel 3 */
#define BITM_RTC_SR4_RSYNCIC2                (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Synchronization status of posted reads of RTC Input Channel 2 */
#define BITM_RTC_SR4_RSYNCIC0                (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Synchronization status of posted reads of RTC Input Channel 0 */
#define BITM_RTC_SR4_WSYNCOC1                (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Output Compare Channel 1 Register */
#define BITM_RTC_SR4_WSYNCOC1ARL             (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Auto-Reload for Output Compare Channel 1 Register */
#define BITM_RTC_SR4_WSYNCOCMSK              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Masks for Output Compare Channel Register */
#define BITM_RTC_SR4_WSYNCCR4OC              (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Control 4 for Configuring Output Compare Channel Register */
#define BITM_RTC_SR4_WSYNCCR3OC              (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Control 3 for Configuring Output Compare Channel Register */
#define BITM_RTC_SR4_WSYNCCR2IC              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Synchronization status of posted writes to RTC Control 2 for Configuring Input Capture Channels Register */
#define BITM_RTC_SR4_WSYNCSR3                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Synchronization status of posted clearances to interrupt sources in RTC Status 3 Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR5                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR5_RPENDIC4                14            /*  Pending status of posted reads of RTC Input Channel 4 */
#define BITP_RTC_SR5_RPENDIC3                13            /*  Pending status of posted reads of RTC Input Channel 3 */
#define BITP_RTC_SR5_RPENDIC2                12            /*  Pending status of posted reads of RTC Input Channel 2 */
#define BITP_RTC_SR5_RPENDIC0                10            /*  Pending status of posted reads of RTC Input Channel 0 */
#define BITP_RTC_SR5_WPENDOC1                 6            /*  Pending status of posted writes to Output Compare Channel 1 */
#define BITP_RTC_SR5_WPENDOC1ARL              5            /*  Pending status of posted writes to RTC Auto-Reload for Output Compare Channel 1 Register */
#define BITP_RTC_SR5_WPENDOCMSK               4            /*  Pending status of posted writes to RTC Masks for Output Compare Channel Register */
#define BITP_RTC_SR5_WPENDCR4OC               3            /*  Pending status of posted writes to RTC Control 4 for Configuring Output Compare Channel Register */
#define BITP_RTC_SR5_WPENDCR3OC               2            /*  Pending status of posted writes to RTC Control 3 for Configuring Output Compare Channel Register */
#define BITP_RTC_SR5_WPENDCR2IC               1            /*  Pending status of posted writes to RTC Control 2 for Configuring Input Capture Channels Register */
#define BITP_RTC_SR5_WPNDSR0                  0            /*  Pending status of posted clearances of interrupt sources in RTC Status 3 Register */
#define BITM_RTC_SR5_RPENDIC4                (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Pending status of posted reads of RTC Input Channel 4 */
#define BITM_RTC_SR5_RPENDIC3                (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Pending status of posted reads of RTC Input Channel 3 */
#define BITM_RTC_SR5_RPENDIC2                (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Pending status of posted reads of RTC Input Channel 2 */
#define BITM_RTC_SR5_RPENDIC0                (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Pending status of posted reads of RTC Input Channel 0 */
#define BITM_RTC_SR5_WPENDOC1                (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Pending status of posted writes to Output Compare Channel 1 */
#define BITM_RTC_SR5_WPENDOC1ARL             (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Pending status of posted writes to RTC Auto-Reload for Output Compare Channel 1 Register */
#define BITM_RTC_SR5_WPENDOCMSK              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Pending status of posted writes to RTC Masks for Output Compare Channel Register */
#define BITM_RTC_SR5_WPENDCR4OC              (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Pending status of posted writes to RTC Control 4 for Configuring Output Compare Channel Register */
#define BITM_RTC_SR5_WPENDCR3OC              (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Pending status of posted writes to RTC Control 3 for Configuring Output Compare Channel Register */
#define BITM_RTC_SR5_WPENDCR2IC              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Pending status of posted writes to RTC Control 2 for Configuring Input Capture Channels Register */
#define BITM_RTC_SR5_WPNDSR0                 (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Pending status of posted clearances of interrupt sources in RTC Status 3 Register */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_SR6                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_SR6_RTCFRZCNTPTR             9            /*  Pointer for the triple-read sequence of the RTC Freeze Count MMR */
#define BITP_RTC_SR6_RTCIC0SNAP               8            /*  Confirmation that RTC Snapshot 0, 1, 2 registers reflect the value of RTC Input Capture Channel 0 */
#define BITP_RTC_SR6_RTCIC4UNR                4            /*  Sticky unread status of the RTC Input Capture Channel 4 */
#define BITP_RTC_SR6_RTCIC3UNR                3            /*  Sticky unread status of the RTC Input Capture Channel 3 */
#define BITP_RTC_SR6_RTCIC2UNR                2            /*  Sticky unread status of the RTC Input Capture Channel 2 */
#define BITP_RTC_SR6_RTCIC0UNR                0            /*  Sticky unread status of the RTC Input Capture Channel 0 */
#define BITM_RTC_SR6_RTCFRZCNTPTR            (_ADI_MSK_3(0x00000600,0x00000600U, uint16_t  ))    /*  Pointer for the triple-read sequence of the RTC Freeze Count MMR */
#define BITM_RTC_SR6_RTCIC0SNAP              (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Confirmation that RTC Snapshot 0, 1, 2 registers reflect the value of RTC Input Capture Channel 0 */
#define BITM_RTC_SR6_RTCIC4UNR               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Sticky unread status of the RTC Input Capture Channel 4 */
#define BITM_RTC_SR6_RTCIC3UNR               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Sticky unread status of the RTC Input Capture Channel 3 */
#define BITM_RTC_SR6_RTCIC2UNR               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Sticky unread status of the RTC Input Capture Channel 2 */
#define BITM_RTC_SR6_RTCIC0UNR               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Sticky unread status of the RTC Input Capture Channel 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_OC1TGT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_OC1TGT_RTCOC1TGT             0            /*  Current, cumulative target time for Output Compare Channel 1, taking account of any auto-reloading */
#define BITM_RTC_OC1TGT_RTCOC1TGT            (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Current, cumulative target time for Output Compare Channel 1, taking account of any auto-reloading */

/* -------------------------------------------------------------------------------------------------------------------------
          RTC_FRZCNT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RTC_FRZCNT_RTCFRZCNT             0            /*  RTC Freeze Count */
#define BITM_RTC_FRZCNT_RTCFRZCNT            (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  RTC Freeze Count */


/* ============================================================================================================================
        System Identification and Debug Enable
   ============================================================================================================================ */

/* ============================================================================================================================
        SYS
   ============================================================================================================================ */
#define REG_SYS_ADIID                        0x40002020            /*  SYS ADI Identification */
#define REG_SYS_CHIPID                       0x40002024            /*  SYS Chip Identifier */
#define REG_SYS_SWDEN                        0x40002040            /*  SYS Serial Wire Debug Enable */

/* ============================================================================================================================
        SYS Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          SYS_ADIID                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SYS_ADIID_VALUE                  0            /*  Reads a fixed value of 0x4144 to indicate to debuggers that they are connected to an Analog Devices implemented Cortex based part */
#define BITM_SYS_ADIID_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Reads a fixed value of 0x4144 to indicate to debuggers that they are connected to an Analog Devices implemented Cortex based part */

/* -------------------------------------------------------------------------------------------------------------------------
          SYS_CHIPID                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SYS_CHIPID_PARTID                4            /*  Part identifier */
#define BITP_SYS_CHIPID_REV                   0            /*  Silicon revision */
#define BITM_SYS_CHIPID_PARTID               (_ADI_MSK_3(0x0000FFF0,0x0000FFF0U, uint16_t  ))    /*  Part identifier */
#define BITM_SYS_CHIPID_REV                  (_ADI_MSK_3(0x0000000F,0x0000000FU, uint16_t  ))    /*  Silicon revision */

/* -------------------------------------------------------------------------------------------------------------------------
          SYS_SWDEN                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SYS_SWDEN_VALUE                  0            /*  To enable SWD interface */
#define BITM_SYS_SWDEN_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  To enable SWD interface */


/* ============================================================================================================================
        Watchdog Timer
   ============================================================================================================================ */

/* ============================================================================================================================
        WDT0
   ============================================================================================================================ */
#define REG_WDT0_LOAD                        0x40002C00            /*  WDT0 Load value */
#define REG_WDT0_CCNT                        0x40002C04            /*  WDT0 Current count value */
#define REG_WDT0_CTL                         0x40002C08            /*  WDT0 Control */
#define REG_WDT0_RESTART                     0x40002C0C            /*  WDT0 Clear interrupt */
#define REG_WDT0_STAT                        0x40002C18            /*  WDT0 Status */

/* ============================================================================================================================
        WDT Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          WDT_LOAD                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_WDT_LOAD_VALUE                   0            /*  Load value */
#define BITM_WDT_LOAD_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load value */

/* -------------------------------------------------------------------------------------------------------------------------
          WDT_CCNT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_WDT_CCNT_VALUE                   0            /*  Current count value */
#define BITM_WDT_CCNT_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Current count value */

/* -------------------------------------------------------------------------------------------------------------------------
          WDT_CTL                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_WDT_CTL_SPARE                    7            /*  Unused spare bit */
#define BITP_WDT_CTL_MODE                     6            /*  Timer mode */
#define BITP_WDT_CTL_EN                       5            /*  Timer enable */
#define BITP_WDT_CTL_PRE                      2            /*  Prescaler */
#define BITP_WDT_CTL_IRQ                      1            /*  Timer interrupt */
#define BITM_WDT_CTL_SPARE                   (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Unused spare bit */
#define BITM_WDT_CTL_MODE                    (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Timer mode */
#define BITM_WDT_CTL_EN                      (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Timer enable */
#define BITM_WDT_CTL_PRE                     (_ADI_MSK_3(0x0000000C,0x0000000CU, uint16_t  ))    /*  Prescaler */
#define BITM_WDT_CTL_IRQ                     (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Timer interrupt */
#define ENUM_WDT_CTL_DIV1                    (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  PRE: source clock/1. */
#define ENUM_WDT_CTL_DIV16                   (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  PRE: source clock/16. */
#define ENUM_WDT_CTL_DIV256                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  PRE: source clock/256 (default). */
#define ENUM_WDT_CTL_RESERVED                (_ADI_MSK_3(0x0000000C,0x0000000CU, uint16_t  ))    /*  PRE: Reserved */

/* -------------------------------------------------------------------------------------------------------------------------
          WDT_RESTART                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_WDT_RESTART_CLRWORD              0            /*  Clear watchdog */
#define BITM_WDT_RESTART_CLRWORD             (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Clear watchdog */

/* -------------------------------------------------------------------------------------------------------------------------
          WDT_STAT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_WDT_STAT_RSTCTL                  5            /*  Reset Control Register written and locked */
#define BITP_WDT_STAT_LOCKED                  4            /*  Lock status bit */
#define BITP_WDT_STAT_COUNTING                3            /*  Control Register write sync in progress */
#define BITP_WDT_STAT_LOADING                 2            /*  Load Register write sync in progress */
#define BITP_WDT_STAT_CLRIRQ                  1            /*  Clear Interrupt Register write sync in progress */
#define BITP_WDT_STAT_IRQ                     0            /*  WDT Interrupt */
#define BITM_WDT_STAT_RSTCTL                 (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Reset Control Register written and locked */
#define BITM_WDT_STAT_LOCKED                 (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Lock status bit */
#define BITM_WDT_STAT_COUNTING               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Control Register write sync in progress */
#define BITM_WDT_STAT_LOADING                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Load Register write sync in progress */
#define BITM_WDT_STAT_CLRIRQ                 (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Clear Interrupt Register write sync in progress */
#define BITM_WDT_STAT_IRQ                    (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  WDT Interrupt */


/* ============================================================================================================================
        I2C Master/Slave
   ============================================================================================================================ */

/* ============================================================================================================================
        I2C0
   ============================================================================================================================ */
#define REG_I2C0_MCTL                        0x40003000            /*  I2C0 Master control */
#define REG_I2C0_MSTAT                       0x40003004            /*  I2C0 Master status */
#define REG_I2C0_MRX                         0x40003008            /*  I2C0 Master receive data */
#define REG_I2C0_MTX                         0x4000300C            /*  I2C0 Master transmit data */
#define REG_I2C0_MRXCNT                      0x40003010            /*  I2C0 Master receive data count */
#define REG_I2C0_MCRXCNT                     0x40003014            /*  I2C0 Master current receive data count */
#define REG_I2C0_ADDR1                       0x40003018            /*  I2C0 1st master address byte */
#define REG_I2C0_ADDR2                       0x4000301C            /*  I2C0 2nd master address byte */
#define REG_I2C0_BYT                         0x40003020            /*  I2C0 Start byte */
#define REG_I2C0_DIV                         0x40003024            /*  I2C0 Serial clock period divisor */
#define REG_I2C0_SCTL                        0x40003028            /*  I2C0 Slave control */
#define REG_I2C0_SSTAT                       0x4000302C            /*  I2C0 Slave I2C Status/Error/IRQ */
#define REG_I2C0_SRX                         0x40003030            /*  I2C0 Slave receive */
#define REG_I2C0_STX                         0x40003034            /*  I2C0 Slave transmit */
#define REG_I2C0_ALT                         0x40003038            /*  I2C0 Hardware general call ID */
#define REG_I2C0_ID0                         0x4000303C            /*  I2C0 1st slave address device ID */
#define REG_I2C0_ID1                         0x40003040            /*  I2C0 2nd slave address device ID */
#define REG_I2C0_ID2                         0x40003044            /*  I2C0 3rd slave address device ID */
#define REG_I2C0_ID3                         0x40003048            /*  I2C0 4th slave address device ID */
#define REG_I2C0_STAT                        0x4000304C            /*  I2C0 Master and slave FIFO status */
#define REG_I2C0_SHCTL                       0x40003050            /*  I2C0 Shared control */
#define REG_I2C0_TCTL                        0x40003054            /*  I2C0 Timing Control Register */
#define REG_I2C0_ASTRETCH_SCL                0x40003058            /*  I2C0 Automatic stretch SCL register */

/* ============================================================================================================================
        I2C Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          I2C_MCTL                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_MCTL_STOPBUSCLR             13            /*  Prestop Bus-Clear */
#define BITP_I2C_MCTL_BUSCLR                 12            /*  Bus-Clear Enable */
#define BITP_I2C_MCTL_MTXDMA                 11            /*  Enable master Tx DMA request */
#define BITP_I2C_MCTL_MRXDMA                 10            /*  Enable master Rx DMA request */
#define BITP_I2C_MCTL_MXMITDEC                9            /*  Decrement master TX FIFO status when a byte has been transmitted */
#define BITP_I2C_MCTL_IENCMP                  8            /*  Transaction completed (or stop detected) interrupt enable */
#define BITP_I2C_MCTL_IENACK                  7            /*  ACK not received interrupt enable */
#define BITP_I2C_MCTL_IENALOST                6            /*  Arbitration lost interrupt enable */
#define BITP_I2C_MCTL_IENMTX                  5            /*  Transmit request interrupt enable. */
#define BITP_I2C_MCTL_IENMRX                  4            /*  Receive request interrupt enable */
#define BITP_I2C_MCTL_STRETCHSCL              3            /*  Stretch SCL enable */
#define BITP_I2C_MCTL_LOOPBACK                2            /*  Internal loopback enable */
#define BITP_I2C_MCTL_COMPLETE                1            /*  Start back-off disable */
#define BITP_I2C_MCTL_MASEN                   0            /*  Master enable */
#define BITM_I2C_MCTL_STOPBUSCLR             (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Prestop Bus-Clear */
#define BITM_I2C_MCTL_BUSCLR                 (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Bus-Clear Enable */
#define BITM_I2C_MCTL_MTXDMA                 (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Enable master Tx DMA request */
#define BITM_I2C_MCTL_MRXDMA                 (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Enable master Rx DMA request */
#define BITM_I2C_MCTL_MXMITDEC               (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Decrement master TX FIFO status when a byte has been transmitted */
#define BITM_I2C_MCTL_IENCMP                 (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Transaction completed (or stop detected) interrupt enable */
#define BITM_I2C_MCTL_IENACK                 (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  ACK not received interrupt enable */
#define BITM_I2C_MCTL_IENALOST               (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Arbitration lost interrupt enable */
#define BITM_I2C_MCTL_IENMTX                 (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Transmit request interrupt enable. */
#define BITM_I2C_MCTL_IENMRX                 (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Receive request interrupt enable */
#define BITM_I2C_MCTL_STRETCHSCL             (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Stretch SCL enable */
#define BITM_I2C_MCTL_LOOPBACK               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Internal loopback enable */
#define BITM_I2C_MCTL_COMPLETE               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Start back-off disable */
#define BITM_I2C_MCTL_MASEN                  (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Master enable */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_MSTAT                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_MSTAT_SCLFILT               14            /*  State of SCL Line */
#define BITP_I2C_MSTAT_SDAFILT               13            /*  State of SDA Line */
#define BITP_I2C_MSTAT_MTXUNDR               12            /*  Master Transmit Underflow */
#define BITP_I2C_MSTAT_MSTOP                 11            /*  STOP driven by this I2C Master */
#define BITP_I2C_MSTAT_LINEBUSY              10            /*  Line is busy */
#define BITP_I2C_MSTAT_MRXOVR                 9            /*  Master Receive FIFO overflow */
#define BITP_I2C_MSTAT_TCOMP                  8            /*  Transaction complete or stop detected */
#define BITP_I2C_MSTAT_NACKDATA               7            /*  ACK not received in response to data write */
#define BITP_I2C_MSTAT_MBUSY                  6            /*  Master busy */
#define BITP_I2C_MSTAT_ALOST                  5            /*  Arbitration lost */
#define BITP_I2C_MSTAT_NACKADDR               4            /*  ACK not received in response to an address */
#define BITP_I2C_MSTAT_MRXREQ                 3            /*  Master Receive request */
#define BITP_I2C_MSTAT_MTXREQ                 2            /*  When read is master Transmit request; when write is Clear master transmit interrupt bit */
#define BITP_I2C_MSTAT_MTXF                   0            /*  Master Transmit FIFO status */
#define BITM_I2C_MSTAT_SCLFILT               (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  State of SCL Line */
#define BITM_I2C_MSTAT_SDAFILT               (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  State of SDA Line */
#define BITM_I2C_MSTAT_MTXUNDR               (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Master Transmit Underflow */
#define BITM_I2C_MSTAT_MSTOP                 (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  STOP driven by this I2C Master */
#define BITM_I2C_MSTAT_LINEBUSY              (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Line is busy */
#define BITM_I2C_MSTAT_MRXOVR                (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Master Receive FIFO overflow */
#define BITM_I2C_MSTAT_TCOMP                 (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Transaction complete or stop detected */
#define BITM_I2C_MSTAT_NACKDATA              (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  ACK not received in response to data write */
#define BITM_I2C_MSTAT_MBUSY                 (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Master busy */
#define BITM_I2C_MSTAT_ALOST                 (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Arbitration lost */
#define BITM_I2C_MSTAT_NACKADDR              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  ACK not received in response to an address */
#define BITM_I2C_MSTAT_MRXREQ                (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Master Receive request */
#define BITM_I2C_MSTAT_MTXREQ                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  When read is master Transmit request; when write is Clear master transmit interrupt bit */
#define BITM_I2C_MSTAT_MTXF                  (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Master Transmit FIFO status */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_MRX                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_MRX_VALUE                    0            /*  Master receive register */
#define BITM_I2C_MRX_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Master receive register */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_MTX                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_MTX_VALUE                    0            /*  Master transmit register */
#define BITM_I2C_MTX_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Master transmit register */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_MRXCNT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_MRXCNT_EXTEND                8            /*  Extended read */
#define BITP_I2C_MRXCNT_VALUE                 0            /*  Receive count */
#define BITM_I2C_MRXCNT_EXTEND               (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Extended read */
#define BITM_I2C_MRXCNT_VALUE                (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Receive count */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_MCRXCNT                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_MCRXCNT_VALUE                0            /*  Current receive count */
#define BITM_I2C_MCRXCNT_VALUE               (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Current receive count */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ADDR1                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ADDR1_VALUE                  0            /*  Address byte 1 */
#define BITM_I2C_ADDR1_VALUE                 (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Address byte 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ADDR2                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ADDR2_VALUE                  0            /*  Address byte 2 */
#define BITM_I2C_ADDR2_VALUE                 (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Address byte 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_BYT                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_BYT_SBYTE                    0            /*  Start byte */
#define BITM_I2C_BYT_SBYTE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Start byte */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_DIV                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_DIV_HIGH                     8            /*  Serial clock high time */
#define BITP_I2C_DIV_LOW                      0            /*  Serial clock low time */
#define BITM_I2C_DIV_HIGH                    (_ADI_MSK_3(0x0000FF00,0x0000FF00U, uint16_t  ))    /*  Serial clock high time */
#define BITM_I2C_DIV_LOW                     (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Serial clock low time */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_SCTL                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_SCTL_STXDMA                 14            /*  Enable slave Tx DMA request */
#define BITP_I2C_SCTL_SRXDMA                 13            /*  Enable slave Rx DMA request */
#define BITP_I2C_SCTL_IENREPST               12            /*  Repeated start interrupt enable */
#define BITP_I2C_SCTL_STXDEC                 11            /*  Decrement Slave Tx FIFO status when a byte has been transmitted */
#define BITP_I2C_SCTL_IENSTX                 10            /*  Slave Transmit request interrupt enable */
#define BITP_I2C_SCTL_IENSRX                  9            /*  Slave Receive request interrupt enable */
#define BITP_I2C_SCTL_IENSTOP                 8            /*  Stop condition detected interrupt enable */
#define BITP_I2C_SCTL_NACK                    7            /*  NACK next communication */
#define BITP_I2C_SCTL_EARLYTXR                5            /*  Early transmit request mode */
#define BITP_I2C_SCTL_GCSBCLR                 4            /*  General call status bit clear */
#define BITP_I2C_SCTL_HGCEN                   3            /*  Hardware general call enable */
#define BITP_I2C_SCTL_GCEN                    2            /*  General call enable */
#define BITP_I2C_SCTL_ADR10EN                 1            /*  Enabled 10-bit addressing */
#define BITP_I2C_SCTL_SLVEN                   0            /*  Slave enable */
#define BITM_I2C_SCTL_STXDMA                 (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Enable slave Tx DMA request */
#define BITM_I2C_SCTL_SRXDMA                 (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Enable slave Rx DMA request */
#define BITM_I2C_SCTL_IENREPST               (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Repeated start interrupt enable */
#define BITM_I2C_SCTL_STXDEC                 (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Decrement Slave Tx FIFO status when a byte has been transmitted */
#define BITM_I2C_SCTL_IENSTX                 (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Slave Transmit request interrupt enable */
#define BITM_I2C_SCTL_IENSRX                 (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Slave Receive request interrupt enable */
#define BITM_I2C_SCTL_IENSTOP                (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Stop condition detected interrupt enable */
#define BITM_I2C_SCTL_NACK                   (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  NACK next communication */
#define BITM_I2C_SCTL_EARLYTXR               (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Early transmit request mode */
#define BITM_I2C_SCTL_GCSBCLR                (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  General call status bit clear */
#define BITM_I2C_SCTL_HGCEN                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Hardware general call enable */
#define BITM_I2C_SCTL_GCEN                   (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  General call enable */
#define BITM_I2C_SCTL_ADR10EN                (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Enabled 10-bit addressing */
#define BITM_I2C_SCTL_SLVEN                  (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Slave enable */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_SSTAT                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_SSTAT_START                 14            /*  Start and matching address */
#define BITP_I2C_SSTAT_REPSTART              13            /*  Repeated start and matching address */
#define BITP_I2C_SSTAT_IDMAT                 11            /*  Device ID matched */
#define BITP_I2C_SSTAT_STOP                  10            /*  Stop after start and matching address */
#define BITP_I2C_SSTAT_GCID                   8            /*  General ID */
#define BITP_I2C_SSTAT_GCINT                  7            /*  General call interrupt */
#define BITP_I2C_SSTAT_SBUSY                  6            /*  Slave busy */
#define BITP_I2C_SSTAT_NOACK                  5            /*  Ack not generated by the slave */
#define BITP_I2C_SSTAT_SRXOVR                 4            /*  Slave Receive FIFO overflow */
#define BITP_I2C_SSTAT_SRXREQ                 3            /*  Slave Receive request */
#define BITP_I2C_SSTAT_STXREQ                 2            /*  When read is slave transmit request; when write is clear slave transmit interrupt bit */
#define BITP_I2C_SSTAT_STXUNDR                1            /*  Slave Transmit FIFO underflow */
#define BITP_I2C_SSTAT_STXFSEREQ              0            /*  Slave Tx FIFO Status or early request */
#define BITM_I2C_SSTAT_START                 (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Start and matching address */
#define BITM_I2C_SSTAT_REPSTART              (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Repeated start and matching address */
#define BITM_I2C_SSTAT_IDMAT                 (_ADI_MSK_3(0x00001800,0x00001800U, uint16_t  ))    /*  Device ID matched */
#define BITM_I2C_SSTAT_STOP                  (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Stop after start and matching address */
#define BITM_I2C_SSTAT_GCID                  (_ADI_MSK_3(0x00000300,0x00000300U, uint16_t  ))    /*  General ID */
#define BITM_I2C_SSTAT_GCINT                 (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  General call interrupt */
#define BITM_I2C_SSTAT_SBUSY                 (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Slave busy */
#define BITM_I2C_SSTAT_NOACK                 (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Ack not generated by the slave */
#define BITM_I2C_SSTAT_SRXOVR                (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Slave Receive FIFO overflow */
#define BITM_I2C_SSTAT_SRXREQ                (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Slave Receive request */
#define BITM_I2C_SSTAT_STXREQ                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  When read is slave transmit request; when write is clear slave transmit interrupt bit */
#define BITM_I2C_SSTAT_STXUNDR               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Slave Transmit FIFO underflow */
#define BITM_I2C_SSTAT_STXFSEREQ             (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Slave Tx FIFO Status or early request */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_SRX                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_SRX_VALUE                    0            /*  Slave receive register */
#define BITM_I2C_SRX_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave receive register */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_STX                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_STX_VALUE                    0            /*  Slave transmit register */
#define BITM_I2C_STX_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave transmit register */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ALT                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ALT_ID                       0            /*  Slave Alt */
#define BITM_I2C_ALT_ID                      (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave Alt */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ID0                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ID0_VALUE                    0            /*  Slave device ID 0 */
#define BITM_I2C_ID0_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave device ID 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ID1                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ID1_VALUE                    0            /*  Slave device ID 1 */
#define BITM_I2C_ID1_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave device ID 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ID2                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ID2_VALUE                    0            /*  Slave device ID 2 */
#define BITM_I2C_ID2_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave device ID 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ID3                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ID3_VALUE                    0            /*  Slave device ID 3 */
#define BITM_I2C_ID3_VALUE                   (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Slave device ID 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_STAT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_STAT_MFLUSH                  9            /*  Flush the master transmit FIFO */
#define BITP_I2C_STAT_SFLUSH                  8            /*  Flush the slave transmit FIFO */
#define BITP_I2C_STAT_MRXF                    6            /*  Master receive FIFO status */
#define BITP_I2C_STAT_MTXF                    4            /*  Master transmit FIFO status */
#define BITP_I2C_STAT_SRXF                    2            /*  Slave receive FIFO status */
#define BITP_I2C_STAT_STXF                    0            /*  Slave transmit FIFO status */
#define BITM_I2C_STAT_MFLUSH                 (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Flush the master transmit FIFO */
#define BITM_I2C_STAT_SFLUSH                 (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Flush the slave transmit FIFO */
#define BITM_I2C_STAT_MRXF                   (_ADI_MSK_3(0x000000C0,0x000000C0U, uint16_t  ))    /*  Master receive FIFO status */
#define BITM_I2C_STAT_MTXF                   (_ADI_MSK_3(0x00000030,0x00000030U, uint16_t  ))    /*  Master transmit FIFO status */
#define BITM_I2C_STAT_SRXF                   (_ADI_MSK_3(0x0000000C,0x0000000CU, uint16_t  ))    /*  Slave receive FIFO status */
#define BITM_I2C_STAT_STXF                   (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Slave transmit FIFO status */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_SHCTL                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_SHCTL_RST                    0            /*  Reset START STOP detect circuit */
#define BITM_I2C_SHCTL_RST                   (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Reset START STOP detect circuit */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_TCTL                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_TCTL_FILTEROFF               8            /*  Input Filter Control */
#define BITP_I2C_TCTL_THDATIN                 0            /*  Data In Hold Start */
#define BITM_I2C_TCTL_FILTEROFF              (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Input Filter Control */
#define BITM_I2C_TCTL_THDATIN                (_ADI_MSK_3(0x0000001F,0x0000001FU, uint16_t  ))    /*  Data In Hold Start */

/* -------------------------------------------------------------------------------------------------------------------------
          I2C_ASTRETCH_SCL                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_I2C_ASTRETCH_SCL_SLVTMO          9            /*  slave automatic stretch timeout */
#define BITP_I2C_ASTRETCH_SCL_MSTTMO          8            /*  master automatic stretch timeout */
#define BITP_I2C_ASTRETCH_SCL_SLV             4            /*  slave automatic stretch mode */
#define BITP_I2C_ASTRETCH_SCL_MST             0            /*  master automatic stretch mode */
#define BITM_I2C_ASTRETCH_SCL_SLVTMO         (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  slave automatic stretch timeout */
#define BITM_I2C_ASTRETCH_SCL_MSTTMO         (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  master automatic stretch timeout */
#define BITM_I2C_ASTRETCH_SCL_SLV            (_ADI_MSK_3(0x000000F0,0x000000F0U, uint16_t  ))    /*  slave automatic stretch mode */
#define BITM_I2C_ASTRETCH_SCL_MST            (_ADI_MSK_3(0x0000000F,0x0000000FU, uint16_t  ))    /*  master automatic stretch mode */


/* ============================================================================================================================
        Serial Peripheral Interface
   ============================================================================================================================ */

/* ============================================================================================================================
        SPI0
   ============================================================================================================================ */
#define REG_SPI0_STAT                        0x40004000            /*  SPI0 Status */
#define REG_SPI0_RX                          0x40004004            /*  SPI0 Receive */
#define REG_SPI0_TX                          0x40004008            /*  SPI0 Transmit */
#define REG_SPI0_DIV                         0x4000400C            /*  SPI0 SPI baud rate selection */
#define REG_SPI0_CTL                         0x40004010            /*  SPI0 SPI configuration 1 */
#define REG_SPI0_IEN                         0x40004014            /*  SPI0 SPI configuration 2 */
#define REG_SPI0_CNT                         0x40004018            /*  SPI0 Transfer byte count */
#define REG_SPI0_DMA                         0x4000401C            /*  SPI0 SPI DMA enable */
#define REG_SPI0_FIFO_STAT                   0x40004020            /*  SPI0 FIFO Status */
#define REG_SPI0_RD_CTL                      0x40004024            /*  SPI0 Read Control */
#define REG_SPI0_FLOW_CTL                    0x40004028            /*  SPI0 Flow Control */
#define REG_SPI0_WAIT_TMR                    0x4000402C            /*  SPI0 Wait timer for flow control */
#define REG_SPI0_CS_CTL                      0x40004030            /*  SPI0 Chip-Select control for multi-slave connections */
#define REG_SPI0_CS_OVERRIDE                 0x40004034            /*  SPI0 Chip-Select Override */

/* ============================================================================================================================
        SPI1
   ============================================================================================================================ */
#define REG_SPI1_STAT                        0x40024000            /*  SPI1 Status */
#define REG_SPI1_RX                          0x40024004            /*  SPI1 Receive */
#define REG_SPI1_TX                          0x40024008            /*  SPI1 Transmit */
#define REG_SPI1_DIV                         0x4002400C            /*  SPI1 SPI baud rate selection */
#define REG_SPI1_CTL                         0x40024010            /*  SPI1 SPI configuration 1 */
#define REG_SPI1_IEN                         0x40024014            /*  SPI1 SPI configuration 2 */
#define REG_SPI1_CNT                         0x40024018            /*  SPI1 Transfer byte count */
#define REG_SPI1_DMA                         0x4002401C            /*  SPI1 SPI DMA enable */
#define REG_SPI1_FIFO_STAT                   0x40024020            /*  SPI1 FIFO Status */
#define REG_SPI1_RD_CTL                      0x40024024            /*  SPI1 Read Control */
#define REG_SPI1_FLOW_CTL                    0x40024028            /*  SPI1 Flow Control */
#define REG_SPI1_WAIT_TMR                    0x4002402C            /*  SPI1 Wait timer for flow control */
#define REG_SPI1_CS_CTL                      0x40024030            /*  SPI1 Chip-Select control for multi-slave connections */
#define REG_SPI1_CS_OVERRIDE                 0x40024034            /*  SPI1 Chip-Select Override */

/* ============================================================================================================================
        SPI Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          SPI_STAT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_STAT_RDY                    15            /*  Detected an edge on Ready indicator for flow-control */
#define BITP_SPI_STAT_CSFALL                 14            /*  Detected a falling edge on CS, in slave CON mode */
#define BITP_SPI_STAT_CSRISE                 13            /*  Detected a rising edge on CS, in slave CON mode */
#define BITP_SPI_STAT_CSERR                  12            /*  Detected a CS error condition in slave mode */
#define BITP_SPI_STAT_CS                     11            /*  CS Status */
#define BITP_SPI_STAT_RXOVR                   7            /*  SPI Rx FIFO overflow */
#define BITP_SPI_STAT_RXIRQ                   6            /*  SPI Rx IRQ */
#define BITP_SPI_STAT_TXIRQ                   5            /*  SPI Tx IRQ */
#define BITP_SPI_STAT_TXUNDR                  4            /*  SPI Tx FIFO underflow */
#define BITP_SPI_STAT_TXDONE                  3            /*  SPI Tx Done in read command mode */
#define BITP_SPI_STAT_TXEMPTY                 2            /*  SPI Tx FIFO empty interrupt */
#define BITP_SPI_STAT_XFRDONE                 1            /*  SPI transfer completion */
#define BITP_SPI_STAT_IRQ                     0            /*  SPI Interrupt status */
#define BITM_SPI_STAT_RDY                    (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Detected an edge on Ready indicator for flow-control */
#define BITM_SPI_STAT_CSFALL                 (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Detected a falling edge on CS, in slave CON mode */
#define BITM_SPI_STAT_CSRISE                 (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Detected a rising edge on CS, in slave CON mode */
#define BITM_SPI_STAT_CSERR                  (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  Detected a CS error condition in slave mode */
#define BITM_SPI_STAT_CS                     (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  CS Status */
#define BITM_SPI_STAT_RXOVR                  (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  SPI Rx FIFO overflow */
#define BITM_SPI_STAT_RXIRQ                  (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  SPI Rx IRQ */
#define BITM_SPI_STAT_TXIRQ                  (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  SPI Tx IRQ */
#define BITM_SPI_STAT_TXUNDR                 (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  SPI Tx FIFO underflow */
#define BITM_SPI_STAT_TXDONE                 (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  SPI Tx Done in read command mode */
#define BITM_SPI_STAT_TXEMPTY                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  SPI Tx FIFO empty interrupt */
#define BITM_SPI_STAT_XFRDONE                (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  SPI transfer completion */
#define BITM_SPI_STAT_IRQ                    (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  SPI Interrupt status */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_RX                               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_RX_BYTE2                     8            /*  8-bit receive buffer, used only in DMA modes */
#define BITP_SPI_RX_BYTE1                     0            /*  8-bit receive buffer */
#define BITM_SPI_RX_BYTE2                    (_ADI_MSK_3(0x0000FF00,0x0000FF00U, uint16_t  ))    /*  8-bit receive buffer, used only in DMA modes */
#define BITM_SPI_RX_BYTE1                    (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  8-bit receive buffer */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_TX                               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_TX_BYTE2                     8            /*  8-bit transmit buffer, used only in DMA modes */
#define BITP_SPI_TX_BYTE1                     0            /*  8-bit transmit buffer */
#define BITM_SPI_TX_BYTE2                    (_ADI_MSK_3(0x0000FF00,0x0000FF00U, uint16_t  ))    /*  8-bit transmit buffer, used only in DMA modes */
#define BITM_SPI_TX_BYTE1                    (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  8-bit transmit buffer */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_DIV                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_DIV_VALUE                    0            /*  SPI clock divider */
#define BITM_SPI_DIV_VALUE                   (_ADI_MSK_3(0x0000003F,0x0000003FU, uint16_t  ))    /*  SPI clock divider */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_CTL                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_CTL_CSRST                   14            /*  Reset Mode for CS Error bit */
#define BITP_SPI_CTL_TFLUSH                  13            /*  SPI Tx FIFO Flush enable */
#define BITP_SPI_CTL_RFLUSH                  12            /*  SPI Rx FIFO Flush enable */
#define BITP_SPI_CTL_CON                     11            /*  Continuous transfer enable */
#define BITP_SPI_CTL_LOOPBACK                10            /*  Loopback enable */
#define BITP_SPI_CTL_OEN                      9            /*  Slave MISO output enable */
#define BITP_SPI_CTL_RXOF                     8            /*  RX overflow overwrite enable */
#define BITP_SPI_CTL_ZEN                      7            /*  Transmit zeros enable */
#define BITP_SPI_CTL_TIM                      6            /*  SPI transfer and interrupt mode */
#define BITP_SPI_CTL_LSB                      5            /*  LSB first transfer enable */
#define BITP_SPI_CTL_WOM                      4            /*  SPI Wired Or mode */
#define BITP_SPI_CTL_CPOL                     3            /*  Serial Clock Polarity */
#define BITP_SPI_CTL_CPHA                     2            /*  Serial clock phase mode */
#define BITP_SPI_CTL_MASEN                    1            /*  Master mode enable */
#define BITP_SPI_CTL_SPIEN                    0            /*  SPI enable */
#define BITM_SPI_CTL_CSRST                   (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Reset Mode for CS Error bit */
#define BITM_SPI_CTL_TFLUSH                  (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  SPI Tx FIFO Flush enable */
#define BITM_SPI_CTL_RFLUSH                  (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  SPI Rx FIFO Flush enable */
#define BITM_SPI_CTL_CON                     (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Continuous transfer enable */
#define BITM_SPI_CTL_LOOPBACK                (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Loopback enable */
#define BITM_SPI_CTL_OEN                     (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Slave MISO output enable */
#define BITM_SPI_CTL_RXOF                    (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  RX overflow overwrite enable */
#define BITM_SPI_CTL_ZEN                     (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Transmit zeros enable */
#define BITM_SPI_CTL_TIM                     (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  SPI transfer and interrupt mode */
#define BITM_SPI_CTL_LSB                     (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  LSB first transfer enable */
#define BITM_SPI_CTL_WOM                     (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  SPI Wired Or mode */
#define BITM_SPI_CTL_CPOL                    (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Serial Clock Polarity */
#define BITM_SPI_CTL_CPHA                    (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Serial clock phase mode */
#define BITM_SPI_CTL_MASEN                   (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Master mode enable */
#define BITM_SPI_CTL_SPIEN                   (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  SPI enable */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_IEN                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_IEN_TXEMPTY                 14            /*  Tx-FIFO Empty interrupt enable */
#define BITP_SPI_IEN_XFRDONE                 13            /*  SPI transfer completion interrupt enable */
#define BITP_SPI_IEN_TXDONE                  12            /*  SPI transmit done interrupt enable */
#define BITP_SPI_IEN_RDY                     11            /*  Ready signal edge interrupt enable */
#define BITP_SPI_IEN_RXOVR                   10            /*  Rx-overflow interrupt enable */
#define BITP_SPI_IEN_TXUNDR                   9            /*  Tx-underflow interrupt enable */
#define BITP_SPI_IEN_CS                       8            /*  Enable interrupt on every CS edge in slave CON mode */
#define BITP_SPI_IEN_IRQMODE                  0            /*  SPI IRQ mode bits */
#define BITM_SPI_IEN_TXEMPTY                 (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Tx-FIFO Empty interrupt enable */
#define BITM_SPI_IEN_XFRDONE                 (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  SPI transfer completion interrupt enable */
#define BITM_SPI_IEN_TXDONE                  (_ADI_MSK_3(0x00001000,0x00001000U, uint16_t  ))    /*  SPI transmit done interrupt enable */
#define BITM_SPI_IEN_RDY                     (_ADI_MSK_3(0x00000800,0x00000800U, uint16_t  ))    /*  Ready signal edge interrupt enable */
#define BITM_SPI_IEN_RXOVR                   (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Rx-overflow interrupt enable */
#define BITM_SPI_IEN_TXUNDR                  (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Tx-underflow interrupt enable */
#define BITM_SPI_IEN_CS                      (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Enable interrupt on every CS edge in slave CON mode */
#define BITM_SPI_IEN_IRQMODE                 (_ADI_MSK_3(0x00000007,0x00000007U, uint16_t  ))    /*  SPI IRQ mode bits */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_CNT                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_CNT_FRAMECONT               15            /*  Continue frame */
#define BITP_SPI_CNT_VALUE                    0            /*  Transfer byte count */
#define BITM_SPI_CNT_FRAMECONT               (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Continue frame */
#define BITM_SPI_CNT_VALUE                   (_ADI_MSK_3(0x00003FFF,0x00003FFFU, uint16_t  ))    /*  Transfer byte count */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_DMA                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_DMA_RXEN                     2            /*  Enable receive DMA request */
#define BITP_SPI_DMA_TXEN                     1            /*  Enable transmit DMA request */
#define BITP_SPI_DMA_EN                       0            /*  Enable DMA for data transfer */
#define BITM_SPI_DMA_RXEN                    (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Enable receive DMA request */
#define BITM_SPI_DMA_TXEN                    (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Enable transmit DMA request */
#define BITM_SPI_DMA_EN                      (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Enable DMA for data transfer */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_FIFO_STAT                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_FIFO_STAT_RX                 8            /*  SPI Rx FIFO status */
#define BITP_SPI_FIFO_STAT_TX                 0            /*  SPI Tx FIFO status */
#define BITM_SPI_FIFO_STAT_RX                (_ADI_MSK_3(0x00000F00,0x00000F00U, uint16_t  ))    /*  SPI Rx FIFO status */
#define BITM_SPI_FIFO_STAT_TX                (_ADI_MSK_3(0x0000000F,0x0000000FU, uint16_t  ))    /*  SPI Tx FIFO status */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_RD_CTL                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_RD_CTL_THREEPIN              8            /*  Three pin SPI mode */
#define BITP_SPI_RD_CTL_TXBYTES               2            /*  Transmit byte count minus 1 for read command */
#define BITP_SPI_RD_CTL_OVERLAP               1            /*  Tx/Rx Overlap mode */
#define BITP_SPI_RD_CTL_CMDEN                 0            /*  Read command enable */
#define BITM_SPI_RD_CTL_THREEPIN             (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Three pin SPI mode */
#define BITM_SPI_RD_CTL_TXBYTES              (_ADI_MSK_3(0x0000003C,0x0000003CU, uint16_t  ))    /*  Transmit byte count minus 1 for read command */
#define BITM_SPI_RD_CTL_OVERLAP              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Tx/Rx Overlap mode */
#define BITM_SPI_RD_CTL_CMDEN                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Read command enable */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_FLOW_CTL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_FLOW_CTL_RDBURSTSZ           8            /*  Read data burst size minus 1 */
#define BITP_SPI_FLOW_CTL_RDYPOL              4            /*  Polarity of RDY/MISO line */
#define BITP_SPI_FLOW_CTL_MODE                0            /*  Flow control mode */
#define BITM_SPI_FLOW_CTL_RDBURSTSZ          (_ADI_MSK_3(0x00000F00,0x00000F00U, uint16_t  ))    /*  Read data burst size minus 1 */
#define BITM_SPI_FLOW_CTL_RDYPOL             (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Polarity of RDY/MISO line */
#define BITM_SPI_FLOW_CTL_MODE               (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Flow control mode */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_WAIT_TMR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_WAIT_TMR_VALUE               0            /*  Wait timer for flow-control */
#define BITM_SPI_WAIT_TMR_VALUE              (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Wait timer for flow-control */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_CS_CTL                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_CS_CTL_SEL                   0            /*  Chip-Select control */
#define BITM_SPI_CS_CTL_SEL                  (_ADI_MSK_3(0x0000000F,0x0000000FU, uint16_t  ))    /*  Chip-Select control */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_CS_OVERRIDE                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_CS_OVERRIDE_CTL              0            /*  CS Override Control */
#define BITM_SPI_CS_OVERRIDE_CTL             (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  CS Override Control */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        UART0
   ============================================================================================================================ */
#define REG_UART0_COMRX                      0x40005000            /*  UART0 Receive Buffer Register */
#define REG_UART0_COMTX                      0x40005000            /*  UART0 Transmit Holding Register */
#define REG_UART0_COMIEN                     0x40005004            /*  UART0 Interrupt Enable */
#define REG_UART0_COMIIR                     0x40005008            /*  UART0 Interrupt ID */
#define REG_UART0_COMLCR                     0x4000500C            /*  UART0 Line Control */
#define REG_UART0_COMMCR                     0x40005010            /*  UART0 Modem Control */
#define REG_UART0_COMLSR                     0x40005014            /*  UART0 Line Status */
#define REG_UART0_COMMSR                     0x40005018            /*  UART0 Modem Status */
#define REG_UART0_COMSCR                     0x4000501C            /*  UART0 Scratch buffer */
#define REG_UART0_COMFCR                     0x40005020            /*  UART0 FIFO Control */
#define REG_UART0_COMFBR                     0x40005024            /*  UART0 Fractional Baud Rate */
#define REG_UART0_COMDIV                     0x40005028            /*  UART0 Baudrate divider */
#define REG_UART0_COMLCR2                    0x4000502C            /*  UART0 Second Line Control */
#define REG_UART0_COMCTL                     0x40005030            /*  UART0 UART control register */
#define REG_UART0_COMRFC                     0x40005034            /*  UART0 RX FIFO byte count */
#define REG_UART0_COMTFC                     0x40005038            /*  UART0 TX FIFO byte count */
#define REG_UART0_COMRSC                     0x4000503C            /*  UART0 RS485 half-duplex Control */
#define REG_UART0_COMACR                     0x40005040            /*  UART0 Auto Baud Control */
#define REG_UART0_COMASRL                    0x40005044            /*  UART0 Auto Baud Status (Low) */
#define REG_UART0_COMASRH                    0x40005048            /*  UART0 Auto Baud Status (High) */

/* ============================================================================================================================
        UART Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMRX                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMRX_RBR                   0            /*  Receive Buffer Register */
#define BITM_UART_COMRX_RBR                  (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Receive Buffer Register */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMTX                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMTX_THR                   0            /*  Transmit Holding Register */
#define BITM_UART_COMTX_THR                  (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Transmit Holding Register */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMIEN                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMIEN_EDMAR                5            /*  DMA requests in receive mode */
#define BITP_UART_COMIEN_EDMAT                4            /*  DMA requests in transmit mode */
#define BITP_UART_COMIEN_EDSSI                3            /*  Modem status interrupt */
#define BITP_UART_COMIEN_ELSI                 2            /*  Rx status interrupt */
#define BITP_UART_COMIEN_ETBEI                1            /*  Transmit buffer empty interrupt */
#define BITP_UART_COMIEN_ERBFI                0            /*  Receive buffer full interrupt */
#define BITM_UART_COMIEN_EDMAR               (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  DMA requests in receive mode */
#define BITM_UART_COMIEN_EDMAT               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  DMA requests in transmit mode */
#define BITM_UART_COMIEN_EDSSI               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Modem status interrupt */
#define BITM_UART_COMIEN_ELSI                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Rx status interrupt */
#define BITM_UART_COMIEN_ETBEI               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Transmit buffer empty interrupt */
#define BITM_UART_COMIEN_ERBFI               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Receive buffer full interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMIIR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMIIR_FEND                 6            /*  FIFO enabled */
#define BITP_UART_COMIIR_STA                  1            /*  Interrupt status */
#define BITP_UART_COMIIR_NIRQ                 0            /*  Interrupt flag */
#define BITM_UART_COMIIR_FEND                (_ADI_MSK_3(0x000000C0,0x000000C0U, uint16_t  ))    /*  FIFO enabled */
#define BITM_UART_COMIIR_STA                 (_ADI_MSK_3(0x0000000E,0x0000000EU, uint16_t  ))    /*  Interrupt status */
#define BITM_UART_COMIIR_NIRQ                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Interrupt flag */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMLCR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMLCR_BRK                  6            /*  Set Break */
#define BITP_UART_COMLCR_SP                   5            /*  Stick Parity */
#define BITP_UART_COMLCR_EPS                  4            /*  Parity Select */
#define BITP_UART_COMLCR_PEN                  3            /*  Parity Enable */
#define BITP_UART_COMLCR_STOP                 2            /*  Stop Bit */
#define BITP_UART_COMLCR_WLS                  0            /*  Word Length Select */
#define BITM_UART_COMLCR_BRK                 (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Set Break */
#define BITM_UART_COMLCR_SP                  (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Stick Parity */
#define BITM_UART_COMLCR_EPS                 (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Parity Select */
#define BITM_UART_COMLCR_PEN                 (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Parity Enable */
#define BITM_UART_COMLCR_STOP                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Stop Bit */
#define BITM_UART_COMLCR_WLS                 (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Word Length Select */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMMCR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMMCR_LOOPBACK             4            /*  Loopback mode */
#define BITP_UART_COMMCR_OUT2                 3            /*  Output 2 */
#define BITP_UART_COMMCR_OUT1                 2            /*  Output 1 */
#define BITP_UART_COMMCR_RTS                  1            /*  Request to send */
#define BITP_UART_COMMCR_DTR                  0            /*  Data Terminal Ready */
#define BITM_UART_COMMCR_LOOPBACK            (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Loopback mode */
#define BITM_UART_COMMCR_OUT2                (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Output 2 */
#define BITM_UART_COMMCR_OUT1                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Output 1 */
#define BITM_UART_COMMCR_RTS                 (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Request to send */
#define BITM_UART_COMMCR_DTR                 (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Data Terminal Ready */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMLSR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMLSR_FIFOERR              7            /*  data byte(s) in RX FIFO have either parity error, frame error or break indication. only used in 16550 mode; Read-clear if no more error in RX FIFO */
#define BITP_UART_COMLSR_TEMT                 6            /*  COMTX and Shift Register Empty Status */
#define BITP_UART_COMLSR_THRE                 5            /*  COMTX Empty */
#define BITP_UART_COMLSR_BI                   4            /*  Break Indicator */
#define BITP_UART_COMLSR_FE                   3            /*  Framing Error */
#define BITP_UART_COMLSR_PE                   2            /*  Parity Error */
#define BITP_UART_COMLSR_OE                   1            /*  Overrun Error */
#define BITP_UART_COMLSR_DR                   0            /*  Data Ready */
#define BITM_UART_COMLSR_FIFOERR             (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  data byte(s) in RX FIFO have either parity error, frame error or break indication. only used in 16550 mode; Read-clear if no more error in RX FIFO */
#define BITM_UART_COMLSR_TEMT                (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  COMTX and Shift Register Empty Status */
#define BITM_UART_COMLSR_THRE                (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  COMTX Empty */
#define BITM_UART_COMLSR_BI                  (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Break Indicator */
#define BITM_UART_COMLSR_FE                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Framing Error */
#define BITM_UART_COMLSR_PE                  (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Parity Error */
#define BITM_UART_COMLSR_OE                  (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Overrun Error */
#define BITM_UART_COMLSR_DR                  (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Data Ready */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMMSR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMMSR_DCD                  7            /*  Data Carrier Detect */
#define BITP_UART_COMMSR_RI                   6            /*  Ring Indicator */
#define BITP_UART_COMMSR_DSR                  5            /*  Data Set Ready */
#define BITP_UART_COMMSR_CTS                  4            /*  Clear To Send */
#define BITP_UART_COMMSR_DDCD                 3            /*  Delta DCD */
#define BITP_UART_COMMSR_TERI                 2            /*  Trailing Edge RI */
#define BITP_UART_COMMSR_DDSR                 1            /*  Delta DSR */
#define BITP_UART_COMMSR_DCTS                 0            /*  Delta CTS */
#define BITM_UART_COMMSR_DCD                 (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Data Carrier Detect */
#define BITM_UART_COMMSR_RI                  (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Ring Indicator */
#define BITM_UART_COMMSR_DSR                 (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Data Set Ready */
#define BITM_UART_COMMSR_CTS                 (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Clear To Send */
#define BITM_UART_COMMSR_DDCD                (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Delta DCD */
#define BITM_UART_COMMSR_TERI                (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Trailing Edge RI */
#define BITM_UART_COMMSR_DDSR                (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Delta DSR */
#define BITM_UART_COMMSR_DCTS                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Delta CTS */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMSCR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMSCR_SCR                  0            /*  Scratch */
#define BITM_UART_COMSCR_SCR                 (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Scratch */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMFCR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMFCR_RFTRIG               6            /*  RX FIFO Trig level */
#define BITP_UART_COMFCR_FDMAMD               3            /*  FIFO DMA mode */
#define BITP_UART_COMFCR_TFCLR                2            /*  clear TX FIFO */
#define BITP_UART_COMFCR_RFCLR                1            /*  clear RX FIFO */
#define BITP_UART_COMFCR_FIFOEN               0            /*  FIFO enable as to work in 16550 mode */
#define BITM_UART_COMFCR_RFTRIG              (_ADI_MSK_3(0x000000C0,0x000000C0U, uint16_t  ))    /*  RX FIFO Trig level */
#define BITM_UART_COMFCR_FDMAMD              (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  FIFO DMA mode */
#define BITM_UART_COMFCR_TFCLR               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  clear TX FIFO */
#define BITM_UART_COMFCR_RFCLR               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  clear RX FIFO */
#define BITM_UART_COMFCR_FIFOEN              (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  FIFO enable as to work in 16550 mode */
#define ENUM_UART_COMFCR_MODE0               (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  FDMAMD: in DMA mode 0, RX DMA request will be asserted whenever there's data in RBR or RX FIFO and de-assert whenever RBR or RX FIFO is empty; TX DMA request will be asserted whenever THR or TX FIFO is empty and de-assert whenever data written to */
#define ENUM_UART_COMFCR_MODE1               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  FDMAMD: in DMA mode 1, RX DMA request will be asserted whenever RX FIFO trig level or time out reached and de-assert thereafter when RX FIFO is empty; TX DMA request will be asserted whenever TX FIFO is empty and de-assert thereafter when TX FIFO is completely filled up full; */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMFBR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMFBR_FBEN                15            /*  Fractional baud rate generator enable */
#define BITP_UART_COMFBR_DIVM                11            /*  Fractional baud rate M divide bits 1 to 3 */
#define BITP_UART_COMFBR_DIVN                 0            /*  Fractional baud rate N divide bits 0 to 2047. */
#define BITM_UART_COMFBR_FBEN                (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Fractional baud rate generator enable */
#define BITM_UART_COMFBR_DIVM                (_ADI_MSK_3(0x00001800,0x00001800U, uint16_t  ))    /*  Fractional baud rate M divide bits 1 to 3 */
#define BITM_UART_COMFBR_DIVN                (_ADI_MSK_3(0x000007FF,0x000007FFU, uint16_t  ))    /*  Fractional baud rate N divide bits 0 to 2047. */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMDIV                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMDIV_DIV                  0            /*  Baud rate divider */
#define BITM_UART_COMDIV_DIV                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Baud rate divider */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMLCR2                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMLCR2_OSR                 0            /*  Over Sample Rate */
#define BITM_UART_COMLCR2_OSR                (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Over Sample Rate */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMCTL                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMCTL_REV                  8            /*  UART revision ID */
#define BITP_UART_COMCTL_RXINV                4            /*  invert receiver line */
#define BITP_UART_COMCTL_FORCECLKON           1            /*  Force UCLKg on */
#define BITM_UART_COMCTL_REV                 (_ADI_MSK_3(0x0000FF00,0x0000FF00U, uint16_t  ))    /*  UART revision ID */
#define BITM_UART_COMCTL_RXINV               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  invert receiver line */
#define BITM_UART_COMCTL_FORCECLKON          (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Force UCLKg on */
#define ENUM_UART_COMCTL_EN000               (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  RXINV: don't invert receiver line (idling high) */
#define ENUM_UART_COMCTL_EN001               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  RXINV: invert receiver line (idling low) */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMRFC                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMRFC_RFC                  0            /*  Current RX FIFO data bytes */
#define BITM_UART_COMRFC_RFC                 (_ADI_MSK_3(0x0000001F,0x0000001FU, uint16_t  ))    /*  Current RX FIFO data bytes */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMTFC                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMTFC_TFC                  0            /*  Current TX FIFO data bytes */
#define BITM_UART_COMTFC_TFC                 (_ADI_MSK_3(0x0000001F,0x0000001FU, uint16_t  ))    /*  Current TX FIFO data bytes */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMRSC                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMRSC_DISTX                3            /*  Hold off TX when receiving */
#define BITP_UART_COMRSC_DISRX                2            /*  disable RX when transmitting */
#define BITP_UART_COMRSC_OENSP                1            /*  SOUT_EN de-assert before full stop bit(s) */
#define BITP_UART_COMRSC_OENP                 0            /*  SOUT_EN polarity */
#define BITM_UART_COMRSC_DISTX               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Hold off TX when receiving */
#define BITM_UART_COMRSC_DISRX               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  disable RX when transmitting */
#define BITM_UART_COMRSC_OENSP               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  SOUT_EN de-assert before full stop bit(s) */
#define BITM_UART_COMRSC_OENP                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  SOUT_EN polarity */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMACR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMACR_EEC                  8            /*  Ending Edge Count */
#define BITP_UART_COMACR_SEC                  4            /*  Starting Edge Count */
#define BITP_UART_COMACR_TOIEN                2            /*  enable time-out interrupt */
#define BITP_UART_COMACR_DNIEN                1            /*  enable done interrupt */
#define BITP_UART_COMACR_ABE                  0            /*  Auto Baud enable */
#define BITM_UART_COMACR_EEC                 (_ADI_MSK_3(0x00000F00,0x00000F00U, uint16_t  ))    /*  Ending Edge Count */
#define BITM_UART_COMACR_SEC                 (_ADI_MSK_3(0x00000070,0x00000070U, uint16_t  ))    /*  Starting Edge Count */
#define BITM_UART_COMACR_TOIEN               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  enable time-out interrupt */
#define BITM_UART_COMACR_DNIEN               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  enable done interrupt */
#define BITM_UART_COMACR_ABE                 (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Auto Baud enable */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMASRL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMASRL_CNT                 4            /*  Auto Baud Counter value */
#define BITP_UART_COMASRL_NEETO               3            /*  Timed out due to no valid ending edge found */
#define BITP_UART_COMASRL_NSETO               2            /*  Timed out due to no valid start edge found */
#define BITP_UART_COMASRL_BRKTO               1            /*  Timed out due to long time break condition */
#define BITP_UART_COMASRL_DONE                0            /*  Auto Baud Done successfully */
#define BITM_UART_COMASRL_CNT                (_ADI_MSK_3(0x0000FFF0,0x0000FFF0U, uint16_t  ))    /*  Auto Baud Counter value */
#define BITM_UART_COMASRL_NEETO              (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Timed out due to no valid ending edge found */
#define BITM_UART_COMASRL_NSETO              (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Timed out due to no valid start edge found */
#define BITM_UART_COMASRL_BRKTO              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Timed out due to long time break condition */
#define BITM_UART_COMASRL_DONE               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Auto Baud Done successfully */

/* -------------------------------------------------------------------------------------------------------------------------
          UART_COMASRH                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UART_COMASRH_CNT                 0            /*  Auto Baud Counter value */
#define BITM_UART_COMASRH_CNT                (_ADI_MSK_3(0x000000FF,0x000000FFU, uint16_t  ))    /*  Auto Baud Counter value */


/* ============================================================================================================================
        DMA
   ============================================================================================================================ */

/* ============================================================================================================================
        DMA0
   ============================================================================================================================ */
#define REG_DMA0_STAT                        0x40010000            /*  DMA0 DMA Status */
#define REG_DMA0_CFG                         0x40010004            /*  DMA0 DMA Configuration */
#define REG_DMA0_PDBPTR                      0x40010008            /*  DMA0 DMA channel primary control data base pointer */
#define REG_DMA0_ADBPTR                      0x4001000C            /*  DMA0 DMA channel alternate control data base pointer */
#define REG_DMA0_SWREQ                       0x40010014            /*  DMA0 DMA channel software request */
#define REG_DMA0_RMSK_SET                    0x40010020            /*  DMA0 DMA channel request mask set */
#define REG_DMA0_RMSK_CLR                    0x40010024            /*  DMA0 DMA channel request mask clear */
#define REG_DMA0_EN_SET                      0x40010028            /*  DMA0 DMA channel enable set */
#define REG_DMA0_EN_CLR                      0x4001002C            /*  DMA0 DMA channel enable clear */
#define REG_DMA0_ALT_SET                     0x40010030            /*  DMA0 DMA channel primary-alternate set */
#define REG_DMA0_ALT_CLR                     0x40010034            /*  DMA0 DMA channel primary-alternate clear */
#define REG_DMA0_PRI_SET                     0x40010038            /*  DMA0 DMA channel priority set */
#define REG_DMA0_PRI_CLR                     0x4001003C            /*  DMA0 DMA channel priority clear */
#define REG_DMA0_ERRCHNL_CLR                 0x40010048            /*  DMA0 DMA Per Channel Error Clear */
#define REG_DMA0_ERR_CLR                     0x4001004C            /*  DMA0 DMA bus error clear */
#define REG_DMA0_INVALIDDESC_CLR             0x40010050            /*  DMA0 DMA Per Channel Invalid Descriptor Clear */
#define REG_DMA0_BS_SET                      0x40010800            /*  DMA0 DMA channel bytes swap enable set */
#define REG_DMA0_BS_CLR                      0x40010804            /*  DMA0 DMA channel bytes swap enable clear */
#define REG_DMA0_SRCADDR_SET                 0x40010810            /*  DMA0 DMA channel source address decrement enable set */
#define REG_DMA0_SRCADDR_CLR                 0x40010814            /*  DMA0 DMA channel source address decrement enable clear */
#define REG_DMA0_DSTADDR_SET                 0x40010818            /*  DMA0 DMA channel destination address decrement enable set */
#define REG_DMA0_DSTADDR_CLR                 0x4001081C            /*  DMA0 DMA channel destination address decrement enable clear */
#define REG_DMA0_REVID                       0x40010FE0            /*  DMA0 DMA Controller Revision ID */

/* ============================================================================================================================
        DMA Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          DMA_STAT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_STAT_CHANM1                 16            /*  Number of available DMA channels minus 1 */
#define BITP_DMA_STAT_MEN                     0            /*  Enable status of the controller */
#define BITM_DMA_STAT_CHANM1                 (_ADI_MSK_3(0x001F0000,0x001F0000UL, uint32_t  ))    /*  Number of available DMA channels minus 1 */
#define BITM_DMA_STAT_MEN                    (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable status of the controller */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_CFG                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_CFG_MEN                      0            /*  Controller enable */
#define BITM_DMA_CFG_MEN                     (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Controller enable */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_PDBPTR                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_PDBPTR_ADDR                  0            /*  Pointer to the base address of the primary data structure */
#define BITM_DMA_PDBPTR_ADDR                 (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Pointer to the base address of the primary data structure */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_ADBPTR                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_ADBPTR_ADDR                  0            /*  Base address of the alternate data structure */
#define BITM_DMA_ADBPTR_ADDR                 (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Base address of the alternate data structure */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_SWREQ                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_SWREQ_CHAN                   0            /*  Generate software request */
#define BITM_DMA_SWREQ_CHAN                  (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Generate software request */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_RMSK_SET                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_RMSK_SET_CHAN                0            /*  Mask requests from DMA channels */
#define BITM_DMA_RMSK_SET_CHAN               (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Mask requests from DMA channels */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_RMSK_CLR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_RMSK_CLR_CHAN                0            /*  Clear Request Mask Set bits */
#define BITM_DMA_RMSK_CLR_CHAN               (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Clear Request Mask Set bits */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_EN_SET                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_EN_SET_CHAN                  0            /*  Enable DMA channels */
#define BITM_DMA_EN_SET_CHAN                 (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Enable DMA channels */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_EN_CLR                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_EN_CLR_CHAN                  0            /*  Disable DMA channels */
#define BITM_DMA_EN_CLR_CHAN                 (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Disable DMA channels */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_ALT_SET                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_ALT_SET_CHAN                 0            /*  Control struct status / select alt struct */
#define BITM_DMA_ALT_SET_CHAN                (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Control struct status / select alt struct */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_ALT_CLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_ALT_CLR_CHAN                 0            /*  Select primary data struct */
#define BITM_DMA_ALT_CLR_CHAN                (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Select primary data struct */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_PRI_SET                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_PRI_SET_CHAN                 0            /*  Configure channel for high priority */
#define BITM_DMA_PRI_SET_CHAN                (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Configure channel for high priority */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_PRI_CLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_PRI_CLR_CHPRICLR             0            /*  Configure channel for default priority level */
#define BITM_DMA_PRI_CLR_CHPRICLR            (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Configure channel for default priority level */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_ERRCHNL_CLR                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_ERRCHNL_CLR_CHAN             0            /*  Per channel Bus error status/ Per channel bus error clear */
#define BITM_DMA_ERRCHNL_CLR_CHAN            (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Per channel Bus error status/ Per channel bus error clear */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_ERR_CLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_ERR_CLR_CHAN                 0            /*  Bus error status */
#define BITM_DMA_ERR_CLR_CHAN                (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Bus error status */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_INVALIDDESC_CLR                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_INVALIDDESC_CLR_CHAN         0            /*  Per channel Invalid Descriptor status/ Per channel Invalid descriptor status clear */
#define BITM_DMA_INVALIDDESC_CLR_CHAN        (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Per channel Invalid Descriptor status/ Per channel Invalid descriptor status clear */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_BS_SET                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_BS_SET_CHAN                  0            /*  Byte swap status */
#define BITM_DMA_BS_SET_CHAN                 (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Byte swap status */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_BS_CLR                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_BS_CLR_CHAN                  0            /*  Disable byte swap */
#define BITM_DMA_BS_CLR_CHAN                 (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Disable byte swap */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_SRCADDR_SET                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_SRCADDR_SET_CHAN             0            /*  Source Address decrement status / configure Source address decrement */
#define BITM_DMA_SRCADDR_SET_CHAN            (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Source Address decrement status / configure Source address decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_SRCADDR_CLR                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_SRCADDR_CLR_CHAN             0            /*  Disable source address decrement */
#define BITM_DMA_SRCADDR_CLR_CHAN            (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Disable source address decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_DSTADDR_SET                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_DSTADDR_SET_CHAN             0            /*  Destination Address decrement status / configure destination address decrement */
#define BITM_DMA_DSTADDR_SET_CHAN            (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Destination Address decrement status / configure destination address decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_DSTADDR_CLR                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_DSTADDR_CLR_CHAN             0            /*  Disable destination address decrement */
#define BITM_DMA_DSTADDR_CLR_CHAN            (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Disable destination address decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          DMA_REVID                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DMA_REVID_VALUE                  0            /*  DMA Controller revision ID */
#define BITM_DMA_REVID_VALUE                 (_ADI_MSK_3(0x000000FF,0x000000FFUL, uint32_t  ))    /*  DMA Controller revision ID */


/* ============================================================================================================================
        Flash Controller
   ============================================================================================================================ */

/* ============================================================================================================================
        FLCC0
   ============================================================================================================================ */
#define REG_FLCC0_STAT                       0x40018000            /*  FLCC0 Status */
#define REG_FLCC0_IEN                        0x40018004            /*  FLCC0 Interrupt Enable */
#define REG_FLCC0_CMD                        0x40018008            /*  FLCC0 Command */
#define REG_FLCC0_KH_ADDR                    0x4001800C            /*  FLCC0 WRITE Address */
#define REG_FLCC0_KH_DATA0                   0x40018010            /*  FLCC0 WRITE Lower Data */
#define REG_FLCC0_KH_DATA1                   0x40018014            /*  FLCC0 WRITE Upper Data */
#define REG_FLCC0_PAGE_ADDR0                 0x40018018            /*  FLCC0 Lower Page Address */
#define REG_FLCC0_PAGE_ADDR1                 0x4001801C            /*  FLCC0 Upper Page Address */
#define REG_FLCC0_KEY                        0x40018020            /*  FLCC0 Key */
#define REG_FLCC0_WR_ABORT_ADDR              0x40018024            /*  FLCC0 Write Abort Address */
#define REG_FLCC0_WRPROT                     0x40018028            /*  FLCC0 Write Protection */
#define REG_FLCC0_SIGNATURE                  0x4001802C            /*  FLCC0 Signature */
#define REG_FLCC0_UCFG                       0x40018030            /*  FLCC0 User Configuration */
#define REG_FLCC0_TIME_PARAM0                0x40018034            /*  FLCC0 Time Parameter 0 */
#define REG_FLCC0_TIME_PARAM1                0x40018038            /*  FLCC0 Time parameter 1 */
#define REG_FLCC0_ABORT_EN_LO                0x4001803C            /*  FLCC0 IRQ Abort Enable (lower bits) */
#define REG_FLCC0_ABORT_EN_HI                0x40018040            /*  FLCC0 IRQ Abort Enable (upper bits) */
#define REG_FLCC0_ECC_CFG                    0x40018044            /*  FLCC0 ECC Config */
#define REG_FLCC0_ECC_ADDR                   0x40018048            /*  FLCC0 ECC Status (Address) */
#define REG_FLCC0_ADI_POR_SEC                0x40018050            /*  FLCC0 ADI flash security */

/* ============================================================================================================================
        FLCC Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_STAT                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_STAT_CACHESRAMPERR         29            /*  SRAM parity errors in Cache Controller */
#define BITP_FLCC_STAT_ECCDCODE              27            /*  DCode AHB Bus Error ECC status */
#define BITP_FLCC_STAT_ECCICODE              25            /*  ICode AHB Bus Error ECC status */
#define BITP_FLCC_STAT_ECCERRCNT             17            /*  ECC correction counter */
#define BITP_FLCC_STAT_ECCINFOSIGN           15            /*  ECC status of flash initialization */
#define BITP_FLCC_STAT_INIT                  14            /*  Flash controller initialization in progress */
#define BITP_FLCC_STAT_SIGNERR               13            /*  Signature check failure during initialization */
#define BITP_FLCC_STAT_OVERLAP               11            /*  Overlapping Command */
#define BITP_FLCC_STAT_ECCRDERR               9            /*  ECC IRQ cause */
#define BITP_FLCC_STAT_ECCERRCMD              7            /*  ECC errors detected during user issued SIGN command */
#define BITP_FLCC_STAT_SLEEPING               6            /*  Flash array is in low power (sleep) mode */
#define BITP_FLCC_STAT_CMDFAIL                4            /*  Provides information on command failures */
#define BITP_FLCC_STAT_WRALCOMP               3            /*  Write almost complete */
#define BITP_FLCC_STAT_CMDCOMP                2            /*  Command complete */
#define BITP_FLCC_STAT_WRCLOSE                1            /*  WRITE registers are closed */
#define BITP_FLCC_STAT_CMDBUSY                0            /*  Command busy */
#define BITM_FLCC_STAT_CACHESRAMPERR         (_ADI_MSK_3(0x20000000,0x20000000UL, uint32_t  ))    /*  SRAM parity errors in Cache Controller */
#define BITM_FLCC_STAT_ECCDCODE              (_ADI_MSK_3(0x18000000,0x18000000UL, uint32_t  ))    /*  DCode AHB Bus Error ECC status */
#define BITM_FLCC_STAT_ECCICODE              (_ADI_MSK_3(0x06000000,0x06000000UL, uint32_t  ))    /*  ICode AHB Bus Error ECC status */
#define BITM_FLCC_STAT_ECCERRCNT             (_ADI_MSK_3(0x000E0000,0x000E0000UL, uint32_t  ))    /*  ECC correction counter */
#define BITM_FLCC_STAT_ECCINFOSIGN           (_ADI_MSK_3(0x00018000,0x00018000UL, uint32_t  ))    /*  ECC status of flash initialization */
#define BITM_FLCC_STAT_INIT                  (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  Flash controller initialization in progress */
#define BITM_FLCC_STAT_SIGNERR               (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  Signature check failure during initialization */
#define BITM_FLCC_STAT_OVERLAP               (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Overlapping Command */
#define BITM_FLCC_STAT_ECCRDERR              (_ADI_MSK_3(0x00000600,0x00000600UL, uint32_t  ))    /*  ECC IRQ cause */
#define BITM_FLCC_STAT_ECCERRCMD             (_ADI_MSK_3(0x00000180,0x00000180UL, uint32_t  ))    /*  ECC errors detected during user issued SIGN command */
#define BITM_FLCC_STAT_SLEEPING              (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Flash array is in low power (sleep) mode */
#define BITM_FLCC_STAT_CMDFAIL               (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  Provides information on command failures */
#define BITM_FLCC_STAT_WRALCOMP              (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Write almost complete */
#define BITM_FLCC_STAT_CMDCOMP               (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Command complete */
#define BITM_FLCC_STAT_WRCLOSE               (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  WRITE registers are closed */
#define BITM_FLCC_STAT_CMDBUSY               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Command busy */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_IEN                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_IEN_ECC_ERROR               6            /*  Control whether to generate bus errors, interrupts, or neither in response to 2-bit ECC Error events */
#define BITP_FLCC_IEN_ECC_CORRECT             4            /*  Control whether to generate bus errors, interrupts, or neither in response to 1-bit ECC Correction events */
#define BITP_FLCC_IEN_CMDFAIL                 2            /*  Command fail interrupt enable */
#define BITP_FLCC_IEN_WRALCMPLT               1            /*  Write almost complete interrupt enable */
#define BITP_FLCC_IEN_CMDCMPLT                0            /*  Command complete interrupt enable */
#define BITM_FLCC_IEN_ECC_ERROR              (_ADI_MSK_3(0x000000C0,0x000000C0UL, uint32_t  ))    /*  Control whether to generate bus errors, interrupts, or neither in response to 2-bit ECC Error events */
#define BITM_FLCC_IEN_ECC_CORRECT            (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  Control whether to generate bus errors, interrupts, or neither in response to 1-bit ECC Correction events */
#define BITM_FLCC_IEN_CMDFAIL                (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Command fail interrupt enable */
#define BITM_FLCC_IEN_WRALCMPLT              (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Write almost complete interrupt enable */
#define BITM_FLCC_IEN_CMDCMPLT               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Command complete interrupt enable */
#define ENUM_FLCC_IEN_NONE_ERR               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  ECC_ERROR: Do not generate a response to ECC events */
#define ENUM_FLCC_IEN_BUS_ERR_ERR            (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  ECC_ERROR: Generate Bus Errors in response to ECC events */
#define ENUM_FLCC_IEN_IRQ_ERR                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  ECC_ERROR: Generate IRQs in response to ECC events */
#define ENUM_FLCC_IEN_NONE_COR               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  ECC_CORRECT: Do not generate a response to ECC events */
#define ENUM_FLCC_IEN_BUS_ERR_COR            (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  ECC_CORRECT: Generate Bus Errors in response to ECC events */
#define ENUM_FLCC_IEN_IRQ_COR                (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  ECC_CORRECT: Generate IRQs in response to ECC events */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_CMD                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_CMD_VALUE                   0            /*  Commands */
#define BITM_FLCC_CMD_VALUE                  (_ADI_MSK_3(0x0000000F,0x0000000FUL, uint32_t  ))    /*  Commands */
#define ENUM_FLCC_CMD_IDLE                   (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  VALUE: IDLE */
#define ENUM_FLCC_CMD_ABORT                  (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  VALUE: ABORT */
#define ENUM_FLCC_CMD_SLEEP                  (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  VALUE: Requests flash to enter Sleep mode */
#define ENUM_FLCC_CMD_SIGN                   (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  VALUE: SIGN */
#define ENUM_FLCC_CMD_WRITE                  (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  VALUE: WRITE */
#define ENUM_FLCC_CMD_BLANK_CHECK            (_ADI_MSK_3(0x00000005,0x00000005UL, uint32_t  ))    /*  VALUE: Checks all of User Space; fails if any bits in user space are cleared */
#define ENUM_FLCC_CMD_ERASEPAGE              (_ADI_MSK_3(0x00000006,0x00000006UL, uint32_t  ))    /*  VALUE: ERASEPAGE */
#define ENUM_FLCC_CMD_MASSERASE              (_ADI_MSK_3(0x00000007,0x00000007UL, uint32_t  ))    /*  VALUE: MASSERASE */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_KH_ADDR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_KH_ADDR_VALUE               3            /*  Address to be written on a WRITE command */
#define BITM_FLCC_KH_ADDR_VALUE              (_ADI_MSK_3(0x0007FFF8,0x0007FFF8UL, uint32_t  ))    /*  Address to be written on a WRITE command */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_KH_DATA0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_KH_DATA0_VALUE              0            /*  Lower half of 64-bit dual word data to be written on a WRITE command */
#define BITM_FLCC_KH_DATA0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Lower half of 64-bit dual word data to be written on a WRITE command */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_KH_DATA1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_KH_DATA1_VALUE              0            /*  Upper half of 64-bit dual word data to be written on a WRITE command */
#define BITM_FLCC_KH_DATA1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Upper half of 64-bit dual word data to be written on a WRITE command */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_PAGE_ADDR0                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_PAGE_ADDR0_VALUE           10            /*  Lower address bits of the page address */
#define BITM_FLCC_PAGE_ADDR0_VALUE           (_ADI_MSK_3(0x0007FC00,0x0007FC00UL, uint32_t  ))    /*  Lower address bits of the page address */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_PAGE_ADDR1                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_PAGE_ADDR1_VALUE           10            /*  Upper address bits of the page address */
#define BITM_FLCC_PAGE_ADDR1_VALUE           (_ADI_MSK_3(0x0007FC00,0x0007FC00UL, uint32_t  ))    /*  Upper address bits of the page address */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_KEY                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_KEY_VALUE                   0            /*  Key register */
#define BITM_FLCC_KEY_VALUE                  (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Key register */
#define ENUM_FLCC_KEY_USERKEY                (_ADI_MSK_3(0x676C7565,0x676C7565, int32_t   ))    /*  VALUE: USERKEY */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_WR_ABORT_ADDR                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_WR_ABORT_ADDR_VALUE         0            /*  Holds the address targeted by an ongoing write command and retains its value after an ABORT event */
#define BITM_FLCC_WR_ABORT_ADDR_VALUE        (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Holds the address targeted by an ongoing write command and retains its value after an ABORT event */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_WRPROT                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_WRPROT_WORD                 0            /*  Clear bits to write protect related groups of user space pages. Once cleared these bits can only be set again by resetting the part */
#define BITM_FLCC_WRPROT_WORD                (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Clear bits to write protect related groups of user space pages. Once cleared these bits can only be set again by resetting the part */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_SIGNATURE                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_SIGNATURE_VALUE             0            /*  Provides read access to the most recently generated signature */
#define BITM_FLCC_SIGNATURE_VALUE            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Provides read access to the most recently generated signature */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_UCFG                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_UCFG_AUTOINCEN              1            /*  Auto address increment for Key hole access */
#define BITP_FLCC_UCFG_KHDMAEN                0            /*  Key Hole DMA enable */
#define BITM_FLCC_UCFG_AUTOINCEN             (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Auto address increment for Key hole access */
#define BITM_FLCC_UCFG_KHDMAEN               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Key Hole DMA enable */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_TIME_PARAM0                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_TIME_PARAM0_TNVH1          28            /*  NVSTR Hold time during Mass Erase */
#define BITP_FLCC_TIME_PARAM0_TERASE         24            /*  Erase Time */
#define BITP_FLCC_TIME_PARAM0_TRCV           20            /*  Recovery time */
#define BITP_FLCC_TIME_PARAM0_TNVH           16            /*  NVSTR Hold time */
#define BITP_FLCC_TIME_PARAM0_TPROG          12            /*  Program time */
#define BITP_FLCC_TIME_PARAM0_TPGS            8            /*  NVSTR to Program setup time */
#define BITP_FLCC_TIME_PARAM0_TNVS            4            /*  PROG/ERASE to NVSTR setup time */
#define BITP_FLCC_TIME_PARAM0_DIVREFCLK       0            /*  Divide Reference Clock (by 2) */
#define BITM_FLCC_TIME_PARAM0_TNVH1          (_ADI_MSK_3(0xF0000000,0xF0000000UL, uint32_t  ))    /*  NVSTR Hold time during Mass Erase */
#define BITM_FLCC_TIME_PARAM0_TERASE         (_ADI_MSK_3(0x0F000000,0x0F000000UL, uint32_t  ))    /*  Erase Time */
#define BITM_FLCC_TIME_PARAM0_TRCV           (_ADI_MSK_3(0x00F00000,0x00F00000UL, uint32_t  ))    /*  Recovery time */
#define BITM_FLCC_TIME_PARAM0_TNVH           (_ADI_MSK_3(0x000F0000,0x000F0000UL, uint32_t  ))    /*  NVSTR Hold time */
#define BITM_FLCC_TIME_PARAM0_TPROG          (_ADI_MSK_3(0x0000F000,0x0000F000UL, uint32_t  ))    /*  Program time */
#define BITM_FLCC_TIME_PARAM0_TPGS           (_ADI_MSK_3(0x00000F00,0x00000F00UL, uint32_t  ))    /*  NVSTR to Program setup time */
#define BITM_FLCC_TIME_PARAM0_TNVS           (_ADI_MSK_3(0x000000F0,0x000000F0UL, uint32_t  ))    /*  PROG/ERASE to NVSTR setup time */
#define BITM_FLCC_TIME_PARAM0_DIVREFCLK      (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Divide Reference Clock (by 2) */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_TIME_PARAM1                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_TIME_PARAM1_TWK             0            /*  Wake up time */
#define BITM_FLCC_TIME_PARAM1_TWK            (_ADI_MSK_3(0x0000000F,0x0000000FUL, uint32_t  ))    /*  Wake up time */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_ABORT_EN_LO                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_ABORT_EN_LO_VALUE           0            /*  Sys IRQ abort enable */
#define BITM_FLCC_ABORT_EN_LO_VALUE          (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Sys IRQ abort enable */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_ABORT_EN_HI                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_ABORT_EN_HI_VALUE           0            /*  Sys IRQ abort enable */
#define BITM_FLCC_ABORT_EN_HI_VALUE          (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Sys IRQ abort enable */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_ECC_CFG                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_ECC_CFG_PTR                 8            /*  ECC start page pointer (user should write bits [31:8] of the start page address into bits [31:8] of this register) */
#define BITP_FLCC_ECC_CFG_INFOEN              1            /*  Info space ECC Enable bit */
#define BITP_FLCC_ECC_CFG_EN                  0            /*  ECC Enable */
#define BITM_FLCC_ECC_CFG_PTR                (_ADI_MSK_3(0xFFFFFF00,0xFFFFFF00UL, uint32_t  ))    /*  ECC start page pointer (user should write bits [31:8] of the start page address into bits [31:8] of this register) */
#define BITM_FLCC_ECC_CFG_INFOEN             (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Info space ECC Enable bit */
#define BITM_FLCC_ECC_CFG_EN                 (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  ECC Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_ECC_ADDR                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_ECC_ADDR_VALUE              0            /*  This register has the address for which ECC error is detected */
#define BITM_FLCC_ECC_ADDR_VALUE             (_ADI_MSK_3(0x0007FFFF,0x0007FFFFUL, uint32_t  ))    /*  This register has the address for which ECC error is detected */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_ADI_POR_SEC                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_ADI_POR_SEC_SECURE          0            /*  Set this bit to prevent read or write access to User Space (sticky when set) */
#define BITM_FLCC_ADI_POR_SEC_SECURE         (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Set this bit to prevent read or write access to User Space (sticky when set) */


/* ============================================================================================================================
        Cache Controller
   ============================================================================================================================ */

/* ============================================================================================================================
        FLCC0_CACHE
   ============================================================================================================================ */
#define REG_FLCC0_CACHE_STAT                 0x40018058            /*  FLCC0_CACHE Cache Status register */
#define REG_FLCC0_CACHE_SETUP                0x4001805C            /*  FLCC0_CACHE Cache Setup register */
#define REG_FLCC0_CACHE_KEY                  0x40018060            /*  FLCC0_CACHE Cache Key register */

/* ============================================================================================================================
        FLCC_CACHE Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_CACHE_STAT                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_CACHE_STAT_ICEN             0            /*  If this bit is set then I-Cache is enabled and when cleared I-Cache is disabled. */
#define BITM_FLCC_CACHE_STAT_ICEN            (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  If this bit is set then I-Cache is enabled and when cleared I-Cache is disabled. */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_CACHE_SETUP                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_CACHE_SETUP_ICEN            0            /*  If this bit set, then I-Cache is enabled for AHB accesses. If 0, then I-cache is disabled, and all AHB accesses will be via Flash memory. */
#define BITM_FLCC_CACHE_SETUP_ICEN           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  If this bit set, then I-Cache is enabled for AHB accesses. If 0, then I-cache is disabled, and all AHB accesses will be via Flash memory. */

/* -------------------------------------------------------------------------------------------------------------------------
          FLCC_CACHE_KEY                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FLCC_CACHE_KEY_VALUE             0            /*  Cache Key register */
#define BITM_FLCC_CACHE_KEY_VALUE            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Cache Key register */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        GPIO0
   ============================================================================================================================ */
#define REG_GPIO0_CFG                        0x40020000            /*  GPIO0 Port  Configuration */
#define REG_GPIO0_OEN                        0x40020004            /*  GPIO0 Port output enable */
#define REG_GPIO0_PE                         0x40020008            /*  GPIO0 Port output pullup/pulldown enable */
#define REG_GPIO0_IEN                        0x4002000C            /*  GPIO0 Port  Input Path Enable */
#define REG_GPIO0_IN                         0x40020010            /*  GPIO0 Port  registered data input */
#define REG_GPIO0_OUT                        0x40020014            /*  GPIO0 Port data output */
#define REG_GPIO0_SET                        0x40020018            /*  GPIO0 Port data out set */
#define REG_GPIO0_CLR                        0x4002001C            /*  GPIO0 Port Data Out Clear */
#define REG_GPIO0_TGL                        0x40020020            /*  GPIO0 Port Pin Toggle */
#define REG_GPIO0_POL                        0x40020024            /*  GPIO0 Port Interrupt Polarity */
#define REG_GPIO0_IENA                       0x40020028            /*  GPIO0 Port Interrupt A Enable */
#define REG_GPIO0_IENB                       0x4002002C            /*  GPIO0 Port Interrupt B Enable */
#define REG_GPIO0_INT                        0x40020030            /*  GPIO0 Port Interrupt Status */
#define REG_GPIO0_DS                         0x40020034            /*  GPIO0 Port Drive Strength Select */

/* ============================================================================================================================
        GPIO1
   ============================================================================================================================ */
#define REG_GPIO1_CFG                        0x40020040            /*  GPIO1 Port  Configuration */
#define REG_GPIO1_OEN                        0x40020044            /*  GPIO1 Port output enable */
#define REG_GPIO1_PE                         0x40020048            /*  GPIO1 Port output pullup/pulldown enable */
#define REG_GPIO1_IEN                        0x4002004C            /*  GPIO1 Port  Input Path Enable */
#define REG_GPIO1_IN                         0x40020050            /*  GPIO1 Port  registered data input */
#define REG_GPIO1_OUT                        0x40020054            /*  GPIO1 Port data output */
#define REG_GPIO1_SET                        0x40020058            /*  GPIO1 Port data out set */
#define REG_GPIO1_CLR                        0x4002005C            /*  GPIO1 Port Data Out Clear */
#define REG_GPIO1_TGL                        0x40020060            /*  GPIO1 Port Pin Toggle */
#define REG_GPIO1_POL                        0x40020064            /*  GPIO1 Port Interrupt Polarity */
#define REG_GPIO1_IENA                       0x40020068            /*  GPIO1 Port Interrupt A Enable */
#define REG_GPIO1_IENB                       0x4002006C            /*  GPIO1 Port Interrupt B Enable */
#define REG_GPIO1_INT                        0x40020070            /*  GPIO1 Port Interrupt Status */
#define REG_GPIO1_DS                         0x40020074            /*  GPIO1 Port Drive Strength Select */

/* ============================================================================================================================
        GPIO2
   ============================================================================================================================ */
#define REG_GPIO2_CFG                        0x40020080            /*  GPIO2 Port  Configuration */
#define REG_GPIO2_OEN                        0x40020084            /*  GPIO2 Port output enable */
#define REG_GPIO2_PE                         0x40020088            /*  GPIO2 Port output pullup/pulldown enable */
#define REG_GPIO2_IEN                        0x4002008C            /*  GPIO2 Port  Input Path Enable */
#define REG_GPIO2_IN                         0x40020090            /*  GPIO2 Port  registered data input */
#define REG_GPIO2_OUT                        0x40020094            /*  GPIO2 Port data output */
#define REG_GPIO2_SET                        0x40020098            /*  GPIO2 Port data out set */
#define REG_GPIO2_CLR                        0x4002009C            /*  GPIO2 Port Data Out Clear */
#define REG_GPIO2_TGL                        0x400200A0            /*  GPIO2 Port Pin Toggle */
#define REG_GPIO2_POL                        0x400200A4            /*  GPIO2 Port Interrupt Polarity */
#define REG_GPIO2_IENA                       0x400200A8            /*  GPIO2 Port Interrupt A Enable */
#define REG_GPIO2_IENB                       0x400200AC            /*  GPIO2 Port Interrupt B Enable */
#define REG_GPIO2_INT                        0x400200B0            /*  GPIO2 Port Interrupt Status */
#define REG_GPIO2_DS                         0x400200B4            /*  GPIO2 Port Drive Strength Select */

/* ============================================================================================================================
        GPIO Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_CFG                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_CFG_PIN15                  30            /*  Pin 15  configuration bits */
#define BITP_GPIO_CFG_PIN14                  28            /*  Pin 14  configuration bits */
#define BITP_GPIO_CFG_PIN13                  26            /*  Pin 13  configuration bits */
#define BITP_GPIO_CFG_PIN12                  24            /*  Pin 12  configuration bits */
#define BITP_GPIO_CFG_PIN11                  22            /*  Pin 11  configuration bits */
#define BITP_GPIO_CFG_PIN10                  20            /*  Pin 10  configuration bits */
#define BITP_GPIO_CFG_PIN09                  18            /*  Pin 9 configuration bits */
#define BITP_GPIO_CFG_PIN08                  16            /*  Pin 8 configuration bits */
#define BITP_GPIO_CFG_PIN07                  14            /*  Pin 7 configuration bits */
#define BITP_GPIO_CFG_PIN06                  12            /*  Pin 6 configuration bits */
#define BITP_GPIO_CFG_PIN05                  10            /*  Pin 5 configuration bits */
#define BITP_GPIO_CFG_PIN04                   8            /*  Pin 4 configuration bits */
#define BITP_GPIO_CFG_PIN03                   6            /*  Pin 3 configuration bits */
#define BITP_GPIO_CFG_PIN02                   4            /*  Pin 2 configuration bits */
#define BITP_GPIO_CFG_PIN01                   2            /*  Pin 1 configuration bits */
#define BITP_GPIO_CFG_PIN00                   0            /*  Pin 0 configuration bits */
#define BITM_GPIO_CFG_PIN15                  (_ADI_MSK_3(0xC0000000,0xC0000000UL, uint32_t  ))    /*  Pin 15  configuration bits */
#define BITM_GPIO_CFG_PIN14                  (_ADI_MSK_3(0x30000000,0x30000000UL, uint32_t  ))    /*  Pin 14  configuration bits */
#define BITM_GPIO_CFG_PIN13                  (_ADI_MSK_3(0x0C000000,0x0C000000UL, uint32_t  ))    /*  Pin 13  configuration bits */
#define BITM_GPIO_CFG_PIN12                  (_ADI_MSK_3(0x03000000,0x03000000UL, uint32_t  ))    /*  Pin 12  configuration bits */
#define BITM_GPIO_CFG_PIN11                  (_ADI_MSK_3(0x00C00000,0x00C00000UL, uint32_t  ))    /*  Pin 11  configuration bits */
#define BITM_GPIO_CFG_PIN10                  (_ADI_MSK_3(0x00300000,0x00300000UL, uint32_t  ))    /*  Pin 10  configuration bits */
#define BITM_GPIO_CFG_PIN09                  (_ADI_MSK_3(0x000C0000,0x000C0000UL, uint32_t  ))    /*  Pin 9 configuration bits */
#define BITM_GPIO_CFG_PIN08                  (_ADI_MSK_3(0x00030000,0x00030000UL, uint32_t  ))    /*  Pin 8 configuration bits */
#define BITM_GPIO_CFG_PIN07                  (_ADI_MSK_3(0x0000C000,0x0000C000UL, uint32_t  ))    /*  Pin 7 configuration bits */
#define BITM_GPIO_CFG_PIN06                  (_ADI_MSK_3(0x00003000,0x00003000UL, uint32_t  ))    /*  Pin 6 configuration bits */
#define BITM_GPIO_CFG_PIN05                  (_ADI_MSK_3(0x00000C00,0x00000C00UL, uint32_t  ))    /*  Pin 5 configuration bits */
#define BITM_GPIO_CFG_PIN04                  (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  Pin 4 configuration bits */
#define BITM_GPIO_CFG_PIN03                  (_ADI_MSK_3(0x000000C0,0x000000C0UL, uint32_t  ))    /*  Pin 3 configuration bits */
#define BITM_GPIO_CFG_PIN02                  (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  Pin 2 configuration bits */
#define BITM_GPIO_CFG_PIN01                  (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  Pin 1 configuration bits */
#define BITM_GPIO_CFG_PIN00                  (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  Pin 0 configuration bits */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_OEN                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_OEN_VALUE                   0            /*  Pin Output Drive enable */
#define BITM_GPIO_OEN_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Pin Output Drive enable */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_PE                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_PE_VALUE                    0            /*  Pin Pull enable */
#define BITM_GPIO_PE_VALUE                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Pin Pull enable */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_IEN                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_IEN_VALUE                   0            /*  Input path enable */
#define BITM_GPIO_IEN_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Input path enable */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_IN                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_IN_VALUE                    0            /*  Registered data input */
#define BITM_GPIO_IN_VALUE                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Registered data input */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_OUT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_OUT_VALUE                   0            /*  Data out */
#define BITM_GPIO_OUT_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Data out */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_SET                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_SET_VALUE                   0            /*  Set the output HIGH for the pin */
#define BITM_GPIO_SET_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Set the output HIGH for the pin */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_CLR                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_CLR_VALUE                   0            /*  Set the output low  for the port pin */
#define BITM_GPIO_CLR_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Set the output low  for the port pin */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_TGL                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_TGL_VALUE                   0            /*  Toggle the output of the port pin */
#define BITM_GPIO_TGL_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Toggle the output of the port pin */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_POL                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_POL_VALUE                   0            /*  Interrupt polarity */
#define BITM_GPIO_POL_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Interrupt polarity */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_IENA                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_IENA_VALUE                  0            /*  Interrupt A enable */
#define BITM_GPIO_IENA_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Interrupt A enable */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_IENB                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_IENB_VALUE                  0            /*  Interrupt B enable */
#define BITM_GPIO_IENB_VALUE                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Interrupt B enable */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_INT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_INT_VALUE                   0            /*  Interrupt Status */
#define BITM_GPIO_INT_VALUE                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Interrupt Status */

/* -------------------------------------------------------------------------------------------------------------------------
          GPIO_DS                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_GPIO_DS_VALUE                    0            /*  Drive strength select */
#define BITM_GPIO_DS_VALUE                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Drive strength select */


/* ============================================================================================================================
        CRC Accelerator
   ============================================================================================================================ */

/* ============================================================================================================================
        CRC0
   ============================================================================================================================ */
#define REG_CRC0_CTL                         0x40040000            /*  CRC0 CRC Control Register */
#define REG_CRC0_IPDATA                      0x40040004            /*  CRC0 Input Data Word Register */
#define REG_CRC0_RESULT                      0x40040008            /*  CRC0 CRC Result Register */
#define REG_CRC0_POLY                        0x4004000C            /*  CRC0 Programmable CRC Polynomial */
#define REG_CRC0_IPBITS0                     0x40040010            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS1                     0x40040011            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS2                     0x40040012            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS3                     0x40040013            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS4                     0x40040014            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS5                     0x40040015            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS6                     0x40040016            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITS7                     0x40040017            /*  CRC0 Input Data Bits */
#define REG_CRC0_IPBITSn(i)                  (REG_CRC0_IPBITS0 + ((i) * 1))
#define REG_CRC0_IPBITSn_COUNT               8
#define REG_CRC0_IPBYTE                      0x40040010            /*  CRC0 Input Data Byte */

/* ============================================================================================================================
        CRC Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          CRC_CTL                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRC_CTL_REVID                   28            /*  Revision ID */
#define BITP_CRC_CTL_W16SWP                   4            /*  Word16 Swap */
#define BITP_CRC_CTL_BYTMIRR                  3            /*  Byte Mirroring */
#define BITP_CRC_CTL_BITMIRR                  2            /*  Bit Mirroring */
#define BITP_CRC_CTL_LSBFIRST                 1            /*  LSB First Calculation Order */
#define BITP_CRC_CTL_EN                       0            /*  CRC Peripheral Enable */
#define BITM_CRC_CTL_REVID                   (_ADI_MSK_3(0xF0000000,0xF0000000UL, uint32_t  ))    /*  Revision ID */
#define BITM_CRC_CTL_W16SWP                  (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Word16 Swap */
#define BITM_CRC_CTL_BYTMIRR                 (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Byte Mirroring */
#define BITM_CRC_CTL_BITMIRR                 (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Bit Mirroring */
#define BITM_CRC_CTL_LSBFIRST                (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  LSB First Calculation Order */
#define BITM_CRC_CTL_EN                      (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  CRC Peripheral Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          CRC_IPDATA                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRC_IPDATA_VALUE                 0            /*  Data Input. */
#define BITM_CRC_IPDATA_VALUE                (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Data Input. */

/* -------------------------------------------------------------------------------------------------------------------------
          CRC_RESULT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRC_RESULT_VALUE                 0            /*  CRC Residue */
#define BITM_CRC_RESULT_VALUE                (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  CRC Residue */

/* -------------------------------------------------------------------------------------------------------------------------
          CRC_POLY                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRC_POLY_VALUE                   0            /*  CRC Reduction Polynomial */
#define BITM_CRC_POLY_VALUE                  (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  CRC Reduction Polynomial */

/* -------------------------------------------------------------------------------------------------------------------------
          CRC_IPBITS[n]                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRC_IPBITS_DATA_BITS             0            /*  Input Data Bits. */
#define BITM_CRC_IPBITS_DATA_BITS            (_ADI_MSK_3(0x000000FF,0x000000FFU, uint8_t   ))    /*  Input Data Bits. */

/* -------------------------------------------------------------------------------------------------------------------------
          CRC_IPBYTE                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRC_IPBYTE_DATA_BYTE             0            /*  Input Data Byte. */
#define BITM_CRC_IPBYTE_DATA_BYTE            (_ADI_MSK_3(0x000000FF,0x000000FFU, uint8_t   ))    /*  Input Data Byte. */


/* ============================================================================================================================
        Random Number Generator
   ============================================================================================================================ */

/* ============================================================================================================================
        RNG0
   ============================================================================================================================ */
#define REG_RNG0_CTL                         0x40040400            /*  RNG0 RNG Control Register */
#define REG_RNG0_LEN                         0x40040404            /*  RNG0 RNG Sample Length Register */
#define REG_RNG0_STAT                        0x40040408            /*  RNG0 RNG Status Register */
#define REG_RNG0_DATA                        0x4004040C            /*  RNG0 RNG Data Register */
#define REG_RNG0_OSCCNT                      0x40040410            /*  RNG0 Oscillator Count */
#define REG_RNG0_OSCDIFF0                    0x40040414            /*  RNG0 Oscillator Difference */
#define REG_RNG0_OSCDIFF1                    0x40040415            /*  RNG0 Oscillator Difference */
#define REG_RNG0_OSCDIFF2                    0x40040416            /*  RNG0 Oscillator Difference */
#define REG_RNG0_OSCDIFF3                    0x40040417            /*  RNG0 Oscillator Difference */
#define REG_RNG0_OSCDIFFn(i)                 (REG_RNG0_OSCDIFF0 + ((i) * 1))
#define REG_RNG0_OSCDIFFn_COUNT              4

/* ============================================================================================================================
        RNG Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          RNG_CTL                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RNG_CTL_SINGLE                   3            /*  Generate a single number */
#define BITP_RNG_CTL_EN                       0            /*  RNG Enable */
#define BITM_RNG_CTL_SINGLE                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Generate a single number */
#define BITM_RNG_CTL_EN                      (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  RNG Enable */
#define ENUM_RNG_CTL_WORD                    (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  SINGLE: Buffer Word */
#define ENUM_RNG_CTL_SINGLE                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  SINGLE: Single Byte */
#define ENUM_RNG_CTL_DISABLE                 (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  EN: Disable the RNG */
#define ENUM_RNG_CTL_ENABLE                  (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  EN: Enable the RNG */

/* -------------------------------------------------------------------------------------------------------------------------
          RNG_LEN                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RNG_LEN_PRESCALE                12            /*  Prescaler for the sample counter */
#define BITP_RNG_LEN_RELOAD                   0            /*  Reload value for the sample counter */
#define BITM_RNG_LEN_PRESCALE                (_ADI_MSK_3(0x0000F000,0x0000F000U, uint16_t  ))    /*  Prescaler for the sample counter */
#define BITM_RNG_LEN_RELOAD                  (_ADI_MSK_3(0x00000FFF,0x00000FFFU, uint16_t  ))    /*  Reload value for the sample counter */

/* -------------------------------------------------------------------------------------------------------------------------
          RNG_STAT                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RNG_STAT_STUCK                   1            /*  Sampled data stuck high or low */
#define BITP_RNG_STAT_RNRDY                   0            /*  Random number ready */
#define BITM_RNG_STAT_STUCK                  (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Sampled data stuck high or low */
#define BITM_RNG_STAT_RNRDY                  (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Random number ready */

/* -------------------------------------------------------------------------------------------------------------------------
          RNG_DATA                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RNG_DATA_BUFF                    8            /*  Buffer for RNG data */
#define BITP_RNG_DATA_VALUE                   0            /*  Value of the CRC accumulator */
#define BITM_RNG_DATA_BUFF                   (_ADI_MSK_3(0xFFFFFF00,0xFFFFFF00UL, uint32_t  ))    /*  Buffer for RNG data */
#define BITM_RNG_DATA_VALUE                  (_ADI_MSK_3(0x000000FF,0x000000FFUL, uint32_t  ))    /*  Value of the CRC accumulator */

/* -------------------------------------------------------------------------------------------------------------------------
          RNG_OSCCNT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RNG_OSCCNT_VALUE                 0            /*  Oscillator count */
#define BITM_RNG_OSCCNT_VALUE                (_ADI_MSK_3(0x0FFFFFFF,0x0FFFFFFFUL, uint32_t  ))    /*  Oscillator count */

/* -------------------------------------------------------------------------------------------------------------------------
          RNG_OSCDIFF[n]                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RNG_OSCDIFF_DELTA                0            /*  Oscillator Count difference */
#define BITM_RNG_OSCDIFF_DELTA               (_ADI_MSK_3(0x000000FF,0x000000FF, int8_t    ))    /*  Oscillator Count difference */


/* ============================================================================================================================
        Cryptogaphic
   ============================================================================================================================ */

/* ============================================================================================================================
        CRYPT0
   ============================================================================================================================ */
#define REG_CRYPT0_CFG                       0x40044000            /*  CRYPT0 Configuration Register */
#define REG_CRYPT0_DATALEN                   0x40044004            /*  CRYPT0 Payload Data Length */
#define REG_CRYPT0_PREFIXLEN                 0x40044008            /*  CRYPT0 Authentication Data Length */
#define REG_CRYPT0_INTEN                     0x4004400C            /*  CRYPT0 Interrupt Enable Register */
#define REG_CRYPT0_STAT                      0x40044010            /*  CRYPT0 Status Register */
#define REG_CRYPT0_INBUF                     0x40044014            /*  CRYPT0 Input Buffer */
#define REG_CRYPT0_OUTBUF                    0x40044018            /*  CRYPT0 Output Buffer */
#define REG_CRYPT0_NONCE0                    0x4004401C            /*  CRYPT0 Nonce Bits [31:0] */
#define REG_CRYPT0_NONCE1                    0x40044020            /*  CRYPT0 Nonce Bits [63:32] */
#define REG_CRYPT0_NONCE2                    0x40044024            /*  CRYPT0 Nonce Bits [95:64] */
#define REG_CRYPT0_NONCE3                    0x40044028            /*  CRYPT0 Nonce Bits [127:96] */
#define REG_CRYPT0_AESKEY0                   0x4004402C            /*  CRYPT0 Key Bits[ 31:0 ] */
#define REG_CRYPT0_AESKEY1                   0x40044030            /*  CRYPT0 Key Bits [ 63:32 ] */
#define REG_CRYPT0_AESKEY2                   0x40044034            /*  CRYPT0 Key Bits [ 95:64 ] */
#define REG_CRYPT0_AESKEY3                   0x40044038            /*  CRYPT0 Key Bits [ 127:96 ] */
#define REG_CRYPT0_AESKEY4                   0x4004403C            /*  CRYPT0 Key Bits [ 159:128 ] */
#define REG_CRYPT0_AESKEY5                   0x40044040            /*  CRYPT0 Key Bits [ 191:160 ] */
#define REG_CRYPT0_AESKEY6                   0x40044044            /*  CRYPT0 Key Bits [ 223:192 ] */
#define REG_CRYPT0_AESKEY7                   0x40044048            /*  CRYPT0 Key Bits [ 255:224 ] */
#define REG_CRYPT0_CNTRINIT                  0x4004404C            /*  CRYPT0 Counter Initialization Vector */
#define REG_CRYPT0_SHAH0                     0x40044050            /*  CRYPT0 SHA Bits [ 31:0 ] */
#define REG_CRYPT0_SHAH1                     0x40044054            /*  CRYPT0 SHA Bits [ 63:32 ] */
#define REG_CRYPT0_SHAH2                     0x40044058            /*  CRYPT0 SHA Bits [ 95:64 ] */
#define REG_CRYPT0_SHAH3                     0x4004405C            /*  CRYPT0 SHA Bits [ 127:96 ] */
#define REG_CRYPT0_SHAH4                     0x40044060            /*  CRYPT0 SHA Bits [ 159:128 ] */
#define REG_CRYPT0_SHAH5                     0x40044064            /*  CRYPT0 SHA Bits [ 191:160 ] */
#define REG_CRYPT0_SHAH6                     0x40044068            /*  CRYPT0 SHA Bits [ 223:192] */
#define REG_CRYPT0_SHAH7                     0x4004406C            /*  CRYPT0 SHA Bits [ 255:224 ] */
#define REG_CRYPT0_SHA_LAST_WORD             0x40044070            /*  CRYPT0 SHA Last Word and Valid Bits Information */
#define REG_CRYPT0_CCM_NUM_VALID_BYTES       0x40044074            /*  CRYPT0 NUM_VALID_BYTES */

/* ============================================================================================================================
        CRYPT Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_CFG                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_CFG_REVID                 28            /*  Rev ID for Crypto on Glue Micro */
#define BITP_CRYPT_CFG_SHADATSRC             27            /*  Select Data Input Source to SHA Engine */
#define BITP_CRYPT_CFG_SHAINIT               26            /*  Restarts SHA Computation */
#define BITP_CRYPT_CFG_SHA256EN              25            /*  Enable SHA-256 Operation */
#define BITP_CRYPT_CFG_CMACEN                20            /*  Enable CMAC Mode Operation */
#define BITP_CRYPT_CFG_CCMEN                 19            /*  Enable CCM/CCM* Mode Operation */
#define BITP_CRYPT_CFG_CBCEN                 18            /*  Enable CBC Mode Operation */
#define BITP_CRYPT_CFG_CTREN                 17            /*  Enable CTR Mode Operation */
#define BITP_CRYPT_CFG_ECBEN                 16            /*  Enable ECB Mode Operation */
#define BITP_CRYPT_CFG_KEYLEN                 8            /*  Select Key Length for AES Cipher */
#define BITP_CRYPT_CFG_ENDIAN                 6            /*  Endianness */
#define BITP_CRYPT_CFG_OUTFLUSH               5            /*  Output Buffer Flush */
#define BITP_CRYPT_CFG_INFLUSH                4            /*  Input Buffer Flush */
#define BITP_CRYPT_CFG_OUTDMAEN               3            /*  Enable DMA for Output Buffer */
#define BITP_CRYPT_CFG_INDMAEN                2            /*  Enable DMA for Input Buffer */
#define BITP_CRYPT_CFG_ENCR                   1            /*  Encrypt or Decrypt */
#define BITP_CRYPT_CFG_BLKEN                  0            /*  Enable BIT for the Crypto Block */
#define BITM_CRYPT_CFG_REVID                 (_ADI_MSK_3(0xF0000000,0xF0000000UL, uint32_t  ))    /*  Rev ID for Crypto on Glue Micro */
#define BITM_CRYPT_CFG_SHADATSRC             (_ADI_MSK_3(0x08000000,0x08000000UL, uint32_t  ))    /*  Select Data Input Source to SHA Engine */
#define BITM_CRYPT_CFG_SHAINIT               (_ADI_MSK_3(0x04000000,0x04000000UL, uint32_t  ))    /*  Restarts SHA Computation */
#define BITM_CRYPT_CFG_SHA256EN              (_ADI_MSK_3(0x02000000,0x02000000UL, uint32_t  ))    /*  Enable SHA-256 Operation */
#define BITM_CRYPT_CFG_CMACEN                (_ADI_MSK_3(0x00100000,0x00100000UL, uint32_t  ))    /*  Enable CMAC Mode Operation */
#define BITM_CRYPT_CFG_CCMEN                 (_ADI_MSK_3(0x00080000,0x00080000UL, uint32_t  ))    /*  Enable CCM/CCM* Mode Operation */
#define BITM_CRYPT_CFG_CBCEN                 (_ADI_MSK_3(0x00040000,0x00040000UL, uint32_t  ))    /*  Enable CBC Mode Operation */
#define BITM_CRYPT_CFG_CTREN                 (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))    /*  Enable CTR Mode Operation */
#define BITM_CRYPT_CFG_ECBEN                 (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  Enable ECB Mode Operation */
#define BITM_CRYPT_CFG_KEYLEN                (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  Select Key Length for AES Cipher */
#define BITM_CRYPT_CFG_ENDIAN                (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Endianness */
#define BITM_CRYPT_CFG_OUTFLUSH              (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Output Buffer Flush */
#define BITM_CRYPT_CFG_INFLUSH               (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Input Buffer Flush */
#define BITM_CRYPT_CFG_OUTDMAEN              (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Enable DMA for Output Buffer */
#define BITM_CRYPT_CFG_INDMAEN               (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Enable DMA for Input Buffer */
#define BITM_CRYPT_CFG_ENCR                  (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Encrypt or Decrypt */
#define BITM_CRYPT_CFG_BLKEN                 (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable BIT for the Crypto Block */
#define ENUM_CRYPT_CFG_INBUF                 (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  SHADATSRC: SHA takes input from input buffer */
#define ENUM_CRYPT_CFG_OPBUF                 (_ADI_MSK_3(0x08000000,0x08000000UL, uint32_t  ))    /*  SHADATSRC: SHA takes input from output buffer */
#define ENUM_CRYPT_CFG_LITTLE_ENDIAN         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  ENDIAN: Little Endian Format */
#define ENUM_CRYPT_CFG_BIG_ENDIAN            (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  ENDIAN: Big Endian Format */
#define ENUM_CRYPT_CFG_DMA_DISABLE_OUTBUF    (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  OUTDMAEN: Disable DMA Requesting for Output Buffer */
#define ENUM_CRYPT_CFG_DMA_ENABLE_OUTBUF     (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  OUTDMAEN: Enable DMA Requesting for Output Buffer */
#define ENUM_CRYPT_CFG_DMA_DISABLE_INBUF     (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  INDMAEN: Disable DMA Requesting for Input Buffer */
#define ENUM_CRYPT_CFG_DMA_ENABLE_INBUF      (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  INDMAEN: Enable DMA Requesting for Input Buffer */
#define ENUM_CRYPT_CFG_ENABLE                (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  BLKEN: Enable Crypto Block */
#define ENUM_CRYPT_CFG_DISABLE               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  BLKEN: Disable Crypto Block */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_DATALEN                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_DATALEN_VALUE              0            /*  Length of Payload Data */
#define BITM_CRYPT_DATALEN_VALUE             (_ADI_MSK_3(0x000FFFFF,0x000FFFFFUL, uint32_t  ))    /*  Length of Payload Data */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_PREFIXLEN                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_PREFIXLEN_VALUE            0            /*  Length of Associated Data */
#define BITM_CRYPT_PREFIXLEN_VALUE           (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  Length of Associated Data */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_INTEN                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_INTEN_SHADONEN             5            /*  Enable SHA_Done Interrupt */
#define BITP_CRYPT_INTEN_OUTUNDREN            3            /*  Enable the Output Underflow Interrupt */
#define BITP_CRYPT_INTEN_INOVREN              2            /*  Enable Input Overflow Interrupt. */
#define BITP_CRYPT_INTEN_OUTRDYEN             1            /*  Enables the Output Ready Interrupt. */
#define BITP_CRYPT_INTEN_INRDYEN              0            /*  Enable Input Ready Interrupt */
#define BITM_CRYPT_INTEN_SHADONEN            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Enable SHA_Done Interrupt */
#define BITM_CRYPT_INTEN_OUTUNDREN           (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Enable the Output Underflow Interrupt */
#define BITM_CRYPT_INTEN_INOVREN             (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Enable Input Overflow Interrupt. */
#define BITM_CRYPT_INTEN_OUTRDYEN            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Enables the Output Ready Interrupt. */
#define BITM_CRYPT_INTEN_INRDYEN             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable Input Ready Interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_STAT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_STAT_OUTWORDS             10            /*  Number of Words in the Output Buffer */
#define BITP_CRYPT_STAT_INWORDS               7            /*  Number of Words in the Input Buffer */
#define BITP_CRYPT_STAT_SHABUSY               6            /*  SHA Busy. in Computation */
#define BITP_CRYPT_STAT_SHADONE               5            /*  SHA Computation Complete */
#define BITP_CRYPT_STAT_OUTUNDR               3            /*  Underflow Interrupt in the Output */
#define BITP_CRYPT_STAT_INOVR                 2            /*  Overflow in the INPUT Buffer. */
#define BITP_CRYPT_STAT_OUTRDY                1            /*  Output Data Ready */
#define BITP_CRYPT_STAT_INRDY                 0            /*  Input Buffer Status */
#define BITM_CRYPT_STAT_OUTWORDS             (_ADI_MSK_3(0x00001C00,0x00001C00UL, uint32_t  ))    /*  Number of Words in the Output Buffer */
#define BITM_CRYPT_STAT_INWORDS              (_ADI_MSK_3(0x00000380,0x00000380UL, uint32_t  ))    /*  Number of Words in the Input Buffer */
#define BITM_CRYPT_STAT_SHABUSY              (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  SHA Busy. in Computation */
#define BITM_CRYPT_STAT_SHADONE              (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  SHA Computation Complete */
#define BITM_CRYPT_STAT_OUTUNDR              (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Underflow Interrupt in the Output */
#define BITM_CRYPT_STAT_INOVR                (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Overflow in the INPUT Buffer. */
#define BITM_CRYPT_STAT_OUTRDY               (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Output Data Ready */
#define BITM_CRYPT_STAT_INRDY                (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Input Buffer Status */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_INBUF                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_INBUF_VALUE                0            /*  Input Buffer */
#define BITM_CRYPT_INBUF_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Input Buffer */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_OUTBUF                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_OUTBUF_VALUE               0            /*  Output Buffer */
#define BITM_CRYPT_OUTBUF_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Output Buffer */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_NONCE0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_NONCE0_VALUE               0            /*  Word 0: Nonce : Bits [31:0] */
#define BITM_CRYPT_NONCE0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 0: Nonce : Bits [31:0] */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_NONCE1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_NONCE1_VALUE               0            /*  Word 1: Nonce : Bits [63:32] */
#define BITM_CRYPT_NONCE1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 1: Nonce : Bits [63:32] */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_NONCE2                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_NONCE2_VALUE               0            /*  Word 2: Nonce : Bits [95:64] */
#define BITM_CRYPT_NONCE2_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 2: Nonce : Bits [95:64] */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_NONCE3                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_NONCE3_VALUE               0            /*  Word 3: Nonce : Bits [127:96] */
#define BITM_CRYPT_NONCE3_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 3: Nonce : Bits [127:96] */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY0_VALUE              0            /*  Key: Bytes [3:0]; */
#define BITM_CRYPT_AESKEY0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [3:0]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY1_VALUE              0            /*  Key: Bytes [7:4]; */
#define BITM_CRYPT_AESKEY1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [7:4]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY2                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY2_VALUE              0            /*  Key: Bytes [11:8]; */
#define BITM_CRYPT_AESKEY2_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [11:8]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY3                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY3_VALUE              0            /*  Key: Bytes [15:12]; */
#define BITM_CRYPT_AESKEY3_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [15:12]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY4                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY4_VALUE              0            /*  Key: Bytes [3:0]; */
#define BITM_CRYPT_AESKEY4_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [3:0]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY5                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY5_VALUE              0            /*  Key: Bytes [7:4]; */
#define BITM_CRYPT_AESKEY5_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [7:4]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY6                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY6_VALUE              0            /*  Key: Bytes [11:8]; */
#define BITM_CRYPT_AESKEY6_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [11:8]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_AESKEY7                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_AESKEY7_VALUE              0            /*  Key: Bytes [15:12]; */
#define BITM_CRYPT_AESKEY7_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Key: Bytes [15:12]; */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_CNTRINIT                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_CNTRINIT_VALUE             0            /*  Counter Initialization Value */
#define BITM_CRYPT_CNTRINIT_VALUE            (_ADI_MSK_3(0x000FFFFF,0x000FFFFFUL, uint32_t  ))    /*  Counter Initialization Value */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH0                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH0_SHAHASH0             0            /*  Word 0: SHA Hash */
#define BITM_CRYPT_SHAH0_SHAHASH0            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 0: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH1                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH1_SHAHASH1             0            /*  Word 1: SHA Hash */
#define BITM_CRYPT_SHAH1_SHAHASH1            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 1: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH2                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH2_SHAHASH2             0            /*  Word 2: SHA Hash */
#define BITM_CRYPT_SHAH2_SHAHASH2            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 2: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH3                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH3_SHAHASH3             0            /*  Word 3: SHA Hash */
#define BITM_CRYPT_SHAH3_SHAHASH3            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 3: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH4                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH4_SHAHASH4             0            /*  Word 4: SHA Hash */
#define BITM_CRYPT_SHAH4_SHAHASH4            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 4: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH5                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH5_SHAHASH5             0            /*  Word 5: SHA Hash */
#define BITM_CRYPT_SHAH5_SHAHASH5            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 5: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH6                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH6_SHAHASH6             0            /*  Word 6: SHA Hash */
#define BITM_CRYPT_SHAH6_SHAHASH6            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 6: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHAH7                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHAH7_SHAHASH7             0            /*  Word 7: SHA Hash */
#define BITM_CRYPT_SHAH7_SHAHASH7            (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Word 7: SHA Hash */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_SHA_LAST_WORD                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_SHA_LAST_WORD_O_BITS_VALID  1            /*  Bits Valid in SHA Last Word Input */
#define BITP_CRYPT_SHA_LAST_WORD_O_LAST_WORD  0            /*  Last SHA Input Word */
#define BITM_CRYPT_SHA_LAST_WORD_O_BITS_VALID (_ADI_MSK_3(0x0000003E,0x0000003EUL, uint32_t  ))    /*  Bits Valid in SHA Last Word Input */
#define BITM_CRYPT_SHA_LAST_WORD_O_LAST_WORD (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Last SHA Input Word */

/* -------------------------------------------------------------------------------------------------------------------------
          CRYPT_CCM_NUM_VALID_BYTES            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CRYPT_CCM_NUM_VALID_BYTES_RESERVED_31_4  4            /*  Reserved */
#define BITP_CRYPT_CCM_NUM_VALID_BYTES_NUM_VALID_BYTES  0            /*  Number of Valid Bytes in CCM Last Data */
#define BITM_CRYPT_CCM_NUM_VALID_BYTES_RESERVED_31_4 (_ADI_MSK_3(0xFFFFFFF0,0xFFFFFFF0UL, uint32_t  ))    /*  Reserved */
#define BITM_CRYPT_CCM_NUM_VALID_BYTES_NUM_VALID_BYTES (_ADI_MSK_3(0x0000000F,0x0000000FUL, uint32_t  ))    /*  Number of Valid Bytes in CCM Last Data */


/* ============================================================================================================================
        Power Management Registers
   ============================================================================================================================ */

/* ============================================================================================================================
        PMG0
   ============================================================================================================================ */
#define REG_PMG0_IEN                         0x4004C000            /*  PMG0 Power Supply Monitor Interrupt Enable */
#define REG_PMG0_PSM_STAT                    0x4004C004            /*  PMG0 Power supply monitor status */
#define REG_PMG0_PWRMOD                      0x4004C008            /*  PMG0 Power Mode Register */
#define REG_PMG0_PWRKEY                      0x4004C00C            /*  PMG0 Key protection for PWRMOD and  SRAMRET */
#define REG_PMG0_SHDN_STAT                   0x4004C010            /*  PMG0 SHUTDOWN Status Register */
#define REG_PMG0_SRAMRET                     0x4004C014            /*  PMG0 Control for Retention SRAM during HIBERNATE Mode */
#define REG_PMG0_RST_STAT                    0x4004C040            /*  PMG0 Reset status */
#define REG_PMG0_CTL1                        0x4004C044            /*  PMG0 HPBUCK control */

/* ============================================================================================================================
        PMG Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          PMG_IEN                              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_IEN_IENBAT                  10            /*  Interrupt enable for VBAT range */
#define BITP_PMG_IEN_RANGEBAT                 8            /*  Battery Monitor Range */
#define BITP_PMG_IEN_VREGOVR                  2            /*  Enable Interrupt when VREG over-voltage: over- 1.32V */
#define BITP_PMG_IEN_VREGUNDR                 1            /*  Enable Interrupt when VREG under-voltage: below 1V */
#define BITP_PMG_IEN_VBAT                     0            /*  Enable Interrupt for VBAT */
#define BITM_PMG_IEN_IENBAT                  (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Interrupt enable for VBAT range */
#define BITM_PMG_IEN_RANGEBAT                (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  Battery Monitor Range */
#define BITM_PMG_IEN_VREGOVR                 (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Enable Interrupt when VREG over-voltage: over- 1.32V */
#define BITM_PMG_IEN_VREGUNDR                (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Enable Interrupt when VREG under-voltage: below 1V */
#define BITM_PMG_IEN_VBAT                    (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable Interrupt for VBAT */
#define ENUM_PMG_IEN_REGION1                 (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  RANGEBAT: Configure to generate interrupt if VBAT > 2.75V */
#define ENUM_PMG_IEN_REGION2                 (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  RANGEBAT: Configure to generate interrupt if VBAT between 2.75V - 1.6V */
#define ENUM_PMG_IEN_REGION3                 (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  RANGEBAT: Configure to generate interrupt if VBAT between 2.3V - 1.6V */
#define ENUM_PMG_IEN_NA                      (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  RANGEBAT: N/A */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_PSM_STAT                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_PSM_STAT_RORANGE3           15            /*  VBAT range3 (2.3v - 1.6v) */
#define BITP_PMG_PSM_STAT_RORANGE2           14            /*  VBAT range2 (2.75v - 2.3v) */
#define BITP_PMG_PSM_STAT_RORANGE1           13            /*  VBAT range1 (> 2.75v) */
#define BITP_PMG_PSM_STAT_RANGE3             10            /*  VBAT range3 (2.3v - 1.6v) */
#define BITP_PMG_PSM_STAT_RANGE2              9            /*  VBAT range2 (2.75v - 2.3v) */
#define BITP_PMG_PSM_STAT_RANGE1              8            /*  VBAT range1 (> 2.75v) */
#define BITP_PMG_PSM_STAT_WICENACK            7            /*  WIC Enable Acknowledge from Cortex */
#define BITP_PMG_PSM_STAT_VREGOVR             2            /*  Status bit for alarm indicating Overvoltage for VREG */
#define BITP_PMG_PSM_STAT_VREGUNDR            1            /*  Status bit for Alarm indicating VREG is below 1V. */
#define BITP_PMG_PSM_STAT_VBATUNDR            0            /*  Status bit indicating an Alarm that battery is below 1.8V. */
#define BITM_PMG_PSM_STAT_RORANGE3           (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  VBAT range3 (2.3v - 1.6v) */
#define BITM_PMG_PSM_STAT_RORANGE2           (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  VBAT range2 (2.75v - 2.3v) */
#define BITM_PMG_PSM_STAT_RORANGE1           (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  VBAT range1 (> 2.75v) */
#define BITM_PMG_PSM_STAT_RANGE3             (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  VBAT range3 (2.3v - 1.6v) */
#define BITM_PMG_PSM_STAT_RANGE2             (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  VBAT range2 (2.75v - 2.3v) */
#define BITM_PMG_PSM_STAT_RANGE1             (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  VBAT range1 (> 2.75v) */
#define BITM_PMG_PSM_STAT_WICENACK           (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  WIC Enable Acknowledge from Cortex */
#define BITM_PMG_PSM_STAT_VREGOVR            (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Status bit for alarm indicating Overvoltage for VREG */
#define BITM_PMG_PSM_STAT_VREGUNDR           (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Status bit for Alarm indicating VREG is below 1V. */
#define BITM_PMG_PSM_STAT_VBATUNDR           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Status bit indicating an Alarm that battery is below 1.8V. */
#define ENUM_PMG_PSM_STAT_BATSTAT1           (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  RORANGE1: VBAT NOT in the range specified */
#define ENUM_PMG_PSM_STAT_BATSTAT0           (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  RORANGE1: VBAT in the range specified */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_PWRMOD                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_PWRMOD_MONVBATN              3            /*  Monitor VBAT during HIBERNATE Mode. Monitors VBAT by default */
#define BITP_PMG_PWRMOD_MODE                  0            /*  Power Mode Bits */
#define BITM_PMG_PWRMOD_MONVBATN             (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Monitor VBAT during HIBERNATE Mode. Monitors VBAT by default */
#define BITM_PMG_PWRMOD_MODE                 (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  Power Mode Bits */
#define ENUM_PMG_PWRMOD_FLEXI                (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  MODE: FLEXI Mode */
#define ENUM_PMG_PWRMOD_HIBERNATE            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  MODE: HIBERNATE Mode */
#define ENUM_PMG_PWRMOD_SHUTDOWN             (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  MODE: SHUTDOWN Mode */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_PWRKEY                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_PWRKEY_VALUE                 0            /*  Power control key register */
#define BITM_PMG_PWRKEY_VALUE                (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  Power control key register */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_SHDN_STAT                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_SHDN_STAT_RTC                3            /*  Interrupt from RTC */
#define BITP_PMG_SHDN_STAT_EXTINT2            2            /*  Interrupt from External Interrupt 2 */
#define BITP_PMG_SHDN_STAT_EXTINT1            1            /*  Interrupt from External Interrupt 1 */
#define BITP_PMG_SHDN_STAT_EXTINT0            0            /*  Interrupt from External Interrupt 0 */
#define BITM_PMG_SHDN_STAT_RTC               (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Interrupt from RTC */
#define BITM_PMG_SHDN_STAT_EXTINT2           (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Interrupt from External Interrupt 2 */
#define BITM_PMG_SHDN_STAT_EXTINT1           (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Interrupt from External Interrupt 1 */
#define BITM_PMG_SHDN_STAT_EXTINT0           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Interrupt from External Interrupt 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_SRAMRET                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_SRAMRET_BNK2EN               1            /*  Enable retention bank 2 (16kB) */
#define BITP_PMG_SRAMRET_BNK1EN               0            /*  Enable retention bank 1 (8kB) */
#define BITM_PMG_SRAMRET_BNK2EN              (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Enable retention bank 2 (16kB) */
#define BITM_PMG_SRAMRET_BNK1EN              (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable retention bank 1 (8kB) */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_RST_STAT                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_RST_STAT_PORSRC              4            /*  Power on reset Source (pmg_rst_src) */
#define BITP_PMG_RST_STAT_SWRST               3            /*  Software reset */
#define BITP_PMG_RST_STAT_WDRST               2            /*  Watchdog timeout */
#define BITP_PMG_RST_STAT_EXTRST              1            /*  External reset */
#define BITP_PMG_RST_STAT_POR                 0            /*  Power-on reset */
#define BITM_PMG_RST_STAT_PORSRC             (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  Power on reset Source (pmg_rst_src) */
#define BITM_PMG_RST_STAT_SWRST              (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Software reset */
#define BITM_PMG_RST_STAT_WDRST              (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Watchdog timeout */
#define BITM_PMG_RST_STAT_EXTRST             (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  External reset */
#define BITM_PMG_RST_STAT_POR                (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Power-on reset */
#define ENUM_PMG_RST_STAT_FAILSAFE_HV        (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  PORSRC: POR triggered because VBAT drops below Fail Safe */
#define ENUM_PMG_RST_STAT_RST_VBAT           (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  PORSRC: POR trigger because VBAT supply (VBAT<1.7v) */
#define ENUM_PMG_RST_STAT_RST_VREG           (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  PORSRC: POR triggered because VDD supply (VDD < 1.08v) */
#define ENUM_PMG_RST_STAT_FAILSAFE_LV        (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  PORSRC: POR triggered because VREG drops below Fail Safe */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_CTL1                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_CTL1_HPBUCKEN                0            /*  Enable HP Buck */
#define BITM_PMG_CTL1_HPBUCKEN               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable HP Buck */


/* ============================================================================================================================
        External interrupt configuration
   ============================================================================================================================ */

/* ============================================================================================================================
        XINT0
   ============================================================================================================================ */
#define REG_XINT0_CFG0                       0x4004C080            /*  XINT0 External Interrupt Configuration */
#define REG_XINT0_EXT_STAT                   0x4004C084            /*  XINT0 External Wakeup Interrupt Status */
#define REG_XINT0_CLR                        0x4004C090            /*  XINT0 External Interrupt Clear */
#define REG_XINT0_NMICLR                     0x4004C094            /*  XINT0 Non-Maskable Interrupt Clear */

/* ============================================================================================================================
        XINT Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          XINT_CFG0                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_XINT_CFG0_UART_RX_MDE           21            /*  External Interrupt using UART_RX wakeup Mode registers */
#define BITP_XINT_CFG0_UART_RX_EN            20            /*  External Interrupt enable bit */
#define BITP_XINT_CFG0_IRQ3EN                15            /*  External Interrupt 3 enable bit */
#define BITP_XINT_CFG0_IRQ3MDE               12            /*  External Interrupt 3 Mode registers */
#define BITP_XINT_CFG0_IRQ2EN                11            /*  External Interrupt 2 Enable bit */
#define BITP_XINT_CFG0_IRQ2MDE                8            /*  External Interrupt 2 Mode registers */
#define BITP_XINT_CFG0_IRQ1EN                 7            /*  External Interrupt 1 Enable bit */
#define BITP_XINT_CFG0_IRQ1MDE                4            /*  External Interrupt 1 Mode registers */
#define BITP_XINT_CFG0_IRQ0EN                 3            /*  External Interrupt 0 Enable bit */
#define BITP_XINT_CFG0_IRQ0MDE                0            /*  External Interrupt 0 Mode registers */
#define BITM_XINT_CFG0_UART_RX_MDE           (_ADI_MSK_3(0x00E00000,0x00E00000UL, uint32_t  ))    /*  External Interrupt using UART_RX wakeup Mode registers */
#define BITM_XINT_CFG0_UART_RX_EN            (_ADI_MSK_3(0x00100000,0x00100000UL, uint32_t  ))    /*  External Interrupt enable bit */
#define BITM_XINT_CFG0_IRQ3EN                (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  External Interrupt 3 enable bit */
#define BITM_XINT_CFG0_IRQ3MDE               (_ADI_MSK_3(0x00007000,0x00007000UL, uint32_t  ))    /*  External Interrupt 3 Mode registers */
#define BITM_XINT_CFG0_IRQ2EN                (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  External Interrupt 2 Enable bit */
#define BITM_XINT_CFG0_IRQ2MDE               (_ADI_MSK_3(0x00000700,0x00000700UL, uint32_t  ))    /*  External Interrupt 2 Mode registers */
#define BITM_XINT_CFG0_IRQ1EN                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  External Interrupt 1 Enable bit */
#define BITM_XINT_CFG0_IRQ1MDE               (_ADI_MSK_3(0x00000070,0x00000070UL, uint32_t  ))    /*  External Interrupt 1 Mode registers */
#define BITM_XINT_CFG0_IRQ0EN                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  External Interrupt 0 Enable bit */
#define BITM_XINT_CFG0_IRQ0MDE               (_ADI_MSK_3(0x00000007,0x00000007UL, uint32_t  ))    /*  External Interrupt 0 Mode registers */

/* -------------------------------------------------------------------------------------------------------------------------
          XINT_EXT_STAT                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_XINT_EXT_STAT_STAT_UART_RXWKUP   5            /*  Interrupt status bit for UART RX wakeup interrupt */
#define BITP_XINT_EXT_STAT_STAT_EXTINT3       3            /*  Interrupt status bit for External Interrupt 3 */
#define BITP_XINT_EXT_STAT_STAT_EXTINT2       2            /*  Interrupt status bit for External Interrupt 2 */
#define BITP_XINT_EXT_STAT_STAT_EXTINT1       1            /*  Interrupt status bit for External Interrupt 1 */
#define BITP_XINT_EXT_STAT_STAT_EXTINT0       0            /*  Interrupt status bit for External Interrupt 0 */
#define BITM_XINT_EXT_STAT_STAT_UART_RXWKUP  (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Interrupt status bit for UART RX wakeup interrupt */
#define BITM_XINT_EXT_STAT_STAT_EXTINT3      (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Interrupt status bit for External Interrupt 3 */
#define BITM_XINT_EXT_STAT_STAT_EXTINT2      (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Interrupt status bit for External Interrupt 2 */
#define BITM_XINT_EXT_STAT_STAT_EXTINT1      (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Interrupt status bit for External Interrupt 1 */
#define BITM_XINT_EXT_STAT_STAT_EXTINT0      (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Interrupt status bit for External Interrupt 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          XINT_CLR                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_XINT_CLR_UART_RX_CLR             5            /*  External interrupt Clear for UART_RX WAKEUP interrupt */
#define BITP_XINT_CLR_IRQ3                    3            /*  External interrupt 3 */
#define BITP_XINT_CLR_IRQ2                    2            /*  External interrupt 2 */
#define BITP_XINT_CLR_IRQ1                    1            /*  External interrupt 1 */
#define BITP_XINT_CLR_IRQ0                    0            /*  External interrupt 0 */
#define BITM_XINT_CLR_UART_RX_CLR            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  External interrupt Clear for UART_RX WAKEUP interrupt */
#define BITM_XINT_CLR_IRQ3                   (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  External interrupt 3 */
#define BITM_XINT_CLR_IRQ2                   (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  External interrupt 2 */
#define BITM_XINT_CLR_IRQ1                   (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  External interrupt 1 */
#define BITM_XINT_CLR_IRQ0                   (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  External interrupt 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          XINT_NMICLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_XINT_NMICLR_CLR                  0            /*  NMI clear */
#define BITM_XINT_NMICLR_CLR                 (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  NMI clear */


/* ============================================================================================================================
        Clocking registers
   ============================================================================================================================ */

/* ============================================================================================================================
        CLKG0_OSC
   ============================================================================================================================ */
#define REG_CLKG0_OSC_KEY                    0x4004C10C            /*  CLKG0_OSC Key Protection for OSCCTRL */
#define REG_CLKG0_OSC_CTL                    0x4004C110            /*  CLKG0_OSC Oscillator Control */

/* ============================================================================================================================
        CLKG_OSC Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_OSC_KEY                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_OSC_KEY_VALUE               0            /*  Oscillator key */
#define BITM_CLKG_OSC_KEY_VALUE              (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  Oscillator key */

/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_OSC_CTL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_OSC_CTL_LFXTAL_MON_FAIL_STAT 31            /*  LF XTAL (crystal clock) Not Stable */
#define BITP_CLKG_OSC_CTL_HFXTALOK           11            /*  Status of HFXTAL oscillator */
#define BITP_CLKG_OSC_CTL_LFXTALOK           10            /*  Status of LFXTAL oscillator */
#define BITP_CLKG_OSC_CTL_HFOSCOK             9            /*  Status of HFOSC oscillator */
#define BITP_CLKG_OSC_CTL_LFOSCOK             8            /*  Status of LFOSC oscillator */
#define BITP_CLKG_OSC_CTL_LFXTAL_MON_EN       5            /*  LFXTAL clock monitor and Clock FAIL interrupt enable */
#define BITP_CLKG_OSC_CTL_LFXTAL_BYPASS       4            /*  Low frequency crystal oscillator Bypass */
#define BITP_CLKG_OSC_CTL_HFXTALEN            3            /*  High frequency crystal oscillator enable */
#define BITP_CLKG_OSC_CTL_LFXTALEN            2            /*  Low frequency crystal oscillator enable */
#define BITP_CLKG_OSC_CTL_HFOSCEN             1            /*  High frequency internal oscillator enable */
#define BITP_CLKG_OSC_CTL_LFCLKMUX            0            /*  32 KHz clock select mux */
#define BITM_CLKG_OSC_CTL_LFXTAL_MON_FAIL_STAT (_ADI_MSK_3(0x80000000,0x80000000UL, uint32_t  ))    /*  LF XTAL (crystal clock) Not Stable */
#define BITM_CLKG_OSC_CTL_HFXTALOK           (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Status of HFXTAL oscillator */
#define BITM_CLKG_OSC_CTL_LFXTALOK           (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Status of LFXTAL oscillator */
#define BITM_CLKG_OSC_CTL_HFOSCOK            (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Status of HFOSC oscillator */
#define BITM_CLKG_OSC_CTL_LFOSCOK            (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Status of LFOSC oscillator */
#define BITM_CLKG_OSC_CTL_LFXTAL_MON_EN      (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  LFXTAL clock monitor and Clock FAIL interrupt enable */
#define BITM_CLKG_OSC_CTL_LFXTAL_BYPASS      (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Low frequency crystal oscillator Bypass */
#define BITM_CLKG_OSC_CTL_HFXTALEN           (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  High frequency crystal oscillator enable */
#define BITM_CLKG_OSC_CTL_LFXTALEN           (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Low frequency crystal oscillator enable */
#define BITM_CLKG_OSC_CTL_HFOSCEN            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  High frequency internal oscillator enable */
#define BITM_CLKG_OSC_CTL_LFCLKMUX           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  32 KHz clock select mux */


/* ============================================================================================================================
        Power Management Registers
   ============================================================================================================================ */

/* ============================================================================================================================
        PMG0_TST
   ============================================================================================================================ */
#define REG_PMG0_TST_SRAM_CTL                0x4004C260            /*  PMG0_TST Control for SRAM parity and instruction SRAM */
#define REG_PMG0_TST_SRAM_INITSTAT           0x4004C264            /*  PMG0_TST Initialization Status Register */
#define REG_PMG0_TST_CLR_LATCH_GPIOS         0x4004C268            /*  PMG0_TST CLEAR GPIO AFTER SHUTDOWN MODE */
#define REG_PMG0_TST_SCRPAD_IMG              0x4004C26C            /*  PMG0_TST SCRATCH PAD IMAGE */
#define REG_PMG0_TST_SCRPAD_3V_RD            0x4004C270            /*  PMG0_TST SCRATCH PAD SAVED IN BATTERY DOMAIN */

/* ============================================================================================================================
        PMG_TST Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          PMG_TST_SRAM_CTL                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_TST_SRAM_CTL_INSTREN        31            /*  Enables instruction SRAM */
#define BITP_PMG_TST_SRAM_CTL_PENBNK5        21            /*  Enable parity check */
#define BITP_PMG_TST_SRAM_CTL_PENBNK4        20            /*  Enable parity check */
#define BITP_PMG_TST_SRAM_CTL_PENBNK3        19            /*  Enable parity check */
#define BITP_PMG_TST_SRAM_CTL_PENBNK2        18            /*  Enable parity check */
#define BITP_PMG_TST_SRAM_CTL_PENBNK1        17            /*  Enable parity check */
#define BITP_PMG_TST_SRAM_CTL_PENBNK0        16            /*  Enable parity check */
#define BITP_PMG_TST_SRAM_CTL_ABTINIT        15            /*  Abort current initialization. Self-cleared */
#define BITP_PMG_TST_SRAM_CTL_AUTOINIT       14            /*  Automatic initialization on wake up from Hibernate mode */
#define BITP_PMG_TST_SRAM_CTL_STARTINIT      13            /*  Write one to trigger initialization. Self-cleared */
#define BITP_PMG_TST_SRAM_CTL_BNK5EN          5            /*  Enable initialization */
#define BITP_PMG_TST_SRAM_CTL_BNK4EN          4            /*  Enable initialization */
#define BITP_PMG_TST_SRAM_CTL_BNK3EN          3            /*  Enable initialization */
#define BITP_PMG_TST_SRAM_CTL_BNK2EN          2            /*  Enable initialization */
#define BITP_PMG_TST_SRAM_CTL_BNK1EN          1            /*  Enable initialization */
#define BITP_PMG_TST_SRAM_CTL_BNK0EN          0            /*  Enable initialization */
#define BITM_PMG_TST_SRAM_CTL_INSTREN        (_ADI_MSK_3(0x80000000,0x80000000UL, uint32_t  ))    /*  Enables instruction SRAM */
#define BITM_PMG_TST_SRAM_CTL_PENBNK5        (_ADI_MSK_3(0x00200000,0x00200000UL, uint32_t  ))    /*  Enable parity check */
#define BITM_PMG_TST_SRAM_CTL_PENBNK4        (_ADI_MSK_3(0x00100000,0x00100000UL, uint32_t  ))    /*  Enable parity check */
#define BITM_PMG_TST_SRAM_CTL_PENBNK3        (_ADI_MSK_3(0x00080000,0x00080000UL, uint32_t  ))    /*  Enable parity check */
#define BITM_PMG_TST_SRAM_CTL_PENBNK2        (_ADI_MSK_3(0x00040000,0x00040000UL, uint32_t  ))    /*  Enable parity check */
#define BITM_PMG_TST_SRAM_CTL_PENBNK1        (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))    /*  Enable parity check */
#define BITM_PMG_TST_SRAM_CTL_PENBNK0        (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  Enable parity check */
#define BITM_PMG_TST_SRAM_CTL_ABTINIT        (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  Abort current initialization. Self-cleared */
#define BITM_PMG_TST_SRAM_CTL_AUTOINIT       (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  Automatic initialization on wake up from Hibernate mode */
#define BITM_PMG_TST_SRAM_CTL_STARTINIT      (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  Write one to trigger initialization. Self-cleared */
#define BITM_PMG_TST_SRAM_CTL_BNK5EN         (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Enable initialization */
#define BITM_PMG_TST_SRAM_CTL_BNK4EN         (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Enable initialization */
#define BITM_PMG_TST_SRAM_CTL_BNK3EN         (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Enable initialization */
#define BITM_PMG_TST_SRAM_CTL_BNK2EN         (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Enable initialization */
#define BITM_PMG_TST_SRAM_CTL_BNK1EN         (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Enable initialization */
#define BITM_PMG_TST_SRAM_CTL_BNK0EN         (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable initialization */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_TST_SRAM_INITSTAT                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_TST_SRAM_INITSTAT_BNK5       5            /*  0:Not initialized; 1:Initialization completed */
#define BITP_PMG_TST_SRAM_INITSTAT_BNK4       4            /*  0:Not initialized; 1:Initialization completed */
#define BITP_PMG_TST_SRAM_INITSTAT_BNK3       3            /*  0:Not initialized; 1:Initialization completed */
#define BITP_PMG_TST_SRAM_INITSTAT_BNK2       2            /*  0:Not initialized; 1:Initialization completed */
#define BITP_PMG_TST_SRAM_INITSTAT_BNK1       1            /*  0:Not initialized; 1:Initialization completed */
#define BITP_PMG_TST_SRAM_INITSTAT_BNK0       0            /*  0:Not initialized; 1:Initialization completed */
#define BITM_PMG_TST_SRAM_INITSTAT_BNK5      (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  0:Not initialized; 1:Initialization completed */
#define BITM_PMG_TST_SRAM_INITSTAT_BNK4      (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  0:Not initialized; 1:Initialization completed */
#define BITM_PMG_TST_SRAM_INITSTAT_BNK3      (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  0:Not initialized; 1:Initialization completed */
#define BITM_PMG_TST_SRAM_INITSTAT_BNK2      (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  0:Not initialized; 1:Initialization completed */
#define BITM_PMG_TST_SRAM_INITSTAT_BNK1      (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  0:Not initialized; 1:Initialization completed */
#define BITM_PMG_TST_SRAM_INITSTAT_BNK0      (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  0:Not initialized; 1:Initialization completed */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_TST_CLR_LATCH_GPIOS              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_TST_CLR_LATCH_GPIOS_VALUE    0            /*  Writing 0x58FA creates a pulse to clear the latches for the GPIOs */
#define BITM_PMG_TST_CLR_LATCH_GPIOS_VALUE   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Writing 0x58FA creates a pulse to clear the latches for the GPIOs */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_TST_SCRPAD_IMG                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_TST_SCRPAD_IMG_DATA          0            /*  Anything written to this register will be saved in 3V when going to shutdown mode */
#define BITM_PMG_TST_SCRPAD_IMG_DATA         (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Anything written to this register will be saved in 3V when going to shutdown mode */

/* -------------------------------------------------------------------------------------------------------------------------
          PMG_TST_SCRPAD_3V_RD                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PMG_TST_SCRPAD_3V_RD_DATA        0            /*  Read Only register. Reading the scratch pad stored in shutdown mode */
#define BITM_PMG_TST_SCRPAD_3V_RD_DATA       (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Read Only register. Reading the scratch pad stored in shutdown mode */


/* ============================================================================================================================
        Clocking registers
   ============================================================================================================================ */

/* ============================================================================================================================
        CLKG0_CLK
   ============================================================================================================================ */
#define REG_CLKG0_CLK_CTL0                   0x4004C300            /*  CLKG0_CLK Misc clock settings */
#define REG_CLKG0_CLK_CTL1                   0x4004C304            /*  CLKG0_CLK Clock dividers */
#define REG_CLKG0_CLK_CTL3                   0x4004C30C            /*  CLKG0_CLK System PLL */
#define REG_CLKG0_CLK_CTL5                   0x4004C314            /*  CLKG0_CLK User clock gating control */
#define REG_CLKG0_CLK_STAT0                  0x4004C318            /*  CLKG0_CLK Clocking status */

/* ============================================================================================================================
        CLKG_CLK Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_CLK_CTL0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_CLK_CTL0_HFXTALIE          15            /*  High frequency crystal interrupt enable */
#define BITP_CLKG_CLK_CTL0_LFXTALIE          14            /*  Low frequency crystal interrupt enable */
#define BITP_CLKG_CLK_CTL0_SPLLIPSEL         11            /*  SPLL source select mux */
#define BITP_CLKG_CLK_CTL0_RCLKMUX            8            /*  Flash reference clock and HPBUCK clock source mux */
#define BITP_CLKG_CLK_CTL0_CLKMUX             0            /*  Clock mux select */
#define BITM_CLKG_CLK_CTL0_HFXTALIE          (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  High frequency crystal interrupt enable */
#define BITM_CLKG_CLK_CTL0_LFXTALIE          (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  Low frequency crystal interrupt enable */
#define BITM_CLKG_CLK_CTL0_SPLLIPSEL         (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  SPLL source select mux */
#define BITM_CLKG_CLK_CTL0_RCLKMUX           (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  Flash reference clock and HPBUCK clock source mux */
#define BITM_CLKG_CLK_CTL0_CLKMUX            (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  Clock mux select */

/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_CLK_CTL1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_CLK_CTL1_ACLKDIVCNT        16            /*  ACLK Divide Count. */
#define BITP_CLKG_CLK_CTL1_PCLKDIVCNT         8            /*  PCLK divide count */
#define BITP_CLKG_CLK_CTL1_HCLKDIVCNT         0            /*  HCLK divide count */
#define BITM_CLKG_CLK_CTL1_ACLKDIVCNT        (_ADI_MSK_3(0x00FF0000,0x00FF0000UL, uint32_t  ))    /*  ACLK Divide Count. */
#define BITM_CLKG_CLK_CTL1_PCLKDIVCNT        (_ADI_MSK_3(0x00003F00,0x00003F00UL, uint32_t  ))    /*  PCLK divide count */
#define BITM_CLKG_CLK_CTL1_HCLKDIVCNT        (_ADI_MSK_3(0x0000003F,0x0000003FUL, uint32_t  ))    /*  HCLK divide count */

/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_CLK_CTL3                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_CLK_CTL3_SPLLMUL2          16            /*  system PLL multiply by 2 */
#define BITP_CLKG_CLK_CTL3_SPLLMSEL          11            /*  System PLL M Divider */
#define BITP_CLKG_CLK_CTL3_SPLLIE            10            /*  System PLL interrupt enable */
#define BITP_CLKG_CLK_CTL3_SPLLEN             9            /*  System PLL enable */
#define BITP_CLKG_CLK_CTL3_SPLLDIV2           8            /*  System PLL division by 2 */
#define BITP_CLKG_CLK_CTL3_SPLLNSEL           0            /*  System PLL N multiplier */
#define BITM_CLKG_CLK_CTL3_SPLLMUL2          (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  system PLL multiply by 2 */
#define BITM_CLKG_CLK_CTL3_SPLLMSEL          (_ADI_MSK_3(0x00007800,0x00007800UL, uint32_t  ))    /*  System PLL M Divider */
#define BITM_CLKG_CLK_CTL3_SPLLIE            (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  System PLL interrupt enable */
#define BITM_CLKG_CLK_CTL3_SPLLEN            (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  System PLL enable */
#define BITM_CLKG_CLK_CTL3_SPLLDIV2          (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  System PLL division by 2 */
#define BITM_CLKG_CLK_CTL3_SPLLNSEL          (_ADI_MSK_3(0x0000001F,0x0000001FUL, uint32_t  ))    /*  System PLL N multiplier */

/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_CLK_CTL5                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_CLK_CTL5_PERCLKOFF          5            /*  This bit is used to disable all clocks connected to all peripherals */
#define BITP_CLKG_CLK_CTL5_GPIOCLKOFF         4            /*  GPIO clock control */
#define BITP_CLKG_CLK_CTL5_UCLKI2COFF         3            /*  I2C clock user control */
#define BITP_CLKG_CLK_CTL5_GPTCLK2OFF         2            /*  GP timer 2 user control */
#define BITP_CLKG_CLK_CTL5_GPTCLK1OFF         1            /*  GP timer 1 user control */
#define BITP_CLKG_CLK_CTL5_GPTCLK0OFF         0            /*  GP timer 0 user control */
#define BITM_CLKG_CLK_CTL5_PERCLKOFF         (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  This bit is used to disable all clocks connected to all peripherals */
#define BITM_CLKG_CLK_CTL5_GPIOCLKOFF        (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  GPIO clock control */
#define BITM_CLKG_CLK_CTL5_UCLKI2COFF        (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  I2C clock user control */
#define BITM_CLKG_CLK_CTL5_GPTCLK2OFF        (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  GP timer 2 user control */
#define BITM_CLKG_CLK_CTL5_GPTCLK1OFF        (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  GP timer 1 user control */
#define BITM_CLKG_CLK_CTL5_GPTCLK0OFF        (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  GP timer 0 user control */

/* -------------------------------------------------------------------------------------------------------------------------
          CLKG_CLK_STAT0                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_CLKG_CLK_STAT0_HFXTALNOK        14            /*  HF crystal not stable */
#define BITP_CLKG_CLK_STAT0_HFXTALOK         13            /*  HF crystal stable */
#define BITP_CLKG_CLK_STAT0_HFXTAL           12            /*  HF crystal status */
#define BITP_CLKG_CLK_STAT0_LFXTALNOK        10            /*  LF crystal not stable */
#define BITP_CLKG_CLK_STAT0_LFXTALOK          9            /*  LF crystal stable */
#define BITP_CLKG_CLK_STAT0_LFXTAL            8            /*  LF crystal status */
#define BITP_CLKG_CLK_STAT0_SPLLUNLK          2            /*  System PLL unlock */
#define BITP_CLKG_CLK_STAT0_SPLLLK            1            /*  System PLL lock */
#define BITP_CLKG_CLK_STAT0_SPLL              0            /*  System PLL status */
#define BITM_CLKG_CLK_STAT0_HFXTALNOK        (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  HF crystal not stable */
#define BITM_CLKG_CLK_STAT0_HFXTALOK         (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  HF crystal stable */
#define BITM_CLKG_CLK_STAT0_HFXTAL           (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  HF crystal status */
#define BITM_CLKG_CLK_STAT0_LFXTALNOK        (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  LF crystal not stable */
#define BITM_CLKG_CLK_STAT0_LFXTALOK         (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  LF crystal stable */
#define BITM_CLKG_CLK_STAT0_LFXTAL           (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  LF crystal status */
#define BITM_CLKG_CLK_STAT0_SPLLUNLK         (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  System PLL unlock */
#define BITM_CLKG_CLK_STAT0_SPLLLK           (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  System PLL lock */
#define BITM_CLKG_CLK_STAT0_SPLL             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  System PLL status */


/* ============================================================================================================================
        Bus matrix
   ============================================================================================================================ */

/* ============================================================================================================================
        BUSM0
   ============================================================================================================================ */
#define REG_BUSM0_ARBIT0                     0x4004C800            /*  BUSM0 Arbitration Priority Configuration for FLASH and SRAM0 */
#define REG_BUSM0_ARBIT1                     0x4004C804            /*  BUSM0 Arbitration Priority Configuration for SRAM1 and SIP */
#define REG_BUSM0_ARBIT2                     0x4004C808            /*  BUSM0 Arbitration Priority Configuration for APB32 and APB16 */
#define REG_BUSM0_ARBIT3                     0x4004C80C            /*  BUSM0 Arbitration Priority Configuration for APB16 priority for core and for DMA1 */

/* ============================================================================================================================
        BUSM Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          BUSM_ARBIT0                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_BUSM_ARBIT0_SRAM0_DMA0          20            /*  SRAM0 priority for DMA0 */
#define BITP_BUSM_ARBIT0_SRAM0_SBUS          18            /*  SRAM0 priority for SBUS */
#define BITP_BUSM_ARBIT0_SRAM0_DCODE         16            /*  SRAM0 priority for Dcode */
#define BITP_BUSM_ARBIT0_FLSH_DMA0            4            /*  Flash priority for DMA0 */
#define BITP_BUSM_ARBIT0_FLSH_SBUS            2            /*  Flash priority for SBUS */
#define BITP_BUSM_ARBIT0_FLSH_DCODE           0            /*  Flash priority for DCODE */
#define BITM_BUSM_ARBIT0_SRAM0_DMA0          (_ADI_MSK_3(0x00300000,0x00300000UL, uint32_t  ))    /*  SRAM0 priority for DMA0 */
#define BITM_BUSM_ARBIT0_SRAM0_SBUS          (_ADI_MSK_3(0x000C0000,0x000C0000UL, uint32_t  ))    /*  SRAM0 priority for SBUS */
#define BITM_BUSM_ARBIT0_SRAM0_DCODE         (_ADI_MSK_3(0x00030000,0x00030000UL, uint32_t  ))    /*  SRAM0 priority for Dcode */
#define BITM_BUSM_ARBIT0_FLSH_DMA0           (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  Flash priority for DMA0 */
#define BITM_BUSM_ARBIT0_FLSH_SBUS           (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  Flash priority for SBUS */
#define BITM_BUSM_ARBIT0_FLSH_DCODE          (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  Flash priority for DCODE */

/* -------------------------------------------------------------------------------------------------------------------------
          BUSM_ARBIT1                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_BUSM_ARBIT1_SIP_DMA0            20            /*  SIP priority for DMA0 */
#define BITP_BUSM_ARBIT1_SIP_SBUS            18            /*  SIP priority for SBUS */
#define BITP_BUSM_ARBIT1_SIP_DCODE           16            /*  SIP priority for DCODE */
#define BITP_BUSM_ARBIT1_SRAM1_DMA0           4            /*  SRAM1 priority for DMA0 */
#define BITP_BUSM_ARBIT1_SRAM1_SBUS           2            /*  SRAM1 priority for SBUS */
#define BITP_BUSM_ARBIT1_SRAM1_DCODE          0            /*  SRAM1 priority for Dcode */
#define BITM_BUSM_ARBIT1_SIP_DMA0            (_ADI_MSK_3(0x00300000,0x00300000UL, uint32_t  ))    /*  SIP priority for DMA0 */
#define BITM_BUSM_ARBIT1_SIP_SBUS            (_ADI_MSK_3(0x000C0000,0x000C0000UL, uint32_t  ))    /*  SIP priority for SBUS */
#define BITM_BUSM_ARBIT1_SIP_DCODE           (_ADI_MSK_3(0x00030000,0x00030000UL, uint32_t  ))    /*  SIP priority for DCODE */
#define BITM_BUSM_ARBIT1_SRAM1_DMA0          (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  SRAM1 priority for DMA0 */
#define BITM_BUSM_ARBIT1_SRAM1_SBUS          (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  SRAM1 priority for SBUS */
#define BITM_BUSM_ARBIT1_SRAM1_DCODE         (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  SRAM1 priority for Dcode */

/* -------------------------------------------------------------------------------------------------------------------------
          BUSM_ARBIT2                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_BUSM_ARBIT2_APB16_DMA0          20            /*  APB16 priority for DMA0 */
#define BITP_BUSM_ARBIT2_APB16_SBUS          18            /*  APB16 priority for SBUS */
#define BITP_BUSM_ARBIT2_APB16_DCODE         16            /*  APB16 priority for DCODE */
#define BITP_BUSM_ARBIT2_APB32_DMA0           4            /*  APB32 priority for DMA0 */
#define BITP_BUSM_ARBIT2_APB32_SBUS           2            /*  APB32 priority for SBUS */
#define BITP_BUSM_ARBIT2_APB32_DCODE          0            /*  APB32 priority for DCODE */
#define BITM_BUSM_ARBIT2_APB16_DMA0          (_ADI_MSK_3(0x00300000,0x00300000UL, uint32_t  ))    /*  APB16 priority for DMA0 */
#define BITM_BUSM_ARBIT2_APB16_SBUS          (_ADI_MSK_3(0x000C0000,0x000C0000UL, uint32_t  ))    /*  APB16 priority for SBUS */
#define BITM_BUSM_ARBIT2_APB16_DCODE         (_ADI_MSK_3(0x00030000,0x00030000UL, uint32_t  ))    /*  APB16 priority for DCODE */
#define BITM_BUSM_ARBIT2_APB32_DMA0          (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  APB32 priority for DMA0 */
#define BITM_BUSM_ARBIT2_APB32_SBUS          (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  APB32 priority for SBUS */
#define BITM_BUSM_ARBIT2_APB32_DCODE         (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  APB32 priority for DCODE */

/* -------------------------------------------------------------------------------------------------------------------------
          BUSM_ARBIT3                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_BUSM_ARBIT3_APB16_4DMA_DMA1     17            /*  APB16 for dma priority for DMA1 */
#define BITP_BUSM_ARBIT3_APB16_4DMA_CORE     16            /*  APB16 for dma priority for CORE */
#define BITP_BUSM_ARBIT3_APB16_DMA1           1            /*  APB16 priority for DMA1 */
#define BITP_BUSM_ARBIT3_APB16_CORE           0            /*  APB16 priority for CORE */
#define BITM_BUSM_ARBIT3_APB16_4DMA_DMA1     (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))    /*  APB16 for dma priority for DMA1 */
#define BITM_BUSM_ARBIT3_APB16_4DMA_CORE     (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  APB16 for dma priority for CORE */
#define BITM_BUSM_ARBIT3_APB16_DMA1          (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  APB16 priority for DMA1 */
#define BITM_BUSM_ARBIT3_APB16_CORE          (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  APB16 priority for CORE */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        AGPIO2
   ============================================================================================================================ */
#define REG_AGPIO2_CON                       0x400C0080            /*  AGPIO2 GPIO Port Configuration */
#define REG_AGPIO2_OEN                       0x400C0084            /*  AGPIO2 GPIO Port Output Enable */
#define REG_AGPIO2_PE                        0x400C0088            /*  AGPIO2 GPIO Port Pullup/Pulldown Enable */
#define REG_AGPIO2_IEN                       0x400C008C            /*  AGPIO2 GPIO Port Input Path Enable */
#define REG_AGPIO2_IN                        0x400C0090            /*  AGPIO2 GPIO Port Registered Data Input */
#define REG_AGPIO2_OUT                       0x400C0094            /*  AGPIO2 GPIO Port Data Output */
#define REG_AGPIO2_SET                       0x400C0098            /*  AGPIO2 GPIO Port Data Out Set */
#define REG_AGPIO2_CLR                       0x400C009C            /*  AGPIO2 GPIO Port Data Out Clear */
#define REG_AGPIO2_TGL                       0x400C00A0            /*  AGPIO2 GPIO Port Pin Toggle */

/* ============================================================================================================================
        AGPIO Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_CON                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_CON_PIN7CFG               14            /*  Pin 7 Configuration Bits */
#define BITP_AGPIO_CON_PIN6CFG               12            /*  Pin 6 Configuration Bits */
#define BITP_AGPIO_CON_PIN5CFG               10            /*  Pin 5 Configuration Bits */
#define BITP_AGPIO_CON_PIN4CFG                8            /*  Pin 4 Configuration Bits */
#define BITP_AGPIO_CON_PIN3CFG                6            /*  Pin 3 Configuration Bits */
#define BITP_AGPIO_CON_PIN2CFG                4            /*  Pin 2 Configuration Bits */
#define BITP_AGPIO_CON_PIN1CFG                2            /*  Pin 1 Configuration Bits */
#define BITP_AGPIO_CON_PIN0CFG                0            /*  Pin 0 Configuration Bits */
#define BITM_AGPIO_CON_PIN7CFG               (_ADI_MSK_3(0x0000C000,0x0000C000UL, uint32_t  ))    /*  Pin 7 Configuration Bits */
#define BITM_AGPIO_CON_PIN6CFG               (_ADI_MSK_3(0x00003000,0x00003000UL, uint32_t  ))    /*  Pin 6 Configuration Bits */
#define BITM_AGPIO_CON_PIN5CFG               (_ADI_MSK_3(0x00000C00,0x00000C00UL, uint32_t  ))    /*  Pin 5 Configuration Bits */
#define BITM_AGPIO_CON_PIN4CFG               (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  Pin 4 Configuration Bits */
#define BITM_AGPIO_CON_PIN3CFG               (_ADI_MSK_3(0x000000C0,0x000000C0UL, uint32_t  ))    /*  Pin 3 Configuration Bits */
#define BITM_AGPIO_CON_PIN2CFG               (_ADI_MSK_3(0x00000030,0x00000030UL, uint32_t  ))    /*  Pin 2 Configuration Bits */
#define BITM_AGPIO_CON_PIN1CFG               (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  Pin 1 Configuration Bits */
#define BITM_AGPIO_CON_PIN0CFG               (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  Pin 0 Configuration Bits */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_OEN                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_OEN_OEN                    0            /*  Pin Output Drive enable */
#define BITM_AGPIO_OEN_OEN                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Pin Output Drive enable */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_PE                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_PE_PE                      0            /*  Pin Pull enable */
#define BITM_AGPIO_PE_PE                     (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Pin Pull enable */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_IEN                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_IEN_IEN                    0            /*  Input path enable */
#define BITM_AGPIO_IEN_IEN                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Input path enable */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_IN                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_IN_IN                      0            /*  Registered data input */
#define BITM_AGPIO_IN_IN                     (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Registered data input */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_OUT                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_OUT_OUT                    0            /*  Data out */
#define BITM_AGPIO_OUT_OUT                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Data out */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_SET                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_SET_SET                    0            /*  Set the output HIGH for the pin */
#define BITM_AGPIO_SET_SET                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Set the output HIGH for the pin */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_CLR                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_CLR_CLR                    0            /*  Set the output low  for the port pin */
#define BITM_AGPIO_CLR_CLR                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Set the output low  for the port pin */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPIO_TGL                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPIO_TGL_TGL                    0            /*  Toggle the output of the port pin */
#define BITM_AGPIO_TGL_TGL                   (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Toggle the output of the port pin */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        AFECON
   ============================================================================================================================ */
#define REG_AFECON_ADIID                     0x400C0400            /*  AFECON ADI Identification */
#define REG_AFECON_CHIPID                    0x400C0404            /*  AFECON Chip Identification */
#define REG_AFECON_CLKCON0                   0x400C0408            /*  AFECON Clock Divider Configuration */
#define REG_AFECON_CLKEN1                    0x400C0410            /*  AFECON Clock Gate Enable */
#define REG_AFECON_CLKSEL                    0x400C0414            /*  AFECON Clock Select */
#define REG_AFECON_GPIOCLKMUXSEL             0x400C041C            /*  AFECON GPIO Clock MUX Select */
#define REG_AFECON_CLKCON0KEY                0x400C0420            /*  AFECON Enable Clock Division to 8Mhz,4Mhz and 2Mhz */
#define REG_AFECON_MKEY                      0x400C0434            /*  AFECON MKEY */
#define REG_AFECON_DSPUPDATEEN               0x400C0438            /*  AFECON DSP Update Enable */

/* ============================================================================================================================
        AFECON Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_ADIID                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_ADIID_ADIID               0            /*  ADI Identifier. */
#define BITM_AFECON_ADIID_ADIID              (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  ADI Identifier. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_CHIPID                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_CHIPID_PARTID             4            /*  Part Identifier */
#define BITP_AFECON_CHIPID_REVISION           0            /*  Silicon Revision Number */
#define BITM_AFECON_CHIPID_PARTID            (_ADI_MSK_3(0x0000FFF0,0x0000FFF0U, uint16_t  ))    /*  Part Identifier */
#define BITM_AFECON_CHIPID_REVISION          (_ADI_MSK_3(0x0000000F,0x0000000FU, uint16_t  ))    /*  Silicon Revision Number */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_CLKCON0                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_CLKCON0_SFFTCLKDIVCNT    10            /*  SFFT Clock Divider Configuration */
#define BITP_AFECON_CLKCON0_ADCCLKDIV         6            /*  ADC Clock Divider Configuration */
#define BITP_AFECON_CLKCON0_SYSCLKDIV         0            /*  System Clock Divider Configuration */
#define BITM_AFECON_CLKCON0_SFFTCLKDIVCNT    (_ADI_MSK_3(0x0000FC00,0x0000FC00U, uint16_t  ))    /*  SFFT Clock Divider Configuration */
#define BITM_AFECON_CLKCON0_ADCCLKDIV        (_ADI_MSK_3(0x000003C0,0x000003C0U, uint16_t  ))    /*  ADC Clock Divider Configuration */
#define BITM_AFECON_CLKCON0_SYSCLKDIV        (_ADI_MSK_3(0x0000003F,0x0000003FU, uint16_t  ))    /*  System Clock Divider Configuration */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_CLKEN1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_CLKEN1_GPT1DIS            7            /*  GPT1 Clock Enable */
#define BITP_AFECON_CLKEN1_GPT0DIS            6            /*  GPT0 Clock Enable */
#define BITP_AFECON_CLKEN1_ACLKDIS            5            /*  ACLK Clock Enable */
#define BITM_AFECON_CLKEN1_GPT1DIS           (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  GPT1 Clock Enable */
#define BITM_AFECON_CLKEN1_GPT0DIS           (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  GPT0 Clock Enable */
#define BITM_AFECON_CLKEN1_ACLKDIS           (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  ACLK Clock Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_CLKSEL                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_CLKSEL_ADCCLKSEL          2            /*  Select ADC Clock Source */
#define BITP_AFECON_CLKSEL_SYSCLKSEL          0            /*  Select System Clock Source */
#define BITM_AFECON_CLKSEL_ADCCLKSEL         (_ADI_MSK_3(0x0000000C,0x0000000CU, uint16_t  ))    /*  Select ADC Clock Source */
#define BITM_AFECON_CLKSEL_SYSCLKSEL         (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Select System Clock Source */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_GPIOCLKMUXSEL                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_GPIOCLKMUXSEL_SEL         0            /*  Configure Clock MUX Out to GPIO */
#define BITM_AFECON_GPIOCLKMUXSEL_SEL        (_ADI_MSK_3(0x00000007,0x00000007U, uint16_t  ))    /*  Configure Clock MUX Out to GPIO */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_CLKCON0KEY                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_CLKCON0KEY_DIVSYSCLK_ULP_EN  0            /*  Enable Clock Division to 8Mhz,4Mhz and 2Mhz */
#define BITM_AFECON_CLKCON0KEY_DIVSYSCLK_ULP_EN (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Enable Clock Division to 8Mhz,4Mhz and 2Mhz */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_MKEY                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_MKEY_KEY                  0            /*  Key to Unlock SWRSTCON */
#define BITM_AFECON_MKEY_KEY                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFU, uint16_t  ))    /*  Key to Unlock SWRSTCON */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECON_DSPUPDATEEN                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECON_DSPUPDATEEN_DSPLOOP       0            /*  ADC Digital Logic Test */
#define BITM_AFECON_DSPUPDATEEN_DSPLOOP      (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  ADC Digital Logic Test */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        AFEWDT
   ============================================================================================================================ */
#define REG_AFEWDT_WDTLD                     0x400C0900            /*  AFEWDT Watchdog Timer Load Value */
#define REG_AFEWDT_WDTVALS                   0x400C0904            /*  AFEWDT Current Count Value */
#define REG_AFEWDT_WDTCON                    0x400C0908            /*  AFEWDT Watchdog Timer Control Register */
#define REG_AFEWDT_WDTCLRI                   0x400C090C            /*  AFEWDT Refresh Watchdog Register */
#define REG_AFEWDT_WDTSTA                    0x400C0918            /*  AFEWDT Timer Status */
#define REG_AFEWDT_WDTMINLD                  0x400C091C            /*  AFEWDT Minimum Load Value */

/* ============================================================================================================================
        AFEWDT Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AFEWDT_WDTLD                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFEWDT_WDTLD_LOAD                0            /*  WDT Load Value */
#define BITM_AFEWDT_WDTLD_LOAD               (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  WDT Load Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AFEWDT_WDTVALS                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFEWDT_WDTVALS_CCOUNT            0            /*  Current WDT Count Value. */
#define BITM_AFEWDT_WDTVALS_CCOUNT           (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Current WDT Count Value. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFEWDT_WDTCON                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFEWDT_WDTCON_RESERVED_15_11    11            /*  RESERVED */
#define BITP_AFEWDT_WDTCON_WDTIRQEN          10            /*  WDT Interrupt Enable */
#define BITP_AFEWDT_WDTCON_MINLOAD_EN         9            /*  Timer Window Control */
#define BITP_AFEWDT_WDTCON_CLKDIV2            8            /*  Clock Source */
#define BITP_AFEWDT_WDTCON_RESERVED1_7        7            /*  Reserved */
#define BITP_AFEWDT_WDTCON_MDE                6            /*  Timer Mode Select */
#define BITP_AFEWDT_WDTCON_EN                 5            /*  Timer Enable */
#define BITP_AFEWDT_WDTCON_PRE                2            /*  Prescaler. */
#define BITP_AFEWDT_WDTCON_IRQ                1            /*  WDT Interrupt Enable */
#define BITP_AFEWDT_WDTCON_PDSTOP             0            /*  Power Down Stop Enable */
#define BITM_AFEWDT_WDTCON_RESERVED_15_11    (_ADI_MSK_3(0x0000F800,0x0000F800U, uint16_t  ))    /*  RESERVED */
#define BITM_AFEWDT_WDTCON_WDTIRQEN          (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  WDT Interrupt Enable */
#define BITM_AFEWDT_WDTCON_MINLOAD_EN        (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Timer Window Control */
#define BITM_AFEWDT_WDTCON_CLKDIV2           (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Clock Source */
#define BITM_AFEWDT_WDTCON_RESERVED1_7       (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Reserved */
#define BITM_AFEWDT_WDTCON_MDE               (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Timer Mode Select */
#define BITM_AFEWDT_WDTCON_EN                (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Timer Enable */
#define BITM_AFEWDT_WDTCON_PRE               (_ADI_MSK_3(0x0000000C,0x0000000CU, uint16_t  ))    /*  Prescaler. */
#define BITM_AFEWDT_WDTCON_IRQ               (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  WDT Interrupt Enable */
#define BITM_AFEWDT_WDTCON_PDSTOP            (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Power Down Stop Enable */
#define ENUM_AFEWDT_WDTCON_RESET             (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  IRQ: Watchdog Timer timeout creates a reset. */
#define ENUM_AFEWDT_WDTCON_INTERRUPT         (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  IRQ: Watchdog Timer  timeout creates an interrupt instead of reset. */
#define ENUM_AFEWDT_WDTCON_CONTINUE          (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  PDSTOP: Continue Counting When In Hibernate */
#define ENUM_AFEWDT_WDTCON_STOP              (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  PDSTOP: Stop Counter When In Hibernate. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFEWDT_WDTCLRI                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFEWDT_WDTCLRI_CLRWDG            0            /*  Refresh Register */
#define BITM_AFEWDT_WDTCLRI_CLRWDG           (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Refresh Register */

/* -------------------------------------------------------------------------------------------------------------------------
          AFEWDT_WDTSTA                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFEWDT_WDTSTA_RESERVED_15_7      7            /*  RESERVED */
#define BITP_AFEWDT_WDTSTA_TMINLD             6            /*  WDTMINLD Write Status */
#define BITP_AFEWDT_WDTSTA_OTPWRDONE          5            /*  Reset Type Status */
#define BITP_AFEWDT_WDTSTA_LOCK               4            /*  Lock Status */
#define BITP_AFEWDT_WDTSTA_CON                3            /*  WDTCON Write Status */
#define BITP_AFEWDT_WDTSTA_TLD                2            /*  WDTVAL Write Status */
#define BITP_AFEWDT_WDTSTA_CLRI               1            /*  WDTCLRI Write Status */
#define BITP_AFEWDT_WDTSTA_IRQ                0            /*  WDT Interrupt */
#define BITM_AFEWDT_WDTSTA_RESERVED_15_7     (_ADI_MSK_3(0x0000FF80,0x0000FF80U, uint16_t  ))    /*  RESERVED */
#define BITM_AFEWDT_WDTSTA_TMINLD            (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  WDTMINLD Write Status */
#define BITM_AFEWDT_WDTSTA_OTPWRDONE         (_ADI_MSK_3(0x00000020,0x00000020U, uint16_t  ))    /*  Reset Type Status */
#define BITM_AFEWDT_WDTSTA_LOCK              (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Lock Status */
#define BITM_AFEWDT_WDTSTA_CON               (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  WDTCON Write Status */
#define BITM_AFEWDT_WDTSTA_TLD               (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  WDTVAL Write Status */
#define BITM_AFEWDT_WDTSTA_CLRI              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  WDTCLRI Write Status */
#define BITM_AFEWDT_WDTSTA_IRQ               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  WDT Interrupt */
#define ENUM_AFEWDT_WDTSTA_OPEN              (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  LOCK: Timer Operation Not Locked */
#define ENUM_AFEWDT_WDTSTA_LOCKED            (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  LOCK: Timer Enabled and Locked */
#define ENUM_AFEWDT_WDTSTA_SYNC_COMPLETE     (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  TLD: Arm and AFE Watchdog Clock Domains WDTLD values match */
#define ENUM_AFEWDT_WDTSTA_SYNC_IN_PROGRESS  (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  TLD: Synchronize In Progress */
#define ENUM_AFEWDT_WDTSTA_CLEARED           (_ADI_MSK_3(0x00000000,0x00000000U, uint16_t  ))    /*  IRQ: Watchdog Timer Interrupt Not Pending */
#define ENUM_AFEWDT_WDTSTA_PENDING           (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  IRQ: Watchdog Timer Interrupt Pending */

/* -------------------------------------------------------------------------------------------------------------------------
          AFEWDT_WDTMINLD                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFEWDT_WDTMINLD_MIN_LOAD         0            /*  WDT Min Load Value */
#define BITM_AFEWDT_WDTMINLD_MIN_LOAD        (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  WDT Min Load Value */


/* ============================================================================================================================
        Always On Register
   ============================================================================================================================ */

/* ============================================================================================================================
        ALLON
   ============================================================================================================================ */
#define REG_ALLON_PWRMOD                     0x400C0A00            /*  ALLON Power Modes */
#define REG_ALLON_PWRKEY                     0x400C0A04            /*  ALLON Key Protection for PWRMOD */
#define REG_ALLON_OSCKEY                     0x400C0A0C            /*  ALLON Key Protection for OSCCON */
#define REG_ALLON_OSCCON                     0x400C0A10            /*  ALLON Oscillator Control */
#define REG_ALLON_EI2CON                     0x400C0A28            /*  ALLON External Interrupt Configuration 2 */
#define REG_ALLON_EICLR                      0x400C0A30            /*  ALLON External Interrupt Clear */
#define REG_ALLON_RSTSTA                     0x400C0A40            /*  ALLON Reset Status */
#define REG_ALLON_PMUSTA                     0x400C0A44            /*  ALLON PMU Status */
#define REG_ALLON_CLKEN0                     0x400C0A70            /*  ALLON 32KHz Peripheral Clock Enable */

/* ============================================================================================================================
        ALLON Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_PWRMOD                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_PWRMOD_PWRMOD              0            /*  Power Mode Control Bits */
#define BITM_ALLON_PWRMOD_PWRMOD             (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Power Mode Control Bits */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_PWRKEY                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_PWRKEY_PWRKEY              0            /*  PWRMOD Key Register */
#define BITM_ALLON_PWRKEY_PWRKEY             (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  PWRMOD Key Register */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_OSCKEY                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_OSCKEY_OSCKEY              0            /*  Oscillator Control Key Register. */
#define BITM_ALLON_OSCKEY_OSCKEY             (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Oscillator Control Key Register. */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_OSCCON                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_OSCCON_HFXTALOK           10            /*  Status of HFXTAL Oscillator */
#define BITP_ALLON_OSCCON_HFOSCOK             9            /*  Status of HFOSC Oscillator */
#define BITP_ALLON_OSCCON_LFOSCOK             8            /*  Status of LFOSC Oscillator */
#define BITP_ALLON_OSCCON_HFXTALEN            2            /*  High Frequency Crystal Oscillator Enable */
#define BITP_ALLON_OSCCON_HFOSCEN             1            /*  High Frequency Internal Oscillator Enable */
#define BITP_ALLON_OSCCON_LFOSCEN             0            /*  Low Frequency Internal Oscillator Enable */
#define BITM_ALLON_OSCCON_HFXTALOK           (_ADI_MSK_3(0x00000400,0x00000400U, uint16_t  ))    /*  Status of HFXTAL Oscillator */
#define BITM_ALLON_OSCCON_HFOSCOK            (_ADI_MSK_3(0x00000200,0x00000200U, uint16_t  ))    /*  Status of HFOSC Oscillator */
#define BITM_ALLON_OSCCON_LFOSCOK            (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Status of LFOSC Oscillator */
#define BITM_ALLON_OSCCON_HFXTALEN           (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  High Frequency Crystal Oscillator Enable */
#define BITM_ALLON_OSCCON_HFOSCEN            (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  High Frequency Internal Oscillator Enable */
#define BITM_ALLON_OSCCON_LFOSCEN            (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Low Frequency Internal Oscillator Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_EI2CON                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_EI2CON_BUSINTEN            3            /*  BUS Interrupt Detection Enable Bit */
#define BITP_ALLON_EI2CON_BUSINTMDE           0            /*  BUS Interrupt Detection Mode Registers */
#define BITM_ALLON_EI2CON_BUSINTEN           (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  BUS Interrupt Detection Enable Bit */
#define BITM_ALLON_EI2CON_BUSINTMDE          (_ADI_MSK_3(0x00000007,0x00000007U, uint16_t  ))    /*  BUS Interrupt Detection Mode Registers */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_EICLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_EICLR_AUTCLRBUSEN         15            /*  Enable Auto Clear of Bus Interrupt */
#define BITP_ALLON_EICLR_BUSINT               8            /*  BUS Interrupt */
#define BITM_ALLON_EICLR_AUTCLRBUSEN         (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Enable Auto Clear of Bus Interrupt */
#define BITM_ALLON_EICLR_BUSINT              (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  BUS Interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_RSTSTA                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_RSTSTA_MMRSWRST            3            /*  MMR Software Reset */
#define BITP_ALLON_RSTSTA_WDRST               2            /*  Watchdog Timeout */
#define BITP_ALLON_RSTSTA_EXTRST              1            /*  External Reset */
#define BITP_ALLON_RSTSTA_POR                 0            /*  Power-on Reset */
#define BITM_ALLON_RSTSTA_MMRSWRST           (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  MMR Software Reset */
#define BITM_ALLON_RSTSTA_WDRST              (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Watchdog Timeout */
#define BITM_ALLON_RSTSTA_EXTRST             (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  External Reset */
#define BITM_ALLON_RSTSTA_POR                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Power-on Reset */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_PMUSTA                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_PMUSTA_PMUSTATE            0            /*  PMU FSM States */
#define BITM_ALLON_PMUSTA_PMUSTATE           (_ADI_MSK_3(0x00000007,0x00000007U, uint16_t  ))    /*  PMU FSM States */

/* -------------------------------------------------------------------------------------------------------------------------
          ALLON_CLKEN0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_ALLON_CLKEN0_TIACHPDIS           2            /*  TIA Chop Clock Disable */
#define BITP_ALLON_CLKEN0_SLPWUTDIS           1            /*  Sleep/Wakeup Timer Clock Disable */
#define BITP_ALLON_CLKEN0_WDTDIS              0            /*  Watch Dog Timer Clock Disable */
#define BITM_ALLON_CLKEN0_TIACHPDIS          (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  TIA Chop Clock Disable */
#define BITM_ALLON_CLKEN0_SLPWUTDIS          (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Sleep/Wakeup Timer Clock Disable */
#define BITM_ALLON_CLKEN0_WDTDIS             (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Watch Dog Timer Clock Disable */


/* ============================================================================================================================
        General Purpose Timer
   ============================================================================================================================ */

/* ============================================================================================================================
        AGPT0
   ============================================================================================================================ */
#define REG_AGPT0_LD0                        0x400C0D00            /*  AGPT0 16-bit Load Value Register. */
#define REG_AGPT0_VAL0                       0x400C0D04            /*  AGPT0 16-Bit Timer Value Register. */
#define REG_AGPT0_CON0                       0x400C0D08            /*  AGPT0 Control Register. */
#define REG_AGPT0_CLRI0                      0x400C0D0C            /*  AGPT0 Clear Interrupt Register. */
#define REG_AGPT0_CAP0                       0x400C0D10            /*  AGPT0 Capture Register. */
#define REG_AGPT0_ALD0                       0x400C0D14            /*  AGPT0 16-Bit Load Value, Asynchronous. */
#define REG_AGPT0_AVAL0                      0x400C0D18            /*  AGPT0 16-Bit Timer Value, Asynchronous Register. */
#define REG_AGPT0_STA0                       0x400C0D1C            /*  AGPT0 Status Register. */
#define REG_AGPT0_PWMCON0                    0x400C0D20            /*  AGPT0 PWM Control Register. */
#define REG_AGPT0_PWMMAT0                    0x400C0D24            /*  AGPT0 PWM Match Value Register. */
#define REG_AGPT0_INTEN                      0x400C0D28            /*  AGPT0 Interrupt Enable */

/* ============================================================================================================================
        AGPT0 Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_LD0                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_LD0_LOAD                   0            /*  Load Value */
#define BITM_AGPT0_LD0_LOAD                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_VAL0                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_VAL0_VAL                   0            /*  Current Count */
#define BITM_AGPT0_VAL0_VAL                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Current Count */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_CON0                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_CON0_SYNCBYP              15            /*  Synchronization Bypass */
#define BITP_AGPT0_CON0_RSTEN                14            /*  Counter and Prescale Reset Enable */
#define BITP_AGPT0_CON0_EVTEN                13            /*  Event Select */
#define BITP_AGPT0_CON0_EVENT                 8            /*  Event Select Range */
#define BITP_AGPT0_CON0_RLD                   7            /*  Reload Control */
#define BITP_AGPT0_CON0_CLK                   5            /*  Clock Select */
#define BITP_AGPT0_CON0_ENABLE                4            /*  Timer Enable */
#define BITP_AGPT0_CON0_MOD                   3            /*  Timer Mode */
#define BITP_AGPT0_CON0_UP                    2            /*  Count up */
#define BITP_AGPT0_CON0_PRE                   0            /*  Prescaler */
#define BITM_AGPT0_CON0_SYNCBYP              (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Synchronization Bypass */
#define BITM_AGPT0_CON0_RSTEN                (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Counter and Prescale Reset Enable */
#define BITM_AGPT0_CON0_EVTEN                (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Event Select */
#define BITM_AGPT0_CON0_EVENT                (_ADI_MSK_3(0x00001F00,0x00001F00U, uint16_t  ))    /*  Event Select Range */
#define BITM_AGPT0_CON0_RLD                  (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Reload Control */
#define BITM_AGPT0_CON0_CLK                  (_ADI_MSK_3(0x00000060,0x00000060U, uint16_t  ))    /*  Clock Select */
#define BITM_AGPT0_CON0_ENABLE               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Timer Enable */
#define BITM_AGPT0_CON0_MOD                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Timer Mode */
#define BITM_AGPT0_CON0_UP                   (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Count up */
#define BITM_AGPT0_CON0_PRE                  (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Prescaler */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_CLRI0                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_CLRI0_CAP                  1            /*  Clear Captured Event Interrupt */
#define BITP_AGPT0_CLRI0_TMOUT                0            /*  Clear Timeout Interrupt */
#define BITM_AGPT0_CLRI0_CAP                 (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Clear Captured Event Interrupt */
#define BITM_AGPT0_CLRI0_TMOUT               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Clear Timeout Interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_CAP0                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_CAP0_CAP                   0            /*  16-bit Captured Value */
#define BITM_AGPT0_CAP0_CAP                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  16-bit Captured Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_ALD0                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_ALD0_ALOAD                 0            /*  Load Value, Asynchronous */
#define BITM_AGPT0_ALD0_ALOAD                (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load Value, Asynchronous */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_AVAL0                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_AVAL0_AVAL                 0            /*  Counter Value */
#define BITM_AGPT0_AVAL0_AVAL                (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Counter Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_STA0                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_STA0_RSTCNT                8            /*  Counter Reset Occurring */
#define BITP_AGPT0_STA0_PDOK                  7            /*  Clear Interrupt Register Synchronization */
#define BITP_AGPT0_STA0_BUSY                  6            /*  Timer Busy */
#define BITP_AGPT0_STA0_CAP                   1            /*  Capture Event Pending */
#define BITP_AGPT0_STA0_TMOUT                 0            /*  Timeout Event Occurred */
#define BITM_AGPT0_STA0_RSTCNT               (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Counter Reset Occurring */
#define BITM_AGPT0_STA0_PDOK                 (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Clear Interrupt Register Synchronization */
#define BITM_AGPT0_STA0_BUSY                 (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Timer Busy */
#define BITM_AGPT0_STA0_CAP                  (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Capture Event Pending */
#define BITM_AGPT0_STA0_TMOUT                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Timeout Event Occurred */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_PWMCON0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_PWMCON0_IDLE               1            /*  PWM Idle State */
#define BITP_AGPT0_PWMCON0_MATCHEN            0            /*  PWM Match Enabled */
#define BITM_AGPT0_PWMCON0_IDLE              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  PWM Idle State */
#define BITM_AGPT0_PWMCON0_MATCHEN           (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  PWM Match Enabled */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_PWMMAT0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_PWMMAT0_MATCHVAL           0            /*  PWM Match Value */
#define BITM_AGPT0_PWMMAT0_MATCHVAL          (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  PWM Match Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT0_INTEN                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT0_INTEN_INTEN                0            /*  Interrupt Enable */
#define BITM_AGPT0_INTEN_INTEN               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Interrupt Enable */


/* ============================================================================================================================
        General Purpose Timer
   ============================================================================================================================ */

/* ============================================================================================================================
        AGPT1
   ============================================================================================================================ */
#define REG_AGPT1_LD1                        0x400C0E00            /*  AGPT1 16-bit Load Value Register */
#define REG_AGPT1_VAL1                       0x400C0E04            /*  AGPT1 16-bit Timer Value Register */
#define REG_AGPT1_CON1                       0x400C0E08            /*  AGPT1 Control Register */
#define REG_AGPT1_CLRI1                      0x400C0E0C            /*  AGPT1 Clear Interrupt Register */
#define REG_AGPT1_CAP1                       0x400C0E10            /*  AGPT1 Capture Register */
#define REG_AGPT1_ALD1                       0x400C0E14            /*  AGPT1 16-bit Load Value, Asynchronous Register */
#define REG_AGPT1_AVAL1                      0x400C0E18            /*  AGPT1 16-bit Timer Value, Asynchronous Register */
#define REG_AGPT1_STA1                       0x400C0E1C            /*  AGPT1 Status Register */
#define REG_AGPT1_PWMCON1                    0x400C0E20            /*  AGPT1 PWM Control Register */
#define REG_AGPT1_PWMMAT1                    0x400C0E24            /*  AGPT1 PWM Match Value Register */
#define REG_AGPT1_INTEN1                     0x400C0E28            /*  AGPT1 Interrupt Enable */

/* ============================================================================================================================
        AGPT1 Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_LD1                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_LD1_LOAD                   0            /*  Load Value */
#define BITM_AGPT1_LD1_LOAD                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_VAL1                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_VAL1_VAL                   0            /*  Current Count */
#define BITM_AGPT1_VAL1_VAL                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Current Count */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_CON1                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_CON1_SYNCBYP              15            /*  Synchronization Bypass */
#define BITP_AGPT1_CON1_RSTEN                14            /*  Counter and Prescale Reset Enable */
#define BITP_AGPT1_CON1_EVENTEN              13            /*  Event Select */
#define BITP_AGPT1_CON1_EVENT                 8            /*  Event Select Range */
#define BITP_AGPT1_CON1_RLD                   7            /*  Reload Control */
#define BITP_AGPT1_CON1_CLK                   5            /*  Clock Select */
#define BITP_AGPT1_CON1_ENABLE                4            /*  Timer Enable */
#define BITP_AGPT1_CON1_MOD                   3            /*  Timer Mode */
#define BITP_AGPT1_CON1_UP                    2            /*  Count up */
#define BITP_AGPT1_CON1_PRE                   0            /*  Prescaler */
#define BITM_AGPT1_CON1_SYNCBYP              (_ADI_MSK_3(0x00008000,0x00008000U, uint16_t  ))    /*  Synchronization Bypass */
#define BITM_AGPT1_CON1_RSTEN                (_ADI_MSK_3(0x00004000,0x00004000U, uint16_t  ))    /*  Counter and Prescale Reset Enable */
#define BITM_AGPT1_CON1_EVENTEN              (_ADI_MSK_3(0x00002000,0x00002000U, uint16_t  ))    /*  Event Select */
#define BITM_AGPT1_CON1_EVENT                (_ADI_MSK_3(0x00001F00,0x00001F00U, uint16_t  ))    /*  Event Select Range */
#define BITM_AGPT1_CON1_RLD                  (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Reload Control */
#define BITM_AGPT1_CON1_CLK                  (_ADI_MSK_3(0x00000060,0x00000060U, uint16_t  ))    /*  Clock Select */
#define BITM_AGPT1_CON1_ENABLE               (_ADI_MSK_3(0x00000010,0x00000010U, uint16_t  ))    /*  Timer Enable */
#define BITM_AGPT1_CON1_MOD                  (_ADI_MSK_3(0x00000008,0x00000008U, uint16_t  ))    /*  Timer Mode */
#define BITM_AGPT1_CON1_UP                   (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  Count up */
#define BITM_AGPT1_CON1_PRE                  (_ADI_MSK_3(0x00000003,0x00000003U, uint16_t  ))    /*  Prescaler */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_CLRI1                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_CLRI1_CAP                  1            /*  Clear Captured Event Interrupt */
#define BITP_AGPT1_CLRI1_TMOUT                0            /*  Clear Timeout Interrupt */
#define BITM_AGPT1_CLRI1_CAP                 (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Clear Captured Event Interrupt */
#define BITM_AGPT1_CLRI1_TMOUT               (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Clear Timeout Interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_CAP1                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_CAP1_CAP                   0            /*  16-bit Captured Value. */
#define BITM_AGPT1_CAP1_CAP                  (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  16-bit Captured Value. */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_ALD1                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_ALD1_ALOAD                 0            /*  Load Value, Asynchronous */
#define BITM_AGPT1_ALD1_ALOAD                (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Load Value, Asynchronous */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_AVAL1                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_AVAL1_AVAL                 0            /*  Counter Value */
#define BITM_AGPT1_AVAL1_AVAL                (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  Counter Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_STA1                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_STA1_RSTCNT                8            /*  Counter Reset Occurring */
#define BITP_AGPT1_STA1_PDOK                  7            /*  Clear Interrupt Register Synchronization */
#define BITP_AGPT1_STA1_BUSY                  6            /*  Timer Busy */
#define BITP_AGPT1_STA1_CAP                   1            /*  Capture Event Pending */
#define BITP_AGPT1_STA1_TMOUT                 0            /*  Timeout Event Occurred */
#define BITM_AGPT1_STA1_RSTCNT               (_ADI_MSK_3(0x00000100,0x00000100U, uint16_t  ))    /*  Counter Reset Occurring */
#define BITM_AGPT1_STA1_PDOK                 (_ADI_MSK_3(0x00000080,0x00000080U, uint16_t  ))    /*  Clear Interrupt Register Synchronization */
#define BITM_AGPT1_STA1_BUSY                 (_ADI_MSK_3(0x00000040,0x00000040U, uint16_t  ))    /*  Timer Busy */
#define BITM_AGPT1_STA1_CAP                  (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Capture Event Pending */
#define BITM_AGPT1_STA1_TMOUT                (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Timeout Event Occurred */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_PWMCON1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_PWMCON1_IDLE               1            /*  PWM Idle State. */
#define BITP_AGPT1_PWMCON1_MATCHEN            0            /*  PWM Match Enabled. */
#define BITM_AGPT1_PWMCON1_IDLE              (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  PWM Idle State. */
#define BITM_AGPT1_PWMCON1_MATCHEN           (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  PWM Match Enabled. */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_PWMMAT1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_PWMMAT1_MATCHVAL           0            /*  PWM Match Value */
#define BITM_AGPT1_PWMMAT1_MATCHVAL          (_ADI_MSK_3(0x0000FFFF,0x0000FFFF, int16_t   ))    /*  PWM Match Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AGPT1_INTEN1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AGPT1_INTEN1_INTEN               0            /*  Interrupt Enable */
#define BITM_AGPT1_INTEN1_INTEN              (_ADI_MSK_3(0x00000001,0x00000001U, uint16_t  ))    /*  Interrupt Enable */


/* ============================================================================================================================
        CRC Accelerator
   ============================================================================================================================ */

/* ============================================================================================================================
        AFECRC
   ============================================================================================================================ */
#define REG_AFECRC_CTL                       0x400C1000            /*  AFECRC CRC Control Register */
#define REG_AFECRC_IPDATA                    0x400C1004            /*  AFECRC Data Input. */
#define REG_AFECRC_RESULT                    0x400C1008            /*  AFECRC CRC Residue */
#define REG_AFECRC_POLY                      0x400C100C            /*  AFECRC CRC Reduction Polynomial */
#define REG_AFECRC_IPBITS                    0x400C1010            /*  AFECRC Input Data Bits */
#define REG_AFECRC_IPBYTE                    0x400C1014            /*  AFECRC Input Data Byte */
#define REG_AFECRC_CRC_SIG_COMP              0x400C1020            /*  AFECRC CRC Signature Compare Data Input. */
#define REG_AFECRC_CRCINTEN                  0x400C1024            /*  AFECRC CRC Error Interrupt Enable Bit */
#define REG_AFECRC_INTSTA                    0x400C1028            /*  AFECRC CRC Error Interrupt Status Bit */

/* ============================================================================================================================
        AFECRC Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_CTL                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_CTL_REVID                28            /*  Revision ID */
#define BITP_AFECRC_CTL_MON_EN                9            /*  Enable Apb32/Apb16 to Get Address/Data for CRC Calculation */
#define BITP_AFECRC_CTL_W16SWP                4            /*  Word16 Swap Enabled. */
#define BITP_AFECRC_CTL_BYTMIRR               3            /*  Byte Mirroring. */
#define BITP_AFECRC_CTL_BITMIRR               2            /*  Bit Mirroring. */
#define BITP_AFECRC_CTL_LSBFIRST              1            /*  LSB First Calculation Order */
#define BITP_AFECRC_CTL_EN                    0            /*  CRC Peripheral Enable */
#define BITM_AFECRC_CTL_REVID                (_ADI_MSK_3(0xF0000000,0xF0000000UL, uint32_t  ))    /*  Revision ID */
#define BITM_AFECRC_CTL_MON_EN               (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Enable Apb32/Apb16 to Get Address/Data for CRC Calculation */
#define BITM_AFECRC_CTL_W16SWP               (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Word16 Swap Enabled. */
#define BITM_AFECRC_CTL_BYTMIRR              (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Byte Mirroring. */
#define BITM_AFECRC_CTL_BITMIRR              (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Bit Mirroring. */
#define BITM_AFECRC_CTL_LSBFIRST             (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  LSB First Calculation Order */
#define BITM_AFECRC_CTL_EN                   (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  CRC Peripheral Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_IPDATA                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_IPDATA_VALUE              0            /*  Data Input. */
#define BITM_AFECRC_IPDATA_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  Data Input. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_RESULT                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_RESULT_VALUE              0            /*  CRC Residue */
#define BITM_AFECRC_RESULT_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFF, int32_t   ))    /*  CRC Residue */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_POLY                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_POLY_VALUE                0            /*  CRC Reduction Polynomial */
#define BITM_AFECRC_POLY_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  CRC Reduction Polynomial */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_IPBITS                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_IPBITS_DATA_BITS          0            /*  Input Data Bits. */
#define BITM_AFECRC_IPBITS_DATA_BITS         (_ADI_MSK_3(0x000000FF,0x000000FFU, uint8_t   ))    /*  Input Data Bits. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_IPBYTE                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_IPBYTE_DATA_BYTE          0            /*  Input Data Byte. */
#define BITM_AFECRC_IPBYTE_DATA_BYTE         (_ADI_MSK_3(0x000000FF,0x000000FFU, uint8_t   ))    /*  Input Data Byte. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_CRC_SIG_COMP                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_CRC_SIG_COMP_CRC_SIG      0            /*  CRC Signature Compare Data Input. */
#define BITM_AFECRC_CRC_SIG_COMP_CRC_SIG     (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  CRC Signature Compare Data Input. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_CRCINTEN                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_CRCINTEN_RESERVED_31_1    1            /*  Reserved */
#define BITP_AFECRC_CRCINTEN_CRC_ERR_EN       0            /*  CRC Error Interrupt Enable Bit */
#define BITM_AFECRC_CRCINTEN_RESERVED_31_1   (_ADI_MSK_3(0xFFFFFFFE,0xFFFFFFFEUL, uint32_t  ))    /*  Reserved */
#define BITM_AFECRC_CRCINTEN_CRC_ERR_EN      (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  CRC Error Interrupt Enable Bit */

/* -------------------------------------------------------------------------------------------------------------------------
          AFECRC_INTSTA                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFECRC_INTSTA_CRC_ERR_ST         0            /*  CRC Error Interrupt Status Bit */
#define BITM_AFECRC_INTSTA_CRC_ERR_ST        (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  CRC Error Interrupt Status Bit */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        AFE
   ============================================================================================================================ */
#define REG_AFE_AFECON                       0x400C2000            /*  AFE AFE Configuration */
#define REG_AFE_SWCON                        0x400C200C            /*  AFE Switch Matrix Configuration */
#define REG_AFE_HSDACCON                     0x400C2010            /*  AFE High Speed DAC Configuration */
#define REG_AFE_WGCON                        0x400C2014            /*  AFE Waveform Generator Configuration */
#define REG_AFE_WGFCW                        0x400C2030            /*  AFE Waveform Generator - Sinusoid Frequency Control Word */
#define REG_AFE_WGPHASE                      0x400C2034            /*  AFE Waveform Generator - Sinusoid Phase Offset */
#define REG_AFE_WGOFFSET                     0x400C2038            /*  AFE Waveform Generator - Sinusoid Offset */
#define REG_AFE_WGAMPLITUDE                  0x400C203C            /*  AFE Waveform Generator - Sinusoid Amplitude */
#define REG_AFE_ADCFILTERCON                 0x400C2044            /*  AFE ADC Output Filters Configuration */
#define REG_AFE_HSDACDAT                     0x400C2048            /*  AFE HS DAC Code */
#define REG_AFE_LPREFBUFCON                  0x400C2050            /*  AFE LPREF_BUF_CON */
#define REG_AFE_ADCDAT                       0x400C2074            /*  AFE ADC Raw Result */
#define REG_AFE_DFTREAL                      0x400C2078            /*  AFE DFT Result, Real Part */
#define REG_AFE_DFTIMAG                      0x400C207C            /*  AFE DFT Result, Imaginary Part */
#define REG_AFE_SINC2DAT                     0x400C2080            /*  AFE Supply Rejection Filter Result */
#define REG_AFE_TEMPSENSDAT                  0x400C2084            /*  AFE Temperature Sensor Result */
#define REG_AFE_ADCINTIEN                    0x400C2088            /*  AFE ADC Interrupt Enable Register */
#define REG_AFE_ADCINTSTA                    0x400C2098            /*  AFE ADC Interrupt Status */
#define REG_AFE_AFEGENINTSTA                 0x400C209C            /*  AFE Analog Generation Interrupt */
#define REG_AFE_ADCMIN                       0x400C20A8            /*  AFE ADC Minimum Value Check */
#define REG_AFE_ADCMINSM                     0x400C20AC            /*  AFE ADCMIN Hysteresis Value */
#define REG_AFE_ADCMAX                       0x400C20B0            /*  AFE ADC Maximum Value Check */
#define REG_AFE_ADCMAXSMEN                   0x400C20B4            /*  AFE ADCMAX Hysteresis Value */
#define REG_AFE_ADCDELTA                     0x400C20B8            /*  AFE ADC Delta Value */
#define REG_AFE_HPOSCCON                     0x400C20BC            /*  AFE HPOSC Configuration */
#define REG_AFE_DFTCON                       0x400C20D0            /*  AFE AFE DSP Configuration */
#define REG_AFE_LPTIASW1                     0x400C20E0            /*  AFE ULPTIA Switch Configuration for Channel 1 */
#define REG_AFE_LPTIASW0                     0x400C20E4            /*  AFE ULPTIA Switch Configuration for Channel 0 */
#define REG_AFE_LPTIACON1                    0x400C20E8            /*  AFE ULPTIA Control Bits Channel 1 */
#define REG_AFE_LPTIACON0                    0x400C20EC            /*  AFE ULPTIA Control Bits Channel 0 */
#define REG_AFE_HSRTIACON                    0x400C20F0            /*  AFE High Power RTIA Configuration */
#define REG_AFE_DE1RESCON                    0x400C20F4            /*  AFE DE1 HSTIA Resistors Configuration */
#define REG_AFE_DE0RESCON                    0x400C20F8            /*  AFE DE0 HSTIA Resistors Configuration */
#define REG_AFE_HSTIACON                     0x400C20FC            /*  AFE HSTIA Amplifier Configuration */
#define REG_AFE_DACDCBUFCON                  0x400C2104            /*  AFE DAC DC Buffer Configuration */
#define REG_AFE_LPDACDAT0                    0x400C2120            /*  AFE LPDAC Data-out */
#define REG_AFE_LPDACSW0                     0x400C2124            /*  AFE LPDAC0 Switch Control */
#define REG_AFE_LPDACCON0                    0x400C2128            /*  AFE LPDAC Control Bits */
#define REG_AFE_LPDACDAT1                    0x400C212C            /*  AFE Low Power DAC1 data register */
#define REG_AFE_LPDACSW1                     0x400C2130            /*  AFE Control register for switches to LPDAC1 */
#define REG_AFE_LPDACCON1                    0x400C2134            /*  AFE ULP_DACCON1 */
#define REG_AFE_DSWFULLCON                   0x400C2150            /*  AFE Switch Matrix Full Configuration (D) */
#define REG_AFE_NSWFULLCON                   0x400C2154            /*  AFE Switch Matrix Full Configuration (N) */
#define REG_AFE_PSWFULLCON                   0x400C2158            /*  AFE Switch Matrix Full Configuration (P) */
#define REG_AFE_TSWFULLCON                   0x400C215C            /*  AFE Switch Matrix Full Configuration (T) */
#define REG_AFE_TEMPCON0                     0x400C2174            /*  AFE Temp Sensor Configuration */
#define REG_AFE_BUFSENCON                    0x400C2180            /*  AFE HP and LP Buffer Control */
#define REG_AFE_ADCCON                       0x400C21A8            /*  AFE ADC Configuration */
#define REG_AFE_DSWSTA                       0x400C21B0            /*  AFE Switch Matrix Status (D) */
#define REG_AFE_PSWSTA                       0x400C21B4            /*  AFE Switch Matrix Status (P) */
#define REG_AFE_NSWSTA                       0x400C21B8            /*  AFE Switch Matrix Status (N) */
#define REG_AFE_TSWSTA                       0x400C21BC            /*  AFE Switch Matrix Status (T) */
#define REG_AFE_STATSVAR                     0x400C21C0            /*  AFE Variance Output */
#define REG_AFE_STATSCON                     0x400C21C4            /*  AFE Statistics Control */
#define REG_AFE_STATSMEAN                    0x400C21C8            /*  AFE Statistics Mean Output */
#define REG_AFE_REPEATADCCNV                 0x400C21F0            /*  AFE REPEAT ADC Conversions */
#define REG_AFE_CALDATLOCK                   0x400C2230            /*  AFE Calibration Data Lock */
#define REG_AFE_ADCOFFSETHSTIA               0x400C2234            /*  AFE ADC Offset Calibration High Speed TIA Channel */
#define REG_AFE_ADCGAINTEMPSENS0             0x400C2238            /*  AFE ADC Gain Calibration Temp Sensor Channel */
#define REG_AFE_ADCOFFSETTEMPSENS0           0x400C223C            /*  AFE ADC Offset Calibration Temp Sensor Channel 0 */
#define REG_AFE_ADCGAINGN1                   0x400C2240            /*  AFE ADCPGAGN1: ADC Gain Calibration Auxiliary Input Channel */
#define REG_AFE_ADCOFFSETGN1                 0x400C2244            /*  AFE ADC Offset Calibration Auxiliary Channel (PGA Gain=1) */
#define REG_AFE_DACGAIN                      0x400C2260            /*  AFE DACGAIN */
#define REG_AFE_DACOFFSETATTEN               0x400C2264            /*  AFE DAC Offset with Attenuator Enabled (LP Mode) */
#define REG_AFE_DACOFFSET                    0x400C2268            /*  AFE DAC Offset with Attenuator Disabled (LP Mode) */
#define REG_AFE_ADCGAINGN1P5                 0x400C2270            /*  AFE ADC Gain Calibration Auxiliary Input Channel (PGA Gain=1.5) */
#define REG_AFE_ADCGAINGN2                   0x400C2274            /*  AFE ADC Gain Calibration Auxiliary Input Channel (PGA Gain=2) */
#define REG_AFE_ADCGAINGN4                   0x400C2278            /*  AFE ADC Gain Calibration Auxiliary Input Channel (PGA Gain=4) */
#define REG_AFE_ADCPGAOFFSETCANCEL           0x400C2280            /*  AFE ADC Offset Cancellation (Optional) */
#define REG_AFE_ADCGNHSTIA                   0x400C2284            /*  AFE ADC Gain Calibration for HS TIA Channel */
#define REG_AFE_ADCOFFSETLPTIA0              0x400C2288            /*  AFE ADC Offset Calibration ULP-TIA0 Channel */
#define REG_AFE_ADCGNLPTIA0                  0x400C228C            /*  AFE ADC GAIN Calibration for LP TIA0 Channel */
#define REG_AFE_ADCPGAGN4OFCAL               0x400C2294            /*  AFE ADC Gain Calibration with DC Cancellation(PGA G=4) */
#define REG_AFE_ADCGAINGN9                   0x400C2298            /*  AFE ADC Gain Calibration Auxiliary Input Channel (PGA Gain=9) */
#define REG_AFE_ADCOFFSETEMPSENS1            0x400C22A8            /*  AFE ADC Offset Calibration  Temp Sensor Channel 1 */
#define REG_AFE_ADCGAINTEMPSENS1             0x400C22AC            /*  AFE ADC Gain Calibration Temperature Sensor Channel */
#define REG_AFE_DACOFFSETATTENHP             0x400C22B8            /*  AFE DAC Offset with Attenuator Enabled (HP Mode) */
#define REG_AFE_DACOFFSETHP                  0x400C22BC            /*  AFE DAC Offset with Attenuator Disabled (HP Mode) */
#define REG_AFE_ADCOFFSETLPTIA1              0x400C22C0            /*  AFE ADC Offset Calibration LP TIA1 Channel */
#define REG_AFE_ADCGNLPTIA1                  0x400C22C4            /*  AFE ADC GAIN Calibration for LP TIA1 Channel */
#define REG_AFE_ADCOFFSETGN2                 0x400C22C8            /*  AFE Offset Calibration Auxiliary Channel (PGA Gain =2) */
#define REG_AFE_ADCOFFSETGN1P5               0x400C22CC            /*  AFE Offset Calibration Auxiliary Channel (PGA Gain =1.5) */
#define REG_AFE_ADCOFFSETGN9                 0x400C22D0            /*  AFE Offset Calibration Auxiliary Channel (PGA Gain =9) */
#define REG_AFE_ADCOFFSETGN4                 0x400C22D4            /*  AFE Offset Calibration Auxiliary Channel (PGA Gain =4) */
#define REG_AFE_PMBW                         0x400C22F0            /*  AFE Power Mode Configuration */
#define REG_AFE_SWMUX                        0x400C235C            /*  AFE Switch Mux for ECG */
#define REG_AFE_TEMPCON1                     0x400C2374            /*  AFE AFE_TEMPSEN_DIO */
#define REG_AFE_TESTDAC                      0x400C2388            /*  AFE DAC Test */
#define REG_AFE_ADCBUFCON                    0x400C238C            /*  AFE Configure ADC Input Buffer */

/* ============================================================================================================================
        AFE Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AFE_AFECON                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_AFECON_DACBUFEN             21            /*  Enable DC DAC Buffer */
#define BITP_AFE_AFECON_DACREFEN             20            /*  High Speed DAC Reference Enable */
#define BITP_AFE_AFECON_ALDOILIMITEN         19            /*  Analog LDO Current Limiting Enable */
#define BITP_AFE_AFECON_SINC2EN              16            /*  ADC Output 50/60Hz Filter Enable */
#define BITP_AFE_AFECON_DFTEN                15            /*  DFT Hardware Accelerator Enable */
#define BITP_AFE_AFECON_WAVEGENEN            14            /*  Waveform Generator Enable */
#define BITP_AFE_AFECON_TEMPCONVEN           13            /*  ADC Temp Sensor Convert Enable */
#define BITP_AFE_AFECON_TEMPSENSEN0          12            /*  ADC Temperature Sensor Channel Enable */
#define BITP_AFE_AFECON_TIAEN                11            /*  High Power TIA Enable */
#define BITP_AFE_AFECON_INAMPEN              10            /*  Enable Excitation Amplifier */
#define BITP_AFE_AFECON_EXBUFEN               9            /*  Enable Excitation Buffer */
#define BITP_AFE_AFECON_ADCCONVEN             8            /*  ADC Conversion Start Enable */
#define BITP_AFE_AFECON_ADCEN                 7            /*  ADC Power Enable */
#define BITP_AFE_AFECON_DACEN                 6            /*  High Power DAC Enable */
#define BITP_AFE_AFECON_HPREFDIS              5            /*  Disable High Power Reference */
#define BITM_AFE_AFECON_DACBUFEN             (_ADI_MSK_3(0x00200000,0x00200000UL, uint32_t  ))    /*  Enable DC DAC Buffer */
#define BITM_AFE_AFECON_DACREFEN             (_ADI_MSK_3(0x00100000,0x00100000UL, uint32_t  ))    /*  High Speed DAC Reference Enable */
#define BITM_AFE_AFECON_ALDOILIMITEN         (_ADI_MSK_3(0x00080000,0x00080000UL, uint32_t  ))    /*  Analog LDO Current Limiting Enable */
#define BITM_AFE_AFECON_SINC2EN              (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  ADC Output 50/60Hz Filter Enable */
#define BITM_AFE_AFECON_DFTEN                (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  DFT Hardware Accelerator Enable */
#define BITM_AFE_AFECON_WAVEGENEN            (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  Waveform Generator Enable */
#define BITM_AFE_AFECON_TEMPCONVEN           (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  ADC Temp Sensor Convert Enable */
#define BITM_AFE_AFECON_TEMPSENSEN0          (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  ADC Temperature Sensor Channel Enable */
#define BITM_AFE_AFECON_TIAEN                (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  High Power TIA Enable */
#define BITM_AFE_AFECON_INAMPEN              (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Enable Excitation Amplifier */
#define BITM_AFE_AFECON_EXBUFEN              (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Enable Excitation Buffer */
#define BITM_AFE_AFECON_ADCCONVEN            (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  ADC Conversion Start Enable */
#define BITM_AFE_AFECON_ADCEN                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  ADC Power Enable */
#define BITM_AFE_AFECON_DACEN                (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  High Power DAC Enable */
#define BITM_AFE_AFECON_HPREFDIS             (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Disable High Power Reference */
#define ENUM_AFE_AFECON_OFF                  (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  DACEN: High Power DAC Disabled */
#define ENUM_AFE_AFECON_ON                   (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  DACEN: High Power DAC Enabled */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_SWCON                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_SWCON_T11CON                19            /*  Control of T[11] */
#define BITP_AFE_SWCON_T10CON                18            /*  Control of T[10] */
#define BITP_AFE_SWCON_T9CON                 17            /*  Control of T[9] */
#define BITP_AFE_SWCON_SWSOURCESEL           16            /*  Switch Control Select */
#define BITP_AFE_SWCON_TMUXCON               12            /*  Control of T Switch MUX. */
#define BITP_AFE_SWCON_NMUXCON                8            /*  Control of N Switch MUX */
#define BITP_AFE_SWCON_PMUXCON                4            /*  Control of P Switch MUX */
#define BITP_AFE_SWCON_DMUXCON                0            /*  Control of D Switch MUX */
#define BITM_AFE_SWCON_T11CON                (_ADI_MSK_3(0x00080000,0x00080000UL, uint32_t  ))    /*  Control of T[11] */
#define BITM_AFE_SWCON_T10CON                (_ADI_MSK_3(0x00040000,0x00040000UL, uint32_t  ))    /*  Control of T[10] */
#define BITM_AFE_SWCON_T9CON                 (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))    /*  Control of T[9] */
#define BITM_AFE_SWCON_SWSOURCESEL           (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  Switch Control Select */
#define BITM_AFE_SWCON_TMUXCON               (_ADI_MSK_3(0x0000F000,0x0000F000UL, uint32_t  ))    /*  Control of T Switch MUX. */
#define BITM_AFE_SWCON_NMUXCON               (_ADI_MSK_3(0x00000F00,0x00000F00UL, uint32_t  ))    /*  Control of N Switch MUX */
#define BITM_AFE_SWCON_PMUXCON               (_ADI_MSK_3(0x000000F0,0x000000F0UL, uint32_t  ))    /*  Control of P Switch MUX */
#define BITM_AFE_SWCON_DMUXCON               (_ADI_MSK_3(0x0000000F,0x0000000FUL, uint32_t  ))    /*  Control of D Switch MUX */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_HSDACCON                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_HSDACCON_INAMPGNMDE         12            /*  Excitation Amplifier Gain Control */
#define BITP_AFE_HSDACCON_RATE                1            /*  DAC Update Rate */
#define BITP_AFE_HSDACCON_ATTENEN             0            /*  PGA Stage Gain Attenuation */
#define BITM_AFE_HSDACCON_INAMPGNMDE         (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  Excitation Amplifier Gain Control */
#define BITM_AFE_HSDACCON_RATE               (_ADI_MSK_3(0x000001FE,0x000001FEUL, uint32_t  ))    /*  DAC Update Rate */
#define BITM_AFE_HSDACCON_ATTENEN            (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  PGA Stage Gain Attenuation */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_WGCON                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_WGCON_DACGAINCAL             5            /*  Bypass DAC Gain */
#define BITP_AFE_WGCON_DACOFFSETCAL           4            /*  Bypass DAC Offset */
#define BITP_AFE_WGCON_TYPESEL                1            /*  Selects the Type of Waveform */
#define BITM_AFE_WGCON_DACGAINCAL            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Bypass DAC Gain */
#define BITM_AFE_WGCON_DACOFFSETCAL          (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Bypass DAC Offset */
#define BITM_AFE_WGCON_TYPESEL               (_ADI_MSK_3(0x00000006,0x00000006UL, uint32_t  ))    /*  Selects the Type of Waveform */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_WGFCW                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_WGFCW_SINEFCW                0            /*  Sinusoid Generator Frequency Control Word */
#define BITM_AFE_WGFCW_SINEFCW               (_ADI_MSK_3(0x00FFFFFF,0x00FFFFFFUL, uint32_t  ))    /*  Sinusoid Generator Frequency Control Word */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_WGPHASE                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_WGPHASE_SINEOFFSET           0            /*  Sinusoid Phase Offset */
#define BITM_AFE_WGPHASE_SINEOFFSET          (_ADI_MSK_3(0x000FFFFF,0x000FFFFFUL, uint32_t  ))    /*  Sinusoid Phase Offset */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_WGOFFSET                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_WGOFFSET_SINEOFFSET          0            /*  Sinusoid Offset */
#define BITM_AFE_WGOFFSET_SINEOFFSET         (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  Sinusoid Offset */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_WGAMPLITUDE                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_WGAMPLITUDE_SINEAMPLITUDE    0            /*  Sinusoid Amplitude */
#define BITM_AFE_WGAMPLITUDE_SINEAMPLITUDE   (_ADI_MSK_3(0x000007FF,0x000007FFUL, uint32_t  ))    /*  Sinusoid Amplitude */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCFILTERCON                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCFILTERCON_DFTCLKENB      18            /*  DFT Clock Enable */
#define BITP_AFE_ADCFILTERCON_DACWAVECLKENB  17            /*  DAC Wave Clock Enable */
#define BITP_AFE_ADCFILTERCON_SINC2CLKENB    16            /*  SINC2 Filter Clock Enable */
#define BITP_AFE_ADCFILTERCON_AVRGNUM        14            /*  Number of Samples Averaged */
#define BITP_AFE_ADCFILTERCON_SINC3OSR       12            /*  SINC3 OSR */
#define BITP_AFE_ADCFILTERCON_SINC2OSR        8            /*  SINC2 OSR */
#define BITP_AFE_ADCFILTERCON_AVRGEN          7            /*  Average Function Enable */
#define BITP_AFE_ADCFILTERCON_SINC3BYP        6            /*  SINC3 Filter Bypass */
#define BITP_AFE_ADCFILTERCON_LPFBYPEN        4            /*  50/60Hz Low Pass Filter */
#define BITP_AFE_ADCFILTERCON_ADCCLK          0            /*  ADC Data Rate */
#define BITM_AFE_ADCFILTERCON_DFTCLKENB      (_ADI_MSK_3(0x00040000,0x00040000UL, uint32_t  ))    /*  DFT Clock Enable */
#define BITM_AFE_ADCFILTERCON_DACWAVECLKENB  (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))    /*  DAC Wave Clock Enable */
#define BITM_AFE_ADCFILTERCON_SINC2CLKENB    (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  SINC2 Filter Clock Enable */
#define BITM_AFE_ADCFILTERCON_AVRGNUM        (_ADI_MSK_3(0x0000C000,0x0000C000UL, uint32_t  ))    /*  Number of Samples Averaged */
#define BITM_AFE_ADCFILTERCON_SINC3OSR       (_ADI_MSK_3(0x00003000,0x00003000UL, uint32_t  ))    /*  SINC3 OSR */
#define BITM_AFE_ADCFILTERCON_SINC2OSR       (_ADI_MSK_3(0x00000F00,0x00000F00UL, uint32_t  ))    /*  SINC2 OSR */
#define BITM_AFE_ADCFILTERCON_AVRGEN         (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Average Function Enable */
#define BITM_AFE_ADCFILTERCON_SINC3BYP       (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  SINC3 Filter Bypass */
#define BITM_AFE_ADCFILTERCON_LPFBYPEN       (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  50/60Hz Low Pass Filter */
#define BITM_AFE_ADCFILTERCON_ADCCLK         (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  ADC Data Rate */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_HSDACDAT                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_HSDACDAT_DACDAT              0            /*  DAC Code */
#define BITM_AFE_HSDACDAT_DACDAT             (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  DAC Code */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPREFBUFCON                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPREFBUFCON_BOOSTCURRENT     2            /*  Set: Drive 2 Dac ;Unset Drive 1 Dac, and Save Power */
#define BITP_AFE_LPREFBUFCON_LPBUF2P5DIS      1            /*  Low Power Bandgap's Output Buffer */
#define BITP_AFE_LPREFBUFCON_LPREFDIS         0            /*  Set This Bit Will Power Down Low Power Bandgap */
#define BITM_AFE_LPREFBUFCON_BOOSTCURRENT    (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Set: Drive 2 Dac ;Unset Drive 1 Dac, and Save Power */
#define BITM_AFE_LPREFBUFCON_LPBUF2P5DIS     (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Low Power Bandgap's Output Buffer */
#define BITM_AFE_LPREFBUFCON_LPREFDIS        (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Set This Bit Will Power Down Low Power Bandgap */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCDAT                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCDAT_DATA                  0            /*  ADC Result */
#define BITM_AFE_ADCDAT_DATA                 (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  ADC Result */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DFTREAL                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DFTREAL_DATA                 0            /*  DFT Real */
#define BITM_AFE_DFTREAL_DATA                (_ADI_MSK_3(0x0003FFFF,0x0003FFFFUL, uint32_t  ))    /*  DFT Real */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DFTIMAG                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DFTIMAG_DATA                 0            /*  DFT Imaginary */
#define BITM_AFE_DFTIMAG_DATA                (_ADI_MSK_3(0x0003FFFF,0x0003FFFFUL, uint32_t  ))    /*  DFT Imaginary */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_SINC2DAT                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_SINC2DAT_DATA                0            /*  LPF Result */
#define BITM_AFE_SINC2DAT_DATA               (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  LPF Result */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_TEMPSENSDAT                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_TEMPSENSDAT_DATA             0            /*  Temp Sensor */
#define BITM_AFE_TEMPSENSDAT_DATA            (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  Temp Sensor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCINTIEN                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCINTIEN_VARIEN             8            /*  Variance Interrupt */
#define BITP_AFE_ADCINTIEN_MEANIEN            7            /*  Mean Interrupt */
#define BITP_AFE_ADCINTIEN_ADCDELTAFAILIEN    6            /*  Delta Interrupt */
#define BITP_AFE_ADCINTIEN_ADCMAXFAILIEN      5            /*  ADCMAX Interrupt */
#define BITP_AFE_ADCINTIEN_ADCMINFAILIEN      4            /*  ADCMIN Interrupt */
#define BITP_AFE_ADCINTIEN_TEMPRDYIEN         3            /*  Temp Sensor Interrupt */
#define BITP_AFE_ADCINTIEN_SINC2RDYIEN        2            /*  Low Pass Filter Result Interrupt */
#define BITP_AFE_ADCINTIEN_DFTRDYIEN          1            /*  DFT Result Ready Interrupt */
#define BITP_AFE_ADCINTIEN_ADCRDYIEN          0            /*  ADCDAT Ready Interrupt */
#define BITM_AFE_ADCINTIEN_VARIEN            (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Variance Interrupt */
#define BITM_AFE_ADCINTIEN_MEANIEN           (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Mean Interrupt */
#define BITM_AFE_ADCINTIEN_ADCDELTAFAILIEN   (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Delta Interrupt */
#define BITM_AFE_ADCINTIEN_ADCMAXFAILIEN     (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  ADCMAX Interrupt */
#define BITM_AFE_ADCINTIEN_ADCMINFAILIEN     (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  ADCMIN Interrupt */
#define BITM_AFE_ADCINTIEN_TEMPRDYIEN        (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Temp Sensor Interrupt */
#define BITM_AFE_ADCINTIEN_SINC2RDYIEN       (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Low Pass Filter Result Interrupt */
#define BITM_AFE_ADCINTIEN_DFTRDYIEN         (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  DFT Result Ready Interrupt */
#define BITM_AFE_ADCINTIEN_ADCRDYIEN         (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  ADCDAT Ready Interrupt */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCINTSTA                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCINTSTA_VARRDY             8            /*  Variance Result Ready */
#define BITP_AFE_ADCINTSTA_MEANRDY            7            /*  Mean Result Ready */
#define BITP_AFE_ADCINTSTA_ADCDIFFERR         6            /*  ADC Delta Ready */
#define BITP_AFE_ADCINTSTA_ADCMAXERR          5            /*  ADC Maximum Value */
#define BITP_AFE_ADCINTSTA_ADCMINERR          4            /*  ADC Minimum Value */
#define BITP_AFE_ADCINTSTA_TEMPRDY            3            /*  Temp Sensor Result Ready */
#define BITP_AFE_ADCINTSTA_SINC2RDY           2            /*  Low Pass Filter Result Status */
#define BITP_AFE_ADCINTSTA_DFTRDY             1            /*  DFT Result Ready Status */
#define BITP_AFE_ADCINTSTA_ADCRDY             0            /*  ADC Result Ready Status */
#define BITM_AFE_ADCINTSTA_VARRDY            (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Variance Result Ready */
#define BITM_AFE_ADCINTSTA_MEANRDY           (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Mean Result Ready */
#define BITM_AFE_ADCINTSTA_ADCDIFFERR        (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  ADC Delta Ready */
#define BITM_AFE_ADCINTSTA_ADCMAXERR         (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  ADC Maximum Value */
#define BITM_AFE_ADCINTSTA_ADCMINERR         (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  ADC Minimum Value */
#define BITM_AFE_ADCINTSTA_TEMPRDY           (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Temp Sensor Result Ready */
#define BITM_AFE_ADCINTSTA_SINC2RDY          (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Low Pass Filter Result Status */
#define BITM_AFE_ADCINTSTA_DFTRDY            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  DFT Result Ready Status */
#define BITM_AFE_ADCINTSTA_ADCRDY            (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  ADC Result Ready Status */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_AFEGENINTSTA                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_AFEGENINTSTA_CUSTOMIRQ3      3            /*  Custom IRQ 3. */
#define BITP_AFE_AFEGENINTSTA_CUSTOMIRQ2      2            /*  Custom IRQ 2 */
#define BITP_AFE_AFEGENINTSTA_CUSTOMIRQ1      1            /*  Custom IRQ 1. */
#define BITP_AFE_AFEGENINTSTA_CUSTOMIRQ0      0            /*  Custom IRQ 0 */
#define BITM_AFE_AFEGENINTSTA_CUSTOMIRQ3     (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Custom IRQ 3. */
#define BITM_AFE_AFEGENINTSTA_CUSTOMIRQ2     (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Custom IRQ 2 */
#define BITM_AFE_AFEGENINTSTA_CUSTOMIRQ1     (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Custom IRQ 1. */
#define BITM_AFE_AFEGENINTSTA_CUSTOMIRQ0     (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Custom IRQ 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCMIN                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCMIN_MINVAL                0            /*  ADC Minimum Value Threshold */
#define BITM_AFE_ADCMIN_MINVAL               (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  ADC Minimum Value Threshold */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCMINSM                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCMINSM_MINCLRVAL           0            /*  ADCMIN Hysteresis Value */
#define BITM_AFE_ADCMINSM_MINCLRVAL          (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  ADCMIN Hysteresis Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCMAX                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCMAX_MAXVAL                0            /*  ADC Max Threshold */
#define BITM_AFE_ADCMAX_MAXVAL               (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  ADC Max Threshold */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCMAXSMEN                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCMAXSMEN_MAXSWEN           0            /*  ADCMAX Hysteresis Value */
#define BITM_AFE_ADCMAXSMEN_MAXSWEN          (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  ADCMAX Hysteresis Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCDELTA                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCDELTA_DELTAVAL            0            /*  ADCDAT Code Differences Limit Option */
#define BITM_AFE_ADCDELTA_DELTAVAL           (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  ADCDAT Code Differences Limit Option */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_HPOSCCON                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_HPOSCCON_CLK32MHZEN          2            /*  16M/32M Output Selector Signal. */
#define BITM_AFE_HPOSCCON_CLK32MHZEN         (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  16M/32M Output Selector Signal. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DFTCON                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DFTCON_DFTINSEL             20            /*  DFT Input Select */
#define BITP_AFE_DFTCON_DFTNUM                4            /*  ADC Samples Used */
#define BITP_AFE_DFTCON_HANNINGEN             0            /*  Hanning Window Enable */
#define BITM_AFE_DFTCON_DFTINSEL             (_ADI_MSK_3(0x00300000,0x00300000UL, uint32_t  ))    /*  DFT Input Select */
#define BITM_AFE_DFTCON_DFTNUM               (_ADI_MSK_3(0x000000F0,0x000000F0UL, uint32_t  ))    /*  ADC Samples Used */
#define BITM_AFE_DFTCON_HANNINGEN            (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Hanning Window Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPTIASW1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPTIASW1_TIABIASSEL         13            /*  TIA SW13 Control. Active High */
#define BITP_AFE_LPTIASW1_PABIASSEL          12            /*  TIA SW12 Control. Active High */
#define BITP_AFE_LPTIASW1_TIASWCON            0            /*  TIA SW[11:0] Control */
#define BITM_AFE_LPTIASW1_TIABIASSEL         (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  TIA SW13 Control. Active High */
#define BITM_AFE_LPTIASW1_PABIASSEL          (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  TIA SW12 Control. Active High */
#define BITM_AFE_LPTIASW1_TIASWCON           (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  TIA SW[11:0] Control */
#define ENUM_AFE_LPTIASW1_CAPA_LP            (_ADI_MSK_3(0x00000014,0x00000014UL, uint32_t  ))    /*  TIASWCON: CAPA test with LP TIA */
#define ENUM_AFE_LPTIASW1_NORM               (_ADI_MSK_3(0x0000002C,0x0000002CUL, uint32_t  ))    /*  TIASWCON: Normal work mode */
#define ENUM_AFE_LPTIASW1_DIO                (_ADI_MSK_3(0x0000002D,0x0000002DUL, uint32_t  ))    /*  TIASWCON: Normal work mode with back-back diode enabled. */
#define ENUM_AFE_LPTIASW1_SHORTSW            (_ADI_MSK_3(0x0000002E,0x0000002EUL, uint32_t  ))    /*  TIASWCON: Work mode with short switch protection */
#define ENUM_AFE_LPTIASW1_LOWNOISE           (_ADI_MSK_3(0x0000006C,0x0000006CUL, uint32_t  ))    /*  TIASWCON: Work mode, vzero-vbias=0. */
#define ENUM_AFE_LPTIASW1_CAPA_RAMP_H        (_ADI_MSK_3(0x00000094,0x00000094UL, uint32_t  ))    /*  TIASWCON: CAPA test or Ramp test with HP TIA */
#define ENUM_AFE_LPTIASW1_BUFDIS             (_ADI_MSK_3(0x00000180,0x00000180UL, uint32_t  ))    /*  TIASWCON: Set PA/TIA as unity gain buffer. */
#define ENUM_AFE_LPTIASW1_BUFEN              (_ADI_MSK_3(0x000001A4,0x000001A4UL, uint32_t  ))    /*  TIASWCON: Set PA/TIA as unity gain buffer. Connect amp's output to CE1 & RC11. */
#define ENUM_AFE_LPTIASW1_TWOLEAD            (_ADI_MSK_3(0x0000042C,0x0000042CUL, uint32_t  ))    /*  TIASWCON: Two lead sensor, set PA as unity gain buffer. */
#define ENUM_AFE_LPTIASW1_BUFEN2             (_ADI_MSK_3(0x000004A4,0x000004A4UL, uint32_t  ))    /*  TIASWCON: Set PA/TIA as unity gain buffer. */
#define ENUM_AFE_LPTIASW1_SESHORTRE          (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  TIASWCON: Close SW11 - Short SE1 to RE1, */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPTIASW0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPTIASW0_RECAL              15            /*  TIA SW15 Control. Active High */
#define BITP_AFE_LPTIASW0_VZEROSHARE         14            /*  TIA SW14 Control. Active High */
#define BITP_AFE_LPTIASW0_TIABIASSEL         13            /*  TIA SW13 Control. Active High */
#define BITP_AFE_LPTIASW0_PABIASSEL          12            /*  TIA SW12 Control. Active High */
#define BITP_AFE_LPTIASW0_TIASWCON            0            /*  TIA SW[11:0] Control */
#define BITM_AFE_LPTIASW0_RECAL              (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  TIA SW15 Control. Active High */
#define BITM_AFE_LPTIASW0_VZEROSHARE         (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  TIA SW14 Control. Active High */
#define BITM_AFE_LPTIASW0_TIABIASSEL         (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  TIA SW13 Control. Active High */
#define BITM_AFE_LPTIASW0_PABIASSEL          (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  TIA SW12 Control. Active High */
#define BITM_AFE_LPTIASW0_TIASWCON           (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  TIA SW[11:0] Control */
#define ENUM_AFE_LPTIASW0_11                 (_ADI_MSK_3(0x00000014,0x00000014UL, uint32_t  ))    /*  TIASWCON: CAPA test with LP TIA */
#define ENUM_AFE_LPTIASW0_NORM               (_ADI_MSK_3(0x0000002C,0x0000002CUL, uint32_t  ))    /*  TIASWCON: Normal work mode */
#define ENUM_AFE_LPTIASW0_DIO                (_ADI_MSK_3(0x0000002D,0x0000002DUL, uint32_t  ))    /*  TIASWCON: Normal work mode with back-back diode enabled. */
#define ENUM_AFE_LPTIASW0_SHORTSW            (_ADI_MSK_3(0x0000002E,0x0000002EUL, uint32_t  ))    /*  TIASWCON: Work mode with short switch protection */
#define ENUM_AFE_LPTIASW0_LOWNOISE           (_ADI_MSK_3(0x0000006C,0x0000006CUL, uint32_t  ))    /*  TIASWCON: Work mode, vzero-vbias=0. */
#define ENUM_AFE_LPTIASW0_1                  (_ADI_MSK_3(0x00000094,0x00000094UL, uint32_t  ))    /*  TIASWCON: CAPA test or Ramp test with HP TIA */
#define ENUM_AFE_LPTIASW0_BUFDIS             (_ADI_MSK_3(0x00000180,0x00000180UL, uint32_t  ))    /*  TIASWCON: Set PA/TIA as unity gain buffer. */
#define ENUM_AFE_LPTIASW0_BUFEN              (_ADI_MSK_3(0x000001A4,0x000001A4UL, uint32_t  ))    /*  TIASWCON: Set PA/TIA as unity gain buffer. Connect amp's output to CE0 & RC01. */
#define ENUM_AFE_LPTIASW0_TWOLEAD            (_ADI_MSK_3(0x0000042C,0x0000042CUL, uint32_t  ))    /*  TIASWCON: Two lead sensor, set PA as unity gain buffer. */
#define ENUM_AFE_LPTIASW0_BUFEN2             (_ADI_MSK_3(0x000004A4,0x000004A4UL, uint32_t  ))    /*  TIASWCON: Set PA/TIA as unity gain buffer. */
#define ENUM_AFE_LPTIASW0_SESHORTRE          (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  TIASWCON: Close SW11 - Short SE0 to RE0. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPTIACON1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPTIACON1_CHOPEN            16            /*  Chopping Enable */
#define BITP_AFE_LPTIACON1_TIARF             13            /*  Set LPF Resistor */
#define BITP_AFE_LPTIACON1_TIARL             10            /*  Set RLOAD */
#define BITP_AFE_LPTIACON1_TIAGAIN            5            /*  Set RTIA Gain Resistor */
#define BITP_AFE_LPTIACON1_IBOOST             3            /*  Current Boost Control */
#define BITP_AFE_LPTIACON1_HALFPWR            2            /*  Half Power Mode Select */
#define BITP_AFE_LPTIACON1_PAPDEN             1            /*  PA Power Down */
#define BITP_AFE_LPTIACON1_TIAPDEN            0            /*  TIA Power Down */
#define BITM_AFE_LPTIACON1_CHOPEN            (_ADI_MSK_3(0x00030000,0x00030000UL, uint32_t  ))    /*  Chopping Enable */
#define BITM_AFE_LPTIACON1_TIARF             (_ADI_MSK_3(0x0000E000,0x0000E000UL, uint32_t  ))    /*  Set LPF Resistor */
#define BITM_AFE_LPTIACON1_TIARL             (_ADI_MSK_3(0x00001C00,0x00001C00UL, uint32_t  ))    /*  Set RLOAD */
#define BITM_AFE_LPTIACON1_TIAGAIN           (_ADI_MSK_3(0x000003E0,0x000003E0UL, uint32_t  ))    /*  Set RTIA Gain Resistor */
#define BITM_AFE_LPTIACON1_IBOOST            (_ADI_MSK_3(0x00000018,0x00000018UL, uint32_t  ))    /*  Current Boost Control */
#define BITM_AFE_LPTIACON1_HALFPWR           (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Half Power Mode Select */
#define BITM_AFE_LPTIACON1_PAPDEN            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  PA Power Down */
#define BITM_AFE_LPTIACON1_TIAPDEN           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  TIA Power Down */
#define ENUM_AFE_LPTIACON1_DISCONRF          (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  TIARF: Disconnect TIA output from LPF pin */
#define ENUM_AFE_LPTIACON1_BYPRF             (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  TIARF: Bypass resistor */
#define ENUM_AFE_LPTIACON1_RF20K             (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  TIARF: 20k Ohm */
#define ENUM_AFE_LPTIACON1_RF100K            (_ADI_MSK_3(0x00006000,0x00006000UL, uint32_t  ))    /*  TIARF: 100k Ohm */
#define ENUM_AFE_LPTIACON1_RF200K            (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  TIARF: 200k Ohm */
#define ENUM_AFE_LPTIACON1_RF400K            (_ADI_MSK_3(0x0000A000,0x0000A000UL, uint32_t  ))    /*  TIARF: 400k Ohm */
#define ENUM_AFE_LPTIACON1_RF600K            (_ADI_MSK_3(0x0000C000,0x0000C000UL, uint32_t  ))    /*  TIARF: 600k Ohm */
#define ENUM_AFE_LPTIACON1_RF1MOHM           (_ADI_MSK_3(0x0000E000,0x0000E000UL, uint32_t  ))    /*  TIARF: 1Meg Ohm */
#define ENUM_AFE_LPTIACON1_RL0               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  TIARL: 0 ohm */
#define ENUM_AFE_LPTIACON1_RL10              (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  TIARL: 10 ohm */
#define ENUM_AFE_LPTIACON1_RL30              (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  TIARL: 30 ohm */
#define ENUM_AFE_LPTIACON1_RL50              (_ADI_MSK_3(0x00000C00,0x00000C00UL, uint32_t  ))    /*  TIARL: 50 ohm */
#define ENUM_AFE_LPTIACON1_RL100             (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  TIARL: 100 ohm */
#define ENUM_AFE_LPTIACON1_RL1P6K            (_ADI_MSK_3(0x00001400,0x00001400UL, uint32_t  ))    /*  TIARL: 1.6kohm */
#define ENUM_AFE_LPTIACON1_RL3P1K            (_ADI_MSK_3(0x00001800,0x00001800UL, uint32_t  ))    /*  TIARL: 3.1kohm */
#define ENUM_AFE_LPTIACON1_RL3P5K            (_ADI_MSK_3(0x00001C00,0x00001C00UL, uint32_t  ))    /*  TIARL: 3.6kohm */
#define ENUM_AFE_LPTIACON1_DISCONTIA         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  TIAGAIN: Disconnect TIA Gain resistor */
#define ENUM_AFE_LPTIACON1_TIAGAIN200        (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  TIAGAIN: 200 Ohm */
#define ENUM_AFE_LPTIACON1_TIAGAIN1K         (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  TIAGAIN: 1k ohm */
#define ENUM_AFE_LPTIACON1_TIAGAIN2K         (_ADI_MSK_3(0x00000060,0x00000060UL, uint32_t  ))    /*  TIAGAIN: 2k */
#define ENUM_AFE_LPTIACON1_TIAGAIN3K         (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  TIAGAIN: 3k */
#define ENUM_AFE_LPTIACON1_TIAGAIN4K         (_ADI_MSK_3(0x000000A0,0x000000A0UL, uint32_t  ))    /*  TIAGAIN: 4k */
#define ENUM_AFE_LPTIACON1_TIAGAIN6K         (_ADI_MSK_3(0x000000C0,0x000000C0UL, uint32_t  ))    /*  TIAGAIN: 6k */
#define ENUM_AFE_LPTIACON1_TIAGAIN8K         (_ADI_MSK_3(0x000000E0,0x000000E0UL, uint32_t  ))    /*  TIAGAIN: 8k */
#define ENUM_AFE_LPTIACON1_TIAGAIN10K        (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  TIAGAIN: 10k */
#define ENUM_AFE_LPTIACON1_TIAGAIN12K        (_ADI_MSK_3(0x00000120,0x00000120UL, uint32_t  ))    /*  TIAGAIN: 12k */
#define ENUM_AFE_LPTIACON1_TIAGAIN16K        (_ADI_MSK_3(0x00000140,0x00000140UL, uint32_t  ))    /*  TIAGAIN: 16k */
#define ENUM_AFE_LPTIACON1_TIAGAIN20K        (_ADI_MSK_3(0x00000160,0x00000160UL, uint32_t  ))    /*  TIAGAIN: 20k */
#define ENUM_AFE_LPTIACON1_TIAGAIN24K        (_ADI_MSK_3(0x00000180,0x00000180UL, uint32_t  ))    /*  TIAGAIN: 24k */
#define ENUM_AFE_LPTIACON1_TIAGAIN30K        (_ADI_MSK_3(0x000001A0,0x000001A0UL, uint32_t  ))    /*  TIAGAIN: 30k */
#define ENUM_AFE_LPTIACON1_TIAGAIN32K        (_ADI_MSK_3(0x000001C0,0x000001C0UL, uint32_t  ))    /*  TIAGAIN: 32k */
#define ENUM_AFE_LPTIACON1_TIAGAIN40K        (_ADI_MSK_3(0x000001E0,0x000001E0UL, uint32_t  ))    /*  TIAGAIN: 40k */
#define ENUM_AFE_LPTIACON1_TIAGAIN48K        (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  TIAGAIN: 48k */
#define ENUM_AFE_LPTIACON1_TIAGAIN64K        (_ADI_MSK_3(0x00000220,0x00000220UL, uint32_t  ))    /*  TIAGAIN: 64k */
#define ENUM_AFE_LPTIACON1_TIAGAIN85K        (_ADI_MSK_3(0x00000240,0x00000240UL, uint32_t  ))    /*  TIAGAIN: 85k */
#define ENUM_AFE_LPTIACON1_TIAGAIN96K        (_ADI_MSK_3(0x00000260,0x00000260UL, uint32_t  ))    /*  TIAGAIN: 96k */
#define ENUM_AFE_LPTIACON1_TIAGAIN100K       (_ADI_MSK_3(0x00000280,0x00000280UL, uint32_t  ))    /*  TIAGAIN: 100k */
#define ENUM_AFE_LPTIACON1_TIAGAIN120K       (_ADI_MSK_3(0x000002A0,0x000002A0UL, uint32_t  ))    /*  TIAGAIN: 120k */
#define ENUM_AFE_LPTIACON1_TIAGAIN128K       (_ADI_MSK_3(0x000002C0,0x000002C0UL, uint32_t  ))    /*  TIAGAIN: 128k */
#define ENUM_AFE_LPTIACON1_TIAGAIN160K       (_ADI_MSK_3(0x000002E0,0x000002E0UL, uint32_t  ))    /*  TIAGAIN: 160k */
#define ENUM_AFE_LPTIACON1_TIAGAIN196K       (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  TIAGAIN: 196k */
#define ENUM_AFE_LPTIACON1_TIAGAIN256K       (_ADI_MSK_3(0x00000320,0x00000320UL, uint32_t  ))    /*  TIAGAIN: 256k */
#define ENUM_AFE_LPTIACON1_TIAGAIN512K       (_ADI_MSK_3(0x00000340,0x00000340UL, uint32_t  ))    /*  TIAGAIN: 512k */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPTIACON0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPTIACON0_CHOPEN            16            /*  Chopping Enable */
#define BITP_AFE_LPTIACON0_TIARF             13            /*  Set LPF Resistor */
#define BITP_AFE_LPTIACON0_TIARL             10            /*  Set RLOAD */
#define BITP_AFE_LPTIACON0_TIAGAIN            5            /*  Set RTIA */
#define BITP_AFE_LPTIACON0_IBOOST             3            /*  Current Boost Control */
#define BITP_AFE_LPTIACON0_HALFPWR            2            /*  Half Power Mode Select */
#define BITP_AFE_LPTIACON0_PAPDEN             1            /*  PA Power Down */
#define BITP_AFE_LPTIACON0_TIAPDEN            0            /*  TIA Power Down */
#define BITM_AFE_LPTIACON0_CHOPEN            (_ADI_MSK_3(0x00030000,0x00030000UL, uint32_t  ))    /*  Chopping Enable */
#define BITM_AFE_LPTIACON0_TIARF             (_ADI_MSK_3(0x0000E000,0x0000E000UL, uint32_t  ))    /*  Set LPF Resistor */
#define BITM_AFE_LPTIACON0_TIARL             (_ADI_MSK_3(0x00001C00,0x00001C00UL, uint32_t  ))    /*  Set RLOAD */
#define BITM_AFE_LPTIACON0_TIAGAIN           (_ADI_MSK_3(0x000003E0,0x000003E0UL, uint32_t  ))    /*  Set RTIA */
#define BITM_AFE_LPTIACON0_IBOOST            (_ADI_MSK_3(0x00000018,0x00000018UL, uint32_t  ))    /*  Current Boost Control */
#define BITM_AFE_LPTIACON0_HALFPWR           (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Half Power Mode Select */
#define BITM_AFE_LPTIACON0_PAPDEN            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  PA Power Down */
#define BITM_AFE_LPTIACON0_TIAPDEN           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  TIA Power Down */
#define ENUM_AFE_LPTIACON0_DISCONRF          (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  TIARF: Disconnect TIA output from LPF pin */
#define ENUM_AFE_LPTIACON0_BYPRF             (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  TIARF: Bypass resistor */
#define ENUM_AFE_LPTIACON0_RF20K             (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  TIARF: 20k Ohm */
#define ENUM_AFE_LPTIACON0_RF100K            (_ADI_MSK_3(0x00006000,0x00006000UL, uint32_t  ))    /*  TIARF: 100k Ohm */
#define ENUM_AFE_LPTIACON0_RF200K            (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  TIARF: 200k Ohm */
#define ENUM_AFE_LPTIACON0_RF400K            (_ADI_MSK_3(0x0000A000,0x0000A000UL, uint32_t  ))    /*  TIARF: 400k Ohm */
#define ENUM_AFE_LPTIACON0_RF600K            (_ADI_MSK_3(0x0000C000,0x0000C000UL, uint32_t  ))    /*  TIARF: 600k Ohm */
#define ENUM_AFE_LPTIACON0_RF1MOHM           (_ADI_MSK_3(0x0000E000,0x0000E000UL, uint32_t  ))    /*  TIARF: 1Meg Ohm */
#define ENUM_AFE_LPTIACON0_RL0               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  TIARL: 0 ohm */
#define ENUM_AFE_LPTIACON0_RL10              (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  TIARL: 10 ohm */
#define ENUM_AFE_LPTIACON0_RL30              (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  TIARL: 30 ohm */
#define ENUM_AFE_LPTIACON0_RL50              (_ADI_MSK_3(0x00000C00,0x00000C00UL, uint32_t  ))    /*  TIARL: 50 ohm */
#define ENUM_AFE_LPTIACON0_RL100             (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  TIARL: 100 ohm */
#define ENUM_AFE_LPTIACON0_RL1P6K            (_ADI_MSK_3(0x00001400,0x00001400UL, uint32_t  ))    /*  TIARL: 1.6kohm */
#define ENUM_AFE_LPTIACON0_RL3P1K            (_ADI_MSK_3(0x00001800,0x00001800UL, uint32_t  ))    /*  TIARL: 3.1kohm */
#define ENUM_AFE_LPTIACON0_RL3P5K            (_ADI_MSK_3(0x00001C00,0x00001C00UL, uint32_t  ))    /*  TIARL: 3.6kohm */
#define ENUM_AFE_LPTIACON0_DISCONTIA         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  TIAGAIN: Disconnect TIA Gain resistor */
#define ENUM_AFE_LPTIACON0_TIAGAIN200        (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  TIAGAIN: 200 Ohm */
#define ENUM_AFE_LPTIACON0_TIAGAIN1K         (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  TIAGAIN: 1k ohm */
#define ENUM_AFE_LPTIACON0_TIAGAIN2K         (_ADI_MSK_3(0x00000060,0x00000060UL, uint32_t  ))    /*  TIAGAIN: 2k */
#define ENUM_AFE_LPTIACON0_TIAGAIN3K         (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  TIAGAIN: 3k */
#define ENUM_AFE_LPTIACON0_TIAGAIN4K         (_ADI_MSK_3(0x000000A0,0x000000A0UL, uint32_t  ))    /*  TIAGAIN: 4k */
#define ENUM_AFE_LPTIACON0_TIAGAIN6K         (_ADI_MSK_3(0x000000C0,0x000000C0UL, uint32_t  ))    /*  TIAGAIN: 6k */
#define ENUM_AFE_LPTIACON0_TIAGAIN8K         (_ADI_MSK_3(0x000000E0,0x000000E0UL, uint32_t  ))    /*  TIAGAIN: 8k */
#define ENUM_AFE_LPTIACON0_TIAGAIN10K        (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  TIAGAIN: 10k */
#define ENUM_AFE_LPTIACON0_TIAGAIN12K        (_ADI_MSK_3(0x00000120,0x00000120UL, uint32_t  ))    /*  TIAGAIN: 12k */
#define ENUM_AFE_LPTIACON0_TIAGAIN16K        (_ADI_MSK_3(0x00000140,0x00000140UL, uint32_t  ))    /*  TIAGAIN: 16k */
#define ENUM_AFE_LPTIACON0_TIAGAIN20K        (_ADI_MSK_3(0x00000160,0x00000160UL, uint32_t  ))    /*  TIAGAIN: 20k */
#define ENUM_AFE_LPTIACON0_TIAGAIN24K        (_ADI_MSK_3(0x00000180,0x00000180UL, uint32_t  ))    /*  TIAGAIN: 24k */
#define ENUM_AFE_LPTIACON0_TIAGAIN30K        (_ADI_MSK_3(0x000001A0,0x000001A0UL, uint32_t  ))    /*  TIAGAIN: 30k */
#define ENUM_AFE_LPTIACON0_TIAGAIN32K        (_ADI_MSK_3(0x000001C0,0x000001C0UL, uint32_t  ))    /*  TIAGAIN: 32k */
#define ENUM_AFE_LPTIACON0_TIAGAIN40K        (_ADI_MSK_3(0x000001E0,0x000001E0UL, uint32_t  ))    /*  TIAGAIN: 40k */
#define ENUM_AFE_LPTIACON0_TIAGAIN48K        (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  TIAGAIN: 48k */
#define ENUM_AFE_LPTIACON0_TIAGAIN64K        (_ADI_MSK_3(0x00000220,0x00000220UL, uint32_t  ))    /*  TIAGAIN: 64k */
#define ENUM_AFE_LPTIACON0_TIAGAIN85K        (_ADI_MSK_3(0x00000240,0x00000240UL, uint32_t  ))    /*  TIAGAIN: 85k */
#define ENUM_AFE_LPTIACON0_TIAGAIN96K        (_ADI_MSK_3(0x00000260,0x00000260UL, uint32_t  ))    /*  TIAGAIN: 96k */
#define ENUM_AFE_LPTIACON0_TIAGAIN100K       (_ADI_MSK_3(0x00000280,0x00000280UL, uint32_t  ))    /*  TIAGAIN: 100k */
#define ENUM_AFE_LPTIACON0_TIAGAIN120K       (_ADI_MSK_3(0x000002A0,0x000002A0UL, uint32_t  ))    /*  TIAGAIN: 120k */
#define ENUM_AFE_LPTIACON0_TIAGAIN128K       (_ADI_MSK_3(0x000002C0,0x000002C0UL, uint32_t  ))    /*  TIAGAIN: 128k */
#define ENUM_AFE_LPTIACON0_TIAGAIN160K       (_ADI_MSK_3(0x000002E0,0x000002E0UL, uint32_t  ))    /*  TIAGAIN: 160k */
#define ENUM_AFE_LPTIACON0_TIAGAIN196K       (_ADI_MSK_3(0x00000300,0x00000300UL, uint32_t  ))    /*  TIAGAIN: 196k */
#define ENUM_AFE_LPTIACON0_TIAGAIN256K       (_ADI_MSK_3(0x00000320,0x00000320UL, uint32_t  ))    /*  TIAGAIN: 256k */
#define ENUM_AFE_LPTIACON0_TIAGAIN512K       (_ADI_MSK_3(0x00000340,0x00000340UL, uint32_t  ))    /*  TIAGAIN: 512k */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_HSRTIACON                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_HSRTIACON_CTIACON            5            /*  Configure Capacitor in Parallel with RTIA */
#define BITP_AFE_HSRTIACON_TIASW6CON          4            /*  SW6 Control */
#define BITP_AFE_HSRTIACON_RTIACON            0            /*  Configure General RTIA Value */
#define BITM_AFE_HSRTIACON_CTIACON           (_ADI_MSK_3(0x00001FE0,0x00001FE0UL, uint32_t  ))    /*  Configure Capacitor in Parallel with RTIA */
#define BITM_AFE_HSRTIACON_TIASW6CON         (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  SW6 Control */
#define BITM_AFE_HSRTIACON_RTIACON           (_ADI_MSK_3(0x0000000F,0x0000000FUL, uint32_t  ))    /*  Configure General RTIA Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DE1RESCON                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DE1RESCON_DE1RCON            0            /*  DE1 RLOAD RTIA Setting */
#define BITM_AFE_DE1RESCON_DE1RCON           (_ADI_MSK_3(0x000000FF,0x000000FFUL, uint32_t  ))    /*  DE1 RLOAD RTIA Setting */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DE0RESCON                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DE0RESCON_DE0RCON            0            /*  DE0 RLOAD RTIA Setting */
#define BITM_AFE_DE0RESCON_DE0RCON           (_ADI_MSK_3(0x000000FF,0x000000FFUL, uint32_t  ))    /*  DE0 RLOAD RTIA Setting */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_HSTIACON                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_HSTIACON_VBIASSEL            0            /*  Select HSTIA Positive Input */
#define BITM_AFE_HSTIACON_VBIASSEL           (_ADI_MSK_3(0x00000003,0x00000003UL, uint32_t  ))    /*  Select HSTIA Positive Input */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DACDCBUFCON                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DACDCBUFCON_CHANSEL          1            /*  DAC DC Channel Selection */
#define BITP_AFE_DACDCBUFCON_RESERVED_0       0            /*  Reserved */
#define BITM_AFE_DACDCBUFCON_CHANSEL         (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  DAC DC Channel Selection */
#define BITM_AFE_DACDCBUFCON_RESERVED_0      (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Reserved */
#define ENUM_AFE_DACDCBUFCON_CHAN0           (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  CHANSEL: ULPDAC0 Sets DC level */
#define ENUM_AFE_DACDCBUFCON_CHAN1           (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  CHANSEL: ULPDAC1 Sets DC level */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPDACDAT0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPDACDAT0_DACIN6            12            /*  6BITVAL, 1LSB=34.375mV */
#define BITP_AFE_LPDACDAT0_DACIN12            0            /*  12BITVAL, 1LSB=537uV */
#define BITM_AFE_LPDACDAT0_DACIN6            (_ADI_MSK_3(0x0003F000,0x0003F000UL, uint32_t  ))    /*  6BITVAL, 1LSB=34.375mV */
#define BITM_AFE_LPDACDAT0_DACIN12           (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  12BITVAL, 1LSB=537uV */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPDACSW0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPDACSW0_LPMODEDIS           5            /*  Switch Control */
#define BITP_AFE_LPDACSW0_LPDACSW             0            /*  LPDAC0 Switches Matrix */
#define BITM_AFE_LPDACSW0_LPMODEDIS          (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Switch Control */
#define BITM_AFE_LPDACSW0_LPDACSW            (_ADI_MSK_3(0x0000001F,0x0000001FUL, uint32_t  ))    /*  LPDAC0 Switches Matrix */
#define ENUM_AFE_LPDACSW0_DACCONBIT5         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  LPMODEDIS: ULPDAC Switch controlled by ULPDACCON0 bit 5 */
#define ENUM_AFE_LPDACSW0_OVRRIDE            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  LPMODEDIS: ULPDAC Switches override */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPDACCON0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPDACCON0_WAVETYPE           6            /*  LPDAC Data Source */
#define BITP_AFE_LPDACCON0_DACMDE             5            /*  LPDAC0 Switch Settings */
#define BITP_AFE_LPDACCON0_VZEROMUX           4            /*  VZERO MUX Select */
#define BITP_AFE_LPDACCON0_VBIASMUX           3            /*  VBIAS MUX Select */
#define BITP_AFE_LPDACCON0_REFSEL             2            /*  Reference Select Bit */
#define BITP_AFE_LPDACCON0_PWDEN              1            /*  LPDAC0 Power Down */
#define BITP_AFE_LPDACCON0_RSTEN              0            /*  Enable Writes to ULPDAC0 */
#define BITM_AFE_LPDACCON0_WAVETYPE          (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  LPDAC Data Source */
#define BITM_AFE_LPDACCON0_DACMDE            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  LPDAC0 Switch Settings */
#define BITM_AFE_LPDACCON0_VZEROMUX          (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  VZERO MUX Select */
#define BITM_AFE_LPDACCON0_VBIASMUX          (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  VBIAS MUX Select */
#define BITM_AFE_LPDACCON0_REFSEL            (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Reference Select Bit */
#define BITM_AFE_LPDACCON0_PWDEN             (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  LPDAC0 Power Down */
#define BITM_AFE_LPDACCON0_RSTEN             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable Writes to ULPDAC0 */
#define ENUM_AFE_LPDACCON0_MMR               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  WAVETYPE: Direct from ULPDACDAT0 */
#define ENUM_AFE_LPDACCON0_WAVEGEN           (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  WAVETYPE: Waveform generator */
#define ENUM_AFE_LPDACCON0_NORM              (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  DACMDE: ULPDAC0 switches set for normal mode */
#define ENUM_AFE_LPDACCON0_DIAG              (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  DACMDE: ULPDAC0 switches set for Diagnostic mode */
#define ENUM_AFE_LPDACCON0_BITS6             (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  VZEROMUX: VZERO 6BIT */
#define ENUM_AFE_LPDACCON0_BITS12            (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  VZEROMUX: VZERO 12BIT */
#define ENUM_AFE_LPDACCON0_12BIT             (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  VBIASMUX: Output 12Bit */
#define ENUM_AFE_LPDACCON0_EN                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  VBIASMUX: output 6Bit */
#define ENUM_AFE_LPDACCON0_ULPREF            (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  REFSEL: ULP2P5V Ref */
#define ENUM_AFE_LPDACCON0_AVDD              (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  REFSEL: AVDD Reference */
#define ENUM_AFE_LPDACCON0_PWREN             (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  PWDEN: ULPDAC0 Powered On */
#define ENUM_AFE_LPDACCON0_PWRDIS            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  PWDEN: ULPDAC0 Powered Off */
#define ENUM_AFE_LPDACCON0_WRITEDIS          (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  RSTEN: Disable ULPDAC0 Writes */
#define ENUM_AFE_LPDACCON0_WRITEEN           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  RSTEN: Enable ULPDAC0 Writes */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPDACDAT1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPDACDAT1_DACIN6            12            /*  6BITVAL, 1LSB=34.375mV */
#define BITP_AFE_LPDACDAT1_DACIN12            0            /*  12BITVAL, 1LSB=537uV */
#define BITM_AFE_LPDACDAT1_DACIN6            (_ADI_MSK_3(0x0003F000,0x0003F000UL, uint32_t  ))    /*  6BITVAL, 1LSB=34.375mV */
#define BITM_AFE_LPDACDAT1_DACIN12           (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  12BITVAL, 1LSB=537uV */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPDACSW1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPDACSW1_LPMODEDIS           5            /*  Switch Control */
#define BITP_AFE_LPDACSW1_LPDACSW             0            /*  ULPDAC0 Switches Matrix */
#define BITM_AFE_LPDACSW1_LPMODEDIS          (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Switch Control */
#define BITM_AFE_LPDACSW1_LPDACSW            (_ADI_MSK_3(0x0000001F,0x0000001FUL, uint32_t  ))    /*  ULPDAC0 Switches Matrix */
#define ENUM_AFE_LPDACSW1_DACCONBIT5         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  LPMODEDIS: ULPDAC Switch controlled by ULPDACCON1 bit 5 */
#define ENUM_AFE_LPDACSW1_OVRRIDE            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  LPMODEDIS: ULPDAC Switches override */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_LPDACCON1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_LPDACCON1_WAVETYPE           6            /*  DAC Input Source */
#define BITP_AFE_LPDACCON1_DACMDE             5            /*  LPDAC1 Switch Settings */
#define BITP_AFE_LPDACCON1_VZEROMUX           4            /*  VZEROOUT */
#define BITP_AFE_LPDACCON1_VBIASMUX           3            /*  BITSEL */
#define BITP_AFE_LPDACCON1_REFSEL             2            /*  REFSEL */
#define BITP_AFE_LPDACCON1_PWDEN              1            /*  ULPDAC0 Power */
#define BITP_AFE_LPDACCON1_RSTEN              0            /*  Enable Writes to ULPDAC1 */
#define BITM_AFE_LPDACCON1_WAVETYPE          (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  DAC Input Source */
#define BITM_AFE_LPDACCON1_DACMDE            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  LPDAC1 Switch Settings */
#define BITM_AFE_LPDACCON1_VZEROMUX          (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  VZEROOUT */
#define BITM_AFE_LPDACCON1_VBIASMUX          (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  BITSEL */
#define BITM_AFE_LPDACCON1_REFSEL            (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  REFSEL */
#define BITM_AFE_LPDACCON1_PWDEN             (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  ULPDAC0 Power */
#define BITM_AFE_LPDACCON1_RSTEN             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable Writes to ULPDAC1 */
#define ENUM_AFE_LPDACCON1_NORM              (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  DACMDE: ULPDAC1 switches set for normal mode */
#define ENUM_AFE_LPDACCON1_DIAG              (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  DACMDE: ULPDAC1 switches set for Diagnostic mode */
#define ENUM_AFE_LPDACCON1_BITS6             (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  VZEROMUX: VZERO 6BIT */
#define ENUM_AFE_LPDACCON1_BITS12            (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  VZEROMUX: VZERO 12BIT */
#define ENUM_AFE_LPDACCON1_DIS               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  VBIASMUX: 12BIT Output */
#define ENUM_AFE_LPDACCON1_EN                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  VBIASMUX: 6BIT Output */
#define ENUM_AFE_LPDACCON1_ULPREF            (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))
#define ENUM_AFE_LPDACCON1_AVDD              (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))
#define ENUM_AFE_LPDACCON1_PWREN             (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  PWDEN: ULPDAC1 Powered On */
#define ENUM_AFE_LPDACCON1_PWRDIS            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  PWDEN: ULPDAC1 Powered Off */
#define ENUM_AFE_LPDACCON1_WRITEDIS          (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  RSTEN: Disable ULPDAC1 Writes */
#define ENUM_AFE_LPDACCON1_WRITEEN           (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  RSTEN: Enable ULPDAC1 Writes */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DSWFULLCON                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DSWFULLCON_D8                7            /*  Control of D8 Switch. */
#define BITP_AFE_DSWFULLCON_D7                6            /*  Control of D7 Switch. */
#define BITP_AFE_DSWFULLCON_D6                5            /*  Control of D6 Switch. */
#define BITP_AFE_DSWFULLCON_D5                4            /*  Control of D5 Switch. */
#define BITP_AFE_DSWFULLCON_D4                3            /*  Control of D4 Switch. */
#define BITP_AFE_DSWFULLCON_D3                2            /*  Control of D3 Switch. */
#define BITP_AFE_DSWFULLCON_D2                1            /*  Control of D2 Switch. */
#define BITP_AFE_DSWFULLCON_DR0               0            /*  Control of Dr0 Switch. */
#define BITM_AFE_DSWFULLCON_D8               (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Control of D8 Switch. */
#define BITM_AFE_DSWFULLCON_D7               (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Control of D7 Switch. */
#define BITM_AFE_DSWFULLCON_D6               (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Control of D6 Switch. */
#define BITM_AFE_DSWFULLCON_D5               (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Control of D5 Switch. */
#define BITM_AFE_DSWFULLCON_D4               (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Control of D4 Switch. */
#define BITM_AFE_DSWFULLCON_D3               (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Control of D3 Switch. */
#define BITM_AFE_DSWFULLCON_D2               (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Control of D2 Switch. */
#define BITM_AFE_DSWFULLCON_DR0              (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Control of Dr0 Switch. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_NSWFULLCON                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_NSWFULLCON_NL2              11            /*  Control of NL2 Switch. */
#define BITP_AFE_NSWFULLCON_NL               10            /*  Control of NL Switch. */
#define BITP_AFE_NSWFULLCON_NR1               9            /*  Control of Nr1 Switch. Set Will Close Nr1, Unset Open */
#define BITP_AFE_NSWFULLCON_N9                8            /*  Control of N9 Switch. Set Will Close N9, Unset Open */
#define BITP_AFE_NSWFULLCON_N8                7            /*  Control of N8 Switch. Set Will Close N8, Unset Open */
#define BITP_AFE_NSWFULLCON_N7                6            /*  Control of N7 Switch. Set Will Close N7, Unset Open */
#define BITP_AFE_NSWFULLCON_N6                5            /*  Control of N6 Switch. Set Will Close N6, Unset Open */
#define BITP_AFE_NSWFULLCON_N5                4            /*  Control of N5 Switch. Set Will Close N5, Unset Open */
#define BITP_AFE_NSWFULLCON_N4                3            /*  Control of N4 Switch. Set Will Close N4, Unset Open */
#define BITP_AFE_NSWFULLCON_N3                2            /*  Control of N3 Switch. Set Will Close N3, Unset Open */
#define BITP_AFE_NSWFULLCON_N2                1            /*  Control of N2 Switch. Set Will Close N2, Unset Open */
#define BITP_AFE_NSWFULLCON_N1                0            /*  Control of N1 Switch. Set Will Close N1, Unset Open */
#define BITM_AFE_NSWFULLCON_NL2              (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Control of NL2 Switch. */
#define BITM_AFE_NSWFULLCON_NL               (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Control of NL Switch. */
#define BITM_AFE_NSWFULLCON_NR1              (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Control of Nr1 Switch. Set Will Close Nr1, Unset Open */
#define BITM_AFE_NSWFULLCON_N9               (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Control of N9 Switch. Set Will Close N9, Unset Open */
#define BITM_AFE_NSWFULLCON_N8               (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Control of N8 Switch. Set Will Close N8, Unset Open */
#define BITM_AFE_NSWFULLCON_N7               (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Control of N7 Switch. Set Will Close N7, Unset Open */
#define BITM_AFE_NSWFULLCON_N6               (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Control of N6 Switch. Set Will Close N6, Unset Open */
#define BITM_AFE_NSWFULLCON_N5               (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Control of N5 Switch. Set Will Close N5, Unset Open */
#define BITM_AFE_NSWFULLCON_N4               (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Control of N4 Switch. Set Will Close N4, Unset Open */
#define BITM_AFE_NSWFULLCON_N3               (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Control of N3 Switch. Set Will Close N3, Unset Open */
#define BITM_AFE_NSWFULLCON_N2               (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Control of N2 Switch. Set Will Close N2, Unset Open */
#define BITM_AFE_NSWFULLCON_N1               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Control of N1 Switch. Set Will Close N1, Unset Open */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PSWFULLCON                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PSWFULLCON_PL2              14            /*  PL2 Switch Control */
#define BITP_AFE_PSWFULLCON_PL               13            /*  PL Switch Control */
#define BITP_AFE_PSWFULLCON_P12              11            /*  Control of P12 Switch. Set Will Close P12, Unset Open */
#define BITP_AFE_PSWFULLCON_P11              10            /*  Control of P11 Switch. Set Will Close P11, Unset Open */
#define BITP_AFE_PSWFULLCON_P10               9            /*  P10 Switch Control */
#define BITP_AFE_PSWFULLCON_P9                8            /*  Control of P9 Switch. Set Will Close P9, Unset Open */
#define BITP_AFE_PSWFULLCON_P8                7            /*  Control of P8 Switch. Set Will Close P8, Unset Open */
#define BITP_AFE_PSWFULLCON_P7                6            /*  Control of P7 Switch. Set Will Close P7, Unset Open */
#define BITP_AFE_PSWFULLCON_P6                5            /*  Control of P6 Switch. Set Will Close P6, Unset Open */
#define BITP_AFE_PSWFULLCON_P5                4            /*  Control of P5 Switch. Set Will Close P5, Unset Open */
#define BITP_AFE_PSWFULLCON_P4                3            /*  Control of P4 Switch. Set Will Close P4, Unset Open */
#define BITP_AFE_PSWFULLCON_P3                2            /*  Control of P3 Switch. Set Will Close P3, Unset Open */
#define BITP_AFE_PSWFULLCON_P2                1            /*  Control of P2 Switch. Set Will Close P2, Unset Open */
#define BITP_AFE_PSWFULLCON_PR0               0            /*  PR0 Switch Control */
#define BITM_AFE_PSWFULLCON_PL2              (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  PL2 Switch Control */
#define BITM_AFE_PSWFULLCON_PL               (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  PL Switch Control */
#define BITM_AFE_PSWFULLCON_P12              (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Control of P12 Switch. Set Will Close P12, Unset Open */
#define BITM_AFE_PSWFULLCON_P11              (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Control of P11 Switch. Set Will Close P11, Unset Open */
#define BITM_AFE_PSWFULLCON_P10              (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  P10 Switch Control */
#define BITM_AFE_PSWFULLCON_P9               (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Control of P9 Switch. Set Will Close P9, Unset Open */
#define BITM_AFE_PSWFULLCON_P8               (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Control of P8 Switch. Set Will Close P8, Unset Open */
#define BITM_AFE_PSWFULLCON_P7               (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Control of P7 Switch. Set Will Close P7, Unset Open */
#define BITM_AFE_PSWFULLCON_P6               (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Control of P6 Switch. Set Will Close P6, Unset Open */
#define BITM_AFE_PSWFULLCON_P5               (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Control of P5 Switch. Set Will Close P5, Unset Open */
#define BITM_AFE_PSWFULLCON_P4               (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Control of P4 Switch. Set Will Close P4, Unset Open */
#define BITM_AFE_PSWFULLCON_P3               (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Control of P3 Switch. Set Will Close P3, Unset Open */
#define BITM_AFE_PSWFULLCON_P2               (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Control of P2 Switch. Set Will Close P2, Unset Open */
#define BITM_AFE_PSWFULLCON_PR0              (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  PR0 Switch Control */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_TSWFULLCON                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_TSWFULLCON_TR1              11            /*  Control of Tr1 Switch. Set Will Close Tr1, Unset Open */
#define BITP_AFE_TSWFULLCON_T11              10            /*  Control of T11 Switch. Set Will Close T11, Unset Open */
#define BITP_AFE_TSWFULLCON_T10               9            /*  Control of T10 Switch. Set Will Close T10, Unset Open */
#define BITP_AFE_TSWFULLCON_T9                8            /*  Control of T9 Switch. Set Will Close T9, Unset Open */
#define BITP_AFE_TSWFULLCON_T7                6            /*  Control of T7 Switch. Set Will Close T7, Unset Open */
#define BITP_AFE_TSWFULLCON_T5                4            /*  Control of T5 Switch. Set Will Close T5, Unset Open */
#define BITP_AFE_TSWFULLCON_T4                3            /*  Control of T4 Switch. Set Will Close T4, Unset Open */
#define BITP_AFE_TSWFULLCON_T3                2            /*  Control of T3 Switch. Set Will Close T3, Unset Open */
#define BITP_AFE_TSWFULLCON_T2                1            /*  Control of T2 Switch. Set Will Close T2, Unset Open */
#define BITP_AFE_TSWFULLCON_T1                0            /*  Control of T1 Switch. Set Will Close T1, Unset Open */
#define BITM_AFE_TSWFULLCON_TR1              (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Control of Tr1 Switch. Set Will Close Tr1, Unset Open */
#define BITM_AFE_TSWFULLCON_T11              (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Control of T11 Switch. Set Will Close T11, Unset Open */
#define BITM_AFE_TSWFULLCON_T10              (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Control of T10 Switch. Set Will Close T10, Unset Open */
#define BITM_AFE_TSWFULLCON_T9               (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Control of T9 Switch. Set Will Close T9, Unset Open */
#define BITM_AFE_TSWFULLCON_T7               (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Control of T7 Switch. Set Will Close T7, Unset Open */
#define BITM_AFE_TSWFULLCON_T5               (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Control of T5 Switch. Set Will Close T5, Unset Open */
#define BITM_AFE_TSWFULLCON_T4               (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Control of T4 Switch. Set Will Close T4, Unset Open */
#define BITM_AFE_TSWFULLCON_T3               (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Control of T3 Switch. Set Will Close T3, Unset Open */
#define BITM_AFE_TSWFULLCON_T2               (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Control of T2 Switch. Set Will Close T2, Unset Open */
#define BITM_AFE_TSWFULLCON_T1               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Control of T1 Switch. Set Will Close T1, Unset Open */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_TEMPCON0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_TEMPCON0_CHOPFRESEL          2            /*  Chop Mode Frequency Setting */
#define BITP_AFE_TEMPCON0_CHOPCON             1            /*  Temp Sensor Chop Mode */
#define BITP_AFE_TEMPCON0_ENABLE              0            /*  Unused */
#define BITM_AFE_TEMPCON0_CHOPFRESEL         (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  Chop Mode Frequency Setting */
#define BITM_AFE_TEMPCON0_CHOPCON            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Temp Sensor Chop Mode */
#define BITM_AFE_TEMPCON0_ENABLE             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Unused */
#define ENUM_AFE_TEMPCON0_DIS                (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  CHOPCON: Disable chop */
#define ENUM_AFE_TEMPCON0_EN                 (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  CHOPCON: Enable chop */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_BUFSENCON                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_BUFSENCON_V1P8THERMSTEN      8            /*  Buffered Reference Output */
#define BITP_AFE_BUFSENCON_V1P1LPADCCHGDIS    6            /*  Controls Decoupling Cap Discharge Switch */
#define BITP_AFE_BUFSENCON_V1P1LPADCEN        5            /*  ADC 1.1V LP Buffer */
#define BITP_AFE_BUFSENCON_V1P1HPADCEN        4            /*  Enable 1.1V HP CM Buffer */
#define BITP_AFE_BUFSENCON_V1P8HPADCCHGDIS    3            /*  Controls Decoupling Cap Discharge Switch */
#define BITP_AFE_BUFSENCON_V1P8LPADCEN        2            /*  ADC 1.8V LP Reference Buffer */
#define BITP_AFE_BUFSENCON_V1P8HPADCILIMITEN  1            /*  HP ADC Input Current Limit */
#define BITP_AFE_BUFSENCON_V1P8HPADCEN        0            /*  HP 1.8V Reference Buffer */
#define BITM_AFE_BUFSENCON_V1P8THERMSTEN     (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Buffered Reference Output */
#define BITM_AFE_BUFSENCON_V1P1LPADCCHGDIS   (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Controls Decoupling Cap Discharge Switch */
#define BITM_AFE_BUFSENCON_V1P1LPADCEN       (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  ADC 1.1V LP Buffer */
#define BITM_AFE_BUFSENCON_V1P1HPADCEN       (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Enable 1.1V HP CM Buffer */
#define BITM_AFE_BUFSENCON_V1P8HPADCCHGDIS   (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Controls Decoupling Cap Discharge Switch */
#define BITM_AFE_BUFSENCON_V1P8LPADCEN       (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  ADC 1.8V LP Reference Buffer */
#define BITM_AFE_BUFSENCON_V1P8HPADCILIMITEN (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  HP ADC Input Current Limit */
#define BITM_AFE_BUFSENCON_V1P8HPADCEN       (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  HP 1.8V Reference Buffer */
#define ENUM_AFE_BUFSENCON_DIS               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P8THERMSTEN: Disable 1.8V Buffered Reference output */
#define ENUM_AFE_BUFSENCON_EN                (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  V1P8THERMSTEN: Enable 1.8V Buffered Reference output */
#define ENUM_AFE_BUFSENCON_ENCHRG            (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P1LPADCCHGDIS: Open switch */
#define ENUM_AFE_BUFSENCON_DISCHRG           (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  V1P1LPADCCHGDIS: Close Switch */
#define ENUM_AFE_BUFSENCON_DISABLE           (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P1LPADCEN: Disable ADC 1.8V LP Reference Buffer */
#define ENUM_AFE_BUFSENCON_ENABLE            (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  V1P1LPADCEN: Enable ADC 1.8V LP Reference Buffer */
#define ENUM_AFE_BUFSENCON_OFF               (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P1HPADCEN: Disable 1.1V HP Common Mode Buffer */
#define ENUM_AFE_BUFSENCON_ON                (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  V1P1HPADCEN: Enable 1.1V HP Common Mode Buffer */
#define ENUM_AFE_BUFSENCON_OPEN              (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P8HPADCCHGDIS: Open switch */
#define ENUM_AFE_BUFSENCON_CLOSED            (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  V1P8HPADCCHGDIS: Close Switch */
#define ENUM_AFE_BUFSENCON_LPADCREF_DIS      (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P8LPADCEN: Disable LP 1.8V Reference Buffer */
#define ENUM_AFE_BUFSENCON_LPADCREF_EN       (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  V1P8LPADCEN: Enable LP 1.8V Reference Buffer */
#define ENUM_AFE_BUFSENCON_LIMIT_DIS         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P8HPADCILIMITEN: Disable buffer Current Limit */
#define ENUM_AFE_BUFSENCON_LIMIT_EN          (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  V1P8HPADCILIMITEN: Enable buffer Current Limit */
#define ENUM_AFE_BUFSENCON_HPBUF_DIS         (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  V1P8HPADCEN: Disable 1.8V HP ADC Reference Buffer */
#define ENUM_AFE_BUFSENCON_HPBUF_EN          (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  V1P8HPADCEN: Enable 1.8V HP ADC Reference Buffer */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCCON                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCCON_GNPGA                16            /*  PGA Gain Setup */
#define BITP_AFE_ADCCON_GNOFSELPGA           15            /*  Internal Offset/Gain Cancellation */
#define BITP_AFE_ADCCON_GNOFFSEL             13            /*  Obsolete */
#define BITP_AFE_ADCCON_MUXSELN               8            /*  Select Negative Input */
#define BITP_AFE_ADCCON_MUXSELP               0            /*  Select Positive Input */
#define BITM_AFE_ADCCON_GNPGA                (_ADI_MSK_3(0x00070000,0x00070000UL, uint32_t  ))    /*  PGA Gain Setup */
#define BITM_AFE_ADCCON_GNOFSELPGA           (_ADI_MSK_3(0x00008000,0x00008000UL, uint32_t  ))    /*  Internal Offset/Gain Cancellation */
#define BITM_AFE_ADCCON_GNOFFSEL             (_ADI_MSK_3(0x00006000,0x00006000UL, uint32_t  ))    /*  Obsolete */
#define BITM_AFE_ADCCON_MUXSELN              (_ADI_MSK_3(0x00001F00,0x00001F00UL, uint32_t  ))    /*  Select Negative Input */
#define BITM_AFE_ADCCON_MUXSELP              (_ADI_MSK_3(0x0000003F,0x0000003FUL, uint32_t  ))    /*  Select Positive Input */
#define ENUM_AFE_ADCCON_RESERVED             (_ADI_MSK_3(0x00000011,0x00000011UL, uint32_t  ))    /*  MUXSELP: Reserved */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DSWSTA                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DSWSTA_D8STA                 7            /*  Status of D8 Switch. */
#define BITP_AFE_DSWSTA_D7STA                 6            /*  Status of D7 Switch. */
#define BITP_AFE_DSWSTA_D6STA                 5            /*  Status of D6 Switch. */
#define BITP_AFE_DSWSTA_D5STA                 4            /*  Status of D5 Switch. */
#define BITP_AFE_DSWSTA_D4STA                 3            /*  Status of D4 Switch. */
#define BITP_AFE_DSWSTA_D3STA                 2            /*  Status of D3 Switch. */
#define BITP_AFE_DSWSTA_D2STA                 1            /*  Status of D2 Switch. */
#define BITP_AFE_DSWSTA_D1STA                 0            /*  Status of Dr0 Switch. */
#define BITM_AFE_DSWSTA_D8STA                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Status of D8 Switch. */
#define BITM_AFE_DSWSTA_D7STA                (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Status of D7 Switch. */
#define BITM_AFE_DSWSTA_D6STA                (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Status of D6 Switch. */
#define BITM_AFE_DSWSTA_D5STA                (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Status of D5 Switch. */
#define BITM_AFE_DSWSTA_D4STA                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Status of D4 Switch. */
#define BITM_AFE_DSWSTA_D3STA                (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Status of D3 Switch. */
#define BITM_AFE_DSWSTA_D2STA                (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Status of D2 Switch. */
#define BITM_AFE_DSWSTA_D1STA                (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Status of Dr0 Switch. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PSWSTA                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PSWSTA_PL2STA               14            /*  PL Switch Control */
#define BITP_AFE_PSWSTA_PLSTA                13            /*  PL Switch Control */
#define BITP_AFE_PSWSTA_P13STA               12            /*  Status of P13 Switch. */
#define BITP_AFE_PSWSTA_P12STA               11            /*  Status of P12 Switch. */
#define BITP_AFE_PSWSTA_P11STA               10            /*  Status of P11 Switch. */
#define BITP_AFE_PSWSTA_P10STA                9            /*  Status of P10 Switch. */
#define BITP_AFE_PSWSTA_P9STA                 8            /*  Status of P9 Switch. */
#define BITP_AFE_PSWSTA_P8STA                 7            /*  Status of P8 Switch. */
#define BITP_AFE_PSWSTA_P7STA                 6            /*  Status of P7 Switch. */
#define BITP_AFE_PSWSTA_P6STA                 5            /*  Status of P6 Switch. */
#define BITP_AFE_PSWSTA_P5STA                 4            /*  Status of P5 Switch. */
#define BITP_AFE_PSWSTA_P4STA                 3            /*  Status of P4 Switch. */
#define BITP_AFE_PSWSTA_P3STA                 2            /*  Status of P3 Switch. */
#define BITP_AFE_PSWSTA_P2STA                 1            /*  Status of P2 Switch. */
#define BITP_AFE_PSWSTA_PR0STA                0            /*  PR0 Switch Control */
#define BITM_AFE_PSWSTA_PL2STA               (_ADI_MSK_3(0x00004000,0x00004000UL, uint32_t  ))    /*  PL Switch Control */
#define BITM_AFE_PSWSTA_PLSTA                (_ADI_MSK_3(0x00002000,0x00002000UL, uint32_t  ))    /*  PL Switch Control */
#define BITM_AFE_PSWSTA_P13STA               (_ADI_MSK_3(0x00001000,0x00001000UL, uint32_t  ))    /*  Status of P13 Switch. */
#define BITM_AFE_PSWSTA_P12STA               (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Status of P12 Switch. */
#define BITM_AFE_PSWSTA_P11STA               (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Status of P11 Switch. */
#define BITM_AFE_PSWSTA_P10STA               (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Status of P10 Switch. */
#define BITM_AFE_PSWSTA_P9STA                (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Status of P9 Switch. */
#define BITM_AFE_PSWSTA_P8STA                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Status of P8 Switch. */
#define BITM_AFE_PSWSTA_P7STA                (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Status of P7 Switch. */
#define BITM_AFE_PSWSTA_P6STA                (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Status of P6 Switch. */
#define BITM_AFE_PSWSTA_P5STA                (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Status of P5 Switch. */
#define BITM_AFE_PSWSTA_P4STA                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Status of P4 Switch. */
#define BITM_AFE_PSWSTA_P3STA                (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Status of P3 Switch. */
#define BITM_AFE_PSWSTA_P2STA                (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Status of P2 Switch. */
#define BITM_AFE_PSWSTA_PR0STA               (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  PR0 Switch Control */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_NSWSTA                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_NSWSTA_NL2STA               11            /*  Status of NL2 Switch. */
#define BITP_AFE_NSWSTA_NLSTA                10            /*  Status of NL Switch. */
#define BITP_AFE_NSWSTA_NR1STA                9            /*  Status of NR1 Switch. */
#define BITP_AFE_NSWSTA_N9STA                 8            /*  Status of N9 Switch. */
#define BITP_AFE_NSWSTA_N8STA                 7            /*  Status of N8 Switch. */
#define BITP_AFE_NSWSTA_N7STA                 6            /*  Status of N7 Switch. */
#define BITP_AFE_NSWSTA_N6STA                 5            /*  Status of N6 Switch. */
#define BITP_AFE_NSWSTA_N5STA                 4            /*  Status of N5 Switch. */
#define BITP_AFE_NSWSTA_N4STA                 3            /*  Status of N4 Switch. */
#define BITP_AFE_NSWSTA_N3STA                 2            /*  Status of N3 Switch. */
#define BITP_AFE_NSWSTA_N2STA                 1            /*  Status of N2 Switch. */
#define BITP_AFE_NSWSTA_N1STA                 0            /*  Status of N1 Switch. */
#define BITM_AFE_NSWSTA_NL2STA               (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Status of NL2 Switch. */
#define BITM_AFE_NSWSTA_NLSTA                (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Status of NL Switch. */
#define BITM_AFE_NSWSTA_NR1STA               (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Status of NR1 Switch. */
#define BITM_AFE_NSWSTA_N9STA                (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Status of N9 Switch. */
#define BITM_AFE_NSWSTA_N8STA                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Status of N8 Switch. */
#define BITM_AFE_NSWSTA_N7STA                (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Status of N7 Switch. */
#define BITM_AFE_NSWSTA_N6STA                (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Status of N6 Switch. */
#define BITM_AFE_NSWSTA_N5STA                (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Status of N5 Switch. */
#define BITM_AFE_NSWSTA_N4STA                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Status of N4 Switch. */
#define BITM_AFE_NSWSTA_N3STA                (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Status of N3 Switch. */
#define BITM_AFE_NSWSTA_N2STA                (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Status of N2 Switch. */
#define BITM_AFE_NSWSTA_N1STA                (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Status of N1 Switch. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_TSWSTA                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_TSWSTA_TR1STA               11            /*  Status of TR1 Switch. */
#define BITP_AFE_TSWSTA_T11STA               10            /*  Status of T11 Switch. */
#define BITP_AFE_TSWSTA_T10STA                9            /*  Status of T10 Switch. */
#define BITP_AFE_TSWSTA_T9STA                 8            /*  Status of T9 Switch. */
#define BITP_AFE_TSWSTA_T8STA                 7            /*  Status of T8 Switch. */
#define BITP_AFE_TSWSTA_T7STA                 6            /*  Status of T7 Switch. */
#define BITP_AFE_TSWSTA_T6STA                 5            /*  Status of T6 Switch. */
#define BITP_AFE_TSWSTA_T5STA                 4            /*  Status of T5 Switch. */
#define BITP_AFE_TSWSTA_T4STA                 3            /*  Status of T4 Switch. */
#define BITP_AFE_TSWSTA_T3STA                 2            /*  Status of T3 Switch. */
#define BITP_AFE_TSWSTA_T2STA                 1            /*  Status of T2 Switch. */
#define BITP_AFE_TSWSTA_T1STA                 0            /*  Status of T1 Switch. */
#define BITM_AFE_TSWSTA_TR1STA               (_ADI_MSK_3(0x00000800,0x00000800UL, uint32_t  ))    /*  Status of TR1 Switch. */
#define BITM_AFE_TSWSTA_T11STA               (_ADI_MSK_3(0x00000400,0x00000400UL, uint32_t  ))    /*  Status of T11 Switch. */
#define BITM_AFE_TSWSTA_T10STA               (_ADI_MSK_3(0x00000200,0x00000200UL, uint32_t  ))    /*  Status of T10 Switch. */
#define BITM_AFE_TSWSTA_T9STA                (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Status of T9 Switch. */
#define BITM_AFE_TSWSTA_T8STA                (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Status of T8 Switch. */
#define BITM_AFE_TSWSTA_T7STA                (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Status of T7 Switch. */
#define BITM_AFE_TSWSTA_T6STA                (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  Status of T6 Switch. */
#define BITM_AFE_TSWSTA_T5STA                (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  Status of T5 Switch. */
#define BITM_AFE_TSWSTA_T4STA                (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Status of T4 Switch. */
#define BITM_AFE_TSWSTA_T3STA                (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Status of T3 Switch. */
#define BITM_AFE_TSWSTA_T2STA                (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  Status of T2 Switch. */
#define BITM_AFE_TSWSTA_T1STA                (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Status of T1 Switch. */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_STATSVAR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_STATSVAR_VARIANCE            0            /*  Statistical Variance Value */
#define BITM_AFE_STATSVAR_VARIANCE           (_ADI_MSK_3(0x7FFFFFFF,0x7FFFFFFFUL, uint32_t  ))    /*  Statistical Variance Value */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_STATSCON                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_STATSCON_STDDEV              7            /*  Standard Deviation Configuration */
#define BITP_AFE_STATSCON_SAMPLENUM           4            /*  Sample Size */
#define BITP_AFE_STATSCON_RESRVED             1            /*  Reserved */
#define BITP_AFE_STATSCON_STATSEN             0            /*  Statistics Enable */
#define BITM_AFE_STATSCON_STDDEV             (_ADI_MSK_3(0x00000F80,0x00000F80UL, uint32_t  ))    /*  Standard Deviation Configuration */
#define BITM_AFE_STATSCON_SAMPLENUM          (_ADI_MSK_3(0x00000070,0x00000070UL, uint32_t  ))    /*  Sample Size */
#define BITM_AFE_STATSCON_RESRVED            (_ADI_MSK_3(0x0000000E,0x0000000EUL, uint32_t  ))    /*  Reserved */
#define BITM_AFE_STATSCON_STATSEN            (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Statistics Enable */
#define ENUM_AFE_STATSCON_DIS                (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  STATSEN: Disable Statistics */
#define ENUM_AFE_STATSCON_EN                 (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  STATSEN: Enable Statistics */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_STATSMEAN                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_STATSMEAN_MEAN               0            /*  Mean Output */
#define BITM_AFE_STATSMEAN_MEAN              (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  Mean Output */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_REPEATADCCNV                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_REPEATADCCNV_NUM             4            /*  Repeat Value */
#define BITP_AFE_REPEATADCCNV_EN              0            /*  Enable Repeat ADC Conversions */
#define BITM_AFE_REPEATADCCNV_NUM            (_ADI_MSK_3(0x00000FF0,0x00000FF0UL, uint32_t  ))    /*  Repeat Value */
#define BITM_AFE_REPEATADCCNV_EN             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Enable Repeat ADC Conversions */
#define ENUM_AFE_REPEATADCCNV_DIS            (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  EN: Disable Repeat ADC Conversions */
#define ENUM_AFE_REPEATADCCNV_EN             (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  EN: Enable Repeat ADC Conversions */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_CALDATLOCK                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_CALDATLOCK_KEY               0            /*  Password for Calibration Data Registers */
#define BITM_AFE_CALDATLOCK_KEY              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Password for Calibration Data Registers */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETHSTIA                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETHSTIA_VALUE         0            /*  HPTIA Offset Calibration */
#define BITM_AFE_ADCOFFSETHSTIA_VALUE        (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  HPTIA Offset Calibration */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINTEMPSENS0                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINTEMPSENS0_VALUE       0            /*  Gain Calibration Temp Sensor Channel */
#define BITM_AFE_ADCGAINTEMPSENS0_VALUE      (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration Temp Sensor Channel */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETTEMPSENS0               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETTEMPSENS0_VALUE     0            /*  Offset Calibration Temp Sensor */
#define BITM_AFE_ADCOFFSETTEMPSENS0_VALUE    (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Temp Sensor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINGN1                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINGN1_VALUE             0            /*  Gain Calibration PGA Gain 1x */
#define BITM_AFE_ADCGAINGN1_VALUE            (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration PGA Gain 1x */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETGN1                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETGN1_VALUE           0            /*  Offset Calibration Gain1 */
#define BITM_AFE_ADCOFFSETGN1_VALUE          (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Gain1 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DACGAIN                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DACGAIN_VALUE                0            /*  HS DAC Gain Correction Factor */
#define BITM_AFE_DACGAIN_VALUE               (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  HS DAC Gain Correction Factor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DACOFFSETATTEN                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DACOFFSETATTEN_VALUE         0            /*  DAC Offset Correction Factor */
#define BITM_AFE_DACOFFSETATTEN_VALUE        (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  DAC Offset Correction Factor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DACOFFSET                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DACOFFSET_VALUE              0            /*  DAC Offset Correction Factor */
#define BITM_AFE_DACOFFSET_VALUE             (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  DAC Offset Correction Factor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINGN1P5                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINGN1P5_VALUE           0            /*  Gain Calibration PGA Gain 1.5x */
#define BITM_AFE_ADCGAINGN1P5_VALUE          (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration PGA Gain 1.5x */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINGN2                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINGN2_VALUE             0            /*  Gain Calibration PGA Gain 2x */
#define BITM_AFE_ADCGAINGN2_VALUE            (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration PGA Gain 2x */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINGN4                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINGN4_VALUE             0            /*  Gain Calibration PGA Gain 4x */
#define BITM_AFE_ADCGAINGN4_VALUE            (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration PGA Gain 4x */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCPGAOFFSETCANCEL               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCPGAOFFSETCANCEL_OFFSETCANCEL  0            /*  Offset Cancellation */
#define BITM_AFE_ADCPGAOFFSETCANCEL_OFFSETCANCEL (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Cancellation */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGNHSTIA                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGNHSTIA_VALUE             0            /*  Gain Error Calibration HS TIA Channel */
#define BITM_AFE_ADCGNHSTIA_VALUE            (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Error Calibration HS TIA Channel */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETLPTIA0                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETLPTIA0_VALUE        0            /*  Offset Calibration for ULP-TIA0 */
#define BITM_AFE_ADCOFFSETLPTIA0_VALUE       (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration for ULP-TIA0 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGNLPTIA0                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGNLPTIA0_VALUE            0            /*  Gain Error Calibration ULPTIA0 */
#define BITM_AFE_ADCGNLPTIA0_VALUE           (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Error Calibration ULPTIA0 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCPGAGN4OFCAL                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCPGAGN4OFCAL_ADCGAINAUX    0            /*  DC Calibration Gain=4 */
#define BITM_AFE_ADCPGAGN4OFCAL_ADCGAINAUX   (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  DC Calibration Gain=4 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINGN9                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINGN9_VALUE             0            /*  Gain Calibration PGA Gain 9x */
#define BITM_AFE_ADCGAINGN9_VALUE            (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration PGA Gain 9x */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETEMPSENS1                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETEMPSENS1_VALUE      0            /*  Offset Calibration Temp Sensor */
#define BITM_AFE_ADCOFFSETEMPSENS1_VALUE     (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Temp Sensor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGAINTEMPSENS1                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGAINTEMPSENS1_VALUE       0            /*  Gain Calibration for Diode Temp Sensor */
#define BITM_AFE_ADCGAINTEMPSENS1_VALUE      (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration for Diode Temp Sensor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DACOFFSETATTENHP                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DACOFFSETATTENHP_VALUE       0            /*  DAC Offset Correction Factor */
#define BITM_AFE_DACOFFSETATTENHP_VALUE      (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  DAC Offset Correction Factor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_DACOFFSETHP                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_DACOFFSETHP_VALUE            0            /*  DAC Offset Correction Factor */
#define BITM_AFE_DACOFFSETHP_VALUE           (_ADI_MSK_3(0x00000FFF,0x00000FFFUL, uint32_t  ))    /*  DAC Offset Correction Factor */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETLPTIA1                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETLPTIA1_VALUE        0            /*  Offset Calibration for ULP-TIA1 */
#define BITM_AFE_ADCOFFSETLPTIA1_VALUE       (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration for ULP-TIA1 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCGNLPTIA1                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCGNLPTIA1_ULPTIA1GN        0            /*  Gain Calibration ULP-TIA1 */
#define BITM_AFE_ADCGNLPTIA1_ULPTIA1GN       (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Gain Calibration ULP-TIA1 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETGN2                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETGN2_VALUE           0            /*  Offset Calibration Auxiliary Channel (PGA Gain =2) */
#define BITM_AFE_ADCOFFSETGN2_VALUE          (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Auxiliary Channel (PGA Gain =2) */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETGN1P5                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETGN1P5_VALUE         0            /*  Offset Calibration Gain1.5 */
#define BITM_AFE_ADCOFFSETGN1P5_VALUE        (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Gain1.5 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETGN9                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETGN9_VALUE           0            /*  Offset Calibration Gain9 */
#define BITM_AFE_ADCOFFSETGN9_VALUE          (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Gain9 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCOFFSETGN4                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCOFFSETGN4_VALUE           0            /*  Offset Calibration Gain4 */
#define BITM_AFE_ADCOFFSETGN4_VALUE          (_ADI_MSK_3(0x00007FFF,0x00007FFFUL, uint32_t  ))    /*  Offset Calibration Gain4 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PMBW                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PMBW_SYSBW                   2            /*  Configure System Bandwidth */
#define BITP_AFE_PMBW_SYSHP                   0            /*  Set High Speed DAC and ADC in High Power Mode */
#define BITM_AFE_PMBW_SYSBW                  (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  Configure System Bandwidth */
#define BITM_AFE_PMBW_SYSHP                  (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  Set High Speed DAC and ADC in High Power Mode */
#define ENUM_AFE_PMBW_BWNA                   (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  SYSBW: no action for system configuration */
#define ENUM_AFE_PMBW_BW50                   (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  SYSBW: 50kHz -3dB bandwidth */
#define ENUM_AFE_PMBW_BW100                  (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  SYSBW: 100kHz -3dB bandwidth */
#define ENUM_AFE_PMBW_BW250                  (_ADI_MSK_3(0x0000000C,0x0000000CUL, uint32_t  ))    /*  SYSBW: 250kHz -3dB bandwidth */
#define ENUM_AFE_PMBW_LP                     (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  SYSHP: LP mode */
#define ENUM_AFE_PMBW_HP                     (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  SYSHP: HP mode */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_SWMUX                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_SWMUX_CMMUX                  3            /*  CM Resistor Select for Ain2, Ain3 */
#define BITP_AFE_SWMUX_SWMUX                  0            /*  ECG Swmux Control */
#define BITM_AFE_SWMUX_CMMUX                 (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  CM Resistor Select for Ain2, Ain3 */
#define BITM_AFE_SWMUX_SWMUX                 (_ADI_MSK_3(0x00000007,0x00000007UL, uint32_t  ))    /*  ECG Swmux Control */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_TEMPCON1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_TEMPCON1_PWD                17            /*  Power Down Control */
#define BITP_AFE_TEMPCON1_EN                 16            /*  Test Signal Enable */
#define BITP_AFE_TEMPCON1_ISWCON              0            /*  Bias Current Selection */
#define BITM_AFE_TEMPCON1_PWD                (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))    /*  Power Down Control */
#define BITM_AFE_TEMPCON1_EN                 (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  Test Signal Enable */
#define BITM_AFE_TEMPCON1_ISWCON             (_ADI_MSK_3(0x0000FFFF,0x0000FFFFUL, uint32_t  ))    /*  Bias Current Selection */
#define ENUM_AFE_TEMPCON1_ACTIVE             (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))
#define ENUM_AFE_TEMPCON1_POWERDOWN          (_ADI_MSK_3(0x00020000,0x00020000UL, uint32_t  ))
#define ENUM_AFE_TEMPCON1_ON                 (_ADI_MSK_3(0x00000000,0x00000000UL, uint32_t  ))    /*  EN: Turn On */
#define ENUM_AFE_TEMPCON1_OFF                (_ADI_MSK_3(0x00010000,0x00010000UL, uint32_t  ))    /*  EN: Turn Off */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_TESTDAC                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_TESTDAC_LPFBYPEN             2            /*  Bypass Low Pass Filter Between Dac and Buffer */
#define BITM_AFE_TESTDAC_LPFBYPEN            (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Bypass Low Pass Filter Between Dac and Buffer */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADCBUFCON                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADCBUFCON_AMPDIS             4            /*  Disable OpAmp. */
#define BITP_AFE_ADCBUFCON_CHOPDIS            0            /*  Disable Chop */
#define BITM_AFE_ADCBUFCON_AMPDIS            (_ADI_MSK_3(0x000001F0,0x000001F0UL, uint32_t  ))    /*  Disable OpAmp. */
#define BITM_AFE_ADCBUFCON_CHOPDIS           (_ADI_MSK_3(0x0000000F,0x0000000FUL, uint32_t  ))    /*  Disable Chop */


/* ============================================================================================================================
        Cortex-M3 Interrupt Controller
   ============================================================================================================================ */

/* ============================================================================================================================
        NVIC0
   ============================================================================================================================ */
#define REG_NVIC0_INTNUM                     0xE000E004            /*  NVIC0 Interrupt Control Type */
#define REG_NVIC0_STKSTA                     0xE000E010            /*  NVIC0 Systick Control and Status */
#define REG_NVIC0_STKLD                      0xE000E014            /*  NVIC0 Systick Reload Value */
#define REG_NVIC0_STKVAL                     0xE000E018            /*  NVIC0 Systick Current Value */
#define REG_NVIC0_STKCAL                     0xE000E01C            /*  NVIC0 Systick Calibration Value */
#define REG_NVIC0_INTSETE0                   0xE000E100            /*  NVIC0 IRQ0..31 Set_Enable */
#define REG_NVIC0_INTSETE1                   0xE000E104            /*  NVIC0 IRQ32..63 Set_Enable */
#define REG_NVIC0_INTCLRE0                   0xE000E180            /*  NVIC0 IRQ0..31 Clear_Enable */
#define REG_NVIC0_INTCLRE1                   0xE000E184            /*  NVIC0 IRQ32..63 Clear_Enable */
#define REG_NVIC0_INTSETP0                   0xE000E200            /*  NVIC0 IRQ0..31 Set_Pending */
#define REG_NVIC0_INTSETP1                   0xE000E204            /*  NVIC0 IRQ32..63 Set_Pending */
#define REG_NVIC0_INTCLRP0                   0xE000E280            /*  NVIC0 IRQ0..31 Clear_Pending */
#define REG_NVIC0_INTCLRP1                   0xE000E284            /*  NVIC0 IRQ32..63 Clear_Pending */
#define REG_NVIC0_INTACT0                    0xE000E300            /*  NVIC0 IRQ0..31 Active Bit */
#define REG_NVIC0_INTACT1                    0xE000E304            /*  NVIC0 IRQ32..63 Active Bit */
#define REG_NVIC0_INTPRI0                    0xE000E400            /*  NVIC0 IRQ0..3 Priority */
#define REG_NVIC0_INTPRI1                    0xE000E404            /*  NVIC0 IRQ4..7 Priority */
#define REG_NVIC0_INTPRI2                    0xE000E408            /*  NVIC0 IRQ8..11 Priority */
#define REG_NVIC0_INTPRI3                    0xE000E40C            /*  NVIC0 IRQ12..15 Priority */
#define REG_NVIC0_INTPRI4                    0xE000E410            /*  NVIC0 IRQ16..19 Priority */
#define REG_NVIC0_INTPRI5                    0xE000E414            /*  NVIC0 IRQ20..23 Priority */
#define REG_NVIC0_INTPRI6                    0xE000E418            /*  NVIC0 IRQ24..27 Priority */
#define REG_NVIC0_INTPRI7                    0xE000E41C            /*  NVIC0 IRQ28..31 Priority */
#define REG_NVIC0_INTPRI8                    0xE000E420            /*  NVIC0 IRQ32..35 Priority */
#define REG_NVIC0_INTPRI9                    0xE000E424            /*  NVIC0 IRQ36..39 Priority */
#define REG_NVIC0_INTPRI10                   0xE000E428            /*  NVIC0 IRQ40..43 Priority */
#define REG_NVIC0_INTCPID                    0xE000ED00            /*  NVIC0 CPUID Base */
#define REG_NVIC0_INTSTA                     0xE000ED04            /*  NVIC0 Interrupt Control State */
#define REG_NVIC0_INTVEC                     0xE000ED08            /*  NVIC0 Vector Table Offset */
#define REG_NVIC0_INTAIRC                    0xE000ED0C            /*  NVIC0 Application Interrupt/Reset Control */
#define REG_NVIC0_INTCON0                    0xE000ED10            /*  NVIC0 System Control */
#define REG_NVIC0_INTCON1                    0xE000ED14            /*  NVIC0 Configuration Control */
#define REG_NVIC0_INTSHPRIO0                 0xE000ED18            /*  NVIC0 System Handlers 4-7 Priority */
#define REG_NVIC0_INTSHPRIO1                 0xE000ED1C            /*  NVIC0 System Handlers 8-11 Priority */
#define REG_NVIC0_INTSHPRIO3                 0xE000ED20            /*  NVIC0 System Handlers 12-15 Priority */
#define REG_NVIC0_INTSHCSR                   0xE000ED24            /*  NVIC0 System Handler Control and State */
#define REG_NVIC0_INTCFSR                    0xE000ED28            /*  NVIC0 Configurable Fault Status */
#define REG_NVIC0_INTHFSR                    0xE000ED2C            /*  NVIC0 Hard Fault Status */
#define REG_NVIC0_INTDFSR                    0xE000ED30            /*  NVIC0 Debug Fault Status */
#define REG_NVIC0_INTMMAR                    0xE000ED34            /*  NVIC0 Mem Manage Address */
#define REG_NVIC0_INTBFAR                    0xE000ED38            /*  NVIC0 Bus Fault Address */
#define REG_NVIC0_INTAFSR                    0xE000ED3C            /*  NVIC0 Auxiliary Fault Status */
#define REG_NVIC0_INTPFR0                    0xE000ED40            /*  NVIC0 Processor Feature Register 0 */
#define REG_NVIC0_INTPFR1                    0xE000ED44            /*  NVIC0 Processor Feature Register 1 */
#define REG_NVIC0_INTDFR0                    0xE000ED48            /*  NVIC0 Debug Feature Register 0 */
#define REG_NVIC0_INTAFR0                    0xE000ED4C            /*  NVIC0 Auxiliary Feature Register 0 */
#define REG_NVIC0_INTMMFR0                   0xE000ED50            /*  NVIC0 Memory Model Feature Register 0 */
#define REG_NVIC0_INTMMFR1                   0xE000ED54            /*  NVIC0 Memory Model Feature Register 1 */
#define REG_NVIC0_INTMMFR2                   0xE000ED58            /*  NVIC0 Memory Model Feature Register 2 */
#define REG_NVIC0_INTMMFR3                   0xE000ED5C            /*  NVIC0 Memory Model Feature Register 3 */
#define REG_NVIC0_INTISAR0                   0xE000ED60            /*  NVIC0 ISA Feature Register 0 */
#define REG_NVIC0_INTISAR1                   0xE000ED64            /*  NVIC0 ISA Feature Register 1 */
#define REG_NVIC0_INTISAR2                   0xE000ED68            /*  NVIC0 ISA Feature Register 2 */
#define REG_NVIC0_INTISAR3                   0xE000ED6C            /*  NVIC0 ISA Feature Register 3 */
#define REG_NVIC0_INTISAR4                   0xE000ED70            /*  NVIC0 ISA Feature Register 4 */
#define REG_NVIC0_INTTRGI                    0xE000EF00            /*  NVIC0 Software Trigger Interrupt Register */
#define REG_NVIC0_INTPID4                    0xE000EFD0            /*  NVIC0 Peripheral Identification Register 4 */
#define REG_NVIC0_INTPID5                    0xE000EFD4            /*  NVIC0 Peripheral Identification Register 5 */
#define REG_NVIC0_INTPID6                    0xE000EFD8            /*  NVIC0 Peripheral Identification Register 6 */
#define REG_NVIC0_INTPID7                    0xE000EFDC            /*  NVIC0 Peripheral Identification Register 7 */
#define REG_NVIC0_INTPID0                    0xE000EFE0            /*  NVIC0 Peripheral Identification Bits7:0 */
#define REG_NVIC0_INTPID1                    0xE000EFE4            /*  NVIC0 Peripheral Identification Bits15:8 */
#define REG_NVIC0_INTPID2                    0xE000EFE8            /*  NVIC0 Peripheral Identification Bits16:23 */
#define REG_NVIC0_INTPID3                    0xE000EFEC            /*  NVIC0 Peripheral Identification Bits24:31 */
#define REG_NVIC0_INTCID0                    0xE000EFF0            /*  NVIC0 Component Identification Bits7:0 */
#define REG_NVIC0_INTCID1                    0xE000EFF4            /*  NVIC0 Component Identification Bits15:8 */
#define REG_NVIC0_INTCID2                    0xE000EFF8            /*  NVIC0 Component Identification Bits16:23 */
#define REG_NVIC0_INTCID3                    0xE000EFFC            /*  NVIC0 Component Identification Bits24:31 */

/* ============================================================================================================================
        NVIC Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTNUM                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTNUM_VALUE                0            /*  Interrupt Control Type */
#define BITM_NVIC_INTNUM_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Interrupt Control Type */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_STKSTA                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_STKSTA_VALUE                0            /*  Systick Control and Status */
#define BITM_NVIC_STKSTA_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Systick Control and Status */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_STKLD                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_STKLD_VALUE                 0            /*  Systick Reload Value */
#define BITM_NVIC_STKLD_VALUE                (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Systick Reload Value */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_STKVAL                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_STKVAL_VALUE                0            /*  Systick Current Value */
#define BITM_NVIC_STKVAL_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Systick Current Value */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_STKCAL                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_STKCAL_VALUE                0            /*  Systick Calibration Value */
#define BITM_NVIC_STKCAL_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Systick Calibration Value */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSETE0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSETE0_VALUE              0            /*  IRQ0..31 Set_Enable */
#define BITM_NVIC_INTSETE0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ0..31 Set_Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSETE1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSETE1_VALUE              0            /*  IRQ32..63 Set_Enable */
#define BITM_NVIC_INTSETE1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ32..63 Set_Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCLRE0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCLRE0_VALUE              0            /*  IRQ0..31 Clear_Enable */
#define BITM_NVIC_INTCLRE0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ0..31 Clear_Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCLRE1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCLRE1_VALUE              0            /*  IRQ32..63 Clear_Enable */
#define BITM_NVIC_INTCLRE1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ32..63 Clear_Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSETP0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSETP0_VALUE              0            /*  IRQ0..31 Set_Pending */
#define BITM_NVIC_INTSETP0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ0..31 Set_Pending */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSETP1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSETP1_VALUE              0            /*  IRQ32..63 Set_Pending */
#define BITM_NVIC_INTSETP1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ32..63 Set_Pending */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCLRP0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCLRP0_VALUE              0            /*  IRQ0..31 Clear_Pending */
#define BITM_NVIC_INTCLRP0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ0..31 Clear_Pending */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCLRP1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCLRP1_VALUE              0            /*  IRQ32..63 Clear_Pending */
#define BITM_NVIC_INTCLRP1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ32..63 Clear_Pending */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTACT0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTACT0_VALUE               0            /*  IRQ0..31 Active Bit */
#define BITM_NVIC_INTACT0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ0..31 Active Bit */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTACT1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTACT1_VALUE               0            /*  IRQ32..63 Active Bit */
#define BITM_NVIC_INTACT1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ32..63 Active Bit */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI0_VALUE               0            /*  IRQ0..3 Priority */
#define BITM_NVIC_INTPRI0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ0..3 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI1_VALUE               0            /*  IRQ4..7 Priority */
#define BITM_NVIC_INTPRI1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ4..7 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI2                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI2_VALUE               0            /*  IRQ8..11 Priority */
#define BITM_NVIC_INTPRI2_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ8..11 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI3                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI3_VALUE               0            /*  IRQ12..15 Priority */
#define BITM_NVIC_INTPRI3_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ12..15 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI4                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI4_VALUE               0            /*  IRQ16..19 Priority */
#define BITM_NVIC_INTPRI4_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ16..19 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI5                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI5_VALUE               0            /*  IRQ20..23 Priority */
#define BITM_NVIC_INTPRI5_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ20..23 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI6                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI6_VALUE               0            /*  IRQ24..27 Priority */
#define BITM_NVIC_INTPRI6_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ24..27 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI7                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI7_VALUE               0            /*  IRQ28..31 Priority */
#define BITM_NVIC_INTPRI7_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ28..31 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI8                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI8_VALUE               0            /*  IRQ32..35 Priority */
#define BITM_NVIC_INTPRI8_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ32..35 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI9                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI9_VALUE               0            /*  IRQ36..39 Priority */
#define BITM_NVIC_INTPRI9_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ36..39 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPRI10                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPRI10_VALUE              0            /*  IRQ40..43 Priority */
#define BITM_NVIC_INTPRI10_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  IRQ40..43 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCPID                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCPID_VALUE               0            /*  CPUID Base */
#define BITM_NVIC_INTCPID_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  CPUID Base */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSTA                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSTA_VALUE                0            /*  Interrupt Control State */
#define BITM_NVIC_INTSTA_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Interrupt Control State */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTVEC                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTVEC_VALUE                0            /*  Vector Table Offset */
#define BITM_NVIC_INTVEC_VALUE               (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Vector Table Offset */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTAIRC                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTAIRC_VALUE               0            /*  Application Interrupt/Reset Control */
#define BITM_NVIC_INTAIRC_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Application Interrupt/Reset Control */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCON0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCON0_SLEEPDEEP           2            /*  deep sleep flag for HIBERNATE mode */
#define BITP_NVIC_INTCON0_SLEEPONEXIT         1            /*  Sleeps the core on exit from an ISR */
#define BITM_NVIC_INTCON0_SLEEPDEEP          (_ADI_MSK_3(0x00000004,0x00000004U, uint16_t  ))    /*  deep sleep flag for HIBERNATE mode */
#define BITM_NVIC_INTCON0_SLEEPONEXIT        (_ADI_MSK_3(0x00000002,0x00000002U, uint16_t  ))    /*  Sleeps the core on exit from an ISR */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCON1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCON1_VALUE               0            /*  Configuration Control */
#define BITM_NVIC_INTCON1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Configuration Control */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSHPRIO0                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSHPRIO0_VALUE            0            /*  System Handlers 4-7 Priority */
#define BITM_NVIC_INTSHPRIO0_VALUE           (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  System Handlers 4-7 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSHPRIO1                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSHPRIO1_VALUE            0            /*  System Handlers 8-11 Priority */
#define BITM_NVIC_INTSHPRIO1_VALUE           (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  System Handlers 8-11 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSHPRIO3                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSHPRIO3_VALUE            0            /*  System Handlers 12-15 Priority */
#define BITM_NVIC_INTSHPRIO3_VALUE           (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  System Handlers 12-15 Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTSHCSR                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTSHCSR_VALUE              0            /*  System Handler Control and State */
#define BITM_NVIC_INTSHCSR_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  System Handler Control and State */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCFSR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCFSR_VALUE               0            /*  Configurable Fault Status */
#define BITM_NVIC_INTCFSR_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Configurable Fault Status */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTHFSR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTHFSR_VALUE               0            /*  Hard Fault Status */
#define BITM_NVIC_INTHFSR_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Hard Fault Status */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTDFSR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTDFSR_VALUE               0            /*  Debug Fault Status */
#define BITM_NVIC_INTDFSR_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Debug Fault Status */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTMMAR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTMMAR_VALUE               0            /*  Mem Manage Address */
#define BITM_NVIC_INTMMAR_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Mem Manage Address */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTBFAR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTBFAR_VALUE               0            /*  Bus Fault Address */
#define BITM_NVIC_INTBFAR_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Bus Fault Address */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTAFSR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTAFSR_VALUE               0            /*  Auxiliary Fault Status */
#define BITM_NVIC_INTAFSR_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Auxiliary Fault Status */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPFR0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPFR0_VALUE               0            /*  Processor Feature Register 0 */
#define BITM_NVIC_INTPFR0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Processor Feature Register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPFR1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPFR1_VALUE               0            /*  Processor Feature Register 1 */
#define BITM_NVIC_INTPFR1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Processor Feature Register 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTDFR0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTDFR0_VALUE               0            /*  Debug Feature Register 0 */
#define BITM_NVIC_INTDFR0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Debug Feature Register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTAFR0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTAFR0_VALUE               0            /*  Auxiliary Feature Register 0 */
#define BITM_NVIC_INTAFR0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Auxiliary Feature Register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTMMFR0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTMMFR0_VALUE              0            /*  Memory Model Feature Register 0 */
#define BITM_NVIC_INTMMFR0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Memory Model Feature Register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTMMFR1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTMMFR1_VALUE              0            /*  Memory Model Feature Register 1 */
#define BITM_NVIC_INTMMFR1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Memory Model Feature Register 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTMMFR2                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTMMFR2_VALUE              0            /*  Memory Model Feature Register 2 */
#define BITM_NVIC_INTMMFR2_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Memory Model Feature Register 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTMMFR3                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTMMFR3_VALUE              0            /*  Memory Model Feature Register 3 */
#define BITM_NVIC_INTMMFR3_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Memory Model Feature Register 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTISAR0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTISAR0_VALUE              0            /*  ISA Feature Register 0 */
#define BITM_NVIC_INTISAR0_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  ISA Feature Register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTISAR1                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTISAR1_VALUE              0            /*  ISA Feature Register 1 */
#define BITM_NVIC_INTISAR1_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  ISA Feature Register 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTISAR2                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTISAR2_VALUE              0            /*  ISA Feature Register 2 */
#define BITM_NVIC_INTISAR2_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  ISA Feature Register 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTISAR3                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTISAR3_VALUE              0            /*  ISA Feature Register 3 */
#define BITM_NVIC_INTISAR3_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  ISA Feature Register 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTISAR4                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTISAR4_VALUE              0            /*  ISA Feature Register 4 */
#define BITM_NVIC_INTISAR4_VALUE             (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  ISA Feature Register 4 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTTRGI                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTTRGI_VALUE               0            /*  Software Trigger Interrupt Register */
#define BITM_NVIC_INTTRGI_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Software Trigger Interrupt Register */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID4                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID4_VALUE               0            /*  Peripheral Identification Register 4 */
#define BITM_NVIC_INTPID4_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Register 4 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID5                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID5_VALUE               0            /*  Peripheral Identification Register 5 */
#define BITM_NVIC_INTPID5_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Register 5 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID6                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID6_VALUE               0            /*  Peripheral Identification Register 6 */
#define BITM_NVIC_INTPID6_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Register 6 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID7                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID7_VALUE               0            /*  Peripheral Identification Register 7 */
#define BITM_NVIC_INTPID7_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Register 7 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID0_VALUE               0            /*  Peripheral Identification Bits7:0 */
#define BITM_NVIC_INTPID0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Bits7:0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID1_VALUE               0            /*  Peripheral Identification Bits15:8 */
#define BITM_NVIC_INTPID1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Bits15:8 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID2                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID2_VALUE               0            /*  Peripheral Identification Bits16:23 */
#define BITM_NVIC_INTPID2_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Bits16:23 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTPID3                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTPID3_VALUE               0            /*  Peripheral Identification Bits24:31 */
#define BITM_NVIC_INTPID3_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Peripheral Identification Bits24:31 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCID0                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCID0_VALUE               0            /*  Component Identification Bits7:0 */
#define BITM_NVIC_INTCID0_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Component Identification Bits7:0 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCID1                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCID1_VALUE               0            /*  Component Identification Bits15:8 */
#define BITM_NVIC_INTCID1_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Component Identification Bits15:8 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCID2                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCID2_VALUE               0            /*  Component Identification Bits16:23 */
#define BITM_NVIC_INTCID2_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Component Identification Bits16:23 */

/* -------------------------------------------------------------------------------------------------------------------------
          NVIC_INTCID3                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_NVIC_INTCID3_VALUE               0            /*  Component Identification Bits24:31 */
#define BITM_NVIC_INTCID3_VALUE              (_ADI_MSK_3(0xFFFFFFFF,0xFFFFFFFFUL, uint32_t  ))    /*  Component Identification Bits24:31 */

/* ====================================================================================================
 *    Interrupt Definitions
 * ==================================================================================================== */
#define INTR_RESET                           (-15)		/* Cortex-M3 Reset */
#define INTR_NonMaskableInt                  (-14)		/* Cortex-M3 Non-maskable Interrupt */
#define INTR_HardFault                       (-13)		/* Cortex-M3 Hardware Fault */
#define INTR_MemoryManagement                (-12)		/* Cortex-M3 Memory Management Interrupt */
#define INTR_BusFault                        (-11)		/* Cortex-M3 Bus Fault */
#define INTR_UsageFault                      (-10)		/* Cortex-M3 Usage Fault */
#define INTR_SVCall                          ( -5)		/* Cortex-M3 SVCall Interrupt */
#define INTR_DebugMonitor                    ( -4)		/* Cortex-M3 Debug Monitor */
#define INTR_PendSV                          ( -2)		/* Cortex-M3 PendSV Interrupt */
#define INTR_SysTick                         ( -1)		/* Cortex-M3 SysTick Interrupt */
#define INTR_RTC1_EVT                          0		/* Event */
#define INTR_XINT_EVT1                         2		/* External Wakeup Interrupt n */
#define INTR_AFE_EVT3                          4		/* AFE Interrupt */
#define INTR_WDT_EXP                           5		/* Digital Die Watchdog */
#define INTR_PMG0_VREG_OVR                     6		/* Voltage Regulator (VREG) Overvoltage */
#define INTR_PMG0_BATT_RANGE                   7		/* Battery Voltage (VBAT) Out of Range */
#define INTR_RTC0_EVT                          8		/* RTC0 Event */
#define INTR_SYS_GPIO_INTA                     9		/* GPIO Interrupt A */
#define INTR_SYS_GPIO_INTB                    10		/* GPIO Interrupt B */
#define INTR_TMR0_EVT                         11		/* Event */
#define INTR_TMR1_EVT                         12		/* Event */
#define INTR_FLCC_EVT                         13		/* Event */
#define INTR_UART_EVT                         14		/* Event */
#define INTR_SPI0_EVT                         15		/* Event */
#define INTR_SPI1_EVT                         16		/* SPI1 interrupt */
#define INTR_I2C_SLV_EVT                      17		/* Slave Event */
#define INTR_I2C_MST_EVT                      18		/* Master Event */
#define INTR_DMA_CHAN_ERR                     19		/* DMA Error */
#define INTR_DMA0_CH0_DONE                    20		/* Channel SPI1_TX Done */
#define INTR_DMA0_CH1_DONE                    21		/* Channel SPI1_RX Done */
#define INTR_DMA0_CH2_DONE                    22		/* Channel 2 Done */
#define INTR_DMA0_CH3_DONE                    23		/* Channel 3 Done */
#define INTR_DMA0_CH4_DONE                    24		/* Channel SPI0_TX Done */
#define INTR_DMA0_CH5_DONE                    25		/* Channel SPI0_RX Done */
#define INTR_DMA0_CH6_DONE                    26		/* Channel 6 Done */
#define INTR_DMA0_CH7_DONE                    27		/* Channel 7 Done */
#define INTR_DMA0_CH8_DONE                    28		/* Channel UART_TX Done */
#define INTR_DMA0_CH9_DONE                    29		/* Channel UART_RX Done */
#define INTR_DMA0_CH10_DONE                   30		/* Channel I2C0_STX Done */
#define INTR_DMA0_CH11_DONE                   31		/* Channel I2C0_SRX Done */
#define INTR_DMA0_CH12_DONE                   32		/* Channel I2C0_MX Done */
#define INTR_DMA0_CH13_DONE                   33		/* Channel AES_IN_Done */
#define INTR_DMA0_CH14_DONE                   34		/* Channel AES_OUT_Done */
#define INTR_DMA0_CH15_DONE                   35		/* Channel FLASH0_Done */
#define INTR_CRYPT_EVT                        38		/* Event */
#define INTR_TMR2_EVT                         40		/* Event */
#define INTR_CLKG_PLL_EVT                     43		/* PLL Event */
#define INTR_RNG0_EVT                         44		/* RNG0_EVT */
#define INTR_AFE_ERROR                        47		/* AFE_ERROR */
#define INTR_AFE_ADC                          48		/* AFE_ADC */
#define INTR_AFE_GEN                          49		/* AFE_GEN */
#define INTR_AFE_CMDFIFO                      50		/* AFE_CMDFIFO */
#define INTR_AFE_DATAFIFO                     51		/* AFE_DATAFIFO */
#define INTR_AFE_Watchdog                     52		/* AFE_Watchdog */
#define INTR_AFE_CRC                          53		/* AFE_CRC */
#define INTR_AFE_GPT0                         54		/* AFE_GPT0 */
#define INTR_AFE_GPT1                         55		/* AFE_GPT1 */
#define INTR_DMA0_CH16_DONE                   56		/* AFE_DMA_CMDFIFO */
#define INTR_DMA0_CH17_DONE                   57		/* AFE_DMA_DATAFIFO */
#define INTR_DMA0_CH18_DONE                   58		/* Channel 18 Done */
#define INTR_DMA0_CH19_DONE                   59		/* Channel 19 Done */
#define INTR_DMA0_CH20_DONE                   60		/* Channel 20 Done */
#define INTR_DMA0_CH21_DONE                   61		/* Channel 21 Done */
#define INTR_DMA0_CH22_DONE                   62		/* Channel 22 Done */
#define INTR_DMA0_CH23_DONE                   63		/* Channel 23 Done */
#define INTR_AGPT0_EVT                        64		/* AGPT0_EVT */
#define INTR_AGPT1_EVT                        65		/* AGPT1_EVT */


#if defined (_MISRA_RULES)
#pragma diag(pop)
#endif /* _MISRA_RULES */

#endif	/* end ifndef _DEF_ADUCM355_H */
