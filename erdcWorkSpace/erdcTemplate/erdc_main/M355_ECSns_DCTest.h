/**
 *****************************************************************************
   @addtogroup EC sensor
   @{
   @file     M355_ECSns_DCTest.h
   @brief    Set of Electrochemical sensor functions.
   @version  V0.1
   @author   ADI
   @date     Aug 2016
   @par Revision History:
   - V0.1, August 2016: initial version.



All files for ADuCM355 provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#ifndef M355_ECSNS_DCTEST_H
#define M355_ECSNS_DCTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355_Peri.h"
#include "stdio.h"


/*==============  Typedefine and Macros  ============*/
/*Sensor configuration*/

//#define WAKEUP_PERIOD   RTC1_PRESCALE_1       // 60/(32768Hz/1) = 1.831mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_2       // 60/(32768Hz/2) = 3.662mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_4       // 60/(32768Hz/4) = 7.324mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_8       // 60/(32768Hz/8) = 14.65mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_16      // 60/(32768Hz/16) = 29.30mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_32      // 60/(32768Hz/32) = 58.59mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_64      // 60/(32768Hz/64) = 117.2mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_128     // 60/(32768Hz/128) = 234.4mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_256     // 60/(32768Hz/256) = 468.8mS
#define WAKEUP_PERIOD   RTC1_PRESCALE_512     // 60/(32768Hz/512) = 937.5mS
//#define WAKEUP_PERIOD   RTC1_PRESCALE_1024    // 60/(32768Hz/1024) = 1.875S
//#define WAKEUP_PERIOD   RTC1_PRESCALE_2048    // 60/(32768Hz/2048) = 3.75S
//#define WAKEUP_PERIOD   RTC1_PRESCALE_4096    // 60/(32768Hz/4096) = 7.5S
//#define WAKEUP_PERIOD   RTC1_PRESCALE_8192    // 60/(32768Hz/8192) = 15S
//#define WAKEUP_PERIOD   RTC1_PRESCALE_16384   // 60/(32768Hz/16384) = 30S
//#define WAKEUP_PERIOD   RTC1_PRESCALE_32768   // 60/(32768Hz/32768) = 60S

typedef struct
{
   uint32_t Enable;
   uint32_t channel;
   uint32_t Vzero;
   uint32_t Vbias;
   LPTIA_RLOAD_Type Rload;
   LPTIA_RGAIN_Type Rtia;
   LPTIA_RF_Type Rfilter;
   char     SensorName[16];
}SNS_CFG_Type;
#define  SENSOR_CHANNEL_ENABLE   (0xAAAA5555u)

/*=========================== Function declarations ====================*/
void SensorInit(void);
void SesorDCTest(void);
SNS_CFG_Type * getSnsCfg(uint32_t channel);
uint8_t SnsInit(SNS_CFG_Type *pSnsCfg);
uint8_t SnsMeasure(uint8_t channel, uint16_t *pResult, uint16_t iNumber);
void RtcPeriodicallyWakeUpInit(void);
void DC_measure(uint32_t cycles);

#ifdef __cplusplus
}
#endif

#endif // #define SENSORLIB_H
