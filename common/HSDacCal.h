
#include <AfeDacLib.h>
#include <AfeTiaLib.h>


/*=========================== Function declarations ====================*/
void DacAttenSetup(uint8_t u8Atten);
uint32_t SwitchSetup(void);
uint32_t HSDacOffsetAdjustFullRange(int32_t iAdcDat);
uint32_t HSDacOffsetAdjustAttenRange(int32_t iAdcDat);
uint32_t GainAdjust(uint8_t u8GainDir);
