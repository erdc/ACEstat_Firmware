
#include <AfeDacLib.h>
#include <AfeTiaLib.h>

#define RCAL0_RCAL1 0
#define AIN1_AIN0 1
#define AIN2_AIN3 2

#define CONNECT_TO_CE 0
#define DISCONNECT_TO_CE 1
/*=========================== Function declarations ====================*/
//void SetupCal_LPRTIA(uint8_t u8Chan, LPTIA_RGAIN_Type LPRTIA, uint8_t u8SelCalResistor);
void SetupCal_LPRTIA (uint8_t u8Chan, LPTIA_RGAIN_Type LPRTIA, uint8_t u8SelCalResistor, uint8_t u8OpenSensor);
void SetupCal_HPRTIA_RTIA2 (HPTIASE_RTIA_Type HPRTIA, uint8_t u8SelCalResistor);
void SetupCal_HPRTIA_RTIA2_3 (uint8_t u8SelCalResistor);
void SetupCal_HPRTIA_RTIA2_5 (uint8_t u8SelCalResistor);
void SetupMeasureHsTia(uint8_t RTIA2_SEL);
uint32_t  InitOffsetCalLPTIA(uint8_t u8Chan);
uint32_t LpTiaOffsetCalAdjust(uint8_t CHAN_NUM,uint32_t FactoryOffsetCal,int32_t iAdcDat);
//uint32_t  MatchPGALPTIAGainCal(uint8_t u8Chan);

