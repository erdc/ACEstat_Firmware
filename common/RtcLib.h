/**
 *****************************************************************************
   @file     RtcLib.h
   @brief    Set of Real Time Clock peripheral functions.
   @version  V0.1
   @author   ADI
   @date     March 2016


All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef RTCLIB_H
#define RTCLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355.h"

//#define RTC_WAIT_SYNC_ONLY


/* ########################### Definitions and Macro ###################### */
#define RTC_FLUSH_SW_KEY    (0xa2c5)
#define RTC_SNAPSHORT_SW_KEY    (0x7627)

typedef enum
{
   RTC1_PRESCALE_1 = 0,
   RTC1_PRESCALE_2,
   RTC1_PRESCALE_4,
   RTC1_PRESCALE_8,
   RTC1_PRESCALE_16,
   RTC1_PRESCALE_32,
   RTC1_PRESCALE_64,
   RTC1_PRESCALE_128,
   RTC1_PRESCALE_256,
   RTC1_PRESCALE_512,
   RTC1_PRESCALE_1024,
   RTC1_PRESCALE_2048,
   RTC1_PRESCALE_4096,
   RTC1_PRESCALE_8192,
   RTC1_PRESCALE_16384,
   RTC1_PRESCALE_32768,
}RTC1_PRE_t;


/* ########################### Function API ######################## */
extern uint8_t RtcCfgCR0(uint16_t uEnMask,uint8_t enable);
extern uint8_t RtcCfgCR1(uint16_t uEnMask,uint8_t enable);

extern uint8_t RtcSetAlarm(uint32_t uAlm1_0,uint16_t uAlm2);
extern uint8_t RtcSetMod60Alarm(uint8_t Units);
extern uint8_t RtcSetCnt(uint32_t uCnt1_0);
extern uint8_t RtcSetPre(RTC1_PRE_t Pre);
extern uint8_t RtcGetSnap(uint32_t *uCnt1_0, uint16_t *uCnt2);

extern uint8_t RtcWaitPendSR1(uint16_t mask);
extern uint8_t RtcWaitSyncSR0(uint16_t mask);
extern uint8_t RtcWaitPendSR2(uint16_t mask);
extern uint8_t RtcWaitSyncSR2(uint16_t mask);

extern uint8_t RtcIntClrSR0(uint16_t uIntMask);
extern uint8_t RtcIntClrSR2(uint16_t uIntMask);

extern uint8_t RtcSetTrim(uint8_t Interval2Exp,uint8_t AddInterval,uint8_t polarity,uint8_t TrimVal);
extern uint8_t RtcFlushWrite(void);
extern uint16_t RtcReadModulo(void);

#ifdef __cplusplus
}
#endif

#endif // #define RTCLIB_H
